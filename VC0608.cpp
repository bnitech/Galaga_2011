// VC0608.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_VC0608, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_VC0608);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_VC0608);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_VC0608;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_R_L 0 
#define MAX_R_T 0
#define MAX_R_R 800
#define MAX_R_B 550

#define MAX_M_L 800
#define MAX_M_T 0
#define MAX_M_R 1100
#define MAX_M_B 550


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      //CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   hWnd=CreateWindow(szWindowClass, szTitle,WS_BORDER | WS_CAPTION | WS_SYSMENU,
		200,100,MAX_M_R,MAX_R_B+50, NULL,(HMENU)NULL,hInstance,NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



#define MAX_gunLR 20
#define MAX_gunB 20
#define MAX_gunLR_ne 20
#define MAX_gunB_ne 20

#define MAX_monB_r 2
#define MAX_monB_c 10
#define MAX_monA_r 2
#define MAX_monA_c 15
#define MAX_monB_life 15
#define MAX_monA_life 7

HBITMAP hBit,hBG, hMe,hgunLR,hgunB,hMonA,hMonB,hMonC,hMonA_1,hMonA_2,hMonB_1,hMonB_2,hstart,hover,hmenu,hitemA;
HWND hWndMain;

RECT a, g_me,g_ne,g_gunL[MAX_gunLR], g_gunR[MAX_gunLR], g_mon, g_gunS, g_gunB[MAX_gunB];
RECT g_gunL_ne[MAX_gunLR_ne], g_gunR_ne[MAX_gunLR_ne],g_gunB_ne[MAX_gunB_ne];

RECT g_bg, g_monA[MAX_monA_r][MAX_monA_c], g_monB[MAX_monB_r][MAX_monB_c], g_move , g_monC;
RECT g_itemA;

HANDLE H_GL[MAX_gunLR],H_GR[MAX_gunLR],H_GS,H_GB[MAX_gunB], H_IA;
HANDLE H_GL_ne[MAX_gunLR_ne],H_GR_ne[MAX_gunLR_ne],H_GB_ne[MAX_gunB_ne];

int chk_monA[MAX_monA_r][MAX_monA_c],chk_monB[MAX_monB_r][MAX_monB_c],chk_itemA;

int monA_cnt,monB_cnt,gunS_cnt,gunL_index,gunR_index,gunB_index,gunB_total,gunC_total;
int gunL_index_ne,gunR_index_ne,gunB_index_ne, gunB_total_ne;

int gunL_cnt[MAX_gunLR],gunR_cnt[MAX_gunLR],gunB_cnt[MAX_gunB];
int gunL_cnt_ne[MAX_gunLR_ne],gunR_cnt_ne[MAX_gunLR_ne],gunB_cnt_ne[MAX_gunB_ne];

int p1gun_kind,p2gun_kind, monAB_m_r,monAB_m_l, monC_m_l, monC_m_r,monC_m_d,monC_m_u;

int g_xi,g_yi,t_cnt,monAB_move_c[2],monAB_move_r=1;

int monAB_time,GameOver,GameStart, monC_time,itemA_time ,TotalScore,si,bun,cho,p1me_life=4,p2me_life=4,stage,time,player;

char monAB_re='r',monC_re='r';


void DrawSTART(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hstart);
	StretchBlt(hdc,0,0,MAX_M_R,MAX_M_B,MemDC,0,0,600,450,SRCCOPY);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}
void DrawOVER(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hover);

	BitBlt(hdc,MAX_R_R/2-50,MAX_R_B/2,160,30,MemDC,0,0,SRCCOPY);
	
	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}
void DrawBG(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hBG);
	g_bg.top-=2;
	BitBlt(hdc,0,0,MAX_R_R,MAX_R_B,MemDC,0,g_bg.top,SRCCOPY);
	
	if(g_bg.top==0)
		g_bg.top=1400;



	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawMenu(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	HFONT font, oldfont;

	char buf[30];
	
	int i, my=20;
	

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hBG);

	StretchBlt(hdc,MAX_M_L,MAX_M_T,MAX_M_R,MAX_M_B,MemDC,0,0,100,200,SRCCOPY);

	font=CreateFont(30,0,0,0,1000,0,0,0,HANGEUL_CHARSET,0,0,0,0,"굴림");
	oldfont=(HFONT)SelectObject(hdc,font);

