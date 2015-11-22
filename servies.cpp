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
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion,&wsaData);
	cout << "初始化网络中，请等待"  <<tmp  <<endl;
	
	//第二步：建立一个socket
	SOCKET sServer = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	cout << "正在建立连接。。。。"<< tmp << endl;

	//第三步:填充sockaddr_in结构
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	cout << "即将分配端口..." << endl;
	sin.sin_port = htons(16568);
	cout << "分配端口成功" << endl;
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	//第四步：绑定套接字到一个本地地址
	cout << "正在绑定套接字，请稍等..."  <<endl;
	if(::bind(sServer,(LPSOCKADDR)&sin,sizeof(sin)) ==SOCKET_ERROR)
	{
		cout << "套接字绑定失败" <<  tmp<< endl;
		return 0;								//   four step:binding port	
	}
	cout << "套接字绑定成功"    << tmp << endl;
	cout << "等待接受数据" << tmp<< endl;

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
			cout << "接收到的数据是" << tmp << endl;
			cout<< szBuf << endl;
			if (strcmp(szBuf, "exit") == 0)
			{
				cout << "即将退出..."  << tmp << endl;
				break;
			}
		}
	}

	//six:  close socket
	closesocket(sServer);
	cout << "断开连接"  << tmp<< endl;
	WSACleanup();
	return 0;
}