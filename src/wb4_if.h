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
File name      : wb4_if.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_if
Description    : 

Additional Comments:
 
 */
#ifndef WB4_IF_H_
#define WB4_IF_H_

#include <systemc>
#include <uvm>

#include "wb4_pkg.h"
#include "wb4_seq_item.h"
#include "wb4_bfm.h"
template<
    typename T_DAT_I = uint32_t,
    typename T_DAT_O = uint32_t,
    typename T_ADR   = uint32_t,
    typename T_TGC   = bool,
    typename T_TGA   = bool,
    typename T_TGD_I = bool,
    typename T_TGD_O = bool
> class wb4_if : public sc_core::sc_module, public wb4_bfm {
public:
    SC_HAS_PROCESS(wb4_if);
    // Constructor
    wb4_if(sc_core::sc_module_name name)
        : sc_module(name),
          clk_i("clk_i"),
          rst_i("rst_i"),
          cyc("cyc"),
          stb("stb"),
          ack("ack"),
          adr("adr"),
          dat_i("dat_i"),
          dat_o("dat_o"),
          we("we"),
          sel("sel"),
          stall("stall"),
          err("err"),
          lock("lock"),
          rty("rty"),
          tgc("tgc"),
          tga("tga"),
          tgd_i("tgd_i"),
          tgd_o("tgd_o"),
          has_checks(false),
          has_coverage(false),
          is_async(false),
          driving_edge(wb4_clocking_edge_e::RISING),
          sampling_edge(wb4_clocking_edge_e::RISING),
          s_sample_edge(wb4_clocking_edge_e::RISING),
          sample_wait(sc_core::SC_ZERO_TIME) { // Initialize sample_wait
        //
        //SC_THREAD(sync);
        //SC_THREAD(monitor);
        //
       // sensitive << cyc.default_event()
       //           << stb.default_event()
       //           << ack.default_event()
       //           << adr.default_event()
       //           << dat_i.default_event()
       //           << dat_o.default_event()
       //           << we.default_event()
       //           << sel.default_event()
       //           << stall.default_event()
       //           << err.default_event()
       //           << lock.default_event()
       //           << rty.default_event()
       //           << tgc.default_event()
       //           << tga.default_event()
       //           << tgd_i.default_event()
       //           << tgd_o.default_event();
        dont_initialize();
        m_drv_tr = wb4_seq_item::type_id::create();
        m_mon_tr = wb4_seq_item::type_id::create();
    }
    // Clock input signal
    sc_core::sc_in_clk clk_i;
    // Reset input signal
    sc_core::sc_in<bool> rst_i;

    // Wishbone B4 Signals
    sc_core::sc_signal<bool>     cyc;
    sc_core::sc_signal<bool>     stb;
    sc_core::sc_signal<bool>     ack;
    sc_core::sc_signal<T_ADR>    adr;
    sc_core::sc_signal<T_DAT_I>  dat_i;
    sc_core::sc_signal<T_DAT_O>  dat_o;
    sc_core::sc_signal<bool>     we;
    sc_core::sc_signal<uint32_t> sel;
    sc_core::sc_signal<bool>     stall;
    sc_core::sc_signal<uint32_t> err;
    sc_core::sc_signal<bool>     lock;
    sc_core::sc_signal<bool>     rty;
    sc_core::sc_signal<T_TGC>    tgc;
    sc_core::sc_signal<T_TGA>    tga;
    sc_core::sc_signal<T_TGD_I>  tgd_i;
    sc_core::sc_signal<T_TGD_O>  tgd_o;
    //
    sc_core::sc_event monitor_start;
    // Control flags
    bool                  has_checks;
    bool                  has_coverage;
    bool                  is_async;
    wb4_clocking_edge_e   driving_edge;
    wb4_clocking_edge_e   sampling_edge;
    wb4_clocking_edge_e   s_drive_edge;
    wb4_clocking_edge_e   s_sample_edge;
    sc_core::sc_time      sample_wait; // Member variable for sample wait time

    // Synchronization method
    void sync_mon() override {
      if (is_async) { sc_core::wait(sample_wait); }
      else {
        switch (s_sample_edge) {
          case wb4_clocking_edge_e::RISING:
            sc_core::wait(clk_i.posedge_event());
            if(sampling_edge == wb4_clocking_edge_e::BOTH) { s_sample_edge = wb4_clocking_edge_e::FALLING; }
            break;
          case wb4_clocking_edge_e::FALLING:
            sc_core::wait(clk_i.negedge_event());
            if(sampling_edge == wb4_clocking_edge_e::BOTH) { s_sample_edge = wb4_clocking_edge_e::RISING; }
            break;
          case wb4_clocking_edge_e::BOTH:
            sc_core::wait(clk_i.posedge_event());
            if(sampling_edge == wb4_clocking_edge_e::BOTH) { s_sample_edge = wb4_clocking_edge_e::FALLING; }
            break;
        }
      }
    }

    // Synchronization method
    void sync_drv() override {
      if (is_async) { sc_core::wait(sample_wait); }
      else {
        switch (s_drive_edge) {
          case wb4_clocking_edge_e::RISING:
            sc_core::wait(clk_i.posedge_event());
            if(driving_edge == wb4_clocking_edge_e::BOTH) { s_drive_edge = wb4_clocking_edge_e::FALLING; }
            break;
          case wb4_clocking_edge_e::FALLING:
            sc_core::wait(clk_i.negedge_event());
            if(driving_edge == wb4_clocking_edge_e::BOTH) { s_drive_edge = wb4_clocking_edge_e::RISING; }
            break;
          case wb4_clocking_edge_e::BOTH:
            sc_core::wait(clk_i.posedge_event());
            if(driving_edge == wb4_clocking_edge_e::BOTH) { s_drive_edge = wb4_clocking_edge_e::FALLING; }
            break;
        }
      }
    }

    // Positive Edge Clocking Block
    wb4_seq_item* cb_monitor() override {
      wb4_seq_item* mon_tr = wb4_seq_item::type_id::create();
      //
      mon_tr->adr   = this->adr  ;
      mon_tr->dat_o = this->dat_o;
      mon_tr->dat_i = this->dat_i;
      mon_tr->lock  = this->lock ;
      mon_tr->tgc   = this->tgc  ;
      mon_tr->tga   = this->tga  ;
      mon_tr->tgd_o = this->tgd_o;
      mon_tr->tgd_i = this->tgd_i;

      return mon_tr;
    }

    wb4_seq_item* monitor() override {
      wb4_seq_item* mon_tr = wb4_seq_item::type_id::create();
      while(rst_i) { sync_mon(); }
          
      while(cyc == false) { sync_mon(); }
      
      while(stb == false && cyc == true) { sync_mon(); }
      mon_tr = cb_monitor();
      if(this->we) { mon_tr->operation = wb4_operation_e::WRITE; }
      else { mon_tr->operation = wb4_operation_e::READ; }

      while((ack == false && cyc == true)) { sync_mon(); }
      
      if(this->ack == true) { mon_tr->termination = wb4_cycle_termination_e::FULFILLED; }
      else { mon_tr->termination = wb4_cycle_termination_e::ABORTED; }
      
      sync_mon();
      //UVM_INFO("WB4_IF", "Monitor saw cyc", uvm::UVM_NONE);

      return mon_tr;

    }

    // Positive Edge Clocking Block
    void cb_master(wb4_seq_item* tr) override {
      //
      this->adr    = static_cast<T_ADR>(tr->adr);
      this->dat_o  = tr->dat_o ;
      this->lock   = tr->lock  ;
      this->tgc    = tr->tgc   ;
      this->tga    = tr->tga   ;
      this->tgd_o  = tr->tgd_o ;
      //
    }

    void master(wb4_seq_item tr) override {
      switch(tr.operation) {
        case(wb4_operation_e::WRITE):
          write_request(tr);
          break;
        case(wb4_operation_e::READ):
          read_request(tr);
          break;
      }
    }

    //
    void write_request(wb4_seq_item tr) override {
      //
      int cycles = 0;
      //
      if(tr.delay > 0) { sc_core::wait(tr.delay, sc_core::SC_NS); }
      //
      sync_drv();
      cb_master(&tr);
      this->cyc = true;
      this->we  = true;
      this->stb = true;
      //
      //rd_response.termination = wb4_cycle_termination_e::ABORTED;
      //
      while(cycles <= tr.rsp_clks) {
        cycles++;
        sync_drv();
        //
        if(this->stall == false) {
          this->stb = false;
        }

        if(this->ack == true){
          //rd_response.termination = wb4_cycle_termination_e::FULFILLED;
          break;
        }
      }
      // Release the bus
      this->cyc = false;
      this->we  = false;
      this->stb = false;
    }

    //
    void read_request(wb4_seq_item tr) override {
      // Local variables
      //m_drv_tr.copy(tr);
      int     cycles = 0;
      //
      if(tr.delay > 0) { sc_core::wait(tr.delay, sc_core::SC_NS); }
      //
      sync_drv();
      cb_master(&tr);
      this->cyc = true;
      this->we  = false;
      this->stb = true;
      //
      //rd_response.termination = wb4_cycle_termination_e::ABORTED;
      while(cycles <= tr.rsp_clks) {
        cycles++;
        sync_drv();
        if(this->stall == false) {
          this->stb = false;
          //m_drv_tr.stb_= false;
        }

        if(this->ack == true){
         // rd_response.termination = wb4_cycle_termination_e::FULFILLED;
          break;
        }
      }
      // Release the bus
      this->cyc = false;
      this->we  = false;
      this->stb = false;
    }
};
#endif // WB4_IF_H_
