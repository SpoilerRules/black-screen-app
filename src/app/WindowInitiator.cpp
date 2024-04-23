//
// Created by spoil on 04/14/2024.
//

#include "WindowInitiator.hpp"
#include <windows.h>

LRESULT CALLBACK HandleWindowMessages(HWND windowHandle, UINT messageType, WPARAM windowParameterValue, LPARAM messageData);

void WindowInitiator::createWindow() {
    const WNDCLASS windowClass = {
        .lpfnWndProc = HandleWindowMessages,
        .hInstance = GetModuleHandle(nullptr),
        .lpszClassName = "BlackWindowClass"
    };
    RegisterClass(&windowClass);

    const auto windowHandle = CreateWindowEx(
        0,
        "BlackWindowClass",
        "Black Screen Application",
        WS_POPUP | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    ShowCursor(false);

    ShowWindow(windowHandle, SW_SHOW);
    UpdateWindow(windowHandle);

    MSG message;
    while (GetMessage(&message, nullptr, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);

        if (message.message == WM_QUIT) {
            break;
        }
    }

    UnregisterClass("BlackWindowClass", GetModuleHandle(nullptr));
}

LRESULT CALLBACK HandleWindowMessages(const HWND windowHandle, const UINT messageType, const WPARAM windowParameterValue, const LPARAM messageData) { // NOLINT(*-misplaced-const)
    switch (messageType) {
        case WM_CLOSE:
        case WM_KEYDOWN:
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_ERASEBKGND: {
            RECT clientRect;
            GetClientRect(windowHandle, &clientRect);
            FillRect(reinterpret_cast<HDC>(windowParameterValue), &clientRect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
            return 1;
        }
        default:
            return DefWindowProc(windowHandle, messageType, windowParameterValue, messageData);
    }
}

