// Filter_Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "NetCompare.h"
#include "Filter_Dlg.h"
#include "afxdialogex.h"
#include "string.h"


#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CSheets.h"

// CFilter_Dlg 對話方塊

IMPLEMENT_DYNAMIC(CFilter_Dlg, CDialogEx)

CFilter_Dlg::CFilter_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFilter_Dlg::IDD, pParent)
{

}

CFilter_Dlg::~CFilter_Dlg()
{
}

void CFilter_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFilter_Dlg, CDialogEx)
   ON_BN_CLICKED(IDC_BUTTON_LOAD, &CFilter_Dlg::OnBnClickedButtonLoad)
   ON_BN_CLICKED(IDC_MOVE_ONELIST_BUT, &CFilter_Dlg::OnBnClickedMoveOnelistBut)
   ON_BN_CLICKED(IDC_MOVE_ALLNET_BUT, &CFilter_Dlg::OnBnClickedMoveAllnetBut)
   ON_BN_CLICKED(IDC_CLR_ALLCOMPONENT_BUT, &CFilter_Dlg::OnBnClickedClrAllcomponentBut)
   ON_BN_CLICKED(IDC_CLR_ONECOMPONENT_BUT, &CFilter_Dlg::OnBnClickedClrOnecomponentBut)
   ON_BN_CLICKED(IDC_FILT_BUT, &CFilter_Dlg::OnBnClickedFiltBut)   
   ON_LBN_SELCHANGE(IDC_INDICATED_NET_LIST, &CFilter_Dlg::OnLbnSelchangeIndicatedNetList)

   ON_BN_CLICKED(IDOK, &CFilter_Dlg::OnBnClickedOk)
   ON_WM_CREATE()
   ON_WM_CLOSE()
   ON_WM_TIMER()
END_MESSAGE_MAP()


// CFilter_Dlg 訊息處理常式


void CFilter_Dlg::OnBnClickedButtonLoad()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   CString str1, str_net_pathname;
   CFileDialog *file;
   CListBox *pList, *pList2;
   bool b_load_flag;
   int i, i_max;

   pList = (CListBox *)GetDlgItem(IDC_NET_LIST);
   pList2 = (CListBox *)GetDlgItem(IDC_SELECTED_NET_LIST);
   
  	file=new CFileDialog(true,NULL,NULL,OFN_FILEMUSTEXIST,"Netlist files(*.asc)|*.asc|All Files(*.*)|*.*|",NULL);
	file->DoModal();
	str1=file->GetPathName();
   GetDlgItem(IDC_EDIT_NETLIST_FILE)->SetWindowTextA(str1);

   GetDlgItem(IDC_EDIT_NETLIST_FILE) ->GetWindowTextA(str_net_pathname);

   if(str_net_pathname.GetLength() == 0)
      return;

   b_load_flag = m_netfilter.LoadNetlist_Filter(str_net_pathname);      
   
   if ( b_load_flag == true){
      m_netfilter.SortNetlist_Filter();
      pList->ResetContent();
      pList2->ResetContent();

      i_max = m_netfilter.m_netpart_for_filter.i_total_nets;
      for(i=0 ; i<i_max ; i++)
         pList -> AddString (m_netfilter.m_netpart_for_filter.NetList[i]->str_netname);

      MessageBox( "Load netlist file done!", NULL, MB_OK);
   }
   else
      MessageBox( "Load netlist file fail", NULL, MB_OK);

}


void CFilter_Dlg::OnBnClickedMoveOnelistBut()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   int iCount, i, i_inx;
   CString str1;
	CArray<int,int> aryListBoxSel;
   CListBox *pList, *pListTarget;
   

   pList = (CListBox *)GetDlgItem(IDC_NET_LIST);
   pListTarget = (CListBox *)GetDlgItem(IDC_SELECTED_NET_LIST);
   iCount = pList -> GetSelCount();

	aryListBoxSel.SetSize(iCount);
	if (pList->GetSelItems(iCount, aryListBoxSel.GetData()) == LB_ERR)
      return;

	for(i = 0; i < iCount; i++){
		i_inx = aryListBoxSel.GetAt(i);
      pList -> GetText(i_inx, str1);
      pListTarget -> AddString(str1);
	}
   pListTarget->SetCurSel(pListTarget->GetCount()-1);

}


