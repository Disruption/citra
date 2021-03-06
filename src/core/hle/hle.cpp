// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.  

#include <vector>

#include "core/mem_map.h"
#include "core/hle/hle.h"
#include "core/hle/svc.h"
#include "core/hle/service/service.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HLE {

static std::vector<ModuleDef> g_module_db;

const FunctionDef* GetSVCInfo(u32 opcode) {
    u32 func_num = opcode & 0xFFFFFF; // 8 bits
    if (func_num > 0xFF) {
        ERROR_LOG(HLE,"Unknown SVC: 0x%02X", func_num); 
        return NULL;
    }
    return &g_module_db[0].func_table[func_num];
}

void CallSVC(u32 opcode) {
    const FunctionDef *info = GetSVCInfo(opcode);

    if (!info) {
        return;
    }
    if (info->func) {
        info->func();
    } else {
        ERROR_LOG(HLE, "Unimplemented SVC function %s(..)", info->name.c_str());
    }
}

void EatCycles(u32 cycles) {
    // TODO: ImplementMe
}

void ReSchedule(const char *reason) {
#ifdef _DEBUG
    _dbg_assert_msg_(HLE, reason != 0 && strlen(reason) < 256, "ReSchedule: Invalid or too long reason.");
#endif
    // TODO: ImplementMe
}

void RegisterModule(std::string name, int num_functions, const FunctionDef* func_table) {
    ModuleDef module = {name, num_functions, func_table};
    g_module_db.push_back(module);
}

void RegisterAllModules() {
    SVC::Register();
}

void Init() {
    Service::Init();
    
    RegisterAllModules();

    NOTICE_LOG(HLE, "initialized OK");
}

void Shutdown() {
    Service::Shutdown();

    g_module_db.clear();

    NOTICE_LOG(HLE, "shutdown OK");
}

} // namespace
