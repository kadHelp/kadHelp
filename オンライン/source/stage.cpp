#include	"iextreme.h"
#include	"Stage.h"

//*****************************************************************************
//
//		ステージクラス
//
//*****************************************************************************

//*****************************************************************************************************************************
//		初期化・解放
//*****************************************************************************************************************************
cStage::cStage()
{
	sky = new iexMesh("DATA\\STAGE\\SKY\\SKY.IMO");

	obj = new iexMesh("DATA\\STAGE\\FIELD.IMO");
	objX = new iexMesh("DATA\\STAGE\\FIELD.IMO");
}

cStage::~cStage()
{
	delete sky;
	delete obj;
	delete objX;
}

//*****************************************************************************************************************************
//		更新
//*****************************************************************************************************************************
void cStage::Update( Vector3& camera )
{
	sky->SetPos(camera);
	sky->Update();
}

//*****************************************************************************************************************************
//		描画
//*****************************************************************************************************************************
void cStage::Render()
{
	iexSystem::Device->SetRenderState(D3DRS_ZENABLE, FALSE );
	iexSystem::Device->SetRenderState(D3DRS_LIGHTING, FALSE );
	sky->Render(RS_LCOPY);
	iexSystem::Device->SetRenderState(D3DRS_ZENABLE, TRUE );
	iexSystem::Device->SetRenderState(D3DRS_LIGHTING, TRUE );
	obj->Render(RS_COPY);
}

//*****************************************************************************************************************************
//	床の高さ
//*****************************************************************************************************************************
float cStage::GetHeight( Vector3& pos )
{
	Vector3 p = pos + Vector3(0,100,0);
	Vector3	v( 0, -1, 0 );
	float	d = 150;
	Vector3	out;

	objX->RayPick( &out, &p, &v, &d );

	return out.y;
}

//*****************************************************************************************************************************
//	壁判定
//*****************************************************************************************************************************
float cStage::Wall( Vector3& pos, Vector3& v )
{
	Vector3	out;
	float	d = 50.0f;

	Vector3	p = pos;

	int n = objX->RayPick( &out, &p, &v, &d );
	if( n < 0 ) return 10000.0f;

	Vector3 vec = out - pos;
	vec.y = 0;
	d = vec.Length();

	return d;
}


Vector3	cStage::MoveCheck( Vector3& pos, Vector3& move )
{
	Vector3	p = pos;
	//	方向ベクトル補正
	Vector3	m = move;
	float	md = move.Length();
	//	移動ベクトル正規化
	m.Normalize();

	//	壁判定
	Vector3 v = m;
	float d = Wall( p, v );
	if( d >=0 && d < md ){
		//	法線正規化
		v.Normalize();
		float cc = (m.x*v.x + m.z*v.z);

		d = (md-d) * 1.05f;
		m = move - v*cc*d;
		md = m.Length();
		//	進行方向再チェック
		v = m;
		v.Normalize();

		p = pos;
		d = Wall( p, v );
		if( d < .0f || d > md ){
			//	移動
			p += m;
		}
	} else {
		p += move;
	}
	return p;
}


//*****************************************************************************************************************************
//	切り替え
//*****************************************************************************************************************************
void cStage::Change( char* map, char* collision )
{
	//	現在のモデル解放
	if( obj  != NULL ) delete obj;
	if( objX != NULL ) delete objX;

	char	file[256];
	//	表示ステージ読み込み
	sprintf( file, "DATA\\BG\\%s", map );
	obj = new iexMesh(file);
	//	当たりステージ読み込み
	sprintf( file, "DATA\\BG\\%s", collision );
	objX = new iexMesh(file);
}
