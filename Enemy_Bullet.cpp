#include "stdafx.h"
#include "Enemy_Bullet.h"


HRESULT Enemy_Bullet::init(float x1, float y1, float x2,float y2 )
{
	_image = IMAGEMANAGER->addImage("Enemy_Bullet", "./image./Enemy./Enemy_Bullet.bmp", 24, 24, true, RGB(255, 0, 255));
	_x = x1;
	_y = y2;
	_probeX = _x;
	_probeY = _y;
	_angle = getAngle(_x, _y, x2, y2);
	_rect = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	_isFire = true;

	return S_OK;
}

void Enemy_Bullet::release()
{
}

void Enemy_Bullet::update()
{
	bulletMove();
}

void Enemy_Bullet::render()
{
	_image->render(CAMERAMANAGER->getWorDC(), _x, _y);
}

void Enemy_Bullet::bulletMove()
{
	if (_isFire)
	{
		_x += cosf(_angle) * 3;
		_y -= sinf(_angle) * 3;
		_probeX = _x;

		_probeY = _y;
		_rect = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
		//probe();
	}
}

void Enemy_Bullet::probe()
{
	for (int i = _probeX - _image->getWidth();i < _probeX + _image->getWidth();++i)
	{
		for (int j = _probeY - _image->getHeight();i < _probeY + _image->getWidth();++j)
		{
			COLORREF COLOR = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), i, j);

			int r = GetRValue(COLOR);
			int g = GetGValue(COLOR);
			int b = GetBValue(COLOR);

			if ((r == 255 && g == 255 && b == 00) || (r == 255 && g == 0 && b == 0))
			{
				_isFire = false;
				break;
			}
		}
	}
}