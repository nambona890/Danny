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

#include <atomic>

#include <tray.hpp>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HMENU hmenu = NULL;
std::atomic_bool closewin = false;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DANNY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DANNY));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DANNY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DANNY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}




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
    constexpr size_t msglength = 11;
    size_t keyIndex = 0;
    WORD keys[11] = {
        'L','O','L',VK_SPACE,'R','E','T','A','R','D',VK_RETURN
    };
    DWORD delay[11] = {
        kd,kd,kd,kd,kd,kd,kd,kd,kd,kd,1000
    };
    while (!closewin)
    {
        bool found = false;
        std::vector<WindowTitle> titles;
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&titles));
        for (auto t : titles)
        {
            const size_t findsubstr = t.title.find(L"command prompt");
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
    closewin = true;
    Sleep(1000);
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