#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // ¾à 

	return S_OK;
}

void playerManager::update()
{
	_eric->update();
}

void playerManager::release()
{
	_eric->release();
}

void playerManager::render()
{
	_eric->render();
}
