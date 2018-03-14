
// edgeSearchingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "edgeSearching.h"
#include "edgeSearchingDlg.h"
#include "afxdialogex.h"
#include"SetNoise.h" 
#include"commonPara.h"
#include"ShowInfo.h"
#include"AddBoxFilterKenelValue.h"
#include"com.fanyu.Filter.h"
#include"com.fanyu.Enhance.h"
#include"com.fanyu.EdgeCheck.h"
#include"SetCannyPara.h"
#include"com.fanyu.CreateNoise.h"
#include"SetSobelPara.h"
#include<atlimage.h>
#include"SetLaplaceHole.h"
#include"Paint.h"

#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenFile_Menu();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)


END_MESSAGE_MAP()


// CedgeSearchingDlg 对话框


CedgeSearchingDlg::CedgeSearchingDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CedgeSearchingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CedgeSearchingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWORGIMAGE_STATIC, m_Show_ORG_Picture);
}

BEGIN_MESSAGE_MAP(CedgeSearchingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CedgeSearchingDlg::OnOpenFile)
	ON_COMMAND(ID_32782, &CedgeSearchingDlg::OnCreateGaNoise)
	ON_COMMAND(ID_32783, &CedgeSearchingDlg::OnAddPSNoise)
	ON_COMMAND(ID_32784, &CedgeSearchingDlg::OnBoxFilter)
	ON_COMMAND(ID_32819, &CedgeSearchingDlg::OnFilterIntroduction)
	ON_COMMAND(ID_32785, &CedgeSearchingDlg::OnAverageFilter)
	ON_COMMAND(ID_32776, &CedgeSearchingDlg::OnExpEnhance)
	ON_COMMAND(ID_32820, &CedgeSearchingDlg::OnLogEnhance)
	ON_COMMAND(ID_32792, &CedgeSearchingDlg::OnHighPass)
	ON_COMMAND(ID_32791, &CedgeSearchingDlg::OnExplorOver)
	ON_COMMAND(ID_32778, &CedgeSearchingDlg::OnCanny)
	ON_BN_CLICKED(IDC_BUTTON_GRAY, &CedgeSearchingDlg::OnBnClickedButtonGray)
	ON_BN_CLICKED(IDC_BUTTON_BINARY, &CedgeSearchingDlg::OnBnClickedButtonBinary)
	ON_COMMAND(ID_32786, &CedgeSearchingDlg::OnGaussianFilter)
	ON_COMMAND(ID_32773, &CedgeSearchingDlg::OnExit)
	ON_COMMAND(ID_32772, &CedgeSearchingDlg::OnSave)
	ON_COMMAND(ID_32797, &CedgeSearchingDlg::OnGaInfo)
	ON_COMMAND(ID_32798, &CedgeSearchingDlg::OnPSInfo)
	ON_COMMAND(ID_32788, &CedgeSearchingDlg::OnMediumFilter)
	ON_COMMAND(ID_32789, &CedgeSearchingDlg::OnDoubleEdgeFilter)
	ON_COMMAND(ID_32790, &CedgeSearchingDlg::OnWaveChange)
	ON_COMMAND(ID_32800, &CedgeSearchingDlg::OnBoxFilterInfo)
	ON_COMMAND(ID_32801, &CedgeSearchingDlg::OnAverageFilterInfo)
	ON_COMMAND(ID_32802, &CedgeSearchingDlg::OnGauFilterInfo)
	ON_COMMAND(ID_32803, &CedgeSearchingDlg::OnMediumFilterInfo)
	ON_COMMAND(ID_32804, &CedgeSearchingDlg::OnDouFilterInfo)
	ON_COMMAND(ID_32805, &CedgeSearchingDlg::OnWaveInfo)
	ON_COMMAND(ID_32807, &CedgeSearchingDlg::OnExpInfo)
	ON_COMMAND(ID_32808, &CedgeSearchingDlg::OnLogInfo)
	ON_COMMAND(ID_32809, &CedgeSearchingDlg::OnHPInfo)
	ON_COMMAND(ID_32810, &CedgeSearchingDlg::OnHConvInfo)
	ON_COMMAND(ID_32779, &CedgeSearchingDlg::OnRoberts)
	ON_COMMAND(ID_32780, &CedgeSearchingDlg::OnSobel)
	ON_COMMAND(ID_32781, &CedgeSearchingDlg::OnLaplace)
	ON_COMMAND(ID_32793, &CedgeSearchingDlg::OnSusan)
	ON_COMMAND(ID_32794, &CedgeSearchingDlg::OnKrisch)
	ON_COMMAND(ID_32795, &CedgeSearchingDlg::OnPrewitt)
	ON_COMMAND(ID_32812, &CedgeSearchingDlg::OnCannyInfo)
	ON_COMMAND(ID_32813, &CedgeSearchingDlg::OnRobertsInfo)
	ON_COMMAND(ID_32814, &CedgeSearchingDlg::OnSobelInfo)
	ON_COMMAND(ID_32815, &CedgeSearchingDlg::OnLaplaceInfo)
	ON_COMMAND(ID_32816, &CedgeSearchingDlg::OnSusanInfo)
	ON_COMMAND(ID_32817, &CedgeSearchingDlg::OnKrischInfo)
	ON_COMMAND(ID_32818, &CedgeSearchingDlg::OnPrewittInfo)
	ON_BN_CLICKED(IDC_BUTTON_AUTOCHECK, &CedgeSearchingDlg::OnBnClickedButtonAutocheck)
	ON_BN_CLICKED(IDC_SAVE_PICTURE_BUTTON, &CedgeSearchingDlg::OnBnClickedSavePictureButton)
	ON_BN_CLICKED(IDC__AMPLIFICATION_BUTTON, &CedgeSearchingDlg::OnBnClickedButtonAmpl)
	ON_BN_CLICKED(IDC_BUTTON_HAND_FIX, &CedgeSearchingDlg::OnBnClickedButtonHandFix)
	ON_BN_CLICKED(IDC_BUTTON_ANALISE, &CedgeSearchingDlg::OnBnClickedButtonAnalise)
