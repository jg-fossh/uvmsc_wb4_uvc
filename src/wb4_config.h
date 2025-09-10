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
File name      : wb4_config.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_config
Description    : 

Additional Comments:
 
 */
#ifndef WB4_CONFIG_H_
#define WB4_CONFIG_H_

#include <systemc>
#include <uvm>

#include "wb4_if.h"
#include "wb4_bfm.h"


// --------------------------------------------------------------------------------------------------
// Class : WB4 Config
//
// --------------------------------------------------------------------------------------------------
class wb4_config : public uvm::uvm_object {
public:

   // Features
   bool                  has_checks        = false;
   bool                  has_coverage      = false;
   // Attributes
   bool                  is_async          = false;
   wb4_role_e            role              = wb4_role_e::WB4_MASTER;
   //
   wb4_clocking_edge_e   driving_edge      = wb4_clocking_edge_e::RISING;
   wb4_clocking_edge_e   sampling_edge     = wb4_clocking_edge_e::FALLING;
   wb4_data_attribute_e  data_unit         = wb4_data_attribute_e::BYTE;
   wb4_data_attribute_e  data_granularity  = wb4_data_attribute_e::BIT;
   wb4_data_attribute_e  data_operand_size = wb4_data_attribute_e::BYTE;

   // Pre-conditions
   wb4_clocking_edge_e   s_sample_edge = wb4_clocking_edge_e::FALLING;
   // Attributes
   
  
   // THIS agent's Virtual Interface
   wb4_bfm* vif;

   UVM_OBJECT_UTILS(wb4_config);

   // Constructor
   wb4_config(const std::string & name = "wb4_config") {}

   // Print function
   virtual void do_print(const uvm::uvm_printer& printer) const {
      // 
      printer.print_string("has_checks",   (has_checks    ? "true" : "false"));
      printer.print_string("has_coverage", (has_coverage  ? "true" : "false"));
      printer.print_string("is_async",     (is_async      ? "true" : "false"));
      //
      printer.print_field_int("driving_edge",      driving_edge     , 32, uvm::UVM_NORADIX, ".", "wb4_clocking_edge_e");
      printer.print_field_int("sampling_edge",     sampling_edge    , 32, uvm::UVM_NORADIX, ".", "wb4_clocking_edge_e");
      printer.print_field_int("data_unit",         data_unit        , 32, uvm::UVM_NORADIX, ".", "wb4_data_unit_e"    );
      printer.print_field_int("data_granularity",  data_granularity , 32, uvm::UVM_NORADIX, ".", "wb4_granularity_e"  );
      printer.print_field_int("data_operand_size", data_operand_size, 32, uvm::UVM_NORADIX, ".", "wb4_operand_size_e" );
   }
};

#endif /* WB4_CONFIG_H_ */

