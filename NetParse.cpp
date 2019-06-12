#include "stdafx.h"
#include "NetParse.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"


CNetParse::CNetParse(void)
{
   int i;

   for (i=0 ; i< MAX_NET_NUM ; i++){
      g_old_net_part.NetList[i] = NULL;      
      g_new_net_part.NetList[i] = NULL;
   }
   g_old_net_part.i_total_nets = 0;
   g_old_net_part.i_total_parts = 0;
   g_new_net_part.i_total_nets = 0;
   g_new_net_part.i_total_parts = 0;
  
}
//--------------------------------------------------------------------------------------------------
CNetParse::~CNetParse(void)
{
   int i;

   for (i=0 ; i< g_old_net_part.i_total_nets ; i++){
      if ( g_old_net_part.NetList[i] != NULL){
         delete g_old_net_part.NetList[i];
         g_old_net_part.NetList[i] = NULL;
      }
   }

   for (i=0 ; i< g_new_net_part.i_total_nets ; i++){
      if ( g_new_net_part.NetList[i] != NULL){
         delete g_new_net_part.NetList[i];
         g_new_net_part.NetList[i] = NULL;
      }
   }

   g_old_net_part.i_total_nets = 0;
   g_old_net_part.i_total_parts = 0;
   g_new_net_part.i_total_nets = 0;
   g_new_net_part.i_total_parts = 0;

}
//--------------------------------------------------------------------------------------------------
int CNetParse :: ReadOneLine (CFile *fp_in, CString *p_one_line)
{
	char cRD;
	bool bExit_mark_loop, bEnd_of_file;
	CString str_rd;
	str_rd.Empty();

	bExit_mark_loop = false;
   bEnd_of_file = false;
	do{	
      if ( fp_in->Read(&cRD, sizeof(char)) < sizeof(char)){
         bExit_mark_loop = true;      
         bEnd_of_file =  true;
      }

	   if ( (cRD == 0x0d || cRD == 0x0a) && !bExit_mark_loop){
		   fp_in->Read(&cRD, sizeof(char));

		   if (cRD == 0x0d || cRD == 0x0a)
		      bExit_mark_loop = true;

	   }//end of (cRD == 0x0d || cRD == 0x0a)	
      if( !bExit_mark_loop){
         str_rd = str_rd + cRD;
      }
	}while (!bExit_mark_loop);	
	
   if (bEnd_of_file)
	   return -1;
   else 
   {
      *p_one_line = str_rd;
      return 0;
   }
	
}
//--------------------------------------------------------------------------------------------------
bool CNetParse :: IsKeyword (CString str_keyword, CString str_dest)
{
   int i_find_index;
   
   i_find_index = str_dest.Find(str_keyword);
   if (i_find_index == -1)
      return false;
   else
      return true;
}
//--------------------------------------------------------------------------------------------------
void CNetParse :: ExtractPartFootprint (CString str_dest, CString *p_part, CString *p_decal)
{
   int i_space_inx, i_str_len;
   CString str_part, str_decal;
   i_str_len = str_dest.GetLength();

   i_space_inx = str_dest.Find(' ');
   str_part = str_dest.Left(i_space_inx);

   i_space_inx = str_dest.ReverseFind(' ');
   str_decal = str_dest.Right( (i_str_len - i_space_inx-1));

   *p_part = str_part;
   *p_decal = str_decal;
}
//--------------------------------------------------------------------------------------------------
void CNetParse :: ExtractNetname (CString str_dest, CString *p_netname)
{
   int i_space_inx, i_str_len;
   CString str_net;

   i_str_len = str_dest.GetLength();
   i_space_inx = str_dest.ReverseFind(' ');

   str_net = str_dest.Right( (i_str_len - i_space_inx - 1));

   *p_netname = str_net;  

}

