#include "head.h"
int main()
{
	int clientFd1, clientFd2, clientFd3;
	struct sockaddr_in clintaddr, serveraddr;//<netinet/in.h>
	
	if((clientFd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("client socket fail\n");
	
	if((clientFd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("client socket fail\n");
	
	if((clientFd3 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("client socket fail\n");
	
//	memset((char *)&clintaddr, 0, sizeof(clintaddr));
	bzero(&clintaddr, sizeof(clintaddr));
	clintaddr.sin_family = AF_INET;
	clintaddr.sin_port = htons(30001);
	clintaddr.sin_addr.s_addr = htons(INADDR_ANY);

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(ASSERVERPORT);
    inet_aton(ASSERVERADDR, &serveraddr.sin_addr);//将a.b.c.d => 二进制
//	serveraddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1",

//connect AS
	if(connect(clientFd1, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		perror("connect AS error\n");
	else 
		printf("connect AS success\n");

	char rev[100] = {0};
	recv(clientFd1, rev, 20, 0);
	puts(rev);
//	close(clientFd);	
//connect TGS
	serveraddr.sin_port = htons(TGSSERVERPORT);
    inet_aton(TGSSERVERADDR, &serveraddr.sin_addr);//将a.b.c.d => 二进制
	if(connect(clientFd2, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		perror("connect TGS error\n");
	else 
		printf("connect TGS success\n");

	while(recv(clientFd2, rev, 100, 0)){
		puts(rev);
		send(clientFd2, rev, sizeof(rev), 0); 
		sleep(2);
	}
//	close(clientFd);	
//connect B
	serveraddr.sin_port = htons(BSERVERPORT);
    inet_aton(BSERVERADDR, &serveraddr.sin_addr);//将a.b.c.d => 二进制
	if(connect(clientFd3, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		perror("connect B error\n");
	else 
		printf("connect B success\n");

	recv(clientFd3, rev, 20, 0);
	puts(rev);

	close(clientFd3);	

}
