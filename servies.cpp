#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
#include  <time.h>
#pragma comment(lib, "WS2_32.lib")
using namespace std;
int main(){
	//��һ������ʼ������
	time_t t = time(0); 
char tmp[64]; 
strftime( tmp, sizeof(tmp), " %X ",localtime(&t) ); 
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion,&wsaData);
	cout << "��ʼ�������У���ȴ�"  <<tmp  <<endl;
	
	//�ڶ���������һ��socket
	SOCKET sServer = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	cout << "���ڽ������ӡ�������"<< tmp << endl;

	//������:���sockaddr_in�ṹ
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	cout << "��������˿�..." << endl;
	sin.sin_port = htons(16568);
	cout << "����˿ڳɹ�" << endl;
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	//���Ĳ������׽��ֵ�һ�����ص�ַ
	cout << "���ڰ��׽��֣����Ե�..."  <<endl;
	if(::bind(sServer,(LPSOCKADDR)&sin,sizeof(sin)) ==SOCKET_ERROR)
	{
		cout << "�׽��ְ�ʧ��" <<  tmp<< endl;
		return 0;								//   four step:binding port	
	}
	cout << "�׽��ְ󶨳ɹ�"    << tmp << endl;
	cout << "�ȴ���������" << tmp<< endl;

	//five: get message
	char szBuf[1024];
	sockaddr_in addr;
	int nLen = sizeof(addr);
	while(true)
	{
		int nRecv = recvfrom (sServer,szBuf,1024,0,(sockaddr*)&addr,&nLen);
		if(nRecv>0)
		{
			szBuf[nRecv] = '\0';
			cout << "���յ���������" << tmp << endl;
			cout<< szBuf << endl;
			if (strcmp(szBuf, "exit") == 0)
			{
				cout << "�����˳�..."  << tmp << endl;
				break;
			}
		}
	}

	//six:  close socket
	closesocket(sServer);
	cout << "�Ͽ�����"  << tmp<< endl;
	WSACleanup();
	return 0;
}