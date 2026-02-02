#pragma once

#define VER_MAJOR                1
#define VER_MINOR                0
#define VER_REVISION             0

#define STRINGIZE_(s) #s
#define STRINGIZE(s)  STRINGIZE_(s)

#define VER_STRING   STRINGIZE(VER_MAJOR) "." STRINGIZE(VER_MINOR) "." STRINGIZE(VER_REVISION)

#define IDI_APP                                100

#define IDR_MAINMENU                           200
#define IDM_APP_OPEN                           201
#define IDM_APP_CREATESHORTCUT                 202
#define IDM_APP_EXIT                           203
#define IDM_VIEW_REFRESH                       204
#define IDM_VIEW_ICONS                         205
#define IDM_VIEW_LIST                          206
#define IDM_HELP_ABOUT                         207

#define IDR_LISTITEMMENU                       300
#define IDR_LISTMENU                           301
