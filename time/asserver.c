#include "head.h"
int main()
{
	struct sockaddr_in serveraddr;
	int serverfd, clientfd;
	
	if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) != 0)
		perror("socket error\n");
	
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(ASSERVERPORT);
//    inet_aton(ASSERVERADDR, &serveraddr.sin_addr);//将a.b.c.d => 二进制
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
// 	serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
	
	if(bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		perror("Bind error\n");
	else 
		printf("Bind Success\n");	
	
/*	if(listen(serverfd, Max) != 0)
		perror("Listen error\n");
	else 
		printf("Listen Success\n");	
*/
/*		if((clientfd = accept(serverfd, NULL, NULL)) == -1)
			perror("Accept error\n");
		else 
			printf("Accept Success\n");	
*/
	char buf[] = "Hello from udp server\n";
	
//	struct sockaddr_in fsin;
	int alen = sizeof(serveraddr);
	time_t now;	
	while(1){	
		if(recvfrom(serverfd, buf, sizeof (buf), 0, (struct sockaddr *)&serveraddr, &alen) > 0){
			printf("recvfrom %s\n", buf);
			(void) time(&now);
			sendto(serverfd, (char *)&now, sizeof(now), 0, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
		}		
	}
	return 0;
}
