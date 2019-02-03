摘要：本文主要介绍了几种主流的图像边缘检测算法，包括Canny算子、Sobel算子、Laplace算子、Roberts算子、Krisch算子、Prewitt算子、Susan角点检测算法等。另外也介绍了相应衍生的概念如图像噪声、图像滤波等。          

---

文中所有代码均在本人电脑上正常运行！

测试环境：VS2013+opevCV2.49

----------

[TOC]

---

### 一、图像噪声

#### 1.图像噪声分类

##### 1.1 图像噪声分类

噪声的分类和该噪声的分布符合什么模型有关，常见的噪声有高斯白噪声、椒盐噪声、泊松分布噪声、指数分布噪声等。

##### 1.2 图像滤波器

图像滤波器有空域滤波器，比如均值滤波器、中值滤波器、低通滤波器、高斯滤波等；频域滤波器，比如小波变换、傅里叶变换、余弦变换等；形态学滤波器，主要是通过膨胀和腐蚀等形态学操作进行去噪。
一般平时见的比较多是是高斯白噪声，像用均值滤波、中值滤波、高斯滤波可以去噪。除此以外，像椒盐噪声，一般用中值滤波基本可以去噪。

#### 2.给图像添加噪声

以上说了图像噪声的分类，以下则针对常见的高斯白噪声和椒盐噪声进行详解

##### 2.1 高斯白噪声

高斯白噪声中的高斯是指概率分布是正态函数，而白噪声是指它的二阶矩不相关，一阶矩为常数，是指先后信号在时间上的相关性。这是考查一个信号的两个不同方面的问题。

##### 2.2 椒盐噪声

椒盐噪声其实是椒噪声和盐噪声的统称，椒噪声即图像中灰度值为255的像素点，盐噪声则为0。

##### 2.3 编程实现

```c++
/*-----------CreateNoise类-------------------*/
//CreateNoise.h文件
//功能：产生图像噪声
//使用：调用成员函数void AddGaussianNoise(Mat&)添加高斯噪声
//调用成员函数void AddPepperNoise(Mat&int n)添加高斯噪声
//调用成员函数void AddSaitNoise(Mat&,int n)添加高斯噪声

#ifndef _CREATENOISE
#define _CREATENOISE

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#define TWO_PI 6.2831853071795864769252866

using namespace cv;
using namespace std;

class CreateNoise{
private:
	double generateGaussianNoise();//创建高斯噪声函数原型

public:
	void AddPepperNoise(Mat &image, int n);//添加椒噪声
	void AddSaltNoise(Mat &image, int n);//添加盐噪声
	void AddGaussianNoise(Mat&);//添加高斯噪声
};

#endif
```

```c++
//CreateNoise.cpp文件
/*给图像添加高斯噪声*/
#include"com.fanyu.createNoise.h"

//产生高斯噪声
double CreateNoise::generateGaussianNoise(){
	static bool hasSpare = false;
	static double rand1, rand2;

	if (hasSpare)
	{
		hasSpare = false;
		return sqrt(rand1) * sin(rand2);
	}

	hasSpare = true;

	rand1 = rand() / ((double)RAND_MAX);
	if (rand1 < 1e-100) rand1 = 1e-100;
	rand1 = -2 * log(rand1);
	rand2 = (rand() / ((double)RAND_MAX)) * TWO_PI;

	return sqrt(rand1) * cos(rand2);
}

//高斯噪声
void CreateNoise::AddGaussianNoise(Mat& I){
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous()){
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i){
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j){
			double val = p[j] + generateGaussianNoise() * 32;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;

			p[j] = (uchar)val;

		}
	}

}

//盐噪声
void CreateNoise::AddSaltNoise(Mat &image, int n) {//n为噪点数目
	int i, j;
	for (int k = 0; k<n / 2; k++) {

		// rand() is the random number generator
		i = std::rand() % image.cols; // % 整除取余数运算符,rand=1022,cols=1000,rand%cols=22
		j = std::rand() % image.rows;

		if (image.type() == CV_8UC1) { // gray-level image

			image.at<uchar>(j, i) = 255; //at方法需要指定Mat变量返回值类型,如uchar等

		}
		else if (image.type() == CV_8UC3) { // color image

			image.at<cv::Vec3b>(j, i)[0] = 255; //cv::Vec3b为opencv定义的一个3个值的向量类型
			image.at<cv::Vec3b>(j, i)[1] = 255; //[]指定通道，B:0，G:1，R:2
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

//椒噪声
void CreateNoise::AddPepperNoise(Mat &image, int n) {//n为噪点数目

	int i, j;
	for (int k = 0; k<n; k++) {

		// rand() is the random number generator
		i = std::rand() % image.cols; // % 整除取余数运算符,rand=1022,cols=1000,rand%cols=22
		j = std::rand() % image.rows;

		if (image.type() == CV_8UC1) { // gray-level image

			image.at<uchar>(j, i) = 0; //at方法需要指定Mat变量返回值类型,如uchar等

		}
		else if (image.type() == CV_8UC3) { // color image

			image.at<cv::Vec3b>(j, i)[0] = 0; //cv::Vec3b为opencv定义的一个3个值的向量类型
			image.at<cv::Vec3b>(j, i)[1] = 0; //[]指定通道，B:0，G:1，R:2
			image.at<cv::Vec3b>(j, i)[2] = 0;
		}
	}
}
```

