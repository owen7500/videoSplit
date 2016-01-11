#include "videogui.h"
#include "ui_videogui.h"

videoGUI::videoGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::videoGUI)
{
    ui->setupUi(this);
    setWindowTitle("视频切分");

    ui->splitProcessBtn->setEnabled(false);
    ui->cancelBtn->setEnabled(false);
    ui->displayAction->setChecked(true);

    stopFlag = false;
    showFlag = true;
    firstFlag = true;
    outputNameFlag = false;
    videoFrameCount = 0;
    AlgMethod = 1;      //默认选择分块帧间差分
    outPutFileName = "E:\\srcVideo\\dv_18.avi";
    logFileName = "videoSearchProgram_log.edt";

    /*动静态切分算法action的互斥选择设置*/
    QActionGroup* algrithmAction = new QActionGroup(this);
    algrithmAction->addAction(ui->frameDifAlgAction);
    algrithmAction->addAction(ui->multiThrhldFramedifAction);
    algrithmAction->addAction(ui->vibeAlgAction);
    algrithmAction->setExclusive(true);
    ui->multiThrhldFramedifAction->setChecked(true);    //默认勾选分块帧间差分

    /*获取启动时间，写日志*/
    QDateTime startTime = QDateTime::currentDateTime();
    QString logStr = QString("启动时间：")+startTime.toString("yyyy-MM-dd hh:mm:ss ddd");
    writeLogFile(logStr.toStdString());
}

bool videoGUI::openVideoCaptue(QString fileName)
{
    capture.open(fileName.toStdString().c_str());
    if (!capture.isOpened())
    {
        string errmsg = "can't initialize the videoCapture!";
        cerr << "can't initialize the videoCapture!" << endl;
        writeLogFile(errmsg);
        return false;
    }
    else
        return true;
}

bool videoGUI::frameDifAlgorithm(Mat leftFrame, Mat rightFrame, Mat &resultFrame, float &forePercentage)
{
    Mat ldstFrame, rdstFrame;
    int forePixelCount = 0;
    bool dynamicVideoFlag = false;
    forePercentage = 0.0;

    //预处理，中值滤波
    //medianBlur(leftFrame, ldstFrame, 3);
    //medianBlur(rightFrame, rdstFrame, 3);

    //高斯滤波
    GaussianBlur(leftFrame, ldstFrame, Size(7, 7),0,0);
    GaussianBlur(rightFrame, rdstFrame, Size(7,7),0,0);

    //均值滤波
    //blur(leftFrame, ldstFrame, Size(3,3),Point(-1,-1));
    //blur(rightFrame, rdstFrame, Size(3,3),Point(-1,-1));

    ////双边滤波
    //bilateralFilter(leftFrame, ldstFrame, 5, 10.0, 2.0);
    //bilateralFilter(rightFrame, rdstFrame, 5, 10.0, 2.0);


    cvtColor(ldstFrame, ldstFrame, CV_BGR2GRAY);
    cvtColor(rdstFrame, rdstFrame, CV_BGR2GRAY);

    if (resultFrame.empty())
    {
        resultFrame.create(ldstFrame.rows, ldstFrame.cols, ldstFrame.type());
    }

    absdiff(ldstFrame, rdstFrame, resultFrame);
    //adaptiveThreshold(resultFrame, resultFrame, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 21, 5);
    adaptiveThreshold(resultFrame, resultFrame, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 21, 7);

    forePercentage = getForeGroundPixelPercent(resultFrame, forePixelCount, 1);
    if (forePercentage > 0.75)
        dynamicVideoFlag = true;
    else
        dynamicVideoFlag = false;

    return dynamicVideoFlag;
}

