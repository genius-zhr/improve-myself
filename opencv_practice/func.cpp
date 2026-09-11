#include "func.h"
#include <vector>
void OpenCV::pixelAccess(Mat& image){
    int w=image.cols;
    int h=image.rows;
    int dims=image.channels();
    for(int row=0;row<h;row++){
        for(int col=0;col<w;col++){
            if(dims==1){
                uchar &pix=image.at<uchar>(row,col);
                pix=255-pix;
            }else if(dims==3){
                Vec3b &pix=image.at<Vec3b>(row,col);
                pix[0]=255-pix[0];
                pix[1]=255-pix[1];
                pix[2]=255-pix[2];
            }
        }
    }

}//颜色反转

void OpenCV::on_trackbar(int value,void *userdata){
    Mat *p=(Mat*)userdata;
    if(p->empty()) return;                 // 图片没读进来就不处理,防崩
    Mat dst;
    int delta = value-100;
    if(delta>=0){
        add(*p,Scalar(delta,delta,delta),dst);
    }
    else{
        subtract(*p,Scalar(-delta,-delta,-delta),dst);
    }
    imshow("light",dst);                   // 窗口名必须和 namedWindow 一致
}

void OpenCV::tracking_bar_demo(Mat &image){
    namedWindow("light",WINDOW_AUTOSIZE);
    createTrackbar("light","light",NULL,200,on_trackbar,&image);
    setTrackbarPos("light","light",100);   // 滑条初始拨到中间=原图亮度
    on_trackbar(100,&image);               // 先画一次初始画面
}

void OpenCV::Key_demo(Mat &image){
    cout<<"1.灰度化 2.HSV 3.亮度增加 4.亮度降低"<<endl;
    Mat dst=Mat::zeros(image.size(),image.type());
    imshow("oringin",image);
    while(1){
        int key=waitKey(100);
        if(key==27) break;  // ESC 退出
        else if(key==49){   // 1 键 灰度化
            cvtColor(image,dst,COLOR_BGR2GRAY);
        }
        else if(key==50){   // 2 键 HSV
            cvtColor(image,dst,COLOR_BGR2HSV);
        }
        else if(key==51){   // 3 键
            dst=image+Scalar(50,50,50);  // 亮度增加
        }
        else if(key==52){   // 4 键
            dst=image-Scalar(50,50,50); //亮度降低
        }
        imshow("demo",dst);
    }
}//按键响应

void OpenCV::type_color(Mat &image){
    int color_map[] = {
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_CIVIDIS,
		COLORMAP_COOL,
		COLORMAP_DEEPGREEN,
		COLORMAP_HOT,
		COLORMAP_HSV,
		COLORMAP_INFERNO,
		COLORMAP_JET,
		COLORMAP_MAGMA,
		COLORMAP_OCEAN,
		COLORMAP_PARULA,
		COLORMAP_PINK,
		COLORMAP_PLASMA,
		COLORMAP_RAINBOW,
		COLORMAP_SPRING,
		COLORMAP_SUMMER,
		COLORMAP_TURBO,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED,
		COLORMAP_VIRIDIS,
		//COLORMAP_WINTER
	};
    //namedWindow("color",WINDOW_FREERATIO);
    Mat dst;
    int index=0;
    imshow("oringin",image);
    while(1){
        int key=waitKey(100);
        if(key==27){
            break;
        }
        else if(key>=49 && key<=57){
            applyColorMap(image,dst,color_map[index%21]);
            index++;
            imshow("color",dst);
        }
    }
}

void OpenCV::paint_demo(){
    // int choice=0;
    // cout<<"1.画线 2.画矩形 3.画圆 4.画椭圆 5.画多边形"<<endl;
    // cin>>choice;
    // switch(choice){
    //     case 1:
    //         break;
    //     default:
    //         cout<<"Invalid choice"<<endl;
    // }
    Mat m1=Mat::zeros(400,400,CV_8UC3);
    Mat m2=m1.clone();
    rectangle(m1,Rect(66,88,100,100),Scalar(255,0,255),-1,LINE_8,0);
    rectangle(m2,Rect(116,138,100,100),Scalar(255,255,0),-1,LINE_8,0);
    imshow("m1",m1);
    imshow("m2",m2);
    Mat dst;
    //bitwise_and(m1,m2,dst);
    //bitwise_or(m1,m2,dst);
    //bitwise_not(m1,dst);
    bitwise_xor(m1,m2,dst);
    imshow("dst",dst);
}

void OpenCV::channel_demo(Mat &image){
    vector<Mat> channels;
    split(image,channels);
    imshow("oringin",image);
    // imshow("B",channels[0]);
    // imshow("G",channels[1]);
    // imshow("R",channels[2]);
    //channels[0]=155;
    //channels[2]=0;
    // Mat dst;
    // merge(channels,dst);
    // imshow("merge",dst);
    // Mat dst;
    // merge(channels,dst);//合并通道
    // imshow("merge",dst);
    Mat dst=image.clone();
    int from_to[]={0,2,1,1,2,0};//必须传数组名，参数是一个指针
    mixChannels(&image,1,&dst,1,from_to,3);//交换通道
    imshow("mixChannels",dst);
}