END_MESSAGE_MAP()


// CedgeSearchingDlg 消息处理程序

BOOL CedgeSearchingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO:  在此添加额外的初始化代码
	m_Menu.LoadMenu(IDR_MENU1);//加载菜单栏
	SetMenu(&m_Menu);
	
	CONTINUE=true;//灰度图转换只执行一次标志
	InitFlag = true;//初始化一次标志


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CedgeSearchingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CedgeSearchingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		//// 添加代码对话框背景贴图
		//CPaintDC   dc(this);
		//CRect   rect;
		//GetClientRect(&rect);    //获取对话框长宽      
		//
		//CDC   dcBmp;             //定义并创建一个内存设备环境
		//dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
		//
		//CBitmap   bmpBackground;
		//bmpBackground.LoadBitmap(IDB_BITMAP2);    //载入资源中图片
		//
		//BITMAP   m_bitmap;                         //图片变量               
		//bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
		//
		////将位图选入临时内存设备环境
		//CBitmap  *pbmpOld = dcBmp.SelectObject(&bmpBackground);
		//
		////调用函数显示图片StretchBlt显示形状可变
		//dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CedgeSearchingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/***********************************************
 *                     菜单事件函数
 *
 *
 **
 ***********************************************/
/*--------------------公有对象----------------------*/
static CString FILEPATH;//图片文件地址

//定义共有Mat对象
static cv::Mat orgMat;//初始对象
static cv::Mat noiMat;//加噪对象
static cv::Mat filMat;//滤波对象
static cv::Mat enhMat;//强化对象
static cv::Mat edgMat;//边缘对象
static cv::Mat graMat;//灰度图对象
static cv::Mat binMat;//二值化对象
extern cv::Mat cMat;//cpp中共享对象

//初始化
void InitMat()
{
	if (InitFlag)
		InitFlag = false;
	
	binMat = edgMat = enhMat = filMat = noiMat = orgMat;
}
/*--------------------END----------------------*/

/*------------------------------成员函数---------------------------------*/

//在对话框显示图片函数
void CedgeSearchingDlg::showImage(IplImage* image, UINT ID){

	//把Mat对象显示到picture控件中需要的对象
	static CDC *pDC;
	static HDC hDC;
	static CRect rect;
	static CvvImage cimg;

	pDC = GetDlgItem(ID)->GetDC();
	hDC = pDC->GetSafeHdc();

	GetDlgItem(ID)->GetClientRect(&rect);

	cimg.CopyOf(image, image->nChannels);
	cimg.DrawToHDC(hDC, &rect);
	
	ReleaseDC(pDC);
}

//图片地址传递函数
void getFilePath(CString BmpName)
{
	FILEPATH = BmpName;
}


