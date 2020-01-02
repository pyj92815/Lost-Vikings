#include "stdafx.h"
#include "scene_Manager.h"

scene_Manager::scene_Manager()
{
}

scene_Manager::~scene_Manager()
{
}

HRESULT scene_Manager::init()
{

	// ���Ŵ����� ���� �߰��Ѵ�.
	SCENEMANAGER->addScene("Intro", new introScene);
	SCENEMANAGER->addScene("Stage", new stageScene);
	SCENEMANAGER->addScene("GameOver", new gameOverScene);

	// ���� ó������ ��Ʈ�θ� ������� �Ѵ�.
	SCENEMANAGER->set_SceneState(SS_INTRO);

	return S_OK;
}

void scene_Manager::release()
{
}

void scene_Manager::update()
{
	SCENEMANAGER->SceneChange();	// �� ���¿� ���� ���� �ٲ��ش�.
	SCENEMANAGER->update();
}

void scene_Manager::render()
{
	SCENEMANAGER->render();
}