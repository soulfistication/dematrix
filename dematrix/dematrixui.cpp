#if defined(_WIN32)

#include <windows.h>

// Controls

#define ID_TEXTINPUT 101
#define ID_BUTTON 102

// Forward declaration of the window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// The entry point for a graphical Windows-based application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "SampleWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // Register the window class
    if (!RegisterClass(&wc)) {
        return 0;
    }

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        "My First Win32 App",           // Window text (title)
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position (X, Y)
        800, 600,                       // Size (Width, Height)
        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

/*
// The window procedure (handles messages sent to the window)
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Painting code goes here
            
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    
    // Default handling for all other messages
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
*/

// Global or static variables to hold control handles (optional, but useful)
HWND hEdit;
HWND hButton;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Create a Text Input (Edit control)
            hEdit = CreateWindowEx(
                WS_EX_CLIENTEDGE,               // 3D border
                "EDIT",                         // Predefined class for text boxes
                "",                             // Default text
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, // Styles (Child, Visible, Scrollable)
                20, 20, 200, 25,                // X, Y, Width, Height
                hwnd,                           // Parent window
                (HMENU)ID_TEXTINPUT,            // Control ID
                GetModuleHandle(NULL),          // Instance handle
                NULL
            );

            // Create a Button
            hButton = CreateWindow(
                "BUTTON",                       // Predefined class for buttons
                "Show Message",                 // Button text
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // Styles
                230, 20, 120, 25,               // X, Y, Width, Height
                hwnd,                           // Parent window
                (HMENU)ID_BUTTON,               // Control ID
                GetModuleHandle(NULL),          // Instance handle
                NULL
            );
            
            // Optional: Set a standard system font so it doesn't look ancient
            HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            return 0;
        }

        case WM_COMMAND: {
            // Check if the event is a button click
            if (LOWORD(wParam) == ID_BUTTON) {
                // Get the length of the text in the edit control
                int len = GetWindowTextLength(hEdit);
                if (len > 0) {
                    // Allocate buffer and get the text
                    char* buffer = new char[len + 1];
                    GetWindowText(hEdit, buffer, len + 1);
                    
                    // Show it in a Message Box
                    MessageBox(hwnd, buffer, "Input Result", MB_OK | MB_ICONINFORMATION);
                    
                    delete[] buffer;
                } else {
                    MessageBox(hwnd, "Please enter some text!", "Warning", MB_OK | MB_ICONWARNING);
                }
            }
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
 
#endif