bool videoGUI::multiThredFrameDif(Mat leftFrame, Mat rightFrame, Mat &resultFrame, int &blockNum, float &forePercentage)
{
    Mat lastFrameBlock[9], firstFrameBlock[9], cutFrameBlock[9];					//图像分块
    int forePixelcount = 0,totalForePixelCount =0;									//前景点统计
    float forePixelPercent[9] = {0}, percentCount = 0.0;
    bool hasMovingObject = false;							//是否存在运动目标
    Mat ldstFrame, rdstFrame;

    resultFrame.create(leftFrame.rows,leftFrame.cols,CV_8UC1);
    resultFrame.setTo(0);

    static float percentThreshold[10] = { 1.6, 2.2, 2, 2.1, 1.5, 0.8, 0.8, 1.4, 1.9, 8 };				//分块阀值
    static double WeightThreshold[9] = { 1, 1, 1, 1.5, 2, 1.8, 1.3, 1.1, 0.8 };									//像素点加权值

    //矩阵长宽定义
    static int rows = leftFrame.rows;
    static int cols = leftFrame.cols;

    static int rowSeg1 = (int)(rows / 3);
    static int colSeg1 = (int)(cols / 3);

    static int rowSeg2 = rowSeg1 * 2;
    static int colSeg2 = colSeg1 * 2;

    //矩阵分块及关键点的定义
    /**A*********B**************C****************P
    --------5-----------6----------------9--------
    ***D*********E**************F****************O
    --------4-----------7----------------8--------
    ***G*********H**************I****************N
    --------1-----------2----------------3--------
    ***J*********K**************L****************M
    */
    static Point A(0, 0), B(colSeg1, 0), C(colSeg2, 0), D(0, rowSeg1);
    static Point E(colSeg1, rowSeg1), F(colSeg2, rowSeg1), G(0, rowSeg2), H(colSeg1, rowSeg2);
    static Point I(colSeg2, rowSeg2), J(0, rows - 1), K(colSeg1, rows - 1), L(colSeg2, rows - 1);
    static Point M(cols - 1, rows - 1), N(cols - 1, rowSeg2), O(cols - 1, rowSeg1), P(cols - 1, 0);

    static Rect blockRects[9] = { Rect(G, K), Rect(H, L), Rect(I, M), Rect(D, H), Rect(A, E),
        Rect(B, F), Rect(E, I), Rect(F, N), Rect(C, O) };

    for (int i = 0; i < 9;i++)
    {
        //定义感兴趣区域
        lastFrameBlock[i] = leftFrame(blockRects[i]);
        firstFrameBlock[i] = rightFrame(blockRects[i]);
        cutFrameBlock[i] = resultFrame(blockRects[i]);

        //高斯滤波
        GaussianBlur(lastFrameBlock[i], ldstFrame, Size(7, 7), 0, 0);
        GaussianBlur(firstFrameBlock[i], rdstFrame, Size(7, 7), 0, 0);

        cvtColor(ldstFrame, ldstFrame, CV_BGR2GRAY);
        cvtColor(rdstFrame, rdstFrame, CV_BGR2GRAY);

        absdiff(ldstFrame, rdstFrame, cutFrameBlock[i]);
        adaptiveThreshold(cutFrameBlock[i], cutFrameBlock[i], 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 21, 7);

        forePixelPercent[i] = getForeGroundPixelPercent(cutFrameBlock[i], forePixelcount,WeightThreshold[i]);

        if (forePixelPercent[i]>percentThreshold[i])
        {
            hasMovingObject = true;
            blockNum = i+1;
            forePercentage = forePixelPercent[i];
            break;
        }
        totalForePixelCount += forePixelcount;
    }

    //前景像素总百分比
    percentCount = (float)totalForePixelCount / (float)(leftFrame.cols*leftFrame.rows);

    if (!hasMovingObject)
    {
        if (percentCount>percentThreshold[9])
            hasMovingObject = true;

        blockNum = 0;
        forePercentage = percentCount;
    }
    return hasMovingObject;
}

