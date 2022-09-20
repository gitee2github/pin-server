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
    This file contains the declaration of the Plugin_Log class.
*/

#ifndef PLUGIN_LOG_H
#define PLUGIN_LOG_H

namespace PinServer {
#define LOG_FILE_SIZE   (10 * 1024 * 1024)

enum LogPriority : uint8_t {
    PRIORITY_ERROR = 0,
    PRIORITY_WARN,
    PRIORITY_INFO,
    PRIORITY_DEBUG
};
void LogPrint(LogPriority priority, const char *tag, const char *fmt, ...);
void CloseLog(void);
bool SetLogPriority(LogPriority priority);

#define LOGE(...) LogPrint(PRIORITY_ERROR, "ERROR:", __VA_ARGS__)
#define LOGW(...) LogPrint(PRIORITY_WARN, "WARN:", __VA_ARGS__)
#define LOGI(...) LogPrint(PRIORITY_INFO, "", __VA_ARGS__)
#define LOGD(...) LogPrint(PRIORITY_DEBUG, "DEBUG:", __VA_ARGS__)
} // namespace PinServer

#endif