//菜单->文件->打开
void CedgeSearchingDlg::OnOpenFile()
{
	//打开文件 定义四种格式的文件bmp gif jpg tiff
	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK)
	{
		//打开对话框获取图像信息
		CString BmpName = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp
		CString EntName = dlg.GetFileExt();      //获取文件扩展名

		getFilePath(BmpName);//获取文件地址供以后调用

		EntName.MakeLower();                     //将文件扩展名转换为一个小写字符

		if (EntName.Compare(_T("bmp")) == 0)
		{
			//定义变量存储图片信息
			BITMAPINFO *pBmpInfo;       //记录图像细节
			BYTE *pBmpData;             //图像数据
			BITMAPFILEHEADER bmpHeader; //文件头
			BITMAPINFOHEADER bmpInfo;   //信息头
			CFile bmpFile;              //记录打开文件

			//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
			if (!bmpFile.Open(BmpName, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];

			//为图像数据申请空间
			memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
			DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
			pBmpData = (BYTE*)new char[dataBytes];
			bmpFile.Read(pBmpData, dataBytes);
			bmpFile.Close();

			/*为了Mat对象的共有使用*/
			//把CSring类型转换为String类型
			USES_CONVERSION;
			String str(W2A(FILEPATH));
			orgMat = imread(str, 3);//把读入的Mat存到cMat中

			//显示图像
			CRect rect;
			static CDC *pDC;
			CWnd *pWnd = GetDlgItem(IDC_SHOWORGIMAGE_STATIC); //获得pictrue控件窗口的句柄
			pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
			pDC = pWnd->GetDC(); //获得pictrue控件的DC
			pDC->SetStretchBltMode(COLORONCOLOR);
			StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
				bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		}
	}
	CONTINUE = true;//灰度图按钮可用
	InitMat();//初始化所有使用到的Mat对象
}

//菜单->文件->退出
void CedgeSearchingDlg::OnExit()
{
	EndDialog(IDD_EDGESEARCHING_DIALOG);
}

//菜单->文件->保存
void CedgeSearchingDlg::OnSave()
{
	CString saveFilePath;
	CClientDC dc(this);
    CRect rect;
	BOOL  showMsgTag = FALSE;                  //是否要弹出”图像保存成功对话框" 

	GetClientRect(&rect);                  //获取画布大小

	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);
	
	//创建兼容位图

	HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式

	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);

	//将位图选入DC，并保存返回值 

	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);

	//将屏幕DC的图像复制到内存DC中
	ATL::CImage image;

	image.Attach(hbitmap);

	BOOL saveTag = FALSE;

	if (!saveTag)                          //如果图像是第一次被写入,则打开对话框
	{
		saveTag = TRUE;

		showMsgTag = TRUE;

		CString  strFilter = _T("位图文件(*.bmp)|*.bmp|JPEG 图像文件|*.jpg|GIF图像文件 | *.gif | PNG图像文件 | *.png |其他格式(*.*) | *.* || ");
		CFileDialog dlg(FALSE, _T("bmp"), _T("iPaint1.bmp"), NULL, strFilter);

		if (dlg.DoModal() != IDOK)
			return;

		CString strFileName;          //如果用户没有指定文件扩展名，则为其添加一个
		CString strExtension;
		strFileName = dlg.m_ofn.lpstrFile;

		if (dlg.m_ofn.nFileExtension = 0)               //扩展名项目为0
		{
			switch (dlg.m_ofn.nFilterIndex)
			{
			case 1:
				strExtension = "bmp"; break;
			case 2:
				strExtension = "jpg"; break;
			case 3:
				strExtension = "gif"; break;
			case 4:
				strExtension = "png"; break;
			default:
				break;
			}

			strFileName = strFileName + "." + strExtension;

		}

		saveFilePath = strFileName;     //saveFilePath为视类中的全局变量,类型为CString
	}

	else
		showMsgTag = FALSE;

	//AfxMessageBox(saveFilePath);               //显示图像保存的全路径(包含文件名)

	HRESULT hResult = image.Save(saveFilePath);     //保存图像

	if (FAILED(hResult))

	{

		MessageBox(_T("保存图像文件失败！"));

	}

	else

	{

		if (showMsgTag)

			MessageBox(_T("文件保存成功！"));

	}

	image.Detach();

	SelectObject(hdc, hOldMap);

}



//菜单->添加噪声->高斯噪声
void CedgeSearchingDlg::OnCreateGaNoise()
{
	noiMat = orgMat;//载入图像对象

	CreateNoise *m_CreateGaNoise = NULL;  //创建一个生成噪声类对象
	m_CreateGaNoise->AddGaussianNoise(noiMat);  //调用高斯噪声函数

	delete m_CreateGaNoise; //释放

	showImage(&(IplImage)noiMat, IDC_SHOW_NOISE_PICTURE_STATIC);//显示图片到指定控件
}

