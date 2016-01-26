#include	"winsock.h"
#include	"SocketClient.h"
//*****************************************************************************************************************************
//
//		ゲームデータ管理
//
//*****************************************************************************************************************************

//*****************************************************************************************************************************
//	プレイヤーデータ
//*****************************************************************************************************************************
#define	PLAYER_MAX		100

//	プレイヤー基本情報
typedef struct
{
	bool	bActive;
	int		type;
	char	name[17];
} PlayerInfo;

//	プレイヤーパラメータ
typedef struct
{
	Vector3 pos;
	float	angle;
	int		motion;
} PlayerParam;

//	チャットパラメータ
typedef struct
{
	char	msg[50];
	int		count;
} ChatParam;

//*****************************************************************************************************************************
//
//
//
//*****************************************************************************************************************************

class cGameParam :public SocketClient
{
private:
	int		myIndex;

	PlayerInfo	playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];
	ChatParam	chatParam[PLAYER_MAX];
	
	int ptr;
	char mes[60];

public:
	//------------------------------------------------------
	//	初期化・解放
	//------------------------------------------------------
	cGameParam();
	~cGameParam();
	bool IntializeClient( char* addr, int nPort, char* name, int type );
	void CloseClient();

	//------------------------------------------------------
	//	データ更新（送受信）
	//------------------------------------------------------
	void Update();
	void Receive();

	//------------------------------------------------------
	//	プレイヤーパラメータ操作
	//------------------------------------------------------
	void setPlayerParam( int id, PlayerParam& param );
	void setPlayerParam( int id, Vector3& pos, float angle, int motion );
	PlayerParam& getPlayerParam( int id ){ return playerParam[id]; }
	//------------------------------------------------------
	//	プレイヤー情報操作
	//------------------------------------------------------
	void  setPlayerInfo( int id, char* name, int type );
	void  RemovePlayerInfo( int id );

	bool  getPlayerActive( int id ){ return playerInfo[id].bActive; }
	int   getIndex(){ return myIndex; }
	int   getPlayerType( int id ){ return playerInfo[id].type; }
	char* getPlayerName( int id ){ return playerInfo[id].name; }

	//------------------------------------------------------
	//	チャット関連
	//------------------------------------------------------
	void Chat( TCHAR chr );
	char* getCurMes(){ return mes; }

};

//*****************************************************************************************************************************
//
//		データ送受信用構造体
//
//*****************************************************************************************************************************

//	新規参加情報
typedef struct
{
	char	com;
	int		id;
	int		type;
	char	name[17];
} NET_INFO;

//	脱退情報
typedef struct {
	char  com;
	int	  id;
} NET_OUT;

//	チャット情報
typedef struct {
	char  com;
	int	  id;
	char  msg[50];
} NET_CHAT;

