#include "head.h"
int main()
{
	struct sockaddr_in serveraddr, clientaddr;
	int serverfd, clientfd;
	
	if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) != 0)
		perror("socket error\n");
	
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(BSERVERPORT);
    inet_aton("127.0.0.3", &serveraddr.sin_addr);//将a.b.c.d => 二进制
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
		char msg[] = "Hello from b server";
		send(clientfd, msg, sizeof(msg), 0); 
	}
	close(clientfd);
}