//--------------------------------------------------------------------------------------------------
int CNetParse :: ExtractNode (CString str_dest, CString *p_NodeArray)
{
   int i_node_inx, i_str_len, i;
   CString str_node, str_ch;
   
   i_str_len = str_dest.GetLength();
   i_node_inx = 0;
   for( i=0 ; i<i_str_len ; i++){
      str_ch = str_dest.GetAt(i);
      if(str_ch == ' ' ){
         p_NodeArray[i_node_inx++] = str_node;
         str_node.Empty();
      }
      else{
         str_node = str_node + str_ch;
      }
   }//end of i_str_len loop   
   if( (i_str_len !=0) && (i == i_str_len))
      p_NodeArray[i_node_inx++] = str_node;

   return i_node_inx;
}
//--------------------------------------------------------------------------------------------------
bool CNetParse :: LoadNetlist_OLD (CString str_o_path_name)
{
	CString str_one_line, str_keyword;
   CString str_part, str_footprint;
   CString str_netname;
   CString str_node_array[128];
   bool bExit = false;
   bool bIsPartSection = false, bIsNetSection = false, b_SignalSection = false;
   bool b_CutNet = false, b_NodeSection = false, b_END = false;
   bool b_pass_thisline = false; 

   int i_nodes, ii, i, k;
   int i_parts_inx, i_net_inx;

	if (fp_OLD_file.Open(str_o_path_name ,CFile::modeRead | CFile::typeBinary,NULL) == 0)
      return false;

	fp_OLD_file.SeekToBegin();   

   //Clear structure variable (NetPartGroup)
   for (i=0 ; i< g_old_net_part.i_total_nets ; i++){
      if ( g_old_net_part.NetList[i] != NULL){
         delete g_old_net_part.NetList[i];
         g_old_net_part.NetList[i] = NULL;
      }
   }
   g_old_net_part.i_total_nets = 0;

   i_parts_inx = 0;
   i_net_inx = 0;
      
   do{
      if ( ReadOneLine(&fp_OLD_file, &str_one_line) == -1)
         bExit = true;

      if( !bExit){

         //bypass this line, if too short words of one line.
         if (str_one_line.GetLength() < 3 )            
            b_pass_thisline = true;
         
         str_keyword = "*PART*";
         if (IsKeyword (str_keyword, str_one_line) ){
            bIsPartSection = true;
            b_pass_thisline = true;
         } //end of *PART*

         str_keyword = "*NET*";
         if (IsKeyword (str_keyword, str_one_line) ){
            bIsPartSection = false;
            bIsNetSection = true;
            b_pass_thisline = true;
            g_old_net_part.i_total_parts = i_parts_inx;
         } //end of *NET*

         str_keyword = "*SIGNAL*";
         if (IsKeyword (str_keyword, str_one_line) ){
            b_SignalSection = true;
            b_CutNet = true;     
            b_NodeSection = false;  
            i_nodes = 0;
         } //end of *SIGNAL*  

         if( b_SignalSection && !b_CutNet)
            b_NodeSection = true;

         str_keyword = "*END*";
         if (IsKeyword (str_keyword, str_one_line) ){
            bIsNetSection = false;         
            g_old_net_part.i_total_nets = i_net_inx;
         } //end of *SIGNAL*

         if(b_pass_thisline)
            b_pass_thisline = false;
         else{
            if(bIsPartSection){//start extract parts and footprint from part section of netlist file
               ExtractPartFootprint(str_one_line, &str_part, &str_footprint);
               g_old_net_part.PartsList[i_parts_inx].str_location = str_part;
               g_old_net_part.PartsList[i_parts_inx].str_decal = str_footprint;
               i_parts_inx ++;
            }

            if(bIsNetSection && b_SignalSection && b_CutNet) { //cut net name from *SIGNALS* and toggle extract component node flag.
               ExtractNetname(str_one_line, &str_netname);

               //allocate memory space for Net
               g_old_net_part.NetList[i_net_inx] = new Net;
               g_old_net_part.NetList[i_net_inx]->i_total_nodes = 0;
               g_old_net_part.NetList[i_net_inx]->str_netname = str_netname;
               i_net_inx ++;              

               b_CutNet = false;
            }

            if(bIsNetSection && b_SignalSection && b_NodeSection){ //extract component node
               ii = ExtractNode(str_one_line, str_node_array);

               k = 0;
               for(i=i_nodes ; i< (ii+i_nodes) ;i++)
                  g_old_net_part.NetList[i_net_inx - 1]->str_nodes[i] = str_node_array[k++];

               i_nodes += ii;
               g_old_net_part.NetList[i_net_inx - 1]->i_total_nodes = i_nodes;
            }

         }// end of else 'b_pass_thisline'
         
      }//bExit
      
   }while (	!bExit );

   //get parts of net.
   ii = g_old_net_part.i_total_nets;
   for(i = 0 ; i< ii ; i++){
      GetParts_in_Net (g_old_net_part.NetList[i]);
   }

	fp_OLD_file.Close();
   return true;
}

