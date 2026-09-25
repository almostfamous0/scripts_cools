#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <iostream> // ini yg Semalem
#include <d3dx9math.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <cmath>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma once using namespace std;

class RenderContext;
class RenderData;


struct CPlayers
{
float yaw;
float pitch;
D3DXVECTOR3 pos;
char unkno8[2704];
};
struct CRank
{
BYTE iRank;
};

struct CGrade
{
char szGrade[33];//21
};

struct CNames
{
char szNames[33];
};

struct CTeam
{
BYTE iTeam;
};


struct CHealth
{
float CurHP;
};

class PlayerInfo
{
public:
D3DXVECTOR3 origin;
};

class RenderContext
{
public:
RenderData* pRenderData; 
char unknown4[1076];
D3DXVECTOR3 bone;
D3DXVECTOR3 bone1;
D3DXVECTOR3 bone2;
};

class RenderData
{
public:
char unknown0[2400];
D3DXMATRIX ViewMatrix;
D3DXMATRIX ProjMatrix;
D3DXMATRIX World; 
D3DXMATRIX WorldView[80];
};


#define NAMESIZE 0x21
#define OFS_HEALTH 0x304
#define HPSIZE 0x1C
#define MAXPLAYERS 16
#define OFS_BASEPLAYER 0x66EE78
#define OFS_BASEPLAYER2 0x66EE44
#define OFS_Grade 4745
#define OFS_RDATA 0x18B0D4
#define PLAYERSIZE 0x11AC
#define OFS_NAMES 0x49B3
#define OFS_PLAYER 0x6184
#define OFS_TEAM 0x4E18
#define GradeSIZE 0x2A
//#include "Struct.h"
LPTSTR AZ = "I3GfxDx.dll";

#define CHAR_WIDTH 8
#define Q_COLOR_ESCAPE   '^'
#define Q_IsColorString(p)   ( p && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) != Q_COLOR_ESCAPE )
#define LR_WIDTH 1

DWORD dwGFX    = (DWORD)GetModuleHandle(AZ);
RenderContext *pRC    = (RenderContext*)(dwGFX + OFS_RDATA);

//LPDIRECT3DDEVICE9 npDevice;
D3DVIEWPORT9 Viewport;
LPD3DXFONT fName   = NULL;
LPD3DXFONT JAMTANGGAL =NULL;
LPD3DXFONT fSmall   = NULL;
LPD3DXLINE pLine   = NULL;
LPD3DXFONT Keterangan   = NULL;


int GetTeam(int MyT)
{
if (MyT == 0 ||
MyT == 2 || 
MyT == 4 || 
MyT == 6 || 
MyT == 8 || 
MyT == 10|| 
MyT == 12|| 
MyT == 14)
return 1;

else if (MyT == 1 ||
MyT == 3 || 
MyT == 5 || 
MyT == 7 || 
MyT == 9 || 
MyT == 11|| 
MyT == 13|| 
MyT == 15)
return 2;
return 0;
}



bool SEMPAXWTS(D3DVECTOR Player,D3DVECTOR &PlayerScaled)
{
D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
D3DXMATRIX identity;
D3DXVECTOR3 vScreen;
npDevice->GetViewport(&Viewport);
Viewport.X = Viewport.Y = 0;
Viewport.MinZ = 0;
Viewport.MaxZ = 1;
D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);

if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
{
PlayerScaled.x = vScreen.x;
PlayerScaled.y = vScreen.y ;
PlayerScaled.z = vScreen.z;

return true; 
}
return false;
}