### 二、图像滤波

#### 1. 图像滤波说明【来源搜狗词条】

>  图像滤波，即在尽量保留图像细节特征的条件下对目标像的噪声进行抑制，是图像预处理中不可缺少的操作，其处理效果的好坏将直接影响到后续图像处理和分析的有效性和可靠性。
>  由于成像系统、传输介质和记录设备等的不完善，数字图像在其形成、传输记录过程中往往会受到多种噪声的污染。另外，在图像处理的某些环节当输入的像对象并不如预想时也会在结果图像中引入噪声。这些噪声在图像上常表现为一引起较强视觉效果的孤立像素点或像素块。一般，噪声信号与要研究的对象不相关它以无用的信息形式出现，扰乱图像的可观测信息。对于数字图像信号，噪声表为或大或小的极值，这些极值通过加减作用于图像像素的真实灰度值上，在图像造成亮、暗点干扰，极大降低了图像质量，影响图像复原、分割、特征提取、图识别等后继工作的进行。要构造一种有效抑制噪声的滤波机必须考虑两个基本问题能有效地去除目标和背景中的噪声;同时，能很好地护图像目标的形状、大小及特定的几何和拓扑结构特征。

#### 2. 滤波器分类

对于滤波器的分类按需求可有多种分类方式，滤波方法也各不相同，在此主要根据图像噪声处理介绍一种分类：

> 不同的滤波器用于不同的噪声，很难说某一个降噪滤波器能符所有的噪声。
首先，说一下噪声的类型吧，噪声的分类和该噪声的分布符合什么模型有关，常见的噪声有高斯白噪声、椒盐噪声、泊松分布噪声、指数分布噪声等。
其次，采用的滤波器有空域滤波器，比如均值滤波器、中值滤波器、低通滤波器、高斯滤波等；频域滤波器，比如小波变换、傅里叶变换、余弦变换等；形态学滤波器，主要是通过膨胀和腐蚀等形态学操作进行去噪。
第三，对应场合。一般平时见的比较多是是高斯白噪声，像用均值滤波、中值滤波、高斯滤波可以去噪。还有在低照度下，比如晚上拍照时的图像，一般属于泊松分布的噪声，可以采用一些3d去噪算法，比如效果不错的BM3D算法。像椒盐噪声，一般用中值滤波基本可以去噪。

>作者：chaoren xiongmao
链接：http://www.zhihu.com/question/20095134/answer/14158067
来源：知乎
著作权归作者所有，转载请联系作者获得授权。

#### 3. 滤波算法

##### 3.1 高斯滤波算法

openCV中封装了高斯滤波函数

```c++
C++: void GaussianBlur(InputArray src,OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, intborderType=BORDER_DEFAULT )  
```
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。它可以是单独的任意通道数的图片，但需要注意，图片深度应该为CV_8U,CV_16U, CV_16S, CV_32F 以及 CV_64F之一。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。比如可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，Size类型的ksize高斯内核的大小。其中ksize.width和ksize.height可以不同，但他们都必须为正数和奇数。或者，它们可以是零的，它们都是由sigma计算而来。
第四个参数，double类型的sigmaX，表示高斯核函数在X方向的的标准偏差。
第五个参数，double类型的sigmaY，表示高斯核函数在Y方向的的标准偏差。若sigmaY为零，就将它设为sigmaX，如果sigmaX和sigmaY都是0，那么就由ksize.width和ksize.height计算出来。
为了结果的正确性着想，最好是把第三个参数Size，第四个参数sigmaX和第五个参数sigmaY全部指定到。
第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。应用：