//	SetBkColor(hdc,RGB(255,255,0));
	SetTextColor(hdc,RGB(255,0,0));
	wsprintf(buf,"STAGE 0%d",stage);
	TextOut(hdc, MAX_M_L+100, 70,buf,strlen(buf));

	font=CreateFont(20,0,0,0,1000,0,0,0,HANGEUL_CHARSET,0,0,0,0,"굴림");
	oldfont=(HFONT)SelectObject(hdc,font);

	SetTextColor(hdc,RGB(255,255,50));
	SetBkMode(hdc,TRANSPARENT);

	wsprintf(buf,"SCORE :  %d",TotalScore);
	TextOut(hdc, MAX_M_L+50, 150,buf,strlen(buf));

	wsprintf(buf,"TIME :  %d / %d / %d",si,bun,cho);
	TextOut(hdc, MAX_M_L+50, 180,buf,strlen(buf));

	if(player==1)
	{
		SetTextColor(hdc,RGB(0,0,255));
		wsprintf(buf,"PLAYER 1");
		TextOut(hdc, MAX_M_L+50,220,buf,strlen(buf));

		wsprintf(buf,"( 1 )        ∞");
		TextOut(hdc, MAX_M_L+50, 260,buf,strlen(buf));

		OldBitmap=(HBITMAP)SelectObject(MemDC, hgunLR);
		StretchBlt(hdc,MAX_M_L+100,260,10,20,MemDC,0,0,10,20,MERGECOPY);

		wsprintf(buf,"( 2 )        %d",20);
		TextOut(hdc, MAX_M_L+50, 290,buf,strlen(buf));

		OldBitmap=(HBITMAP)SelectObject(MemDC, hgunB);
		StretchBlt(hdc,MAX_M_L+100,290,20,20,MemDC,0,0,20,20,MERGECOPY);

		wsprintf(buf,"( 3 )        %d",gunC_total);
		TextOut(hdc, MAX_M_L+50, 320,buf,strlen(buf));
	}
	else
	{
		SetTextColor(hdc,RGB(0,0,255));
		wsprintf(buf,"PLAYER 1");
		TextOut(hdc, MAX_M_L+50,220,buf,strlen(buf));

		wsprintf(buf,"( p )        ∞");
		TextOut(hdc, MAX_M_L+50, 260,buf,strlen(buf));

		OldBitmap=(HBITMAP)SelectObject(MemDC, hgunLR);
		StretchBlt(hdc,MAX_M_L+120,260,10,20,MemDC,0,0,10,20,MERGECOPY);

		wsprintf(buf,"( [ )        %d",20);
		TextOut(hdc, MAX_M_L+50, 290,buf,strlen(buf));

		OldBitmap=(HBITMAP)SelectObject(MemDC, hgunB);
		StretchBlt(hdc,MAX_M_L+120,290,20,20,MemDC,0,0,20,20,MERGECOPY);

		wsprintf(buf,"( ] )        %d",gunC_total);
		TextOut(hdc, MAX_M_L+50, 320,buf,strlen(buf));

		SetTextColor(hdc,RGB(255,0,0));
		wsprintf(buf,"PLAYER 2");
		TextOut(hdc, MAX_M_L+50,360,buf,strlen(buf));

		wsprintf(buf,"( q )        ∞");
		TextOut(hdc, MAX_M_L+50, 400,buf,strlen(buf));

		OldBitmap=(HBITMAP)SelectObject(MemDC, hgunLR);
		StretchBlt(hdc,MAX_M_L+120,400,10,20,MemDC,0,0,10,20,MERGECOPY);

		wsprintf(buf,"( w )        %d",20);
		TextOut(hdc, MAX_M_L+50, 430,buf,strlen(buf));

		OldBitmap=(HBITMAP)SelectObject(MemDC, hgunB);
		StretchBlt(hdc,MAX_M_L+120,430,20,20,MemDC,0,0,20,20,MERGECOPY);

		wsprintf(buf,"( e )        %d",gunC_total);
		TextOut(hdc, MAX_M_L+50, 460,buf,strlen(buf));



	}

	for(i=0;i<=p1me_life-1;i++)
	{
		OldBitmap=(HBITMAP)SelectObject(MemDC, hMe);
		StretchBlt(hdc,MAX_M_L+70+i*40,500,35,30,MemDC,0,0,35,30,MERGECOPY);
	}
	for(i=0;i<=p2me_life-1;i++)
	{
		OldBitmap=(HBITMAP)SelectObject(MemDC, hMe);
		StretchBlt(hdc,MAX_M_L+70+i*40,500,35,30,MemDC,0,0,35,30,MERGECOPY);
	}

	SelectObject(hdc,oldfont);
	DeleteObject(font);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void DrawME(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hMe);

	if(player==1)
	{
		StretchBlt(hdc,g_me.left,g_me.top,35,30,MemDC,0,0,35,30,MERGECOPY);
	}
	else
	{
		StretchBlt(hdc,g_me.left,g_me.top,35,30,MemDC,0,0,35,30,MERGECOPY);
		StretchBlt(hdc,g_ne.left,g_ne.top,35,30,MemDC,0,0,35,30,MERGECOPY);

	}

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}
void DrawMonA(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBit;

	int i,j;

	for(i=0;i<MAX_monA_r;i++)
	{
		for(j=0;j<MAX_monA_c;j++)
		{
			if(chk_monA[i][j]==7)
			{
				MemDC=CreateCompatibleDC(hdc);
				OldBit=(HBITMAP)SelectObject(MemDC, hMonA);

				StretchBlt(hdc,g_monA[i][j].left,g_monA[i][j].top,20,20,MemDC,0,0,20,20,MERGECOPY);

				SelectObject(MemDC,OldBit);
				DeleteDC(MemDC);
			}
			if(chk_monA[i][j]>=5 && chk_monA[i][j]<7)
			{
				MemDC=CreateCompatibleDC(hdc);
				OldBit=(HBITMAP)SelectObject(MemDC, hMonA_1);

				StretchBlt(hdc,g_monA[i][j].left,g_monA[i][j].top,20,20,MemDC,0,0,20,20,MERGECOPY);

				SelectObject(MemDC,OldBit);
				DeleteDC(MemDC);
			}
			if(chk_monA[i][j]>=1 && chk_monA[i][j]<5)
			{
				MemDC=CreateCompatibleDC(hdc);
				OldBit=(HBITMAP)SelectObject(MemDC, hMonA_2);

				StretchBlt(hdc,g_monA[i][j].left,g_monA[i][j].top,20,20,MemDC,0,0,20,20,MERGECOPY);

				SelectObject(MemDC,OldBit);
				DeleteDC(MemDC);
			}
		}
	}
}
void DrawMonB(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBit;

	int i,j;

	for(i=0;i<MAX_monB_r;i++)
	{
		for(j=0;j<MAX_monB_c;j++)
		{
			if(chk_monB[i][j]==15)
			{
				MemDC=CreateCompatibleDC(hdc);
				OldBit=(HBITMAP)SelectObject(MemDC, hMonB);

				StretchBlt(hdc,g_monB[i][j].left,g_monB[i][j].top,20,20,MemDC,0,0,20,20,MERGECOPY);

				SelectObject(MemDC,OldBit);
				DeleteDC(MemDC);
			}
			if(chk_monB[i][j]>=9 && chk_monB[i][j]<15)
			{
				MemDC=CreateCompatibleDC(hdc);
				OldBit=(HBITMAP)SelectObject(MemDC, hMonB_1);

				StretchBlt(hdc,g_monB[i][j].left,g_monB[i][j].top,20,20,MemDC,0,0,20,20,MERGECOPY);

				SelectObject(MemDC,OldBit);
				DeleteDC(MemDC);
			}
			if(chk_monB[i][j]>=1 && chk_monB[i][j]<10)
			{
				MemDC=CreateCompatibleDC(hdc);
				OldBit=(HBITMAP)SelectObject(MemDC, hMonB_2);

				StretchBlt(hdc,g_monB[i][j].left,g_monB[i][j].top,20,20,MemDC,0,0,20,20,MERGECOPY);

				SelectObject(MemDC,OldBit);
				DeleteDC(MemDC);
			}
		}
	}
}
void DrawMonC(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hMonC);

	BitBlt(hdc,g_monC.left,g_monC.top,30,30,MemDC,0,0,MERGECOPY);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);

}
void DrawgunL(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	int i;

	for(i=0;i<MAX_gunLR;i++)
	{
		MemDC=CreateCompatibleDC(hdc);
		OldBitmap=(HBITMAP)SelectObject(MemDC,hgunLR);

		StretchBlt(hdc,g_gunL[i].left,g_gunL[i].top,10,20,MemDC,0,0,10,20,MERGECOPY);

		SelectObject(MemDC,OldBitmap);
		DeleteDC(MemDC);
	}
}
void DrawgunL_ne(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	int i;

	for(i=0;i<MAX_gunLR_ne;i++)
	{
		MemDC=CreateCompatibleDC(hdc);
		OldBitmap=(HBITMAP)SelectObject(MemDC,hgunLR);

		StretchBlt(hdc,g_gunL_ne[i].left,g_gunL_ne[i].top,10,20,MemDC,0,0,10,20,MERGECOPY);

		SelectObject(MemDC,OldBitmap);
		DeleteDC(MemDC);
	}
}
void DrawgunR(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	int i;

	for(i=0;i<MAX_gunLR;i++)
	{
		MemDC=CreateCompatibleDC(hdc);
		OldBitmap=(HBITMAP)SelectObject(MemDC,hgunLR);

		StretchBlt(hdc,g_gunR[i].left,g_gunR[i].top,10,20,MemDC,0,0,10,20,MERGECOPY);

		SelectObject(MemDC,OldBitmap);
		DeleteDC(MemDC);
	}
}
void DrawgunR_ne(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	int i;

	for(i=0;i<MAX_gunLR_ne;i++)
	{
		MemDC=CreateCompatibleDC(hdc);
		OldBitmap=(HBITMAP)SelectObject(MemDC,hgunLR);

		StretchBlt(hdc,g_gunR_ne[i].left,g_gunR_ne[i].top,10,20,MemDC,0,0,10,20,MERGECOPY);

		SelectObject(MemDC,OldBitmap);
		DeleteDC(MemDC);
	}

}

void DrawgunB(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	int i;

	for(i=0;i<MAX_gunB;i++)
	{
		MemDC=CreateCompatibleDC(hdc);
		OldBitmap=(HBITMAP)SelectObject(MemDC,hgunB);

		StretchBlt(hdc,g_gunB[i].left,g_gunB[i].top,20,20,MemDC,0,0,20,20,MERGECOPY);

		SelectObject(MemDC,OldBitmap);
		DeleteDC(MemDC);
	}
}
void DrawgunB_ne(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	int i;

	for(i=0;i<MAX_gunB_ne;i++)
	{
		MemDC=CreateCompatibleDC(hdc);
		OldBitmap=(HBITMAP)SelectObject(MemDC,hgunB);

		StretchBlt(hdc,g_gunB_ne[i].left,g_gunB_ne[i].top,20,20,MemDC,0,0,20,20,MERGECOPY);

		SelectObject(MemDC,OldBitmap);
		DeleteDC(MemDC);
	}

}
void DrawitemA(HDC hdc)
{
	HDC MemDC;
	HBITMAP OldBitmap;

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hitemA);

	StretchBlt(hdc,g_itemA.left,g_itemA.top,30,30,MemDC,0,0,50,50,MERGECOPY);
	
	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}
