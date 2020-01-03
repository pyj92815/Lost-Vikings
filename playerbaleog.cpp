#include "stdafx.h"
#include "playerbaleog.h"


playerbaleog::playerbaleog()
{
}

playerbaleog::~playerbaleog()
{
}

HRESULT playerbaleog::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("벨로그기본", "./image/Characters/baleog_idel_x3.bmp", 156, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("벨로그이동", "./image/Characters/baleog_move_x3.bmp", 744, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("벨로그칼1", "./image/Characters/baleog_sword1_x3.bmp", 444, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("벨로그칼2", "./image/Characters/baleog_sword2_x3.bmp", 444, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("화살준비", "./image/Characters/baleog_arrow1_x3.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("화살발사", "./image/Characters/baleog_arrow2_x3.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("밀기", "./image/Characters/baleog_push_x3.bmp", 372, 198, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("죽음", "./image/Characters/baleog_die_x3.bmp", 768, 192, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("낙하", "./image/Characters/baleog_air_x3.bmp", 168, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("독사", "./image/Characters/baleog_poison_x3.bmp", 186, 198, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("압사", "./image/Characters/baleog_pressdie_x3.bmp", 279, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미라사", "./image/Characters/baleog_mirra_x3.bmp", 216, 186, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("관통사", "./image/Characters/baleog_trapdie_x3.bmp", 288, 180, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사다리이동", "./image/Characters/baleog_ladder_x3.bmp", 321, 192, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사다리도착", "./image/Characters/bakeog_ladder_end_x3.bmp", 186, 192, 2, 1, true, RGB(255, 0, 255));

	_baleog.image = IMAGEMANAGER->findImage("벨로그기본");	//처음에는 기본 이미지 찾아놓고
	_baleog.image->setFrameY(0);
	_baleog.currentFrameX = _baleog.currentFrameY = 0;
	_baleog.state = STATE_IDLE;
	_baleog.posState = POSSTATE_GROUND;
	_baleog.x = x;
	_baleog.y = y;
	_baleog.hp = 3;
	_baleog.frameSpeed = 15;
	_baleog.frameCount = 0;
	_baleog.rc = RectMake(_baleog.x, _baleog.y, _baleog.image->getFrameWidth(), _baleog.image->getFrameHeight());
	_baleog.currentFrameX = _baleog.currentFrameY = 0;

	_notMove = false;	//활 시위 댕길 때 이동 못하게 하는 것


	_baleog.gravity = 0;	//중력
	_probeY = _baleog.y + _baleog.image->getHeight() / 2;

	//화살
	_ar = new arrow;
	_ar->init(300);
	/*_ar->init(300, 10);*/

	_moveSpeed = 5;

	_stop = false;

	return S_OK;
}

void playerbaleog::release()
{
}

void playerbaleog::update()
{

	// 비밀이동키
	//if (!_baleogAttack) hgKey();
	setBaleogImage();
	setBaleogPosImage();

	if (!_stop)
	{
		if (_stopControl)key();
		if (_stopControl) PixelCollision();

		PixelRightCollision();
		PixelLeftCollision();
	}

	_baleog.rc = RectMake(_baleog.x, _baleog.y, _baleog.image->getFrameWidth(), _baleog.image->getFrameHeight());

	
	
	/*setBaleogState();
	setBaleogPosState();*/

	



	//중력
	if (_baleog.posState == POSSTATE_AIR)
	{/*
		if (_baleog.currentFrameX != 0)
		{
			_baleog.currentFrameX = 0;
			_baleog.image->setFrameX(_baleog.currentFrameX);
		}
		else
		{*/
		_baleog.currentFrameX = 0;	//낙하하기 직전에 깜빡이는 문제 해결 하기 위해서 프레임 0에서 바로 시작하도록
		_baleog.image->setFrameX(_baleog.currentFrameX);	//프레임을 셋에 고정하는 예외처리 문장


		if (_baleog.gravity < 5)	_baleog.gravity += 0.7;
		_baleog.y += _baleog.gravity;
	}

	//프레임회전
	_baleog.frameCount++;


	//이구문 
	if (_baleog.state == STATE_BALEOG_SWORD1 || _baleog.state == STATE_BALEOG_SWORD2)
	{

		if (_baleog.state == STATE_BALEOG_SWORD1)
		{
			_baleogAttackMotion = true;
			

		}
		else
		{
			_baleogAttackMotion = false;
			

		}
		if (_baleog.frameCount > _baleog.frameSpeed - 5)
		{

			_baleog.currentFrameX++;
			_baleog.image->setFrameX(_baleog.currentFrameX);
			
			if (_baleog.image->getMaxFrameX() <= _baleog.currentFrameX)
			{
				_baleog.state = STATE_IDLE;
				_baleog.currentFrameX = 0;
				_baleog.image->setFrameX(_baleog.currentFrameX);
				_notMove = false;
			}

			if (_baleog.currentFrameX >= 1)//프레임 1이 넘어가면 칼질의 참격이 적용됌
			{
				_ar->blade(_baleog.x + _baleog.image->getFrameWidth() / 2,
					_baleog.y + _baleog.image->getFrameHeight() / 2, 20.f, _baleog.currentFrameY * PI, _baleog.currentFrameY, 40);
			}
			_baleog.frameCount = 0;
		}
	}
	else if (_baleog.state == STATE_BALEOG_ARROW_REDY)//활을 준비하면
	{
		//벨로그 프레임카운트가 돌아간다
		if (_baleog.frameCount >= _baleog.frameSpeed-5)	//프레임카운트가 15를 넘어가면
		{

			_baleog.image->setFrameX(_baleog.currentFrameX);//이미지 프레임셋은 currentFrameX변수로 셋팅한다
			//_baleog.currentFrameX++;

			if (_baleog.image->getMaxFrameX() > _baleog.currentFrameX) _baleog.currentFrameX++;
			//currentFrameX가 이미지 최대보다 작으면 currentFrameX++해서 돌아가도록

			if (_baleog.image->getMaxFrameX() < _baleog.currentFrameX)//currentFrameX가 이미지 최대보다 크면 불값은 꺼진다
			{
				/*
				if(_baleog.state == STATE_BALEOG_ARROW_REDY)*/
				//_baleog.currentFrameX = 3;
				_pullString = false;	//즉,이미지 프레임이 최대에 도착하면 이미지가 돌아가는 걸 멈추는 것
			}
			_baleog.frameCount = 0;	//프레임카운트 0으로 초기화
		}
	}
	else if (_baleog.state == STATE_BALEOG_ARROW_FIRE)//활을 쏘고나면
	{
		//벨로그 프레임카운트가 돌아간다
		if (_baleog.frameCount >= _baleog.frameSpeed-5)	//프레임카운트가 15를 넘어가면
		{

			_baleog.image->setFrameX(_baleog.currentFrameX);//이미지 프레임셋은 currentFrameX변수로 셋팅한다
			//_baleog.currentFrameX++;
			_baleog.state = STATE_IDLE;
			if (_baleog.image->getMaxFrameX() > _baleog.currentFrameX) _baleog.currentFrameX++;
			//currentFrameX가 이미지 최대보다 작으면 currentFrameX++해서 돌아가도록
			_notMove = false;

			_baleog.frameCount = 0;	//프레임카운트 0으로 초기화
		}
	}
	else
	{
		if (_baleog.frameCount > _baleog.frameSpeed)	//프레임카운트 > 프레임스피드 면
		{
			_baleog.currentFrameX++;
			_baleog.image->setFrameX(_baleog.currentFrameX);

			if (_baleog.currentFrameX > _baleog.image->getMaxFrameX())
			{
				if (_baleog.state == STATE_DIE ||
					_baleog.state == STATE_MIRRA ||
					_baleog.state == STATE_PRESSDIE ||
					_baleog.state == STATE_POISON ||
					_baleog.state == STATE_TRAPDIE)
				{
					_baleog.isDead = true;
				}
				else
				{
					_baleog.currentFrameX = 0;
				}
				_baleog.frameCount = 0;
			}


			if (_baleog.image->getMaxFrameX() < _baleog.currentFrameX)
			{

				_baleog.currentFrameX = 0;

			}
			_baleog.frameCount = 0;
		}
	}


	/*if (_count % 2 == 0 && _move.type != MT_BOSS &&
		_move.type != MT_BOSS2)
		if(_count % 2 == 0)
	{
		if (_baleog.currentFrameX >= _baleog.image->getMaxFrameX()) _baleog.currentFrameX = 0;

		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;
		_count = 0;
	}
*/

	_ar->update();

	baleogDie();

}

void playerbaleog::render()
{
	Rectangle(getMemDC(), _baleog.rc);
	_baleog.image->frameRender(CAMERAMANAGER->getWorDC(), _baleog.x, _baleog.y, _baleog.currentFrameX, _baleog.currentFrameY);



	_ar->render();

}

void playerbaleog::key()
{

	//이동
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (!_notMove)
		{
			_baleog.state = STATE_MOVE;
			_baleog.x += 5;
		}
		_baleog.currentFrameY = 0;

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_notMove)
		{
			_baleog.state = STATE_MOVE;
			_baleog.x -= 5;
		}
		_baleog.currentFrameY = 1;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_baleog.state = STATE_IDLE;
		_baleog.currentFrameX = 0;
		_baleog.image->setFrameX(_baleog.currentFrameX);
		_baleog.frameCount = 0;
	}

	////이동키 예외처리
	//if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	//{
	//	if (_baleog.state == STATE_MOVE )
	//		_baleog.state = STATE_IDLE;
	//	_baleog.image->setFrameY(0);
	//}
	//if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	//{
	//	if ((_baleog.state == STATE_MOVE && _baleog.currentFrameY == 1) ||
	//		(_baleog.state == STATE_BALEOG_SWORD1 && _baleog.currentFrameY == 1))
	//		_baleog.state = STATE_IDLE;
	//	_baleog.image->setFrameY(1);
	//}

	if (_baleog.posState == POSSTATE_GROUND) //낙하할 때 조작키는 이동만 가능하게 할려고
	{

		//공격키
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_notMove = true;	//칼 쓰는 동안 이동키 금지
			

			_baleog.currentFrameX = 0;
			_baleog.image->setFrameX(_baleog.currentFrameX);

			/*if (_baleog.currentFrameX >= 2)
			{
				_ar->blade(_baleog.x + _baleog.image->getFrameWidth() / 2,
					_baleog.y + _baleog.image->getFrameHeight() / 2, 20.f, _baleog.currentFrameY * PI, _baleog.currentFrameY, 40);
			}*/

			if (!_baleogAttackMotion)
			{
				_baleog.state = STATE_BALEOG_SWORD1;

			}
			if (_baleogAttackMotion)
			{
				_baleog.state = STATE_BALEOG_SWORD2;

			}
		}

		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_notMove = true;	//활시위 당기는 동안 이동키 금지
			_baleog.state = STATE_BALEOG_ARROW_REDY;
			if (!_pullString)
			{
				_baleog.currentFrameX = 0;	//불값이 켜지지 않았을 경우,프레임을 0으로 해준다.
				_pullString = true;		//D를 누르면 불값이 켜지는것
			}

		}

		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			_notMove = true;	//활쏘는 동안 이동키 금지
			_baleog.state = STATE_BALEOG_ARROW_FIRE;
			_baleog.currentFrameX = 0;


			_ar->fire(_baleog.x + _baleog.image->getFrameWidth() / 2,
				_baleog.y + _baleog.image->getFrameHeight() / 2, 10.f, _baleog.currentFrameY * PI, _baleog.currentFrameY,1800);


		}

	}

}
//
//void playerbaleog::setBaleogState()
//{
//	if (_baleog.hp == 0)
//	{
//		_baleog.state = STATE_DIE;
//	}
//
//
//	switch (_baleog.state)
//	{
//	case STATE_IDLE:
//		_baleog.image = IMAGEMANAGER->findImage("벨로그기본");
//		break;
//	case STATE_MOVE:
//		_baleog.image = IMAGEMANAGER->findImage("벨로그이동");
//		break;
//	case STATE_ERIC_JUMP:
//		break;
//	case STATE_ERIC_HEADBUTT:
//		break;
//	case STATE_OLAF_GUARD:
//		break;
//	case STATE_OLAF_FLY:
//		break;
//	case STATE_BALEOG_ARROW_REDY:
//		_baleog.image = IMAGEMANAGER->findImage("화살준비");
//		break;
//	case STATE_BALEOG_ARROW_FIRE:
//		_baleog.image = IMAGEMANAGER->findImage("화살발사");
//		break;
//	case STATE_BALEOG_SWORD1:
//		_baleog.image = IMAGEMANAGER->findImage("벨로그칼1");
//		break;
//	case STATE_BALEOG_SWORD2:
//		_baleog.image = IMAGEMANAGER->findImage("벨로그칼2");
//		break;
//	case STATE_PUSH:
//		_baleog.image = IMAGEMANAGER->findImage("밀기");
//		break;
//	case STATE_DIE:
//		_baleog.image = IMAGEMANAGER->findImage("죽음");
//		break;
//	case STATE_POISON:
//		_baleog.image = IMAGEMANAGER->findImage("독사");
//		break;
//	case STATE_MIRRA:
//		_baleog.image = IMAGEMANAGER->findImage("미라사");
//		break;
//	case STATE_PRESSDIE:
//		_baleog.image = IMAGEMANAGER->findImage("압사");
//		break;
//	case STATE_TRAPDIE:
//		_baleog.image = IMAGEMANAGER->findImage("관통사");
//		break;
//	case STATE_STEPLADDER:
//		_baleog.image = IMAGEMANAGER->findImage("사다리이동");
//		break;
//	case STATE_STEPLADDEREND:
//		_baleog.image = IMAGEMANAGER->findImage("사다리도착");
//		break;
//	}
//
//
//}

void playerbaleog::PixelCollision()
{/*
	_probeY = _baleog.y + _baleog.image->getHeight() / 2;*/
	//// 플레이어 왼쪽 영역 픽셀 검색
	//COLORREF getPixel_Left = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _baleog.rc.left, _baleog.rc.top);
	//int r_left = GetRValue(getPixel_Left);
	//int g_left = GetGValue(getPixel_Left);
	//int b_left = GetBValue(getPixel_Left);

	//// 플레이어 오른쪽 영역 픽셀 검색
	//COLORREF getPixel_Right = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _baleog.rc.right, _baleog.rc.top);
	//int r_right = GetRValue(getPixel_Right);
	//int g_right = GetGValue(getPixel_Right);
	//int b_right = GetBValue(getPixel_Right);

	//// 플레이어 위쪽 영역 픽셀 검색
	//COLORREF getPixel_Top = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_baleog.rc.right + _baleog.rc.left) / 2, _baleog.rc.top);
	//int r_top = GetRValue(getPixel_Top);
	//int g_top = GetGValue(getPixel_Top);
	//int b_top = GetBValue(getPixel_Top);

	//// 플레이어 아래 영역 픽셀 검색
	//for (int i = _probeY - 4; i < _probeY + 10; ++i)
	//{
	//	COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_baleog.rc.right + _baleog.rc.left) / 2, i);
	//	int r_bottom = GetRValue(getPixel_Bottom);
	//	int g_bottom = GetGValue(getPixel_Bottom);
	//	int b_bottom = GetBValue(getPixel_Bottom);

	//	if (!(r_bottom == 255 && g_bottom == 0 && b_bottom == 255))//마젠타가 아니면 중력 0으로 해서 멈춰주기
	//	{
	//		if (_baleog.gravity > 0)
	//		{
	//			_baleog.y -= (_baleog.gravity - 1);
	//			_baleog.gravity = 0;
	//		}

	//		_baleog.y = i - _baleog.image->getHeight() / 2;
	//		_baleog.posState = POSSTATE_GROUND;

	//		break;
	//	}
	//	else
	//	{
	//		_baleog.posState = POSSTATE_AIR;
	//		/*	_baleog.image = IMAGEMANAGER->findImage("낙하");*/
	//	}
	//}

	//=========================================================================
	_baleog.probeY = _baleog.y + _baleog.image->getFrameHeight();

	for (int i = _baleog.probeY - 6; i < _baleog.probeY + 10; ++i)
	{
		COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), (_baleog.rc.left + _baleog.rc.right) / 2, i);

		int r = GetRValue(getPixel_Bottom);
		int g = GetGValue(getPixel_Bottom);
		int b = GetBValue(getPixel_Bottom);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_baleog.y = i - _baleog.image->getFrameHeight();
			_baleog.posState = POSSTATE_GROUND;
			if (_baleog.gravity > 0)
			{
				_baleog.gravity = 0;
			}
			break;
		}
		else
		{
			_baleog.posState = POSSTATE_AIR;
		}
	}
}

void playerbaleog::setBaleogImage()
{
	if (_baleog.hp == 0)
	{
		_baleog.state = STATE_DIE;
		_stop = true;
	}


	switch (_baleog.state)
	{
	case STATE_IDLE:
		_baleog.image = IMAGEMANAGER->findImage("벨로그기본");
		break;
	case STATE_MOVE:
		_baleog.image = IMAGEMANAGER->findImage("벨로그이동");
		break;
	case STATE_ERIC_JUMP:
		break;
	case STATE_ERIC_HEADBUTT:
		break;
	case STATE_OLAF_GUARD:
		break;
	case STATE_OLAF_FLY:
		break;
	case STATE_BALEOG_ARROW_REDY:
		_baleog.image = IMAGEMANAGER->findImage("화살준비");
		break;
	case STATE_BALEOG_ARROW_FIRE:
		_baleog.image = IMAGEMANAGER->findImage("화살발사");
		break;
	case STATE_BALEOG_SWORD1:
		_baleog.image = IMAGEMANAGER->findImage("벨로그칼1");
		break;
	case STATE_BALEOG_SWORD2:
		_baleog.image = IMAGEMANAGER->findImage("벨로그칼2");
		break;
	case STATE_PUSH:
		_baleog.image = IMAGEMANAGER->findImage("밀기");
		break;
	case STATE_DIE:
		_baleog.image = IMAGEMANAGER->findImage("죽음");
		break;
	case STATE_POISON:
		_baleog.image = IMAGEMANAGER->findImage("독사");
		break;
	case STATE_MIRRA:
		_baleog.image = IMAGEMANAGER->findImage("미라사");
		break;
	case STATE_PRESSDIE:
		_baleog.image = IMAGEMANAGER->findImage("압사");
		break;
	case STATE_TRAPDIE:
		_baleog.image = IMAGEMANAGER->findImage("관통사");
		break;
	case STATE_STEPLADDER:
		_baleog.image = IMAGEMANAGER->findImage("사다리이동");
		break;
	case STATE_STEPLADDEREND:
		_baleog.image = IMAGEMANAGER->findImage("사다리도착");
		break;
	}
}

void playerbaleog::setBaleogPosImage()
{
	switch (_baleog.posState)
	{
	case POSSTATE_GROUND:

		break;
	case POSSTATE_AIR:
		_baleog.image = IMAGEMANAGER->findImage("낙하");
		break;

	case POSSTATE_STEPLADDER:
		_baleog.image = IMAGEMANAGER->findImage("사다리이동");
		break;

	case POSSTATE_LADDERFALL:
		_baleog.image = IMAGEMANAGER->findImage("사다리도착");
		break;
	}
}

void playerbaleog::PixelRightCollision()
{
	_baleog.probeX = _baleog.x + _baleog.image->getFrameWidth(); 
	COLORREF getPixel_RIGHT = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _baleog.probeX + 2, _baleog.y);

	int r = GetRValue(getPixel_RIGHT);
	int g = GetGValue(getPixel_RIGHT);
	int b = GetBValue(getPixel_RIGHT);

	if (!(r == 255 && g == 0 && b == 255))
	{
		if (_baleog.posState == POSSTATE_GROUND)
		{
			if (_baleog.state != STATE_PUSH)
			{
				_baleog.state = STATE_PUSH;
				_baleog.currentFrameX = 0;
				_baleog.image->setFrameX(0);
			}
		}
		_baleog.x = _baleog.probeX - _baleog.image->getFrameWidth();
	}
}

