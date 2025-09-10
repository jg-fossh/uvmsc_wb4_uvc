 /* 
 
 Copyright (c) 2025, Jose R. Garcia (jg-fossh@protonmail.com)
 All rights reserved.

 
    Licensed under the Apache License, Version 2.0 (the
    "License"); you may not use this file except in
    compliance with the License.  You may obtain a copy of
    the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in
    writing, software distributed under the License is
    distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, either express or implied.  See
    the License for the specific language governing
    permissions and limitations under the License.

 --------------------------------------------------------------------------------
File name      : wb4_bfm.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_bfm
Description    : 

Additional Comments:
 
 */
#ifndef WB4_BFM_H_
#define WB4_BFM_H_

#include <systemc>
#include "wb4_pkg.h"
#include "wb4_seq_item.h"

using namespace sc_core;
//------------------------------------------------------------------
// Class: wb4_bfm_base
//------------------------------------------------------------------
class wb4_bfm : virtual public sc_interface {
public:
  //
  //virtual ~wb4_bfm() = default;
  virtual ~wb4_bfm() {};
  //
  virtual void sync_mon() = 0;
  virtual void sync_drv() = 0;
  //
  virtual wb4_seq_item* cb_monitor() = 0;
  virtual wb4_seq_item* monitor()    = 0;
  //virtual void start_monitor()         = 0;
  //virtual wb4_seq_item* get_monitored() = 0;
  //
  virtual void cb_master(wb4_seq_item* tr)    = 0;
  virtual void master(wb4_seq_item tr)        = 0;
  virtual void write_request(wb4_seq_item tr) = 0;
  virtual void read_request(wb4_seq_item tr)  = 0;


protected:
  int          id;
  wb4_role_e   role;
  wb4_seq_item* m_drv_tr;
  wb4_seq_item* m_mon_tr;
};

#endif /* WB4_BFM_H_ */
