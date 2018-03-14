#pragma once


// CAddBoxFilterKenelValue 对话框

class CAddBoxFilterKenelValue : public CDialogEx
{
	DECLARE_DYNAMIC(CAddBoxFilterKenelValue)

public:
	CAddBoxFilterKenelValue(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddBoxFilterKenelValue();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHOOSE_BOXFILTER_KENELVALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_AddBoxFilterKenelValue;
};
