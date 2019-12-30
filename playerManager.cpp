#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // ¾à 

	_baleog = new playerbaleog;
	_baleog->init(100, 185);

	return S_OK;
}

void playerManager::update()
{
	_eric->update();
	_baleog->update();
	setColisionFloor();
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

void playerManager::setColisionFloor()
{
	for (int i = _eric->getEric().y; i < _eric->getEric().y + (_eric->getEric().image->getFrameHeight()); ++i)
	{
		COLORREF color = GetPixel(CAMERAMANAGER->getWorDC(), _eric->getEric().x + 45, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		cout << "r :" << r << "g :" << g << "b :" << b << endl;
		if ((r == 255 && g == 255 && b == 0))
		{
			_eric->setEricY(i - (_eric->getEric().image->getFrameHeight()));
			break;
		}
	}
}
