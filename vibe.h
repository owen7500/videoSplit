#ifndef VIBE_H
#define VIBE_H

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#define NUM_SAMPLES 20      //每个像素点的样本个数
#define MIN_MATCHES 2       //#min指数
#define RADIUS 20           //Sqthere半径
#define SUBSAMPLE_FACTOR 16 //子采样概率


class Vibe
{
public:
    Vibe();
    ~Vibe();
    void init(const Mat _image);   //初始化
    void processFirstFrame(const Mat _image);
    void testAndUpdate(const Mat _image);  //更新
    Mat getMask(void){return m_mask;}
    int ForegroundPixel(Mat binaryImg);
    Mat getColorImg(Mat binaryImg,Mat srcImg);
    Mat getColorForeImg(Mat binaryImg,Mat srcImg);
    cv::Point getCenterPoint(Mat binaryImg);
    int getDerection(Mat binaryImg);

    void setWidth(int width);
    void setHeight(int height);

private:
    Mat m_samples[NUM_SAMPLES];
    Mat m_foregroundMatchCount;
    Mat m_mask;

    int Width;
    int Height;
};  
#endif // VIBE_H
