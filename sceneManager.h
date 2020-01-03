#pragma once
#include "singletonBase.h"
#include <map>

class gameNode;

// 진행중인 씬의 상태
enum SceneState
{
	SS_NONE,
	SS_PAUSE,
	SS_INTRO,
	SS_STAGE,
	SS_GAMEOVER,
	SS_STOP,
	SS_RESTART
};

enum PlayerName
{
	PN_Eric,
	PN_Baleog,
	PN_Olaf
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

	bool	  _YouDie[3];		// 캐릭터의 죽음을 관리한다.


public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	gameNode* addScene(string sceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);

	void set_SceneState(int state);							// 씬의 상태를 셋팅해준다.
	SceneState get_SceneState() { return _scene.state; }	// 씬의 상태를 불러온다.

	void SceneChange();										// 상태에 따라 씬을 바꿔준다.

	void set_PlayerLife(int type, bool dead) { _YouDie[type] = dead; }		// 플레이어 타입, 죽음 여부 (0 = 에릭, 1 = 벨로그, 2 = 올라프)
																			// 죽었다면 true의 값을 넣어준다.
	bool* get_PlayerLife() { return _YouDie; }
	

};

