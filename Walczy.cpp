#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <thread>


using  namespace std;
void title();

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
string  mdb = "GameAssembly.dll";


void walczyF509(uintptr_t playerB, vector<unsigned int>  offsets, float speed)
{
    HWND hwnd = FindWindowA(NULL, "Among Us");
    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);

    uintptr_t modulebase = GetModuleBaseAddress(procID, L"GameAssembly.dll");
    HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    uintptr_t dynamicPtrBaseAddr = modulebase + playerB;


    uintptr_t speedaddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, offsets);

    speed;

    WriteProcessMemory(hProcess, (LPVOID)speedaddr, &speed, sizeof(speed), NULL);


}

void walczy509(uintptr_t playerB, vector<unsigned int>  offsets,int speed)
{
    HWND hwnd = FindWindowA(NULL, "Among Us");
    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);

    uintptr_t modulebase = GetModuleBaseAddress(procID, L"GameAssembly.dll");
    HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    uintptr_t dynamicPtrBaseAddr = modulebase + playerB;


    uintptr_t speedaddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, offsets);

    speed ;

    WriteProcessMemory(hProcess, (LPVOID)speedaddr, &speed, sizeof(speed), NULL);


}

int main() {
    thread x(title);

    int nm;
    while (true) {
        int ax;
        std::cout << "1-Speed Hack \n2-Full Vision \n3-Change Role (You Can Be Imposter or Ghost  Or Crew Also You Will Be  Able To See  The Real Imposter in Crew)!\n4:Instant Skip\n\nEnter Number :  ";
        cin >> nm;
        switch (nm)
        {
        case 1:
            walczy509(0x00DA5B3C, { 0x5C, 0x2C, 0x14 }, 100);
            std::cout << "Speed Hack  Activated";
            Sleep(1000);
            system("cls");
            break;
        case 2:
            walczy509(0x00D0C7EC, { 0x134, 0xC, 0x24, 0x5C ,0x4,0x20 }, 1000);
            system("cls");
            break;
        case  3:
            std::cout << "1-CREW 2-IMPOSTER 3-GHOST:" << std::endl;// CREW = 0, IMP = 1; GHOST = 257
            cin >> ax;
            if (ax == 1) {
                walczy509(0xDAF3E8, { 0x5C, 0x20, 0x34, 0x28 }, 0);
                std::cout << "Crew Role Activated";
                Sleep(1000);
                system("cls");
            }
            else if ( ax == 2 ) {
                walczy509(0xDAF3E8, { 0x5C, 0x20, 0x34, 0x28 }, 1);
                std::cout << "Imposter Role Activated";
                Sleep(1000);
                system("cls");

            }
            else if (ax == 3) {
                walczy509(0xDAF3E8, { 0x5C, 0x20, 0x34, 0x28 }, 257);
                std::cout << "GHOST Role Activated";
                Sleep(1000);
                system("cls");
            }
            

            break;
        case  4:
            walczy509(0xDAF3E8, { 0x5C, 0x4, 0x48 }, 1);
            system("cls");
            break;
        default:
            std::cout << "Invalid  Number";
            break;
        }

       
    }
}



void title()
{
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 300, TRUE);
    while (TRUE)
    {
        SetConsoleTitleA("C");
        Sleep(100);
        SetConsoleTitleA("CR");
        Sleep(100);
        SetConsoleTitleA("CREA");
        Sleep(200);
        SetConsoleTitleA("CREAT");
        Sleep(100);
        SetConsoleTitleA("CREATED");
        Sleep(150);
        SetConsoleTitleA("CREATED B");
        Sleep(150);
        SetConsoleTitleA("CREATED BY");
        Sleep(150);
        SetConsoleTitleA("CREATED BY W");
        Sleep(150);
        SetConsoleTitleA("CREATED BY WA");
        Sleep(150);
        SetConsoleTitleA("CREATED BY WAL");
        Sleep(150);
        SetConsoleTitleA("CREATED BY WALC");
        Sleep(100);
        SetConsoleTitleA("CREATED BY WALCZ");
        Sleep(100);
        SetConsoleTitleA("CREATED BY WALCZY");
        Sleep(3000);
        SetConsoleTitleA("Among-Us Cheat");
        Sleep(4000);
    }
}