//--------------------------------------------------------------------------------------------------
bool CNetParse :: LoadNetlist_NEW (CString str_n_path_name)
{
	CString str_one_line, str_keyword;
   CString str_part, str_footprint;
   CString str_netname;
   CString str_node_array[128];
   bool bExit = false;
   bool bIsPartSection = false, bIsNetSection = false, b_SignalSection = false;
   bool b_CutNet = false, b_NodeSection = false, b_END = false;
   bool b_pass_thisline = false; 

   int i_nodes, ii, i, k;
   int i_parts_inx, i_net_inx;

	if (fp_NEW_file.Open(str_n_path_name ,CFile::modeRead | CFile::typeBinary,NULL) == 0)
      return false;

	fp_NEW_file.SeekToBegin();   

   //Clear structure variable (NetPartGroup)
   for (i=0 ; i< g_new_net_part.i_total_nets ; i++){
      if ( g_new_net_part.NetList[i] != NULL){
         delete g_new_net_part.NetList[i];
         g_new_net_part.NetList[i] = NULL;
      }
   }
   g_new_net_part.i_total_nets = 0;

   i_parts_inx = 0;
   i_net_inx = 0;
      
   do{
      if ( ReadOneLine(&fp_NEW_file, &str_one_line) == -1)
         bExit = true;

      if( !bExit){

         //bypass this line, if too short words of one line.
         if (str_one_line.GetLength() < 3 )            
            b_pass_thisline = true;
         
         str_keyword = "*PART*";
         if (IsKeyword (str_keyword, str_one_line) ){
            bIsPartSection = true;
            b_pass_thisline = true;
         } //end of *PART*

         str_keyword = "*NET*";
         if (IsKeyword (str_keyword, str_one_line) ){
            bIsPartSection = false;
            bIsNetSection = true;
            b_pass_thisline = true;
            g_new_net_part.i_total_parts = i_parts_inx;
         } //end of *NET*

         str_keyword = "*SIGNAL*";
         if (IsKeyword (str_keyword, str_one_line) ){
            b_SignalSection = true;
            b_CutNet = true;     
            b_NodeSection = false;  
            i_nodes = 0;
         } //end of *SIGNAL*  

         if( b_SignalSection && !b_CutNet)
            b_NodeSection = true;

         str_keyword = "*END*";
         if (IsKeyword (str_keyword, str_one_line) ){
            bIsNetSection = false;     
            g_new_net_part.i_total_nets = i_net_inx;
         } //end of *SIGNAL*

         if(b_pass_thisline)
            b_pass_thisline = false;
         else{
            if(bIsPartSection){//start extract parts and footprint from part section of netlist file
               ExtractPartFootprint(str_one_line, &str_part, &str_footprint);
               g_new_net_part.PartsList[i_parts_inx].str_location = str_part;
               g_new_net_part.PartsList[i_parts_inx].str_decal = str_footprint;
               i_parts_inx ++;
            }

            if(bIsNetSection && b_SignalSection && b_CutNet) { //cut net name from *SIGNALS* and toggle extract component node flag.
               ExtractNetname(str_one_line, &str_netname);

               if( str_netname == "DDR_S_A13")
                  int jjj=0;

               //allocate memory space for Net
               g_new_net_part.NetList[i_net_inx] = new Net;
               g_new_net_part.NetList[i_net_inx]->i_total_nodes = 0;
               g_new_net_part.NetList[i_net_inx]->str_netname = str_netname;
               i_net_inx ++;              

               b_CutNet = false;
            }

            if(bIsNetSection && b_SignalSection && b_NodeSection){ //extract component node
               ii = ExtractNode(str_one_line, str_node_array);

               k = 0;
               for(i=i_nodes ; i< (ii+i_nodes) ;i++)
                  g_new_net_part.NetList[i_net_inx - 1]->str_nodes[i] = str_node_array[k++];

               i_nodes += ii;
               g_new_net_part.NetList[i_net_inx - 1]->i_total_nodes = i_nodes;
            }

         }// end of else 'b_pass_thisline'
         
      }//bExit
      
   }while (	!bExit );

   //get parts of net.
   ii = g_new_net_part.i_total_nets;
   for(i = 0 ; i< ii ; i++){
      GetParts_in_Net (g_new_net_part.NetList[i]);
   }

	fp_NEW_file.Close();
   return true;
}
//--------------------------------------------------------------------------------------------------
int CNetParse :: PartHaveMatch_OldToNew(int i_old_partlist_inx, unsigned int *i_error_code)
{
   bool b_find_flag;
   int i_inx_in_new, i_finded_inx_in_new, i_total_parts_in_new;
   CString str_old_location, str_old_decal;

   b_find_flag = false;
   *i_error_code = CODE_NO_MATCH;
   str_old_location = g_old_net_part.PartsList[i_old_partlist_inx].str_location;
   str_old_decal = g_old_net_part.PartsList[i_old_partlist_inx].str_decal;

   i_total_parts_in_new = g_new_net_part.i_total_parts;
   for(i_inx_in_new=0 ; i_inx_in_new<i_total_parts_in_new && !b_find_flag; i_inx_in_new ++){
      if( str_old_location == g_new_net_part.PartsList[i_inx_in_new].str_location ){
         b_find_flag = true; //find matched parts
         i_finded_inx_in_new = i_inx_in_new;
         if( str_old_decal == g_new_net_part.PartsList[i_inx_in_new].str_decal)
            *i_error_code = CODE_NORMAL;
         else
            *i_error_code = CODE_DECAL;         
      } //end of location compare, "str_old_location == g_new_net_part.PartList[i_inx_in_new].str_location"

   }//end of i_inx_in_new

   if(b_find_flag){
      return i_finded_inx_in_new;
   }   
   else
      return -1;
}

