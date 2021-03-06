// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.


#ifndef _MEMORYUTIL_H
#define _MEMORYUTIL_H

#ifndef _WIN32
#include <sys/mman.h>
#endif
#include <string>

void* AllocateExecutableMemory(size_t size, bool low = true);
void* AllocateMemoryPages(size_t size);
void FreeMemoryPages(void* ptr, size_t size);
void* AllocateAlignedMemory(size_t size,size_t alignment);
void FreeAlignedMemory(void* ptr);
void WriteProtectMemory(void* ptr, size_t size, bool executable = false);
void UnWriteProtectMemory(void* ptr, size_t size, bool allowExecute = false);
std::string MemUsage();

inline int GetPageSize() { return 4096; }

#endif
