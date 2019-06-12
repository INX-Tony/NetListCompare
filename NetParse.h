#pragma once
//#include "stdafx.h"

#define MAX_PARTS_NUM 5000
#define MAX_NET_NUM 5000
#define MAX_NODE_NUM 5000
#define MAX_PARTS_IN_NET_NUM 1000
#define CODE_NO_MATCH 0x00FF
#define CODE_NORMAL   0x0000  //no error occurred
#define CODE_DECAL    0x0001  //Component decal not matched
#define CODE_NODE     0x0002  //node on the net not matched

//define Part structure
   //Part composite of component location and decal.
   struct Part{
      CString str_location, str_decal;
   };

   //define structure 
   //Net composite of one netname and nodes.
   struct Net{
      CString str_netname;
      CString str_nodes[MAX_NODE_NUM];
      Part Parts_in_Net[MAX_PARTS_IN_NET_NUM];      
      int i_total_nodes, i_parts_in_net;
   };

   struct NetPartGroup{
      Part PartsList[MAX_PARTS_NUM];

      Net *NetList[MAX_NET_NUM];

      int i_total_nets, i_total_parts;
   };

   struct NetCompareOption{
      bool bPart_decal_change, bPart_removed, bPart_added;
      bool bNet_removed, bNet_added;
      bool bNode_change, bNode_removed, bNode_added;
   };


class CNetParse
{
protected:
   /*
   //define Part structure
   //Part composite of component location and decal.
   struct Part{
      CString str_location, str_decal;
   };

   //define structure 
   //Net composite of one netname and nodes.
   struct Net{
      CString str_netname;
      CString str_nodes[MAX_NODE_NUM];
      Part Parts_in_Net[MAX_PARTS_IN_NET_NUM];      
      int i_total_nodes, i_parts_in_net;
   };

   struct NetPartGroup{
      Part PartsList[MAX_PARTS_NUM];

      Net *NetList[MAX_NET_NUM];

      int i_total_nets, i_total_parts;
   };
   */


   //define protected variable
   CFile fp_OLD_file, fp_NEW_file;
   
 
   //define protected member function
   int ReadOneLine (CFile *fp_in, CString *p_one_line); //read one line that end of Ox0D/0x0A from file.
   bool IsKeyword (CString str_keyword, CString str_dest); //match keyword string in str_dest string.
   void ExtractPartFootprint (CString str_dest, CString *p_part, CString *p_decal); //extract part and footprint from str_dest string.
   void ExtractNetname (CString str_dest, CString *p_netname);
   int ExtractNode (CString str_dest, CString *p_NodeArray); //return number of node in this line
   void GetParts_in_Net(Net *p_Net); //get parts from indicated net

public:
   NetPartGroup g_old_net_part, g_new_net_part;

   bool LoadNetlist_OLD (CString str_o_path_name);
   bool LoadNetlist_NEW (CString str_n_path_name);
   int PartHaveMatch_OldToNew(int i_old_partlist_inx, unsigned int *i_error_code); //return -1, if no match in NEW NetPartGroup.
                                                                                  //else return non -1 value & error code, return value is matached index in new NetPartGroup 
                                                                                  //, and error_code == ERROR_DECAL means parts matached but decal have changed.
                                                                      
   int PartHaveMatch_NewToOld(int i_new_partlist_inx, unsigned int *i_error_code); //return -1, if no match in OLD NetPartGroup.
                                                                                  //else return non -1 value & error code, return value is matached index in new NetPartGroup 
                                                                                  //, and error_code == ERROR_DECAL means parts matached but decal have changed.

   int NetHaveMatch_OldToNew(int i_old_netlist_inx, unsigned int *i_error_code); //return -1, if no match in NEW NetPartGroup.
                                                                                 //else return non -1 value & error code, return value is matached index in new NetPartGroup 
                                                                                 //, and error_code == ERROR_NODE means parts matached but decal have changed.
                                                                      
   int NetHaveMatch_NewToOld(int i_new_netlist_inx, unsigned int *i_error_code); //return -1, if no match in OLD NetPartGroup.
                                                                               //else return non -1 value & error code, return value is matached index in new NetPartGroup 
                                                                               //, and error_code == ERROR_NODE means parts matached but decal have changed.

   int NodeHaveMatch_OldToNew (int i_old_node_inx, int i_old_net_inx, int i_new_net_inx, unsigned int *i_error_code);

   int NodeHaveMatch_NewToOld (int i_new_node_inx, int i_new_net_inx, int i_old_net_inx, unsigned int *i_error_code);



    CNetParse(void);
    ~CNetParse(void);

};
