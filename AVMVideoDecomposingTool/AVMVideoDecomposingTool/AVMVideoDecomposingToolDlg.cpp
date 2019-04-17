
// AVMVideoDecomposingToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AVMVideoDecomposingTool.h"
#include "AVMVideoDecomposingToolDlg.h"
#include "afxdialogex.h"
#include "func.h"
#include "Mtx_and_Coord_Operation.h"
#include "DialogProgress.h"
#include "LD_LaneDetection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define INV_IMAGE_WIDTH 360
#define INV_IMAGE_HEIGHT 360

extern CDialogProgress* g_pDialogProgress;

OVSBasicInfo g_stOVSBasicInfo;
AvmTableLead g_stAvmTableLead;
AvmTableSupport g_stAvmTableSupport;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAVMVideoDecomposingToolDlg 对话框



CAVMVideoDecomposingToolDlg::CAVMVideoDecomposingToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AVMVIDEODECOMPOSINGTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAVMVideoDecomposingToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SAVE_PATH_EDIT, m_pathEdit);
	DDX_Control(pDX, IDC_PARAMETER_PATH_EDIT, m_parameterEdit);
	DDX_Control(pDX, IDC_COMBO2, m_comVideo);
}

BEGIN_MESSAGE_MAP(CAVMVideoDecomposingToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_VIDEO_BUTTON, &CAVMVideoDecomposingToolDlg::OnBnClickedVideoButton)
	ON_BN_CLICKED(IDC_PARAMETER_BUTTON, &CAVMVideoDecomposingToolDlg::OnBnClickedParameterButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CAVMVideoDecomposingToolDlg::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_TSFMN_BUTTON, &CAVMVideoDecomposingToolDlg::OnBnClickedTsfmnButton)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAVMVideoDecomposingToolDlg 消息处理程序

BOOL CAVMVideoDecomposingToolDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	memset(&g_stOVSBasicInfo, 0, sizeof(OVSBasicInfo));
	memset(&g_stAvmTableLead, 0, sizeof(AvmTableLead));
	memset(&g_stAvmTableSupport, 0, sizeof(AvmTableSupport));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAVMVideoDecomposingToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAVMVideoDecomposingToolDlg::OnPaint()
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
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAVMVideoDecomposingToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAVMVideoDecomposingToolDlg::OnBnClickedParameterButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ParameterPath;
	CString strLine;
	CStdioFile fpFile;
	vector<float> container;

	container.reserve(8);
	container.clear();
	camera.FirstCamera.clear();
	camera.SecondCamera.clear();
	camera.ThirdCamera.clear();
	camera.FourthCamera.clear();

	CFileDialog dlg(TRUE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("视频参数文件 (*.txt)|*.txt|All Files (*.*)|*.*||"),
		NULL);

	if (IDOK == dlg.DoModal())
	{
		ParameterPath = dlg.GetPathName();
	}

	m_parameterEdit.SetWindowText(ParameterPath);

	fpFile.Open(ParameterPath, CFile::modeRead | CFile::typeText);
	
	if (ParameterPath == "")
	{
		return;
	}

	while (fpFile.ReadString(strLine) != NULL)
	{
		CString czLine = strLine;
		CString strSub;

		if (czLine.Left(1) == "0")
		{
			for (int i = 0; i < 8; i++)
			{
				AfxExtractSubString(strSub, (LPCTSTR)czLine + 2, i, ' ');
				container.push_back(atof(strSub));
				camera.FirstCamera.push_back(container[i]);
			}
			container.clear();
		}

		if (czLine.Left(1) == "1")
		{
			for (int i = 0; i < 8; i++)
			{
				AfxExtractSubString(strSub, (LPCTSTR)czLine + 2, i, ' ');
				container.push_back(atof(strSub));
				camera.SecondCamera.push_back(container[i]);
			}
			container.clear();
		}

		if (czLine.Left(1) == "2")
		{
			for (int i = 0; i < 8; i++)
			{
				AfxExtractSubString(strSub, (LPCTSTR)czLine + 2, i, ' ');
				container.push_back(atof(strSub));
				camera.ThirdCamera.push_back(container[i]);
			}
			container.clear();
		}

		if (czLine.Left(1) == "3")
		{
			for (int i = 0; i < 8; i++)
			{
				AfxExtractSubString(strSub, (LPCTSTR)czLine + 2, i, ' ');
				container.push_back(atof(strSub));
				camera.FourthCamera.push_back(container[i]);
			}
			container.clear();
		}
	}
	fpFile.Close();

	g_stOVSBasicInfo.stCameraParamINT[0].daIntParam[3] = camera.FirstCamera[0];
	g_stOVSBasicInfo.stCameraParamINT[0].daIntParam[4] = camera.FirstCamera[1];

	g_stOVSBasicInfo.stCameraParamINT[1].daIntParam[3] = camera.SecondCamera[0];
	g_stOVSBasicInfo.stCameraParamINT[1].daIntParam[4] = camera.SecondCamera[1];

	g_stOVSBasicInfo.stCameraParamINT[2].daIntParam[3] = camera.ThirdCamera[0];
	g_stOVSBasicInfo.stCameraParamINT[2].daIntParam[4] = camera.ThirdCamera[1];

	g_stOVSBasicInfo.stCameraParamINT[3].daIntParam[3] = camera.FourthCamera[0];
	g_stOVSBasicInfo.stCameraParamINT[3].daIntParam[4] = camera.FourthCamera[1];

	g_stOVSBasicInfo.staCameraParamEXT[0].daExtParam[0] = camera.FirstCamera[2];
	g_stOVSBasicInfo.staCameraParamEXT[0].daExtParam[1] = camera.FirstCamera[3];
	g_stOVSBasicInfo.staCameraParamEXT[0].daExtParam[2] = camera.FirstCamera[4];
	g_stOVSBasicInfo.staCameraParamEXT[0].daExtParam[3] = camera.FirstCamera[5];
	g_stOVSBasicInfo.staCameraParamEXT[0].daExtParam[4] = camera.FirstCamera[6];
	g_stOVSBasicInfo.staCameraParamEXT[0].daExtParam[5] = camera.FirstCamera[7];

	g_stOVSBasicInfo.staCameraParamEXT[1].daExtParam[0] = camera.SecondCamera[2];
	g_stOVSBasicInfo.staCameraParamEXT[1].daExtParam[1] = camera.SecondCamera[3];
	g_stOVSBasicInfo.staCameraParamEXT[1].daExtParam[2] = camera.SecondCamera[4];
	g_stOVSBasicInfo.staCameraParamEXT[1].daExtParam[3] = camera.SecondCamera[5];
	g_stOVSBasicInfo.staCameraParamEXT[1].daExtParam[4] = camera.SecondCamera[6];
	g_stOVSBasicInfo.staCameraParamEXT[1].daExtParam[5] = camera.SecondCamera[7];

	g_stOVSBasicInfo.staCameraParamEXT[2].daExtParam[0] = camera.ThirdCamera[2];
	g_stOVSBasicInfo.staCameraParamEXT[2].daExtParam[1] = camera.ThirdCamera[3];
	g_stOVSBasicInfo.staCameraParamEXT[2].daExtParam[2] = camera.ThirdCamera[4];
	g_stOVSBasicInfo.staCameraParamEXT[2].daExtParam[3] = camera.ThirdCamera[5];
	g_stOVSBasicInfo.staCameraParamEXT[2].daExtParam[4] = camera.ThirdCamera[6];
	g_stOVSBasicInfo.staCameraParamEXT[2].daExtParam[5] = camera.ThirdCamera[7];

	g_stOVSBasicInfo.staCameraParamEXT[3].daExtParam[0] = camera.FourthCamera[2];
	g_stOVSBasicInfo.staCameraParamEXT[3].daExtParam[1] = camera.FourthCamera[3];
	g_stOVSBasicInfo.staCameraParamEXT[3].daExtParam[2] = camera.FourthCamera[4];
	g_stOVSBasicInfo.staCameraParamEXT[3].daExtParam[3] = camera.FourthCamera[5];
	g_stOVSBasicInfo.staCameraParamEXT[3].daExtParam[4] = camera.FourthCamera[6];
	g_stOVSBasicInfo.staCameraParamEXT[3].daExtParam[5] = camera.FourthCamera[7];

	TvsLibSetDefaultParam(&g_stOVSBasicInfo);

	int iRet = init_malloc(&g_stOVSBasicInfo, &g_stAvmTableLead, &g_stAvmTableSupport);
	LDWBirdview_CalcVerAndTex(&g_stOVSBasicInfo, &g_stAvmTableLead, &g_stAvmTableSupport);
}

void CAVMVideoDecomposingToolDlg::OnBnClickedVideoButton()
{
	// TODO: 在此添加控件通知处理程序代码
	char pFileNameBuffer[30 * 200] = { 0 };

	m_comVideo.ResetContent();
	videoFilePath.reserve(100);
	videoFilePath.clear();

	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = "视频文件(*.mp4) | *.mp4 | All Files(*.*) | *.* || ";
	dlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;
	dlg.m_ofn.nMaxFile = 30 * 200;
	dlg.m_ofn.lpstrFile = pFileNameBuffer;

	if (IDOK == dlg.DoModal())
	{
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{ 
			videoFilePath.push_back(dlg.GetNextPathName(pos));
		}
	}

	for (int i = 0; i < videoFilePath.size(); i++)
	{
		m_comVideo.AddString(videoFilePath[i]);
	}
	m_comVideo.SetCurSel(0);

}

void CAVMVideoDecomposingToolDlg::OnBnClickedSaveButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ChosefilePath;
	CString fileName;
	CString FolderPath;

	m_pathEdit.Clear();
	folderFilePath.resize(100);
	folderFilePath.clear();
	fileNameContainer.reserve(100);
	fileNameContainer.clear();

	CFolderPickerDialog fd(NULL, 0, this, 0);

	if (fd.DoModal() == IDOK)
	{
		ChosefilePath = fd.GetPathName();
		m_pathEdit.SetWindowText(ChosefilePath);

		for (int i = 0; i < videoFilePath.size(); i++)
		{
			int num = videoFilePath[i].ReverseFind('.');
			fileName = videoFilePath[i].Left(num);
			num = fileName.ReverseFind('\\');
			fileName.Delete(0, num + 1);
			fileNameContainer.push_back(fileName);
			FolderPath = ChosefilePath + "\\" + fileName;
			if (!PathIsDirectory(FolderPath))
			{
				CreateDirectory(FolderPath, NULL);
			}
			else
			{
				MessageBox("目录已存在！");
				return;
			}
			
			folderFilePath.push_back(FolderPath);
		}
	}
	
}

