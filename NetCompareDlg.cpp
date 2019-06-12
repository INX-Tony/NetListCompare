
// NetCompareDlg.cpp : 實作檔
//
#include "stdafx.h"
#include "afxwin.h"
#include "NetCompare.h"
#include "NetCompareDlg.h"
#include "Filter_Dlg.h"
#include "Option_Dlg.h"
#include "afxdialogex.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CSheets.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
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


// CNetCompareDlg 對話方塊




CNetCompareDlg::CNetCompareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetCompareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetCompareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CNetCompareDlg::OnBnClickedCancel)
	ON_COMMAND(IDCLOSE, &CNetCompareDlg::OnIdclose)
	ON_BN_CLICKED(IDOK, &CNetCompareDlg::OnBnClickedOk)
   ON_BN_CLICKED(IDOK_START, &CNetCompareDlg::OnBnClickedStart)
   ON_BN_CLICKED(IDOK_CLEAR_LOG, &CNetCompareDlg::OnBnClickedClearLog)
   ON_BN_CLICKED(IDOK_SAVE_LOG, &CNetCompareDlg::OnBnClickedSaveLog)
   ON_BN_CLICKED(IDC_BUTTON_OPEN_OLD, &CNetCompareDlg::OnBnClickedButtonOpenOld)
   ON_BN_CLICKED(IDC_BUTTON_OPEN_NEW, &CNetCompareDlg::OnBnClickedButtonOpenNew)
//   ON_WM_KEYDOWN()
//ON_WM_KEYUP()
//ON_WM_CHAR()
//ON_WM_VKEYTOITEM()
//ON_WM_LBUTTONUP()
//ON_WM_CTLCOLOR()
//ON_WM_DRAWITEM()
//ON_WM_DRAWITEM()
ON_WM_DRAWITEM()
ON_BN_CLICKED(IDOK_SAVE_LOG2, &CNetCompareDlg::OnBnClickedSaveLog2)
ON_LBN_SELCHANGE(IDC_LIST_LOG, &CNetCompareDlg::OnLbnSelchangeListLog)
ON_WM_CREATE()
ON_BN_CLICKED(IDOK_OPTION, &CNetCompareDlg::OnBnClickedOption)
END_MESSAGE_MAP()


// CNetCompareDlg 訊息處理常式

BOOL CNetCompareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CNetCompareDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CNetCompareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CNetCompareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNetCompareDlg::OnBnClickedCancel()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	CDialogEx::OnCancel();
}


void CNetCompareDlg::OnIdclose()
{
	// TODO: 在此加入您的命令處理常式程式碼

}

void CNetCompareDlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼

  
	
}


