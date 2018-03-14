// SetNoise.cpp : 实现文件
//

#include "stdafx.h"
#include "edgeSearching.h"
#include "SetNoise.h"
#include "afxdialogex.h"


// CSetNoise 对话框

IMPLEMENT_DYNAMIC(CSetNoise, CDialogEx)

CSetNoise::CSetNoise(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetNoise::IDD, pParent)
	, m_SetNoise(0)
{

}

CSetNoise::~CSetNoise()
{
}

void CSetNoise::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NOISE_PS_SPOT_N, m_SetNoise);
}


BEGIN_MESSAGE_MAP(CSetNoise, CDialogEx)
END_MESSAGE_MAP()


// CSetNoise 消息处理程序
