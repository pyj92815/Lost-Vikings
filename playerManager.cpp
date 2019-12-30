#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // ¾à 

	_baleog = new playerbaleog;
	_baleog->init(100, 185);

	_olaf = new PlayerOlaf;
	_olaf->init(180, 155);
	return S_OK;
}

void playerManager::update()
{
	_eric->update();
	_baleog->update();
	_olaf->update();
	setColisionFloor();
}

void playerManager::release()
{
	_eric->release();
	_baleog->release();
	_olaf->release();
}

void playerManager::render()
{
	_eric->render();
	_baleog->render();
	_olaf->render();
}

void playerManager::setColisionFloor()
{
<<<<<<< HEAD
	for (int i = _eric->getEric().y;  i < _eric->getEric().y + (_eric->getEric().image->getFrameHeight()); ++i)
=======
	for (int i = _eric->getEricProbeY(); i < _eric->getEricProbeY() + 450; ++i)
>>>>>>> b6db8201b7c119eae05dcf64b92b3daeed20d771
	{
		COLORREF color = GetPixel(CAMERAMANAGER->getWorDC(), _eric->getEric().x + 45, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		
		cout << "r :" << r << "g :" << g << "b :" << b << endl;
		if ((r == 255 && g == 255 && b ==0))
		{
			_eric->setEricY(i - _eric->getEric().image->getFrameHeight() );
			break;
		}

	}
}
