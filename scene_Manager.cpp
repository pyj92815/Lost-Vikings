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

	// ���� ó������ ��Ʈ�θ� ������� �Ѵ�.
	SCENEMANAGER->set_SceneState(SS_STAGE);

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