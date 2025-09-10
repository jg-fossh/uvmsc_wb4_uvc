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
File name      : wb4_pkg.h
Author         : Jose R Garcia (jg-fossh@protonmail.com)
Project Name   : UVMSC Wishbone B4 Verification Component
Class(es) Name : 
Description    : Contains constants and type definitions used by the component

Additional Comments:
 
 */
#ifndef WB4_PKG_H_
#define WB4_PKG_H_

// Enum definition for sampling edge
typedef enum {
    WB4_MASTER,
    WB4_SLAVE
} wb4_role_e;

// Enum definition for sampling edge
typedef enum {
    RISING,
    FALLING,
    BOTH
} wb4_clocking_edge_e;


// Enum(S) definition
typedef enum {
  BOOL   = 0,
  BIT    = 1,
  NIBBLE = 4,
  BYTE   = 8,
  WORD   = 16,
  DWORD  = 32,
  QWORD  = 64,
  DQWORD = 128
} wb4_data_attribute_e;

// Enum definition
typedef enum {
  READ,
  WRITE,
  RESET
} wb4_operation_e;

typedef enum {
  FULFILLED,
  ABORTED
} wb4_cycle_termination_e;


#endif /* WB4_PKG_H_ */
