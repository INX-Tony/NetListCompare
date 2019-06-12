
// NetCompareDlg.h : ���Y��
//

#pragma once

#include "NetParse.h"
#include "afxdlgs.h"

// CNetCompareDlg ��ܤ��
class CNetCompareDlg : public CDialogEx
{
// �غc
public:
	CNetCompareDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_NETCOMPARE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩

// �{���X��@
protected:
	CNetParse m_par_netlist;
   
   void m_PartsCompare(void);
   void m_NetsNodesCompare(void);

public:
   NetCompareOption m_net_compare_option;
	

// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
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
