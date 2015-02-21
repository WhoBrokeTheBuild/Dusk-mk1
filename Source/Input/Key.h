#ifndef DUSK_KEY_H
#define DUSK_KEY_H

#include <Graphics/Graphics.h>

namespace Dusk
{

namespace Input
{

enum Key
{
    INVALID_KEY         = -1,

    KEY_0               = 48,
    KEY_1               = 49,
    KEY_2               = 50,
    KEY_3               = 51,
    KEY_4               = 52,
    KEY_5               = 53,
    KEY_6               = 54,
    KEY_7               = 55,
    KEY_8               = 56,
    KEY_9               = 57,

    KEY_A               = 65,
    KEY_B               = 66,
    KEY_C               = 67,
    KEY_D               = 68,
    KEY_E               = 69,
    KEY_F               = 70,
    KEY_G               = 71,
    KEY_H               = 72,
    KEY_I               = 73,
    KEY_J               = 74,
    KEY_K               = 75,
    KEY_L               = 76,
    KEY_M               = 77,
    KEY_N               = 78,
    KEY_O               = 79,
    KEY_P               = 80,
    KEY_Q               = 81,
    KEY_R               = 82,
    KEY_S               = 83,
    KEY_T               = 84,
    KEY_U               = 85,
    KEY_V               = 86,
    KEY_W               = 87,
    KEY_X               = 88,
    KEY_Y               = 89,
    KEY_Z               = 90,

    KEY_SPACE           = 32,
    KEY_APOSTROPHE      = 39,
    KEY_SINGLE_QUOTE    = KEY_APOSTROPHE,
    KEY_GRAVE           = 96,
    KEY_COMMA           = 44,
    KEY_MINUS           = 45,
    KEY_DASH            = KEY_MINUS,
    KEY_PERIOD          = 46,
    KEY_DOT             = KEY_PERIOD,
    KEY_SLASH           = 47,
    KEY_BACKSLASH       = 92,
    KEY_SEMICOLON       = 59,
    KEY_EQUAL           = 61,
    KEY_LEFT_BRACKET    = 91,
    KEY_RIGHT_BRACKET   = 93,

    KEY_ESCAPE,
    KEY_ENTER,
    KEY_TAB,
    KEY_BACKSPACE,
    KEY_INSERT,
    KEY_DELETE,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_CAPS_LOCK,
    KEY_SCROLL_LOCK,
    KEY_NUM_LOCK,
    KEY_PRINT_SCREEN,
    KEY_PAUSE,
    KEY_MENU,

    KEY_LEFT_SHIFT,
    KEY_LEFT_CONTROL,
    KEY_LEFT_ALT,
    KEY_LEFT_SUPER,
    KEY_RIGHT_SHIFT,
    KEY_RIGHT_CONTROL,
    KEY_RIGHT_ALT,
    KEY_RIGHT_SUPER,

    KEY_LEFT,
    KEY_UP,
    KEY_RIGHT,
    KEY_DOWN,

