#include "func.h"
#include <vector>
#include <string>
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

void OpenCV::inrange_demo(Mat &image){
    Mat hsv;
    cvtColor(image,hsv,COLOR_BGR2HSV);//原图先转hsv
    //imshow("HSV",hsv);
    Mat mask;
    inRange(hsv,Scalar(35,43,46),Scalar(77,255,255),mask);//框选颜色范围，范围内变白（255，255，255），外边黑（0，0，0）
    imshow("mask",mask);
    bitwise_not(mask,mask);//黑白反转
    Mat redback=image.clone();
    redback=Scalar(175, 150, 205);//粉色
    image.copyTo(redback,mask);//把原图像复制到粉色背景上，mask为白色的地方才会复制
    imshow("redback",redback);
}

void OpenCV::pixel_count(Mat &image){
    double max_value,min_value;
    Point max_loc,min_loc;
    vector<Mat> channels;
    split(image,channels);
    for(int i=0;i<channels.size();i++){
        minMaxLoc(channels[i],&min_value,&max_value,&min_loc,&max_loc,Mat());
        cout<<"channel:"<<i<<" min_value:"<<min_value<<" max_value:"<<max_value<<endl;
        cout<<"channel:"<<i<<" min_loc:"<<min_loc<<" max_loc:"<<max_loc<<endl;
    }
    Mat mean,stddev;
    meanStdDev(image,mean,stddev);
    cout<<"mean:"<<mean<<endl<<" stddev:"<<stddev<<endl;
}

void OpenCV::drawing_demo(){
    Mat back=Mat::zeros(1000,1000,CV_8UC3);
    back=Scalar(255,255,255);                                              //白纸

    // ================= 天空 =================
    circle(back,Point(140,140),80,Scalar(0,215,255),-1,LINE_AA,0);         //太阳(黄)
    circle(back,Point(700,150),55,Scalar(240,240,240),-1,LINE_AA,0);       //云(左圆)
    circle(back,Point(775,140),70,Scalar(240,240,240),-1,LINE_AA,0);       //云(中圆)
    circle(back,Point(855,155),50,Scalar(240,240,240),-1,LINE_AA,0);       //云(右圆)

    // ================= 草地 =================
    rectangle(back,Rect(0,700,1000,300),Scalar(80,175,90),-1,LINE_AA,0);   //草坪(绿)

    // ================= 小路 =================
    vector<Point> path={Point(465,700),Point(535,700),Point(630,1000),Point(370,1000)};
    fillPoly(back,path,Scalar(200,205,210),LINE_AA);                       //石板路(浅灰梯形)

    // ================= 房子 =================
    rectangle(back,Rect(600,300,60,110),Scalar(90,90,90),-1,LINE_AA,0);    //烟囱(深灰,先画)
    rectangle(back,Rect(300,460,400,240),Scalar(160,190,220),-1,LINE_AA,0);//墙(米黄)

    vector<Point> roof={Point(260,460),Point(740,460),Point(500,280)};     //屋顶三个顶点
    fillPoly(back,roof,Scalar(60,60,180),LINE_AA);                         //屋顶(砖红三角形)

    rectangle(back,Rect(460,570,80,130),Scalar(50,80,130),-1,LINE_AA,0);   //门(棕)
    circle(back,Point(525,635),8,Scalar(30,30,30),-1,LINE_AA,0);           //门把手

    rectangle(back,Rect(340,520,90,90),Scalar(230,210,150),-1,LINE_AA,0);  //左窗玻璃(浅蓝)
    rectangle(back,Rect(340,520,90,90),Scalar(90,90,90),6,LINE_AA,0);      //左窗框
    line(back,Point(385,520),Point(385,610),Scalar(90,90,90),6,LINE_AA,0); //左窗竖棂
    line(back,Point(340,565),Point(430,565),Scalar(90,90,90),6,LINE_AA,0); //左窗横棂

    rectangle(back,Rect(570,520,90,90),Scalar(230,210,150),-1,LINE_AA,0);  //右窗玻璃
    rectangle(back,Rect(570,520,90,90),Scalar(90,90,90),6,LINE_AA,0);      //右窗框
    line(back,Point(615,520),Point(615,610),Scalar(90,90,90),6,LINE_AA,0); //右窗竖棂
    line(back,Point(570,565),Point(660,565),Scalar(90,90,90),6,LINE_AA,0); //右窗横棂

    // ================= 花园 =================
    rectangle(back,Rect(130,620,30,80),Scalar(50,80,130),-1,LINE_AA,0);    //左树干
    circle(back,Point(145,590),75,Scalar(60,150,70),-1,LINE_AA,0);         //左树冠
    rectangle(back,Rect(845,640,30,60),Scalar(50,80,130),-1,LINE_AA,0);    //右树干
    circle(back,Point(860,610),60,Scalar(60,150,70),-1,LINE_AA,0);         //右树冠

    line(back,Point(230,800),Point(230,745),Scalar(60,150,70),6,LINE_AA,0);//花茎(左)
    circle(back,Point(230,735),18,Scalar(80,80,235),-1,LINE_AA,0);         //红花
    line(back,Point(320,880),Point(320,830),Scalar(60,150,70),6,LINE_AA,0);//花茎(中左)
    circle(back,Point(320,820),16,Scalar(0,215,255),-1,LINE_AA,0);         //黄花
    line(back,Point(760,800),Point(760,750),Scalar(60,150,70),6,LINE_AA,0);//花茎(右)
    circle(back,Point(760,740),18,Scalar(230,130,220),-1,LINE_AA,0);       //粉花
    line(back,Point(680,900),Point(680,850),Scalar(60,150,70),6,LINE_AA,0);//花茎(中右)
    circle(back,Point(680,840),16,Scalar(255,255,255),-1,LINE_AA,0);       //白花

    imshow("back",back);
}

