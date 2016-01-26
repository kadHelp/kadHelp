#include	"winsock.h"
#include	"SocketClient.h"
//*****************************************************************************************************************************
//
//		�Q�[���f�[�^�Ǘ�
//
//*****************************************************************************************************************************

//*****************************************************************************************************************************
//	�v���C���[�f�[�^
//*****************************************************************************************************************************
#define	PLAYER_MAX		100

//	�v���C���[��{���
typedef struct
{
	bool	bActive;
	int		type;
	char	name[17];
} PlayerInfo;

//	�v���C���[�p�����[�^
typedef struct
{
	Vector3 pos;
	float	angle;
	int		motion;
} PlayerParam;

//	�`���b�g�p�����[�^
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
	//	�������E���
	//------------------------------------------------------
	cGameParam();
	~cGameParam();
	bool IntializeClient( char* addr, int nPort, char* name, int type );
	void CloseClient();

	//------------------------------------------------------
	//	�f�[�^�X�V�i����M�j
	//------------------------------------------------------
	void Update();
	void Receive();

	//------------------------------------------------------
	//	�v���C���[�p�����[�^����
	//------------------------------------------------------
	void setPlayerParam( int id, PlayerParam& param );
	void setPlayerParam( int id, Vector3& pos, float angle, int motion );
	PlayerParam& getPlayerParam( int id ){ return playerParam[id]; }
	//------------------------------------------------------
	//	�v���C���[��񑀍�
	//------------------------------------------------------
	void  setPlayerInfo( int id, char* name, int type );
	void  RemovePlayerInfo( int id );

	bool  getPlayerActive( int id ){ return playerInfo[id].bActive; }
	int   getIndex(){ return myIndex; }
	int   getPlayerType( int id ){ return playerInfo[id].type; }
	char* getPlayerName( int id ){ return playerInfo[id].name; }

	//------------------------------------------------------
	//	�`���b�g�֘A
	//------------------------------------------------------
	void Chat( TCHAR chr );
	char* getCurMes(){ return mes; }

};

//*****************************************************************************************************************************
//
//		�f�[�^����M�p�\����
//
//*****************************************************************************************************************************

//	�V�K�Q�����
typedef struct
{
	char	com;
	int		id;
	int		type;
	char	name[17];
} NET_INFO;

//	�E�ޏ��
typedef struct {
	char  com;
	int	  id;
} NET_OUT;

//	�`���b�g���
typedef struct {
	char  com;
	int	  id;
	char  msg[50];
} NET_CHAT;

