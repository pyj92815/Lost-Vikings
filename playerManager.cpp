#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // ¾à 

	_baleog = new playerbaleog;
	_baleog->init(70, 185);

	return S_OK;
}

void playerManager::update()
{
	_eric->update();
	_baleog->update();
}

void playerManager::release()
{
	_eric->release();
	_baleog->release();
}

void playerManager::render()
{
	_eric->render();
	_baleog->render();
}