void OpenCV::random_demo(){
    Mat rand=Mat(Size(600,600),CV_8UC3);
    int w=rand.cols;
    int h=rand.rows;
    RNG rng(10);
    while(1){
        int key=waitKey(100);
        if(key==27){
            break;
        }
        int x1=rng.uniform(0,w);
        int y1=rng.uniform(0,h);
        int x2=rng.uniform(0,w);
        int y2=rng.uniform(0,h);
        int b=rng.uniform(0,255);
        int g=rng.uniform(0,255);
        int r=rng.uniform(0,255);
        rand=Scalar(0,0,0);
        line(rand,Point(x1,y1),Point(x2,y2),Scalar(b,g,r),1,LINE_8,0);
        imshow("random",rand);
    }
}

void OpenCV::drawing_demo2(){
    Mat dst=Mat::zeros(Size(600,600),CV_8UC3);
    vector<Point> ptr;
    ptr.push_back(Point(100,200));
    ptr.push_back(Point(100,400));
    ptr.push_back(Point(400,300));
    vector<Point> ptr1;
    ptr1.push_back(Point(300,200));
    ptr1.push_back(Point(300,400));
    ptr1.push_back(Point(600,500));
    ptr1.push_back(Point(600,300));
    vector<vector<Point>> contour;
    contour.push_back(ptr);
    contour.push_back(ptr1);
    // polylines(dst,ptr,true,Scalar(255,55,55),5,LINE_AA,0);
    // fillPoly(dst,ptr,Scalar(55,255,55),LINE_AA,0);
    drawContours(dst,contour,-1,Scalar(175, 150, 205),-1);
    imshow("contour",dst);
}

void OpenCV::on_draw(int event,int x,int y,int flags,void* userdata){
    static Point sp(-1,-1);        // 按下点;(-1,-1) 表示"当前没在拖拽"
    static Mat canvas;             // 干净底图,用来擦掉上一帧的矩形
    static Mat oringin;
    Mat &img=*((Mat*)userdata);    // 引用,直接改到原图上
    if(event==EVENT_LBUTTONDOWN){  // ---- 按下:记起点 + 拍一张干净底图 ----
        if(oringin.empty()){
            img.copyTo(oringin);
        }
        sp=Point(x,y);
        img.copyTo(canvas);
        return;
    }
    if(sp.x<0) return;             // 没在拖拽,其余事件(右键/滚轮等)一律忽略

    // ---- 下面只在"按住拖动"期间执行 ----
    if(event==EVENT_MOUSEMOVE || event==EVENT_LBUTTONUP){
        Point ep(x,y);
        int dx=abs(ep.x-sp.x);
        int dy=abs(ep.y-sp.y);
        int x0=sp.x<ep.x?sp.x:ep.x;   // 左上角(支持反方向拖拽)
        int y0=sp.y<ep.y?sp.y:ep.y;

        oringin.copyTo(img);           // 1. 先还原干净底图 → 擦掉上一帧的矩形
        if(dx>0 && dy>0){
            rectangle(img,Rect(x0,y0,dx,dy),Scalar(0,0,255),2,LINE_AA,0); // 2. 画这一帧的矩形
        }
        imshow("mouse_drawing",img);  // 3. 刷新窗口 ← 这步才产生"动画"

        if(event==EVENT_LBUTTONUP){ // 4. 松开 → 本次拖拽结束
            Point ep(x,y);
            int dx=abs(ep.x-sp.x);
            int dy=abs(ep.y-sp.y);
            int x0=sp.x<ep.x?sp.x:ep.x;   // 左上角(支持反方向拖拽)
            int y0=sp.y<ep.y?sp.y:ep.y;
            Rect roi(x0,y0,dx,dy);
            if(dx>0 && dy>0){
                Mat Roi=oringin(roi).clone();
                imshow("roi",Roi);
            }
            sp=Point(-1,-1);
        }
    }
}

