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
File name      : wb4_agent.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_agent
Description    : 

Additional Comments:
 
 */
#ifndef WB4_AGENT_H_
#define WB4_AGENT_H_

#include <systemc>
#include <uvm>

#include "wb4_config.h"
#include "wb4_driver.h"
#include "wb4_sequencer.h"

//------------------------------------------------------------------
// Class: wb4_agent
//------------------------------------------------------------------
class wb4_agent : public uvm::uvm_agent {
public:
  //
  wb4_config*      cfg;
  wb4_driver*      drv;
  wb4_sequencer*   sqr;
  wb4_monitor*     mon;

  UVM_COMPONENT_UTILS(wb4_agent);


  // 
  wb4_agent(uvm::uvm_component_name name) : uvm::uvm_agent(name) {}

  // 
  ~wb4_agent(){
    if (sqr)
      delete sqr;

    if (drv) 
      delete drv;

    if (cfg) 
      delete cfg;

    if (mon) 
      delete mon;
  }

  virtual void build_phase(uvm::uvm_phase& phase){
    uvm::uvm_agent::build_phase(phase);

    if(get_is_active() == uvm::UVM_ACTIVE) {
      sqr = wb4_sequencer::type_id::create("sqr", this);
      drv = wb4_driver::type_id::create("drv", this);
    }
    mon = wb4_monitor::type_id::create("mon", this);
  }

  virtual void connect_phase(uvm::uvm_phase& phase){

    mon->bfm  = cfg->vif;

    if(get_is_active() == uvm::UVM_ACTIVE) { 
      drv->vif  = cfg->vif;
      drv->role = cfg->role;
      drv->seq_item_port.connect(sqr->seq_item_export); 
    }
      
  }

protected:
  int master_id;

};

#endif /* WB4_AGENT_H_ */