DWORD WINAPI gunL(LPVOID lp)
{
	HDC hdc;
	hdc = GetDC(hWndMain);
	int i,j,index;

	index = (int)lp;
	g_gunL[index].left = g_me.left-10;
	g_gunL[index].top = g_me.top-20;
	g_gunL[index].right =g_gunL[index].left+10;
	g_gunL[index].bottom = g_gunL[index].top+20;
	
	while(1)	
	{
		g_gunL[index].top-=3;
		g_gunL[index].bottom-=3;

		Sleep(10);

		for(i=0;i<MAX_monA_r;i++)
		{
			for(j=0;j<MAX_monA_c;j++)
			{
				if(IntersectRect(&a,&g_gunL[index],&g_monA[i][j]))
				{
					
					g_gunL[index].left = MAX_M_R;
					g_gunL[index].top = 0;
					g_gunL[index].right = 0;
					g_gunL[index].bottom = 0;
					gunL_cnt[index]=0;
					TerminateThread(H_GL[index],0);
				}
			}
		}
		for(i=0;i<MAX_monB_r;i++)
		{
			for(j=0;j<MAX_monB_c;j++)
			{
				if(IntersectRect(&a,&g_gunL[index],&g_monB[i][j]))
				{
					
					g_gunL[index].left = MAX_M_R;
					g_gunL[index].top = 0;
					g_gunL[index].right = 0;
					g_gunL[index].bottom = 0;
					gunL_cnt[index]=0;
					TerminateThread(H_GL[index],0);
					
				}
			}
		}

		if(IntersectRect(&a,&g_gunL[index],&g_monC))
		{
			
			g_gunL[index].left = MAX_M_R;
			g_gunL[index].top = 0;
			g_gunL[index].right = 0;
			g_gunL[index].bottom = 0;
			gunL_cnt[index]=0;
			TerminateThread(H_GL[index],0);
			
		}
		if(MAX_R_T>=g_gunL[index].top-10)
		{
			
			g_gunL[index].left = MAX_M_R;
			g_gunL[index].top = 0;
			g_gunL[index].right = 0;
			g_gunL[index].bottom = 0;
			gunL_cnt[index]=0;
			TerminateThread(H_GL[index],0);
			
		}
	}
	
	ReleaseDC(hWndMain,hdc);

	return 0;
}
DWORD WINAPI gunL_ne(LPVOID lp)
{
	HDC hdc;
	hdc = GetDC(hWndMain);
	int i,j,index;

	index = (int)lp;
	g_gunL_ne[index].left = g_ne.left-10;
	g_gunL_ne[index].top = g_ne.top-20;
	g_gunL_ne[index].right =g_gunL_ne[index].left+10;
	g_gunL_ne[index].bottom = g_gunL_ne[index].top+20;
	
	while(1)	
	{
		g_gunL_ne[index].top-=3;
		g_gunL_ne[index].bottom-=3;

		Sleep(10);

		for(i=0;i<MAX_monA_r;i++)
		{
			for(j=0;j<MAX_monA_c;j++)
			{
				if(IntersectRect(&a,&g_gunL_ne[index],&g_monA[i][j]))
				{
					
					g_gunL_ne[index].left = MAX_M_R;
					g_gunL_ne[index].top = 0;
					g_gunL_ne[index].right = 0;
					g_gunL_ne[index].bottom = 0;
					gunL_cnt_ne[index]=0;
					TerminateThread(H_GL_ne[index],0);
				}
			}
		}
		for(i=0;i<MAX_monB_r;i++)
		{
			for(j=0;j<MAX_monB_c;j++)
			{
				if(IntersectRect(&a,&g_gunL_ne[index],&g_monB[i][j]))
				{
					
					g_gunL_ne[index].left = MAX_M_R;
					g_gunL_ne[index].top = 0;
					g_gunL_ne[index].right = 0;
					g_gunL_ne[index].bottom = 0;
					gunL_cnt_ne[index]=0;
					TerminateThread(H_GL_ne[index],0);
					
				}
			}
		}

		if(IntersectRect(&a,&g_gunL_ne[index],&g_monC))
		{
			
			g_gunL_ne[index].left = MAX_M_R;
			g_gunL_ne[index].top = 0;
			g_gunL_ne[index].right = 0;
			g_gunL_ne[index].bottom = 0;
			gunL_cnt_ne[index]=0;
			TerminateThread(H_GL_ne[index],0);
			
		}
		if(MAX_R_T>=g_gunL_ne[index].top-10)
		{
			
			g_gunL_ne[index].left = MAX_M_R;
			g_gunL_ne[index].top = 0;
			g_gunL_ne[index].right = 0;
			g_gunL_ne[index].bottom = 0;
			gunL_cnt_ne[index]=0;
			TerminateThread(H_GL_ne[index],0);
			
		}
	}
	
	ReleaseDC(hWndMain,hdc);

	return 0;
}
DWORD WINAPI gunR(LPVOID lp)
{
	HDC hdc;
	hdc = GetDC(hWndMain);
	int index,i,j;

	index = (int)lp;
	g_gunR[index].left = g_me.right-3;
	g_gunR[index].top = g_me.top-20;
	g_gunR[index].right = g_gunR[index].left+10;
	g_gunR[index].bottom = g_gunR[index].top+20;
	
	while(1)	
	{
		g_gunR[index].top-=3;
		g_gunR[index].bottom-=3;

		Sleep(10);


		for(i=0;i<MAX_monA_r;i++)
		{
			for(j=0;j<MAX_monA_c;j++)
			{
				if(IntersectRect(&a,&g_gunR[index],&g_monA[i][j]))
				{
					g_gunR[index].left = MAX_M_R;
					g_gunR[index].top = 0;
					g_gunR[index].right = 0;
					g_gunR[index].bottom = 0;
					gunR_cnt[index]=0;
					TerminateThread(H_GR[index],0);
					
				}
				else if(IntersectRect(&a,&g_gunR[index],&g_monB[i][j]))
				{
					g_gunR[index].left = MAX_M_R;
					g_gunR[index].top = 0;
					g_gunR[index].right = 0;
					g_gunR[index].bottom = 0;	
					gunR_cnt[index]=0;
					TerminateThread(H_GR[index],0);
					
				}
			}
		}
		if(IntersectRect(&a,&g_gunR[index],&g_monC))
		{
			
			g_gunR[index].left = MAX_M_R;
			g_gunR[index].top = 0;
			g_gunR[index].right = 0;
			g_gunR[index].bottom = 0;
			gunR_cnt[index]=0;
			TerminateThread(H_GR[index],0);
			
		}
		if(MAX_R_T>=g_gunR[index].top-10)
		{
			g_gunR[index].left = MAX_M_R;
			g_gunR[index].top = 0;
			g_gunR[index].right = 0;
			g_gunR[index].bottom = 0;
			gunR_cnt[index]=0;
			TerminateThread(H_GR[index],0);
			
		}
	}

	ReleaseDC(hWndMain,hdc);

	return 0;
}
DWORD WINAPI gunR_ne(LPVOID lp)
{
	HDC hdc;
	hdc = GetDC(hWndMain);
	int index,i,j;

	index = (int)lp;
	g_gunR_ne[index].left = g_ne.right-3;
	g_gunR_ne[index].top = g_ne.top-20;
	g_gunR_ne[index].right = g_gunR_ne[index].left+10;
	g_gunR_ne[index].bottom = g_gunR_ne[index].top+20;
	
	while(1)	
	{
		g_gunR_ne[index].top-=3;
		g_gunR_ne[index].bottom-=3;

		Sleep(10);


		for(i=0;i<MAX_monA_r;i++)
		{
			for(j=0;j<MAX_monA_c;j++)
			{
				if(IntersectRect(&a,&g_gunR_ne[index],&g_monA[i][j]))
				{
					g_gunR_ne[index].left = MAX_M_R;
					g_gunR_ne[index].top = 0;
					g_gunR_ne[index].right = 0;
					g_gunR_ne[index].bottom = 0;
					gunR_cnt_ne[index]=0;
					TerminateThread(H_GR_ne[index],0);
					
				}
				else if(IntersectRect(&a,&g_gunR_ne[index],&g_monB[i][j]))
				{
					g_gunR_ne[index].left = MAX_M_R;
					g_gunR_ne[index].top = 0;
					g_gunR_ne[index].right = 0;
					g_gunR_ne[index].bottom = 0;	
					gunR_cnt_ne[index]=0;
					TerminateThread(H_GR_ne[index],0);
					
				}
			}
		}
		if(IntersectRect(&a,&g_gunR_ne[index],&g_monC))
		{
			
			g_gunR_ne[index].left = MAX_M_R;
			g_gunR_ne[index].top = 0;
			g_gunR_ne[index].right = 0;
			g_gunR_ne[index].bottom = 0;
			gunR_cnt_ne[index]=0;
			TerminateThread(H_GR_ne[index],0);
			
		}
		if(MAX_R_T>=g_gunR_ne[index].top-10)
		{
			g_gunR_ne[index].left = MAX_M_R;
			g_gunR_ne[index].top = 0;
			g_gunR_ne[index].right = 0;
			g_gunR_ne[index].bottom = 0;
			gunR_cnt_ne[index]=0;
			TerminateThread(H_GR_ne[index],0);
			
		}
	}

	ReleaseDC(hWndMain,hdc);

	return 0;
}
DWORD WINAPI gunB(LPVOID lp)
{
	int i,j; //R=10;
	int xi,yi,index, t_cnt=0;

	
	index = (int)lp;
	if(index%3==0)
	{
		g_gunB[index].left=g_me.left-20; //초기위치 , 현재위치
		g_gunB[index].top=g_me.top-20;
		xi=-4;  //이동거리
		yi=-2;
	}
	else if(index%3==1)
	{
		g_gunB[index].left=g_me.right; 
		g_gunB[index].top=g_me.bottom-40;
		xi=4;  
		yi=-2;
	}
	else
	{
		g_gunB[index].left=g_me.left+8; 
		g_gunB[index].top=g_me.top-20;
		yi=-5;
	}

	
	while(1)
	{
		t_cnt++;
		if ( MAX_R_L >= g_gunB[index].left || g_gunB[index].right >= MAX_R_R-10) {
			xi*=-1;
		}

		if ( MAX_R_T >= g_gunB[index].top || g_gunB[index].bottom >= MAX_R_B-10) {
			yi*=-1;
		}

		g_gunB[index].left+=xi;
		g_gunB[index].top+=yi;
		g_gunB[index].right = g_gunB[index].left+20;
		g_gunB[index].bottom = g_gunB[index].top+20;

		Sleep(10);

		
		if(t_cnt==10000)
		{
			gunB_cnt[index]=2;
			TerminateThread(H_GB[index],0);
		}
		
		for(i=0;i<MAX_monA_r;i++)
		{
			for(j=0;j<MAX_monA_c;j++)
			{
				if(IntersectRect(&a,&g_gunB[index],&g_monA[i][j]))
				{
					g_gunB[index].left = MAX_M_R;
					g_gunB[index].top = 0;
					g_gunB[index].right = 0;
					g_gunB[index].bottom = 0;
					gunB_cnt[index]=2;
					TerminateThread(H_GB[index],0);
					
				}
				else if(IntersectRect(&a,&g_gunB[index],&g_monB[i][j]))
				{
					g_gunB[index].left = MAX_M_R;
					g_gunB[index].top = 0;
					g_gunB[index].right = 0;
					g_gunB[index].bottom = 0;
					gunB_cnt[index]=2;
					TerminateThread(H_GB[index],0);
					
				}
				else if(IntersectRect(&a,&g_gunB[index],&g_monC))
				{
					g_gunB[index].left = MAX_M_R;
					g_gunB[index].top = 0;
					g_gunB[index].right = 0;
					g_gunB[index].bottom = 0;
					gunB_cnt[index]=2;
					TerminateThread(H_GB[index],0);
					
				}
			}
		}
	}
}
DWORD WINAPI gunB_ne(LPVOID lp)
{
	int i,j; //R=10;
	int xi,yi,index, t_cnt=0;

	
	index = (int)lp;
	if(index%3==0)
	{
		g_gunB_ne[index].left=g_ne.left-20; //초기위치 , 현재위치
		g_gunB_ne[index].top=g_ne.top-20;
		xi=-4;  //이동거리
		yi=-2;
	}
	else if(index%3==1)
	{
		g_gunB_ne[index].left=g_ne.right; 
		g_gunB_ne[index].top=g_ne.bottom-40;
		xi=4;  
		yi=-2;
	}
	else
	{
		g_gunB_ne[index].left=g_ne.left+8; 
		g_gunB_ne[index].top=g_ne.top-20;
		yi=-5;
	}

	
	while(1)
	{
		t_cnt++;
		if ( MAX_R_L >= g_gunB_ne[index].left || g_gunB_ne[index].right >= MAX_R_R-10) {
			xi*=-1;
		}

		if ( MAX_R_T >= g_gunB_ne[index].top || g_gunB_ne[index].bottom >= MAX_R_B-10) {
			yi*=-1;
		}

		g_gunB_ne[index].left+=xi;
		g_gunB_ne[index].top+=yi;
		g_gunB_ne[index].right = g_gunB_ne[index].left+20;
		g_gunB_ne[index].bottom = g_gunB_ne[index].top+20;

		Sleep(10);

		
		if(t_cnt==10000)
		{
			gunB_cnt_ne[index]=2;
			TerminateThread(H_GB_ne[index],0);
		}
		
		for(i=0;i<MAX_monA_r;i++)
		{
			for(j=0;j<MAX_monA_c;j++)
			{
				if(IntersectRect(&a,&g_gunB_ne[index],&g_monA[i][j]))
				{
					g_gunB_ne[index].left = MAX_M_R;
					g_gunB_ne[index].top = 0;
					g_gunB_ne[index].right = 0;
					g_gunB_ne[index].bottom = 0;
					gunB_cnt_ne[index]=2;
					TerminateThread(H_GB_ne[index],0);
					
				}
				else if(IntersectRect(&a,&g_gunB_ne[index],&g_monB[i][j]))
				{
					g_gunB_ne[index].left = MAX_M_R;
					g_gunB_ne[index].top = 0;
					g_gunB_ne[index].right = 0;
					g_gunB_ne[index].bottom = 0;
					gunB_cnt_ne[index]=2;
					TerminateThread(H_GB_ne[index],0);
					
				}
				else if(IntersectRect(&a,&g_gunB_ne[index],&g_monC))
				{
					g_gunB_ne[index].left = MAX_M_R;
					g_gunB_ne[index].top = 0;
					g_gunB_ne[index].right = 0;
					g_gunB_ne[index].bottom = 0;
					gunB_cnt_ne[index]=2;
					TerminateThread(H_GB_ne[index],0);
					
				}
			}
		}
	}
}