void playerbaleog::PixelLeftCollision()
{
	_baleog.probeX = _baleog.x - 3;

	COLORREF getPixel_LEFT = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _baleog.probeX, _baleog.y);

	int r = GetRValue(getPixel_LEFT);
	int g = GetGValue(getPixel_LEFT);
	int b = GetBValue(getPixel_LEFT);

	if (!(r == 255 && g == 0 && b == 255))
	{
		if (_baleog.posState == POSSTATE_GROUND)
		{
			if (_baleog.state != STATE_PUSH)
			{
				_baleog.state = STATE_PUSH;
				_baleog.currentFrameX = 0;
				_baleog.image->setFrameX(0);
			}
		}
		_baleog.x = _baleog.probeX + 6;
	}
}

//
//void playerbaleog::setBaleogPosState()
//{
//	switch (_baleog.posState)
//	{
//	case POSSTATE_GROUND:
//
//		break;
//	case POSSTATE_AIR:
//		_baleog.image = IMAGEMANAGER->findImage("낙하");
//		break;
//
//	case POSSTATE_STEPLADDER:
//		_baleog.image = IMAGEMANAGER->findImage("사다리이동");
//		break;
//
//	case POSSTATE_LADDERFALL:
//		_baleog.image = IMAGEMANAGER->findImage("사다리도착");
//		break;
//	}
//
//}

