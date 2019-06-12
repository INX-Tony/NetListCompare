
// NetCompareDlg.h : 標頭檔
//

#pragma once

#include "NetParse.h"
#include "afxdlgs.h"

// CNetCompareDlg 對話方塊
class CNetCompareDlg : public CDialogEx
{
// 建構
public:
	CNetCompareDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_NETCOMPARE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援

// 程式碼實作
protected:
	CNetParse m_par_netlist;
   
   void m_PartsCompare(void);
   void m_NetsNodesCompare(void);

public:
   NetCompareOption m_net_compare_option;
	

// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnIdclose();
	afx_msg void OnBnClickedOk();
   afx_msg void OnBnClickedStart();
   afx_msg void OnBnClickedClearLog();
   afx_msg void OnBnClickedSaveLog();
   afx_msg void OnBnClickedButtonOpenOld();
   afx_msg void OnBnClickedButtonOpenNew();

   afx_msg void OnBnClickedSaveLog2();
   afx_msg void OnLbnSelchangeListLog();
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnBnClickedOption();
};
