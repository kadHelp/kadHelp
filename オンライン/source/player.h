//*****************************************************************************************************************************
//
//		プレイヤークラス
//
//*****************************************************************************************************************************
class cPlayer
{
private:
	iex3DObj*	obj;		//	モデル

	//------------------------------------------------------
	//	パラメータ
	//------------------------------------------------------
	int			type;		//	タイプ
	Vector3		pos;		//	座標
	float		angle;		//	方向

public:
	//------------------------------------------------------
	//	初期化・解放
	//------------------------------------------------------
	cPlayer( iex3DObj* obj );
	~cPlayer();

	//------------------------------------------------------
	//	更新・描画
	//------------------------------------------------------
	bool Update( PlayerParam& param );
	void Render();

	//------------------------------------------------------
	//	ゲッター・セッター
	//------------------------------------------------------
	Vector3 getPos(){ return pos; }
};


//*****************************************************************************************************************************
//
//		プレイヤー管理クラス
//
//*****************************************************************************************************************************
#define	POBJ_MAX		8

class cPlayerManager
{
private:
	iex3DObj*	obj[ POBJ_MAX ];		//	元モデル
	cPlayer*	player[ PLAYER_MAX ];	//	プレイヤークラス

	cGameParam* gameParam;
public:
	//------------------------------------------------------
	//	初期化・解放
	//------------------------------------------------------
	cPlayerManager( cGameParam* gameParam );
	~cPlayerManager();

	//------------------------------------------------------
	//	更新・描画
	//------------------------------------------------------
	void Update();
	void Render();
	void RenderName();

	//------------------------------------------------------
	//	プレイヤー生成
	//------------------------------------------------------
	void Set( int id, int type );
	void Remove( int id );

	//------------------------------------------------------
	//	ゲッター・セッター
	//------------------------------------------------------
	Vector3 getPos( int id ){ return player[id]->getPos(); }
	Vector3 get2DPos( int id );

};


