注：当前图片无法加载，完整查看请到这里： https://blog.csdn.net/zyc121561/article/details/52454920
前言：最近在学习关于图像边缘检测技术，更新此博文仅为      了记录个人学习过程，也供有共同志趣的朋友参考！

本文内容包括：图像噪声添加与去除、几种滤波算法【高斯滤波，方框滤波，均值滤波，中值滤波，双边滤波，小波变换】、几种检测算法【Canny算子、Sobel算子、Laplace算子、Roberts算子、Krisch算子、Prewitt算子、Susan角点检测算法】、MFC图形界面实现等。          

----------
了解更多有趣文章，关注公众号： yooongchun小屋
![这里写图片描述](https://img-blog.csdn.net/20180521111641885?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p5YzEyMTU2MQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

----------
文中所有代码均在本人电脑上正常运行！

测试环境：VS2013+opevCV2.49

----------
先上一张最终效果图
![这里写图片描述](http://img.blog.csdn.net/20160911201622385)


----------


目录：
一、图像噪声
1.图像噪声分类
<1>噪声分类
<2>滤波算法

2.给图像添加噪声
<1>高斯白噪声
<2>椒盐噪声
<3>编程实现

二、滤波算法
1.关于图像滤波

2.图像滤波分类

3.滤波算法介绍
<1>高斯滤波
<2>方框滤波
<3>均值滤波
<4>中值滤波
<5>双边滤波

三、图像增强
1.对数增强算法
2.指数增强算法
3.高曝光
4.高反差

四、边缘检测
1.Canny算子
2.Sobel算子
3.Laplace算子
4.Roberts算子
5.Krisch算子
6.Prewitt算子

7.角点检测算法
<1>Susan角点检测

五、MFC实现
1.框架搭建
2.功能实现

六、结论


----------
一、图像噪声

1.图像噪声分类

<1>图像噪声分类
噪声的分类和该噪声的分布符合什么模型有关，常见的噪声有高斯白噪声、椒盐噪声、泊松分布噪声、指数分布噪声等。

<2>图像滤波器
图像滤波器有空域滤波器，比如均值滤波器、中值滤波器、低通滤波器、高斯滤波等；频域滤波器，比如小波变换、傅里叶变换、余弦变换等；形态学滤波器，主要是通过膨胀和腐蚀等形态学操作进行去噪。
一般平时见的比较多是是高斯白噪声，像用均值滤波、中值滤波、高斯滤波可以去噪。除此以外，像椒盐噪声，一般用中值滤波基本可以去噪。

2.给图像添加噪声
以上说了图像噪声的分类，以下则针对常见的高斯白噪声和椒盐噪声进行详解

<1>高斯白噪声
高斯白噪声中的高斯是指概率分布是正态函数，而白噪声是指它的二阶矩不相关，一阶矩为常数，是指先后信号在时间上的相关性。这是考查一个信号的两个不同方面的问题。

<2>椒盐噪声
椒盐噪声其实是椒噪声和盐噪声的统称，椒噪声即图像中灰度值为255的像素点，盐噪声则为0。

<3>编程实现
```
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

```
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

二、图像滤波

1.图像滤波说明【来源搜狗词条】
>  图像滤波，即在尽量保留图像细节特征的条件下对目标像的噪声进行抑制，是图像预处理中不可缺少的操作，其处理效果的好坏将直接影响到后续图像处理和分析的有效性和可靠性。
>  由于成像系统、传输介质和记录设备等的不完善，数字图像在其形成、传输记录过程中往往会受到多种噪声的污染。另外，在图像处理的某些环节当输入的像对象并不如预想时也会在结果图像中引入噪声。这些噪声在图像上常表现为一引起较强视觉效果的孤立像素点或像素块。一般，噪声信号与要研究的对象不相关它以无用的信息形式出现，扰乱图像的可观测信息。对于数字图像信号，噪声表为或大或小的极值，这些极值通过加减作用于图像像素的真实灰度值上，在图像造成亮、暗点干扰，极大降低了图像质量，影响图像复原、分割、特征提取、图识别等后继工作的进行。要构造一种有效抑制噪声的滤波机必须考虑两个基本问题能有效地去除目标和背景中的噪声;同时，能很好地护图像目标的形状、大小及特定的几何和拓扑结构特征。

2.滤波器分类
对于滤波器的分类按需求可有多种分类方式，滤波方法也各不相同，在此主要根据图像噪声处理介绍一种分类：

> 不同的滤波器用于不同的噪声，很难说某一个降噪滤波器能符所有的噪声。
首先，说一下噪声的类型吧，噪声的分类和该噪声的分布符合什么模型有关，常见的噪声有高斯白噪声、椒盐噪声、泊松分布噪声、指数分布噪声等。
其次，采用的滤波器有空域滤波器，比如均值滤波器、中值滤波器、低通滤波器、高斯滤波等；频域滤波器，比如小波变换、傅里叶变换、余弦变换等；形态学滤波器，主要是通过膨胀和腐蚀等形态学操作进行去噪。
第三，对应场合。一般平时见的比较多是是高斯白噪声，像用均值滤波、中值滤波、高斯滤波可以去噪。还有在低照度下，比如晚上拍照时的图像，一般属于泊松分布的噪声，可以采用一些3d去噪算法，比如效果不错的BM3D算法。像椒盐噪声，一般用中值滤波基本可以去噪。

>作者：chaoren xiongmao
链接：http://www.zhihu.com/question/20095134/answer/14158067
来源：知乎
著作权归作者所有，转载请联系作者获得授权。

3.滤波算法
<1>高斯滤波算法
openCV中封装了高斯滤波函数

```
C++: void GaussianBlur(InputArray src,OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, intborderType=BORDER_DEFAULT )  
```
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。它可以是单独的任意通道数的图片，但需要注意，图片深度应该为CV_8U,CV_16U, CV_16S, CV_32F 以及 CV_64F之一。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。比如可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，Size类型的ksize高斯内核的大小。其中ksize.width和ksize.height可以不同，但他们都必须为正数和奇数。或者，它们可以是零的，它们都是由sigma计算而来。
第四个参数，double类型的sigmaX，表示高斯核函数在X方向的的标准偏差。
第五个参数，double类型的sigmaY，表示高斯核函数在Y方向的的标准偏差。若sigmaY为零，就将它设为sigmaX，如果sigmaX和sigmaY都是0，那么就由ksize.width和ksize.height计算出来。
为了结果的正确性着想，最好是把第三个参数Size，第四个参数sigmaX和第五个参数sigmaY全部指定到。
第六个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。
　　
应用：

```
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
![这里写图片描述](http://img.blog.csdn.net/20160911144141958)


<2>方框滤波算法
openCV中封装该函数，函数原型为

```
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

编程实现

```
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
![这里写图片描述](http://img.blog.csdn.net/20160911145529276)

<3>均值滤波算法
openCV中封装了均值滤波算法函数

```
C++: void blur(InputArray src, OutputArraydst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT )  
```
参数详解
第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。该函数对通道是独立处理的，且可以处理任意通道数的图片，但需要注意，待处理的图片深度应该为CV_8U, CV_16U, CV_16S, CV_32F 以及 CV_64F之一。
第二个参数，OutputArray类型的dst，即目标图像，需要和源图片有一样的尺寸和类型。比如可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，Size类型（对Size类型稍后有讲解）的ksize，内核的大小。一般这样写Size( w,h )来表示内核的大小( 其中，w 为像素宽度， h为像素高度)。Size（3,3）就表示3x3的核大小，Size（5,5）就表示5x5的核大小
第四个参数，Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point(-1,-1)。如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point(-1,-1)表示这个锚点在核的中心。
第五个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。

应用

```
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
![这里写图片描述](http://img.blog.csdn.net/20160911181800458)



<4>中值滤波算法
openCV封装了该算法

``` 
C++: void medianBlur(InputArray src,OutputArray dst, int ksize) 
```
参数详解：
第一个参数，InputArray类型的src，函数的输入参数，填1、3或者4通道的Mat类型的图像；当ksize为3或者5的时候，图像深度需为CV_8U，CV_16U，或CV_32F其中之一，而对于较大孔径尺寸的图片，它只能是CV_8U。
第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。我们可以用Mat::Clone，以源图片为模板，来初始化得到如假包换的目标图。
第三个参数，int类型的ksize，孔径的线性尺寸（aperture linear size），注意这个参数必须是大于1的奇数，比如：3，5，7，9 ...

应用

```
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
![这里写图片描述](http://img.blog.csdn.net/20160911182311040)

<5>双边滤波算法
openCV封装了该函数

```
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
 

```
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
![这里写图片描述](http://img.blog.csdn.net/20160911182641374)


三、图像增强
1.对数增强算法
2.指数增强算法
3.高曝光
4.高反差
以上功能集成在下面的cpp文件中
```
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
![这里写图片描述](http://img.blog.csdn.net/20160911185813401)

指数增强
![这里写图片描述](http://img.blog.csdn.net/20160911185832588)

高曝光
![这里写图片描述](http://img.blog.csdn.net/20160911185919042)

高反差
![这里写图片描述](http://img.blog.csdn.net/20160911185943886)



**重头戏来了！！！**
上面讲了那么多，其实都只是在为图像检测做准备，以下就是本文的重点！

四、边缘检测
1.Canny算子
关于Canny算子原理请参考百度百科
http://baike.baidu.com/link?url=ExVCDbWfd9DPB20z2SzPjB4kHDcxHkJD25lVQIDL-cZSc9HVeTNWPCTLHsCveobPulIUaX6HEu8z0lbsGRfi9a


首先来看openCV中的Canny函数
```
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

```
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
![这里写图片描述](http://img.blog.csdn.net/20160911191005621)


2.Sobel算子
Sobel 算子是一个主要用作边缘检测的离散微分算子 (discrete differentiation operator)。 它Sobel算子结合了高斯平滑和微分求导，用来计算图像灰度函数的近似梯度。在图像的任何一点使用此算子，将会产生对应的梯度矢量或是其法矢量。

sobel算子的wikipedia：
http://zh.wikipedia.org/wiki/%E7%B4%A2%E8%B2%9D%E7%88%BE%E7%AE%97%E5%AD%90
 
sobel算子相关概念，还可以参看这篇博文：
http://www.cnblogs.com/lancidie/archive/2011/07/17/2108885.html

openCV中的Sobel算子详解
```
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
```
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
![这里写图片描述](http://img.blog.csdn.net/20160911191436641)


3.Laplace算子
Laplacian 算子是n维欧几里德空间中的一个二阶微分算子，定义为梯度grad（）的散度div（）。因此如果f是二阶可微的实函数，则f的拉普拉斯算子定义为：

(1) f的拉普拉斯算子也是笛卡儿坐标系xi中的所有非混合二阶偏导数求和：
(2) 作为一个二阶微分算子，拉普拉斯算子把C函数映射到C函数，对于k ≥ 2。表达式(1)（或(2)）定义了一个算子Δ :C(R) → C(R)，或更一般地，定义了一个算子Δ : C(Ω) → C(Ω)，对于任何开集Ω。

关于Laplace算子的相关概念阐述，可以参看这篇博文：
http://www.cnblogs.com/xfzhang/archive/2011/01/19/1939020.html
Laplace算子的wikipedia：
http://zh.wikipedia.org/wiki/%E6%8B%89%E6%99%AE%E6%8B%89%E6%96%AF%E7%AE%97%E5%AD%90

openCV中的Laplace函数

```
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

```
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
![这里写图片描述](http://img.blog.csdn.net/20160911191838737)


4.Roberts算子
这个函数在openCV库中没有，因此需要自己来实现
具体代码如下

```
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
![这里写图片描述](http://img.blog.csdn.net/20160911192329035)

5.Krisch算子
Kirsch算子是R.Kirsch提出来一种边缘检测新算法，它采用8个模板对图像上的每一个像素点进行卷积求导数，这8个模板代表8个方向，对图像上的8个特定边缘方向作出最大响应，运算中取最大值作为图像的边缘输出（上述算法中用到的8个模板在下面的实现代码中给出）。为了便于读者理解该算法的实现，这里我们给出实现该算法的函数代码，读者可以稍加改动应用到自己的项目中去。[1] 
int ntemplate[8][9]={{5,5,5,-3,0,-3,-3,-3,-3},
　　{-3,5,5,-3,0,5,-3,-3,-3},
　　{-3,-3,5,-3,0,5,-3,-3,5},
　　{-3,-3,-3,-3,0,5,-3,5,5},
　　{-3,-3,-3,-3,0,-3,5,5,5},
　　{-3,-3,-3,5,0,-3,5,5,-3},
　　{5,-3,-3,5,0,-3,5,-3,-3},
　　{5,5,-3,5,0,-3,-3,-3,-3}};//3×3
用这个8个模版来计算每个边缘方向的最大响应值作为边缘特征值-边缘强度。
详情参见百度百科
http://baike.baidu.com/link?url=g4TjG-zN4bTLIJmo8wppKe-Ov1STWrL5HON_XiPL3izUNbG-bi0xisrFsHdtIdAFKuY2dTOXvOZmV1rOq-TpVq

实现代码

```
/************************************************************
*  边缘检测算法函数之Krisch检测算子【在主函数main中调用即可】
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

void Krisch(char* path)
{
	IplImage *src;
	src = cvLoadImage(path, 0); //0 单通道加载
	if (!src)
		return;
	IplImage *dst = cvCloneImage(src);
	int x, y;
	float a, b, c, d;
	float p1, p2, p3, p4, p5, p6, p7, p8, p9;
	uchar* ps = (uchar*)src->imageData; //ps为指向输入图片数据的指针
	uchar* pd = (uchar*)dst->imageData; //pd为指向输出图片数据的指针
	int w = dst->width;
	int h = dst->height;
	int step = dst->widthStep;

	for (x = 0; x<w - 2; x++)      //取以（x+1，y+1)为中心的9个邻域像素  1 4 7
	{                                                            // 2 5 8
		for (y = 0; y<h - 2; y++)                                     // 3 6 9
		{
			p1 = ps[y*step + x];
			p2 = ps[y*step + (x + 1)];
			p3 = ps[y*step + (x + 2)];
			p4 = ps[(y + 1)*step + x];
			p5 = ps[(y + 1)*step + (x + 1)];
			p6 = ps[(y + 1)*step + (x + 2)];
			p7 = ps[(y + 2)*step + x];
			p8 = ps[(y + 2)*step + (x + 1)];
			p9 = ps[(y + 2)*step + (x + 2)];//得到(i+1,j+1)周围九个点的灰度值
			a = fabs(float(-5 * p1 - 5 * p2 - 5 * p3 + 3 * p4 + 3 * p6 + 3 * p7 + 3 * p8 + 3 * p9));    //计算4个方向的梯度值
			b = fabs(float(3 * p1 - 5 * p2 - 5 * p3 + 3 * p4 - 5 * p6 + 3 * p7 + 3 * p8 + 3 * p9));
			c = fabs(float(3 * p1 + 3 * p2 - 5 * p3 + 3 * p4 - 5 * p6 + 3 * p7 + 3 * p8 - 5 * p9));
			d = fabs(float(3 * p1 + 3 * p2 + 3 * p3 + 3 * p4 - 5 * p6 + 3 * p7 - 5 * p8 - 5 * p9));
			a = (a>b) ? a : b;                                         //取各个方向上的最大值作为边缘强度
			a = (a>c) ? a : c;
			a = (a>d) ? a : d;
			pd[(y + 1)*step + (x + 1)] = a;
		}
	}
	cvNormalize(dst, dst, 0, 255, CV_MINMAX); //归一化处理

	cvNamedWindow("krisch", 0);      /* 定义一个窗口名为src的显示窗口 */
	cvShowImage("krisch", dst);    /* 在src窗口中，显示src指针所指的图像 */
	cvWaitKey(0);                      /* 无限等待，即图像总显示 */
	cvDestroyAllWindows();   /* 销毁窗口 */
	cvReleaseImage(&dst);
	cvReleaseImage(&src);
}
```

效果：
![这里写图片描述](http://img.blog.csdn.net/20160911193343515)

6.Prewitt算子
Prewitt算子是一种一阶微分算子的边缘检测，利用像素点上下、左右邻点的灰度差，在边缘处达到极值检测边缘，去掉部分伪边缘，对噪声具有平滑作用 。其原理是在图像空间利用两个方向模板与图像进行邻域卷积来完成的，这两个方向模板一个检测水平边缘，一个检测垂直边缘。

实现代码

```
/************************************************************
*  边缘检测算法函数之Prewitt算子【在主函数main中调用即可】
*  使用说明：
*
*
*  @author zha_yongchun
*  @version 2016.8.5.001
*************************************************************/

#include <opencv2/highgui/highgui.hpp>  
#include "cv.h"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <cxcore.h>

using namespace cv;
using namespace std;

void Prewitt(char *path)
{
	//-------prewitt算子 适用灰度图 ----
	IplImage *src = cvLoadImage(path, -1);
	if (!src)
		return;
	IplImage *gray = cvCreateImage(cvGetSize(src), 8, 1);
	if (src->nChannels == 1)
	{
		//复制
		cvCopy(src, gray);
	}
	else
	{
		//色彩空间转换，转换类型为CV_BGR2GRAY
		cvCvtColor(src, gray, CV_BGR2GRAY);
	}
	IplImage *dst = NULL;
	dst = cvCreateImage(cvGetSize(gray), 8, 1);
	//定义prewitt算子的模板
	float prewittx[9] =
	{
		-1, 0, 1,
		-1, 0, 1,
		-1, 0, 1
	};
	float prewitty[9] =
	{
		1, 1, 1,
		0, 0, 0,
		-1, -1, -1
	};
	CvMat px;
	px = cvMat(3, 3, CV_32F, prewittx);
	CvMat py;
	py = cvMat(3, 3, CV_32F, prewitty);

	//为输出图像申请空间
	IplImage *dstx = cvCreateImage(cvGetSize(gray), 8, 1);
	IplImage *dsty = cvCreateImage(cvGetSize(gray), 8, 1);

	//对图像使用模板，自动填充边界 cvCvtColor(src,gray,CV_RGB2GRAY);
	cvFilter2D(gray, dstx, &px, cvPoint(-1, -1));
	cvFilter2D(gray, dsty, &py, cvPoint(-1, -1));

	//计算梯度，范数为2，注意学习指针的使用方法
	int i, j, temp;
	float tempx, tempy;  //定义为浮点型是为了避免sqrt函数引起歧义
	uchar* ptrx = (uchar*)dstx->imageData;
	uchar* ptry = (uchar*)dsty->imageData;
	for (i = 0; i<src->width; i++)
	{
		for (j = 0; j<src->height; j++)
		{
			tempx = ptrx[i + j*dstx->widthStep];   //tempx,tempy表示的是指针所指向的像素
			tempy = ptry[i + j*dsty->widthStep];
			temp = (int)sqrt(tempx*tempx + tempy*tempy);
			dst->imageData[i + j*dstx->widthStep] = temp;
		}
	}
	cvReleaseImage(&dstx);
	cvReleaseImage(&dsty);
	cvNamedWindow("Original Image", 0);
	cvShowImage("Original Image", src);
	cvNamedWindow("Prewitt", 0);      /* 定义一个窗口名为src的显示窗口 */
	cvShowImage("Prewitt", dst);    /* 在src窗口中，显示src指针所指的图像 */
	cvWaitKey(0);                      /* 无限等待，即图像总显示 */
	cvDestroyAllWindows();   /* 销毁窗口 */
	cvReleaseImage(&dst);
	cvReleaseImage(&src);
	cvReleaseImage(&gray);
}
```
效果图
![这里写图片描述](http://img.blog.csdn.net/20160911193616081)


7.角点检测算法
角点是图像很重要的特征，对图像图形的理解和分析有很重要的作用。
目前的角点检测算法可归纳为3类：基于灰度图像的角点检测、基于二值图像的角点检测、基于轮廓曲线的角点检测。

<1>SUSAN是Smith和Brady提出的一种图像处理方法，该算法是基于像素领域包含若干元素的近似圆形模板，对每个像素基于该模板领域的图像灰度计算角点响应函数（CRF）的数值，如果大于某阈值且为局部极大值，则认为该点为角点。角点的精度与圆形模板大小无关，圆形模板越大，检测的角点数越多，则计算量也越大，本文圆形模板包含37个元素，该近似圆形模板结构如图1所示。

1）Susan角点检测实现代码
```
/************************************************************
*  边缘检测算法函数之Susan角点检测算子【在主函数main中调用即可】
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


void Susan(char* path)
{
	int height, width, step, channels;
	int i, j, k, same, max, min, thresh, sum;
	uchar*data0, *data1;
	//char *filename="result.bmp";
	IplImage* Img, *nimg; //声明IplImage指针
	//载入图像
	Img = cvLoadImage(path, 0); //单通道形式加载
	if (!Img)
		return;
	nimg = cvCreateImage(cvGetSize(Img), 8, 1);
	height = Img->height;
	width = Img->width;
	step = Img->widthStep / sizeof(uchar);
	channels = Img->nChannels;
	data0 = (uchar*)Img->imageData;
	data1 = (uchar*)nimg->imageData;

	printf("Processing a %d X %d image with %d channels\n", width, height, channels);
	int OffSetX[37] = { -1, 0, 1,
		-2, -1, 0, 1, 2,
		-3, -2, -1, 0, 1, 2, 3,
		-3, -2, -1, 0, 1, 2, 3,
		-3, -2, -1, 0, 1, 2, 3,
		-2, -1, 0, 1, 2,
		-1, 0, 1 };
	int OffSetY[37] = { -3, -3, -3,
		-2, -2, -2, -2, -2,
		-1, -1, -1, -1, -1, -1, -1,
		0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1,
		2, 2, 2, 2, 2,
		3, 3, 3 };

	max = min = data0[0];
	//for(i=0;i<height;i++)
	// for(j=0;j<width;j++)
	//{
	// if(data0[i*step+j]>max) max = data0[i*step+j];
	//if(data0[i*step+j]<min)   min = data0[i*step+j];
	//   }
	for (i = 3; i<height - 3; i++)
	for (j = 3; j<width - 3; j++)
	{
		same = 0; sum = 0;
		for (k = 0; k<37; k++)
		{
			sum += data0[(i + OffSetY[k])*step + (j + OffSetX[k])];
			thresh = sum / 37;
			if (abs(data0[(i + OffSetY[k])*step + (j + OffSetX[k])] - data0[i*step + j]) <= thresh)
				same++;
			if (same<18)
				data1[i*step + j] = 255;
			else
				data1[i*step + j] = 0;
		}
	}

	cvNamedWindow("SUSAN", 0);      /* 定义一个窗口名为src的显示窗口 */
	cvShowImage("SUSAN", nimg);    /* 在src窗口中，显示src指针所指的图像 */
	cvWaitKey(0);                      /* 无限等待，即图像总显示 */
	cvDestroyWindow("SUSAN");   /* 销毁窗口 */
	cvReleaseImage(&nimg);

}
```
效果
![这里写图片描述](http://img.blog.csdn.net/20160911192806211)



以上叙述了关于图像检测过程中的去噪，增强和检测过程，也给出了实现的代码，为程序的统一可观性，博主用MFC实现了整个程序的界面操作。

五、MFC实现
1.框架搭建
由以上讲解，图像检测的步骤，大致可分噪声种类确定，去除噪声，边缘增强及检测过程。基于这样的过程，此MFC程序通过菜单栏形式也将内容划分为了这样四个部分：
加噪-->滤波-->增强-->检测
![这里写图片描述](http://img.blog.csdn.net/20160911194302107)

然后按照易于对比的原则，将窗口划分为五个主要部分，分别显示四个过程的实时图片和选择功能栏
![这里写图片描述](http://img.blog.csdn.net/20160911194452107)

接下来进行菜单功能的拓展
文件
![这里写图片描述](http://img.blog.csdn.net/20160911195547153)

添加噪声
![这里写图片描述](http://img.blog.csdn.net/20160911195610107)

滤波
![这里写图片描述](http://img.blog.csdn.net/20160911195630154)

检测
![这里写图片描述](http://img.blog.csdn.net/20160911195650364)

完整程序界面
![这里写图片描述](http://img.blog.csdn.net/20160911195747927)

运行结果图
![这里写图片描述](http://img.blog.csdn.net/20160911200015397)

2.功能实现
函数的功能实现主要包括了两个部分，其一是MFC界面实现，其二是模块功能代码，其一仅需要基本的MFC基础知识，在此不作解释，其二主要代码则在前文论及。程序源码可到该地址下载

六、小结
项目的完成少不了查阅大量的文献以及与他人合作，在此次完成的过程中一个人还是遇到了许多困扰，有一句话最重要：理论结合实践！

在给出的MFC框架中，有几项功能仍未实现，目前仍在完善中，如有错误，恳请指正！

程序源码下载地址：
链接：http://pan.baidu.com/s/1eSyUu6u 密码：uooi
