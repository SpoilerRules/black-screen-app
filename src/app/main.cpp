#include <windows.h>
#include "WindowInitiator.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WindowInitiator::createWindow();

    return 0;
}