bool videoGUI::vibeForegroundDetect(Mat frame, Mat &resultFrame, float &forePercentage)
{
    static int frameIndex = 1;

    forePercentage = 0;
    bool hasMovingObject = false;

    cvtColor(frame, frame, COLOR_RGB2GRAY);

    if (resultFrame.empty())
    {
        resultFrame.create(frame.rows, frame.cols, CV_8UC1);
        resultFrame.setTo(0);
    }

    if (frameIndex ==1)
    {
        vibe_Bgs.init(frame);
        vibe_Bgs.processFirstFrame(frame);
        hasMovingObject = false;
    }
    else
    {
        vibe_Bgs.testAndUpdate(frame);
        resultFrame = vibe_Bgs.getMask();         //获取二值前景图
        morphologyEx(resultFrame, resultFrame, MORPH_OPEN, Mat());

        int ForePixel = vibe_Bgs.ForegroundPixel(resultFrame);
        forePercentage = float(ForePixel * 100) / (float)(frame.cols*frame.rows);

        if (forePercentage>0.9)
        {
            hasMovingObject = true;
        }
    }

    return hasMovingObject;
}

bool videoGUI::setProcessPrefrences(bool visionFlag)
{
    showFlag = visionFlag;
    if(showFlag)
        writeLogFile("显示处理画面");
    else
        writeLogFile("不显示处理画面");
    return showFlag;
}

double videoGUI::getForeGroundPixelPercent(Mat frame, int &forePixelCount, double weightValue)
{
    forePixelCount = 0;
    float forePixelPercent = 0;

    int rows = frame.rows;      //行数
    int cols = frame.cols*frame.channels();      //列数

    if (frame.isContinuous())
    {
        cols = rows*cols;
        rows = 1;
    }

    for (int j = 0; j < rows; j++)
    {
        uchar* mdata = frame.ptr<uchar>(j);
        for (int i = 0; i<cols; i++)
        {
            if (mdata[i] == 255)
                forePixelCount++;
        }
    }

    forePixelCount =(int)(forePixelCount*weightValue);		//像素点加权

    forePixelPercent = (float)(forePixelCount / ((float)(rows*cols)));
    forePixelPercent *= 100;		//化为百分比

    return forePixelPercent;
}

bool videoGUI::chooseAlgorithm(int method)
{
    AlgMethod = method;
    return true;
}

void videoGUI::drawLineOnImg(Mat &frame)
{
    //矩阵长宽定义
    int rowSeg1, rowSeg2, colSeg1, colSeg2;
    rowSeg1 = (int)(frame.rows / 3);
    colSeg1 = (int)(frame.cols / 3);

    rowSeg2 = rowSeg1 * 2;
    colSeg2 = colSeg1 * 2;

    Scalar colorFill;
    if (frame.channels()==1)
    {
        colorFill = Scalar(255);
    }
    else
    {
        colorFill = Scalar(255,255,255);
    }

    line(frame, Point(colSeg1, 0), Point(colSeg1, frame.rows - 1), colorFill);
    line(frame, Point(colSeg2, 0), Point(colSeg2, frame.rows - 1), colorFill);
    line(frame, Point(0, rowSeg1), Point(frame.cols - 1, rowSeg1), colorFill);
    line(frame, Point(0, rowSeg2), Point(frame.cols - 1, rowSeg2), colorFill);
    return;
}

videoGUI::~videoGUI()
{
    delete processRate;
    delete myVideoWriter;
    delete outputFileLineEdit;
    delete ui;
}

