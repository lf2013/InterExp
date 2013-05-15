#include "head.h"
int main()
{
	struct sockaddr_in serveraddr, clientaddr;
	int serverfd, clientfd;
	
	if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) != 0)
		perror("socket error\n");
	
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(ASSERVERPORT);
    //inet_aton(ASSERVERADDR, &serveraddr.sin_addr);//将a.b.c.d => 二进制
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
// 	serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
	
	if(bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		perror("Bind error\n");
	else 
		printf("Bind Success\n");	
	
	if(listen(serverfd, Max) != 0)
		perror("Listen error\n");
	else 
		printf("Listen Success\n");	

	while(1){
		if((clientfd = accept(serverfd, NULL, NULL)) == -1)
			perror("Accept error\n");
		else 
			printf("Accept Success\n");	
		switch(fork()){
			case 0:
				(void) close(serverfd);
				exit(deal(clientfd));
			default: 
				(void) close(clientfd);
				break;
			case -1:
				perror("fork error\n");
		}
	}
}	
int deal(int clientfd)
{
	char buf[100];
	int cc;
	while(cc = read(clientfd, buf, sizeof buf)){
		write(clientfd, buf, cc);
	}
	return 0;
}