//--------------------------------------------------------------------------------------------------
int CNetParse :: PartHaveMatch_NewToOld(int i_new_partlist_inx, unsigned int *i_error_code)
{
   bool b_find_flag;
   int i_inx_in_old, i_finded_inx_in_old, i_total_parts_in_old;
   CString str_new_location, str_new_decal;

   b_find_flag = false;
   *i_error_code = CODE_NO_MATCH;
   str_new_location = g_new_net_part.PartsList[i_new_partlist_inx].str_location;
   str_new_decal = g_new_net_part.PartsList[i_new_partlist_inx].str_decal;

   i_total_parts_in_old = g_old_net_part.i_total_parts;
   for(i_inx_in_old=0 ; i_inx_in_old<i_total_parts_in_old && !b_find_flag; i_inx_in_old ++){
      if( str_new_location == g_old_net_part.PartsList[i_inx_in_old].str_location ){
         b_find_flag = true; //find matched parts
         i_finded_inx_in_old = i_inx_in_old;
         if( str_new_decal == g_old_net_part.PartsList[i_inx_in_old].str_decal)
            *i_error_code = CODE_NORMAL;
         else
            *i_error_code = CODE_DECAL;         
      } //end of location compare, "str_old_location == g_new_net_part.PartList[i_inx_in_new].str_location"

   }//end of i_inx_in_new

   if(b_find_flag){
      return i_finded_inx_in_old;
   }   
   else
      return -1;
}
//--------------------------------------------------------------------------------------------------
int CNetParse :: NetHaveMatch_OldToNew(int i_old_netlist_inx, unsigned int *i_error_code)
{
   bool b_find_flag;
   int i_inx_in_new, i_finded_inx_in_new, i_total_nets_in_new;
   CString str_old_netname;

   b_find_flag = false;
   *i_error_code = CODE_NO_MATCH;
   str_old_netname = g_old_net_part.NetList[i_old_netlist_inx]->str_netname;
   
   i_total_nets_in_new = g_new_net_part.i_total_nets;
   for(i_inx_in_new=0 ; i_inx_in_new<i_total_nets_in_new && !b_find_flag; i_inx_in_new ++){
      if( str_old_netname == g_new_net_part.NetList[i_inx_in_new]->str_netname ){
         b_find_flag = true; //find matched parts
         i_finded_inx_in_new = i_inx_in_new;
         *i_error_code = CODE_NORMAL;
                 
      } //end of location compare, "str_old_location == g_new_net_part.PartList[i_inx_in_new].str_location"

   }//end of i_inx_in_new

   if(b_find_flag){
      return i_finded_inx_in_new;
   }   
   else
      return -1;
}
//--------------------------------------------------------------------------------------------------
int CNetParse :: NetHaveMatch_NewToOld(int i_new_netlist_inx, unsigned int *i_error_code)
{
   bool b_find_flag;
   int i_inx_in_old, i_finded_inx_in_old, i_total_nets_in_old;
   CString str_new_netname;

   b_find_flag = false;
   *i_error_code = CODE_NO_MATCH;
   str_new_netname = g_new_net_part.NetList[i_new_netlist_inx]->str_netname;   

   i_total_nets_in_old = g_old_net_part.i_total_nets;
   for(i_inx_in_old=0 ; i_inx_in_old<i_total_nets_in_old && !b_find_flag; i_inx_in_old ++){
      if( str_new_netname == g_old_net_part.NetList[i_inx_in_old]->str_netname ){
         b_find_flag = true; //find matched parts
         i_finded_inx_in_old = i_inx_in_old;
         *i_error_code = CODE_NORMAL;
                 
      } //end of location compare, "str_old_location == g_new_net_part.PartList[i_inx_in_new].str_location"
   }//end of i_inx_in_new

   if(b_find_flag){
      return i_finded_inx_in_old;
   }   
   else
      return -1;
}

