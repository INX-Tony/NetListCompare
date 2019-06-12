#pragma once

#include "NetCompareDlg.h"
#include "NetParse.h"


#define TIMER_INIT 1
// COption_Dlg ��ܤ��

class COption_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(COption_Dlg)

public:
	COption_Dlg(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~COption_Dlg();

// ��ܤ�����
	enum { IDD = IDD_OPTION_DIALOG };

protected:
   bool bInit_Flag;


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
   CNetCompareDlg *m_pNetCompareDlg;

   afx_msg void OnBnClickedOk();
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnBnClickedCheckDecalChg();
   afx_msg void OnBnClickedCheckPartsRemove();
   afx_msg void OnBnClickedCheckPartsAdd();
   afx_msg void OnBnClickedCheckNetsRemove();
   afx_msg void OnBnClickedCheckNetsAdd();
   afx_msg void OnBnClickedCheckNodeChg();
   afx_msg void OnBnClickedCheckNodeRemove();
   afx_msg void OnBnClickedCheckAdd();
};
