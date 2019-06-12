#include "stdafx.h"
#include "NetParse.h"
#include "NetFilter.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"


CNetFilter::CNetFilter(void)
{
   int i;

   for (i=0 ; i< MAX_NET_NUM ; i++){
      m_netpart_for_filter.NetList[i] = NULL;
      m_netpart_sel.NetList[i] = NULL;
      m_netpart_filtered.NetList[i] = NULL;
   }  
   m_netpart_for_filter.i_total_nets = 0;
   m_netpart_for_filter.i_total_parts = 0;

   m_netpart_sel.i_total_nets = 0;
   m_netpart_sel.i_total_parts = 0;

   m_netpart_filtered.i_total_nets = 0;
   m_netpart_filtered.i_total_parts = 0;
   
}
//--------------------------------------------------------------------------------------------------
CNetFilter::~CNetFilter(void)
{
   int i;

   for (i=0 ; i< m_netpart_for_filter.i_total_nets ; i++){
      if ( m_netpart_for_filter.NetList[i] != NULL){
         delete m_netpart_for_filter.NetList[i];
         m_netpart_for_filter.NetList[i] = NULL;
      }
   }//end of m_netpart_for_filter

   for (i=0 ; i< m_netpart_sel.i_total_nets ; i++){
      if ( m_netpart_sel.NetList[i] != NULL){
         delete m_netpart_sel.NetList[i];
         m_netpart_sel.NetList[i] = NULL;
      }
   }//end of m_netpart_sel

   for (i=0 ; i< m_netpart_filtered.i_total_nets ; i++){
      if ( m_netpart_filtered.NetList[i] != NULL){
         delete m_netpart_filtered.NetList[i];
         m_netpart_filtered.NetList[i] = NULL;
      }
   }//end of m_netpart_filtered

}

//--------------------------------------------------------------------------------------------------
bool CNetFilter::LoadNetlist_Filter(CString str_net_path_name)
{
   int i, k, i_max, k_max;
   //load netlist from .asc file to parent member variable.
   if ( LoadNetlist_OLD(str_net_path_name) == false)
      return false;

   //duplicates parts from paraent to "m_netpart_for_filter"
   i_max = g_old_net_part.i_total_parts;
   for (i=0 ; i<i_max ; i++){
      m_netpart_for_filter.PartsList[i].str_decal = g_old_net_part.PartsList[i].str_decal;
      m_netpart_for_filter.PartsList[i].str_location = g_old_net_part.PartsList[i].str_location;
   }
   m_netpart_for_filter.i_total_parts = i_max;

   //Release memory space, if it was assigned
   for (i=0 ; i< m_netpart_for_filter.i_total_nets ; i++){
      if ( m_netpart_for_filter.NetList[i] != NULL){
         delete m_netpart_for_filter.NetList[i];
         m_netpart_for_filter.NetList[i] = NULL;
      }
   }//end of m_netpart_for_filter
   m_netpart_for_filter.i_total_nets = 0;


   //duplicates netlist and nodes
   m_netpart_for_filter.i_total_nets = g_old_net_part.i_total_nets;
   i_max = g_old_net_part.i_total_nets;
   for(i=0 ; i<i_max ; i++){
      m_netpart_for_filter.NetList[i] = new Net;
      m_netpart_for_filter.NetList[i]->i_total_nodes = g_old_net_part.NetList[i]->i_total_nodes;
      m_netpart_for_filter.NetList[i]->str_netname = g_old_net_part.NetList[i]->str_netname;
      k_max = g_old_net_part.NetList[i]->i_total_nodes;

      //duplcation nodes
      for (k=0 ; k<k_max ; k++) 
         m_netpart_for_filter.NetList[i]->str_nodes[k] = g_old_net_part.NetList[i]->str_nodes[k];

      //duplcation parts in net
      k_max = g_old_net_part.NetList[i]-> i_parts_in_net;
      for( k=0 ; k<k_max ; k++)
         m_netpart_for_filter.NetList[i]->Parts_in_Net[k].str_location = g_old_net_part.NetList[i]->Parts_in_Net[k].str_location;
      m_netpart_for_filter.NetList[i]-> i_parts_in_net = k_max;
   }


   return true;
}