#define WHITE D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED D3DCOLOR_ARGB(255, 255, 000, 000)
#define GREEN D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLUE D3DCOLOR_ARGB(255, 000, 000, 255)
#define BLACK D3DCOLOR_ARGB(150, 000, 000, 000)
#define mBLACK D3DCOLOR_ARGB(100, 000, 000, 205)
#define PURPLE D3DCOLOR_ARGB(255, 125, 000, 255)
#define GREY D3DCOLOR_ARGB(255, 128, 128, 128)
#define YELLOW D3DCOLOR_ARGB(255, 255, 255, 000)
#define ORANGE D3DCOLOR_ARGB(255, 255, 125, 000)
#define WHITE2 D3DCOLOR_ARGB(100, 255, 255, 255)
#define RED2 D3DCOLOR_ARGB(100, 255, 000, 000)
#define GREEN2 D3DCOLOR_ARGB(100, 000, 255, 000)
#define BLUE2 D3DCOLOR_ARGB(100, 000, 000, 255)
#define BLACK2 D3DCOLOR_ARGB(100, 000, 000, 000)
#define PURPLE2 D3DCOLOR_ARGB(100, 125, 000, 255)
#define GREY2 D3DCOLOR_ARGB(100, 128, 128, 128)
#define YELLOW2 D3DCOLOR_ARGB(100, 255, 255, 000)
#define ORANGE2 D3DCOLOR_ARGB(100, 255, 125, 000)
#define MAROON    D3DCOLOR_ARGB(255, 142, 30, 0)
#define LGRAY    D3DCOLOR_ARGB(255, 174, 174, 174) 
#define WHITE    D3DCOLOR_ARGB(255, 255, 255, 255)
#define PINK2    D3DCOLOR_ARGB(100, 255, 050, 250)
#define CYAN2    D3DCOLOR_ARGB(100, 000, 255, 255)
#define CYAN    D3DCOLOR_ARGB(255, 000, 255, 255)
#define Biru    D3DCOLOR_ARGB( 250, 25, 220, 251)
#define UNGU    D3DCOLOR_ARGB(255, 198, 000, 255)
#define LIME    D3DCOLOR_ARGB(120, 198, 255, 0)
#define SKYBLUE    D3DCOLOR_ARGB(120, 0, 180, 255)
#define TEAL    D3DCOLOR_ARGB(120, 0,   255, 255)
#define DGRAY    D3DCOLOR_ARGB(120, 71, 65, 64) 
#define BROWN2    D3DCOLOR_ARGB(120, 77, 46, 38)
#define SHIT    D3DCOLOR_ARGB(255, 74, 38, 38)


void DrawLine ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, float Health)
{   


DWORD HPcol = GREEN;
if (Health < 78 )HPcol = YELLOW;
if (Health < 55) HPcol = RED;
if (Health < 29) HPcol = RED2;
D3DXVECTOR2 vLine[ 2 ]; // 2 Poin
pLine->SetAntialias( 0 ); // Set Tepi

pLine->SetWidth( dwWidth ); // Lebar Dari Line
pLine->Begin();

vLine[ 0 ][ 0 ] = Xa; // Jadikan Point Menjadi Array
vLine[ 0 ][ 1 ] = Ya;
vLine[ 1 ][ 0 ] = Xb;
vLine[ 1 ][ 1 ] = Yb;

pLine->Draw( vLine, 2, HPcol ); // Draw Garis , Jumlah Garis , Warna Garis 
pLine->End(); // Selesai
}

void DrawLine2 ( long Xa, long Ya, long Xb, long Yb,DWORD Color)
{   

D3DXVECTOR2 vLine[ 2 ]; // 2 Poin
pLine->SetAntialias( 0 ); // Set Tepi

pLine->SetWidth( 1 ); // Lebar Dari Line
pLine->Begin();

vLine[ 0 ][ 0 ] = Xa; // Jadikan Point Menjadi Array
vLine[ 0 ][ 1 ] = Ya;
vLine[ 1 ][ 0 ] = Xb;
vLine[ 1 ][ 1 ] = Yb;

pLine->Draw( vLine, 2, Color ); // Draw Garis , Jumlah Garis , Warna Garis 
pLine->End(); // Selesai
}




void FillRGBBOX( float x, float y, float w, float h, D3DCOLOR color)
{
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;

D3DRECT rec = { x, y, x + w, y + h };
npDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}




void DrawBorder( float x, float y, float w, float h, int px, float Health)
{
DWORD HPcol = GREEN;
if (Health < 78 )HPcol = YELLOW;
if (Health < 55) HPcol = RED;
if (Health < 29) HPcol = RED2;
FillRGBBOX( x, (y + h - px), w, px, HPcol);
FillRGBBOX( x, y, px, h, HPcol);
FillRGBBOX( x, y, w, px, HPcol);
FillRGBBOX( (x + w - px), y, px, h, HPcol);   
}


