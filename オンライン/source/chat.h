//*****************************************************************************
//
//		チャットクラス
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
	//	初期化・解放
	//------------------------------------------------------
	cChat();
	void Set( int id, char* name, char* msg );

	//------------------------------------------------------
	//	更新・描画
	//------------------------------------------------------
	void Update();
	void Render( char* curMes );
	void RenderLog();

};
