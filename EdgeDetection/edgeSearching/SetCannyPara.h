#pragma once


// CSetCannyPara 对话框

class CSetCannyPara : public CDialogEx
{
	DECLARE_DYNAMIC(CSetCannyPara)

public:
	CSetCannyPara(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetCannyPara();

// 对话框数据
	enum { IDD = IDD_DIALOG_CANNY_THRESHOLDVALUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_CannyValue1;
	int m_CannyValue2;
	int m_setCannyValue1;
	int m_setCannyValue2;
	int m_setCannyV1;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int m_setCannyV2;
};
