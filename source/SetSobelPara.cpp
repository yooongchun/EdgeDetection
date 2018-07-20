// SetSobelPara.cpp : 实现文件
//

#include "stdafx.h"
#include "edgeSearching.h"
#include "SetSobelPara.h"
#include "afxdialogex.h"


// CSetSobelPara 对话框

IMPLEMENT_DYNAMIC(CSetSobelPara, CDialogEx)

CSetSobelPara::CSetSobelPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetSobelPara::IDD, pParent)
	, m_Sobeldxdy(0)
	, m_Sobelhole(0)
{

}

CSetSobelPara::~CSetSobelPara()
{
}

void CSetSobelPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SOBEL_DXDY, m_Sobeldxdy);
	DDV_MinMaxInt(pDX, m_Sobeldxdy, 0, 3);
	DDX_Text(pDX, IDC_EDIT2, m_Sobelhole);
	DDV_MinMaxInt(pDX, m_Sobelhole, 1, 7);
}


BEGIN_MESSAGE_MAP(CSetSobelPara, CDialogEx)
END_MESSAGE_MAP()


// CSetSobelPara 消息处理程序
