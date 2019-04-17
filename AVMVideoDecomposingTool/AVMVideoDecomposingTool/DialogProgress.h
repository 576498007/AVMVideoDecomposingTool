#pragma once
#include "resource.h"

// CDialogProgress �Ի���

class CDialogProgress : public CDialog
{
	DECLARE_DYNAMIC(CDialogProgress)

public:
	CDialogProgress(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CDialogProgress();

	// �Ի�������
	//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROGRESS };
	//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void StepIt();
	void SetTip(CString sTip);
	void Stop();
	afx_msg void OnClose();

private:
	CStatic m_progressTip;
	CProgressCtrl m_progressInfo;
	bool m_bProcessing;
};