void OpenCV::Mouse_demo(Mat &image){
    namedWindow("mouse_drawing",WINDOW_AUTOSIZE);
    setMouseCallback("mouse_drawing",on_draw,(void*)(&image));
    imshow("mouse_drawing",image);
}

void OpenCV::norm_demo(Mat &image){
    Mat dst;
    cout<<image.type()<<endl;
    image.convertTo(image,CV_32F);
    cout<<image.type()<<endl;
    normalize(image,dst,1.0,0,NORM_MINMAX);
    cout<<dst.type()<<endl;
    imshow("after_norm",dst);
}

void OpenCV::flip_demo(Mat &image){
    imshow("oringin",image);
    Mat dst;
    //flip(image,dst,-1);//上下再镜像
    //flip(image,dst,1);//左右对称
    flip(image,dst,0);//上下对称
    imshow("flip",dst);
}

void OpenCV::resize_demo(Mat &image){
    imshow("oringin",image);
    Mat zoomin,zoomout;
    int h=image.rows;
    int w=image.cols;
    resize(image,zoomin,Size(w/2,h/2),0,0,INTER_LINEAR);
    //上面等价于resize(image,zoomin,Size(),0.5,0.5,INTER_LINEAR);//dsize和fx,fy只能二选一
    imshow("small",zoomin);
    resize(image,zoomout,Size(),2.0,2.0,INTER_LINEAR);
    imshow("big",zoomout);
    /*
    INTER_LINEAR 平时放大缩小最常用
    INTER_CUBIC  放大更清晰，计算更慢
    INTER_AREA   缩小可用，抗锯齿效果更好，放大效果一般
    INTER_NEAREST  掩码，二值图必须用这个，不用计算
    */
}

void OpenCV::rotate_demo(Mat &image){
    Mat dst,M;
    int w=image.cols;
    int h=image.rows;
    M=getRotationMatrix2D(Point2f(w/2,h/2),45,1.0);//最后一个参数scale是缩放比例
    double cos=abs(M.at<double>(0,0));
    double sin=abs(M.at<double>(0,1));
    int nw=cos*w+sin*h;
    int nh=sin*w+cos*h;//新h就cos*h，新w就cos*w 
    M.at<double>(0,2)+=(nw/2-w/2);
    M.at<double>(1,2)+=(nh/2-h/2);
    warpAffine(image,dst,M,Size(500,400),INTER_LINEAR,0,Scalar(55,255,55));
    imshow("rotate",dst);
    /*Point2f src[]={Point2f(40,180),Point2f(118,150),Point2f(200,200)};
    Point2f dst1[]={Point2f(40,200),Point2f(118,90),Point2f(200,200)};
    M=getAffineTransform(src,dst1);
    M.at<double>(1,2)=30;//y向偏移量
    warpAffine(image,dst,M,Size(400,1100),INTER_LINEAR,0,Scalar(255,255,55));
    imshow("rotate",dst);*/  //getAffineTransform测试,源点不能共线，必须能包住一个面积
}

void OpenCV::video_demo(Mat &image){
    // 0 = 第 0 个摄像头。WSL 默认不把宿主机的摄像头映射进来,/dev/video0 不存在,这里通常打不开
    string path="/home/zhanghaoran/image/video/tom.mp4";
    VideoCapture capture(path);
    if(!capture.isOpened()){
        cout<<"视频读取失败，请检查原因"<<endl;
        return;
    }
    Mat frame;
    Mat gray;
    int h=capture.get(CAP_PROP_FRAME_HEIGHT);
    int w=capture.get(CAP_PROP_FRAME_WIDTH);
    int count=capture.get(CAP_PROP_FRAME_COUNT);
    double fps=capture.get(CAP_PROP_FPS);
    cout<<w<<"*"<<h<<" frameCount:"<<count<<" fps"<<fps<<endl;
    VideoWriter writer("/home/zhanghaoran/image/video",capture.get(CAP_PROP_FOURCC),fps,Size(w,h),false);
    if(!writer.isOpened()){
        cout<<"视频检索失败，请检查原因"<<endl;
        return;
    }
    while(1){
        if(!capture.read(frame)||frame.empty()){  // read 失败时 frame 就是空的,两者一起判
            break;
        }
        cvtColor(frame,gray,COLOR_BGR2GRAY);
        writer.write(gray);
        imshow("frame",gray);
        int key=waitKey(30);       // 33ms ≈ 30fps;waitKey 同时负责刷新窗口
        if(key==27){               // ESC 退出
            break;
        }
    }
    capture.release();
    writer.release();
}