DWORD WINAPI itemA(LPVOID lp)
{
	int i;
	int xi,yi,ch;
	ch=(int)lp;

	srand(GetTickCount());
	
	if(ch==0)
	{
		g_itemA.left=rand()%MAX_R_R-10+10;
		g_itemA.top=MAX_R_T+10;
		xi=-15;  //이동거리
		yi=-5;
	}
	else if(ch==1)
	{
		g_itemA.left=rand()%MAX_R_R-10+10;
		g_itemA.top=MAX_R_T+10;
		xi=15;  
		yi=-5;
	}
	else if(ch==2)
	{
		g_itemA.left=rand()%MAX_R_R-10+10;
		g_itemA.top=MAX_R_T+10;
		xi=-10;  
		yi=-3;
	}
	else if(ch==3)
	{
		g_itemA.left=rand()%MAX_R_R-10+10;
		g_itemA.top=MAX_R_T+10;
		xi=10;  
		yi=-3;
	}
	else if(ch==4)
	{
		g_itemA.left=rand()%MAX_R_R-10+10;
		g_itemA.top=MAX_R_T+10;
		xi=4;  
		yi=-2;
	}
	else
	{
		g_itemA.left=rand()%MAX_R_R-10+10;
		g_itemA.top=MAX_R_T+10;
		xi=-4;  
		yi=-2;
	}

	while(1)
	{
		if ( MAX_R_L >= g_itemA.left || g_itemA.right >= MAX_R_R-10) {
			xi*=-1;
		}

		if ( MAX_R_T >= g_itemA.top || g_itemA.bottom >= MAX_R_B-10) {
			yi*=-1;
		}

		g_itemA.left+=xi;
		g_itemA.top+=yi;
		g_itemA.right = g_itemA.left+30;
		g_itemA.bottom = g_itemA.top+30;

		Sleep(10);

		if(IntersectRect(&a,&g_me,&g_itemA))
		{
			g_itemA.left = MAX_M_R;
			g_itemA.top = 0;
			g_itemA.right = 0;
			g_itemA.bottom = 0;	
			chk_itemA=0;
			for(i=0;i<MAX_gunB;i++)
			{
				if(gunB_cnt[i]==2)
				{	
					gunB_cnt[i]=0;
				}
			}
			ExitThread(0);
		}
		if(IntersectRect(&a,&g_ne,&g_itemA))
		{
			g_itemA.left = MAX_M_R;
			g_itemA.top = 0;
			g_itemA.right = 0;
			g_itemA.bottom = 0;	
			chk_itemA=0;
			for(i=0;i<MAX_gunB_ne;i++)
			{
				if(gunB_cnt_ne[i]==2)
				{	
					gunB_cnt_ne[i]=0;
				}
			}
			ExitThread(0);
		}

	}

}

