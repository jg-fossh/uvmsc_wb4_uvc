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
File name      : wb4_seq_lib.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_base_seq; wb4_wr_request_seq; wb4_rd_request_seq
Description    : 

Additional Comments:
 
 */
#ifndef WB4_SEQ_LIB_H_
#define WB4_SEQ_LIB_H_

#include <systemc>
#include <uvm>

#include "wb4_seq_item.h"

//
class wb4_base_seq : public uvm::uvm_sequence<wb4_seq_item> {
public:

   wb4_seq_item* req{nullptr};
   wb4_seq_item* rsp{nullptr};

   // UVM object utilities macro
   UVM_OBJECT_UTILS(wb4_base_seq);

    // Constructor
    wb4_base_seq(const std::string& name = "wb4_base_seq") : uvm::uvm_sequence<wb4_seq_item>(name) {
        // 
      req = wb4_seq_item::type_id::create();
      rsp = wb4_seq_item::type_id::create();
    }

  ~wb4_base_seq(){
	  delete(req);
	  delete(rsp);
  }

  // 
  virtual void body()
  {
    /* TODO constraints using macro
    UVM_DO_WITH(req,
      { req.addr == start_addr;
        req.read_write == READ;
        req.size == 1;
        req.error_pos == 1000;
        req.transmit_delay == transmit_del; } )
      */

    start_item(req);
    // TBD
    finish_item(req);
    get_response(rsp);

    //
    std::ostringstream msg;
    //msg << get_sequence_path();
    msg << req->convert2string();
    UVM_INFO(get_name()+"::"+__func__, msg.str(), uvm::UVM_FULL);

  }

};

//
class wb4_wr_request_seq : public wb4_base_seq {
public:

   // UVM object utilities macro
   UVM_OBJECT_UTILS(wb4_wr_request_seq);

    // Constructor
    wb4_wr_request_seq(const std::string& name = "wb4_wr_request_seq") : wb4_base_seq(name) {
        // 
      req = wb4_seq_item::type_id::create();
      rsp = wb4_seq_item::type_id::create();

    //
    req->delay     = 0;
    req->rsp_clks  = 1;
    //
    //req->sel  = {true;
    req->err  = 0;
    //
    req->adr   = 0xCAFE;
    req->dat_o = 0xCAFE;
    req->tgc   = 0;
    req->tga   = 0;
    req->tgd_o = 0;
    }

  ~wb4_wr_request_seq(){
	delete(req);
	delete(rsp);
  }


  virtual void body()
  {
    /* TODO constraints using macro
    UVM_DO_WITH(req,
      { req.addr == start_addr;
        req.read_write == READ;
        req.size == 1;
        req.error_pos == 1000;
        req.transmit_delay == transmit_del; } )
    */
    //
    req->operation = wb4_operation_e::WRITE;

    //
    req->lock  = false;
    req->rty   = NULL;


    //
    start_item(req);
    // TBD
    finish_item(req);
    get_response(rsp);

    //
    std::ostringstream msg;
    msg << get_sequence_path();
    UVM_INFO(get_type_name(), msg.str(), uvm::UVM_FULL);

  }
}; //wb4_wr_request_seq


//
class wb4_rd_request_seq : public wb4_base_seq {
public:

   // UVM object utilities macro
   UVM_OBJECT_UTILS(wb4_rd_request_seq);

    // Constructor
    wb4_rd_request_seq(const std::string& name = "wb4_rd_request_seq") : wb4_base_seq(name) {
        // 
      req = wb4_seq_item::type_id::create();
      rsp = wb4_seq_item::type_id::create();

    //
    req->delay     = 0;
    req->rsp_clks  = 1;
    //
    //req->sel = {true};
    req->err  = 0;
    //
    req->adr   = 0;
    req->dat_o = 0;
    req->tgc   = 0;
    req->tga   = 0;
    req->tgd_o = 0;
    }

  ~wb4_rd_request_seq(){
	delete(req);
	delete(rsp);
  }


  virtual void body()
  {
    /* TODO constraints using macro
    UVM_DO_WITH(req,
      { req.addr == start_addr;
        req.read_write == READ;
        req.size == 1;
        req.error_pos == 1000;
        req.transmit_delay == transmit_del; } )
    */
    //
    req->operation = wb4_operation_e::READ;

    req->lock  = false;
    req->rty   = NULL;


    //
    start_item(req);
    // TBD
    finish_item(req);
    get_response(rsp);

    //
    std::ostringstream msg;
    msg << get_sequence_path();
    UVM_INFO(get_type_name(), msg.str(), uvm::UVM_FULL);

  }
}; //wb4_rd_request_seq

#endif // WB4_SEQ_LIB_H_
