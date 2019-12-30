#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	_eric = new playerEric;
	_eric->init(50, 185);  // 약 

	_baleog = new playerbaleog;
	_baleog->init(100, 185);

	_olaf = new PlayerOlaf;
	_olaf->init(180, 155);

	_P_type = 0;

	return S_OK;
}

void playerManager::update()
{
	switch (_P_type)
	{
	case ERIC:
		_eric->update();
		break;

	case BALEOG:
		_baleog->update();
		break;

	case OLAF:
		_olaf->update();
		break;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{
		_P_type++;
		if (_P_type > 2)
		{
			_P_type = 0;
		}
	}

	//_eric->update();
	//_baleog->update();
	//_olaf->update();

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
	for (int i = _eric->getEric().y; i < _eric->getEric().y + (_eric->getEric().image->getFrameHeight()); ++i)
	{
		COLORREF color = GetPixel(CAMERAMANAGER->getWorDC(), _eric->getEric().x + 45, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		// 이걸 지우니까 렉이 사라지는 매직
		//cout << "r :" << r << "g :" << g << "b :" << b << endl;
		if ((r == 255 && g == 255 && b == 0))
		{
			_eric->setEricY(i - (_eric->getEric().image->getFrameHeight()));
			break;
		}
	}
}
