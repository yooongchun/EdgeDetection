#pragma once

// CShowFilterInfo 对话框
//显示查看信息窗口

class CShowFilterInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CShowFilterInfo)

public:
	CShowFilterInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowFilterInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOW_FILTER_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonConfirm();
	CString m_ShowInfo;
	CString m_ShowInformation;
};