void CNetCompareDlg::OnBnClickedStart()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   CString str_o_path_name, str_n_path_name;
   CString str1;
   CListBox *pList;   
   CButton *p_but;
   
   //disable button
   p_but = (CButton *)GetDlgItem(IDOK_START);
   p_but->EnableWindow(false);
   p_but = (CButton *)GetDlgItem(IDCANCEL);
   p_but->EnableWindow(false);
   p_but = (CButton *)GetDlgItem(IDOK_SAVE_LOG);
   p_but->EnableWindow(false);
   p_but = (CButton *)GetDlgItem(IDOK_CLEAR_LOG);
   p_but->EnableWindow(false);

   pList = (CListBox *)GetDlgItem(IDC_LIST_LOG);
   //pList->SetCurSel(pList->GetCount()-1);
   pList->ResetContent();
   Sleep(300);

	//str_o_path_name = "D:\\TonyCoding\\NetCompare\\V650DK3-KS5_IN8922_C-01_20140611.asc";
	//str_n_path_name = "D:\\TonyCoding\\NetCompare\\V650DK3-KS5_IN8922_C-01_20140618.asc";
   GetDlgItem(IDC_EDIT_OLD_FILE) ->GetWindowTextA(str_o_path_name);
   GetDlgItem(IDC_EDIT_NEW_FILE) ->GetWindowTextA(str_n_path_name);
   if(str_o_path_name.GetLength() == 0 || str_n_path_name.GetLength() == 0)
      return;

   str1 =  "Load OLD netlist :";
   str1 = str1 + str_o_path_name;
   pList->AddString(str1);
   m_par_netlist.LoadNetlist_OLD(str_o_path_name);

   str1 =  "Load NEW netlist :";
   str1 = str1 + str_n_path_name;
   pList->AddString(str1);
   m_par_netlist.LoadNetlist_NEW(str_n_path_name);

   //Parts compare
   m_PartsCompare();

   //Nets compare
   m_NetsNodesCompare();

   //disable button
   p_but = (CButton *)GetDlgItem(IDOK_START);
   p_but->EnableWindow(true);
   p_but = (CButton *)GetDlgItem(IDCANCEL);
   p_but->EnableWindow(true);
   p_but = (CButton *)GetDlgItem(IDOK_SAVE_LOG);
   p_but->EnableWindow(true);
   p_but = (CButton *)GetDlgItem(IDOK_CLEAR_LOG);
   p_but->EnableWindow(true);

}
//--------------------------------------------------------------------------------------------------
void CNetCompareDlg::m_PartsCompare(void)
{
   CString str1, str2, str3;
   CListBox *pList;
   int ii, i_match_inx, i_match_counter;
   unsigned int ui_error_code;
   
   pList = (CListBox *)GetDlgItem(IDC_LIST_LOG);
   pList->SetCurSel(pList->GetCount()-1);
   pList -> AddString (" ");

   str1 = "=============== Parts compare ===============";
   pList -> AddString (str1);
   
   i_match_counter = 0;
   for( ii=0 ; ii<m_par_netlist.g_old_net_part.i_total_parts ; ii++){
      i_match_inx = m_par_netlist.PartHaveMatch_OldToNew (ii, &ui_error_code);
      if ( (i_match_inx == -1) &&  m_net_compare_option.bPart_removed){
         str1 = m_par_netlist.g_old_net_part.PartsList[ii].str_location;
         str2 = ", removed from old";
         str3 = str1 + str2;
         pList -> AddString(str3);
         pList->SetCurSel(pList->GetCount()-1);
         
      }//end of if "i_match_inx == -1"
      else{
         if( (ui_error_code == CODE_DECAL) && m_net_compare_option.bPart_decal_change){
            str1 = ", Decal changed, ";
            str2 = m_par_netlist.g_old_net_part.PartsList[ii].str_location + str1;
            str1 = " --->";
            str2 = str2 + m_par_netlist.g_old_net_part.PartsList[ii].str_decal + str1 + m_par_netlist.g_new_net_part.PartsList[i_match_inx].str_decal;
            pList -> AddString (str2);
            pList->SetCurSel(pList->GetCount()-1);
            
         }//end of ui_error_code == CODE_DECAL
         i_match_counter ++;
      }//end of else to "i_match_inx == -1"         
   }//end of for loop of ii<m_par_netlist.g_old_net_part.i_total_parts

   i_match_counter = 0;
   for( ii=0 ; ii<m_par_netlist.g_new_net_part.i_total_parts ; ii++){
      i_match_inx = m_par_netlist.PartHaveMatch_NewToOld (ii, &ui_error_code);
      if ((i_match_inx == -1) && m_net_compare_option.bPart_added){
         str1 = m_par_netlist.g_new_net_part.PartsList[ii].str_location;
         str2 = ", added to new";
         str3 = str1 + str2;
         pList -> AddString(str3);
         pList->SetCurSel(pList->GetCount()-1);
         
      }//end of if "i_match_inx == -1"
      else{
         i_match_counter ++;
      }//end of else to "i_match_inx == -1"         
   }//end of for loop of ii<m_par_netlist.g_old_net_part.i_total_parts

   pList -> AddString (">>>>>>Parts compare done!!!<<<<<<");
   
   pList->SetCurSel(pList->GetCount()-1);
}