//菜单->添加噪声->椒盐噪声
void CedgeSearchingDlg::OnAddPSNoise()
{
	INT_PTR nRes;//用于保存Domodal函数的返回值

	CSetNoise m_SetNoiseN;//构造SetNoiseN类的实例
	
    m_SetNoiseN.m_SetNoise=1000;//默认值
	UpdateData(FALSE);

	nRes = m_SetNoiseN.DoModal();//弹出窗口

	if (nRes == IDCANCEL)//判断对话框返回值是否为CANCEL，实则返回
		return;

	else if (nRes == IDOK)
		UpdateData(TRUE);//把控件的值更新到变量

		int NoiseN = m_SetNoiseN.m_SetNoise;//获取控件变量值，NoiseN表示噪点数

		noiMat = orgMat;//获取Mat对象

		CreateNoise *m_CreatePSNoise = NULL;  //创建一个生成噪声类对象
		m_CreatePSNoise->AddPepperNoise(noiMat, NoiseN);  //调用椒盐噪声函数
		m_CreatePSNoise->AddSaltNoise(noiMat, NoiseN);

		delete m_CreatePSNoise; //释放噪声类对象

		showImage(&(IplImage)noiMat, IDC_SHOW_NOISE_PICTURE_STATIC);//显示图片到指定控件

}


//菜单->添加噪声->高斯噪声介绍
void CedgeSearchingDlg::OnGaInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->添加噪声->椒盐噪声介绍
void CedgeSearchingDlg::OnPSInfo()
{
}
 


//菜单->滤波->方框滤波
void CedgeSearchingDlg::OnBoxFilter()
{
	CAddBoxFilterKenelValue m_BoxFilter;//弹窗对象

	INT_PTR nResB;
	
	m_BoxFilter.m_AddBoxFilterKenelValue=5;//默认值
	UpdateData(FALSE);

	nResB = m_BoxFilter.DoModal();//弹窗操作

	Filter mFilter(noiMat); //初始化滤波对象

	if (nResB==IDCANCEL)
		return;

	if (nResB == IDOK)//点击确定
		UpdateData(TRUE);

	mFilter.kenelValue = m_BoxFilter.m_AddBoxFilterKenelValue;//获取控件值
	mFilter.dDepth = -1;//图像深度为原图深度

	mFilter.boxFilter();//调用方框滤波函数，处理结果保存在dstMat中

	filMat = mFilter.dstMat;//目标图保存到cMat中

	showImage(&(IplImage)filMat, IDC_SHOW_FILTER_PICTURE_STATIC);//显示图片到指定控件
}

//菜单->滤波->均值滤波
void CedgeSearchingDlg::OnAverageFilter()
{
	CAddBoxFilterKenelValue m_BlurFilter;//弹窗对象
	m_BlurFilter.m_AddBoxFilterKenelValue=7;//默认值
	UpdateData(FALSE);

	INT_PTR nResB;
	nResB = m_BlurFilter.DoModal();//弹窗操作

	Filter mFilter(noiMat); //初始化滤波对象
	
	if (nResB == IDCANCEL)
		return;

	if (nResB == IDOK)//点击确定
		UpdateData(TRUE);

	mFilter.kenelValue = m_BlurFilter.m_AddBoxFilterKenelValue;//获取控件值
	mFilter.dDepth = -1;//图像深度为原图深度

	mFilter.averageFilter();//调用滤波函数，处理结果保存在dstMat中

	filMat = mFilter.dstMat;//目标图保存到cMat中

	showImage(&(IplImage)filMat, IDC_SHOW_FILTER_PICTURE_STATIC);//显示图片到指定控件
}

//菜单->滤波->高斯滤波
void CedgeSearchingDlg::OnGaussianFilter()
{
	CAddBoxFilterKenelValue m_GauFilter;//弹窗对象
	m_GauFilter.m_AddBoxFilterKenelValue = 3;//默认值
	UpdateData(FALSE);

	INT_PTR nResB;
	nResB = m_GauFilter.DoModal();//弹窗操作

	Filter mFilter(noiMat); //初始化滤波对象

	if (nResB == IDCANCEL)
		return;

	if (nResB == IDOK)//点击确定
		UpdateData(TRUE);

	mFilter.kenelValue = m_GauFilter.m_AddBoxFilterKenelValue;//获取控件值
	mFilter.dDepth = -1;//图像深度为原图深度

	mFilter.GaussianFilter();//调用滤波函数，处理结果保存在dstMat中

	filMat = mFilter.dstMat;//目标图保存到cMat中

	showImage(&(IplImage)filMat, IDC_SHOW_FILTER_PICTURE_STATIC);//显示图片到指定控件
}