void OnTimer()
{
	RECT crt;
	HDC hdc,hMemDC;
	HBITMAP OldBit;
	int i,j,k,tmp_right,tmp_left,total=0;

	GetClientRect(hWndMain,&crt);
	hdc=GetDC(hWndMain);

	if (hBit==NULL) {
		hBit=CreateCompatibleBitmap(hdc,crt.right,crt.bottom);
	}

	hMemDC=CreateCompatibleDC(hdc);
	OldBit=(HBITMAP)SelectObject(hMemDC,hBit);


	if(GameOver==1)
		DrawOVER(hMemDC);

	if(GameStart==1)
		DrawSTART(hMemDC);

	if(GameStart!=1 && GameOver!=1)
	{
		DrawBG(hMemDC);
		DrawitemA(hMemDC);
		DrawgunL(hMemDC);
		DrawgunR(hMemDC);
		DrawgunB(hMemDC);
		DrawgunL_ne(hMemDC);
		DrawgunR_ne(hMemDC);
		DrawgunB_ne(hMemDC);
		DrawME(hMemDC);
		DrawMonA(hMemDC);
		DrawMonB(hMemDC);
		DrawMonC(hMemDC);
		DrawMenu(hMemDC);
	
	}
	
	SelectObject(hMemDC,OldBit);
	DeleteDC(hMemDC);

	time++;
	if(time==100)
	{
		cho++;
		if(cho==60)
		{
			bun++;
			if(bun==60)
			{
				si++;
				bun=0;
			}
			cho=0;
		}
		time=0;
	}



	for(i=0;i<MAX_gunB;i++)
	{
		if(gunB_cnt[i]==2)
			total++;
		if(gunB_cnt[i]==0)
			total++;
	}
	for(i=0;i<MAX_gunB_ne;i++)
	{
		if(gunB_cnt_ne[i]==2)
			total++;
		if(gunB_cnt_ne[i]==0)
			total++;
	}
	gunB_total = total;

//////////////////////////// itemA ///////////////////////////
	itemA_time++;
	if(itemA_time%1000==0)
	{
		if(chk_itemA==0)
		{
			int ch=rand()%6+0;
			H_IA = CreateThread(NULL,0,itemA,(LPVOID)ch,NULL,NULL);
			chk_itemA=1;
			itemA_time=0;
		}
	}
////////////////////////////////////////////////////////////////           monC              ///////////////////////////////////////////////////

if(GameStart==0)
{	
	monC_time++;
	if(monC_time==2)
	{

		if(monC_re=='r')
		{
			g_monC.left += 10;
			g_monC.right += 10;
			if(g_monC.right>=MAX_R_R-10)
				monC_re='d';
		}
		else if(monC_re=='d')
		{
			g_monC.top +=10;
			g_monC.bottom += 10;
			if(g_monC.bottom>=MAX_R_B-40)
				monC_re='l';
		}
		else if(monC_re=='l')
		{
			g_monC.left -=10;
			g_monC.right -=10;

			if(g_monC.left<=MAX_R_L+10)
				monC_re='u';
		}
		else if(monC_re=='u')
		{
			g_monC.top -=10;
			g_monC.bottom -=10;
			if(g_monC.top<=MAX_R_T+50)
				monC_re='r';
		}
		monC_time=0;
	}

	
}


////////////////////////////////////////////////////////////////           monAB             ///////////////////////////////////////
	monAB_time++;

	if(monAB_time<=30000)
	{
		g_move.left =MAX_R_R/3+monAB_m_l;
		g_move.top =MAX_R_T+150;
		g_move.right=MAX_R_R/3+25+monAB_m_r;
		g_move.bottom= g_move.top+25;
		

		for(i=0;i<MAX_monA_r;i++)
		{
			for(j=0;j<MAX_monA_c;j++)
			{
				if(chk_monA[i][j] !=0)
				{
					g_monA[i][j].left=g_move.left;
					g_monA[i][j].top=g_move.top;
					g_monA[i][j].right=g_move.right;
					g_monA[i][j].bottom=g_move.bottom;
				}
			
				if(i==0 && j==MAX_monA_c-1)
					tmp_right=g_move.right;
				if(i==0 && j==0)
					tmp_left = g_move.left;
				g_move.left+=25;
				g_move.right+=25;
			}


			g_move.left =MAX_R_R/3+monAB_m_l;
			g_move.right=MAX_R_R/3+25+monAB_m_r;
			g_move.top+=25;
			g_move.bottom+=25;
		}

		g_move.left =MAX_R_R/3+65+monAB_m_l;
		g_move.top =MAX_R_T+100;
		g_move.right=MAX_R_R/3+65+25+monAB_m_r;
		g_move.bottom= g_move.top+25;

		for(i=0;i<MAX_monB_r;i++)
		{
			for(j=0;j<MAX_monB_c;j++)
			{
				if(chk_monB[i][j] !=0)
				{
					g_monB[i][j].left=g_move.left;
					g_monB[i][j].top=g_move.top;
					g_monB[i][j].right=g_move.right;
					g_monB[i][j].bottom=g_move.bottom;
				}
		
				if(i==0 && j==MAX_monB_c-1)
					tmp_right=g_move.right;
				if(i==0 && j==0)
					tmp_left = g_move.left;
				g_move.left+=25;
				g_move.right+=25;
			}


			g_move.left =MAX_R_R/3+65+monAB_m_l;
			g_move.right=MAX_R_R/3+65+25+monAB_m_r;
			g_move.top+=25;
			g_move.bottom+=25;
		}

		t_cnt++;
		if(t_cnt==30)
		{
			if(monAB_re=='r')
			{
				monAB_m_l +=20;
				monAB_m_r +=20;
				if(tmp_right>=MAX_R_R-100)
				{
					monAB_m_l-=20;
					monAB_m_r-=20;
					monAB_re='l';
				}
			}
			else if(monAB_re=='l')
			{
				monAB_m_l-=20;
				monAB_m_r-=20;
				if(tmp_left<=MAX_R_L+100)
				{
					monAB_m_l +=20;
					monAB_m_r +=20;
					monAB_re='r';
				}
			}
			t_cnt=0;
		}
	}
	else
	{
		if(player==1)
		{
			if(g_me.left != g_monA[monAB_move_r][monAB_move_c[0]].left)
			{
				if(g_me.left < g_monA[monAB_move_r][monAB_move_c[0]].left)
				{
					g_monA[monAB_move_r][monAB_move_c[0]].left -= 1;
					g_monA[monAB_move_r][monAB_move_c[0]].right -= 1;
				}
				else
				{
					g_monA[monAB_move_r][monAB_move_c[0]].left +=1;
					g_monA[monAB_move_r][monAB_move_c[0]].right +=1;
				}
			}
			if(g_me.top != g_monA[monAB_move_r][monAB_move_c[0]].top)
			{
				if(g_me.top < g_monA[monAB_move_r][monAB_move_c[0]].top)
				{
					g_monA[monAB_move_r][monAB_move_c[0]].top -= 1;
					g_monA[monAB_move_r][monAB_move_c[0]].bottom -= 1;
				}
				else 
				{
					g_monA[monAB_move_r][monAB_move_c[0]].top += 1;
					g_monA[monAB_move_r][monAB_move_c[0]].bottom+=1;
				}
			}

			if(g_me.left != g_monA[monAB_move_r][monAB_move_c[1]].left)
			{
				if(g_me.left < g_monA[1][monAB_move_c[1]].left)
				{
					g_monA[monAB_move_r][monAB_move_c[1]].left -= 1;
					g_monA[monAB_move_r][monAB_move_c[1]].right -= 1;
				}
				else
				{
					g_monA[monAB_move_r][monAB_move_c[1]].left +=1;
					g_monA[monAB_move_r][monAB_move_c[1]].right +=1;
				}
			}

			if(g_me.top != g_monA[monAB_move_r][monAB_move_c[1]].top)
			{
				if(g_me.top < g_monA[monAB_move_r][monAB_move_c[1]].top)
				{
					g_monA[monAB_move_r][monAB_move_c[1]].top -= 1;
					g_monA[monAB_move_r][monAB_move_c[1]].bottom -= 1;
				}
				else 
				{
					g_monA[monAB_move_r][monAB_move_c[1]].top += 1;
					g_monA[monAB_move_r][monAB_move_c[1]].bottom+=1;
				}
			}
			if(chk_monA[1][monAB_move_c[0]]==0 && chk_monA[1][monAB_move_c[1]]==0)
			{
				monAB_time=0;
				t_cnt=0;
				monAB_move_c[0]++;
				monAB_move_c[1]--;
				if(	monAB_move_c[0]==7 || monAB_move_c[1]==7)
				{
					monAB_move_r =0;
					monAB_move_c[0]=0;
					monAB_move_c[1]=14;
				}
			}
		}
		else
		{
			if(g_ne.left != g_monA[monAB_move_r][monAB_move_c[0]].left)
			{
				if(g_ne.left < g_monA[monAB_move_r][monAB_move_c[0]].left)
				{
					g_monA[monAB_move_r][monAB_move_c[0]].left -= 1;
					g_monA[monAB_move_r][monAB_move_c[0]].right -= 1;
				}
				else
				{
					g_monA[monAB_move_r][monAB_move_c[0]].left +=1;
					g_monA[monAB_move_r][monAB_move_c[0]].right +=1;
				}
			}
			if(g_ne.top != g_monA[monAB_move_r][monAB_move_c[0]].top)
			{
				if(g_ne.top < g_monA[monAB_move_r][monAB_move_c[0]].top)
				{
					g_monA[monAB_move_r][monAB_move_c[0]].top -= 1;
					g_monA[monAB_move_r][monAB_move_c[0]].bottom -= 1;
				}
				else 
				{
					g_monA[monAB_move_r][monAB_move_c[0]].top += 1;
					g_monA[monAB_move_r][monAB_move_c[0]].bottom+=1;
				}
			}

			if(g_me.left != g_monA[monAB_move_r][monAB_move_c[1]].left)
			{
				if(g_me.left < g_monA[1][monAB_move_c[1]].left)
				{
					g_monA[monAB_move_r][monAB_move_c[1]].left -= 1;
					g_monA[monAB_move_r][monAB_move_c[1]].right -= 1;
				}
				else
				{
					g_monA[monAB_move_r][monAB_move_c[1]].left +=1;
					g_monA[monAB_move_r][monAB_move_c[1]].right +=1;
				}
			}

			if(g_me.top != g_monA[monAB_move_r][monAB_move_c[1]].top)
			{
				if(g_me.top < g_monA[monAB_move_r][monAB_move_c[1]].top)
				{
					g_monA[monAB_move_r][monAB_move_c[1]].top -= 1;
					g_monA[monAB_move_r][monAB_move_c[1]].bottom -= 1;
				}
				else 
				{
					g_monA[monAB_move_r][monAB_move_c[1]].top += 1;
					g_monA[monAB_move_r][monAB_move_c[1]].bottom+=1;
				}
			}
			if(chk_monA[1][monAB_move_c[0]]==0 && chk_monA[1][monAB_move_c[1]]==0)
			{
				monAB_time=0;
				t_cnt=0;
				monAB_move_c[0]++;
				monAB_move_c[1]--;
				if(	monAB_move_c[0]==7 || monAB_move_c[1]==7)
				{
					monAB_move_r =0;
					monAB_move_c[0]=0;
					monAB_move_c[1]=14;
				}
			}
		}
	}
///////////////////////////////////////////////////////////////////////////       IntersectRect          ///////////////////////////////
		for(i=0;i<MAX_monA_r;i++)
		{
			for(j=0;j<MAX_monA_c;j++)
			{
				for(k=0;k<MAX_gunLR;k++)
				{
					if(IntersectRect(&a,&g_gunL[k],&g_monA[i][j]))
					{
						chk_monA[i][j]--;
						TotalScore+=10;
						if(chk_monA[i][j]<1)
						{
							monA_cnt--;

							g_monA[i][j].left=MAX_M_R;
							g_monA[i][j].top=0;
							g_monA[i][j].right=0;
							g_monA[i][j].bottom=0;
						}
					}
					else if(IntersectRect(&a,&g_gunR[k],&g_monA[i][j]))
					{
						chk_monA[i][j]--;
						TotalScore+=10;
						if(chk_monA[i][j]<1)
						{
							monA_cnt--;
							g_monA[i][j].left=MAX_M_R;
							g_monA[i][j].top=0;
							g_monA[i][j].right=0;
							g_monA[i][j].bottom=0;
						}
					}
				}
				for(k=0;k<MAX_gunB;k++)
				{
					if(IntersectRect(&a,&g_gunB[k],&g_monA[i][j]))
					{
				
						chk_monA[i][j]-=3;
						TotalScore+=10;
						if(chk_monA[i][j]<1)
						{
							monB_cnt--;
							g_monA[i][j].left=MAX_M_R;
							g_monA[i][j].top=0;
							g_monA[i][j].right=0;
							g_monA[i][j].bottom=0;
						}
					}
			
				}
				if(IntersectRect(&a,&g_me,&g_monA[i][j]))
				{
					GameOver=1;
					p1me_life--;
	
				}
/////////////////////////////////////////////////////////////////////////
				for(k=0;k<MAX_gunLR_ne;k++)
				{
					if(IntersectRect(&a,&g_gunL_ne[k],&g_monA[i][j]))
					{
						chk_monA[i][j]--;
						TotalScore+=10;
						if(chk_monA[i][j]<1)
						{
							monA_cnt--;

							g_monA[i][j].left=MAX_M_R;
							g_monA[i][j].top=0;
							g_monA[i][j].right=0;
							g_monA[i][j].bottom=0;
						}
					}
					else if(IntersectRect(&a,&g_gunR_ne[k],&g_monA[i][j]))
					{
						chk_monA[i][j]--;
						TotalScore+=10;
						if(chk_monA[i][j]<1)
						{
							monA_cnt--;
							g_monA[i][j].left=MAX_M_R;
							g_monA[i][j].top=0;
							g_monA[i][j].right=0;
							g_monA[i][j].bottom=0;
						}
					}
				}
				for(k=0;k<MAX_gunB_ne;k++)
				{
					if(IntersectRect(&a,&g_gunB_ne[k],&g_monA[i][j]))
					{
				
						chk_monA[i][j]-=3;
						TotalScore+=10;
						if(chk_monA[i][j]<1)
						{
							monB_cnt--;
							g_monA[i][j].left=MAX_M_R;
							g_monA[i][j].top=0;
							g_monA[i][j].right=0;
							g_monA[i][j].bottom=0;
						}
					}
			
				}
				if(IntersectRect(&a,&g_ne,&g_monA[i][j]))
				{
					GameOver=1;
					p2me_life--;
	
				}
			}
		}
		
		for(i=0;i<MAX_monB_r;i++)
		{
			for(j=0;j<MAX_monB_c;j++)
			{
				for(k=0;k<MAX_gunLR;k++)
				{
					if(IntersectRect(&a,&g_gunL[k],&g_monB[i][j]))
					{
						chk_monB[i][j]--;
						TotalScore+=10;
						if(chk_monB[i][j]<1)
						{
							monB_cnt--;
							g_monB[i][j].left=MAX_M_R;
							g_monB[i][j].top=0;
							g_monB[i][j].right=0;
							g_monB[i][j].bottom=0;
						}
					}
					else if(IntersectRect(&a,&g_gunR[k],&g_monB[i][j]))
					{
						chk_monB[i][j]--;
						TotalScore+=10;
						if(chk_monB[i][j]<1)
						{
							monB_cnt--;
							g_monB[i][j].left=MAX_M_R;
							g_monB[i][j].top=0;
							g_monB[i][j].right=0;
							g_monB[i][j].bottom=0;
						}
					}
				}
				for(k=0;k<MAX_gunB;k++)
				{
					if(IntersectRect(&a,&g_gunB[k],&g_monB[i][j]))
					{
				
						chk_monB[i][j]-=3;
						TotalScore+=10;
						if(chk_monB[i][j]<1)
						{
							monB_cnt--;
							g_monB[i][j].left=MAX_M_R;
							g_monB[i][j].top=0;
							g_monB[i][j].right=0;
							g_monB[i][j].bottom=0;
						}
					}
			
				}
				
				if(IntersectRect(&a,&g_me,&g_monB[i][j]))
				{
					GameOver=1;
					p1me_life--;
				}

////////////////////////////////////////////////////////////////////////
				for(k=0;k<MAX_gunLR_ne;k++)
				{
					if(IntersectRect(&a,&g_gunL_ne[k],&g_monB[i][j]))
					{
						chk_monB[i][j]--;
						TotalScore+=10;
						if(chk_monB[i][j]<1)
						{
							monB_cnt--;
							g_monB[i][j].left=MAX_M_R;
							g_monB[i][j].top=0;
							g_monB[i][j].right=0;
							g_monB[i][j].bottom=0;
						}
					}
					else if(IntersectRect(&a,&g_gunR_ne[k],&g_monB[i][j]))
					{
						chk_monB[i][j]--;
						TotalScore+=10;
						if(chk_monB[i][j]<1)
						{
							monB_cnt--;
							g_monB[i][j].left=MAX_M_R;
							g_monB[i][j].top=0;
							g_monB[i][j].right=0;
							g_monB[i][j].bottom=0;
						}
					}
				}
				for(k=0;k<MAX_gunB_ne;k++)
				{
					if(IntersectRect(&a,&g_gunB_ne[k],&g_monB[i][j]))
					{
				
						chk_monB[i][j]-=3;
						TotalScore+=10;
						if(chk_monB[i][j]<1)
						{
							monB_cnt--;
							g_monB[i][j].left=MAX_M_R;
							g_monB[i][j].top=0;
							g_monB[i][j].right=0;
							g_monB[i][j].bottom=0;
						}
					}
			
				}
				
				if(IntersectRect(&a,&g_me,&g_monB[i][j]))
				{
					GameOver=1;
					p2me_life--;
				}
			}
		}
		for(k=0;k<MAX_gunLR;k++)
		{
			if(IntersectRect(&a,&g_gunL[k],&g_monC))
			{
			
			}
			else if(IntersectRect(&a,&g_gunR[k],&g_monC))
			{
	
			}
		}
		if(IntersectRect(&a,&g_gunB[k],&g_monC))
		{
	
		}
		if(IntersectRect(&a,&g_me,&g_monC))
		{
			GameOver=1;
			p1me_life--;
		}
		if(IntersectRect(&a,&g_ne,&g_monC))
		{
			GameOver=1;
			p2me_life--;
		}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
	ReleaseDC(hWndMain,hdc);
	InvalidateRect(hWndMain,NULL,false);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	
	hWndMain = hWnd;
	HDC hdc,hMemDC;
	PAINTSTRUCT ps;
	HBITMAP OldBit;
	RECT crt;

	int i,j=0,tmp_right=0,tmp_left=0;

	char key;

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_CREATE:
			SetTimer(hWnd,1,10,NULL);

			GameStart=1;
			monAB_time=0;
			itemA_time=0;
			stage=1;

			p1gun_kind=1;
			p2gun_kind=1;

			gunL_index=0;
			gunR_index=0;
			gunB_index=0;

			gunL_index_ne=0;
			gunR_index_ne=0;
			gunB_index_ne=0;
			g_bg.top=1400;

			g_itemA.left = MAX_M_R;
			
			chk_itemA=0;
				
			TotalScore=0;		

			hBG=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_BG));
			hMe=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_me));
			hgunLR=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_gunLR));
			hgunB=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_gunB));
			hMonA=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_MA1));
			hMonA_1=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_MA1_1));
			hMonA_2=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_MA1_2));
			hMonB=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_MA2));
			hMonB_1=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_MA2_1));
			hMonB_2=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_MA2_2));
			hMonC=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_MC));
			hstart=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_START));
			hover=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_OVER));
			hmenu=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_MENU));
			hitemA=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP_IA));
				

			if(player==1)
			{
				g_me.left=MAX_R_R/2; 
				g_me.top = MAX_R_B-45;
				g_me.right=g_me.left+35;
				g_me.bottom=g_me.top+30;

				p1me_life--;
					
				g_itemA.left = MAX_M_R;

			}
			else
			{

				p1me_life--;
				g_me.left=MAX_R_R/2 +10; 
				g_me.top = MAX_R_B-45;
				g_me.right=g_me.left+35;
				g_me.bottom=g_me.top+30;
				

				p2me_life--;
				g_ne.left=MAX_R_R/2-45; 
				g_ne.top = MAX_R_B-45;
				g_ne.right=g_ne.left+35;
				g_ne.bottom=g_ne.top+30;
			}
			
			



			monC_re='r';


			g_monC.left = MAX_R_R/2;
			g_monC.right = MAX_R_R/2+30;
			g_monC.top = MAX_R_T+50;
			g_monC.bottom = g_monC.top+30;
			
			
			monAB_m_l=0;
			monAB_m_r=0;
			monAB_re='r';
			monAB_move_c[0]=0;
			monAB_move_c[1]=14;

			
			g_move.left =MAX_R_R/3;
			g_move.top =MAX_R_T+150;
			g_move.right=MAX_R_R/3+25;
			g_move.bottom= g_move.top+25;
			
		

			for(i=0;i<MAX_gunLR;i++)
			{
				TerminateThread(H_GL[i],0);
				TerminateThread(H_GR[i],0);
				gunL_cnt[i]=0;
				gunR_cnt[i]=0;
			}
			for(i=0;i<MAX_gunLR_ne;i++)
			{
				TerminateThread(H_GL_ne[i],0);
				TerminateThread(H_GR_ne[i],0);
				gunL_cnt_ne[i]=0;
				gunR_cnt_ne[i]=0;
			}
			for(i=0;i<MAX_gunB;i++)
			{
				TerminateThread(H_GB[i],0);
				gunB_cnt[i]=0;
			}
			for(i=0;i<MAX_gunB;i++)
			{
				TerminateThread(H_GB_ne[i],0);
				gunB_cnt_ne[i]=0;
			}


			for(i=0;i<MAX_monA_r;i++)
			{
				for(j=0;j<MAX_monA_c;j++)
				{
					chk_monA[i][j]=MAX_monA_life;

					g_monA[i][j].left=g_move.left;
					g_monA[i][j].top=g_move.top;
					g_monA[i][j].right=g_move.right;
					g_monA[i][j].bottom=g_move.bottom;
				
					if(i==0 && j==MAX_monA_c-1)
						tmp_right=g_move.right;
					if(i==0 && j==0)
						tmp_left = g_move.left;
					g_move.left+=25;
					g_move.right+=25;
				}


				g_move.left =MAX_R_R/3;
				g_move.right=MAX_R_R/3+25;
				g_move.top+=25;
				g_move.bottom+=25;
			}

			g_move.left =MAX_R_R/3+65;
			g_move.top =MAX_R_T+100;
			g_move.right=MAX_R_R/3+65+25;
			g_move.bottom= g_move.top+25;

			for(i=0;i<MAX_monB_r;i++)
			{
				for(j=0;j<MAX_monB_c;j++)
				{
					chk_monB[i][j]=MAX_monB_life;

					g_monB[i][j].left=g_move.left;
					g_monB[i][j].top=g_move.top;
					g_monB[i][j].right=g_move.right;
					g_monB[i][j].bottom=g_move.bottom;
			
					if(i==0 && j==MAX_monB_c-1)
						tmp_right=g_move.right;
					if(i==0 && j==0)
						tmp_left = g_move.left;
					g_move.left+=25;
					g_move.right+=25;
				}


				g_move.left =MAX_R_R/3+65;
				g_move.right=MAX_R_R/3+65+25;
				g_move.top+=25;
				g_move.bottom+=25;
			}
			
			for(i=0;i<MAX_gunLR;i++)
			{
				g_gunL[i].left=MAX_M_L;
				g_gunL[i].top=0;
				g_gunL[i].right=0;
				g_gunL[i].bottom=0;
				g_gunR[i].left=MAX_M_L;
				g_gunR[i].top=0;
				g_gunR[i].right=0;
				g_gunR[i].bottom=0;
				TerminateThread(H_GL[i],0);
				TerminateThread(H_GR[i],0);
			}
			for(i=0;i<MAX_gunB;i++)
			{
				g_gunB[i].left=MAX_M_L;
				g_gunB[i].top=0;
				g_gunB[i].right=0;
				g_gunB[i].bottom=0;
				TerminateThread(H_GB[i],0);
			}
			for(i=0;i<MAX_gunLR_ne;i++)
			{
				g_gunL_ne[i].left=MAX_M_L;
				g_gunL_ne[i].top=0;
				g_gunL_ne[i].right=0;
				g_gunL_ne[i].bottom=0;
				g_gunR_ne[i].left=MAX_M_L;
				g_gunR_ne[i].top=0;
				g_gunR_ne[i].right=0;
				g_gunR_ne[i].bottom=0;
				TerminateThread(H_GL_ne[i],0);
				TerminateThread(H_GR_ne[i],0);
			}
			for(i=0;i<MAX_gunB_ne;i++)
			{
				g_gunB_ne[i].left=MAX_M_L;
				g_gunB_ne[i].top=0;
				g_gunB_ne[i].right=0;
				g_gunB_ne[i].bottom=0;
				TerminateThread(H_GB_ne[i],0);
			}

			monA_cnt=MAX_monA_r*MAX_monA_c;
			monB_cnt=MAX_monB_r*MAX_monB_c;
		

			break;
		case WM_LBUTTONDOWN:
		
			
			break;
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_RETURN:
				if(GameOver==1)
				{
					KillTimer(hWnd,1);
					SendMessage(hWnd,WM_CREATE,NULL,NULL);
					GameOver=0;
					
				}
		
				break;
			}
			if(player==2 || player==1)
			{	
				switch(wParam)
				{
					case VK_LEFT:
						g_me.left -= 15;
						g_me.right -= 15;
						if(g_me.left < MAX_R_L)
						{
							g_me.left += 15; 
							g_me.right += 15;
						}
						break;
					case VK_RIGHT:
						g_me.left += 15;
						g_me.right += 15;
						if(g_me.right > MAX_R_R-10)
						{
							g_me.left -= 15;
							g_me.right -= 15;
						}
						break;
					case VK_DOWN:
						g_me.top += 15;
						g_me.bottom += 15;
						if(g_me.bottom > MAX_R_B)
						{
						g_me.top -= 15;
						g_me.bottom -= 15;
						}
						break;
					case VK_UP:
						g_me.top -= 15;
						g_me.bottom -= 15;
						if(g_me.top < MAX_R_T)
						{
							g_me.top += 15;
							g_me.bottom += 15;
						}
						break;
				}
			}
			if(player==2)
			{
				switch(wParam)
				{
					case VK_SHIFT:
						switch(p1gun_kind)
						{
						case 1:
							
							if(gunL_cnt[gunL_index]==0)
							{
								H_GL[gunL_index] = CreateThread(NULL,0,gunL,(LPVOID)gunL_index,NULL,NULL);
								gunL_cnt[gunL_index]=1;
							}
							else
							{
								gunL_index++;
								if(gunL_index==MAX_gunLR)
									gunL_index=0;
							}

							if(gunR_cnt[gunR_index] == 0)
							{
								H_GR[gunR_index] = CreateThread(NULL,0,gunR,(LPVOID)gunR_index,NULL,NULL);
								gunB_total--;
								gunR_cnt[gunR_index]=1;
								
							}
							else
							{
								gunR_index++;
								if(gunR_index==MAX_gunLR)
									gunR_index=0;
							}
				
									
							break;

						case 2:

							if(gunB_cnt[gunB_index]==0)
							{
								H_GB[gunB_index]=CreateThread(NULL,0,gunB,(LPVOID)gunB_index,NULL,NULL);
								gunB_cnt[gunB_index]=1;

								
							}
							else
							{
								gunB_index++;
								if(gunB_index==MAX_gunB)
									gunB_index=0;
							}
							break;
						}

					break;

					case VK_CONTROL:
						switch(p2gun_kind)
						{
						case 1:
							
							if(gunL_cnt_ne[gunL_index_ne]==0)
							{
								H_GL_ne[gunL_index_ne] = CreateThread(NULL,0,gunL_ne,(LPVOID)gunL_index_ne,NULL,NULL);
								gunL_cnt_ne[gunL_index_ne]=1;
							}
							else
							{
								gunL_index_ne++;
								if(gunL_index_ne==MAX_gunLR_ne)
									gunL_index_ne=0;
							}

							if(gunR_cnt_ne[gunR_index_ne] == 0)
							{
								H_GR_ne[gunR_index_ne] = CreateThread(NULL,0,gunR_ne,(LPVOID)gunR_index_ne,NULL,NULL);
								gunB_total_ne--;
								gunR_cnt_ne[gunR_index_ne]=1;
								
							}
							else
							{
								gunR_index_ne++;
								if(gunR_index_ne==MAX_gunLR_ne)
									gunR_index_ne=0;
							}
				
									
							break;

						case 2:

							if(gunB_cnt_ne[gunB_index_ne]==0)
							{
								H_GB_ne[gunB_index_ne]=CreateThread(NULL,0,gunB_ne,(LPVOID)gunB_index_ne,NULL,NULL);
								gunB_cnt_ne[gunB_index_ne]=1;

								
							}
							else
							{
								gunB_index_ne++;
								if(gunB_index_ne==MAX_gunB_ne)
									gunB_index_ne=0;
							}
							break;
						}

					break;


				}
			}
			if(player==1)
			{
				switch(wParam)
				{
					case VK_SPACE:
						switch(p1gun_kind)
						{
						case 1:
							
							if(gunL_cnt[gunL_index]==0)
							{
								H_GL[gunL_index] = CreateThread(NULL,0,gunL,(LPVOID)gunL_index,NULL,NULL);
								gunL_cnt[gunL_index]=1;
							}
							else
							{
								gunL_index++;
								if(gunL_index==MAX_gunLR)
									gunL_index=0;
							}

							if(gunR_cnt[gunR_index] == 0)
							{
								H_GR[gunR_index] = CreateThread(NULL,0,gunR,(LPVOID)gunR_index,NULL,NULL);
								gunB_total--;
								gunR_cnt[gunR_index]=1;
								
							}
							else
							{
								gunR_index++;
								if(gunR_index==MAX_gunLR)
									gunR_index=0;
							}
				
									
							break;

						case 2:

							if(gunB_cnt[gunB_index]==0)
							{
								H_GB[gunB_index]=CreateThread(NULL,0,gunB,(LPVOID)gunB_index,NULL,NULL);
								gunB_cnt[gunB_index]=1;

								
							}
							else
							{
								gunB_index++;
								if(gunB_index==MAX_gunB)
									gunB_index=0;
							}
							break;
						}
						break;
					}
				}
			break;
		case WM_CHAR:
			key=(TCHAR)wParam;
			if(GameStart==1)
			{
				switch(key)
				{
				case '1':
					player=1;
					break;
				case '2':
					player=2;
					break;
				}
				GameStart=0;
				SetTimer(hWnd,1,10,NULL);
				break;
			}
			if(player==1)
			{
				switch(key)
				{
				case '1':
					p1gun_kind=1;
					break;
				case '2':
					p1gun_kind=2;
					break;
				case '3':
					p1gun_kind=3;
					break;
				}
			}
			else//player==2
			{
				switch(key)
				{
				case 'p':
					p1gun_kind=1;
					break;
				case '[':
					p1gun_kind=2;
					break;
				case ']':
					p1gun_kind=3;
					break;

				case 'q':
					p2gun_kind=1;
					break;
				case 'w':
					p2gun_kind=2;
					break;
				case 'e':
					p2gun_kind=3;
					break;

				case 'f':
					g_ne.left -= 15;
					g_ne.right -= 15;
					if(g_me.left < MAX_R_L)
					{
						g_ne.left += 15; 
						g_ne.right += 15;
					}
					break;
				case 'h':
					g_ne.left += 15;
					g_ne.right += 15;
					if(g_me.right > MAX_R_R-10)
					{
						g_ne.left -= 15;
						g_ne.right -= 15;
					}
					break;
				case 't':
					g_ne.top -= 15;
					g_ne.bottom -= 15;
					if(g_me.top < MAX_R_T)
					{
						g_ne.top += 15;
						g_ne.bottom += 15;
					}
					break;
				case 'g':
					g_ne.top += 15;
					g_ne.bottom += 15;
					if(g_ne.bottom > MAX_R_B)
					{
					g_ne.top -= 15;
					g_ne.bottom -= 15;
					break;	
					}
				}
			}

			break;
		case WM_TIMER:
			
			OnTimer();
			break;
		case WM_PAINT:
			hdc=BeginPaint(hWnd, &ps);
			
			GetClientRect(hWnd,&crt);
			hMemDC=CreateCompatibleDC(hdc);
			OldBit=(HBITMAP)SelectObject(hMemDC, hBit);

			BitBlt(hdc,0,0,crt.right,crt.bottom,hMemDC,0,0,SRCCOPY);

			SelectObject(hMemDC, OldBit);
			DeleteDC(hMemDC);

			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			if (hBit) {
				DeleteObject(hBit);
			}
			DeleteObject(hBG);
			DeleteObject(hMe);
			DeleteObject(hgunLR);
			DeleteObject(hMonA);
			DeleteObject(hMonB);
			DeleteObject(hMonC);
			DeleteObject(hMonA_1);
			DeleteObject(hMonA_2);
			DeleteObject(hMonB_1);
			DeleteObject(hMonB_2);
			DeleteObject(hstart);
			DeleteObject(hover);
			DeleteObject(hmenu);
			DeleteObject(hitemA);
			PostQuitMessage(0);
			KillTimer(hWnd,1);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
