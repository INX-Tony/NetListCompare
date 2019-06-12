// Option_Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "NetCompare.h"
#include "Option_Dlg.h"
#include "afxdialogex.h"



// COption_Dlg 對話方塊

IMPLEMENT_DYNAMIC(COption_Dlg, CDialogEx)

COption_Dlg::COption_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COption_Dlg::IDD, pParent)
{

}

COption_Dlg::~COption_Dlg()
{
}

void COption_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COption_Dlg, CDialogEx)

   ON_BN_CLICKED(IDOK, &COption_Dlg::OnBnClickedOk)
   ON_WM_CREATE()
   ON_WM_TIMER()
   ON_BN_CLICKED(IDC_CHECK_DECAL_CHG, &COption_Dlg::OnBnClickedCheckDecalChg)
   ON_BN_CLICKED(IDC_CHECK_PARTS_REMOVE, &COption_Dlg::OnBnClickedCheckPartsRemove)
   ON_BN_CLICKED(IDC_CHECK_PARTS_ADD, &COption_Dlg::OnBnClickedCheckPartsAdd)
   ON_BN_CLICKED(IDC_CHECK_NETS_REMOVE, &COption_Dlg::OnBnClickedCheckNetsRemove)
   ON_BN_CLICKED(IDC_CHECK_NETS_ADD, &COption_Dlg::OnBnClickedCheckNetsAdd)
   ON_BN_CLICKED(IDC_CHECK_NODE_CHG, &COption_Dlg::OnBnClickedCheckNodeChg)
   ON_BN_CLICKED(IDC_CHECK_NODE_REMOVE, &COption_Dlg::OnBnClickedCheckNodeRemove)
   ON_BN_CLICKED(IDC_CHECK_ADD, &COption_Dlg::OnBnClickedCheckAdd)
END_MESSAGE_MAP()


void COption_Dlg::OnBnClickedOk()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   CDialogEx::OnOK();
}


int COption_Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CDialogEx::OnCreate(lpCreateStruct) == -1)
      return -1;

   // TODO:  在此加入特別建立的程式碼
   bInit_Flag = false;
   SetTimer(TIMER_INIT, 200, NULL);

   return 0;
}


void COption_Dlg::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值 

   if (nIDEvent == TIMER_INIT && GetDlgItem(IDC_CHECK_DECAL_CHG)!=NULL && !bInit_Flag){     

      //Parts compare options
      if(m_pNetCompareDlg->m_net_compare_option.bPart_decal_change)
         ((CButton *)GetDlgItem(IDC_CHECK_DECAL_CHG))->SetCheck(true);
      else
         ((CButton *)GetDlgItem(IDC_CHECK_DECAL_CHG))->SetCheck(false);

      if(m_pNetCompareDlg->m_net_compare_option.bPart_removed)
         ((CButton *)GetDlgItem(IDC_CHECK_PARTS_REMOVE))->SetCheck(true);
      else
         ((CButton *)GetDlgItem(IDC_CHECK_PARTS_REMOVE))->SetCheck(false);

      if(m_pNetCompareDlg->m_net_compare_option.bPart_added)
         ((CButton *)GetDlgItem(IDC_CHECK_PARTS_ADD))->SetCheck(true);
      else
         ((CButton *)GetDlgItem(IDC_CHECK_PARTS_ADD))->SetCheck(false);

      //Nets compare options
      if(m_pNetCompareDlg->m_net_compare_option.bNet_removed)
         ((CButton *)GetDlgItem(IDC_CHECK_NETS_REMOVE))->SetCheck(true);
      else
         ((CButton *)GetDlgItem(IDC_CHECK_NETS_REMOVE))->SetCheck(false);

      if(m_pNetCompareDlg->m_net_compare_option.bNet_added)
         ((CButton *)GetDlgItem(IDC_CHECK_NETS_ADD))->SetCheck(true);
      else
         ((CButton *)GetDlgItem(IDC_CHECK_NETS_ADD))->SetCheck(false);

      //Node compare options
      if(m_pNetCompareDlg->m_net_compare_option.bNode_change)
         ((CButton *)GetDlgItem(IDC_CHECK_NODE_CHG))->SetCheck(true);
      else
         ((CButton *)GetDlgItem(IDC_CHECK_NODE_CHG))->SetCheck(false);

      if(m_pNetCompareDlg->m_net_compare_option.bNode_removed)
         ((CButton *)GetDlgItem(IDC_CHECK_NODE_REMOVE))->SetCheck(true);
      else
         ((CButton *)GetDlgItem(IDC_CHECK_NODE_REMOVE))->SetCheck(false);

      if(m_pNetCompareDlg->m_net_compare_option.bNode_added)
         ((CButton *)GetDlgItem(IDC_CHECK_ADD))->SetCheck(true);
      else
         ((CButton *)GetDlgItem(IDC_CHECK_ADD))->SetCheck(false);

      bInit_Flag = true;
      KillTimer(TIMER_INIT);
   }//end of TIMER_INIT


   CDialogEx::OnTimer(nIDEvent);
}


