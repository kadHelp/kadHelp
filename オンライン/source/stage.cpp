#include	"iextreme.h"
#include	"Stage.h"

//*****************************************************************************
//
//		�X�e�[�W�N���X
//
//*****************************************************************************

//*****************************************************************************************************************************
//		�������E���
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
//		�X�V
//*****************************************************************************************************************************
void cStage::Update( Vector3& camera )
{
	sky->SetPos(camera);
	sky->Update();
}

//*****************************************************************************************************************************
//		�`��
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
//	���̍���
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
//	�ǔ���
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
	//	�����x�N�g���␳
	Vector3	m = move;
	float	md = move.Length();
	//	�ړ��x�N�g�����K��
	m.Normalize();

	//	�ǔ���
	Vector3 v = m;
	float d = Wall( p, v );
	if( d >=0 && d < md ){
		//	�@�����K��
		v.Normalize();
		float cc = (m.x*v.x + m.z*v.z);

		d = (md-d) * 1.05f;
		m = move - v*cc*d;
		md = m.Length();
		//	�i�s�����ă`�F�b�N
		v = m;
		v.Normalize();

		p = pos;
		d = Wall( p, v );
		if( d < .0f || d > md ){
			//	�ړ�
			p += m;
		}
	} else {
		p += move;
	}
	return p;
}


//*****************************************************************************************************************************
//	�؂�ւ�
//*****************************************************************************************************************************
void cStage::Change( char* map, char* collision )
{
	//	���݂̃��f�����
	if( obj  != NULL ) delete obj;
	if( objX != NULL ) delete objX;

	char	file[256];
	//	�\���X�e�[�W�ǂݍ���
	sprintf( file, "DATA\\BG\\%s", map );
	obj = new iexMesh(file);
	//	������X�e�[�W�ǂݍ���
	sprintf( file, "DATA\\BG\\%s", collision );
	objX = new iexMesh(file);
}
