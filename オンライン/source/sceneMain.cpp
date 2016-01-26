#include	"iextreme.h"
#include	"system/system.h"
#include	"sceneMain.h"

cStage* sceneMain::stage;
cPlayerManager*	sceneMain::player;
cChat*	sceneMain::chat;

extern char	IPAddress[32];
extern char	PlayerName[32];
extern int	PlayerType;
extern cGameParam* GameParam;

#pragma comment( lib, "WSOCK32.lib")

//*****************************************************************************************************************************
//
//
//
//*****************************************************************************************************************************
bool sceneMain::Initialize()
{
	//	WinSock初期化
	WSADATA	wsaData;
	WSAStartup( MAKEWORD(1,1), &wsaData );

	//	環境設定
	iexLight::SetAmbient(0x404040);
	iexLight::SetFog( 800, 1000, 0 );

	Vector3 dir( 1.0f, -1.0f, -0.5f );
	iexLight::DirLight( shader, 0, &dir, 0.9f, 0.9f, 0.9f );

	gameParam = new cGameParam();
	GameParam = gameParam;

	//	カメラ初期化
	camera = new cCamera();
	//	プレイヤー初期化
	player = new cPlayerManager(gameParam);
	//	ステージ初期化
	stage = new cStage();

	chat = new cChat();

	//	BGM再生
//	bgm = IEX_PlayStreamSound("DATA\\SOUND\\FFX_1_20.ogg");
	bgm = NULL;

	if( gameParam->IntializeClient( IPAddress, 7000, PlayerName, PlayerType ) == false )
	{
		MessageBox( iexSystem::Window, "クライアント初期化失敗！", "ERROR!", MB_OK );
		PostQuitMessage(0);
		return false;
	}

	return true;
}

sceneMain::~sceneMain()
{
	delete	camera;
	delete	stage;
	delete	player;
	delete	gameParam;
	IEX_StopStreamSound(bgm);

	//	WinSock終了
	WSACleanup();
}

//*****************************************************************************************************************************
//
//		主処理
//
//*****************************************************************************************************************************
void	sceneMain::Update()
{
	gameParam->Update();
	player->Update();

	//	カメラ更新
	int	index = gameParam->getIndex();
	camera->SetPlayerPos( player->getPos(index) );
	camera->Update();
	stage->Update(camera->getPos());
	chat->Update();
}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************
void	sceneMain::Render( void )
{
	camera->Activate();

	stage->Render();
	player->Render();

	player->RenderName();
	chat->Render( gameParam->getCurMes() );
}



