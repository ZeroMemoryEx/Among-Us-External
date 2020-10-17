
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>


uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), NULL);
        addr += offsets[i];
    }
    return addr;
}


int main() {
    HWND hwnd = FindWindowA(NULL, "Among Us");
    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);

    uintptr_t modulebase = GetModuleBaseAddress(procID, L"GameAssembly.dll");
    HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

    uintptr_t dynamicPtrBaseAddr = modulebase + 0x00DA5B3C;

    std::vector<unsigned int> speedoffsets = { 0x5C, 0x2C,0x14};

    uintptr_t speedaddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, speedoffsets);

    float speed = 6;

    WriteProcessMemory(hProcess, (LPVOID)speedaddr, &speed, sizeof(speed), NULL);

    return 0;


}



