// DialogProgress.cpp : 实现文件
//

#include "stdafx.h"
#include "AVMVideoDecomposingTool.h"
#include "DialogProgress.h"
#include "afxdialogex.h"


CDialogProgress* g_pDialogProgress = NULL;

// CDialogProgress 对话框

IMPLEMENT_DYNAMIC(CDialogProgress, CDialog)

CDialogProgress::CDialogProgress(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_PROGRESS, pParent)
{

}

CDialogProgress::~CDialogProgress()
{
}

void CDialogProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_TIP, m_progressTip);
	DDX_Control(pDX, IDC_PROGRESS_INFO, m_progressInfo);
}


BEGIN_MESSAGE_MAP(CDialogProgress, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDialogProgress 消息处理程序


BOOL CDialogProgress::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_progressInfo.SetRange32(0, 10);
	m_progressInfo.SetStep(1);
	m_progressInfo.SetPos(0);
	m_progressTip.SetWindowText(_T("正在等待执行..."));
	m_bProcessing = false;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogProgress::StepIt()
{
	// TODO: 在此处添加实现代码.
	m_bProcessing = true;
	if (m_progressInfo.GetPos() >= 10)
	{
		m_progressInfo.SetPos(0);
	}
	else
	{
		m_progressInfo.StepIt();
	}
	m_progressInfo.SetRedraw(TRUE);
}


void CDialogProgress::SetTip(CString sTip)
{
	// TODO: 在此处添加实现代码.
	m_bProcessing = true;
	m_progressTip.SetWindowText(sTip);
	m_progressTip, SetRedraw(TRUE);
}


void CDialogProgress::Stop()
{
	// TODO: 在此处添加实现代码.
	m_bProcessing = false;
	m_progressInfo.SetPos(10);
	m_progressTip.SetWindowText(_T("结束..."));
	SetRedraw(TRUE);
}


void CDialogProgress::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bProcessing)
		return;
	CDialog::OnClose();
}
