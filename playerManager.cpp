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
	for (int i = _eric->getEricProbeY(); i < _eric->getEricProbeY() + 10; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("worldMap")->getMemDC(), _eric->getEric().x + (_eric->getEric().image->getFrameWidth() / 2), i);

		int r = GetRValue(color);
		int g = GetRValue(color);
		int b = GetRValue(color);
		cout << "eric.x :" << _eric->getEric().x << endl;
		cout << "eric.y :" << _eric->getEric().y << endl;
		
		//cout << "r :" << r << "g :" << g << "b :" << b << endl;
		if (!(r == 255 && g == 0 && b == 255))
		{
			_eric->setEricY(i- _eric->getEric().image->getFrameHeight()/2);
			break;
		}

	}
}