//菜单->滤波->中值滤波
void CedgeSearchingDlg::OnMediumFilter()
{
	CAddBoxFilterKenelValue m_MedFilter;//弹窗对象

	INT_PTR nResB;
	
	m_MedFilter.m_AddBoxFilterKenelValue = 7;//默认值
	UpdateData(FALSE);

	nResB = m_MedFilter.DoModal();//弹窗操作

	Filter mFilter(noiMat); //初始化滤波对象

	if (nResB == IDCANCEL)
		return;

	if (nResB == IDOK)//点击确定
		UpdateData(TRUE);

	mFilter.kenelValue = m_MedFilter.m_AddBoxFilterKenelValue;//获取控件值
	mFilter.dDepth = -1;//图像深度为原图深度

	mFilter.medianFilter();//调用滤波函数，处理结果保存在dstMat中

	filMat = mFilter.dstMat;//目标图保存到cMat中

	showImage(&(IplImage)filMat, IDC_SHOW_FILTER_PICTURE_STATIC);//显示图片到指定控件
}

//菜单->滤波->双边滤波
void CedgeSearchingDlg::OnDoubleEdgeFilter()
{
	CAddBoxFilterKenelValue m_DouFilter;//弹窗对象
	m_DouFilter.m_AddBoxFilterKenelValue = 25;//默认值
	UpdateData(FALSE);

	INT_PTR nResB;
	nResB = m_DouFilter.DoModal();//弹窗操作

	Filter mFilter(noiMat); //初始化滤波对象

	if (nResB == IDCANCEL)
		return;

	if (nResB == IDOK)//点击确定
		UpdateData(TRUE);

	mFilter.kenelValue = m_DouFilter.m_AddBoxFilterKenelValue;//获取控件值
	mFilter.dDepth = -1;//图像深度为原图深度

	mFilter.bilateralFilter();//调用滤波函数，处理结果保存在dstMat中

    filMat = mFilter.dstMat;//目标图保存到cMat中

	showImage(&(IplImage)filMat, IDC_SHOW_FILTER_PICTURE_STATIC);//显示图片到指定控件
}

//菜单->滤波->小波变换
void CedgeSearchingDlg::OnWaveChange()
{
	CAddBoxFilterKenelValue m_waveConvert;//弹窗对象
	
	m_waveConvert.m_AddBoxFilterKenelValue=2;//默认值
	
	INT_PTR nResB;
	nResB = m_waveConvert.DoModal();//弹窗操作

	Filter mFilter(noiMat); //初始化滤波对象

	if (nResB == IDCANCEL)
		return;

	if (nResB == IDOK)//点击确定
		UpdateData(TRUE);

	mFilter.kenelValue = m_waveConvert.m_AddBoxFilterKenelValue;//获取控件值
	mFilter.dDepth = -1;//图像深度为原图深度

	mFilter.waveConvert();//调用滤波函数，处理结果保存在dstMat中

	filMat = mFilter.dstMat;//目标图保存到cMat中

	showImage(&(IplImage)filMat, IDC_SHOW_FILTER_PICTURE_STATIC);//显示图片到指定控件
}


//菜单->滤波->查看说明->图像滤波介绍
void CedgeSearchingDlg::OnFilterIntroduction()
{
	CShowFilterInfo m_ShowInfo;//实例化查看信息窗口对象
	m_ShowInfo.DoModal();//弹出窗口
}

//菜单->滤波->查看说明->方框滤波介绍
void CedgeSearchingDlg::OnBoxFilterInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->滤波->查看说明->均值滤波介绍
void CedgeSearchingDlg::OnAverageFilterInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->滤波->查看说明->高斯滤波介绍
void CedgeSearchingDlg::OnGauFilterInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->滤波->查看说明->中值滤波介绍
void CedgeSearchingDlg::OnMediumFilterInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->滤波->查看说明->双边滤波介绍
void CedgeSearchingDlg::OnDouFilterInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->滤波->查看说明->小波变换介绍
void CedgeSearchingDlg::OnWaveInfo()
{
	// TODO:  在此添加命令处理程序代码
}



//菜单->增强->指数增强
void CedgeSearchingDlg::OnExpEnhance()
{

	Enhance mEnhance(filMat);//初始化增强类对象
	Mat dst;
	mEnhance.ExpEnhance(&(IplImage)filMat, &(IplImage)dst);//指数增强

	enhMat = dst;//更新enhMat

	showImage(&(IplImage)enhMat, IDC_SHOWENHANCEIMAGE_STATIC);//显示图片到指定控件

}