```c++
/*线性滤波：高斯滤波*/
bool GaussianBlur(String srcAdress, String dstAdress = "E:/opencv/averageFilter.jpg"){

	Mat srcImage = imread(srcAdress, 1);
	Mat dstImage;
	if (!srcImage.data) {
		cout << "图像读取出错！";
		return false;
	}

	//滤波操作
	GaussianBlur(srcImage, dstImage, Size(7,7),0,0);

	//导出
	imwrite(dstAdress, dstImage);

	//显示
	imshow("原图：", srcImage);
	imshow("高斯滤波效果：", dstImage);

	waitKey(0);

	return true;
}
```

效果展示：
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911144141958.jpg)



##### 3.2 方框滤波算法

openCV中封装该函数，函数原型为

```c++
C++: void boxFilter(InputArray src,OutputArray dst, int ddepth, Size ksize, Point anchor=Point(-1,-1), boolnormalize=true, int borderType=BORDER_DEFAULT )  
```
参数详解：
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，且可以处理任意通道数的图片，但需要注意，待处理的图片深度应该为CV_8U, CV_16U, CV_16S, CV_32F 以及 CV_64F之一。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。
第三个参数，int类型的ddepth，输出图像的深度，-1代表使用原图深度，即src.depth()。
第四个参数，Size类型（对Size类型稍后有讲解）的ksize，内核的大小。一般这样写Size( w,h )来表示内核的大小( 其中，w 为像素宽度， h为像素高度)。Size（3,3）就表示3x3的核大小，Size（5,5）就表示5x5的核大小
第五个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point(-1,-1)。如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point(-1,-1)表示这个锚点在核的中心。
第六个参数，bool类型的normalize，默认值为true，一个标识符，表示内核是否被其区域归一化（normalized）了。
第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。

编程实现:

```c++
/*线性滤波：方框滤波*/
int kenelValue = 3;
int MaxkenelValue = 50;
String srcAdress, dstAdress;
//回调函数
static void callBackboxFilter(int, void*){

	Mat srcImage = imread(srcAdress,1);
	Mat dstImage;
	if (!srcImage.data){
		cout << "图像读取出错";
		return;
	}

	//滤波操作
	boxFilter(srcImage, dstImage, -1, Size(kenelValue+1, kenelValue+1));

	//显示
	imshow("方框滤波效果预览：", dstImage);

}
//创建进度条
int boxFilter(String ssrcAdress, String sdstAdress = "E:/opencv/boxFilter.jpg"){
	
	srcAdress = ssrcAdress;
	dstAdress=sdstAdress;

	namedWindow("方框滤波效果预览：",WINDOW_AUTOSIZE);
	
	//创建进度条
	createTrackbar("内核大小：", "方框滤波效果预览：", &kenelValue, MaxkenelValue, callBackboxFilter);
	
	//回调
	callBackboxFilter(kenelValue, 0);
	
	waitKey(0);

	return 0;
}
```
效果展示
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911145529276.jpg)

##### 3.3 均值滤波算法

openCV中封装了均值滤波算法函数

```c++
C++: void blur(InputArray src, OutputArraydst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT )  
```
参数详解
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，且可以处理任意通道数的图片，但需要注意，待处理的图片深度应该为CV_8U, CV_16U, CV_16S, CV_32F 以及 CV_64F之一。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。比如可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，Size类型（对Size类型稍后有讲解）的ksize，内核的大小。一般这样写Size( w,h )来表示内核的大小( 其中，w 为像素宽度， h为像素高度)。Size（3,3）就表示3x3的核大小，Size（5,5）就表示5x5的核大小
第四个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point(-1,-1)。如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point(-1,-1)表示这个锚点在核的中心。
第五个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。

应用

```c++
/*线性滤波：均值滤波*/
bool blur(String srcAdress, String dstAdress = "E:/opencv/averageFilter.jpg"){

	Mat srcImage = imread(srcAdress, 1);
	Mat dstImage;
	if (!srcImage.data) {
		cout << "图像读取出错！";
		return false;
	}

	//滤波操作
	blur(srcImage, dstImage, Size(7, 7));

	//导出
	imwrite(dstAdress, dstImage);

	//显示
	imshow("原图：", srcImage);
	imshow("均值滤波效果：", dstImage);

	waitKey(0);

	return true;
}
```
效果
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911181800458.jpg)

##### 3.4 中值滤波算法