void playerbaleog::baleogDie()
{
	if (_baleog.hp == 0)
	{
		_baleog.state = STATE_DIE;
	}

}


HRESULT arrow::init(int arrowMax)
{
	_arrowMax = arrowMax;

	return S_OK;
}

void arrow::release()
{
}

void arrow::update()
{
	arrowMove(0);
}

void arrow::render()
{
	for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end(); ++_viArrow)
	{
		_viArrow->arrowImage->frameRender(CAMERAMANAGER->getWorDC(),
			_viArrow->rc.left,
			_viArrow->rc.top,
			_viArrow->arrowImage->getFrameX(), _viArrow->direction);

		_viArrow->count++;
		if (_viArrow->count % 5 == 0)
		{
			_viArrow->arrowImage->setFrameX(_viArrow->arrowImage->getFrameX() + 1);
			if (_viArrow->arrowImage->getFrameX() >= _viArrow->arrowImage->getMaxFrameX())
			{
				_viArrow->arrowImage->setFrameX(0);
			}

			_viArrow->count = 0;

		}
	}
}

void arrow::fire(float x, float y, float speed, float angle, int direction, float range)
{

	if (_arrowMax < _vArrow.size())return;
	tagArrow arrow;
	ZeroMemory(&arrow, sizeof(arrow));

	arrow.arrowImage = new image;
	arrow.arrowImage->init("./image/Characters/화살1.bmp", 0, 0, 126, 28, 3, 2, true, RGB(255, 0, 255));
	arrow.speed = speed;
	arrow.angle = angle;
	arrow.range = range;
	arrow.x = arrow.fireX = x;
	arrow.y = arrow.fireY = y;
	arrow.rc = RectMakeCenter(arrow.x, arrow.y,
		arrow.arrowImage->getFrameWidth(),
		arrow.arrowImage->getFrameHeight());
	arrow.direction = direction;

	_vArrow.push_back(arrow);
}

