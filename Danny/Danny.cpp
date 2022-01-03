// Danny.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Danny.h"
#include <mmsystem.h>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <cwctype>
#include <shellapi.h>
#include <ctime>
#include <utilapiset.h>

#include <atomic>

#include <tray.hpp>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
std::atomic_bool closewin = false;

// Forward declarations of functions included in this code module:





BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);


struct WindowTitle
{
    std::wstring title;
};

void TourettesWindows()
{
    struct WindowSound
    {
        int snd;
        std::vector<std::wstring> subStr;
        bool playing = false;
    };
    std::vector<WindowSound> penises = {
        {IDR_WTF,{L"task manager"}},
        {IDR_WTF,{L"registry editor"}},
        {IDR_BADNEWSBROWN,{L"bad news brown",L"allen coage"}},
        {IDR_HACKSAW,{L"jim duggan",L"james duggan"}},
        {IDR_MRPERFECT,{L"mr perfect",L"mr. perfect",L"curt hennig"}},
        {IDR_MACHOMAN,{L"randy savage",L"macho man",L"randall poffo"}},
        {IDR_DATASTARTREK,{L"brent spiner"}},
        {IDR_RICKMORANIS,{L"rick moranis"}},
        {IDR_RANDYTRAVIS,{L"randy travis"}},
        {IDR_COLGATE,{L"colgate"}},
        {IDR_DAIRYQUEEN,{L"dairy queen"}},
        {IDR_DUSTYRHODES,{L"dusty rhodes",L"virgil runnels"}},
        {IDR_KOOLAID,{L"koolaid",L"kool-aid",L"kool aid"}},
        {IDR_MCDONALDS,{L"mcdonalds",L"mcdonald's",L"ronald mcdonald"}},
        {IDR_WENDYS,{L"wendys",L"wendy's"}},
    };
    while (!closewin)
    {
        std::vector<WindowTitle> titles;
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&titles));
        for (auto& p : penises)
        {
            bool found = false;
            for (auto t : titles)
            {
                if (!found)
                {
                    for (auto ss : p.subStr)
                    {
                        const size_t findsubstr = t.title.find(ss);
                        if (findsubstr != std::string::npos)
                        {
                            found = true;
                        }
                    }
                }
            }
            if (found)
            {
                if (!p.playing)
                {
                    p.playing = true;
                    PlaySound(MAKEINTRESOURCE(p.snd), hInst, SND_RESOURCE | SND_ASYNC);
                }
            }
            else
            {
                p.playing = false;
            }
        }
        Sleep(100);
    }
}

void TourettesRandom()
{
    std::vector<int> randomcurses = {
        IDR_DICK,IDR_FUCK1,IDR_OHSHIT,IDR_PISS1,IDR_PISS2
    };
    Sleep(1000 * (10 + (rand() % 50)));
    while (!closewin)
    {
        const int dick = randomcurses[rand() % randomcurses.size()];
        PlaySound(MAKEINTRESOURCE(dick), hInst, SND_RESOURCE | SND_ASYNC);
        Sleep(1000 * (10 + (rand() % 50)));
    }
}

void AfterEight()
{
    bool playing = false;
    while (!closewin)
    {
        auto now = std::chrono::system_clock::now();

        time_t tnow = std::chrono::system_clock::to_time_t(now);
        std::tm tm;
        localtime_s(&tm,&tnow);
        
        if (tm.tm_hour == 8 && tm.tm_min == 0)
        {
            if (!playing)
            {
                playing = true;
                PlaySound(MAKEINTRESOURCE(IDR_AFTER8), hInst, SND_RESOURCE | SND_ASYNC);
            }
        }
        else
        {
            playing = false;
        }
        Sleep(100);
    }
}

void TourettesCMD()
{
    constexpr DWORD kd = 100;
    constexpr size_t msglength = 12;
    size_t keyIndex = 0;
    WORD keys[msglength] = {
        'L','O','L',VK_SPACE,'D','U','M','B','A','S','S',VK_RETURN
    };
    DWORD delay[msglength] = {
        kd,kd,kd,kd,kd,kd,kd,kd,kd,kd,kd,1000
    };
    while (!closewin)
    {
        bool found = false;
        std::vector<WindowTitle> titles;
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&titles));
        for (auto t : titles)
        {
            size_t findsubstr = t.title.find(L"command prompt");
            if (findsubstr != std::string::npos)
            {
                found = true;
            }
            findsubstr = t.title.find(L"powershell");
            if (findsubstr != std::string::npos)
            {
                found = true;
            }

        }
        if (!found)
        {
            keyIndex = 0;
            Sleep(100);
        }
        else
        {
            KEYBDINPUT keyinput;
            keyinput.wVk = keys[keyIndex];
            keyinput.wScan = 0;
            keyinput.dwFlags = 0;
            keyinput.time = 0;
            keyinput.dwExtraInfo = 0;
            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki = keyinput;
            SendInput(1, &input, sizeof(input));
            PlaySound(MAKEINTRESOURCE(IDR_BEEP), hInst, SND_RESOURCE | SND_ASYNC);
            //Beep(440, 50);
            Sleep(delay[keyIndex++]);
            keyIndex %= msglength;
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int iCmdShow)
{
    std::thread t1(TourettesWindows);
    std::thread t2(TourettesRandom);
    std::thread t3(AfterEight);
    std::thread t4(TourettesCMD);
    LPWSTR cline = GetCommandLineW();
    int argc;
    LPWSTR* argv = CommandLineToArgvW(cline, &argc);

    HICON icon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DANNY));

    Tray::Tray tray("Danny.exe", icon);
    tray.addEntry(Tray::Button("Exit", [&] {tray.exit(); }));

    PlaySound(MAKEINTRESOURCE(IDR_SHIT), hInst, SND_RESOURCE | SND_ASYNC);
    MessageBox(NULL, L"Too late, you're already fucked!", L"Uh oh", MB_OK);
    tray.run();
    PostQuitMessage(0);
    //closewin = true;
    return 0;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    std::vector<WindowTitle>* titles = reinterpret_cast<std::vector<WindowTitle>*>(lParam);
    WindowTitle wtitle;
    WCHAR titlewchar[320];
    GetWindowText(hwnd, titlewchar, sizeof(titlewchar)/2);
    wtitle.title = titlewchar;
    std::transform(wtitle.title.begin(), wtitle.title.end(), wtitle.title.begin(), std::towlower);
    titles->push_back(wtitle);
    return TRUE;
}