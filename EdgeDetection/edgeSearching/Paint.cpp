// Paint.cpp : 实现文件
//

#include "stdafx.h"
#include "edgeSearching.h"
#include "Paint.h"
#include "afxdialogex.h"


// CPaint 对话框

IMPLEMENT_DYNAMIC(CPaint, CDialogEx)

CPaint::CPaint(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPaint::IDD, pParent)
{
}

CPaint::~CPaint()
{
}

void CPaint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CPaint, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_START, &CPaint::OnBnClickedButtonStart)
	ON_STN_CLICKED(IDC_STATIC_PICTURE, &CPaint::OnStnClickedStaticPicture)
END_MESSAGE_MAP()


// CPaint 消息处理程序



void CPaint::OnBnClickedButtonStart()
{
	CPen myPen,pen2,pen3;
	CDC *pDC = m_Picture.GetDC();
	CRect Rect;

	m_Picture.GetClientRect(&Rect);
	myPen.CreatePen(PS_SOLID,3,RGB(0,255,0)); //创建实心画笔，粗度为3，颜色绿色
	pen2.CreatePen(PS_DOT,1,RGB(100,100,100));
	pen3.CreatePen(PS_SOLID,5,(RGB(0,0,255)));


	////绘制坐标系
	pDC->SelectObject(&myPen);//选择画笔
	pDC->MoveTo(Rect.left,Rect.bottom);
	pDC->LineTo(Rect.right,Rect.bottom);
	pDC->MoveTo(Rect.left, Rect.bottom);
	pDC->LineTo(Rect.left, Rect.top);

	const int WIDTH = Rect.right - Rect.left;//矩形宽
	const int HEIGHT =Rect.bottom-Rect.top;//矩形1长
	
	int len = WIDTH / 100 * 40;//定义边长
	
	////定义坐标
	int Ax = 0;
	int Ay = HEIGHT;
	int Bx = len;
	int By = Ay;
	int Cx = len + len*sqrt(2)/2;
	int Cy = HEIGHT - len*sqrt(2)/2;
	int Dx = len*sqrt(2)/2;
	int Dy = Cy;
	int aX = Ax;
	int aY =Ay - len;
	int bX = Bx;
	int bY = By-len;
	int cX = Cx;
	int cY = Cy - len;
	int dX = Dx;
	int dY = Dy - len;

	////绘制正方体
	pDC->MoveTo(Ax,Ay);
	pDC->LineTo(Bx,By);
	pDC->LineTo(Cx, Cy);
	pDC->LineTo(Dx, Dy);
	pDC->LineTo(Ax, Ay);
	pDC->LineTo(aX, aY);
	pDC->LineTo(bX, bY);
	pDC->LineTo(cX, cY);
	pDC->LineTo(dX, dY);
	pDC->LineTo(aX, aY);
	pDC->MoveTo(Bx,By);
	pDC->LineTo(bX,bY);
	pDC->MoveTo(Cx,Cy);
	pDC->LineTo(cX,cY);
	pDC->MoveTo(Dx,Dy);
	pDC->LineTo(dX,dY);
	

	////绘制虚线网格
	pDC->SelectObject(&pen2);//选择画笔

	int span = len / 20;//定义虚线跨度
	
	for (int i = 0; i < span+4; ++i)//背部网格线
	{
		pDC->MoveTo(Dx, Dy - span*i);
		pDC->LineTo(Cx, Cy - span*i);
	}

	for (int i = 0; i < span + 4; ++i)//侧面网格线
	{
		pDC->MoveTo(Ax, Ay - span*i);
		pDC->LineTo(Dx, Dy - span*i);
	}


	////将点绘到坐标面上
	pDC->SelectObject(&pen3);//选择画笔

	//double plLen = (double)len / orgMat.rows;//映射图片的单位长度
	//double pwLen = (double)len / (orgMat.cols*orgMat.channels());//映射图片的单位宽度
	//double phLen = (double)len / 255;//映射图片的单位高度
	//double nX, nY;
	//
	//for (int i = 0; i < orgMat.rows;i++){
	//	for (int j = 0; j < orgMat.cols*orgMat.channels();j++){
	//		nX = pwLen*j / sqrt(2) + plLen*i;
	//		nY = HEIGHT-(pwLen*j / sqrt(2) + phLen*orgMat.at<uchar>(i, j));
	//		
	//		pDC->MoveTo(nX,nY);
	//		pDC->SetPixel(nX, nY, RGB(100, 0, 0));
	//	}
	//}

	double nX,nY;//新坐标
	const double pxDensity = orgMat.rows;//图片行数
	const double pyDensity = orgMat.cols*orgMat.channels();//图片像素列数

	for (double j = 0; j < pyDensity; j++){
		for (double i = 0; i < pxDensity; i++){
			nX = len*(1 + sqrt(2) / 2) / (pxDensity+pyDensity / sqrt(2))* (i + j / (sqrt(2)));
			nY = HEIGHT - len*(1 + sqrt(2) / 2) /(pyDensity/sqrt(2)+255)* (j / sqrt(2) + orgMat.at<uchar>(i, j));
			
			pDC->MoveTo(nX,nY);
			pDC->SetPixel(nX,nY,RGB(0,0,255));

		}
	}

	ReleaseDC(pDC);

	UpdateData(TRUE);
}


void CPaint::OnStnClickedStaticPicture()
{
	// TODO:  在此添加控件通知处理程序代码
}
