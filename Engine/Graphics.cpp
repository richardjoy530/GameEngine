#pragma once

#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;

}

Graphics::~Graphics()
{
	if (factory)		factory->Release();
	if (renderTarget)	renderTarget->Release();
}

bool Graphics::Init(HWND hwnd)
{
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (result != S_OK)	return false;

	RECT rect;
	GetClientRect(hwnd, &rect);
	factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	return true;
}
