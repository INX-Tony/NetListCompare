#pragma once

#include "NetFilter.h"

#define TIMER_INIT 1


// CFilter_Dlg 對話方塊

class CFilter_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilter_Dlg)

public:
   CNetFilter m_netfilter;


	CFilter_Dlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CFilter_Dlg();

// 對話方塊資料
	enum { IDD = IDD_FILTER_DIALOG };

protected:
   CString m_str_keyword;   
   bool bInit_Flag;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
   CString m_str_filename;

   afx_msg void OnBnClickedButtonLoad();
   afx_msg void OnBnClickedMoveOnelistBut();
   afx_msg void OnBnClickedMoveAllnetBut();
   afx_msg void OnBnClickedClrAllcomponentBut();
   afx_msg void OnBnClickedClrOnecomponentBut();
   afx_msg void OnBnClickedFiltBut();
   afx_msg void OnLbnSelchangeIndicatedNetList();
   afx_msg void OnBnClickedOk();
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnClose();
   afx_msg void OnTimer(UINT_PTR nIDEvent);
};
