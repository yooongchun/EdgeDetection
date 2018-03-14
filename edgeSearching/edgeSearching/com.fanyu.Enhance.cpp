/*--------------------Tips------------------------*/
//Enhance类的实现函数
//
#include"stdafx.h"
#include"com.fanyu.Enhance.h"

/*指数图像增强算法*/
//指数图像增强的表达为：S = cR^r，通过合理的选择c和r可以压缩灰度范围，
//算法以c = 1.0 / 255.0, r = 2实现。
bool Enhance::ExpEnhance(IplImage* img, IplImage* dst)
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
	return true;
}


/*对数图像增强算法*/
//对数图像增强是图像增强的一种常见方法，其公式为： S = c log(r + 1)，
//其中c是常数（以下算法c = 255 / (log(256)），这样可以实现整个画面的亮度增大。
bool Enhance::LogEnhance(IplImage* img, IplImage* dst)
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
	return true;
}

/*曝光过度问题处理*/
//对于曝光过度问题，可以通过计算当前图像的反相（255 - image)，
//然后取当前图像和反相图像的较小者为当前像素位置的值。
// 过度曝光原理：图像翻转，然后求原图与反图的最小值
void Enhance::ExporeOver(IplImage* img, IplImage* dst)
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
Mat Enhance::HighPass()
{
	Mat temp;
	GaussianBlur(strMat, temp, Size(7, 7), 1.6, 1.6);

	int r = 3;
	Mat diff = strMat + r*(strMat - temp); //高反差保留算法
	return diff;
}