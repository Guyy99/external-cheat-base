#pragma once

#include <Windows.h>
#include <TlHelp32.h>

namespace memory
{
	inline HANDLE gHandle;

	inline uintptr_t pID;
	

	uintptr_t GetProcID(const wchar_t* process);
	uintptr_t GetModuleBaseAddress(uintptr_t procID, const wchar_t* module);

	template <typename T> T Read(uintptr_t address);
	template <typename T> bool Write(uintptr_t address, T value);


}