//菜单->增强->对数增强
void CedgeSearchingDlg::OnLogEnhance()
{
	Enhance mLogEnhance(filMat);//初始化增强类对象
	Mat dst;
	mLogEnhance.LogEnhance(&(IplImage)filMat, &(IplImage)dst);//指数增强

	enhMat = dst;//更新enhMat

	showImage(&(IplImage)enhMat, IDC_SHOWENHANCEIMAGE_STATIC);//显示图片到指定控件
}

//菜单->增强->高反差
void CedgeSearchingDlg::OnHighPass()
{
	Enhance mHPEnhance(filMat);//初始化增强对象

	enhMat = mHPEnhance.dstMat = mHPEnhance.HighPass();//调用高反差函数

	showImage(&(IplImage)enhMat, IDC_SHOWENHANCEIMAGE_STATIC);//显示图片到指定控件

}

//菜单->增强->高曝光
void CedgeSearchingDlg::OnExplorOver()
{
	Enhance mEOEnhance(filMat);
	mEOEnhance.ExporeOver(&(IplImage)filMat, &(IplImage)(mEOEnhance.dstMat));

	enhMat = mEOEnhance.dstMat;//保存处理结果

	showImage(&(IplImage)enhMat, IDC_SHOWENHANCEIMAGE_STATIC);//显示图片到指定控件

}


//菜单->增强->查看说明-->指数
void CedgeSearchingDlg::OnExpInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->增强->查看说明-->对数
void CedgeSearchingDlg::OnLogInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->增强->查看说明-->高曝光
void CedgeSearchingDlg::OnHPInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->增强->查看说明-->高反差
void CedgeSearchingDlg::OnHConvInfo()
{
	// TODO:  在此添加命令处理程序代码
}





//菜单->检测->Canny算子
void CedgeSearchingDlg::OnCanny()
{
	CSetCannyPara m_SetCannyPara;  //初始化弹窗对象
	
	m_SetCannyPara.m_setCannyValue1=270;//默认值
	m_SetCannyPara.m_setCannyValue2=270*2/3;
	UpdateData(FALSE);

	INT_PTR nResC;//保存弹窗返回值

	nResC = m_SetCannyPara.DoModal();//弹出窗口并获取返回值

	if (nResC == IDCANCEL)
		return;

	else if (nResC == IDOK)//如果点击确定按钮
		UpdateData(TRUE);//从控件更新值到变量

	EdgeCheck mEdgeCheckCanny(enhMat);//初始化边缘检测类对象
	//控件变量赋值给边缘检测类对象成员
	mEdgeCheckCanny.thresholdValue1 = m_SetCannyPara.m_setCannyValue1;
	mEdgeCheckCanny.thresholdValue2 = m_SetCannyPara.m_setCannyValue2;

	mEdgeCheckCanny.Canny();//调用Canny函数

	edgMat = mEdgeCheckCanny.dstMat;//处理结果保存


	showImage(&(IplImage)edgMat, IDC_SHOWEDGEIMAGE_STATIC);//显示图片到指定控件

}

//菜单->检测->Roberts算子
void CedgeSearchingDlg::OnRoberts()
{
	EdgeCheck m_Roberts(enhMat);//初始化检测类对象

	m_Roberts.Roberts();//Roberts算子

	edgMat=m_Roberts.dstMat;//保存
	
	showImage(&(IplImage)edgMat, IDC_SHOWEDGEIMAGE_STATIC);//显示图片到指定控件

}

//菜单->检测->Soberl算子
void CedgeSearchingDlg::OnSobel()
{
	//弹窗设置参数
	CSetSobelPara m_setSobelPara;//弹窗对象

	m_setSobelPara.m_Sobeldxdy=2;//默认值
	m_setSobelPara.m_Sobelhole=3;
	UpdateData(FALSE);

	INT_PTR nResS;

	nResS=m_setSobelPara.DoModal();//弹窗

	if (nResS == IDCANCEL)
		return;

	if (nResS == IDOK)//如果点击确定按钮，则更新控件值到变量
		UpdateData(TRUE);

	////调用检测算子
	EdgeCheck m_SobelCheck(enhMat);//初始化检测类
	
	//赋值
	m_SobelCheck.dxdy = m_setSobelPara.m_Sobeldxdy;
	m_SobelCheck.Sobelhole = m_setSobelPara.m_Sobelhole;

	m_SobelCheck.Sobel();//检测

	edgMat = m_SobelCheck.dstMat;//存储结果

	showImage(&(IplImage)edgMat, IDC_SHOWEDGEIMAGE_STATIC);//显示图片到指定控件
}

