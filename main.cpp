#include <iostream>
#include <Windows.h>

bool isHolding = false;
bool scriptActive = false;
int toggleKey = VK_F1;

void ToggleScript() {
    scriptActive = !scriptActive;
    if (scriptActive) {
        std::cout << "Script activated" << std::endl;
    }
    else {
        std::cout << "Script deactivated" << std::endl;
        if (isHolding) {
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
            isHolding = false;
        }
    }
}

void ToggleRightClick() {
    if (isHolding) {
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        isHolding = false;
    }
    else {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        isHolding = true;
    }
}

int GetVirtualKeyCode(char key) {
    switch (tolower(key)) {
    case 'f1': return VK_F1;
    case 'f2': return VK_F2;
    case 'f3': return VK_F3;
    case 'f4': return VK_F4;
    case 'f5': return VK_F5;
    case 'f6': return VK_F6;
    case 'f7': return VK_F7;
    case 'f8': return VK_F8;
    case 'f9': return VK_F9;
    case 'f10': return VK_F10;
    case 'f11': return VK_F11;
    case 'f12': return VK_F12;
    case 'q': return 'Q';
    case 'w': return 'W';
    case 'e': return 'E';
    case 'r': return 'R';
    case 't': return 'T';
    case 'y': return 'Y';
    case 'u': return 'U';
    case 'i': return 'I';
    case 'o': return 'O';
    case 'p': return 'P';
    case 'a': return 'A';
    case 's': return 'S';
    case 'd': return 'D';
    case 'f': return 'F';
    case 'g': return 'G';
    case 'h': return 'H';
    case 'j': return 'J';
    case 'k': return 'K';
    case 'l': return 'L';
    case 'z': return 'Z';
    case 'x': return 'X';
    case 'c': return 'C';
    case 'v': return 'V';
    case 'b': return 'B';
    case 'n': return 'N';
    case 'm': return 'M';
    default: return VK_F1;
    }
}

int main() {

    std::cout << "<Terminal> Don't close until done." << std::endl;


    std::cout << "Enter the hotkey (e.g., F1, F2, A, S): ";
    char keyInput;
    std::cin >> keyInput;


    toggleKey = GetVirtualKeyCode(keyInput);


    if (!RegisterHotKey(NULL, 1, 0, toggleKey)) {
        std::cerr << "Failed to register hotkey" << std::endl;
        return 1;
    }


    ToggleScript();
    Sleep(5);
    ToggleScript();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            ToggleScript();
        }

        if (scriptActive) {
            ToggleRightClick();
            Sleep(100);
        }
    }

    UnregisterHotKey(NULL, 1);

    return 0;
}