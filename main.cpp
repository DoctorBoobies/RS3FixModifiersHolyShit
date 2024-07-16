#include <windows.h>

#include <iostream>

HHOOK hHook = NULL;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT * pKeyBoard = (KBDLLHOOKSTRUCT * ) lParam;
        int vkCode = pKeyBoard -> vkCode;

        switch (wParam) {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            break;
        case WM_KEYUP:
        case WM_SYSKEYUP:
            if (vkCode == 160 || vkCode == 162) {
                auto fg = GetForegroundWindow();
                auto titleLen = GetWindowTextLength(fg);
                auto title = new char[titleLen + 1];
                GetWindowTextA(fg, title, titleLen + 1);
                if (strcmp(title, "RuneScape") == 0) {
                    Sleep(200);
                }
            }
            break;
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (hHook == NULL) {
        std::cerr << "shit fucked\n";
        return 1;
    }

    MSG msg;
    while (GetMessage( & msg, NULL, 0, 0)) {
        TranslateMessage( & msg);
        DispatchMessage( & msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}
