#pragma once
//#include "stdafx.h"

#include "NetParse.h"

class CNetFilter : public CNetParse
{
protected:

   

public:
  
   NetPartGroup m_netpart_for_filter;
   NetPartGroup m_netpart_sel, m_netpart_filtered;   

   int m_i_nets_sel;

   bool LoadNetlist_Filter (CString str_net_path_name);
   void SortNetlist_Filter (void);
   bool FilterByKeyword (CString str_keyword);

    CNetFilter(void);
    ~CNetFilter(void);

};