//菜单->检测->Laplace算子
void CedgeSearchingDlg::OnLaplace()
{
	////弹窗
	CSetLaplaceHole m_setLaplaceHole;

	m_setLaplaceHole.m_setLaplaceHole=3;//默认值
	UpdateData(FALSE);

	INT_PTR nResL=m_setLaplaceHole.DoModal();
	
	if (nResL == IDCANCEL)
		return;

	if (nResL == IDOK)//若点击确定则更新数据
		UpdateData(TRUE);

	////检测
	EdgeCheck m_Laplace(enhMat);

	m_Laplace.LaplaceHole = m_setLaplaceHole.m_setLaplaceHole;//获取参数
	m_Laplace.Laplace();//检测

	edgMat = m_Laplace.dstMat;//保存
	
	showImage(&(IplImage)edgMat, IDC_SHOWEDGEIMAGE_STATIC);//显示图片到指定控件
}

//菜单->检测->Susan算子
void CedgeSearchingDlg::OnSusan()
{
	EdgeCheck m_Susan(enhMat);
	m_Susan.Susan();

	edgMat = m_Susan.dstMat;//保存
	
	showImage(&(IplImage)edgMat, IDC_SHOWEDGEIMAGE_STATIC);//显示图片到指定控件
}

//菜单->检测->Krisch算子
void CedgeSearchingDlg::OnKrisch()
{
	EdgeCheck m_Krisch(enhMat);
	m_Krisch.Krisch();

    edgMat = m_Krisch.dstMat;//保存
	
	showImage(&(IplImage)edgMat, IDC_SHOWEDGEIMAGE_STATIC);//显示图片到指定控件
}

//菜单->检测->Prewitt算子
void CedgeSearchingDlg::OnPrewitt()
{
	EdgeCheck m_Prewitt(enhMat);
	m_Prewitt.Krisch();

	edgMat = m_Prewitt.dstMat;//保存

	showImage(&(IplImage)edgMat, IDC_SHOWEDGEIMAGE_STATIC);//显示图片到指定控件
}


//菜单->检测->查看说明-->Canny算子介绍
void CedgeSearchingDlg::OnCannyInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->检测->查看说明-->Roberts算子介绍
void CedgeSearchingDlg::OnRobertsInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->检测->查看说明-->Sobel算子介绍
void CedgeSearchingDlg::OnSobelInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->检测->查看说明-->Laplace算子介绍
void CedgeSearchingDlg::OnLaplaceInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->检测->查看说明-->Susan算子介绍
void CedgeSearchingDlg::OnSusanInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->检测->查看说明-->Krisch算子介绍
void CedgeSearchingDlg::OnKrischInfo()
{
	// TODO:  在此添加命令处理程序代码
}

//菜单->检测->查看说明-->Prewitt算子介绍
void CedgeSearchingDlg::OnPrewittInfo()
{
	// TODO:  在此添加命令处理程序代码
}



/***********************************************
*                     按钮事件函数
*
*
**
***********************************************/

//按钮：灰度图转换
void CedgeSearchingDlg::OnBnClickedButtonGray()
{
	if (CONTINUE)
	{
		CONTINUE = false;

		cvtColor(orgMat, graMat, CV_BGR2GRAY);//转为灰度图

		orgMat = graMat;

		showImage(&(IplImage)graMat, IDC_SHOWORGIMAGE_STATIC);//显示图片到指定控件
	}
}

//按钮：二值化图像
void CedgeSearchingDlg::OnBnClickedButtonBinary()
{
	binMat = orgMat;

	CV_Assert(binMat.depth() != sizeof(uchar));  //声明只对深度8bit的图像操作

	int channels = binMat.channels();            //获取图像channel
	int nrows = binMat.rows;                     //矩阵的行数
	int ncols = binMat.cols*channels;             //矩阵的总列数=列数*channel分量数

	if (binMat.isContinuous())               //判断矩阵是否连续，若连续，我们相当于只需要遍历一个一维数组
	{
		ncols *= nrows;
		nrows = 1;                 //一维数组
	}

	//遍历像素点灰度值
	for (int i = 0; i < nrows; i++)
	{
		uchar *p = binMat.ptr<uchar>(i);    //获取行地址

		for (int j = 0; j < ncols; j++)
		{
			if (p[j] < 100)
				p[j] = 0;
			else
				p[j] = 255;
		}
	}

	orgMat= binMat;//保存

	showImage(&(IplImage)binMat, IDC_SHOWORGIMAGE_STATIC);//显示图片到指定控件
}