//--------------------------------------------------------------------------------------------------
//Algorithm for NetCompare V1.1
//Modify nodes compare flow
void CNetCompareDlg::m_NetsNodesCompare(void)
{
   CString str1, str2, str3, str4, str5, str6;
   CListBox *pList;
   int i_match_inx, i_match_counter;
   int i_node_match_inx;
   int i_net_inx;
   int i_total_net;
   int i_total_net_in_new, i_total_net_in_old;
   int i_total_node_in_new, i_total_node_in_old;
   int ii, kk;
   unsigned int ui_error_code;
   bool bFind_Flag;

   pList = (CListBox *)GetDlgItem(IDC_LIST_LOG);
   pList->SetCurSel(pList->GetCount()-1);
   pList -> AddString (" ");

   str1 = "=============== Net & Node compare ===============";
   pList -> AddString (str1);
   
   //compare netlist
   pList -> AddString(">Nets compare<");
   i_match_counter = 0;
   i_total_net = m_par_netlist.g_old_net_part.i_total_nets;
   for( i_net_inx=0 ; i_net_inx < i_total_net ; i_net_inx++){
      i_match_inx = m_par_netlist.NetHaveMatch_OldToNew (i_net_inx, &ui_error_code);
      if ( (i_match_inx == -1) && m_net_compare_option.bNet_removed){
         str1 = m_par_netlist.g_old_net_part.NetList[i_net_inx]->str_netname;
         str2 = ", removed from old";
         str3 = str1 + str2;
         pList -> AddString(str3);
         
         pList->SetCurSel(pList->GetCount()-1);
      }//end of if "i_match_inx == -1"
      else{
         i_match_counter ++;
      }//end of else to "i_match_inx == -1"         
   }//end of for loop of ii<m_par_netlist.g_old_net_part.i_total_parts


   i_match_counter = 0;
   i_total_net = m_par_netlist.g_new_net_part.i_total_nets;
   for( i_net_inx=0 ; i_net_inx < i_total_net ; i_net_inx++){
      i_match_inx = m_par_netlist.NetHaveMatch_NewToOld (i_net_inx, &ui_error_code);
      if ( (i_match_inx == -1) && m_net_compare_option.bNet_added){
         str1 = m_par_netlist.g_new_net_part.NetList[i_net_inx]->str_netname;
         str2 = ", added to new";
         str3 = str1 + str2;
         pList -> AddString(str3);
         
         pList->SetCurSel(pList->GetCount()-1);
      }//end of if "i_match_inx == -1"
      else{
         i_match_counter ++;
      }//end of else to "i_match_inx == -1"         
   }//end of for loop of ii<m_par_netlist.g_old_net_part.i_total_parts   


   //compare nodes
   pList -> AddString("");
   pList -> AddString(">Nodes compare<");   
   i_total_net_in_old = m_par_netlist.g_old_net_part.i_total_nets;
   for( i_net_inx=0 ; i_net_inx < i_total_net_in_old ; i_net_inx++){  //check nodes from OLD to New      
      i_total_node_in_old = m_par_netlist.g_old_net_part.NetList[i_net_inx]->i_total_nodes;

      i_total_net_in_new = m_par_netlist.g_new_net_part.i_total_nets;
      
      for (kk=0 ; kk<i_total_node_in_old ; kk++){
         bFind_Flag = false;
         i_match_counter = 0;
         for (ii=0 ; ii<i_total_net_in_new && !bFind_Flag; ii++){
            i_node_match_inx = m_par_netlist.NodeHaveMatch_OldToNew(kk, i_net_inx, ii, &ui_error_code);
            if( (i_node_match_inx != -1) && m_net_compare_option.bNode_change){//if found node in NEW net.
               bFind_Flag = true;
               i_match_counter ++;
               str1 = m_par_netlist.g_old_net_part.NetList[i_net_inx]->str_netname;
               str2 = m_par_netlist.g_new_net_part.NetList[ii]->str_netname;
               str3 = m_par_netlist.g_old_net_part.NetList[i_net_inx]->str_nodes[kk];
               if( str1 != str2){
                  str5 = ", changed, ";
                  str6 = "--->";
                  str4 = str3 + str5 + str1 + str6 + str2;
                  pList -> AddString (str4);
                  pList -> SetCurSel(pList->GetCount()-1);
               }
            }//end of found node in NEW net.
         }//ii<i_total_net_in_new && !bFind_Flag
         if ( (i_match_counter == 0) && m_net_compare_option.bNode_removed){
            str1 = m_par_netlist.g_old_net_part.NetList[i_net_inx]->str_nodes[kk];
            str2 = ", removed from old, ";
            str3 = m_par_netlist.g_old_net_part.NetList[i_net_inx]->str_netname;
            str4 = str1 + str2 + str3;
            pList -> AddString (str4);
            pList -> SetCurSel(pList->GetCount()-1);
         }
      }//end of kk<i_total_node_in_old, check node of OLD (i_net_inx) have match to NEW.
   }//check nodes from OLD to New, "i_net_inx < i_total_net_in_old"

    i_total_net_in_new = m_par_netlist.g_new_net_part.i_total_nets;
   for( i_net_inx=0 ; i_net_inx < i_total_net_in_new ; i_net_inx++){  //check nodes from NEW to OLD
      i_total_node_in_new = m_par_netlist.g_new_net_part.NetList[i_net_inx]->i_total_nodes;

      i_total_net_in_old = m_par_netlist.g_old_net_part.i_total_nets;
      
      for (kk=0 ; kk<i_total_node_in_new ; kk++){
         bFind_Flag = false;
         i_match_counter = 0;
         for (ii=0 ; ii<i_total_net_in_old && !bFind_Flag; ii++){
            i_node_match_inx = m_par_netlist.NodeHaveMatch_NewToOld(kk, i_net_inx, ii, &ui_error_code);
            if(i_node_match_inx != -1){//if found node in NEW net.
               bFind_Flag = true;
               i_match_counter ++;               
            }//end of found node in NEW net.
         }//ii<i_total_net_in_old && !bFind_Flag
         if ((i_match_counter == 0) && m_net_compare_option.bNode_added){
            str1 = m_par_netlist.g_new_net_part.NetList[i_net_inx]->str_nodes[kk];
            str2 = ", added to new, ";
            str3 = m_par_netlist.g_new_net_part.NetList[i_net_inx]->str_netname;
            str4 = str1 + str2 + str3;
            pList -> AddString (str4);
            pList -> SetCurSel(pList->GetCount()-1);
         }
      }//end of kk<i_total_node_in_old, check node of OLD (i_net_inx) have match to NEW.
   }//check nodes from NEW to OLD, "i_net_inx < i_total_net_in_new"

   pList -> AddString (">>>>>>Net & Node compare done!!!<<<<<<");
   pList -> AddString ("");
   
   pList->SetCurSel(pList->GetCount()-1);

}
//--------------------------------------------------------------------------------------------------
//Algorithm for NetCompare V1.0
/*
void CNetCompareDlg::m_NetsNodesCompare(void)
{
   CString str1, str2, str3, str4, str5;
   CListBox *pList;
   int i_match_inx, i_match_counter;
   int i_node_match_inx;
   int i_net_inx, i_node_inx;
   int i_total_node;
   unsigned int ui_error_code;
   
   pList = (CListBox *)GetDlgItem(IDC_LIST_LOG);
   pList->SetCurSel(pList->GetCount()-1);
   pList -> AddString (" ");

   str1 = "=============== Net & Node compare ===============";
   pList -> AddString (str1);
   
   //compare netlist
   pList -> AddString(">Nets compare<");
   i_match_counter = 0;
   for( i_net_inx=0 ; i_net_inx < m_par_netlist.g_old_net_part.i_total_nets ; i_net_inx++){
      i_match_inx = m_par_netlist.NetHaveMatch_OldToNew (i_net_inx, &ui_error_code);
      if (i_match_inx == -1){
         str1 = m_par_netlist.g_old_net_part.NetList[i_net_inx]->str_netname;
         str2 = " : Removed from OLD netlist.";
         str3 = str1 + str2;
         pList -> AddString(str3);
         
         pList->SetCurSel(pList->GetCount()-1);
      }//end of if "i_match_inx == -1"
      else{
         i_match_counter ++;
      }//end of else to "i_match_inx == -1"         
   }//end of for loop of ii<m_par_netlist.g_old_net_part.i_total_parts


   i_match_counter = 0;
   for( i_net_inx=0 ; i_net_inx < m_par_netlist.g_new_net_part.i_total_nets ; i_net_inx++){
      i_match_inx = m_par_netlist.NetHaveMatch_NewToOld (i_net_inx, &ui_error_code);
      if (i_match_inx == -1){
         str1 = m_par_netlist.g_new_net_part.NetList[i_net_inx]->str_netname;
         str2 = " : Added to NEW netlist.";
         str3 = str1 + str2;
         pList -> AddString(str3);
         
         pList->SetCurSel(pList->GetCount()-1);
      }//end of if "i_match_inx == -1"
      else{
         i_match_counter ++;
      }//end of else to "i_match_inx == -1"         
   }//end of for loop of ii<m_par_netlist.g_old_net_part.i_total_parts   


   //compare nodes
   pList -> AddString("");
   pList -> AddString(">Nodes compare<");
   i_match_counter = 0;
   for( i_net_inx=0 ; i_net_inx < m_par_netlist.g_old_net_part.i_total_nets ; i_net_inx++){
      i_match_inx = m_par_netlist.NetHaveMatch_OldToNew (i_net_inx, &ui_error_code);
      if (i_match_inx != -1){
         //have matched node if netname is match.
         i_total_node = m_par_netlist.g_old_net_part.NetList[i_net_inx]->i_total_nodes;
         for( i_node_inx = 0 ; i_node_inx < i_total_node ; i_node_inx ++){
            i_node_match_inx = m_par_netlist.NodeHaveMatch_OldToNew(i_node_inx, i_net_inx, i_match_inx, &ui_error_code);
            if( i_node_match_inx == -1){
               str1 = m_par_netlist.g_old_net_part.NetList[i_net_inx]->str_nodes[i_node_inx];
               str2 = " in ";
               str3 = m_par_netlist.g_old_net_part.NetList[i_net_inx]->str_netname;
               str4 = " removed from OLD netlist.";
               str5 = str1 + str2 + str3 + str4;
               pList -> AddString (str5);
               
               pList->SetCurSel(pList->GetCount()-1);
            }
         }//end of old to new check loop "i_node_inx"

         i_total_node = m_par_netlist.g_new_net_part.NetList[i_match_inx]->i_total_nodes;
         for( i_node_inx = 0 ; i_node_inx < i_total_node ; i_node_inx ++){
            i_node_match_inx = m_par_netlist.NodeHaveMatch_NewToOld(i_node_inx, i_match_inx, i_net_inx, &ui_error_code);
            if( i_node_match_inx == -1){
               str1 = m_par_netlist.g_new_net_part.NetList[i_match_inx]->str_nodes[i_node_inx];
               str2 = " in ";
               str3 = m_par_netlist.g_new_net_part.NetList[i_match_inx]->str_netname;
               str4 = " added to NEW netlist.";
               str5 = str1 + str2 + str3 + str4;
               pList -> AddString (str5);
               
               pList->SetCurSel(pList->GetCount()-1);
            }
         }//end of new to old check loop "i_node_inx"

         i_match_counter ++;
      }//end of else to "i_match_inx == -1"         
   }//end of for loop of ii<m_par_netlist.g_old_net_part.i_total_parts



   pList -> AddString (">>>>>>Net & Node compare done!!!<<<<<<");
   pList -> AddString ("");
   
   pList->SetCurSel(pList->GetCount()-1);
}
*/
//--------------------------------------------------------------------------------------------------
void CNetCompareDlg::OnBnClickedClearLog()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   CListBox *plist;
   plist = (CListBox *)GetDlgItem(IDC_LIST_LOG);
   plist->ResetContent();
}


