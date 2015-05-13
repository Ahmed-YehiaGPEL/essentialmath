//===============================================================================
// @ IvIndexBufferDX11.cpp
// 
// Description
// ------------------------------------------------------------------------------
// Copyright (C) 2008  Elsevier, Inc.
//
// Implementation notes
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "IvIndexBufferDX11.h"
#include "IvTypes.h"
#include <stdio.h>

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ IvIndexBufferDX11::IvIndexBufferDX11()
//-------------------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------------------
IvIndexBufferDX11::IvIndexBufferDX11() : IvIndexBuffer(), mBufferPtr(0)
{
}	// End of IvIndexBufferDX11::IvIndexBufferDX11()

//-------------------------------------------------------------------------------
// @ IvIndexBufferDX11::~IvIndexBufferDX11()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
IvIndexBufferDX11::~IvIndexBufferDX11()
{
    Destroy();
}

//-------------------------------------------------------------------------------
// @ IvIndexBufferDX11::Create()
//-------------------------------------------------------------------------------
// Create the platform-specific data
//-------------------------------------------------------------------------------
bool
IvIndexBufferDX11::Create(unsigned int numIndices, void* data, IvDataUsage usage, ID3D11Device* device)
{
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.ByteWidth = sizeof(unsigned int)*numIndices;
	switch (usage)
	{
	default:
	case kDefaultUsage:
		indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		break;
	case kDynamicUsage:
		indexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		break;
	case kImmutableUsage:
		indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		break;
	}
	mUsage = usage;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	//*** replacement for D3DMANAGED?

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&indexBufferDesc, &initData, &mBufferPtr)))
	{
		mBufferPtr = 0;
		return false;
	}

	mNumIndices = numIndices;

	return true;
}

//-------------------------------------------------------------------------------
// @ IvIndexBufferDX11::Destroy()
//-------------------------------------------------------------------------------
// Destroy the platform-specific data
//-------------------------------------------------------------------------------
void
IvIndexBufferDX11::Destroy()
{
	if (mBufferPtr)
	{
		// clear the handle and any associated memory
		mBufferPtr->Release();
		mBufferPtr = 0;
	}
    
    mNumIndices = 0;
}

//-------------------------------------------------------------------------------
// @ IvIndexBufferDX11::MakeActive()
//-------------------------------------------------------------------------------
// Make this the active index buffer
//-------------------------------------------------------------------------------
bool
IvIndexBufferDX11::MakeActive(ID3D11DeviceContext* context)
{
    if ( mBufferPtr == 0 || mNumIndices == 0 )
        return false;
    
	context->IASetIndexBuffer(mBufferPtr, DXGI_FORMAT_R32_UINT, 0);
    
    return true;
}

//-------------------------------------------------------------------------------
// @ IvIndexBufferDX11::BeginLoadData()
//-------------------------------------------------------------------------------
// Lock down the buffer and start loading
// Returns pointer to client side data area
//-------------------------------------------------------------------------------
void *
IvIndexBufferDX11::BeginLoadData()
{
	if (mUsage == kImmutableUsage)
	{
		return NULL;
	}

	//*** fix
	return NULL;
}

//-------------------------------------------------------------------------------
// @ IvIndexBufferDX11::EndLoadData()
//-------------------------------------------------------------------------------
// Unlock the buffer, we're done loading
// Returns true if all went well
//-------------------------------------------------------------------------------
bool
IvIndexBufferDX11::EndLoadData()
{
	if (mUsage == kImmutableUsage)
	{
		return false;
	}

	//*** fix
	return false;
}
