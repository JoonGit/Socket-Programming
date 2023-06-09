//#include <iostream>
//#include <winsock2.h>
//#pragma comment(lib, "ws2_32")
//
//DWORD WINAPI ThreadFunction(LPVOID pParam)
//{
//	char szBuffer[128] = { 0 };
//	int nReceive = 0;
//	SOCKET hClient = (SOCKET)pParam;
//
//	printf("%d 클라이언트가 연결되었습니다 \n", hClient);
//
//	// 클라이언트로부터 문자열을 수신한다
//	while ((nReceive = ::recv(hClient, szBuffer, sizeof(szBuffer), 0)) > 0)
//	{
//		// 수신한 문자열을 그대로 반향(Echo)전송.
//		::send(hClient, szBuffer, sizeof(szBuffer), 0);
//		puts(szBuffer); fflush(stdout);
//		memset(szBuffer, 0, sizeof(szBuffer));
//	}
//
//	printf("%d 클라이언트 연결이 끊겼습니다 \n", hClient);
//	::closesocket(hClient);
//
//	return 0;
//}
//
//int main()
//{
//	// 원속 초기화
//	// 윈도우즈 소켓 라이브러리 초기화
//	WSADATA wsa = { 0 };
//	if (::WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//	{
//		puts("ERROR: 원속을 초기화 할 수 없습니다.");
//		return 0;
//	}
//
//	// 1. 접속 대기 소겟 생성
//	SOCKET hSocket = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (hSocket == INVALID_SOCKET)
//	{
//		puts("ERROR: 접속 대기 소켓을 생성할 수 없습니다.");
//		return 0;
//	}
//	// * 바인딩 전에 IP주소와 포트를 재사용하도록 소켓 옵션을 변경한다.
//	BOOL bOption = TRUE;
//	if (::setsockopt(hSocket, SOL_SOCKET,
//		SO_REUSEADDR, (char*)&bOption, sizeof(BOOL)) == SOCKET_ERROR)
//	{
//		puts("ERROR: 소켓 옵션을 변경할 수 없습니다.");
//	}
//
//	// 2. 포트 바인딩
//	SOCKADDR_IN svraddr = { 0 };
//	svraddr.sin_family = AF_INET;
//	svraddr.sin_port = htons(25000);
//	svraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	if (::bind(hSocket, (SOCKADDR*)&svraddr, sizeof(svraddr)) == SOCKET_ERROR)
//	{
//		puts("ERROR: 리슨 상태로 전환할 수 없습니다.");
//		return 0;
//	}
//
//
//
//	// 3. 접속대기 상태로 전환
//	// server는 Listen 상태가 된다
//	if (::listen(hSocket, SOMAXCONN) == SOCKET_ERROR)
//	{
//		puts("ERROR: 리슨 상태로 전환할 수 없습니다.");
//		return 0;
//	}
//	else
//	{
//		puts("Listen State");
//	}
//
//	// 4. 클라이언트 접속 처리 및 대응
//	SOCKADDR_IN clientaddr = { 0 };
//	int nAddrLen = sizeof(clientaddr);
//	SOCKET hClient = 0;
//	DWORD dwThreadID = 0;
//	HANDLE hThread;
//
//	// 4.1 클라이언트 연결을 받아들이고 새로운 소켓 생성(개방)
//	while ((hClient = ::accept(hSocket,
//		(SOCKADDR*)&clientaddr,
//		&nAddrLen)) != INVALID_SOCKET)
//	{
//		// 4.2 새 클라이언트와 통신하기 위한 스레드 생성
//		// 클라이언트 마다 스레드가 하나씩 생성된다
//		hThread = ::CreateThread(
//			NULL,				// 보안속성 상속
//			0,					// 스택 메모리는 기본크기(1MB)
//			ThreadFunction,		// 스래드로 실행할 함수
//			(LPVOID)hClient,	// 새로 생성된 클라이언트 소켓
//			0,					// 생성 플래그는 기본값 사용
//			&dwThreadID);		// 생성된 스레드 ID가 저장될 변수 주소
//
//		::CloseHandle(hThread);
//	}
//
//	// 5. 리슨 소켓 닫기
//	::closesocket(hSocket);
//
//	// 윈속 해제
//	::WSACleanup();
//	return 0;
//
//
//}