void CNetCompareDlg::OnBnClickedSaveLog()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   COleVariant covTrue((short)TRUE), covFalse((short)FALSE), covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	
   LPDISPATCH lpDisp;
	CApplication app;
   CWorkbooks books;
   CWorkbook book;
   CWorksheets sheets;
   CWorksheet sheet;
   CRange range;
   


   CListBox *p_listbox;
   CString str1, str_file, str_ext, str_cell;
   CFileDialog *file;

	CFile fp;

   char szStr[512];
   int iTotalItem, iStrLen, i;


   p_listbox = (CListBox *)GetDlgItem(IDC_LIST_LOG);


	file=new CFileDialog(false,NULL,NULL,OFN_OVERWRITEPROMPT,"CSV files(*.csv)|*.csv|Excel files(*.xls)|*.xls|log files(*.log)|*.log|All Files(*.*)|*.*|",NULL);
	file->DoModal();
	str_file=file->GetPathName();
	str_ext = file->GetFileExt();

	if(!str_file.IsEmpty()){
      if (str_ext == "xls" || str_ext == "XLS"){ //open Excel file

         // Start Excel and get an Application object.
         if(!app.CreateDispatch(TEXT("Excel.Application")))
         {
            AfxMessageBox(TEXT("Couldn't start Excel and get Application object."));
            return;
         }

         app.put_Visible(TRUE);
         app.put_UserControl(TRUE);
         //app.
         lpDisp = app.get_Workbooks();
         ASSERT(lpDisp);               // or fail.
         books.AttachDispatch( lpDisp );

         lpDisp =  books.Add(covOptional);
         book.AttachDispatch (lpDisp);

         sheets = book.get_Worksheets();
         sheet = sheets.get_Item(COleVariant((short)1));
         
         iTotalItem = p_listbox->GetCount();

         
         for(i=0;i<iTotalItem;i++){
            p_listbox->SetCurSel(i);
            p_listbox->GetText(i, szStr); //get string in list0
            str1.Format("'%s", szStr);
            str_cell.Format("A%d", (i+1));
            range = sheet.get_Range(COleVariant(str_cell), COleVariant(str_cell));
            range.put_Value2(COleVariant(str1));            
         }         

         //close & save excel
         book.SaveAs(COleVariant(str_file),covOptional,covOptional,covOptional, covOptional,covOptional,0,covOptional,covOptional,covOptional,covOptional,covOptional);
         book.ReleaseDispatch();
         books.Close();
         books.ReleaseDispatch();
         app.Quit();
         app.ReleaseDispatch();


      }
      else{ //text file, *.csv/*.log fils
         //open file 
         fp.Open(str_file,CFile::modeCreate | CFile::typeBinary |CFile::modeWrite,NULL);

         //get total items in list box
         iTotalItem = p_listbox->GetCount();

         for(i=0;i<iTotalItem;i++){
            p_listbox->SetCurSel(i);
            p_listbox->GetText(i, szStr); //get string in list0
            iStrLen = p_listbox->GetTextLen(i); //get string length
            szStr[iStrLen]=0x0d;
            szStr[iStrLen+1]=0x0a;
            iStrLen+=2;
            fp.Write(szStr, iStrLen);
         }

         //close file
         fp.Close();
      }//end of else
		

	}//end of !str_file.IsEmpty()



	delete file;
}