void DrawStringH(float x, float y , DWORD color, const char *fmt, ...)
{ 

RECT FontPos = { x, y, x + 20, y + 10 };
char buf[1024] = {'\0'};
va_list va_alist;
va_start(va_alist, fmt);
vsprintf(buf, fmt, va_alist);
va_end(va_alist);
fName->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}

void HealthEqui(int x, int y, float Health)
{
const int SizeY[] = { 10,15,10,15,10,15,10,15,10,15,10,15,10,15,10,15,10,15,10,15};
const D3DCOLOR colours[] = { RED, RED, RED, RED, ORANGE, ORANGE, ORANGE, ORANGE, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLUE, BLUE };   // this is our order
int boxSizeX = 2;   // you can fiddle with the box size and gap between them
int boxSizeY = 6;
int boxGap = 1;
for ( int i = 0 ; i < 20; i++ )
{
if ( Health > ( 5 * i ) )
FillRGB(x,y, boxSizeX, SizeY[i],colours[i],npDevice);
else
FillRGB(x,y, boxSizeX, SizeY[i],GREY,npDevice);
//DrawBorder(x-1,y-1,50,6,1,BLACK,npDevice);
x = x + boxSizeX+ boxGap;   // will move to next tile 1 unit to the right
}
}
void DrawBoxESP( int x, int y, int w, int h, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
DrawBorder( x, y, w, h, 1, BorderColor, pDevice );
} 
void Healthbar(int x, int y, float Health)
{
DWORD HPcol = GREEN;
if (Health < 78 )HPcol = YELLOW;
if (Health < 55) HPcol = RED;
if (Health < 29) HPcol = RED2;
DrawBorder(x-1,y-1,50,6,1,BLACK,npDevice);
FillRGB(x,y,Health/2,4,HPcol,npDevice);
}

void MakeESPLine(D3DVECTOR center, float x1, float y1, float z1, float x2, float y2, float z2, D3DCOLOR color)
{
D3DVECTOR pointPos1 = {center.x + x1, center.y + y1, center.z + z1};
D3DVECTOR pointPos2 = {center.x + x2, center.y + y2, center.z + z2};
D3DVECTOR sxy1;
D3DVECTOR sxy2;
if (SEMPAXWTS(pointPos1, sxy1) && SEMPAXWTS(pointPos2,sxy2))
DrawLine2(sxy1.x, sxy1.y, sxy2.x, sxy2.y, color);
}

void Make3DBox(D3DVECTOR center, float w, float h, D3DCOLOR color)
{
//bottom
MakeESPLine(center, -w, -w, 0, w, -w, 0, color);
MakeESPLine(center, -w, -w, 0, -w, w, 0, color);
MakeESPLine(center, w, w, 0, w, -w, 0, color);
MakeESPLine(center, w, w, 0, -w, w, 0, color);

//middle
MakeESPLine(center, -w, -w, 0, -w, -w, h, color);
MakeESPLine(center, -w, w, 0, -w, w, h, color);
MakeESPLine(center, w, -w, 0, w, -w, h, color);
MakeESPLine(center, w, w, 0, w, w, h, color);

//top
MakeESPLine(center, -w, -w, h, w, -w, h, color);
MakeESPLine(center, -w, -w, h, -w, w, h, color);
MakeESPLine(center, w, w, h, w, -w, h, color);
MakeESPLine(center, w, w, h, -w, w, h, color);
} 
float FindDistance(D3DXVECTOR3 my,D3DXVECTOR3 other,CPlayers* pPlayer,CPlayers* pLocal)
{
return sqrt((pLocal->pos.x-pPlayer->pos.x)*(pLocal->pos.x-pPlayer->pos.x) + (pLocal->pos.y-pPlayer->pos.y)*(pLocal->pos.y-pPlayer->pos.y) + (pLocal->pos.z-pPlayer->pos.z)*(pLocal->pos.z-pPlayer->pos.z));
}

DWORD TeamColor;
bool DxInit    = false;

D3DVECTOR HeadPos;
D3DVECTOR FootPos;
D3DVECTOR ScreenPos;


