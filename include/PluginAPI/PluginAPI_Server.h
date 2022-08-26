/* Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.

   Licensed under the Apache License, Version 2.0 (the "License"); you may
   not use this file except in compliance with the License. You may obtain
   a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
   WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
   License for the specific language governing permissions and limitations
   under the License.

   Author: Mingchuan Wu and Yancheng Li
   Create: 2022-08-18
   Description:
    This file contains the declaration of the PluginAPI_Server class.
*/

#ifndef PLUGIN_FRAMEWORK_API_H
#define PLUGIN_FRAMEWORK_API_H

#include "BasicPluginAPI.h"
#include "PluginServer.h"

namespace Plugin_API {
/* The PluginAPI class is the client implementation of plugin api. */
using namespace Plugin_IR;

using std::vector;
using std::string;
class PluginAPI_Server : public BasicPluginAPI {
public:
    PluginAPI_Server () = default;
    ~PluginAPI_Server () = default;

    vector<Operation> SelectOperation(Opcode op, string attribute) override;
    vector<Operation> GetAllFunc(string attribute) override;
    Decl SelectDeclByID(uintptr_t id) override;
    TypeCode GetTypeCodeFromString(string type);
private:
    vector<Operation> GetOperationResult(const string& funName, const string& params);
    Decl GetDeclResult(const string& funName, const string& params);
    Type GetTypeResult(const string& funName, const string& params);
    void WaitClientResult(const string& funName, const string& params);
}; // class PluginAPI_Server
} // namespace Plugin_API

#endif // PLUGIN_FRAMEWORK_API_H
