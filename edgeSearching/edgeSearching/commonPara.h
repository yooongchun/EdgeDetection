//定义公有全局参数
#ifndef _COMMON
#define _COMMON

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;

static bool CONTINUE = false;//继续执行标志
static bool InitFlag = false;//初始化标志

//公有全局函数集
class CommonPara{

public:
	void MatToCImage(Mat &mat, ATL::CImage &cImage);
};


#endif