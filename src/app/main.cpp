#include <iostream>
#include <map>

#include "WindowInitiator.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::string backgroundColor = "black";
    auto shouldExitOnKeyPress = false;

    std::map<std::string, std::string*> argMap = {
        {"-c", &backgroundColor},
        {"--color", &backgroundColor},
        {"-dke", reinterpret_cast<std::string*>(&shouldExitOnKeyPress)},
        {"--disable-key-exit", reinterpret_cast<std::string*>(&shouldExitOnKeyPress)}
    };

    int argc;
    const auto argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    for (auto i = 1; i < argc; ++i) {
        std::wstring currentArgW = argv[i];

        if (std::string currentArg(currentArgW.begin(), currentArgW.end()); argMap.contains(currentArg)) {
            if (currentArg == "-dke" || currentArg == "--disable-key-exit") {
                shouldExitOnKeyPress = true;
            } else {
                std::wstring nextArgW = argv[++i];
                *argMap[currentArg] = std::string(nextArgW.begin(), nextArgW.end());
            }
        }
    }

    LocalFree(argv);

    WindowInitiator windowInitiator(backgroundColor, shouldExitOnKeyPress);
    windowInitiator.createWindow();
    return 0;
}
