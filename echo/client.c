#include "head.h"
int main()
{
	int clientFd, n;
	struct sockaddr_in clintaddr, serveraddr;//<netinet/in.h>
	
	if((clientFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("client socket fail\n");
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(ASSERVERPORT);
    inet_aton(ASSERVERADDR, &serveraddr.sin_addr);//将a.b.c.d => 二进制
	if(connect(clientFd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		perror("connect error\n");
	else 
		printf("connect success\n");
	
	char buf[100] = {0};
	int outchars, inchars;
	while(fgets(buf, sizeof(buf), stdin)){
		outchars = strlen(buf);
		(void) write(clientFd, buf, outchars);
		
		for(inchars = 0; inchars < outchars; inchars += n){
			n = read(clientFd, &buf[inchars], outchars - inchars);
		}
		fputs(buf, stdout);	
	}
}