openCV封装了该算法

```c++
C++: void medianBlur(InputArray src,OutputArray dst, int ksize) 
```
参数详解：
第一个参数，InputArray类型的src，函数的输入参数，填1、3或者4通道的Mat类型的图像；当ksize为3或者5的时候，图像深度需为CV_8U，CV_16U，或CV_32F其中之一，而对于较大孔径尺寸的图片，它只能是CV_8U。
第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。我们可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，int类型的ksize，孔径的线性尺寸（aperture linear size），注意这个参数必须是大于1的奇数，比如：3，5，7，9 ...

应用

```c++
/*非线性滤波：中值滤波*/
bool medianBlur(String src,String dst){
	Mat srcImage = imread(src,1);
	Mat dstImage;
	if (!srcImage.data)
		return false;

	//滤波操作[注意：中间值取奇数]
	medianBlur(srcImage,dstImage,7);

	//显示
	imshow("原图：",srcImage);
	imshow("中值滤波效果图：",dstImage);

	//导出
	imwrite(dst,dstImage);

	waitKey(0);

	return true;
}
```
效果
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911182311040.jpg)

##### 3.5 双边滤波算法

openCV封装了该函数

```c++
C++: void bilateralFilter(InputArray src, OutputArraydst, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT)
```

参数详解：
第一个参数，InputArray类型的src，输入图像，即源图像，需要为8位或者浮点型单通道、三通道的图像。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。
第三个参数，int类型的d，表示在过滤过程中每个像素邻域的直径。如果这个值我们设其为非正数，那么OpenCV会从第五个参数sigmaSpace来计算出它来。
第四个参数，double类型的sigmaColor，颜色空间滤波器的sigma值。这个参数的值越大，就表明该像素邻域内有更宽广的颜色会被混合到一起，产生较大的半相等颜色区域。
第五个参数，double类型的sigmaSpace坐标空间中滤波器的sigma值，坐标空间的标注方差。他的数值越大，意味着越远的像素会相互影响，从而使更大的区域足够相似的颜色获取相同的颜色。当d>0，d指定了邻域大小且与sigmaSpace无关。否则，d正比于sigmaSpace。
第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_DEFAULT。

 应用：


```c++
/*非线性滤波：双边滤波*/
bool bilateralFilter(String src, String dst){
	Mat srcImage = imread(src, 1);
	Mat dstImage;
	if (!srcImage.data)
		return false;

	//滤波操作
	bilateralFilter(srcImage, dstImage, 25*2,25*2*2,25/2*2);

	//显示
	imshow("原图：", srcImage);
	imshow("双边滤波效果图：", dstImage);

	//导出
	imwrite(dst, dstImage);

	waitKey(0);

	return true;
}
```
效果：[由图可见，双边滤波对椒盐噪声是无作用的]
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911182641374.jpg)

#### 三、图像增强

- 对数增强算法

- 指数增强算法

- 高曝光

- 高反差

  以上功能集成在下面的cpp文件中

