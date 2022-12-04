#pragma once
#include	<d3d11.h>
#include	<DirectXMath.h>
#include	"CDirectxGraphics.h"

CDirectXGraphics* GetDX11Obj();
ID3D11Device* GetDX11Device();
ID3D11DeviceContext*	GetDX11DeviceContext();
IDXGISwapChain* GetDX11SwapChain();
ID3D11SamplerState* GetDX11SampState();


void DX11LightInit(DirectX::XMFLOAT4 lightpos);
void DX11LightUninit();
void DX11LightUpdate(DirectX::XMFLOAT4 lpos);

bool DX11Init(HWND hwnd, int width, int height, bool fullscreen);
void DX11Uninit();
void DX11BeforeRender(float ClearColor[]);
void DX11AfterRender();

int DX11GetScreenWidth();
int DX11GetScreenHeight();

void TurnOffZbuffer();
void TurnOnZbuffer();

void TurnOnAlphablend();

void TurnOffAlphablend();

void TurnOnLeftScissor();
void TurnOnRightScissor();

void TurnOffScissor();

void TurnWire();

void TurnSolid();

