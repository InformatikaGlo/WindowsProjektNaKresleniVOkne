// WindowsProjektNaKresleniVOkne.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProjektNaKresleniVOkne.h"
#include <sstream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
    LoadStringW(hInstance, IDC_WINDOWSPROJEKTNAKRESLENIVOKNE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJEKTNAKRESLENIVOKNE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJEKTNAKRESLENIVOKNE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJEKTNAKRESLENIVOKNE);
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

   ShowWindow(hWnd, nCmdShow);
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
            HDC hDC = BeginPaint(hWnd, &ps); //Vytvoříme takzvaný handle device context, reprezentuje plochu pro kreslení
            HPEN hOldPen, hNewPen; //Deklarujeme dvě proměnné pro staré a nové pero   
            HBRUSH hBrush, hOldBrush; //Deklarujeme dvě proměnné pro starý a nový štětec

            hNewPen = CreatePen(PS_SOLID, 3, RGB(0, 180, 180));   // Vytvoříme pero kreslící nepřerušenou čáru tloušťkou 3 a barvou danou složkami červená (R), zelená (G), modrá (B), maximálně 255,255,255
            hOldPen = (HPEN)SelectObject(hDC, hNewPen); //Přidělíme nové pero ploše pro kreslení a uložíme jej do proměnné hOldPen

            // Vypíšeme text do okna:
            std::wstringstream wss; //Vytvoříme si speciální proud
            wss << "Text k výpisu do okna"; //Pošleme do něj text
            TextOut(hDC, 50, 50, wss.str().c_str(), wss.str().size()); //Tento text (4.paramter) vypíšeme na souřadnice [50, 50] a rezervujeme pro jeho výpis potřebný počet znaků (5. parametr)

            //Nakreslíme obdelník
            MoveToEx(hDC, 100, 200, NULL); //Přesuneme kurzor na souřadnice [100, 200]            
            LineTo(hDC, 300, 200); //Nakreslíme čáru, která začíná na aktuálních souřadnicích (ty jsou aktuálně [100, 200]) a končí na souřadnicích [300, 200]
            LineTo(hDC, 300, 300); //Nakreslíme čáru, která začíná na aktuálních souřadnicích (ty jsou aktuálně [300, 200]) a končí na souřadnicích [300, 300]
            LineTo(hDC, 100, 300); //Nakreslíme čáru, která začíná na aktuálních souřadnicích a končí na souřadnicích [100, 300]
            LineTo(hDC, 100, 200); //Nakreslíme čáru, která začíná na aktuálních souřadnicích a končí na souřadnicích [100, 200]


            Ellipse(hDC, 100, 200, 300, 300); //Do obdelníku nakreslíme vepsanou elipsu zadanou souřadnicemi levého horního rohu a pravého spodního rohu.
            
            hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 0, 255)); //Vytvoříme štětec kreslící mřížkovaným vzorem modrou barvou
            hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); //Přidělíme nový štětec ploše pro kreslení
                        
            int ret = ExtFloodFill(hDC, 250, 250, RGB(0, 180, 180), FLOODFILLBORDER); //Vyplníme plochu ohraničenou barvou RGB(0, 180, 180) vzorem nakresleným vytvořeným štětcem, vyplňovat začneme na souřadnicích [250,250].

            hBrush = CreateSolidBrush(RGB(100, 100, 255)); //Vytvoříme štětec kreslící bez vzoru jen zadanou barvou
            hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); //Přidělíme nový štětec ploše pro kreslení

            ret = ExtFloodFill(hDC, 105, 205, RGB(0, 180, 180), FLOODFILLBORDER); //Vyplníme plochu ohraničenou barvou RGB(0, 180, 180) vytvořeným štětcem, vyplňovat začneme na souřadnicích [105,205].

            hNewPen = CreatePen(PS_SOLID, 3, RGB(180, 0, 0));   // Vytvoříme pero kreslící nepřerušenou čáru tloušťkou 3 a barvou danou složkami červená (R), zelená (G), modrá (B)
            hOldPen = (HPEN)SelectObject(hDC, hNewPen); //Přidělíme nové pero ploše pro kreslení a uložíme jej do proměnné hOldPen

            //Na vrchol obdélníku umístíme trojúhelník
            MoveToEx(hDC, 100, 200, NULL);
            LineTo(hDC, 200, 100); //Nakreslíme čáru, která začíná na aktuálních souřadnicích a končí na souřadnicích [200, 100]
            LineTo(hDC, 300, 200); //Nakreslíme čáru, která začíná na aktuálních souřadnicích a končí na souřadnicích [300, 200]            
            

            //Následuje pokus o animaci žlutou barvou vyplněného černě obtaženého kolečka
            hBrush = CreateSolidBrush(RGB(240, 240, 40)); //Vytvoříme štětec kreslící bez vzoru jen zadanou barvou
            hOldBrush = (HBRUSH)SelectObject(hDC, hBrush); //Přidělíme nový štětec ploše pro kreslení

            for (int i = 0; i < 400; i++)
            {
                hNewPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));   // Vytvoříme pero kreslící nepřerušenou čáru tloušťkou 3 a barvou danou složkami červená (R), zelená (G), modrá (B), maximálně 255,255,255
                hOldPen = (HPEN)SelectObject(hDC, hNewPen); //Přidělíme nové pero ploše pro kreslení a uložíme jej do proměnné hOldPen
                Ellipse(hDC, i*2 + 100, 320, i*2 + 200, 420); //Na nové souřadnice nakreslíme černou kružnici.

                Sleep(50);

                hNewPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));   // Vytvoříme pero kreslící nepřerušenou čáru tloušťkou 3 a barvou danou složkami červená (R), zelená (G), modrá (B), maximálně 255,255,255
                hOldPen = (HPEN)SelectObject(hDC, hNewPen); //Přidělíme nové pero ploše pro kreslení a uložíme jej do proměnné hOldPen
                Ellipse(hDC, i*2 + 100, 320, i*2 + 200, 420); //Černou kružnici přemažeme bílou kružnicí, aby vznikl dojem pohybu
            }

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
