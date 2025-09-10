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
File name      : wb4_inorder_scoreboard.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : wb4_inorder_scoreboard
Description    : In-order scoreboard for Wishbone transactions.

Additional Comments:
 
 */
#ifndef WB4_INORDER_SCOREBOARD_H_
#define WB4_INORDER_SCOREBOARD_H_

#include <queue>
#include <systemc>
#include <uvm>
#include "wb4_seq_item.h"

class wb4_inorder_scoreboard : public uvm::uvm_scoreboard {
public:
    sc_core::sc_event trig;
    bool error;
    uvm::uvm_analysis_export<wb4_seq_item> expected_ap;
    uvm::uvm_analysis_export<wb4_seq_item> observed_ap;

    class expected_subscriber : public uvm::uvm_subscriber<wb4_seq_item> {
    public:
        wb4_inorder_scoreboard* sb;
        expected_subscriber(const uvm::uvm_component_name& name, wb4_inorder_scoreboard* sb)
            : uvm_subscriber<wb4_seq_item>(name), sb(sb) {}
        
        void write(const wb4_seq_item& t) override {
            wb4_seq_item* t_clone = new wb4_seq_item();
            t_clone->do_copy(t);
            sb->write_expected(t_clone);
        }
    };

    class observed_subscriber : public uvm::uvm_subscriber<wb4_seq_item> {
    public:
        wb4_inorder_scoreboard* sb;
        observed_subscriber(const uvm::uvm_component_name& name, wb4_inorder_scoreboard* sb)
            : uvm_subscriber<wb4_seq_item>(name), sb(sb) {}
        
        void write(const wb4_seq_item& t) override {
            wb4_seq_item* t_clone = new wb4_seq_item();
            t_clone->do_copy(t);
            sb->write_observed(t_clone);
        }
    };

    expected_subscriber expected_listener;
    observed_subscriber observed_listener;

    UVM_COMPONENT_UTILS(wb4_inorder_scoreboard);

    wb4_inorder_scoreboard(const uvm::uvm_component_name& name)
        : uvm::uvm_scoreboard(name),
          expected_ap("expected_ap"),
          observed_ap("observed_ap"),
          expected_listener("expected_listener", this),
          observed_listener("observed_listener", this),
          error(false),
          matches(0),
          mismatches(0) {}

    virtual void build_phase(uvm::uvm_phase& phase) override {
        uvm_scoreboard::build_phase(phase);
    }

    virtual void connect_phase(uvm::uvm_phase& phase) override {
        uvm_scoreboard::connect_phase(phase);
        expected_ap.connect(expected_listener.analysis_export);
        observed_ap.connect(observed_listener.analysis_export);
    }

    void write_expected(wb4_seq_item* trans) {
        expected_fifo.push(trans);
    }

    void write_observed(wb4_seq_item* trans) {
        observed_fifo.push(trans);
    }

    virtual void check_phase(uvm::uvm_phase& phase) override {
        while (!expected_fifo.empty() && !observed_fifo.empty()) {
            wb4_seq_item* exp = expected_fifo.front();
            wb4_seq_item* obs = observed_fifo.front();
            expected_fifo.pop();
            observed_fifo.pop();

            if (exp->do_compare(*obs)) {
                ++matches;
                //std::ostringstream msg;
                //msg << "Transaction matched: " << matches;
                //UVM_INFO(get_name(), msg.str(), uvm::UVM_FULL);


            } else {
                ++mismatches;
                std::ostringstream msg;
                msg << "Transaction mismatched:\n";
                msg << "Expected: \n" << exp->sprint();
                msg << "Observed: \n" << obs->sprint();
                UVM_ERROR(get_name(), msg.str());
            }
            delete exp;
            delete obs;
        }

        if (!expected_fifo.empty() || !observed_fifo.empty()) {
            error = true;
            UVM_ERROR(get_name(), "** SCOREBOARD: Missing or extra transactions **");
        } else {
            error = false;
        }
    }

    virtual void report_phase(uvm::uvm_phase& phase) override {
        if (mismatches > 0) {
                error = true;
                std::ostringstream msg;
                msg << "\n*** WB4 SCOREBOARD RESULT ***\n";
                msg << "   [matches   : " <<  matches   << "]\n";
                msg << "   [mismatches: " << mismatches << "]";
            UVM_ERROR(get_name(), msg.str());
        } else if (error) {
                std::ostringstream msg;
                msg << "\n*** WB4 SCOREBOARD: Missing transactions ***\n";
                msg << "   [observed: " << observed_fifo.size() << "]\n";
                msg << "   [expected: " << expected_fifo.size() << "]";
            UVM_ERROR(get_name(), msg.str());
        } else {
            std::ostringstream msg;
            msg << "\n*** WB4 SCOREBOARD: All transactions matched! ***\n";
            msg << "   matches: " << matches;
            UVM_INFO(get_name(), msg.str(), uvm::UVM_NONE);
        }
    }

protected:
    std::queue<wb4_seq_item*> expected_fifo;
    std::queue<wb4_seq_item*> observed_fifo;
    uint64_t matches;
    uint64_t mismatches;
};

#endif // WB4_INORDER_SCOREBOARD_H_

