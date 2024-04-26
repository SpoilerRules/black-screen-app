#include <iostream>
#include "WindowInitiator.hpp"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WindowInitiator::createWindow();
    return 0;
}
#else
int main() {
    WindowInitiator::createWindow();
    return 0;
}
#endif
