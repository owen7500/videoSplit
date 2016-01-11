#ifndef VIDEOGUI_H
#define VIDEOGUI_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDialog>
#include <QLineEdit>
#include <QSpacerItem>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QImage>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QProgressDialog>
#include <QProgressBar>
#include <windows.h>

#include <iostream>
#include <fstream>
#include <opencv.hpp>

#include "videoProcessor.h"
//#include "videoTransWriter.h"
#include "vibe.h"

/*两段动态视频之间的最大间隙时间（单位秒）
 * 若大于该时间则分为两段视频
 * 否则化为同一段动态视频
 * */
#define GAPFACTOR 4
#define  STARTREDUNCE 2

using namespace std;
using namespace cv;

namespace Ui {
class videoGUI;
}

class videoGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit videoGUI(QWidget *parent = 0);

    bool openVideoCaptue(QString fileName);

    //前景检测算法
    bool frameDifAlgorithm(Mat leftFrame, Mat rightFrame, Mat &resultFrame, float& forePercentage);		//普通帧间差分
    bool multiThredFrameDif(Mat leftFrame, Mat rightFrame, Mat &resultFrame, int& blockNum, float& forePercentage);//分块多阀值帧间差分
    bool vibeForegroundDetect(Mat frame, Mat &resultFrame, float& forePercentage);

    void startProcess();     //开始切分视频
    void stopProcess();      //停止切分视频
    bool setProcessPrefrences(bool visionFlag);	//设置处理时的喜好，即是否显示视频窗口
    double getForeGroundPixelPercent(Mat frame, int& forePixelCount, double weightValue);

    bool chooseAlgorithm(int method);   //算法选择
    void drawLineOnImg(Mat& frame);     //用于对图像分块显示
    ~videoGUI();

private slots:
    void on_fileOpenBtn_clicked();

    void on_closeBtn_clicked();

    void on_cancelBtn_clicked();

    void on_splitProcessBtn_clicked();

    void showImg();

    void getOutFileName();

    void on_messageTextBrowser_textChanged();

    void on_setOutputAction_triggered();

    void on_displayAction_triggered();

    void on_frameDifAlgAction_triggered();

    void on_multiThrhldFramedifAction_triggered();

    void on_vibeAlgAction_triggered();

    void on_fileOpenAction_triggered();

    void on_exitAction_triggered();

    void closeEvent(QCloseEvent*);

    void on_versionAction_triggered();

    void on_usedToolAction_triggered();

private:
    int getCodec(char codec[4]);            //获取编码器
    bool compareCharArray(char srcArray[],char destArray[],int len);   //检测字符数组是否相等
    bool setOutPutFileNameByInput(QString inputName);

    //写日志
    bool writeLogFile(string text);

    Ui::videoGUI *ui;
    QProgressDialog* processRate;

    QString srcVideoName;
    string capFileName;              //文件名转字符串，作为videocapture的参数
    string outPutFileName;           //动态视频文件名
    string logFileName;

    VideoCapture capture;
    Mat originFrame;
    //以下三帧图像用于隔帧帧差法
    Mat firstFrame;
    Mat secondFrame;
    Mat lastFrame;

    long videoFrameCount;           //视频文件的帧数总和
    bool stopFlag;
    bool firstFlag;
    bool showFlag;
    bool outputNameFlag;

    int AlgMethod;                      //0表示普通帧间差分，1表示分块帧间差分,2表示VIBE，默认为分块帧间差分
    videoProcessor* myVideoWriter;		//写视频器
    //videoTransWriter* H264Writer;       //专门针对H264编码的视频进行编码
    Vibe vibe_Bgs;						//vibe类，使用VIBE算法进行前景检测

    QLineEdit* outputFileLineEdit;
    int codecId;
};

#endif // VIDEOGUI_H