```c++
/************************************************************
*  图像增强算法【在主函数main中调用即可】
*  使用说明：
*   
*
*  @author zha_yongchun
*  @version 2016.8.5.001
*************************************************************/

#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;

/*对数图像增强算法*/
//对数图像增强是图像增强的一种常见方法，其公式为： S = c log(r + 1)，
//其中c是常数（以下算法c = 255 / (log(256)），这样可以实现整个画面的亮度增大。
void LogEnhance(IplImage* img, IplImage* dst)
{
	// 由于oldPixel:[1,256],则可以先保存一个查找表
	uchar lut[256] = { 0 };

	double temp = 255 / log(256);

	for (int i = 0; i<255; i++)
	{
		lut[i] = (uchar)(temp* log(i + 1) + 0.5);
	}

	for (int row = 0; row <img->height; row++)
	{
		uchar *data = (uchar*)img->imageData + row* img->widthStep;
		uchar *dstData = (uchar*)dst->imageData + row* dst->widthStep;

		for (int col = 0; col<img->width; col++)
		{
			for (int k = 0; k<img->nChannels; k++)
			{
				uchar t1 = data[col*img->nChannels + k];
				dstData[col*img->nChannels + k] = lut[t1];
			}
		}
	}
}


/*指数图像增强算法*/
//指数图像增强的表达为：S = cR^r，通过合理的选择c和r可以压缩灰度范围，
//算法以c = 1.0 / 255.0, r = 2实现。
void ExpEnhance(IplImage* img, IplImage* dst)
{
	// 由于oldPixel:[1,256],则可以先保存一个查找表
	uchar lut[256] = { 0 };

	double temp = 1.0 / 255.0;

	for (int i = 0; i<255; i++)
	{
		lut[i] = (uchar)(temp*i*i + 0.5);
	}

	for (int row = 0; row <img->height; row++)
	{
		uchar *data = (uchar*)img->imageData + row* img->widthStep;
		uchar *dstData = (uchar*)dst->imageData + row* dst->widthStep;

		for (int col = 0; col<img->width; col++)
		{
			for (int k = 0; k<img->nChannels; k++)
			{
				uchar t1 = data[col*img->nChannels + k];
				dstData[col*img->nChannels + k] = lut[t1];
			}
		}
	}
}

/*曝光过度问题处理*/
//对于曝光过度问题，可以通过计算当前图像的反相（255 - image)，
//然后取当前图像和反相图像的较小者为当前像素位置的值。
// 过度曝光原理：图像翻转，然后求原图与反图的最小值
void ExporeOver(IplImage* img, IplImage* dst)
{
	for (int row = 0; row <img->height; row++)
	{
		uchar *data = (uchar*)img->imageData + row* img->widthStep;
		uchar *dstData = (uchar*)dst->imageData + row* dst->widthStep;
		for (int col = 0; col<img->width; col++)
		{
			for (int k = 0; k<img->nChannels; k++)
			{
				uchar t1 = data[col*img->nChannels + k];
				uchar t2 = 255 - t1;
				dstData[col*img->nChannels + k] = min(t1, t2);
			}
		}
	}
}


/*高反差保留*/
//高反差保留主要是将图像中颜色、明暗反差较大两部分的交界处保留下来，
//比如图像中有一个人和一块石头，那么石头的轮廓线和人的轮廓线以及面部、
//服装等有明显线条的地方会变被保留，儿其他大面积无明显明暗变化的地方
//则生成中灰色。其表达形式为：dst = r*(img - Blur(img))。
Mat HighPass(Mat img)
{
	Mat temp;
	GaussianBlur(img, temp, Size(7, 7), 1.6, 1.6);

	int r = 3;
	Mat diff = img + r*(img - temp); //高反差保留算法
	return diff;
}

```
效果图：
对数增强
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911185813401.jpg)

指数增强
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911185832588.jpg)

高曝光
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911185919042.jpg)

高反差
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911185943886.jpg)

**重头戏来了！！！**
上面讲了那么多，其实都只是在为图像检测做准备，以下就是本文的重点！

### 四、边缘检测

#### 1. Canny算子

