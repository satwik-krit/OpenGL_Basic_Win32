#include <gl/gl.h>
#include <stdio.h>

#include "win32_base.h"


/* SAMPLE ERROR FETCHING
  DWORD dw = GetLastError(); 
  LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL);
		OutputDebugString(lpMsgBuf); */
void*
LoadGLFunction (const char* name)
{
  void *function = (void *)wglGetProcAddress (name);
  // TODO: Handle case where function is NULL or 0
  return function;
}


void
InitOpenGL (HWND Window, HDC DeviceContext)
{
  PIXELFORMATDESCRIPTOR DesiredPixelFormat = {0};
  PIXELFORMATDESCRIPTOR SuggestedPixelFormat;
  DesiredPixelFormat.nSize = sizeof (DesiredPixelFormat);
  DesiredPixelFormat.nVersion = 1;
  DesiredPixelFormat.dwFlags = PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER|PFD_DRAW_TO_WINDOW;
  DesiredPixelFormat.cColorBits = 32; // Why 32 bits for 3 colors? Does it include the alpha channel as well as opposed to the docs?
  DesiredPixelFormat.cAlphaBits = 8;
  /* DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE; */

  int SuggestedPixelFormatIndex = ChoosePixelFormat (DeviceContext, &DesiredPixelFormat);
  DescribePixelFormat (DeviceContext, SuggestedPixelFormatIndex, sizeof (SuggestedPixelFormat), &SuggestedPixelFormat);
  SetPixelFormat (DeviceContext, SuggestedPixelFormatIndex, &SuggestedPixelFormat);

  HGLRC OpenGLRC = wglCreateContext (DeviceContext);

  if (wglMakeCurrent (DeviceContext, OpenGLRC))
  {
	PFNGLUSEPROGRAMPROC glUseProgram =(PFNGLUSEPROGRAMPROC) LoadGLFunction("glUseProgram");
  }
  else
  {;}
  
}


void
OpenGLDraw (HDC DeviceContext)
{
  glViewport (0, 0, 800, 800);
  glClearColor (0.0f,1.0f,1.0f,1.0f);
  glClear (GL_COLOR_BUFFER_BIT);
  SwapBuffers (DeviceContext);
}


LRESULT
MainWindowCallback(HWND Window,
		   UINT Message,
		   WPARAM wParam,
		   LPARAM lParam)
{
  LRESULT Result = 0;
  switch(Message)
  {
    case WM_CREATE:
      {
      } break;
    case WM_SIZE:
      {
	OutputDebugString("WM_SIZE\n");
      }	break;

    case WM_DESTROY:
      {
	OutputDebugString("WM_DESTROY\n");
      } break;

    case WM_MOVE:
      {
	OutputDebugString("WM_MOVE\n");
      } break;

    case WM_CLOSE:
      {
	OutputDebugString("WM_CLOSE\n");
	exit(0);
      } break;

    case WM_ACTIVATEAPP:
      {
	OutputDebugString("WM_ACTIVATEAPP\n");
      } break;

    default:
      {
	/* OutputDebugString("default\n"); */
	Result = DefWindowProc(Window, Message, wParam, lParam);
      } break;
  }

  return Result;
}

int WINAPI
WinMain(HINSTANCE Instance, // Windows-provided instance of the program
	HINSTANCE prevInstance, // NULL on newer Windows versions
	LPSTR argCount, // Number of command-line arguments
	int windowType) // How to open the window - minimised, maximised or ...
{
  WNDCLASS WindowClass = {0};
  WindowClass.style = CS_HREDRAW|CS_VREDRAW;
  WindowClass.lpfnWndProc = MainWindowCallback;
  WindowClass.hInstance = Instance;
  WindowClass.lpszClassName = "MyFirstWindow";

  if(RegisterClass (&WindowClass))
  {
      HWND WindowHandle = CreateWindowEx (WS_EX_OVERLAPPEDWINDOW|WS_EX_WINDOWEDGE,
					  WindowClass.lpszClassName,
					  "Learning OpenGL",
					  WS_OVERLAPPEDWINDOW|WS_VISIBLE,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  CW_USEDEFAULT,
					  0,
					  0,
					  Instance,
					  0);

      if(WindowHandle)
      {
	  HDC DeviceContext = GetDC (WindowHandle);

	  InitOpenGL (WindowHandle, DeviceContext);

	  while (1)
	  {
	     MSG Message;
	     BOOL MessageResult = GetMessage (&Message, 0, 0, 0);

	     if (MessageResult > 0)
	     {
	      TranslateMessage (&Message);
	      DispatchMessage (&Message);

	      OpenGLDraw (DeviceContext);
	     }

	     else
	     {
	      break;
	     }

	  }
	    
      }

      else
	{
  // TODO: Logging
	}
  }

  else
  {
    // TODO: Logging
  }

  return 0;
}

/* Local Variables: */
/* compile-command: "start /C build.bat" */
/* End: */