//--------------------------------------------------------------------------------------------------
int CNetParse :: NodeHaveMatch_OldToNew (int i_old_node_inx, int i_old_net_inx, int i_new_net_inx, unsigned int *i_error_code)
{
   bool b_find_flag;
   int i_inx_in_new, i_finded_inx_in_new, i_total_nodes_in_new;
   CString str_old_node;
   Net *p_net_in_new_netlist;

   b_find_flag = false;
   *i_error_code = CODE_NO_MATCH;
   str_old_node = g_old_net_part.NetList[i_old_net_inx]->str_nodes[i_old_node_inx];

   i_total_nodes_in_new = g_new_net_part.NetList[i_new_net_inx]->i_total_nodes;
   p_net_in_new_netlist = g_new_net_part.NetList[i_new_net_inx];
   for(i_inx_in_new=0 ; i_inx_in_new<i_total_nodes_in_new && !b_find_flag; i_inx_in_new ++){
      if( str_old_node == p_net_in_new_netlist->str_nodes[i_inx_in_new] ){
         b_find_flag = true; //find matched parts
         i_finded_inx_in_new = i_inx_in_new;
         *i_error_code = CODE_NORMAL;
                 
      } //end of location compare, "str_old_location == g_new_net_part.PartList[i_inx_in_new].str_location"
   }//end of i_inx_in_new

   if(b_find_flag){
      return i_finded_inx_in_new;
   }   
   else
      return -1;
}
//--------------------------------------------------------------------------------------------------
int CNetParse :: NodeHaveMatch_NewToOld (int i_new_node_inx, int i_new_net_inx, int i_old_net_inx, unsigned int *i_error_code)
{
   bool b_find_flag;
   int i_inx_in_old, i_finded_inx_in_old, i_total_nodes_in_old;
   CString str_new_node;
   Net *p_net_in_old_netlist;

   b_find_flag = false;
   *i_error_code = CODE_NO_MATCH;
   str_new_node = g_new_net_part.NetList[i_new_net_inx]->str_nodes[i_new_node_inx];

   i_total_nodes_in_old = g_old_net_part.NetList[i_old_net_inx]->i_total_nodes;
   p_net_in_old_netlist = g_old_net_part.NetList[i_old_net_inx];
   for(i_inx_in_old=0 ; i_inx_in_old<i_total_nodes_in_old && !b_find_flag; i_inx_in_old ++){
      if( str_new_node == p_net_in_old_netlist->str_nodes[i_inx_in_old] ){
         b_find_flag = true; //find matched parts
         i_finded_inx_in_old = i_inx_in_old;
         *i_error_code = CODE_NORMAL;
                 
      } //end of location compare, "str_old_location == g_new_net_part.PartList[i_inx_in_new].str_location"
   }//end of i_inx_in_new

   if(b_find_flag){
      return i_finded_inx_in_old;
   }   
   else
      return -1;
}
//--------------------------------------------------------------------------------------------------
void CNetParse :: GetParts_in_Net (Net *p_Net)
{
   int i_inx, i_node_max, i_part_max;
   int i,j;
   bool b_match_flag;
   CString str_part1;

   p_Net -> i_parts_in_net = 0;
   i_node_max = p_Net -> i_total_nodes;
   i_part_max = p_Net -> i_parts_in_net;

   for(i_inx=0 ; i_inx<i_node_max ; i_inx++){
      i = p_Net -> str_nodes[i_inx].Find(".");
      str_part1 = p_Net -> str_nodes[i_inx].Left(i);

      b_match_flag = false;
      for(j=0 ; (j<i_part_max && !b_match_flag) ; j++){
         if ( p_Net -> Parts_in_Net[j].str_location == str_part1)
            b_match_flag = true;         
      }//end of i_part_max     
      if ( !b_match_flag)
         p_Net -> Parts_in_Net[i_part_max++].str_location = str_part1;      
      
   }//end i_inx
   p_Net -> i_parts_in_net = i_part_max;
}