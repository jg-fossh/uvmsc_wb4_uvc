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
File name      : wb4_seq_item.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_seq_item
Description    : 

Additional Comments:
 
 */
#ifndef WB4_SEQUENCER_H_
#define WB4_SEQUENCER_H_

#include <systemc>
#include <uvm>

class wb4_sequencer : public uvm::uvm_sequencer<wb4_seq_item> {
public:
    // Macro to register this sequencer with the UVM factory
    UVM_COMPONENT_UTILS(wb4_sequencer);

    // Constructor
    wb4_sequencer(uvm::uvm_component_name name) : uvm::uvm_sequencer<wb4_seq_item>(name){}
};

#endif // WB4_SEQUENCER_H_

