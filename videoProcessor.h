#pragma once

#include<QThread>
#include<QMutex>
#include <QtCore>
#include <io.h>
#include <opencv.hpp>
using namespace cv;

class videoProcessor:public QThread
{
public:
    videoProcessor();
    videoProcessor(string &filename);

    //源文件的文件名
    bool setCaptueParams(string &filename);
    //设置输出文件参数，如：文件名，编码器，帧率，是否为彩色视频
    bool setOutPut(string &filename, int codec = 0, double fps = 0.0, bool isColor = true);
    //设置起止帧号
    bool setFrameIndex(int startIndex,int endIndex);
    //写视频文件
    bool writeVideofile();
    //获取已经写入的视频帧数
    int getWritedFrameNum();
    //获取视频帧大小
    Size getFrameSize();
    //获取帧率
    double getFrameRate();
    //获取编码器符号代码
    int getCodec(char codec[4]);

    //设置编码器
    int setCodec(char codec[4]);
    //是否停止处理
    bool isStop();
    //启动写视频器,start之前需要调用该函数
    bool initWriter();

    bool closeWriter();      //关闭写视频器

    void stop();            //停止写线程

    ~videoProcessor();

protected:
    void run();

private:
    cv::VideoWriter writer;		//写视频器
    cv::VideoCapture capture;	//视频处理结构体

    float fps;
    bool ColorFlag;
    int codecIndex;

    volatile int startFrameIndex;
    volatile int endFrameIndex;

    Mat originFrame;			//视频帧
    string outputFileName;		//设置输出视频的名称
    string inputFileName;		//设置原始视频的名称
    volatile int processedFrames;		//已处理的视频帧数
    volatile int writedFrames;			//已经写入的视频帧数
    volatile bool stopFlag;				//是否停止处理

    QMutex mutex;
};

