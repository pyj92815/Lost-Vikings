#include "stdafx.h"
#include "introScene.h"

introScene::introScene()
{
	addIntroImage();	// 인트로에 쓰일 이미지를 셋팅하는 함수
}

introScene::~introScene()
{
}

HRESULT introScene::init()
{
	_introScene.scene_Number = 0;					// 현재 씬 넘버
	_introScene.scene_Image = new image;			// 이미지 공간 할당
	_introScene.scene_State = false;				// 이미지를 서서히 보여주는 상태 : false, 이미지를 서서히 사라지는 상태 : true
	_introScene.fade_In = 0;						// 알파에서 사용할 값
	_introScene.scene_Cnt = 0;						// 이미지가 완전히 보여졌을때 이미지를 사라지게 할때까지의 시간

	// 현재 씬 넘버를 이용하여 이미지를 찾아 넣는다.
	sprintf_s(_introScene.scene_Str, "Intro%d", _introScene.scene_Number);
	_introScene.scene_Image = IMAGEMANAGER->findImage(_introScene.scene_Str);

	// 씬 선택에서 사용할 렉트
	_introScene.scene_Select_rc[SS_GAME_START] = RectMakeCenter(WINSIZEX / 2 - 170, WINSIZEY / 2 - 10, 36, 40);
	_introScene.scene_Select_rc[SS_GAME_PASSWORD] = RectMakeCenter(WINSIZEX / 2 - 170, WINSIZEY / 2 + 30, 36, 40);
	_introScene.scene_Select_Image = IMAGEMANAGER->findImage("Intro_Select");
	_introScene.scene_Select_Image->setX(_introScene.scene_Select_rc[SS_GAME_START].left);
	_introScene.scene_Select_Image->setY(_introScene.scene_Select_rc[SS_GAME_START].top);

	return S_OK;
}

void introScene::release()
{
}

void introScene::update()
{
	setting_AlphaBlend();	// 알파 블랜에 사용할 연산
	Select_Key();			// 선택 키 설정
}

void introScene::render()
{
	IMAGEMANAGER->findImage("Intro_BG")->render(getMemDC(), 0, 0);

	if (_introScene.scene_Number < INTROIMAGESIZE - 1)
	{
		_introScene.scene_Image->alphaRender(getMemDC(), _introScene.fade_In);
	}
	else
	{
		_introScene.scene_Image->render(getMemDC(), 0, 0);

		_introScene.scene_Select_Image->render(getMemDC(),
			_introScene.scene_Select_Image->getX(), _introScene.scene_Select_Image->getY());
	}

	//Rectangle(getMemDC(), _introScene.scene_Select_rc[SS_GAME_START]);
	//Rectangle(getMemDC(), _introScene.scene_Select_rc[SS_GAME_PASSWORD]);
}

