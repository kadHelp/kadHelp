#include	"iextreme.h"
#include	"system/system.h"
#include	"sceneMain.h"


//*****************************************************************************************************************************
//
//		ゲームデータ管理
//
//*****************************************************************************************************************************

//*****************************************************************************************************************************
//		ネットワーククライアント初期化
//*****************************************************************************************************************************
bool cGameParam::IntializeClient( char* addr, int nPort, char* name, int type )
{
	//	クライアント初期化
	InitializeUDP(nPort, addr);

	//	タイプと名前の送信
	NET_INFO info;
	info.com = 10;
	info.type = type;
	strcpy(info.name, name);
	//サーバーにプレイヤー情報を送信
	send((char*)&info, sizeof(info));



	//	個人ID取得
	int size = receive((char*)&info, sizeof(info));
	if (size <= 0){ return false; }
	myIndex = info.id;

	return true;
}

//	脱退
void cGameParam::CloseClient()
{
	char com = 11;
	send(&com, sizeof(char));

}

//*****************************************************************************************************************************
//		ゲームデータ更新（データ送受信）
//*****************************************************************************************************************************

//------------------------------------------------------
//	データ受信
//------------------------------------------------------
void cGameParam::Receive()
{
	char data[256];
	//データを受信
	for (;;)
	{
		//受信
		int size = receive(data, 256);
		if (size <= 0){ break; }
		if (data[0] == -1){ break; }
		//先頭バイトで分岐
		switch (data[0])
		{
		case 0://キャラデータ
			setPlayerParam(
				*((int*)&data[1]),
				*((PlayerParam*)&data[5])
				);
			break;
		case 1:	//チャット
		{
					NET_CHAT *chat = (NET_CHAT*)data;
					sceneMain::setChat(
						chat->id,
						getPlayerName(chat->id),
						chat->msg);
		}
			break;
		case 10://新規参入
		{
					NET_INFO *info;
					info = (NET_INFO*)data;
					setPlayerInfo(info->id, info->name, info->type);
		}
		case 11:
			break;
		}
	}
}

//------------------------------------------------------
//	データ送信
//------------------------------------------------------
void cGameParam::Update()
{
	//	全データ受信
	Receive();

	//方向
	float	axisX = KEY_GetAxisX() * 0.001f;
	float	axisY = -KEY_GetAxisY() * 0.001f;
	float	moveX = axisX*matView._11 + axisY*matView._13;
	float	moveZ = axisX*matView._31 + axisY*matView._33;

	//	移動データ送信
	struct{
		char com;
		float vx, vy;
	}SendData;

	SendData.com = 0;
	SendData.vx = moveX * 3;
	SendData.vy = moveZ * 3;
	send((char*)&SendData, sizeof(SendData));




}

//*****************************************************************************************************************************
//		初期化・解放
//*****************************************************************************************************************************
cGameParam::cGameParam()
{
	//	プレイヤーデータ初期化
	for( int id=0 ; id<PLAYER_MAX ; id++ ) playerInfo[id].bActive = false;
	//	チャット初期化
	ptr = 0;
	for( int i=0 ; i<sizeof(mes) ; i++ ) mes[i] = '\0';
}

cGameParam::~cGameParam()
{
	CloseClient();
}

//*****************************************************************************************************************************
//		プレイヤー情報設定・解除
//*****************************************************************************************************************************
void cGameParam::setPlayerInfo( int id, char* name, int type )
{
	playerInfo[id].bActive = true;
	playerInfo[id].type  = type;
	strcpy( playerInfo[id].name, name );

	sceneMain::SetPlayer( id, type );
}

void cGameParam::RemovePlayerInfo( int id )
{
	playerInfo[id].bActive = false;
	sceneMain::RemovePlayer( id );
}

//*****************************************************************************************************************************
//		プレイヤーパラメータ設定
//*****************************************************************************************************************************
void cGameParam::setPlayerParam( int id, Vector3& pos, float angle, int motion )
{
	playerParam[id].pos    = pos;
	playerParam[id].angle  = angle;
	playerParam[id].motion = motion;
}

void cGameParam::setPlayerParam( int id, PlayerParam& param )
{
	playerParam[id].pos    = param.pos;
	playerParam[id].angle  = param.angle;
	playerParam[id].motion = param.motion;
}

//------------------------------------------------------
//	チャット入力			
//------------------------------------------------------
void	cGameParam::Chat( TCHAR chr )
{











}
