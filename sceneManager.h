#pragma once
#include "singletonBase.h"
#include <map>

class gameNode;

// �������� ���� ����
enum SceneState
{
	SS_NONE,
	SS_PAUSE,
	SS_INTRO,
	SS_STAGE,
	SS_GAMEOVER,
	SS_STOP
};

struct SceneInfo
{
	SceneState	state;
};


class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode* _currentScene;
	mapSceneList _mSceneList;
	SceneInfo _scene;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	gameNode* addScene(string sceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);

	void set_SceneState(int state);					// ���� ���¸� �������ش�.
	SceneState get_SceneState() { return _scene.state; }	// ���� ���¸� �ҷ��´�.

	void SceneChange();								// ���¿� ���� ���� �ٲ��ش�.
};

