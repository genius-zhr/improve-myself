#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
#pragma once
class OpenCV{
    public:
    void pixelAccess(Mat& image);////颜色反转
    static void on_trackbar(int value,void *userdata);////进度条回调函数
    void tracking_bar_demo(Mat &image);////进度条
    void Key_demo(Mat &image);////按键响应
    void type_color(Mat &image);////各种颜色滤镜
    void paint_demo();//绘图
    void channel_demo(Mat &image);//通道分离,合并
};