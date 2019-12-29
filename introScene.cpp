#include "stdafx.h"
#include "introScene.h"

introScene::introScene()
{
	addIntroImage();	// ��Ʈ�ο� ���� �̹����� �����ϴ� �Լ�
}

introScene::~introScene()
{
}

HRESULT introScene::init()
{
	_introScene.scene_Number = 0;					// ���� �� �ѹ�
	_introScene.scene_Image = new image;			// �̹��� ���� �Ҵ�
	_introScene.scene_State = false;				// �̹����� ������ �����ִ� ���� : false, �̹����� ������ ������� ���� : true
	_introScene.fade_In = 0;						// ���Ŀ��� ����� ��
	_introScene.scene_Cnt = 0;						// �̹����� ������ ���������� �̹����� ������� �Ҷ������� �ð�

	// ���� �� �ѹ��� �̿��Ͽ� �̹����� ã�� �ִ´�.
	sprintf_s(_introScene.scene_Str, "Intro%d", _introScene.scene_Number);
	_introScene.scene_Image = IMAGEMANAGER->findImage(_introScene.scene_Str);

	// �� ���ÿ��� ����� ��Ʈ
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
	setting_AlphaBlend();	// ���� ���� ����� ����
	Select_Key();			// ���� Ű ����
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
	char keyName[20];								// Ű���� ���� ����
	char imageAddress[30];							// �̹��� ��θ� ���� ����

	for (int i = 0; i < INTROIMAGESIZE; ++i)		// ��Ʈ�� �̹��� ������ŭ �ݺ��Ѵ�.
	{
		sprintf_s(keyName, "Intro%d", i);
		sprintf_s(imageAddress, "./image/UI/Intro/Intro_%d.bmp", i);

		IMAGEMANAGER->addImage(keyName, imageAddress, WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	}

	// �⺻ ��� �̹���
	IMAGEMANAGER->addImage("Intro_BG", "./image/UI/Intro/Intro_BG.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	// ���� �̹���
	IMAGEMANAGER->addImage("Intro_Select", "./image/UI/Intro/Select_Icon.bmp", 36, 40, true, RGB(255, 0, 255));
}

void introScene::setting_AlphaBlend()
{
	// ��Ʈ�� �̹��� �ִ� ���� - 1 ������ ���� ó���Ѵ�.
	if (_introScene.scene_Number < INTROIMAGESIZE - 1)
	{
		// _introScene.scene_State�� ���°� false�϶��� �̹����� ������ ���̰� �Ѵ�.
		if (!_introScene.scene_State)
		{
			if (_introScene.scene_State < 255)	_introScene.fade_In += 4;

			// �ִ밪�� 255�� ���ų� �̻��̶�� 
			if (_introScene.fade_In >= 255)
			{
				_introScene.fade_In = 255;	// 255�� �Ѿ�� ��� 255�� �������ش�.

				_introScene.scene_Cnt++;

				// ���� ��� ī��Ʈ�� NEXTSCENECOUNT���� ũ�ų� ���ٸ�
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

		// _introScene.scene_State�� ���°� true�϶��� �̹����� ������ ������� �Ѵ�.
		if (_introScene.scene_State)
		{
			if (_introScene.fade_In > 0)  _introScene.fade_In -= 4;

			// �ּҰ��� 0�� ���ų� ���϶��
			if (_introScene.fade_In <= 0)
			{
				_introScene.fade_In = 0;	// 0���Ϸ� �Ѿ�� ��� 0���� �������ش�.

				// ���� ����� ���� �ʱ�ȭ
				_introScene.scene_State = !_introScene.scene_State;
				_introScene.scene_Number++;

				sprintf_s(_introScene.scene_Str, "Intro%d", _introScene.scene_Number);

				_introScene.scene_Image = IMAGEMANAGER->findImage(_introScene.scene_Str);
			}
		}
	}


	// ���� ��Ʈ�� �̹����� �������� �ִ� ��Ȳ���� Ư��Ű�� ������
	// ���� ��Ʈ�� �̹����� �Ѿ��. 
	// ����Ʈ ȭ�鿡���� ��� ���ϰ� ����ó�� �Ұ�
}

void introScene::Select_Key()
{
	// �� �ѹ��� 4�϶��� �����Ѵ�.
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

		// ���͸� �Է��Ѵٸ� �ش� ��Ʈ�� ������ �̵��Ѵ�.
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// _introScene.scene_Change_pos�� ���� false��� ���� ��ŸƮ�� ��ġ�ϰ� �ִ�. (Ű�Է¿��� �������ö� ����ִ°��� �ٲ�� ������)
			if (!_introScene.scene_Change_pos)
			{
				SCENEMANAGER->set_SceneState(SS_STAGE);		// ���¸� �ٲ��ָ鼭 ���� ��ȯ���ش�.
			}

			// ���� true�� ���� ������ �ִٸ�, �н����� ��ġ�� �ִ�.
			if (_introScene.scene_Change_pos)
			{

			}
		}
	}
}
