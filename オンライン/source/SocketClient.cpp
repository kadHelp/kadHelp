#include	"SocketClient.h"
#pragma comment( lib, "wsock32.lib" )

//	�s�b�o�N���C�A���g������
bool SocketClient::InitializeTCP( WORD port, char* addr )
{
	//	�|�[�g���A�h���X�w��
	ZeroMemory( &server, sizeof(server) );
	server.sin_family = AF_INET;
	server.sin_port   = htons(port);

	struct hostent *host = gethostbyname(addr);

	server.sin_addr.S_un.S_addr = *((ULONG*)host->h_addr_list[0]);
	
	//	TCP�\�P�b�g�쐬
	sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( sock == INVALID_SOCKET ) return false;

	//	�^�C���A�E�g�ݒ�(1000ms)	
	int timeout = 1000;
	if( setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout) ) == SOCKET_ERROR ) return false;

	//	�T�[�o�[�ڑ�
	if( connect( sock, (sockaddr*)&server, sizeof(server) ) == SOCKET_ERROR ) return false;

	return true;
}


//	�t�c�o�N���C�A���g������
bool SocketClient::InitializeUDP( WORD port, char* addr )
{
	//	�T�[�o�[���ݒ� 	
	ZeroMemory( &server, sizeof(server) );
	server.sin_family=AF_INET;
	server.sin_port = htons(port);

	struct	hostent *host = gethostbyname(addr);
	server.sin_addr.S_un.S_addr = *((ULONG*)host->h_addr_list[0]);

	//	UDP�\�P�b�g�̍쐬	
	sock = socket( AF_INET, SOCK_DGRAM, 0);
	if( sock == INVALID_SOCKET ) return false;

	//	�^�C���A�E�g�ݒ�(1000ms)	
	int timeout = 1000;
	if( setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout) ) == SOCKET_ERROR ) return false;

	return true;
}

//		�f�[�^���M		
void SocketClient::send( char *data, int size )
{	
	sendto( sock, data, size, 0, (struct sockaddr *)&server, sizeof(server) );
}

//		�f�[�^��M		
int	SocketClient::receive( char *data, int size )
{
	int recvsize = recv( sock, data, size, 0 );
	//	�G���[(�^�C���A�E�g)����		
	if( recvsize == SOCKET_ERROR ) return 0;

	return recvsize;
}