void CNetCompareDlg::OnBnClickedButtonOpenOld()
{
   CString str1;
   CFileDialog *file;
   
  	file=new CFileDialog(true,NULL,NULL,OFN_FILEMUSTEXIST,"Netlist files(*.asc)|*.asc|All Files(*.*)|*.*|",NULL);
	file->DoModal();
	str1=file->GetPathName();
   GetDlgItem(IDC_EDIT_OLD_FILE)->SetWindowTextA(str1);

}


void CNetCompareDlg::OnBnClickedButtonOpenNew()
{
   CString str1;
   CFileDialog *file;


	file=new CFileDialog(true,NULL,NULL,OFN_FILEMUSTEXIST,"Netlist files(*.asc)|*.asc|All Files(*.*)|*.*|",NULL);
	file->DoModal();
	str1=file->GetPathName();

   GetDlgItem(IDC_EDIT_NEW_FILE)->SetWindowTextA(str1);  

}

//HBRUSH CNetCompareDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//   HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//  /*
//   bool bFlag;
//
//   // TODO:  在此變更 DC 的任何屬性
//   //bFlag = true;
//   //if (pWnd->GetDlgCtrlID() == IDC_LIST_LOG){
//      pDC->SetTextColor(RGB(0xFF, 0xFF, 0xFF));
//      pDC->SetBkColor(RGB(0x7F,0,0x7F)); 
//      bFlag = false;
//      //return (HBRUSH)m_Brush.GetSafeHandle();
//   //}
//   
//   if (!bFlag)
//      return (HBRUSH)m_Brush.GetSafeHandle();
//
//   
//   // TODO:  如果預設值並非想要的，則傳回不同的筆刷
//   */
//   return hbr;
//
//}




