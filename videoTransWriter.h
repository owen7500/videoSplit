#ifndef VIDEOTRANSWRITER_H
#define VIDEOTRANSWRITER_H
/*本类可以实现不同视频格式之间的转码和视频片段的裁剪（根据起止视频帧号）
*注意：类中不实现编解码的功能，即只实现封装格式的转换，
*	  内部的编码格式不进行更改
*     .avi(h264码流)->.mp4(h264码流)
*/
#include <iostream>
#include <string>
#include <io.h>
#include<QThread>
#include<QMutex>

//#define __STDC_CONSTANT_MACROS

//#ifndef UINT64_C
//    #define UINT64_C(value) __CONCAT(value, ULL)
//#endif

#ifndef UINT64_C
    #define UINT64_C(C)  C##ULL
#endif

#ifndef INT64_C
    #define INT64_C(C) C##LL
#endif

//Windows
extern "C"
{
#include "libavutil/common.h"
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}


using namespace std;

class videoTransWriter:public QThread
{
public:
    videoTransWriter();
    ~videoTransWriter();

    bool setInputFileName(string filename);			//设置输入文件名
    bool setOutputFileName(string filename);		//设置输出文件名
    bool initTransWriter();							//初始化转换视频写入
    void closeTransWriter();						//关闭

    void setWriteFrameIndex(int startIndex,int endIndex);	//设置起止帧号
    void startWriter();								//开始写视频
    void stopWriter();								//停止写视频

protected:
    void run();

private:
    bool checkRangeState(int frameIndex);			//判断视频帧号是否在设定的起止帧号之间

    string inputFileName;				//输入文件名
    string outPutFileName;				//输出文件名

    char* cstrInputFileName;
    char* cstrOutputFileName;

    AVOutputFormat *ofmt;				//输出文件格式
    AVFormatContext *ifmt_ctx;			//输入文件的信息
    AVFormatContext *ofmt_ctx;			//输出文件的信息
    AVPacket pkt;						//video packet

    int processedFrameNum;				//当前写入的视频序号
    int startFrameIndex;				//每次写入时的起始帧号
    int endFrameIndex;					//结束帧号
    int totalFrameNum;					//视频总帧数
    int writedFrameNum;					//已写入的视频帧数
    volatile bool stopFlag;				//是否停止写视频
    bool videoEndFlag;					//视频结束帧标记

    QMutex mutex;
};

#endif // VIDEOTRANSWRITER_H
