#include "stdafx.h"
#include "Enemy_Mummy.h"

void Enemy_Mummy::EnemyAction()
{
	_probeY = _y + _image->getFrameHeight() / 2;
	switch (_enemyState)
	{
	case EnemyState::IDLE:
		RECT temp;
		//ī�޶� ������ ���� SCOUT���·� ����
		if (IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::SCOUT;
		break;
	case EnemyState::SCOUT:
		
		Scout();				//�����̴� ����/�� �� ������ �ݴ������� ���ư����� �ϴ� �Լ�
		Move();					//�¿�� �����̰� �ϴ� �Լ�

		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_ericRect))
		{
			_enemyState = EnemyState::DISCOVERY;	//�÷��̾ �߰��ϸ� DISCOVERY���·� ����
			_playerRect = _ericRect;
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_olafRect))
		{
			_enemyState = EnemyState::DISCOVERY;	//�÷��̾ �߰��ϸ� DISCOVERY���·� ����
			_playerRect = _olafRect;
		}
		if (IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_baleogRect))
		{
			_enemyState = EnemyState::DISCOVERY;	//�÷��̾ �߰��ϸ� DISCOVERY���·� ����
			_playerRect = _baleogRect;
		}

		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//ī�޶� ������ ������ IDLE���·� ����
		break;
	case EnemyState::DISCOVERY:
		//���� ����
		
		_player.x = (_playerRect.left + _playerRect.right) / 2;
		_player.y = (_playerRect.top + _playerRect.bottom) / 2;
		if (_x > _player.x&&!_turn)
		{
			_turn_Num++;
			_turn = true;
		}
		else if (_x < _player.x&&!_turn)
		{
			_turn_Num++;
			_turn = true;
		}
		Scout();
		Move();
		if (!IntersectRect(&temp, &_enemy_DISCOVERY_Rect, &_playerRect))_enemyState = EnemyState::SCOUT;
		if (!IntersectRect(&temp, &_enemyRect, &_cameraRect)) _enemyState = EnemyState::IDLE;				//ī�޶� ������ ������ IDLE���·� ����
		break;
		break;
	case EnemyState::ATTACK:
		//�̹��� = ���� �̹����� �ٲٰ�
		//if(���� ������ �������� �̹����� �÷��̾ ������ �÷��̾� ���)
		break;
	case EnemyState::DIE:

		break;
	default:
		break;
	}

	switch (_enemyLR)
	{
	case EnemyLR::LEFT:
		_frameY = 1;
		break;
	case EnemyLR::RIGHT:
		_frameY = 0;
		break;
	default:
		break;
	}

	//���� �ٴڿ� �ٿ��ֱ� ����
	for (int i = _probeY - 20; i < _probeY + 200; ++i)
	{
		COLORREF getPixel_Bottom = GetPixel(IMAGEMANAGER->findImage("BG")->getMemDC(), _x, i);

		int r = GetRValue(getPixel_Bottom);
		int g = GetGValue(getPixel_Bottom);
		int b = GetBValue(getPixel_Bottom);

		if (r == 255 && g == 255 && b == 0)
		{
			_y = i - _image->getFrameHeight() / 2;
			break;
		}
	}

}

void Enemy_Mummy::Frame()
{
	switch (_enemyState)
	{
	case EnemyState::IDLE:
		_frameCount = 0;
		_frameX = 0;
		break;
	case EnemyState::SCOUT:
		_frameCount++;
		if (_frameCount >= 10)
		{
			_frameX++;
			if (_frameX > 5)
				_frameX = 0;
			_frameCount = 0;
		}
		break;
	case EnemyState::DISCOVERY:
		_frameCount++;
		if (_frameCount >= 10)
		{
			_frameX++;
			if (_frameX > 5)
				_frameX = 0;
			_frameCount = 0;
		}
		break;
	case EnemyState::ATTACK:
		break;
	case EnemyState::DIE:
		break;
	default:
		break;
	}
}