void CNetCompareDlg::OnBnClickedSaveLog2()
{
   // TODO: 在此加入控制項告知處理常式程式碼

   CString str1;
   CFilter_Dlg *pFilter_dlg;
   
  pFilter_dlg=new CFilter_Dlg;
   GetDlgItem(IDC_EDIT_NEW_FILE)->GetWindowTextA(str1);
   if (str1.GetLength() >0)
      pFilter_dlg->m_str_filename = str1;
	pFilter_dlg->DoModal();
	
}


void CNetCompareDlg::OnLbnSelchangeListLog()
{
   // TODO: 在此加入控制項告知處理常式程式碼
}


int CNetCompareDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CDialogEx::OnCreate(lpCreateStruct) == -1)
      return -1;

   // TODO:  在此加入特別建立的程式碼
   //NetCompare initialization
   m_net_compare_option.bPart_decal_change = true;
   m_net_compare_option.bPart_removed = true;
   m_net_compare_option.bPart_added = true;
   m_net_compare_option.bNet_removed = true;
   m_net_compare_option.bNet_added = true;
   m_net_compare_option.bNode_change = true;
   m_net_compare_option.bNode_removed = true;
   m_net_compare_option.bNode_added = true;   

   return 0;
}


void CNetCompareDlg::OnBnClickedOption()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   COption_Dlg *pOption_dlg;

   pOption_dlg=new COption_Dlg;
   pOption_dlg->m_pNetCompareDlg = this;
	pOption_dlg->DoModal();

}
