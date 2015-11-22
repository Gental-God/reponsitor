#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
#include  <time.h>
#pragma comment(lib, "WS2_32.lib")
using namespace std;
int main(){
	//第一步：初始化网络
		time_t t = time(0); 
char tmp[64]; 
strftime( tmp, sizeof(tmp), " %X ",localtime(&t) ); 
puts( tmp ); 
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion,&wsaData);
	cout << "初始化网络中，请等待..."  <<tmp <<endl;
	
	//第二步：建立一个socket
	cout << "正在建立连接。。。。"<<   tmp << endl;
	SOCKET sClient = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	cout << "建立连接成功。。。。"<<   tmp << endl;
	

	//第三步:填充sockaddr_in结构
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	cout << "正在分配IP地址..."<< tmp << endl;
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	cout << "分配IP地址成功..."<< tmp << endl;
	cout << "正在分配端口..."<< tmp << endl;
	sin.sin_port = ntohs(16568);
	cout << "分配IP地址成功..."<< tmp << endl;



	//发送数据
 char     szBuf[256];
 cout << "建立连接成功..."<< tmp << endl;
 while ( true )
 {
	 cout   <<"请输入数据" <<   tmp << endl;

  cin >> szBuf;
  ::sendto( sClient, szBuf, strlen(szBuf), 0, (sockaddr*)&sin, sizeof(sin) );
  if(strcmp(szBuf, "exit") == 0 )
  {
	cout  <<"即将退出，请稍后。。。"<<   tmp <<endl;
   break;
  }
 }
 
 //关闭socket
 closesocket(sClient);
 cout << tmp<<"退出，成功" << tmp<< endl;
 WSACleanup();
 return 0;
}