void COption_Dlg::OnBnClickedCheckDecalChg()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   if ( ((CButton *)GetDlgItem(IDC_CHECK_DECAL_CHG))->GetCheck() == BST_CHECKED)
      m_pNetCompareDlg->m_net_compare_option.bPart_decal_change = true;
   else
      m_pNetCompareDlg->m_net_compare_option.bPart_decal_change = false;   
}


void COption_Dlg::OnBnClickedCheckPartsRemove()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   if ( ((CButton *)GetDlgItem(IDC_CHECK_PARTS_REMOVE))->GetCheck() == BST_CHECKED)
      m_pNetCompareDlg->m_net_compare_option.bPart_removed = true;
   else
      m_pNetCompareDlg->m_net_compare_option.bPart_removed = false; 

}


void COption_Dlg::OnBnClickedCheckPartsAdd()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   if ( ((CButton *)GetDlgItem(IDC_CHECK_PARTS_ADD))->GetCheck() == BST_CHECKED)
      m_pNetCompareDlg->m_net_compare_option.bPart_added = true;
   else
      m_pNetCompareDlg->m_net_compare_option.bPart_added = false; 
}


void COption_Dlg::OnBnClickedCheckNetsRemove()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   if ( ((CButton *)GetDlgItem(IDC_CHECK_NETS_REMOVE))->GetCheck() == BST_CHECKED)
      m_pNetCompareDlg->m_net_compare_option.bNet_removed = true;
   else
      m_pNetCompareDlg->m_net_compare_option.bNet_removed = false;
}


void COption_Dlg::OnBnClickedCheckNetsAdd()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   if ( ((CButton *)GetDlgItem(IDC_CHECK_NETS_ADD))->GetCheck() == BST_CHECKED)
      m_pNetCompareDlg->m_net_compare_option.bNet_added = true;
   else
      m_pNetCompareDlg->m_net_compare_option.bNet_added = false;
}

void COption_Dlg::OnBnClickedCheckNodeChg()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   if ( ((CButton *)GetDlgItem(IDC_CHECK_NODE_CHG))->GetCheck() == BST_CHECKED)
      m_pNetCompareDlg->m_net_compare_option.bNode_change = true;
   else
      m_pNetCompareDlg->m_net_compare_option.bNode_change = false;
}


void COption_Dlg::OnBnClickedCheckNodeRemove()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   if ( ((CButton *)GetDlgItem(IDC_CHECK_NODE_REMOVE))->GetCheck() == BST_CHECKED)
      m_pNetCompareDlg->m_net_compare_option.bNode_removed = true;
   else
      m_pNetCompareDlg->m_net_compare_option.bNode_removed = false;
}


void COption_Dlg::OnBnClickedCheckAdd()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   if ( ((CButton *)GetDlgItem(IDC_CHECK_ADD))->GetCheck() == BST_CHECKED)
      m_pNetCompareDlg->m_net_compare_option.bNode_added = true;
   else
      m_pNetCompareDlg->m_net_compare_option.bNode_added = false;
}