//自动检测按钮
void CedgeSearchingDlg::OnBnClickedButtonAutocheck()
{
}

//保存图像
void CedgeSearchingDlg::OnBnClickedSavePictureButton()
{
	// TODO:  在此添加控件通知处理程序代码
}

//放大显示
void CedgeSearchingDlg::OnBnClickedButtonAmpl()
{
}


/*--------------------手工优化---------------------*/
//Mat初始化
Mat m_org = edgMat, m_dst, m_img, m_tmp;
void on_mouse(int event, int x, int y, int flags, void*ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
{
	/*event鼠标事件代号:
	#define CV_EVENT_MOUSEMOVE 0                 滑动
	#define CV_EVENT_LBUTTONDOWN 1           左键点击
	#define CV_EVENT_RBUTTONDOWN 2           右键点击
	#define CV_EVENT_MBUTTONDOWN 3          中间点击
	#define CV_EVENT_LBUTTONUP 4                   左键释放
	#define CV_EVENT_RBUTTONUP 5                   右键释放
	#define CV_EVENT_MBUTTONUP 6                  中间释放
	#define CV_EVENT_LBUTTONDBLCLK 7         左键双击
	#define CV_EVENT_RBUTTONDBLCLK 8         右键双击
	#define CV_EVENT_MBUTTONDBLCLK 9         中间释放
	*/

	static Point pre_pt = (-1, -1);//初始坐标  
	static Point cur_pt = (-1, -1);//实时坐标  
	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
	{
		m_org.copyTo(m_img);//将原始图片复制到img中  

		pre_pt = Point(x, y);
		putText(m_img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255), 1, 8);//在窗口上显示坐标  
		circle(m_img, pre_pt, 2, Scalar(255, 255, 0, 0), CV_FILLED, CV_AA, 0);//划圆  
		imshow("手动优化", m_img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//左键没有按下的情况下鼠标移动的处理函数  
	{
		m_img.copyTo(m_tmp);//将img复制到临时图像tmp上，用于显示实时坐标  

		cur_pt = Point(x, y);
		putText(m_tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));//只是实时显示鼠标移动的坐标  
		imshow("手动优化", m_tmp);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//左键按下时，鼠标移动，则在图像上划矩形  
	{
		m_img.copyTo(m_tmp);

		cur_pt = Point(x, y);
		putText(m_tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		rectangle(m_tmp, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//在临时图像上实时显示鼠标拖动时形成的矩形  
		imshow("手动优化", m_tmp);
	}
	else if (event == CV_EVENT_LBUTTONUP)//左键松开，将在图像上划矩形  
	{
		m_org.copyTo(m_img);

		cur_pt = Point(x, y);
		putText(m_img, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		circle(m_img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		rectangle(m_img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//根据初始点和结束点，将矩形画到img上  
		imshow("手动优化", m_img);
		m_img.copyTo(m_tmp);
		//截取矩形包围的图像，并保存到dst中  
		int width = abs(pre_pt.x - cur_pt.x);
		int height = abs(pre_pt.y - cur_pt.y);
		if (width == 0 || height == 0)
			return;

		m_dst = m_org(Rect(min(cur_pt.x, pre_pt.x), min(cur_pt.y, pre_pt.y), width, height));
		//删除选中矩形框中的像素值
		for (int i = 0; i <m_dst.rows; i++){
			for (int j = 0; j < m_dst.cols; j++){
				for (int k = 0; k < m_dst.channels(); k++)
					m_dst.at<cv::Vec3b>(i, j)[k] = 0;
			}
		}
		imshow("手动优化", m_img);
		waitKey(0);
	}
}

void CedgeSearchingDlg::OnBnClickedButtonHandFix()
{
	/*鼠标操作*/
	edgMat.copyTo(m_img);
	edgMat.copyTo(m_tmp);

	namedWindow("手动优化",WINDOW_AUTOSIZE);//定义一个img窗口
	setMouseCallback("手动优化", on_mouse, 0);//调用回调函数  
	imshow("手动优化", m_img);
	waitKey(0);
}


//统计分析
void CedgeSearchingDlg::OnBnClickedButtonAnalise()
{
	CPaint *myPaint;

	myPaint = new CPaint();

	myPaint->orgMat = orgMat;//传递图片对象

	INT_PTR nRes;

	nRes=myPaint->DoModal();
}