//--------------------------------------------------------------------------------------------------
void CNetFilter::SortNetlist_Filter(void)
{
   bool bExit_flag;
   Net *pNet_tmp;
   CString str1, str2;
   unsigned char uChar;
   int i_net_max, i_inx, i, i_str_len;   
   unsigned long *inx_table, ul_tmp;  

   i_net_max = m_netpart_for_filter.i_total_nets;
   inx_table = new unsigned long[i_net_max];
   for (i=0 ; i<i_net_max ; i++) inx_table[i] = 0;
   //Create index table for sorting
   for (i_inx=0 ; i_inx < i_net_max ; i_inx++){
      ul_tmp = 0;
      if (m_netpart_for_filter.NetList[i_inx]->str_netname.GetLength() >=4){
         for (i=0 ;i<4 ; i++){
            ul_tmp <<=8;
            uChar = (unsigned char) m_netpart_for_filter.NetList[i_inx]->str_netname.GetAt(i);
            ul_tmp |= (uChar - 0x20);
         }  
      }// end of "if (m_netpart_for_filter.NetList[i_inx]->str_netname.GetLength() >=4)"
      else{
         i_str_len=m_netpart_for_filter.NetList[i_inx]->str_netname.GetLength();
         for (i=0 ; i< i_str_len ; i++){
            ul_tmp <<=8;
            uChar = (unsigned char) m_netpart_for_filter.NetList[i_inx]->str_netname.GetAt(i);
            ul_tmp |= (uChar - 0x20);
         }
         ul_tmp <<= ((4 - i_str_len)*8);
      }
      inx_table [i_inx] = ul_tmp;
   } //for (i_inx=0 ; i_inx < i_net_max ; i_inx++){

   i_net_max = m_netpart_for_filter.i_total_nets;
   do{
      bExit_flag = true;
      for (i_inx=0 ; i_inx < (i_net_max-1) ; i_inx++){         
         if (inx_table[i_inx] > inx_table[i_inx + 1]){
            pNet_tmp = m_netpart_for_filter.NetList[i_inx];
            m_netpart_for_filter.NetList[i_inx] = m_netpart_for_filter.NetList[i_inx+1];
            m_netpart_for_filter.NetList[i_inx+1] = pNet_tmp;

            ul_tmp = inx_table[i_inx];
            inx_table[i_inx] = inx_table[i_inx+1];
            inx_table[i_inx+1] = ul_tmp;
            bExit_flag = false;
            
         }
      }//end of "for (i_inx=0 ; i_inx < (i_net_max-1) ; i++)"

   }while (!bExit_flag);

   delete inx_table;
  
}
//--------------------------------------------------------------------------------------------------
bool CNetFilter::FilterByKeyword (CString str_keyword)
{
   int i, i_find_inx, i_sel_net_inx;
   int i_sel_net_max;
   int i_part_inx1, i_part_max1, i_part_inx2;
   bool bMatchFlag;

   //Release assigned memory space, m_netpart_filtered
   for (i=0 ; i< m_netpart_filtered.i_total_nets ; i++){
      if ( m_netpart_filtered.NetList[i] != NULL){
         delete m_netpart_filtered.NetList[i];
         m_netpart_filtered.NetList[i] = NULL;
      }
   }//end of m_netpart_for_filter
   m_netpart_filtered.i_total_nets = 0;

   i_sel_net_max = m_netpart_sel.i_total_nets;
   i_find_inx = 0;
   for(i_sel_net_inx=0 ; i_sel_net_inx<i_sel_net_max ; i_sel_net_inx++){
      i_part_max1 = m_netpart_sel.NetList[i_sel_net_inx]->i_parts_in_net;
      bMatchFlag = false;
      i_part_inx2 = 0;
      for(i_part_inx1=0 ; i_part_inx1<i_part_max1 ; i_part_inx1++){
         if( (str_keyword.GetLength()>0) && (str_keyword != "*") ){ //keyword was not universal word and not null string
            if( m_netpart_sel.NetList[i_sel_net_inx]->Parts_in_Net[i_part_inx1].str_location.Find(str_keyword) != -1){// find matched part
               bMatchFlag = true;
               if(m_netpart_filtered.NetList[i_find_inx] == NULL)
                  m_netpart_filtered.NetList[i_find_inx] = new Net;
               m_netpart_filtered.NetList[i_find_inx]->Parts_in_Net[i_part_inx2++].str_location = m_netpart_sel.NetList[i_sel_net_inx]->Parts_in_Net[i_part_inx1].str_location;
            }//end of Find(str_keyword) != -1
         }//if (str_keyword.GetLength()>0) && (str_keyword != "*")
         else{  //bypass filter
            bMatchFlag = true;
            if(m_netpart_filtered.NetList[i_find_inx] == NULL)
               m_netpart_filtered.NetList[i_find_inx] = new Net;
            m_netpart_filtered.NetList[i_find_inx]->Parts_in_Net[i_part_inx2++].str_location = m_netpart_sel.NetList[i_sel_net_inx]->Parts_in_Net[i_part_inx1].str_location;
         }

      } //end of i_part_inx
      if(bMatchFlag){         
         m_netpart_filtered.NetList[i_find_inx]->i_parts_in_net = i_part_inx2;
         m_netpart_filtered.NetList[i_find_inx]->str_netname = m_netpart_sel.NetList[i_sel_net_inx]->str_netname;
         i_find_inx ++;
      }

   }//end of i_sel_net_inx
   m_netpart_filtered.i_total_nets = i_find_inx;
   

   if(m_netpart_filtered.i_total_nets > 0)
      return true;
   else 
      return false;

}