void introScene::addIntroImage()
{
	char keyName[20];								// 키값을 담을 변수
	char imageAddress[30];							// 이미지 경로를 담을 변수

	for (int i = 0; i < INTROIMAGESIZE; ++i)		// 인트로 이미지 개수만큼 반복한다.
	{
		sprintf_s(keyName, "Intro%d", i);
		sprintf_s(imageAddress, "./image/UI/Intro/Intro_%d.bmp", i);

		IMAGEMANAGER->addImage(keyName, imageAddress, WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	}

	// 기본 배경 이미지
	IMAGEMANAGER->addImage("Intro_BG", "./image/UI/Intro/Intro_BG.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	// 선택 이미지
	IMAGEMANAGER->addImage("Intro_Select", "./image/UI/Intro/Select_Icon.bmp", 36, 40, true, RGB(255, 0, 255));
}

void introScene::setting_AlphaBlend()
{
	// 인트로 이미지 최대 개수 - 1 까지는 알파 처리한다.
	if (_introScene.scene_Number < INTROIMAGESIZE - 1)
	{
		// _introScene.scene_State의 상태가 false일때는 이미지를 서서히 보이게 한다.
		if (!_introScene.scene_State)
		{
			if (_introScene.scene_State < 255)	_introScene.fade_In += 4;

			// 최대값인 255와 같거나 이상이라면 
			if (_introScene.fade_In >= 255)
			{
				_introScene.fade_In = 255;	// 255를 넘어갔을 경우 255로 보정해준다.

				_introScene.scene_Cnt++;

				// 만약 장면 카운트가 NEXTSCENECOUNT보다 크거나 같다면
				if (_introScene.scene_Cnt >= NEXTSCENECOUNT)
				{
					_introScene.scene_Cnt = 0;
					_introScene.scene_State = !_introScene.scene_State;

					if (_introScene.scene_Number == 3)
					{
						_introScene.scene_State = false;
						_introScene.scene_Number++;

						sprintf_s(_introScene.scene_Str, "Intro%d", _introScene.scene_Number);

						_introScene.scene_Image = IMAGEMANAGER->findImage(_introScene.scene_Str);
					}
				}
			}
		}

		// _introScene.scene_State의 상태가 true일때는 이미지를 서서히 사라지게 한다.
		if (_introScene.scene_State)
		{
			if (_introScene.fade_In > 0)  _introScene.fade_In -= 4;

			// 최소값인 0과 같거나 이하라면
			if (_introScene.fade_In <= 0)
			{
				_introScene.fade_In = 0;	// 0이하로 넘어갔을 경우 0으로 보정해준다.

				// 다음 장면을 위한 초기화
				_introScene.scene_State = !_introScene.scene_State;
				_introScene.scene_Number++;

				sprintf_s(_introScene.scene_Str, "Intro%d", _introScene.scene_Number);

				_introScene.scene_Image = IMAGEMANAGER->findImage(_introScene.scene_Str);
			}
		}
	}


	// 만약 인트로 이미지가 보여지고 있는 상황에서 특정키를 누르면
	// 다음 인트로 이미지로 넘어간다. 
	// 셀렉트 화면에서는 사용 못하게 예외처리 할것
}

void introScene::Select_Key()
{
	// 씬 넘버가 4일때만 실행한다.
	if (_introScene.scene_Number == 4)
	{
		
		if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown('W'))
		{
			if (!_introScene.scene_Change_pos)	
			{
				_introScene.scene_Select_Image->setX(_introScene.scene_Select_rc[SS_GAME_PASSWORD].left);
				_introScene.scene_Select_Image->setY(_introScene.scene_Select_rc[SS_GAME_PASSWORD].top);
			}

			if (_introScene.scene_Change_pos)
			{
				_introScene.scene_Select_Image->setX(_introScene.scene_Select_rc[SS_GAME_START].left);
				_introScene.scene_Select_Image->setY(_introScene.scene_Select_rc[SS_GAME_START].top);
			}

			_introScene.scene_Change_pos = !_introScene.scene_Change_pos;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN) || KEYMANAGER->isOnceKeyDown('S'))
		{
			if (!_introScene.scene_Change_pos)
			{
				_introScene.scene_Select_Image->setX(_introScene.scene_Select_rc[SS_GAME_PASSWORD].left);
				_introScene.scene_Select_Image->setY(_introScene.scene_Select_rc[SS_GAME_PASSWORD].top);
			}

			if (_introScene.scene_Change_pos)
			{
				_introScene.scene_Select_Image->setX(_introScene.scene_Select_rc[SS_GAME_START].left);
				_introScene.scene_Select_Image->setY(_introScene.scene_Select_rc[SS_GAME_START].top);
			}

			_introScene.scene_Change_pos = !_introScene.scene_Change_pos;
		}

		// 엔터를 입력한다면 해당 렉트의 씬으로 이동한다.
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// _introScene.scene_Change_pos의 값이 false라면 게임 스타트에 위치하고 있다. (키입력에서 빠져나올때 들어있는값이 바뀌기 때문에)
			if (!_introScene.scene_Change_pos)
			{
				SCENEMANAGER->set_SceneState(SS_STAGE);		// 상태를 바꿔주면서 씬을 전환해준다.
			}

			// 만약 true의 값을 가지고 있다면, 패스워드 위치에 있다.
			if (_introScene.scene_Change_pos)
			{

			}
		}
	}
}
