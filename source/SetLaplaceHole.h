#pragma once


// CSetLaplaceHole 对话框

class CSetLaplaceHole : public CDialogEx
{
	DECLARE_DYNAMIC(CSetLaplaceHole)

public:
	CSetLaplaceHole(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetLaplaceHole();

// 对话框数据
	enum { IDD = IDD_DIALOG_LAPLACE_HOLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_setLaplaceHole;
};
