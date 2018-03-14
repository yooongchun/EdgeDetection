/*---------------------------------------Tips-----------------------------------------*/
//创建EdgeCheck类
//功能：对图像进行边缘检测
//使用：
/*----------------------------------------END---------------------------------------*/

#ifndef _CEDGECHECK
#define _CEDGECHECK

#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;

class EdgeCheck{
private:
	Mat strMat;

public:
	explicit EdgeCheck(Mat mat):strMat(mat){}
	bool Canny();//Canny算子
	bool Roberts();// roberts算子
	bool Sobel();//Sobel算子
	bool Laplace();//Laplace算子
	bool Susan();//Susan
	bool Krisch();
	bool Prewitt();

public:
	int LaplaceHole;//Laplace滤波器孔径值
	int Sobelhole;//Sobel孔径大小
	int dxdy;//x,y方向的差分阶数
	int thresholdValue1;//滞后性阈值
	int thresholdValue2;
	Mat dstMat;
};

#endif