void CFilter_Dlg::OnBnClickedMoveAllnetBut()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   int i, i_max;
   CListBox *pList, *pListTarget;
   CString str1;
   
   pList = (CListBox *)GetDlgItem(IDC_NET_LIST);
   pListTarget = (CListBox *)GetDlgItem(IDC_SELECTED_NET_LIST);
   i_max = pList -> GetCount();
   if (i_max == LB_ERR)
      return;

   for(i = 0; i < i_max; i++){
      pList -> GetText(i, str1);
      pListTarget -> AddString(str1);
	}

   pListTarget->SetCurSel(pListTarget->GetCount()-1);
   
}


void CFilter_Dlg::OnBnClickedClrAllcomponentBut()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   CListBox *pList;   
   pList = (CListBox *)GetDlgItem(IDC_SELECTED_NET_LIST);
   pList -> ResetContent();

}


void CFilter_Dlg::OnBnClickedClrOnecomponentBut()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   CListBox *pList;
   CArray<int,int> aryListBoxSel;
   CString str1;
   int iTotalItem, i_inx, iCount;
   int i;

   pList = (CListBox *)GetDlgItem(IDC_SELECTED_NET_LIST);
   iTotalItem = pList -> GetCount();

   if( iTotalItem !=0 ){
      iCount = pList -> GetSelCount();
      aryListBoxSel.SetSize(iCount);

      if (pList->GetSelItems(iCount, aryListBoxSel.GetData()) == LB_ERR)
         return;

      for(i = (iCount - 1); i>=0; i--){
		   i_inx = aryListBoxSel.GetAt(i);         
         pList -> DeleteString(i_inx);
	   }

   }//end iTotalItem
 	
}


void CFilter_Dlg::OnBnClickedFiltBut()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   CListBox *pList, *pList2, *pList3;
   CString str1;
   int i, ii, i_net_inx, i_sel_net_inx;
   int i_net_max, i_sel_net_max;
   bool bExit_Flag, bFind_Flag;

   pList = (CListBox *)GetDlgItem(IDC_SELECTED_NET_LIST);


   //Release assigned memory space, m_netpart_filtered
   ii = m_netfilter.m_netpart_sel.i_total_nets;
   for (i=0 ; i< ii ; i++){
      if ( m_netfilter.m_netpart_sel.NetList[i] != NULL){
         delete m_netfilter.m_netpart_sel.NetList[i];
         m_netfilter.m_netpart_sel.NetList[i] = NULL;
      }
   }//end of m_netfilter.m_netpart_sel
   m_netfilter.m_netpart_sel.i_total_nets = 0;

   //take selected nets and parts to m_netfilter.m_netpart_sel
   i_sel_net_max = pList -> GetCount();
   for(i_sel_net_inx=0 ;i_sel_net_inx<i_sel_net_max ; i_sel_net_inx++){
      i_net_max = m_netfilter.m_netpart_for_filter.i_total_nets;
      bExit_Flag = false;
      pList->GetText(i_sel_net_inx, str1);
      for(i_net_inx=0 ; (i_net_inx<i_net_max && !bExit_Flag); i_net_inx++){
         if(m_netfilter.m_netpart_for_filter.NetList[i_net_inx]->str_netname == str1){
            bExit_Flag = true;
            m_netfilter.m_netpart_sel.NetList[i_sel_net_inx] = new Net;
            m_netfilter.m_netpart_sel.NetList[i_sel_net_inx]->str_netname = str1;
            m_netfilter.m_netpart_sel.i_total_nets++;
            ii = m_netfilter.m_netpart_for_filter.NetList[i_net_inx]->i_parts_in_net;
            for(i=0 ; i<ii ; i++)
               m_netfilter.m_netpart_sel.NetList[i_sel_net_inx]->Parts_in_Net[i].str_location = m_netfilter.m_netpart_for_filter.NetList[i_net_inx]->Parts_in_Net[i].str_location;
            m_netfilter.m_netpart_sel.NetList[i_sel_net_inx]->i_parts_in_net = m_netfilter.m_netpart_for_filter.NetList[i_net_inx]->i_parts_in_net;
            
         }//end of if
      }//end of i_net_inx
   }//end of i_sel_net_inx
   
   GetDlgItem(IDC_EDIT_KEYWORD) ->GetWindowTextA(m_str_keyword);
   m_str_keyword.MakeUpper();
   bFind_Flag = m_netfilter.FilterByKeyword(m_str_keyword);
   if(bFind_Flag){
      MessageBox( "Component extracted!", NULL, MB_OK);
   }
   else
      MessageBox( "No matched component!", NULL, MB_OK);
   
   pList2 = (CListBox *)GetDlgItem(IDC_INDICATED_NET_LIST);
   pList3 = (CListBox *)GetDlgItem(IDC_FILTER_COMPONENT_LIST);
   pList2->ResetContent();
   pList3->ResetContent();
   if(bFind_Flag){
      pList2 = (CListBox *)GetDlgItem(IDC_INDICATED_NET_LIST);
      ii = m_netfilter.m_netpart_filtered.i_total_nets;
      for(i=0 ; i<ii ;i++)
         pList2->AddString (m_netfilter.m_netpart_filtered.NetList[i]->str_netname);      

   }

}



