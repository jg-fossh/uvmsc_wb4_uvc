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
File name      : wb4_monitor.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_monitor
Description    : 

Additional Comments:
 
 */
#ifndef WB4_MONITOR_H_
#define WB4_MONITOR_H_

#include <systemc>
#include <uvm>

#include "wb4_seq_item.h"
#include "wb4_bfm.h"
#include "wb4_if.h"

//
class wb4_monitor : public uvm::uvm_monitor {
public:

    sc_core::sc_event trig;
    // Attributes
    bool          is_async;
    wb4_bfm*      bfm;     
    // Analysis port for sending collected transactions
    uvm::uvm_analysis_port<wb4_seq_item> ap;


    UVM_COMPONENT_UTILS(wb4_monitor);

    
    wb4_monitor(const uvm::uvm_component_name& name) : uvm::uvm_monitor(name),
          ap("ap"),
          bfm(nullptr)
    {
        // Constructor implementation, if needed
    }

    virtual void run_phase(uvm::uvm_phase& phase){
        while (true) {
           wb4_seq_item* tr;
           //UVM_INFO(get_name()+"::"+__func__, "Monitor Called", uvm::UVM_FULL);
           tr = this->bfm->monitor();
           //UVM_INFO(get_name()+"::"+__func__, "Monitor Observed a Tr", uvm::UVM_FULL);
           this->ap.write(*static_cast<const wb4_seq_item*>(tr)); // Dereference the pointer
           //this->ap.write(static_cast<const wb4_seq_item*>(tr));
           this->trig.notify();
        }
    }
};

#endif // WB4_MONITOR_H_