    KEY_PAD_0,
    KEY_PAD_1,
    KEY_PAD_2,
    KEY_PAD_3,
    KEY_PAD_4,
    KEY_PAD_5,
    KEY_PAD_6,
    KEY_PAD_7,
    KEY_PAD_8,
    KEY_PAD_9,
    KEY_PAD_DECIMAL,
    KEY_PAD_DIVIDE,
    KEY_PAD_MULTIPLY,
    KEY_PAD_SUBTRACT,
    KEY_PAD_ADD,
    KEY_PAD_ENTER,
    KEY_PAD_EQUAL,

    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

}; // enum Key

inline Key GLFW2DuskKey( const GLFWKey& glfwKey )
{
    switch (glfwKey)
    {
        case GLFW_KEY_0: return KEY_0;
        case GLFW_KEY_1: return KEY_1;
        case GLFW_KEY_2: return KEY_2;
        case GLFW_KEY_3: return KEY_3;
        case GLFW_KEY_4: return KEY_4;
        case GLFW_KEY_5: return KEY_5;
        case GLFW_KEY_6: return KEY_6;
        case GLFW_KEY_7: return KEY_7;
        case GLFW_KEY_8: return KEY_8;
        case GLFW_KEY_9: return KEY_9;

        case GLFW_KEY_A: return KEY_A;
        case GLFW_KEY_B: return KEY_B;
        case GLFW_KEY_C: return KEY_C;
        case GLFW_KEY_D: return KEY_D;
        case GLFW_KEY_E: return KEY_E;
        case GLFW_KEY_F: return KEY_F;
        case GLFW_KEY_G: return KEY_G;
        case GLFW_KEY_H: return KEY_H;
        case GLFW_KEY_I: return KEY_I;
        case GLFW_KEY_J: return KEY_J;
        case GLFW_KEY_K: return KEY_K;
        case GLFW_KEY_L: return KEY_L;
        case GLFW_KEY_M: return KEY_M;
        case GLFW_KEY_N: return KEY_N;
        case GLFW_KEY_O: return KEY_O;
        case GLFW_KEY_P: return KEY_P;
        case GLFW_KEY_Q: return KEY_Q;
        case GLFW_KEY_R: return KEY_R;
        case GLFW_KEY_S: return KEY_S;
        case GLFW_KEY_T: return KEY_T;
        case GLFW_KEY_U: return KEY_U;
        case GLFW_KEY_V: return KEY_V;
        case GLFW_KEY_W: return KEY_W;
        case GLFW_KEY_X: return KEY_X;
        case GLFW_KEY_Y: return KEY_Y;
        case GLFW_KEY_Z: return KEY_Z;

        case GLFW_KEY_SPACE: return KEY_SPACE;
        case GLFW_KEY_APOSTROPHE: return KEY_APOSTROPHE;
        case GLFW_KEY_GRAVE_ACCENT: return KEY_GRAVE;
        case GLFW_KEY_COMMA: return KEY_COMMA;
        case GLFW_KEY_MINUS: return KEY_MINUS;
        case GLFW_KEY_PERIOD: return KEY_PERIOD;
        case GLFW_KEY_SLASH: return KEY_SLASH;
        case GLFW_KEY_BACKSLASH: return KEY_BACKSLASH;
        case GLFW_KEY_SEMICOLON: return KEY_SEMICOLON;
        case GLFW_KEY_EQUAL: return KEY_EQUAL;
        case GLFW_KEY_LEFT_BRACKET: return KEY_LEFT_BRACKET;
        case GLFW_KEY_RIGHT_BRACKET: return KEY_RIGHT_BRACKET;
        case GLFW_KEY_ESCAPE: return KEY_ESCAPE;
        case GLFW_KEY_ENTER: return KEY_ENTER;
        case GLFW_KEY_TAB: return KEY_TAB;
        case GLFW_KEY_BACKSPACE: return KEY_BACKSPACE;
        case GLFW_KEY_INSERT: return KEY_INSERT;
        case GLFW_KEY_DELETE: return KEY_DELETE;
        case GLFW_KEY_PAGE_UP: return KEY_PAGE_UP;
        case GLFW_KEY_PAGE_DOWN: return KEY_PAGE_DOWN;
        case GLFW_KEY_HOME: return KEY_HOME;
        case GLFW_KEY_END: return KEY_END;
        case GLFW_KEY_CAPS_LOCK: return KEY_CAPS_LOCK;
        case GLFW_KEY_SCROLL_LOCK: return KEY_SCROLL_LOCK;
        case GLFW_KEY_NUM_LOCK: return KEY_NUM_LOCK;
        case GLFW_KEY_PRINT_SCREEN: return KEY_PRINT_SCREEN;
        case GLFW_KEY_PAUSE: return KEY_PAUSE;
        case GLFW_KEY_MENU: return KEY_MENU;
        case GLFW_KEY_LEFT_SHIFT: return KEY_LEFT_SHIFT;
        case GLFW_KEY_LEFT_CONTROL: return KEY_LEFT_CONTROL;
        case GLFW_KEY_LEFT_ALT: return KEY_LEFT_ALT;
        case GLFW_KEY_LEFT_SUPER: return KEY_LEFT_SUPER;
        case GLFW_KEY_RIGHT_SHIFT: return KEY_RIGHT_SHIFT;
        case GLFW_KEY_RIGHT_CONTROL: return KEY_RIGHT_CONTROL;
        case GLFW_KEY_RIGHT_ALT: return KEY_RIGHT_ALT;
        case GLFW_KEY_RIGHT_SUPER: return KEY_RIGHT_SUPER;
        case GLFW_KEY_LEFT: return KEY_LEFT;
        case GLFW_KEY_UP: return KEY_UP;
        case GLFW_KEY_RIGHT: return KEY_RIGHT;
        case GLFW_KEY_DOWN: return KEY_DOWN;

        case GLFW_KEY_KP_0: return KEY_PAD_0;
        case GLFW_KEY_KP_1: return KEY_PAD_1;
        case GLFW_KEY_KP_2: return KEY_PAD_2;
        case GLFW_KEY_KP_3: return KEY_PAD_3;
        case GLFW_KEY_KP_4: return KEY_PAD_4;
        case GLFW_KEY_KP_5: return KEY_PAD_5;
        case GLFW_KEY_KP_6: return KEY_PAD_6;
        case GLFW_KEY_KP_7: return KEY_PAD_7;
        case GLFW_KEY_KP_8: return KEY_PAD_8;
        case GLFW_KEY_KP_9: return KEY_PAD_9;
        case GLFW_KEY_KP_DECIMAL: return KEY_PAD_DECIMAL;
        case GLFW_KEY_KP_DIVIDE: return KEY_PAD_DIVIDE;
        case GLFW_KEY_KP_MULTIPLY: return KEY_PAD_MULTIPLY;
        case GLFW_KEY_KP_SUBTRACT: return KEY_PAD_SUBTRACT;
        case GLFW_KEY_KP_ADD: return KEY_PAD_ADD;
        case GLFW_KEY_KP_ENTER: return KEY_PAD_ENTER;
        case GLFW_KEY_KP_EQUAL: return KEY_PAD_EQUAL;

        case GLFW_KEY_F1: return KEY_F1;
        case GLFW_KEY_F2: return KEY_F2;
        case GLFW_KEY_F3: return KEY_F3;
        case GLFW_KEY_F4: return KEY_F4;
        case GLFW_KEY_F5: return KEY_F5;
        case GLFW_KEY_F6: return KEY_F6;
        case GLFW_KEY_F7: return KEY_F7;
        case GLFW_KEY_F8: return KEY_F8;
        case GLFW_KEY_F9: return KEY_F9;
        case GLFW_KEY_F10: return KEY_F10;
        case GLFW_KEY_F11: return KEY_F11;
        case GLFW_KEY_F12: return KEY_F12;
    }

    return INVALID_KEY;
}

} // namespace Input

} // namespace Dusk

#endif // DUSK_KEY_H
