// test1.cpp (fixed)
// Usage: ./demo <image_path>   e.g.  ./demo ~/image/one.jpg  (~ expands in shell)
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: ./demo <image_path>" << endl;
        return -1;
    }
    Mat src = imread(argv[1]);        // argv[1] 由 shell 展开好传进来
    if (src.empty()) {                // 读图失败必查,否则 imshow 空图必崩
        cout << "Cannot read image: " << argv[1] << endl;
        return -1;
    }
    cout << "Read OK: " << src.cols << " x " << src.rows << endl;
    Mat dst=src.clone();  // 先拷贝一份,否则 src 变了 dst 也变了;
    //自由拉动输出窗口
    namedWindow("free",WINDOW_FREERATIO);  // 可自由拉动窗口
    cvtColor(src,src,COLOR_BGR2GRAY); // 转灰度图
    //imwrite("output.jpg", src);  // 写图
    // imshow("color", dst);
     imshow("free", src);
    waitKey(0);   // 等按键;替代 Windows 的 system("pause")
    return 0;
}