void arrow::blade(float x, float y, float speed, float angle, int direction, float range)
{
	if (_arrowMax < _vArrow.size())return;
	tagArrow arrow;
	ZeroMemory(&arrow, sizeof(arrow));

	arrow.arrowImage = new image;
	arrow.arrowImage->init("./image/Characters/화살1.bmp", 0, 0, 126, 28, 3, 2, true, RGB(255, 0, 255));
	arrow.speed = speed;
	arrow.angle = angle;
	arrow.range = range;
	arrow.x = arrow.fireX = x;
	arrow.y = arrow.fireY = y;
	arrow.rc = RectMakeCenter(arrow.x, arrow.y,
		arrow.arrowImage->getFrameWidth(),
		arrow.arrowImage->getFrameHeight());
	arrow.direction = direction;

	_vArrow.push_back(arrow);
}

void arrow::removeArrow(int arrNum)
{
	//_vArrow[arrNum].arrowImage->release();
	_vArrow.erase(_vArrow.begin() + arrNum);
}

void arrow::arrowMove(bool fire)
{
	if (fire == 0)
	{
		for (_viArrow = _vArrow.begin(); _viArrow != _vArrow.end();)
		{
			_viArrow->x += _viArrow->speed * cos(_viArrow->angle);
			_viArrow->y -= _viArrow->speed * sin(_viArrow->angle);

			_viArrow->rc = RectMakeCenter(_viArrow->x, _viArrow->y,
				_viArrow->arrowImage->getFrameWidth(),
				_viArrow->arrowImage->getFrameHeight());
			if (_viArrow->range < getDistance(_viArrow->x, _viArrow->y, _viArrow->fireX,
				_viArrow->fireY))
			{
				SAFE_RELEASE(_viArrow->arrowImage);
				SAFE_DELETE(_viArrow->arrowImage);
				_viArrow = _vArrow.erase(_viArrow);
			}
			else ++_viArrow;

		}

	}
}

