
//cinta de Moebius sin usar formato de libreria de GLUT (aqui esta con el formato que veia en OpenGl)
/**************************
 * Includes
 *
 **************************/


#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

//declaraciones
#define centro 1.0
 #define desliza 35
 #define phi 3.14159265358979
 
typedef struct _coordenadas_{ 
	float x,y,z;	
}Cord;

float A=1.9;
void segmento(Cord a, Cord b);
void ejes();
void Moebius(float a, float r);


void Moebius(float a, float r){ //a=diametro circulo, r= ancho
//u esta en (0,2pi) , v en (-1,1)
	Cord Moe;
	Cord p1, p2, p3, p4;
	int i,j;
	
	float hu = 2*phi/desliza, hv = 2*r/desliza;  //2r distancia de -1 a 1
	float u_i, v_j;
	
	  
	
	for(i=0; i<desliza ; i++){
		u_i = hu*i;
		for(j=0 ; j<desliza ; j++){ //duda
			
			v_j = -r +hv*j; 
			p1.x=(a+v_j*r*sin(u_i/2.0))*cos(u_i);
			p1.y=(a+v_j*r*sin(u_i/2.0))*sin(u_i);
			p1.z=v_j*r*cos(u_i/2);
			
			p2.x=(a+v_j*r*sin((u_i+hu)/2.0))*cos(u_i+hu); //u_i= u_i+hu
			p2.y=(a+v_j*r*sin((u_i+hu)/2.0))*sin(u_i+hu);
			p2.z=v_j*r*cos((u_i+hu)/2);
			
			p3.x=(a+(v_j+hv)*r*sin((u_i+hu)/2.0))*cos(u_i+hu); //u_i= u_i+hu, v_j= v_j+hv 
			p3.y=(a+(v_j+hv)*r*sin((u_i+hu)/2.0))*sin(u_i+hu);
			p3.z=(v_j+hv)*r*cos((u_i+hu)/2);
			
			p4.x=(a+(v_j+hv)*r*sin(u_i/2.0))*cos(u_i); // v_j= v_j+hv 
			p4.y=(a+(v_j+hv)*r*sin(u_i/2.0))*sin(u_i);
			p4.z=(v_j+hv)*r*cos(u_i/2);
			
			
		/*Begin(GL_QUADS); //moebius solido
				
				glVertex3f(p1.x, p1.y, p1.z);
				glVertex3f(p2.x, p2.y, p2.z);
				glVertex3f(p3.x, p3.y, p3.z);
				glVertex3f(p1.x, p1.y, p1.z);
			glEnd(); */
			
				segmento(p1,p2); //*
				segmento(p2,p3); //parte la cuadricula
				segmento(p3,p4); //*
				segmento(p4,p1); //rayas
			
			
			
		}
	}
	
}

void segmento(Cord a, Cord b){ //forma vectorial de la recta
	Cord director;
	director.x= b.x - a.x; director.y= b.y - a.y; director.z= b.z - a.z;
	int t;
	   double equis, ye, zeta,
	   		equis1, ye1, zeta1;
		
	   glBegin(GL_LINES);   
   		glLineWidth(8.0);   
    	glColor3f(0.0f, 10.0f, 10.0f);     // Green
        
        
        equis= centro+a.x+director.x;
		ye=centro+a.y+director.y;
		zeta=centro+a.z+director.z;
		equis1= centro+a.x;
		ye1=centro+a.y;
		zeta1=centro+a.z;
		
		
        equis*=0.25;
		ye*=0.25;
		zeta*=0.25;
		equis1*= 0.25;
		ye1*=0.25;
		zeta1*=0.25;
		
      	glVertex3f(equis,ye,zeta);
      	glVertex3f(equis1,ye1,zeta1);
     	glEnd();

}

void ejes(){
	   glBegin(GL_LINES);   

        glColor3f(0.0f, 10.0f, 0.0f);     // Green
      glVertex3f(centro,centro,centro);
        glVertex3f(centro+5.0,centro,centro);
            glColor3f(1.0f, 0.0f, 0.0f);     // Red
     glVertex3f(centro,centro,centro);
      glVertex3f(centro,centro+5.0,centro);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(centro,centro,centro);
       glVertex3f(centro,centro,centro+5.0);
       
    glEnd();

    
}



/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
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
    wc.lpszClassName = "Teseracto";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "Teseracto", "Teseracto", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 1256, 1256, //valores pantalla
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

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
            //------------------código-----------

            
            //glClearColor (1.0f, 1.0f, 1.0f, 0.5f);
            glClear (GL_COLOR_BUFFER_BIT);
            glPushMatrix ();
            glRotatef (theta, 0.0f, 1.0f, 0.0f);
            
			ejes();
            Moebius(1.7, 0.73);
			
		    glPopMatrix ();
            SwapBuffers (hDC);
            theta += 1.0f;
            Sleep (1);
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
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
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