void DrawESP()
{
DWORD dwI3EXEC    = (DWORD)GetModuleHandle("PointBlank.Exe");
unsigned long dwBase   = *(DWORD*)(dwI3EXEC + OFS_BASEPLAYER);
unsigned long dwBase2   = *(DWORD*)(dwI3EXEC + OFS_BASEPLAYER2);   
CTeam    *pTeam    = ((CTeam*)(dwBase + OFS_TEAM));

char *dis    = new char[33];
int ScreenCenterX = (Viewport.Width /2);
int ScreenCenterY = (Viewport.Height /2);
int ScreenBottomY = (Viewport.Height);

int MyTeam = GetTeam(pTeam->iTeam);

for (int i = 0; i <= MAXPLAYERS; i++)
{
//CNames    *pNames    = (CNames*)((dwBase + OFS_NAMES) + i * NAMESIZE);
CGrade *PGrade = (CGrade*) ((dwBase + OFS_Grade) + GradeSIZE * i);
CPlayers   *pPlayer   = (CPlayers*)((dwBase + OFS_PLAYER) + i * PLAYERSIZE);
CNames *PNames = (CNames*) ((dwBase + OFS_NAMES) + NAMESIZE * i);
CPlayers *pLocal    = (CPlayers*)((dwBase + OFS_PLAYER) + pTeam->iTeam * PLAYERSIZE);
CHealth    *pHealth   = (CHealth*)((dwBase2 + OFS_HEALTH) + i * HPSIZE);

int iTeam    = GetTeam(i);

HeadPos.x   =   pPlayer->pos.x;
HeadPos.y   =   1.5f + pPlayer->pos.y;
HeadPos.z   =   pPlayer->pos.z;
D3DXVECTOR3 xDistance = pPlayer->pos - pLocal->pos;
D3DXVECTOR3 MyDistance = pLocal->pos - pPlayer->pos;
float xaDistance = D3DXVec3Length(&xDistance );
float MyaDistance = D3DXVec3Length(&MyDistance );
FootPos.x   =   pPlayer->pos.x;
FootPos.y   =   pPlayer->pos.y;
FootPos.z   =   pPlayer->pos.z;

if (iTeam == MyTeam)continue;

if (iTeam == 1){ TeamColor = WHITE; } // warna ESP Box
else if (iTeam == 2){ TeamColor = WHITE; }    // warna ESP Box
else{ continue;}

if (SEMPAXWTS(pPlayer->pos,ScreenPos))
{
if (pHealth->CurHP > 1)
{

if (esphp == 1)

{
Healthbar((int)ScreenPos.x-23,(int)ScreenPos.y+15,pHealth->CurHP);
HealthEqui((int)ScreenPos.x-(10000/MyaDistance)/55,(int)ScreenPos.y+(35000/MyaDistance)/40,pHealth->CurHP);
DrawStringH((int)ScreenPos.x-40,(int)ScreenPos.y-0,BLUE," HP[%0.f] ",pHealth->CurHP); // ini work 

}
if(DBox == 1){ // 3D Box 
Make3DBox(HeadPos,1,1,RED);}

if (espbox == 1)
{
DrawBorder(ScreenPos.x-(10000/MyaDistance)/40,ScreenPos.y-(35000/MyaDistance)/40,50000/MyaDistance/6*2/40,50000/MyaDistance/3*2/40,1,pHealth->CurHP);
//DrawBorder(ScreenPos.x-(10000/MyaDistance)/40,ScreenPos.y-(35000/MyaDistance)/40,50000/MyaDistance/6*2/40,50000/MyaDistance/3*2/40,1,pHealth->CurHP);

}
if (LineESP ==1){
DrawLine(ScreenCenterX,ScreenCenterY+550,ScreenPos.x-10,ScreenPos.y+20,1,pHealth->CurHP);
}
if (espname == 1)
{
DrawStringH(ScreenPos.x+10,ScreenPos.y-55,TeamColor,"[%s]",PNames->szNames); //. ndak work
} // my ESP

if (HealthBarDD == 1)
{
DrawStringH(ScreenPos.x+10,ScreenPos.y-45,GREEN,"Clan : [%s] ",PGrade->szGrade); // ndak work
}
if (DistanceESP == 1)//esp destance
{
DrawStringH(ScreenPos.x+15,ScreenPos.y-15,YELLOW,"[Distance : %0.1f M]",FindDistance(pLocal->pos,pPlayer->pos,pPlayer,pLocal)); // ndak work
}   

}}}}

/*_________________________________________________  
