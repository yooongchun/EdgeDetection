// ShowFilterInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "edgeSearching.h"
#include "ShowInfo.h"
#include "afxdialogex.h"
#include"commonPara.h"
#include<fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// CShowFilterInfo 对话框

IMPLEMENT_DYNAMIC(CShowFilterInfo, CDialogEx)

CShowFilterInfo::CShowFilterInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowFilterInfo::IDD, pParent)
	, m_ShowInfo(_T(""))
	, m_ShowInformation(_T(""))
{
}

CShowFilterInfo::~CShowFilterInfo()
{
}

void CShowFilterInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SHOW_INFO, m_ShowInformation);
}

BEGIN_MESSAGE_MAP(CShowFilterInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &CShowFilterInfo::OnBnClickedButtonConfirm)
END_MESSAGE_MAP()


// CShowFilterInfo 消息处理程序

//显示按钮
void CShowFilterInfo::OnBnClickedButtonConfirm()
{
	std::ifstream mStream; //文件流对象
	mStream.open("E:/opencv/txt/Filter.txt",std::ifstream::in); //打开文件

	std::string line;//存行值
	std::string mString="";//存文本值
	
	if (!mStream)//文件流打开错误则返回
		return;

	while (getline(mStream, line))//读取文本内容直到结束
		mString.append(line+"\r\n");//将每行内容追加到mString中

	mStream.close();//关闭文件

	m_ShowInformation = mString.c_str();//文本赋值
	
	UpdateData(FALSE);//更新数据

}
