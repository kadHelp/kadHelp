//*****************************************************************************
//
//		�`���b�g�N���X
//
//*****************************************************************************
typedef struct 
{
	char	msg[60];
	int		count;
} CHAT;


#define	LOG_MAX	12
typedef struct {
	char	Name[17];
	char	Mes[60];
} LOG;

class cChat {
private:
	CHAT	chat[PLAYER_MAX];
	LOG		Log[LOG_MAX];
public:
	//------------------------------------------------------
	//	�������E���
	//------------------------------------------------------
	cChat();
	void Set( int id, char* name, char* msg );

	//------------------------------------------------------
	//	�X�V�E�`��
	//------------------------------------------------------
	void Update();
	void Render( char* curMes );
	void RenderLog();

};