void CAVMVideoDecomposingToolDlg::OnBnClickedTsfmnButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csStr;
	CString videStr;
	CString saveStr;

	m_parameterEdit.GetWindowText(csStr);
	m_pathEdit.GetWindowText(saveStr);
	m_comVideo.GetWindowText(videStr);

	if (csStr.IsEmpty()|| saveStr.IsEmpty()|| videStr.IsEmpty())
	{
		MessageBox("请选全数据！");
		return;
	}

	_beginthreadex(NULL, 0, &Thread, this, 0, NULL);

}

void CAVMVideoDecomposingToolDlg::ShowImage(IplImage* image, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(image);
	cimg.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);
}

unsigned int __stdcall Thread(LPVOID lpParamter)
{
	CAVMVideoDecomposingToolDlg *pDlg = (CAVMVideoDecomposingToolDlg*)lpParamter;

	pDlg->bStart = TRUE;
	CvCapture * m_pCap;
	IplImage * m_pImgSrc;
	int iCount = 0;

	if (NULL == g_pDialogProgress)
	{
		g_pDialogProgress = new CDialogProgress();
	}

	g_pDialogProgress->Create(CDialogProgress::IDD, pDlg->GetDlgItem(IDD_DIALOG_PROGRESS));
	g_pDialogProgress->ShowWindow(SW_NORMAL);


	for (int i = 0; i < pDlg->videoFilePath.size(); i++)
	{
		m_pCap = cvCreateFileCapture(pDlg->videoFilePath[i]);

		m_pImgSrc = cvQueryFrame(m_pCap);
		int m_iFrames = (int)cvGetCaptureProperty(m_pCap, CV_CAP_PROP_FRAME_COUNT);

		IplImage * pSrcImage[4];
		for (int i = 0; i < 4; i++)
		{
			pSrcImage[i] = cvCreateImage(cvSize(m_pImgSrc->width / 2, m_pImgSrc->height / 2), m_pImgSrc->depth, m_pImgSrc->nChannels);
		}

		IplImage* pInvColorImg = cvCreateImage(cvSize(INV_IMAGE_WIDTH, INV_IMAGE_HEIGHT), IPL_DEPTH_8U, 3);

		CvRect rc[4] = { { 0, 0, m_pImgSrc->width / 2, m_pImgSrc->height / 2 },
		{ m_pImgSrc->width / 2, 0, m_pImgSrc->width / 2, m_pImgSrc->height / 2 },
		{ 0, m_pImgSrc->height / 2, m_pImgSrc->width / 2, m_pImgSrc->height / 2 },
		{ m_pImgSrc->width / 2, m_pImgSrc->height / 2, m_pImgSrc->width / 2, m_pImgSrc->height / 2 } };

		while (m_pImgSrc)
		{
			g_pDialogProgress->StepIt();
			for (int i = 0; i < 4; i++)
			{
				cvSetImageROI(m_pImgSrc, rc[i]);
				cvCopyImage(m_pImgSrc, pSrcImage[i]);
				cvResetImageROI(m_pImgSrc);
			}
			
			MapBirdImgRGB(pSrcImage, pInvColorImg, 0, &g_stAvmTableLead, &g_stAvmTableSupport, LIB_INTERPOLATE_ON, LIB_WHITE_BALANCE_OFF);

			CString str;
			str.Format(_T("%04d"), iCount++);
			CString szFilename = pDlg->folderFilePath[i] + "\\" + pDlg->fileNameContainer[i] + "-" + str + ".jpg";

			g_pDialogProgress->SetTip("正在读取【" + pDlg->fileNameContainer[i] + "】视频信息...");

			cvSaveImage(szFilename, pInvColorImg);

			m_pImgSrc = cvQueryFrame(m_pCap);

			if (pDlg->bStart)
			{
				CString onePicturePath = pDlg->folderFilePath[0] + "\\" + pDlg->fileNameContainer[0] + "-" + "0000" + ".jpg";
				pDlg->ipl = cvLoadImage(CT2CA(onePicturePath), 1);
				pDlg->ShowImage(pDlg->ipl, IDC_SHOW);
				pDlg->bStart = FALSE;
			}

		}
	}

	g_pDialogProgress->Stop();

	if (NULL != g_pDialogProgress)
	{
		if (TRUE == ::IsWindow(g_pDialogProgress->GetSafeHwnd()))
		{
			g_pDialogProgress->DestroyWindow();
		}
		delete g_pDialogProgress;
		g_pDialogProgress = NULL;

	}

	pDlg->ipl = NULL;
	return 1;
}




