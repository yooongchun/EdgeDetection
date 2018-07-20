// SetCannyPara.cpp : 实现文件
//

#include "stdafx.h"
#include "edgeSearching.h"
#include "SetCannyPara.h"
#include "afxdialogex.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 

// CSetCannyPara 对话框

IMPLEMENT_DYNAMIC(CSetCannyPara, CDialogEx)

CSetCannyPara::CSetCannyPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetCannyPara::IDD, pParent)
	, m_setCannyValue1(1)
	, m_setCannyValue2(1)
	, m_setCannyV1(1)
	, m_setCannyV2(1)
{

}

CSetCannyPara::~CSetCannyPara()
{
}

void CSetCannyPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CANNY_VALUE1, m_setCannyValue1);
	DDV_MinMaxInt(pDX, m_setCannyValue1, 1, 500);
	DDX_Text(pDX, IDC_EDIT_CANNY_VALUE2, m_setCannyValue2);
	DDV_MinMaxInt(pDX, m_setCannyValue2, 1, 500);
	DDX_Slider(pDX, IDC_SLIDER_SETCANNY_VALUE1, m_setCannyV1);
	DDV_MinMaxInt(pDX, m_setCannyV1, 1, 500);
	DDX_Slider(pDX, IDC_SLIDER_SET_CANNY_VAULE2, m_setCannyV2);
	DDV_MinMaxInt(pDX, m_setCannyV2, 1, 500);
}


BEGIN_MESSAGE_MAP(CSetCannyPara, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CSetCannyPara 消息处理程序


void CSetCannyPara::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl   *pSlidCtrl1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_SETCANNY_VALUE1);
	CSliderCtrl   *pSlidCtrl2 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_SET_CANNY_VAULE2);
	
	pSlidCtrl1->SetRange(1,500);
	pSlidCtrl2->SetRange(1,500);

	m_setCannyV1 = pSlidCtrl1->GetPos();//取得当前位置值
	m_setCannyV2 = pSlidCtrl2->GetPos();//取得当前位置值  
	
	m_setCannyValue1 = m_setCannyV1;
	m_setCannyValue2 = m_setCannyV2;

	UpdateData(FALSE);  

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
