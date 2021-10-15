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
	
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f), &brush);

	return true;
}

void Graphics::DrawEllipse(FLOAT x, FLOAT y, int r, D2D1_COLOR_F color)
{
	brush->SetColor(color);
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), r, r);
	renderTarget->FillEllipse(ellipse, brush);
}

void Graphics::DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT width, D2D1_COLOR_F color)
{
	brush->SetColor(color);
	renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 0.5f);
}
