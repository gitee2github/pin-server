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

*/
// ===----------------------------------------------------------------------===//
//
// This is the header file for the Plugin dialect.
//
// ===----------------------------------------------------------------------===//

#ifndef PLUGIN_DIALECT_H
#define PLUGIN_DIALECT_H

#include "mlir/IR/Dialect.h"

/// Include the patterns defined in the Declarative Rewrite framework.
#include "Dialect/PluginOpsDialect.h.inc"

#endif // PLUGIN_DIALECT_H
