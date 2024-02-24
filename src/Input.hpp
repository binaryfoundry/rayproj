#pragma once

enum class DPadDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// these are matched to SDL key map scancodes
enum class Scancode
{
    S_UNKNOWN = 0,
    S_A = 4,
    S_B = 5,
    S_C = 6,
    S_D = 7,
    S_E = 8,
    S_F = 9,
    S_G = 10,
    S_H = 11,
    S_I = 12,
    S_J = 13,
    S_K = 14,
    S_L = 15,
    S_M = 16,
    S_N = 17,
    S_O = 18,
    S_P = 19,
    S_Q = 20,
    S_R = 21,
    S_S = 22,
    S_T = 23,
    S_U = 24,
    S_V = 25,
    S_W = 26,
    S_X = 27,
    S_Y = 28,
    S_Z = 29,
    S_1 = 30,
    S_2 = 31,
    S_3 = 32,
    S_4 = 33,
    S_5 = 34,
    S_6 = 35,
    S_7 = 36,
    S_8 = 37,
    S_9 = 38,
    S_0 = 39,
    S_RETURN = 40,
    S_ESCAPE = 41,
    S_BACKSPACE = 42,
    S_TAB = 43,
    S_SPACE = 44,
    S_MINUS = 45,
    S_EQUALS = 46,
    S_LEFTBRACKET = 47,
    S_RIGHTBRACKET = 48,
    S_BACKSLASH = 49,
    S_NONUSHASH = 50,
    S_SEMICOLON = 51,
    S_APOSTROPHE = 52,
    S_GRAVE = 53,
    S_COMMA = 54,
    S_PERIOD = 55,
    S_SLASH = 56,
    S_CAPSLOCK = 57,
    S_F1 = 58,
    S_F2 = 59,
    S_F3 = 60,
    S_F4 = 61,
    S_F5 = 62,
    S_F6 = 63,
    S_F7 = 64,
    S_F8 = 65,
    S_F9 = 66,
    S_F10 = 67,
    S_F11 = 68,
    S_F12 = 69,
    S_PRINTSCREEN = 70,
    S_SCROLLLOCK = 71,
    S_PAUSE = 72,
    S_INSERT = 73,
    S_HOME = 74,
    S_PAGEUP = 75,
    S_DELETE = 76,
    S_END = 77,
    S_PAGEDOWN = 78,
    S_RIGHT = 79,
    S_LEFT = 80,
    S_DOWN = 81,
    S_UP = 82,
    S_NUMLOCKCLEAR = 83,
    S_KP_DIVIDE = 84,
    S_KP_MULTIPLY = 85,
    S_KP_MINUS = 86,
    S_KP_PLUS = 87,
    S_KP_ENTER = 88,
    S_KP_1 = 89,
    S_KP_2 = 90,
    S_KP_3 = 91,
    S_KP_4 = 92,
    S_KP_5 = 93,
    S_KP_6 = 94,
    S_KP_7 = 95,
    S_KP_8 = 96,
    S_KP_9 = 97,
    S_KP_0 = 98,
    S_KP_PERIOD = 99,
    S_NONUSBACKSLASH = 100,
    S_APPLICATION = 101,
    S_POWER = 102,
    S_KP_EQUALS = 103,
    S_F13 = 104,
    S_F14 = 105,
    S_F15 = 106,
    S_F16 = 107,
    S_F17 = 108,
    S_F18 = 109,
    S_F19 = 110,
    S_F20 = 111,
    S_F21 = 112,
    S_F22 = 113,
    S_F23 = 114,
    S_F24 = 115,
    S_EXECUTE = 116,
    S_HELP = 117,
    S_MENU = 118,
    S_SELECT = 119,
    S_STOP = 120,
    S_AGAIN = 121,
    S_UNDO = 122,
    S_CUT = 123,
    S_COPY = 124,
    S_PASTE = 125,
    S_FIND = 126,
    S_MUTE = 127,
    S_VOLUMEUP = 128,
    S_VOLUMEDOWN = 129,
    S_KP_COMMA = 133,
    S_KP_EQUALSAS400 = 134,
    S_INTERNATIONAL1 = 135,
    S_INTERNATIONAL2 = 136,
    S_INTERNATIONAL3 = 137,
    S_INTERNATIONAL4 = 138,
    S_INTERNATIONAL5 = 139,
    S_INTERNATIONAL6 = 140,
    S_INTERNATIONAL7 = 141,
    S_INTERNATIONAL8 = 142,
    S_INTERNATIONAL9 = 143,
    S_LANG1 = 144,
    S_LANG2 = 145,
    S_LANG3 = 146,
    S_LANG4 = 147,
    S_LANG5 = 148,
    S_LANG6 = 149,
    S_LANG7 = 150,
    S_LANG8 = 151,
    S_LANG9 = 152,
    S_ALTERASE = 153,
    S_SYSREQ = 154,
    S_CANCEL = 155,
    S_CLEAR = 156,
    S_PRIOR = 157,
    S_RETURN2 = 158,
    S_SEPARATOR = 159,
    S_OUT = 160,
    S_OPER = 161,
    S_CLEARAGAIN = 162,
    S_CRSEL = 163,
    S_EXSEL = 164,
    S_KP_00 = 176,
    S_KP_000 = 177,
    S_THOUSANDSSEPARATOR = 178,
    S_DECIMALSEPARATOR = 179,
    S_CURRENCYUNIT = 180,
    S_CURRENCYSUBUNIT = 181,
    S_KP_LEFTPAREN = 182,
    S_KP_RIGHTPAREN = 183,
    S_KP_LEFTBRACE = 184,
    S_KP_RIGHTBRACE = 185,
    S_KP_TAB = 186,
    S_KP_BACKSPACE = 187,
    S_KP_A = 188,
    S_KP_B = 189,
    S_KP_C = 190,
    S_KP_D = 191,
    S_KP_E = 192,
    S_KP_F = 193,
    S_KP_XOR = 194,
    S_KP_POWER = 195,
    S_KP_PERCENT = 196,
    S_KP_LESS = 197,
    S_KP_GREATER = 198,
    S_KP_AMPERSAND = 199,
    S_KP_DBLAMPERSAND = 200,
    S_KP_VERTICALBAR = 201,
    S_KP_DBLVERTICALBAR = 202,
    S_KP_COLON = 203,
    S_KP_HASH = 204,
    S_KP_SPACE = 205,
    S_KP_AT = 206,
    S_KP_EXCLAM = 207,
    S_KP_MEMSTORE = 208,
    S_KP_MEMRECALL = 209,
    S_KP_MEMCLEAR = 210,
    S_KP_MEMADD = 211,
    S_KP_MEMSUBTRACT = 212,
    S_KP_MEMMULTIPLY = 213,
    S_KP_MEMDIVIDE = 214,
    S_KP_PLUSMINUS = 215,
    S_KP_CLEAR = 216,
    S_KP_CLEARENTRY = 217,
    S_KP_BINARY = 218,
    S_KP_OCTAL = 219,
    S_KP_DECIMAL = 220,
    S_KP_HEXADECIMAL = 221,
    S_LCTRL = 224,
    S_LSHIFT = 225,
    S_LALT = 226,
    S_LGUI = 227,
    S_RCTRL = 228,
    S_RSHIFT = 229,
    S_RALT = 230,
    S_RGUI = 231,
    S_MODE = 257,
    S_AUDIONEXT = 258,
    S_AUDIOPREV = 259,
    S_AUDIOSTOP = 260,
    S_AUDIOPLAY = 261,
    S_AUDIOMUTE = 262,
    S_MEDIASELECT = 263,
    S_WWW = 264,
    S_MAIL = 265,
    S_CALCULATOR = 266,
    S_COMPUTER = 267,
    S_AC_SEARCH = 268,
    S_AC_HOME = 269,
    S_AC_BACK = 270,
    S_AC_FORWARD = 271,
    S_AC_STOP = 272,
    S_AC_REFRESH = 273,
    S_AC_BOOKMARKS = 274,
    S_BRIGHTNESSDOWN = 275,
    S_BRIGHTNESSUP = 276,
    S_DISPLAYSWITCH = 277,
    S_KBDILLUMTOGGLE = 278,
    S_KBDILLUMDOWN = 279,
    S_KBDILLUMUP = 280,
    S_EJECT = 281,
    S_SLEEP = 282,
    S_APP1 = 283,
    S_APP2 = 284,
    S_AUDIOREWIND = 285,
    S_AUDIOFASTFORWARD = 286,
    NUM_SCANCODES = 512
};
