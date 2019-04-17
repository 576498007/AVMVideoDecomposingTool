// DialogProgress.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AVMVideoDecomposingTool.h"
#include "DialogProgress.h"
#include "afxdialogex.h"


CDialogProgress* g_pDialogProgress = NULL;

// CDialogProgress �Ի���

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


// CDialogProgress ��Ϣ�������


BOOL CDialogProgress::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_progressInfo.SetRange32(0, 10);
	m_progressInfo.SetStep(1);
	m_progressInfo.SetPos(0);
	m_progressTip.SetWindowText(_T("���ڵȴ�ִ��..."));
	m_bProcessing = false;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDialogProgress::StepIt()
{
	// TODO: �ڴ˴����ʵ�ִ���.
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
	// TODO: �ڴ˴����ʵ�ִ���.
	m_bProcessing = true;
	m_progressTip.SetWindowText(sTip);
	m_progressTip, SetRedraw(TRUE);
}


void CDialogProgress::Stop()
{
	// TODO: �ڴ˴����ʵ�ִ���.
	m_bProcessing = false;
	m_progressInfo.SetPos(10);
	m_progressTip.SetWindowText(_T("����..."));
	SetRedraw(TRUE);
}


void CDialogProgress::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bProcessing)
		return;
	CDialog::OnClose();
}
