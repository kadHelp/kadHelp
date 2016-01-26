#include	"iextreme.h"
#include	"system/system.h"
#include	"resource.h"

//*****************************************************************************************************************************
//
//
//
//*****************************************************************************************************************************

char*	TypeStr[8] = { "êÌémÇPÅ|íj", "êÌémÇPÅ|èó", "êÌémÇQÅ|íj", "êÌémÇQÅ|èó", "ïêém" };
char	IPAddress[32];
char	PlayerName[32];
int		PlayerType;

//
//
//

void	SaveInfo( void )
{
	FILE*	fp;
	fp = fopen( "info.txt", "wt" );
	fprintf( fp, "%s\n%s\n%d\n", IPAddress, PlayerName, PlayerType ); 
	fclose( fp );
}

void	LoadInfo( HWND hDlg )
{
	char	ip[18], name[17];
	int		type;

	FILE*	fp;
	fp = fopen( "info.txt", "rt" );
	if( fp != 0 ){
		fscanf( fp, "%s%s%d", ip, name, &type ); 
		fclose( fp );

		SetDlgItemText( hDlg, IDC_IP,   ip );
		SetDlgItemText( hDlg, IDC_NAME, name );
		SendDlgItemMessage( hDlg, IDC_TYPE, CB_SETCURSEL, type, 0 );
	}
}

//
//
//

BOOL CALLBACK	DialogProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int		i;

	switch( uMsg ){
	case WM_INITDIALOG:
			/*	ÉRÉìÉ{É{ÉbÉNÉXê›íË		*/ 
			for( i=0 ; i<5 ; i++ ){
				SendDlgItemMessage( hDlg, IDC_TYPE, CB_ADDSTRING, 0, (LPARAM)TypeStr[i] );
			}
			SendDlgItemMessage( hDlg, IDC_TYPE, CB_SETCURSEL, 0, 0 );
			LoadInfo( hDlg );
			return TRUE;

	case WM_COMMAND:
		switch( LOWORD(wParam) ){
		case IDC_CONNECT:	//	ê⁄ë±É{É^Éì
							GetDlgItemText( hDlg, IDC_NAME, PlayerName, 32 );
							PlayerType = (BYTE)SendDlgItemMessage( hDlg, IDC_TYPE, CB_GETCURSEL, 0, 0 );
							GetDlgItemText( hDlg, IDC_IP, IPAddress, 32 );

							EndDialog( hDlg, TRUE );
							break;
		default:	return FALSE;
		}
		break;

	default:	return FALSE;
	}

	return TRUE;
}

//*****************************************************************************************************************************
//
//
//
//*****************************************************************************************************************************

void	CONFIG_Open( void )
{
	DialogBox( GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CONFIG), NULL, DialogProc );
}
