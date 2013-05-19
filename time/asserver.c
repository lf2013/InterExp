#include "head.h"
int main()
{
	struct sockaddr_in serveraddr, clientaddr;
	int serverfd, clientfd;
	
	if((serverfd = socket(AF_INET, SOCK_DGRAM, 0)) != 0)
		perror("socket error\n");
	
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(ASSERVERPORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		perror("Bind error\n");
	else 
		printf("Bind Success\n");	
	
	char buf[] = "Hello from udp server\n";
	
	int alen = sizeof(serveraddr);
	time_t now;	
	while(1){	
		if(recvfrom(serverfd, buf, sizeof (buf), 0, (struct sockaddr *)&clientaddr, &alen) > 0){
			printf("recvfrom %d : %d \n%s\n", clientaddr.sin_addr.s_addr, clientaddr.sin_port, buf);
			(void) time(&now);
			sendto(serverfd, (char *)&now, sizeof(now), 0, (struct sockaddr *) &clientaddr, sizeof(clientaddr));
		}		
	}
	return 0;
}
