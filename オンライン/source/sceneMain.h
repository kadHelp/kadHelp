#include	"GameParam.h"
#include	"stage.h"
#include	"camera.h"

#include	"player.h"

#include	"chat.h"

//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************

class	sceneMain : public Scene
{
private:
	cGameParam*	gameParam;
	cCamera*	camera;

	static cStage* stage;
	static cPlayerManager*	player;
	static cChat*	chat;

	LPDSSTREAM	bgm;
public:
	~sceneMain();
	//	初期化
	bool Initialize();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画

	//	ステージ判定
	static float GetFloor( Vector3& pos ){ return stage->GetHeight(pos); }

	//	プレイヤー関連
	static void	SetPlayer( int id, int type ){ player->Set( id, type ); }
	static void	RemovePlayer( int id ){ player->Remove(id); }
	static Vector3	getPlayer2DPos( int id ){ return player->get2DPos(id); }

	//	チャット
	static void setChat( int id, char*name, char* msg ){ chat->Set( id, name, msg ); }
};


