#include	"iextreme.h"
#include	"system.h"
#include	"Framework.h"

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//		�t���[�����[�N
//
//*****************************************************************************************************************************

//------------------------------------------------------
//		�������E���
//------------------------------------------------------
Framework::Framework( int FPSMode )
{
	this->FPSMode = FPSMode;

	scene = NULL;

	dwFrameTime = 0;
	dwGameFrame = 0;
}

Framework::~Framework()
{
	if( scene != NULL ) delete scene;
}


//*****************************************************************************************************************************
//		�X�V
//*****************************************************************************************************************************
bool Framework::Update()
{
	static 	DWORD	dwSec = 0;

	//	�v���Z�X���Ԏ擾
	FILETIME real_time;
	FILETIME creation_time;
	FILETIME exit_time;
	FILETIME kernel_time;
	FILETIME user_time;
	GetSystemTimeAsFileTime(&real_time);
	GetProcessTimes(GetCurrentProcess(), &creation_time, &exit_time, &kernel_time, &user_time);

	ULONGLONG work = *((ULONGLONG*) &kernel_time);
	work += *((ULONGLONG*) &user_time);
	//	���݂̃v���Z�X����(100�}�C�N���b�P��)	
	DWORD	CurrentTime = (DWORD)(work/1000);

	//	�t���[������
	if( CurrentTime < dwFrameTime+500 ) return false;

	//	�o�ߎ���
	DWORD	dTime = CurrentTime - dwFrameTime;
	if( dTime > 2000 ) dwFrameTime = CurrentTime;

	//	�X�L�b�v�^�C�v 
	switch( FPSMode ){
	case FPS_60:	bRender = TRUE;	break;
	case FPS_30:	if( dwGameFrame & 0x01 ) bRender=TRUE; else bRender=FALSE;
					break;
	case FPS_FLEX:	if( dTime > 500*2 ) bRender = FALSE; else bRender = TRUE;
					break;
	}

	//	�t���[�����ԍX�V
	dwFrameTime += 500;

	//	�b�ԃt���[�����ۑ�
	if( dwSec < CurrentTime ){
		dwFPS       = dwCurFrame;
		dwRenderFPS = dwRCurFrame;
		dwCurFrame  = dwRCurFrame = 0;
		dwSec += 10000;
	}
	dwCurFrame ++;	//	�t���[�����X�V
	dwGameFrame++;	//	�Q�[���t���[�����X�V

	//	�X�V����
	KEY_SetInfo();
	if( scene != NULL ) scene->Update();

	return true;
}

//*****************************************************************************************************************************
//		�`��
//*****************************************************************************************************************************
void Framework::Render()
{
	if( !bRender ) return;
	//	�V�[���J�n
	iexSystem::BeginScene(); 
	//	�V�[���`��
	if( scene != NULL ) scene->Render();

	//	�t���[���\��
#ifdef _DEBUG
	char	str[64];
	wsprintf( str, "FPS %03d / %03d\n", dwFPS, dwRenderFPS );
	IEX_DrawText( str, 10,10,200,20, 0xFFFFFF00 );
#endif

	// �V�[���I��
	iexSystem::EndScene();

	dwRCurFrame ++;	//	�`��t���[�����X�V
}