void OpenCV::blur_demo(Mat &image){
    Mat dst;
    imshow("origin",image);
    blur(image,dst,Size(15,15),Point(-1,-1));//ksize卷积核大小必须是基数
    imshow("blur",dst);
}

void OpenCV::gaussian_demo(Mat &image){
    Mat dst;
    imshow("origin",image);
    GaussianBlur(image,dst,Size(3,3),0);
    imshow("gaussianBlur",dst);
}

void OpenCV::bilateral_demo(Mat &image){
    Mat dst;
    imshow("origin",image);
    bilateralFilter(image,dst,0,75,10);
    imshow("fix",dst);
}

void OpenCV::edge_demo(Mat &image){
    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    //GaussianBlur(gray,gray,Size(15,15),0);
    cout<<"1.sobel 2.scharr 3.Laplacian 4.Canny"<<endl;
    imshow("gray",gray);
    while(1){
        int c=waitKey(100);
        if(c==27) {break;}
        else if(c==49){//sobel
            Mat sobelX,sobelY,sobelXY;
            Sobel(gray,sobelX,CV_16S,1,0,3);
            Sobel(gray,sobelY,CV_16S,0,1,3);
            convertScaleAbs(sobelX,sobelX);
            convertScaleAbs(sobelY,sobelY);
            sobelXY=sobelX+sobelY;
            imshow("edgeX",sobelX);
            imshow("edgeY",sobelY);
            imshow("edgeXY",sobelXY);
        }
        else if(c==50){
            Mat scharrX,scharrY,scharrXY;
            Scharr(gray,scharrX,CV_16S,1,0,3);
            Scharr(gray,scharrY,CV_16S,0,1,3);
            convertScaleAbs(scharrX,scharrX);
            convertScaleAbs(scharrY,scharrY);
            scharrXY=scharrX+scharrY;
            imshow("edgeX",scharrX);
            imshow("edgeY",scharrY);
            imshow("edgeXY",scharrXY);
        }
        else if(c==51){
            Mat result,resultg;
            Laplacian(gray,result,CV_16S,3,1,0);
            convertScaleAbs(result,result);
            imshow("edgeXY",result);
        }
        else if(c==52){
            Mat resultG;
            Canny(gray,resultG,100,200,3);
            imshow("edgeXY",resultG);
        }
    } 
    destroyAllWindows();
}

void OpenCV::threshold_demo(Mat &image){
    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY);
    Mat two1,two2,two3,two4,OTSU,TRIANGLE,adapt_mean,adapt_gauss;
    threshold(gray,two1,127,255,THRESH_BINARY);//大于取1，低于取0
    threshold(gray,two2,127,255,THRESH_BINARY_INV);//大于取0，小于取1
    threshold(gray,two3,127,255,THRESH_TOZERO);//大于保留，小于取0
    threshold(gray,two4,127,255,THRESH_TOZERO_INV);//小于保留，大于取0
    // Mat greenback=Mat::zeros(image.size(),CV_8UC3);
    // greenback=Scalar(55,200,55);
    // image.copyTo(greenback,two1);
    threshold(gray,OTSU,200,255,THRESH_BINARY|THRESH_OTSU);//大津法，自输入阈值失效
    threshold(gray,TRIANGLE,100,255,THRESH_BINARY|THRESH_TRIANGLE);//三角形法
    adaptiveThreshold(gray,adapt_mean,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,55,0);//自适应法，将图像分为x*x各自分别找阈值
    //最后一个参数是偏移量
    adaptiveThreshold(gray,adapt_gauss,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,55,0);
    imshow("two1",two1);
    imshow("two2",two2);
    imshow("two3",two3);
    imshow("two4",two4);
    imshow("OTSU",OTSU);
    imshow("TRIANGLE",TRIANGLE);
    imshow("adapt_mean",adapt_mean);
    imshow("adapt_gauss",adapt_gauss);
    //imshow("green",greenback);
    //注释内容为掩码辅助抠像
}