void CFilter_Dlg::OnLbnSelchangeIndicatedNetList()
{
   // TODO: 在此加入控制項告知處理常式程式碼
   CListBox *pList, *pList2;
   CString str1;
   int i_inx, i, ii;
   
   pList = (CListBox *)GetDlgItem(IDC_INDICATED_NET_LIST);
   pList2 = (CListBox *)GetDlgItem(IDC_FILTER_COMPONENT_LIST);

   if(pList->GetCount() >0){
      i_inx = pList->GetCurSel();
      pList2->ResetContent();
      ii = m_netfilter.m_netpart_filtered.NetList[i_inx]->i_parts_in_net;
      for(i=0 ; i<ii ; i++){
         pList2->AddString(m_netfilter.m_netpart_filtered.NetList[i_inx]->Parts_in_Net[i].str_location);
      }
   }
   

}



void CFilter_Dlg::OnBnClickedOk()
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

   char szStr[1024];
   int i_total_nets, iStrLen, i_inx1, i_inx2, i_inx_max;
   int i_cnt_cell;


   p_listbox = (CListBox *)GetDlgItem(IDC_LIST_LOG);


	file=new CFileDialog(false,NULL,NULL,OFN_OVERWRITEPROMPT,"log files(*.log)|*.log|Excel files(*.xls)|*.xls|All Files(*.*)|*.*|",NULL);
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
         
         //get total items in list box
         i_total_nets = m_netfilter.m_netpart_filtered.i_total_nets;
         i_cnt_cell = 1;
         for(i_inx1=0 ; i_inx1<i_total_nets ; i_inx1++){
            str1 = "'[" + m_netfilter.m_netpart_filtered.NetList[i_inx1]->str_netname + ']';
            str_cell.Format("A%d", i_cnt_cell++);
            range = sheet.get_Range(COleVariant(str_cell), COleVariant(str_cell));
            range.put_Value2(COleVariant(str1));
         
            //write parts to file
            i_inx_max = m_netfilter.m_netpart_filtered.NetList[i_inx1]->i_parts_in_net;
            for(i_inx2=0 ; i_inx2<i_inx_max ; i_inx2++){
               str1 = m_netfilter.m_netpart_filtered.NetList[i_inx1]->Parts_in_Net[i_inx2].str_location;
               str_cell.Format("A%d", i_cnt_cell++ );               
               range = sheet.get_Range(COleVariant(str_cell), COleVariant(str_cell));
               range.put_Value2(COleVariant(str1));
            }//end of i_inx2

         }//end of i_inx1

         str1 = "'*END*";
         str_cell.Format("A%d", i_cnt_cell++ );               
         range = sheet.get_Range(COleVariant(str_cell), COleVariant(str_cell));
         range.put_Value2(COleVariant(str1));

         //close & save excel
         book.SaveAs(COleVariant(str_file),covOptional,covOptional,covOptional, covOptional,covOptional,0,covOptional,covOptional,covOptional,covOptional,covOptional);
         book.ReleaseDispatch();
         books.Close();
         books.ReleaseDispatch();
         app.Quit();
         app.ReleaseDispatch();


      }
      else{ //text file
         //open file 
         fp.Open(str_file,CFile::modeCreate | CFile::typeBinary |CFile::modeWrite,NULL);      


         //get total items in list box
         i_total_nets = m_netfilter.m_netpart_filtered.i_total_nets;

         for(i_inx1=0 ; i_inx1<i_total_nets ; i_inx1++){
            str1 = '[' + m_netfilter.m_netpart_filtered.NetList[i_inx1]->str_netname + ']';
            strcpy_s (szStr, str1);
            iStrLen = str1.GetLength(); //get string length
            szStr[iStrLen]=0x0d;
            szStr[iStrLen+1]=0x0a;
            iStrLen+=2;
            fp.Write(szStr, iStrLen); //wirte netname to file

            
            //write parts to file
            i_inx_max = m_netfilter.m_netpart_filtered.NetList[i_inx1]->i_parts_in_net;
            for(i_inx2=0 ; i_inx2<i_inx_max ; i_inx2++){
               str1 = m_netfilter.m_netpart_filtered.NetList[i_inx1]->Parts_in_Net[i_inx2].str_location;
               strcpy_s (szStr, str1);
               iStrLen = str1.GetLength(); //get string length
               szStr[iStrLen]=0x0d;
               szStr[iStrLen+1]=0x0a;
               iStrLen+=2;
               fp.Write(szStr, iStrLen); //wirte netname to file
            }//end of i_inx2

         }//end of i_inx1

         str1 = "*END*";
         strcpy_s (szStr, str1);
         iStrLen = str1.GetLength(); //get string length
         szStr[iStrLen]=0x0d;
         szStr[iStrLen+1]=0x0a;
         iStrLen+=2;
         fp.Write(szStr, iStrLen); //wirte netname to file

         //close file
         fp.Close();
      }//end of else
		

	}//end of !str_file.IsEmpty()



	delete file;
}


