
// edgeSearchingDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include"CvvImage.h"
// CedgeSearchingDlg 对话框
class CedgeSearchingDlg : public CDialogEx
{
// 构造
public:
	CedgeSearchingDlg(CWnd* pParent = NULL);	// 标准构造函数
	void showImage(IplImage*, UINT);  //显示图片

// 对话框数据
	enum { IDD = IDD_EDGESEARCHING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Show_ORG_Picture;
    CMenu m_Menu;//菜单栏
	afx_msg void OnOpenFile();
	afx_msg void OnCreateGaNoise();
	afx_msg void OnStnClickedNoisePictureStatic();
	afx_msg void OnStnClickedShowfilterimageStatic();
	afx_msg void OnAddPSNoise();
	afx_msg void OnBoxFilter();
	afx_msg void OnFilterIntroduction();
	afx_msg void OnAverageFilter();
	afx_msg void OnExpEnhance();
	afx_msg void OnLogEnhance();
	afx_msg void OnHighPass();
	afx_msg void OnExplorOver();
	afx_msg void OnCanny();
	afx_msg void OnBnClickedButtonGray();
	afx_msg void OnBnClickedButtonBinary();
	afx_msg void OnGaussianFilter();
	afx_msg void OnExit();
	afx_msg void OnSave();
	afx_msg void OnGaInfo();
	afx_msg void OnPSInfo();
	afx_msg void OnMediumFilter();
	afx_msg void OnDoubleEdgeFilter();
	afx_msg void OnWaveChange();
	afx_msg void OnBoxFilterInfo();
	afx_msg void OnAverageFilterInfo();
	afx_msg void OnGauFilterInfo();
	afx_msg void OnMediumFilterInfo();
	afx_msg void OnDouFilterInfo();
	afx_msg void OnWaveInfo();
	afx_msg void OnExpInfo();
	afx_msg void OnLogInfo();
	afx_msg void OnHPInfo();
	afx_msg void OnHConvInfo();
	afx_msg void OnRoberts();
	afx_msg void OnSobel();
	afx_msg void OnLaplace();
	afx_msg void OnSusan();
	afx_msg void OnKrisch();
	afx_msg void OnPrewitt();
	afx_msg void OnCannyInfo();
	afx_msg void OnRobertsInfo();
	afx_msg void OnSobelInfo();
	afx_msg void OnLaplaceInfo();
	afx_msg void OnSusanInfo();
	afx_msg void OnKrischInfo();
	afx_msg void OnPrewittInfo();
	afx_msg void OnBnClickedButtonAutocheck();
	afx_msg void OnBnClickedSavePictureButton();
	afx_msg void OnBnClickedButtonAmpl();
	afx_msg void OnBnClickedButtonHandFix();
	afx_msg void OnBnClickedButtonAnalise();
};
