//*****************************************************************************
//
//		ステージクラス
//
//*****************************************************************************
class cStage {
private:
	iexMesh*	obj;
	iexMesh*	objX;

	iexMesh*	sky;

public:
	//------------------------------------------------------
	//	初期化・解放
	//------------------------------------------------------
	cStage();
	~cStage();
	//------------------------------------------------------
	//	更新・描画
	//------------------------------------------------------
	void Update( Vector3& camera );
	void Render();

	//------------------------------------------------------
	//	判定
	//------------------------------------------------------
	float GetHeight( Vector3& pos );
	float Wall( Vector3& pos, Vector3& v );

	Vector3	MoveCheck( Vector3& pos, Vector3& move );

	//------------------------------------------------------
	//	切り替え
	//------------------------------------------------------
	void Change( char* map, char* collision );
};
