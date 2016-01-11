#include "videoProcessor.h"


videoProcessor::videoProcessor()
{
    processedFrames = 0;			//视频帧数初始化
    writedFrames = 0;
    stopFlag = false;
    ColorFlag = true;
    codecIndex = -1;
    fps = 25;
    startFrameIndex = 0;
    endFrameIndex = 0;
}

videoProcessor::videoProcessor(string &filename)
{
    if (_access(filename.c_str(), 0) == -1)
    {
        printf("no such file!\n");
        return;
    }
    else
        capture.open(filename.c_str());

    processedFrames = 0;			//视频帧数初始化
    writedFrames = 0;
    inputFileName = filename;		//设置文件名
    stopFlag = false;
    ColorFlag = true;
    codecIndex = -1;
    fps = 25;
    startFrameIndex = 0;
    endFrameIndex = 0;
}

videoProcessor::~videoProcessor()
{
}

void videoProcessor::run()
{
     writeVideofile();
}

//获取帧率
double videoProcessor::getFrameRate()
{
    double fps = capture.get(CV_CAP_PROP_FPS);	//获取帧率
    return fps;
}

//获取编码器代码
int videoProcessor::getCodec(char codec[4])
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
int videoProcessor::setCodec(char codec[4])
{
    union MyUnion
    {
        int value;
        char code[4];
    }codeValue;
    codeValue.code[0] = codec[0];
    codeValue.code[1] = codec[1];
    codeValue.code[2] = codec[2];
    codeValue.code[3] = codec[3];

    return codeValue.value;
}

bool videoProcessor::setCaptueParams(string &filename)
{
    inputFileName = filename;		//设置capture的参数
    if (inputFileName.length())
        return true;
    else
        return false;
}

bool videoProcessor::setOutPut(string &filename,int codec/*=0*/, double fps/*=0.0*/, bool isColor/*=true*/)
{
    char setCodeArray[4] = {'X','V','I','D'};

    outputFileName = filename;
    //获取帧率
    if (fps==0.0)
        fps = getFrameRate();
    char codecArray[4];
    //使用相同编码格式
    if (codec == 0)
        codec = getCodec(codecArray);
    else
        codec = setCodec(setCodeArray);
    //打开输出视频
    return writer.open(outputFileName, codec, fps, getFrameSize(),isColor);
}

bool videoProcessor::setFrameIndex(int startIndex, int endIndex)
{
    {
        QMutexLocker locker(&mutex);
        //mutex.lock();
        startFrameIndex = startIndex;
        endFrameIndex = endIndex;
        //mutex.unlock();
    }
    return true;
}

//写视频，开始帧为startFrameIndex,结束帧为endFrameIndex.成功返回true
bool videoProcessor::writeVideofile()
{
    {
    QMutexLocker locker(&mutex);
    //mutex.lock();
    stopFlag = false;

    qDebug()<<tr("start Frame:")<<startFrameIndex<<endl;
    qDebug()<<tr("end Frame:")<<endFrameIndex<<endl;
    //起止位置检测
    if (startFrameIndex>endFrameIndex)
    {
        printf("frame index out of range!\n");
        stopFlag = true;
        return (!stopFlag);
    }
    //起始位置若小于零，置为0
    if (startFrameIndex < 0)
        startFrameIndex = 0;

    while (!stopFlag)
    {
        //为保证准确定位视频帧，对视频文件进行全解码（逐帧读取）
        if (processedFrames<startFrameIndex)
        {
            capture >> originFrame;
            if(originFrame.empty())
            {
                stopFlag = true;
                break;
            }
            processedFrames++;
        }
        else if (processedFrames<endFrameIndex)
        {
            capture >> originFrame;
            if(originFrame.empty())
            {
                stopFlag = true;
                break;
            }
            writer.write(originFrame);		//写视频
            processedFrames++;				//处理帧
            writedFrames++;					//已写入的视频帧数
        }
        else
        {
            stopFlag = true;
        }
    }
    qDebug()<<processedFrames<<endl;
    }
    //mutex.unlock();
    return (!stopFlag);		//如果stopFlag为假，则说明写入成功呢，否则存在误差
}

//启动写视频器
bool videoProcessor::initWriter()
{
    if(!writer.isOpened())
    {
        setOutPut(outputFileName,-1,getFrameRate(),true);
    }
    stopFlag = false;
    return stopFlag;
}

bool videoProcessor::closeWriter()
{
    while(!stopFlag);
    writer.release();
    return true;
}

void videoProcessor::stop()
{

}
//判断是否停止处理
bool videoProcessor::isStop()
{
    return stopFlag;
}

//获取已经写入的帧数
int videoProcessor::getWritedFrameNum()
{
    return writedFrames;
}

//获取视频帧的大小格式
Size videoProcessor::getFrameSize()
{
    Size frameSize;

    frameSize.height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    frameSize.width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    return frameSize;
}
