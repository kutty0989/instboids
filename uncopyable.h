#pragma once
#include	<windows.h>
#include	<d3d11.h>
#include	<vector>
#include	<wrl/client.h>
#include	<DirectXMath.h>
#include	<string>
#include	"dx11mathutil.h"
#include	"dx11util.h"
#include	"DX11Settransform.h"
#include	"Shader.h"
#include	"shaderhashmap.h"
#include"Application.h"
#include	"CDirectxGraphics.h"
#include <map>

class Uncopyable
{
protected:

	constexpr Uncopyable() = default;

	~Uncopyable() = default;

	Uncopyable(const Uncopyable&) = delete;

	Uncopyable& operator =(const Uncopyable&) = delete;
};