关于Canny算子原理请参考[百度百科](http://baike.baidu.com/link?url=ExVCDbWfd9DPB20z2SzPjB4kHDcxHkJD25lVQIDL-cZSc9HVeTNWPCTLHsCveobPulIUaX6HEu8z0lbsGRfi9a)


首先来看openCV中的Canny函数
```c++
C++: void Canny(InputArray image,OutputArray edges, double threshold1, double threshold2, int apertureSize=3,bool L2gradient=false )  
```
参数详解
第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和类型。
第三个参数，double类型的threshold1，第一个滞后性阈值。
第四个参数，double类型的threshold2，第二个滞后性阈值。
第五个参数，int类型的apertureSize，表示应用Sobel算子的孔径大小，其有默认值3。
第六个参数，bool类型的L2gradient，一个计算图像梯度幅值的标识，有默认值false。

应用：

```c++
/************************************************************
*  边缘检测算法函数之Canny算子【在主函数main中调用即可】
*  使用说明：
*    两个轨迹条分别表示Canny算子中的滞后阈值和高斯滤波内核值
*
*  @author zha_yongchun
*  @version 2016.8.5.001
*************************************************************/

#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;



/*----------------------------------------【Canny算子篇】------------------------------------------*/
/**Canny算子检测
 *1.原理：
 *（1）图像边缘检测必须满足两个条件：一是能有效地抑制噪声，而是必须尽量精确的确定边缘的位置。
 *（2）根据对信噪比与定位乘积进行测度，得到最优化逼近算子，即Canny算子。
 *（3）先平滑后求导
 *
 *2.Canny的目标是找到一个最优的边缘检测算法，最优的含义是：
 *（1）好的检测—算法能够尽可能多的标识出图像中的实际边缘
 *（2）好的定位—标识出的边缘要尽可能与实际图像中的实际边缘尽可能接近。
 *（3）最小响应—图像中的边缘只能标志一次，并且可能存在的图像杂讯不因该标志为边缘。
 *
 *3.Canny边缘检测步骤：
 *（1）去噪
 *任何边缘检测算法都不可能在未经处理的原始数据上很好地處理，所以第一步是对原始数据与高斯 mask 作卷积，得到的
 *图像与原始图像相比有些轻微的模糊（blurred）。这样，单独的一个像素杂讯在经过高斯平滑的图像上变得几乎没有影响。
 *(2)用一阶偏导的有限差分来计算梯度的幅值和方向。
 *(3)对梯度幅值进行非极大值抑制。
 *仅仅得到全局的梯度并不足以确定边缘，因此为确定边缘，必须保留局部梯度最大的点，而抑制非极大值。解决方法：利用梯度的方向。
 *(4)用双阈值算法检测和连接边缘。
 *减少假边缘段数量的典型方法是对N[i，j]使用一个阈值。将低于阈值的所有值赋零值。但问题是如何选取阈值？
 *解决方法：双阈值算法。双阈值算法对非极大值抑制图象作用两个阈值τ1和τ2，且2τ1≈τ2，从而可以得到两个阈值边缘图象N1［i,j］
 *和N2［i，j］。由于N2［i，j］使用高阈值得到，因而含有很少的假边缘，但有间断(不闭合)。双阈值法要在N2［i，j］中把边缘连接成轮
 *廓，当到达轮廓的端点时，该算法就在N1［i,j］的8邻点位置寻找可以连接到轮廓上的边缘，这样，算法不断地在N1［i,j］中收集边缘，
 *直到将N2［i,j］连接起来为止。
 *在连接边缘的时候，用数组模拟队列的实现。以进行8-连通域搜索。
 */

/*---------------------函数使用-------------------------*/
//参数初始化
int thresholdValue1 = 270;//滞后性阈值1
int kenelValueCanny = 4;//降噪内核值
const static int MaxKenelValueCanny = 10;
const static int MaxThresholdValue1 = 300;
String srcAdressCanny;

//回调函数
static void callBackCanny(int, void*){

	Mat srcImage = imread(srcAdressCanny, 3);
	Mat dstImage, grayImage, denoiseImage,cannyImage;
	if (!srcImage.data){
		cout << "图像读取出错";
		return;
	}

	//创建与srcImage同类型和大小的矩阵 
	dstImage.create(srcImage.size(), srcImage.type());

	//将原图像转换为灰度图像  
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//高斯滤波降噪
	GaussianBlur(grayImage, denoiseImage, Size(kenelValueCanny * 2 + 1, kenelValueCanny * 2 + 1), 0, 0);
		
	//使用Canny算子
	Canny(denoiseImage, cannyImage, thresholdValue1, thresholdValue1 * 2 / 3, 3);
	
	//将dstImage内的所有元素设置为0
	dstImage = Scalar::all(0);

	//以cannyImage作为掩码，将原图srcImage拷到目标图dstImage中
	srcImage.copyTo(dstImage, cannyImage);

	//显示
	imshow("原图", srcImage);
	imshow("Canny算子边缘检测效果预览：", dstImage);
	imwrite("E:/opencv/Canny.jpg",dstImage);
}

//创建进度条
void Canny(String ssrcAdress){

	srcAdressCanny = ssrcAdress;

	namedWindow("Canny算子边缘检测效果预览：", WINDOW_AUTOSIZE);

	//创建进度条
	createTrackbar("内核值：", "Canny算子边缘检测效果预览：", &kenelValueCanny, MaxKenelValueCanny, callBackCanny);
	createTrackbar("阈值一：", "Canny算子边缘检测效果预览：", &thresholdValue1, MaxThresholdValue1, callBackCanny);
	
	//回调
	callBackCanny(kenelValueCanny, 0);
	callBackCanny(thresholdValue1, 0);

	waitKey(0);
	
}

```
效果：
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911191005621.jpg)

#### 2. Sobel算子

Sobel 算子是一个主要用作边缘检测的离散微分算子 (discrete differentiation operator)。 它Sobel算子结合了高斯平滑和微分求导，用来计算图像灰度函数的近似梯度。在图像的任何一点使用此算子，将会产生对应的梯度矢量或是其法矢量。

