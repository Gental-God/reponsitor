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
puts( tmp ); 
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion,&wsaData);
	cout << "��ʼ�������У���ȴ�..."  <<tmp <<endl;
	
	//�ڶ���������һ��socket
	cout << "���ڽ������ӡ�������"<<   tmp << endl;
	SOCKET sClient = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	cout << "�������ӳɹ���������"<<   tmp << endl;
	

	//������:���sockaddr_in�ṹ
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	cout << "���ڷ���IP��ַ..."<< tmp << endl;
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	cout << "����IP��ַ�ɹ�..."<< tmp << endl;
	cout << "���ڷ���˿�..."<< tmp << endl;
	sin.sin_port = ntohs(16568);
	cout << "����IP��ַ�ɹ�..."<< tmp << endl;



	//��������
 char     szBuf[256];
 cout << "�������ӳɹ�..."<< tmp << endl;
 while ( true )
 {
	 cout   <<"����������" <<   tmp << endl;

  cin >> szBuf;
  ::sendto( sClient, szBuf, strlen(szBuf), 0, (sockaddr*)&sin, sizeof(sin) );
  if(strcmp(szBuf, "exit") == 0 )
  {
	cout  <<"�����˳������Ժ󡣡���"<<   tmp <<endl;
   break;
  }
 }
 
 //�ر�socket
 closesocket(sClient);
 cout << tmp<<"�˳����ɹ�" << tmp<< endl;
 WSACleanup();
 return 0;
}
