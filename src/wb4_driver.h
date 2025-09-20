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
File name      : wb4_driver.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_driver
Description    : 

Additional Comments:
 
*/
#ifndef WB4_DRIVER_H_
#define WB4_DRIVER_H_

#include <systemc>
#include <uvm>

#include "wb4_seq_item.h"
#include "wb4_bfm.h"
#include "wb4_if.h"

//
class wb4_driver : public uvm::uvm_driver<wb4_seq_item> {
public:

    sc_core::sc_event trig;
    // Attributes
    bool          is_async;
    wb4_role_e    role;
    //
    wb4_bfm*      vif;


    UVM_COMPONENT_UTILS(wb4_driver);

    
    wb4_driver(const uvm::uvm_component_name& name) : uvm::uvm_driver<wb4_seq_item>(name)
    {
        // Constructor implementation, if needed
    }

    virtual void run_phase(uvm::uvm_phase& phase){
        wb4_seq_item tr;
        while (true) {
            //

            // Receive a sequecen item from the sequencer
            this->seq_item_port->get_next_item(tr);
            //
            if(role == wb4_role_e::WB4_MASTER) { this->vif->master(tr); }
            //if(role == wb4_role_e::WB4_SLAVE)  { this->vif->slave(tr);  }
            // Receive the Response
            this->seq_item_port->item_done(tr);
            this->trig.notify();
        }
    }
};

#endif // WB4_DRIVER_H_
