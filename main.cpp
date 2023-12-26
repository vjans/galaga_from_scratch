/**************************
 * Includes
 *
 **************************/
#include <windows.h>
#include <gl/gl.h>
#include <vector>
#include "gameConstants.h"
#include "game.h"

/*

@@@@@
TODOS
@@@@@

X sizes
X appearance from models (appearance to instance)
X bullets should dissappear (exists =false)  after leaving the screen
X Collision

-Game state
-GUI/Menus
-Text Output


Behavior:
- State machine
- State changes, shooting (weapon, freq), movement (seek player, avoid bullets) , animation


-model from type function 
-level loading
-enemy loading
-bullet loading
-weapon types


*/

Game game;
/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{	
	game.init_game();
	
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, SCREEN_SIZE, SCREEN_SIZE,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
    // Initialize shaders here

	
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    // Desired frame time (for 60 FPS)
    const double frameTime = 1000.0 / 60.0;

	/* program main loop */
    
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
        LARGE_INTEGER frameStart, frameEnd;
        QueryPerformanceCounter(&frameStart);
            /* OpenGL animation code goes here */

            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

            glPushMatrix ();
            game.run();
            glPopMatrix ();

            SwapBuffers (hDC);


        QueryPerformanceCounter(&frameEnd);

        // Calculate the elapsed time in milliseconds
        double elapsedTime = (frameEnd.QuadPart - frameStart.QuadPart) * 1000.0 / frequency.QuadPart;

        // Wait if necessary to maintain 60 FPS
        if (elapsedTime < frameTime) {
            //Sleep((DWORD)(frameTime - elapsedTime));
        }
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_UP:game.keys_pressed[2]= true; break;
        case VK_DOWN:game.keys_pressed[3]= true; break;
        case VK_LEFT:game.keys_pressed[0]= true; break;
        case VK_RIGHT:game.keys_pressed[1]= true; break;
        case VK_SPACE:game.keys_pressed[4]= true; break;
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    case WM_KEYUP:
        switch (wParam)
        {
        case VK_UP:game.keys_pressed[2]= false; break;
        case VK_DOWN:game.keys_pressed[3]= false; break;
        case VK_LEFT:game.keys_pressed[0]= false; break;
        case VK_RIGHT:game.keys_pressed[1]= false; break;
        case VK_SPACE:game.keys_pressed[4]= false; break;
        	
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
    glEnable(GL_DEPTH_TEST);
	
}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