void videoGUI::on_fileOpenBtn_clicked()
{
    srcVideoName = QFileDialog::getOpenFileName(this,QString("源视频"),QString("E:\\"),tr("video *.avi *.mp4 *.rmvb *.wmv"),0,0);
    ui->fileNameEdit->setText(srcVideoName);

    //文件名不为空，显示视频的第一帧
    if(!srcVideoName.isEmpty())
    {
        capFileName = srcVideoName.toStdString();

        capture.open(capFileName.c_str());
        capture>>lastFrame;                                          //获取第一帧图像，用于显示
        firstFlag = false;
        videoFrameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);     //获取帧总数

        //显示第一帧图像
        QImage img = QImage((const unsigned char*)lastFrame.data,lastFrame.cols,lastFrame.rows,QImage::Format_RGB888);
        ui->imageLabel->setPixmap(QPixmap::fromImage(img));

        string msg = "打开文件成功！文件名：";
        msg = msg+capFileName;
        writeLogFile(msg);
        //文件已经打开，处理选项使能
        ui->splitProcessBtn->setEnabled(true);
        this->update();
    }
    else
    {
        ui->messageTextBrowser->insertPlainText(tr("No such file"));
        return;
    }
 }

void videoGUI::on_closeBtn_clicked()
{
    close();
    exit(20151216);
}

void videoGUI::on_cancelBtn_clicked()
{
    //vSpliter->stopProcess();
    stopFlag = true;
}

