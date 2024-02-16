#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wingdi.h>
#include <Windows.h>

#include "glext.h"
#include "wglext.h"

#define local_persist static
#define global_variable static
#define internal static

// WINDOWS
LRESULT MainWindowCallback(HWND Window,
			   UINT Message,
			   WPARAM wParam,
			   LPARAM lParam);

// OPENGL
void* LoadGLFunction (const char* name);
void InitOpenGL (HWND Window, HDC DeviceContext);
void OpenGLDraw (HDC DeviceContext);
