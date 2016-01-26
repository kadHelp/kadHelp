#include	"GameParam.h"
#include	"stage.h"
#include	"camera.h"

#include	"player.h"

#include	"chat.h"

//*****************************************************************************************************************************
//
//		���C���V�[��
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
	//	������
	bool Initialize();
	//	�X�V�E�`��
	void Update();	//	�X�V
	void Render();	//	�`��

	//	�X�e�[�W����
	static float GetFloor( Vector3& pos ){ return stage->GetHeight(pos); }

	//	�v���C���[�֘A
	static void	SetPlayer( int id, int type ){ player->Set( id, type ); }
	static void	RemovePlayer( int id ){ player->Remove(id); }
	static Vector3	getPlayer2DPos( int id ){ return player->get2DPos(id); }

	//	�`���b�g
	static void setChat( int id, char*name, char* msg ){ chat->Set( id, name, msg ); }
};


