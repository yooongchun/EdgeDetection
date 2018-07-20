#pragma once
#include "afxwin.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// CPaint 对话框

class CPaint : public CDialogEx
{
	DECLARE_DYNAMIC(CPaint)

public:
	CPaint(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPaint();
// 对话框数据
	enum { IDD = IDD_DIALOG_ANALISE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	CStatic m_Picture;
	cv::Mat orgMat;
	afx_msg void OnStnClickedStaticPicture();
	};