int CFilter_Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CDialogEx::OnCreate(lpCreateStruct) == -1)
      return -1;

   // TODO:  在此加入特別建立的程式碼
   bInit_Flag = false;
   SetTimer(TIMER_INIT, 200, NULL);

   return 0;
}


void CFilter_Dlg::OnClose()
{
   // TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
   KillTimer(TIMER_INIT);


   CDialogEx::OnClose();
}


void CFilter_Dlg::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值   
   CString str1, str_net_pathname;   
   CListBox *pList, *pList2;
   bool b_load_flag;
   int i, i_max;

   pList = (CListBox *)GetDlgItem(IDC_NET_LIST);
   pList2 = (CListBox *)GetDlgItem(IDC_SELECTED_NET_LIST);

   if (nIDEvent == TIMER_INIT && GetDlgItem(IDC_EDIT_NETLIST_FILE)!=NULL && !bInit_Flag){
      if(m_str_filename.GetLength() > 0){
         GetDlgItem(IDC_EDIT_NETLIST_FILE)->SetWindowTextA(m_str_filename);
         b_load_flag = m_netfilter.LoadNetlist_Filter(m_str_filename);         
         if ( b_load_flag == true){
            m_netfilter.SortNetlist_Filter();
            pList->ResetContent();
            pList2->ResetContent();

            i_max = m_netfilter.m_netpart_for_filter.i_total_nets;
            for(i=0 ; i<i_max ; i++)
               pList -> AddString (m_netfilter.m_netpart_for_filter.NetList[i]->str_netname);

      
         }
      
      }
      
      bInit_Flag = true;
      KillTimer(TIMER_INIT);
   }//end of TIMER_INIT


   CDialogEx::OnTimer(nIDEvent);
}
