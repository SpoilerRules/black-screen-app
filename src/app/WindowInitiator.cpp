//
// Created by spoil on 04/14/2024.
//

#include "WindowInitiator.hpp"

#include <algorithm>
#include <regex>
#include <utility>

#include "ColorHandler.hpp"

LRESULT CALLBACK HandleWindowMessages(HWND windowHandle, UINT messageType, WPARAM windowParameterValue, LPARAM messageData);

std::string WindowInitiator::m_color = "black";
bool WindowInitiator::disableKeyExit = false;

WindowInitiator::WindowInitiator(std::string color, const bool& disableKeyExit) {
    WindowInitiator::disableKeyExit = disableKeyExit;

    std::ranges::transform(color, color.begin(),
                           [](const unsigned char stringCharacter) { return std::tolower(stringCharacter); });

    m_color = color == "black" ? std::move(color) :
              ColorHandler::colorMap.contains(color) ? ColorHandler::colorMap[color] : std::move(color);
}

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
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN: {
            if (!WindowInitiator::disableKeyExit) {
                PostQuitMessage(0);
            }
            return 0;
        }
        case WM_ERASEBKGND: {
            RECT clientRect;
            GetClientRect(windowHandle, &clientRect);
            HBRUSH colorBrush;

            if (WindowInitiator::m_color == "black") {
                colorBrush = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
            } else {
                if (std::regex_match(WindowInitiator::m_color, std::regex("^#([a-fA-F0-9]{6}|[a-fA-F0-9]{3})$"))) {
                    auto [red, green, blue] = ColorHandler::convertHextoRGB(WindowInitiator::m_color);
                    colorBrush = CreateSolidBrush(RGB(red, green, blue));
                } else {
                    const auto errorMessage = "Invalid color argument. Expected a hex color code or color name.";
                    MessageBox(nullptr, errorMessage, "Error - Black Screen Application", MB_ICONERROR | MB_OK);
                    throw std::invalid_argument(errorMessage);
                }
            }

            FillRect(reinterpret_cast<HDC>(windowParameterValue), &clientRect, colorBrush);

            if (WindowInitiator::m_color != "black") {
                DeleteObject(colorBrush);
            }

            return 1;
        }
        default:
            return DefWindowProc(windowHandle, messageType, windowParameterValue, messageData);
    }
}