void videoGUI::on_splitProcessBtn_clicked()
{
    //int i = 0;
    int blockNum = 0;					//分块号，用返回对应块号的前景点比例
    static int dynamicVideoSeg = 1;		//存在运动物体的段数
    bool hasMovingObjectFlag = false;	//判断是否存在运动物体
    bool secondFlag = true;			//判断是否为第二帧
    bool dynamicVideoFlag = false;		//动态帧判断
    float forePixelPercent;
    stopFlag = false;
    //用于保存log日志的信息，如：使用的算法、运行起止时间、耗时
    QString methodStr;
    QString costTimeStr;
    QString logText;
    //保存帧差结果
    Mat difResultFrame;

    int rate = (int)capture.get(CV_CAP_PROP_FPS);		//视频的帧率
    int dynamicGap = rate * GAPFACTOR;					//两段视频之间最大允许间隔，若大于该间隔将视为两个动态视频进行分割
    int redundanceGap = rate*1;                         //每段视频前预留的冗余帧数，方便后续的跟踪的背景建模
    int totalFrameNum = (int)capture.get(CV_CAP_PROP_FRAME_COUNT);  //获取视频总帧数

    int currentFrameNum = 0;                            //当前视频帧的编号
    int startFrameNum = 0,endFrameNum = 0;              //每段动态视频在原始视频中的起止位置


    setOutPutFileNameByInput(srcVideoName);
    myVideoWriter = new videoProcessor(capFileName);
    myVideoWriter->setOutPut(outPutFileName, 1, 0, true);		//设置参数
    myVideoWriter->initWriter();

    ui->cancelBtn->setEnabled(true);
    //是否停止处理
    __int64 startTime = GetTickCount();

    dynamicVideoSeg = 1;

    if (!capture.isOpened())
        return;
                              //启动写视频
    ui->statusBar->showMessage("动静态切分处理中......");

    if(!showFlag)
    {
        processRate = new QProgressDialog(this);
        processRate->setWindowTitle(tr("动静态切分处理"));
        processRate->setRange(0,videoFrameCount-1);
        processRate->setModal(true);
        processRate->setCancelButtonText(tr("取消"));
        processRate->resize(600,150);

        processRate->setValue(0);
        if(processRate->wasCanceled())
            stopFlag = true;                  //停止处理
    }
    while (!stopFlag)
    {
        capture >> originFrame;		//读取视频
        currentFrameNum++;			//视频帧数自增

        //对视频的最后一部分进行处理时，避免遗漏最后一小段动态帧
        //（如果不判断将出现动态帧的后续静态部分若小于redundanceGap时将不会被保存）
        if(currentFrameNum==totalFrameNum-1)
        {
            dynamicGap = 0;
        }

        if (originFrame.empty())
            break;

        if (firstFlag)
        {
            lastFrame = originFrame.clone();
            firstFlag = false;
        }
        else if (secondFlag)
        {
            secondFrame = lastFrame.clone();
            lastFrame = originFrame.clone();
            secondFlag = false;
        }
        else
        {
            firstFrame = secondFrame.clone();
            secondFrame = lastFrame.clone();
            lastFrame = originFrame.clone();

            if (firstFrame.empty()||lastFrame.empty()||secondFrame.empty())
                break;

            //frameDifAlgorithm(lastFrame, firstFrame, difResultFrame);
            switch (AlgMethod)
            {
            //普通帧间差分算法
            case 0:
                dynamicVideoFlag = frameDifAlgorithm(lastFrame, firstFrame, difResultFrame, forePixelPercent);
                methodStr = "本次使用普通帧间差分算法，耗时：";
                break;
            //分块多阀值帧间差分算法
            case 1:
                dynamicVideoFlag = multiThredFrameDif(lastFrame, firstFrame,difResultFrame, blockNum, forePixelPercent);
                methodStr = "本次使用分块多阀值帧间差分算法，耗时：";
                break;
            //VIBE前景检测算法
            case 2:
                dynamicVideoFlag = vibeForegroundDetect(firstFrame,difResultFrame,forePixelPercent);
                methodStr = "本次使用VIBE前景检测算法，耗时：";
                break;
            //默认使用分块多阀值帧间差分算法
            default:
                dynamicVideoFlag = multiThredFrameDif(lastFrame, firstFrame, difResultFrame, blockNum, forePixelPercent);
                methodStr = "本次使用分块多阀值帧间差分算法，耗时：";
                break;
            }

            //存在动态帧
            if (dynamicVideoFlag)
            {
                //是否为动态视频的第一帧
                if (!hasMovingObjectFlag)
                {
                    startFrameNum = currentFrameNum - redundanceGap;		//保存的动态视频起始帧为动态帧的前redundanceGap帧，用于背景学习
                    if (startFrameNum < 0)
                        startFrameNum = 0;

                    hasMovingObjectFlag = true;
                    dynamicGap = rate * GAPFACTOR;
                }
                //如果dynamicGap小于2倍rate说明连续两秒内有动态视频
                if (dynamicGap<rate*GAPFACTOR)
                {
                    dynamicGap = rate * GAPFACTOR;
                }
                ui->messageTextBrowser->insertPlainText(
                            QString().sprintf("frame:%d,forePixelPercent:%3.2f,There are %d segement of dynamic video!\r",
                                              currentFrameNum,forePixelPercent,dynamicVideoSeg));
            }
            else
            {
                //判断前一帧是否存在运动物体,如果存在则将动态帧设为否
                if (hasMovingObjectFlag)
                {
                    if (dynamicGap>0)		//用于检测在连续两秒内是否存在动态视频，如果存在在不进行裁剪
                    {
                        dynamicGap--;
                    }
                    else
                    {
                        dynamicVideoSeg++;
                        hasMovingObjectFlag = false;

                        endFrameNum = currentFrameNum-rate*(STARTREDUNCE);

                        myVideoWriter->setFrameIndex(startFrameNum, endFrameNum);
                        myVideoWriter->start();
                    }
                }
                ui->messageTextBrowser->insertPlainText(QString().sprintf(
                                                         "frame:%d,forePixelPercent:%3.2f\r",currentFrameNum,forePixelPercent));
            }

            if (showFlag&&(currentFrameNum % 30 == 0))
            //if(showFlag)
            {
                Mat frame = lastFrame.clone();
                cvtColor(frame,frame,CV_RGB2BGR);
                QImage img = QImage((const unsigned char*)frame.data,frame.cols,
                                    frame.rows,QImage::Format_RGB888);
                ui->imageLabel->setPixmap(QPixmap::fromImage(img));
                ui->imageLabel->resize(ui->imageLabel->pixmap()->size());
            }
            if(!showFlag)
            {
                processRate->setValue(currentFrameNum);
                if(processRate->wasCanceled())
                    stopFlag = true;
            }

        }
        qApp->processEvents();
    }
    __int64 endTime = GetTickCount();
    __int64 costTime = endTime - startTime;

    costTimeStr = QString::number(costTime);
    costTimeStr = costTimeStr+"ms";

    if((!stopFlag)&&originFrame.empty())
    {
        ui->messageTextBrowser->insertPlainText(QString("Finished!\n"));
        capture.set(CV_CAP_PROP_POS_FRAMES,0);          //如果处理完毕则将，capture重定位，至于起始处
        stopFlag = true;
        //写程序日志
        logText = methodStr+costTimeStr;
        writeLogFile(logText.toStdString());

        char chSeg[10];
        string temp,msg="动态视频总段数：";
        sprintf(chSeg,"%d",dynamicVideoSeg);
        temp = chSeg;
        msg = msg+temp;
        writeLogFile(msg);
    }
    ui->messageTextBrowser->insertPlainText(QString("the process cost %1 ms").arg(costTime));
    ui->statusBar->showMessage(tr("切分完毕！"),2000);
    myVideoWriter->closeWriter();
}