sobel算子的[wikipedia](http://zh.wikipedia.org/wiki/%E7%B4%A2%E8%B2%9D%E7%88%BE%E7%AE%97%E5%AD%90)

sobel算子相关概念，还可以参看[这篇博文](http://www.cnblogs.com/lancidie/archive/2011/07/17/2108885.html)

openCV中的Sobel算子详解
```c++
C++: void Sobel (  
InputArray src,//输入图  
 OutputArray dst,//输出图  
 int ddepth,//输出图像的深度  
 int dx,  
 int dy,  
 int ksize=3,  
 double scale=1,  
 double delta=0,  
 int borderType=BORDER_DEFAULT );  
```
参数说明：
第一个参数，InputArray 类型的src，为输入图像，填Mat类型即可。
第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
第三个参数，int类型的ddepth，输出图像的深度，支持如下src.depth()和ddepth的组合：
若src.depth() = CV_8U, 取ddepth =-1/CV_16S/CV_32F/CV_64F
若src.depth() = CV_16U/CV_16S, 取ddepth =-1/CV_32F/CV_64F
若src.depth() = CV_32F, 取ddepth =-1/CV_32F/CV_64F
若src.depth() = CV_64F, 取ddepth = -1/CV_64F
第四个参数，int类型dx，x 方向上的差分阶数。
第五个参数，int类型dy，y方向上的差分阶数。
第六个参数，int类型ksize，有默认值3，表示Sobel核的大小;必须取1，3，5或7。
第七个参数，double类型的scale，计算导数值时可选的缩放因子，默认值是1，表示默认情况下是没有应用缩放的。我们可以在文档中查阅getDerivKernels的相关介绍，来得到这个参数的更多信息。
第八个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。
第九个参数， int类型的borderType，我们的老朋友了（万年是最后一个参数），边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate处得到更详细的信息。

应用：
```c++
/************************************************************
*  边缘检测算法函数之Sobel算子【在主函数main中调用即可】
*  使用说明：
*    
*
*  @author zha_yongchun
*  @version 2016.8.6.001
*************************************************************/

#include <opencv2/opencv.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;



/*----------------------------------------【Sobel算子篇】------------------------------------------*/

bool Sobel(String src, String dst){
	
	Mat srcImage = imread(src,3);
	Mat grad_Image,grayImage;
	Mat abs_grad_Image, dstImage;
	if (!srcImage.data) 
		return false;

	//将原图像转换为灰度图像  
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//求(x,y)方向梯度
	Sobel( grayImage, grad_Image, CV_16S, 1, 1, 3, 1, 1, BORDER_DEFAULT );  
	convertScaleAbs(grad_Image, abs_grad_Image);

	//显示
	imshow("原图：", srcImage);
	imshow("Sobel函数效果图：", abs_grad_Image);

	//导出
	imwrite(dst, abs_grad_Image);

	waitKey(0);

	return true;
}

```

效果
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911191436641.jpg)

#### 3. Laplace算子

Laplacian 算子是n维欧几里德空间中的一个二阶微分算子，定义为梯度grad（）的散度div（）。因此如果f是二阶可微的实函数，则f的拉普拉斯算子定义为：

- f的拉普拉斯算子也是笛卡儿坐标系xi中的所有非混合二阶偏导数求和：

-  作为一个二阶微分算子，拉普拉斯算子把C函数映射到C函数，对于$$k ≥ 2$$ 。表达式(1)（或(2)）定义了一个算子

  $$Δ :C(R) → C(R)$$，或更一般地，定义了一个算子$$Δ : C(Ω) → C(Ω)$$，对于任何开集Ω。

关于Laplace算子的相关概念阐述，可以参看[这篇博文](http://www.cnblogs.com/xfzhang/archive/2011/01/19/1939020.html)
Laplace算子的[wikipedia](http://zh.wikipedia.org/wiki/%E6%8B%89%E6%99%AE%E6%8B%89%E6%96%AF%E7%AE%97%E5%AD%90)

openCV中的Laplace函数

```c++
C++: void Laplacian(InputArray src,OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, intborderType=BORDER_DEFAULT );  
```
第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和通道数。
第三个参数，int类型的ddept，目标图像的深度。
第四个参数，int类型的ksize，用于计算二阶导数的滤波器的孔径尺寸，大小必须为正奇数，且有默认值1。
第五个参数，double类型的scale，计算拉普拉斯值的时候可选的比例因子，有默认值1。
第六个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。
第七个参数， int类型的borderType，边界模式，默认值为BORDER_DEFAULT。这个参数可以在官方文档中borderInterpolate()处得到更详细的信息。

应用

```c++
/************************************************************
*  边缘检测算法函数之Laplace算子【在主函数main中调用即可】
*  使用说明：
*    
*
*  @author zha_yongchun
*  @version 2016.8.5.001
*************************************************************/

#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;



/*----------------------------------------【Laplace算子篇】------------------------------------------*/

bool Laplacian(int kenelValue,String src, String dst){

	Mat srcImage, dstImage, grayImage, abs_dstImage,gaussImage;
	
	srcImage = imread(src,3);
	if (!srcImage.data)
		return false;

	//转为灰度图
	cvtColor(srcImage,grayImage,CV_RGB2GRAY);

	//高斯滤波
	GaussianBlur(grayImage, gaussImage, Size(kenelValue,kenelValue), 0, 0, BORDER_DEFAULT);

	//使用Laplace算子
	Laplacian(gaussImage, abs_dstImage, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	//计算绝对值，并将结果转换成8位  
	convertScaleAbs(abs_dstImage,dstImage );

	//显示
	imshow("原图：",srcImage);
	imshow("Laplace算法：",dstImage);

	//导出
	imwrite(dst,dstImage);

	waitKey(3000);
	return true;
}

```
效果
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911191838737.jpg)

#### 4. Roberts算子

这个函数在openCV库中没有，因此需要自己来实现
具体代码如下

```c++
/************************************************************
*  边缘检测算法函数之Robers算子【在主函数main中调用即可】
*  使用说明：
*    
*
*  @author zha_yongchun
*  @version 2016.8.5.001
*************************************************************/

#include<iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;
using namespace std;

// roberts算子实现
cv::Mat roberts(cv::Mat srcImage)
{
	cv::Mat dstImage = srcImage.clone();
	int nRows = dstImage.rows;
	int nCols = dstImage.cols;
	for (int i = 0; i < nRows - 1; i++)
	{
		for (int j = 0; j < nCols - 1; j++)
		{
			// 根据公式计算
			int t1 = (srcImage.at<uchar>(i, j) -
				srcImage.at<uchar>(i + 1, j + 1)) *
				(srcImage.at<uchar>(i, j) -
				srcImage.at<uchar>(i + 1, j + 1));
			int t2 = (srcImage.at<uchar>(i + 1, j) -
				srcImage.at<uchar>(i, j + 1)) *
				(srcImage.at<uchar>(i + 1, j) -
				srcImage.at<uchar>(i, j + 1));
			// 计算对角线像素差
			dstImage.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
		}
	}
	return dstImage;
}

void Robers(String str,String dst){
	Mat strImage = imread(str,0);
	Mat dstImage;
	if (!strImage.data)
		return;

	imshow("原图",strImage);

	dstImage=roberts(strImage);//调用robers算子

	imshow("Robers算子实现",dstImage);
	imwrite(dst,dstImage);

	cvWaitKey(0);
}
```
效果
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911192329035.jpg)

以上叙述了关于图像检测过程中的去噪，增强和检测过程，也给出了实现的代码，为程序的统一可观性，博主用MFC实现了整个程序的界面操作。

### 五、MFC实现

#### 1. 框架搭建

由以上讲解，图像检测的步骤，大致可分噪声种类确定，去除噪声，边缘增强及检测过程。基于这样的过程，此MFC程序通过菜单栏形式也将内容划分为了这样四个部分：
加噪-->滤波-->增强-->检测，然后按照易于对比的原则，将窗口划分为五个主要部分，分别显示四个过程的实时图片和选择功能栏
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911194452107.jpg)

完整程序界面
![这里写图片描述](http://img.blog.csdn.net/20160911195747927)

运行结果图
![这里写图片描述](https://yooongchun-blog.oss-cn-hangzhou.aliyuncs.com/blog-001/20160911200015397.jpg)

##### 2. 功能实现

函数的功能实现主要包括了两个部分，其一是MFC界面实现，其二是模块功能代码，其一仅需要基本的MFC基础知识，在此不作解释，其二主要代码则在前文论及。程序源码可到该地址下载

### 六、小结

项目的完成少不了查阅大量的文献以及与他人合作，在此次完成的过程中一个人还是遇到了许多困扰，有一句话最重要：理论结合实践！

在给出的MFC框架中，有几项功能仍未实现，目前仍在完善中，如有错误，恳请指正！

---

项目代码github地址： https://github.com/yooongchun/EdgeDetection
