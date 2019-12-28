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
	// ¾À¸Å´ÏÀú¿¡ ¾ÀÀ» Ãß°¡ÇÑ´Ù.
	SCENEMANAGER->addScene("Intro", new introScene);
	SCENEMANAGER->addScene("Stage", new stageScene);

	// Ãâ·ÂÇÒ ¾ÀÀ» º¸³½´Ù.
	SCENEMANAGER->changeScene("Intro");

	return S_OK;
}

void scene_Manager::release()
{
}

void scene_Manager::update()
{
	SCENEMANAGER->update();
}

void scene_Manager::render()
{
	SCENEMANAGER->render();
}
