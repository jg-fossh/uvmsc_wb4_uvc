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
#ifndef WB4_SEQ_H_
#define WB4_SEQ_H_

#include <systemc>
#include <uvm>
//#include <crave2uvm.h>

//#include <algorithm>
#include <vector>

class wb4_seq_item : public uvm::uvm_sequence_item {
public:
    //
    wb4_operation_e          operation;
    wb4_cycle_termination_e  termination;
    wb4_data_attribute_e     granularity;
    //
    uint32_t    delay;
    uint32_t    rsp_clks;
    //
    //vector<bool> sel;
    //
    bool        lock;
    bool        rty;
    uint32_t    err;
    //
    uint64_t    adr;
    uint64_t    dat_i;
    uint64_t    dat_o;
    uint64_t    tgc;
    uint64_t    tga;
    uint64_t    tgd_i;
    uint64_t    tgd_o;

    //
    //wb4_cycle_termination_e termination;

    // UVM object utilities macro
    UVM_OBJECT_UTILS(wb4_seq_item);

    // Constructor
    wb4_seq_item(const std::string& name = "wb4_seq_item") : uvm::uvm_sequence_item(name) {
        // operation = wb4_operation_e::READ;
    }

    // Print function
    virtual void do_print(const uvm::uvm_printer& printer) const {
        //
        printer.print_string("operation", operation == wb4_operation_e::READ  ? "READ"  : 
                                          operation == wb4_operation_e::WRITE ? "WRITE" : "RESET");
        printer.print_string("termination", termination == wb4_cycle_termination_e::FULFILLED ? "FULFILLED" : "ABORTED");
        printer.print_string("granularity", granularity == wb4_data_attribute_e::BIT    ? "BIT" : 
                                            granularity == wb4_data_attribute_e::NIBBLE ? "NIBBLE " : 
                                            granularity == wb4_data_attribute_e::BYTE   ? "BYTE   " : 
                                            granularity == wb4_data_attribute_e::WORD   ? "WORD   " : 
                                            granularity == wb4_data_attribute_e::DWORD  ? "DWORD  " : 
                                            granularity == wb4_data_attribute_e::QWORD  ? "QWORD  " : 
                                            granularity == wb4_data_attribute_e::DQWORD ? "DQWORD " : "BOOL");
        //
        printer.print_string("lock", lock  ? "TRUE" : "FALSE");
        printer.print_string("rty",  rty   ? "TRUE" : "FALSE");
        //
        printer.print_field_int("err",   err,   uvm::UVM_HEX);
        printer.print_field_int("adr",   adr,   uvm::UVM_HEX);
        printer.print_field_int("dat_i", dat_i, uvm::UVM_HEX);
        printer.print_field_int("dat_o", dat_o, uvm::UVM_HEX);
        printer.print_field_int("tgc",   tgc,   uvm::UVM_HEX);
        printer.print_field_int("tga",   tgc,   uvm::UVM_HEX);
        printer.print_field_int("tgd_i", tgd_i, uvm::UVM_HEX);
        printer.print_field_int("tgd_o", tgd_o, uvm::UVM_HEX);

        //printer.print_string("termination", termination == wb4_cycle_termination_e::READ ? "READ" : "WRITE");
    }

    // Pack function
    virtual void do_pack(uvm::uvm_packer& p) const {
        p << (int)operation << (int)lock << (int)rty << err << adr << dat_i << dat_o << tgc << tgc << tgd_i << tgd_o;
    }

    // Unpack function
    virtual void do_unpack(uvm::uvm_packer& p) {
        int operation_enum;
        int lock_;
        int rty_;
        //
        p >> operation_enum;
        p >> lock_;
        p >> rty_;

        p >> operation_enum >> lock_ >> rty_ >> err >> adr >> dat_i >> dat_o >> tgc >> tgc >> tgd_i >> tgd_o;


        operation = (wb4_operation_e)operation_enum;
        lock      = (bool)lock_;
        rty       = (bool)rty_;
    }

    // Copy function
    virtual void do_copy(const uvm::uvm_object& rhs) {
        const wb4_seq_item* drhs = dynamic_cast<const wb4_seq_item*>(&rhs);
        if (!drhs) {
            UVM_FATAL("DO_COPY", "Object not of type wb4_seq_item");
        }
        //
        operation   = drhs->operation;
        termination = drhs->termination;
        granularity = drhs->granularity;
        delay       = drhs->delay   ;
        rsp_clks    = drhs->rsp_clks;
        //sel         = drhs->sel     ;
        lock        = drhs->lock    ;
        rty         = drhs->rty     ;
        err         = drhs->err     ;
        adr         = drhs->adr     ;
        dat_i       = drhs->dat_i   ;
        dat_o       = drhs->dat_o   ;
        tgc         = drhs->tgc     ;
        tga         = drhs->tga     ;
        tgd_i       = drhs->tgd_i   ;
        tgd_o       = drhs->tgd_o   ;
    }

    // Compare function
    virtual bool do_compare(const uvm::uvm_object& rhs, const uvm::uvm_comparer* comparer = NULL) const {
        const wb4_seq_item* drhs = dynamic_cast<const wb4_seq_item*>(&rhs);
        if (!drhs) {
            UVM_FATAL("DO_COMPARE", "Object not of type wb4_seq_item");
        }
        
        if(operation == wb4_operation_e::READ && termination == wb4_cycle_termination_e::ABORTED){
            // If the Read transaction was aborted there is no point in looking at the data
            // as it will most likely not match.
            return( operation   == drhs->operation   &&
                    termination == drhs->termination &&
                    //sel         == drhs->sel         &&
                    //err         == drhs->err         &&
                    adr         == drhs->adr         &&
                    //dat_i       == drhs->dat_i       &&
                    dat_o       == drhs->dat_o       &&
                    tgc         == drhs->tgc         &&
                    tga         == drhs->tga         &&
                    //tgd_i       == drhs->tgd_i       &&
                    tgd_o       == drhs->tgd_o          );
        }
        else {
            return( operation   == drhs->operation   &&
                    termination == drhs->termination &&
                    //sel         == drhs->sel         &&
                    err         == drhs->err         &&
                    adr         == drhs->adr         &&
                    dat_i       == drhs->dat_i       &&
                    dat_o       == drhs->dat_o       &&
                    tgc         == drhs->tgc         &&
                    tga         == drhs->tga         &&
                    tgd_i       == drhs->tgd_i       &&
                    tgd_o       == drhs->tgd_o          );
        }
    }

    // Convert to string function
    std::string convert2string() const {
        std::ostringstream str;
        //
        str << "  operation: " << (operation == wb4_operation_e::READ ? "READ" : "WRITE");
        str << "err: ",   err  ;
        str << "adr: ",   adr  ;
        str << "dat_i: ", dat_i;
        str << "dat_o: ", dat_o;
        str << "tgc: ",   tgc  ;
        str << "tga: ",   tgc  ;
        str << "tgd_i: ", tgd_i;
        str << "tgd_o: ", tgd_o;
       
        return str.str();
    }
};

#endif // WB4_SEQ_H_

