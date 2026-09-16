#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
void on_circle(int event,int x,int y,int flags,void*userdata){
    static Point sp(-1,-1);        // 起点;(-1,-1) 表示"当前没在拖拽"
    static Mat oringin;            // 干净底图,用来擦掉上一帧的圆
    Mat img=*((Mat*)userdata);     // 浅拷贝,和原图共享像素数据

    if(event==EVENT_LBUTTONDOWN){  // ---- 按下:记起点 + 拍一张干净底图 ----
        if(oringin.empty()){
            img.copyTo(oringin);
        }
        sp=Point(x,y);
        return;
    }
    if(sp.x<0) return;             // 没在拖拽,其余事件(右键/滚轮等)一律忽略

    // ---- 下面只在"按住拖动"期间执行 ----
    if(event==EVENT_LBUTTONUP||event==EVENT_MOUSEMOVE){
        Point ep(x,y);
        Point center((sp.x+ep.x)/2,(sp.y+ep.y)/2);  // 圆心 = 起点终点的中点
        double radius=norm(ep-sp)/2.0;              // 半径 = 半弦长

        oringin.copyTo(img);           // 1. 先还原干净底图 → 擦掉上一帧的圆
        if(radius>1){
            circle(img,center,radius,Scalar(0,0,255),2,LINE_AA,0); // 2. 画这一帧的圆
        }
        imshow("mouse_drawing",img);   // 3. 刷新窗口 ← 这步才产生"动画"

        if(event==EVENT_LBUTTONUP){    // 4. 松开 → 本次拖拽结束,抠出圆形区域
            if(radius>1){
                Mat mask=Mat::zeros(oringin.size(),CV_8UC1);  // 和原图同尺寸的单通道黑图
                circle(mask,center,radius,Scalar(255),-1,LINE_8,0); // thickness=-1 → 实心白圆
                Mat roi;
                oringin.copyTo(roi,mask);  // 只拷 mask 非零的像素,其余留 0(黑)
                imshow("roi",roi);
            }
            sp=Point(-1,-1);           // 复位:下次按下才能重新开始
        }
    }
}

void mouse_circle_demo(Mat &image){
    namedWindow("mouse_drawing",WINDOW_AUTOSIZE);
    namedWindow("roi",WINDOW_AUTOSIZE);
    setMouseCallback("mouse_drawing",on_circle,(void*)(&image));
    imshow("mouse_drawing",image);
}
int main(){
    Mat image=imread("/home/zhanghaoran/image/kk.jpg");
    mouse_circle_demo(image);
    waitKey(0);
    return 0;
}