void videoGUI::showImg()
{
    //将Mat格式转换成QImage格式
    QImage* qImg = new QImage((const unsigned char*)(originFrame.data),originFrame.cols,originFrame.rows,QImage::Format_RGB888);
    //将QImage格式转换成QPixmap格式并显示
    ui->imageLabel->setPixmap(QPixmap::fromImage(*qImg));

    this->update();  //发送刷新消息
    delete qImg;
}

void videoGUI::getOutFileName()
{
    QString filename = outputFileLineEdit->text();
    outPutFileName = filename.toStdString();
    ui->messageTextBrowser->insertPlainText(QString("输出文件名："));
    ui->messageTextBrowser->insertPlainText(filename+"\n");
}

void videoGUI::on_messageTextBrowser_textChanged()
{
    ui->messageTextBrowser->moveCursor(QTextCursor::End);
}

void videoGUI::on_setOutputAction_triggered()
{
    QDialog* dlg = new QDialog(this);
    outputFileLineEdit = new QLineEdit(dlg);
    dlg->setWindowTitle(QString("设置输出文件名"));
    QPushButton *okBtn = new QPushButton(dlg);
    QPushButton *cancelBtn = new QPushButton(dlg);
    QLabel *fileLabel = new QLabel(dlg);

    okBtn->setText(QString("确定"));
    cancelBtn->setText(QString("取消"));
    fileLabel->setText(QString("输出文件名"));

    QHBoxLayout* hlayoutEdit = new QHBoxLayout;
    hlayoutEdit->addWidget(fileLabel);
    hlayoutEdit->addWidget(outputFileLineEdit);
    hlayoutEdit->setSpacing(50);

    QHBoxLayout* hlayoutBtn = new QHBoxLayout;
    hlayoutBtn->insertWidget(1,okBtn,0,Qt::AlignHCenter);
    hlayoutBtn->insertWidget(2,cancelBtn,0,Qt::AlignHCenter);
    hlayoutBtn->setSpacing(50);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addLayout(hlayoutEdit);
    VLayout->addLayout(hlayoutBtn);
    VLayout->setSpacing(20);

    QGridLayout* globLayout = new QGridLayout;
    globLayout->addLayout(VLayout,2,10);

    dlg->setLayout(globLayout);
    dlg->setFixedSize(300,100);

    connect(okBtn,SIGNAL(clicked()),this,SLOT(getOutFileName()));
    connect(okBtn,SIGNAL(clicked()),dlg,SLOT(close()));
    connect(cancelBtn,SIGNAL(clicked()),dlg,SLOT(close()));

    outputFileLineEdit->setText(QString::fromStdString(outPutFileName));
    outputNameFlag = true;
    dlg->show();

    string msg = "设置文件名";
    msg = msg+outPutFileName;
    writeLogFile(msg);

    delete okBtn;
    delete cancelBtn;
    delete VLayout;
    delete hlayoutEdit;
    delete hlayoutBtn;
    delete fileLabel;
    delete globLayout;
    delete dlg;
}

