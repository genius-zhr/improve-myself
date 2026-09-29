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
    void inrange_demo(Mat &image);//颜色空间转换
    void pixel_count(Mat &image);//像素统计
    void drawing_demo();//绘图,各种几何图形
    void random_demo();//随机数生成
    void drawing_demo2();//多边形的绘制API
    void Mouse_demo(Mat &image);//鼠标响应，拖动绘制
    static void on_draw(int event,int x,int y,int flags,void* userdata);//绘制规则
    void norm_demo(Mat &image);//图像数据处理
    void flip_demo(Mat &image);//图像翻转
    void resize_demo(Mat &image);//放缩与插值
    void rotate_demo(Mat &image);//图像的旋转
    void video_demo(Mat &image);//播放视频，重点了解播放原理
    void blur_demo(Mat &image);//均值滤波，图像模糊
    void gaussian_demo(Mat &image);//高斯模糊
    void bilateral_demo(Mat &image);//双边滤波
    void edge_demo(Mat &image);//边缘检测
    void threshold_demo(Mat &image);//图像二值化
};