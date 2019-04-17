
// AVMVideoDecomposingToolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CvvImage.h"

#include<vector>
#include "afxcmn.h"
using namespace std;

// CAVMVideoDecomposingToolDlg 对话框
class CAVMVideoDecomposingToolDlg : public CDialogEx
{
// 构造
public:
	CAVMVideoDecomposingToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AVMVIDEODECOMPOSINGTOOL_DIALOG };
#endif

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
	typedef struct _Camera
	{
		vector<double> FirstCamera;
		vector<double> SecondCamera;
		vector<double> ThirdCamera;
		vector<double> FourthCamera;
	}Camera;

	Camera camera;

public:
	afx_msg void OnBnClickedVideoButton();
	afx_msg void OnBnClickedParameterButton();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedTsfmnButton();

	void ShowImage(IplImage* image, UINT ID);
	friend unsigned int __stdcall Thread(LPVOID lpParamter);
public:
	vector<CString> videoFilePath;
	vector<CString> folderFilePath;
	vector<CString> fileNameContainer;

	CEdit m_pathEdit;
	CEdit m_parameterEdit;

	CComboBox m_comVideo;

	BOOL bStart;

	IplImage * ipl;
	
};
