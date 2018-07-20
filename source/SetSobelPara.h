#pragma once


// CSetSobelPara 对话框

class CSetSobelPara : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSobelPara)

public:
	CSetSobelPara(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetSobelPara();

// 对话框数据
	enum { IDD = IDD_DIALOG_SOBEL_PARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Sobeldxdy;
	int m_Sobelhole;
};
