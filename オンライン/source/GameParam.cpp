#include	"iextreme.h"
#include	"system/system.h"
#include	"sceneMain.h"


//*****************************************************************************************************************************
//
//		�Q�[���f�[�^�Ǘ�
//
//*****************************************************************************************************************************

//*****************************************************************************************************************************
//		�l�b�g���[�N�N���C�A���g������
//*****************************************************************************************************************************
bool cGameParam::IntializeClient( char* addr, int nPort, char* name, int type )
{
	//	�N���C�A���g������
	InitializeUDP(nPort, addr);

	//	�^�C�v�Ɩ��O�̑��M
	NET_INFO info;
	info.com = 10;
	info.type = type;
	strcpy(info.name, name);
	//�T�[�o�[�Ƀv���C���[���𑗐M
	send((char*)&info, sizeof(info));



	//	�lID�擾
	int size = receive((char*)&info, sizeof(info));
	if (size <= 0){ return false; }
	myIndex = info.id;

	return true;
}

//	�E��
void cGameParam::CloseClient()
{
	char com = 11;
	send(&com, sizeof(char));

}

//*****************************************************************************************************************************
//		�Q�[���f�[�^�X�V�i�f�[�^����M�j
//*****************************************************************************************************************************

//------------------------------------------------------
//	�f�[�^��M
//------------------------------------------------------
void cGameParam::Receive()
{
	char data[256];
	//�f�[�^����M
	for (;;)
	{
		//��M
		int size = receive(data, 256);
		if (size <= 0){ break; }
		if (data[0] == -1){ break; }
		//�擪�o�C�g�ŕ���
		switch (data[0])
		{
		case 0://�L�����f�[�^
			setPlayerParam(
				*((int*)&data[1]),
				*((PlayerParam*)&data[5])
				);
			break;
		case 1:	//�`���b�g
		{
					NET_CHAT *chat = (NET_CHAT*)data;
					sceneMain::setChat(
						chat->id,
						getPlayerName(chat->id),
						chat->msg);
		}
			break;
		case 10://�V�K�Q��
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
//	�f�[�^���M
//------------------------------------------------------
void cGameParam::Update()
{
	//	�S�f�[�^��M
	Receive();

	//����
	float	axisX = KEY_GetAxisX() * 0.001f;
	float	axisY = -KEY_GetAxisY() * 0.001f;
	float	moveX = axisX*matView._11 + axisY*matView._13;
	float	moveZ = axisX*matView._31 + axisY*matView._33;

	//	�ړ��f�[�^���M
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
//		�������E���
//*****************************************************************************************************************************
cGameParam::cGameParam()
{
	//	�v���C���[�f�[�^������
	for( int id=0 ; id<PLAYER_MAX ; id++ ) playerInfo[id].bActive = false;
	//	�`���b�g������
	ptr = 0;
	for( int i=0 ; i<sizeof(mes) ; i++ ) mes[i] = '\0';
}

cGameParam::~cGameParam()
{
	CloseClient();
}

//*****************************************************************************************************************************
//		�v���C���[���ݒ�E����
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
//		�v���C���[�p�����[�^�ݒ�
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
//	�`���b�g����			
//------------------------------------------------------
void	cGameParam::Chat( TCHAR chr )
{











}
