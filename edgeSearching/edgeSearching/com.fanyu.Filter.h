/*---------------------------------------Tips-----------------------------------------*/
//创建Filter类
//功能：对图像进行滤波
//使用：
/*----------------------------------------END---------------------------------------*/

#ifndef _CFILTER
#define _CFILTER

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;

//创建滤波类
class Filter{
private:


public:
	int kenelValue;//内核大小
	int dDepth = -1;//图像深度
	Mat srcMat;//原图
	Mat dstMat;//保存目标图

public:
	explicit Filter(Mat& mat) :srcMat(mat){}
	bool boxFilter();//方框滤波函数
	bool averageFilter();//均值滤波
	bool GaussianFilter();//高斯滤波
	bool medianFilter();//中值滤波
	bool bilateralFilter();//双边滤波
	bool waveConvert();//小波变换
};
#endif