//是否显示
void videoGUI::on_displayAction_triggered()
{
    if(ui->displayAction->isChecked())
        showFlag = true;
    else
        showFlag = false;
}

void videoGUI::on_frameDifAlgAction_triggered()
{
    AlgMethod = 0;      //普通帧间差分算法
}

void videoGUI::on_multiThrhldFramedifAction_triggered()
{
    AlgMethod = 1;      //分块帧间差分算法
}

void videoGUI::on_vibeAlgAction_triggered()
{
    AlgMethod = 2;      //VIBE算法
}

void videoGUI::on_fileOpenAction_triggered()
{
    on_fileOpenBtn_clicked();
}


void videoGUI::on_exitAction_triggered()
{
    on_closeBtn_clicked();
}

void videoGUI::closeEvent(QCloseEvent *)
{
    /*获取退出时间，写日志*/
    QDateTime startTime = QDateTime::currentDateTime();
    QString logStr = QString("关闭时间：")+startTime.toString("yyyy-MM-dd hh:mm:ss ddd");
    writeLogFile(logStr.toStdString());
    exit(20151216);
}

bool videoGUI::writeLogFile(string text)
{
    ofstream logFile(logFileName.c_str(),ios::out|ios::app);
    if(!logFile.is_open())
    {
        cout<<"can not open log file"<<endl;
        return false;
    }
    logFile<<text<<endl;

    logFile.close();
    return true;
}

void videoGUI::on_versionAction_triggered()
{
    QString programName = "       监控视频检索系统\n\n";
    QString versionString = "版本：beta1.0\n";
    QString authorName = "作者：刘文\n";
    QString companyName = "单位：华侨大学\n";
    QString contactName = "联系方式：owen7500@qq.com\n";
    QString copyRight = "      All rights reserved\n";
    QString text = programName+versionString+authorName+companyName+contactName+copyRight;
    QMessageBox::about(this,QString("版本与版权"),text);
}

void videoGUI::on_usedToolAction_triggered()
{
    QMessageBox::aboutQt(this,QString("系统开发工具"));
}

//获取编码器代码
int videoGUI::getCodec(char codec[4])
{
    union
    {
        int value;
        char code[4];
    }codecValue;

    codecValue.value = (int)capture.get(CV_CAP_PROP_FOURCC);	//获取编码器代码

    //获取编码器对应的四位字符代码，如XVID
    codec[0] = codecValue.code[0];
    codec[1] = codecValue.code[1];
    codec[2] = codecValue.code[2];
    codec[3] = codecValue.code[3];

    return codecValue.value;
}

bool videoGUI::compareCharArray(char srcArray[], char destArray[], int len)
{
    bool equalFlag = false;
    for(int i=0;i<len;i++)
    {
        if(srcArray[i]!=destArray[i])
        {
            equalFlag = false;
            break;
        }
        equalFlag = true;
    }
    return equalFlag;
}

bool videoGUI::setOutPutFileNameByInput(QString inputName)
{
    string prefix;
    QFileInfo file = QFileInfo(inputName);
    QString fileName = file.fileName();
    QString pathName = file.absolutePath();

    if(!outputNameFlag)
    {
        if(ui->frameDifAlgAction->isChecked())
            prefix = "/dv_fdif_";
        else if(ui->multiThrhldFramedifAction->isChecked())
            prefix = "/dv_mtfdif_";
        else
            prefix = "/dv_vibe_";

        outPutFileName = prefix+fileName.toStdString();
        outPutFileName = pathName.toStdString() +outPutFileName;

        string msg = "自动设置文件名";
        msg = msg+outPutFileName;
        writeLogFile(msg);

        return true;
    }
    else
        return false;
}
