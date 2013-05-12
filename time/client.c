#include "head.h"
int main()
{
	int clientFd, n;
	struct sockaddr_in clintaddr, serveraddr;//<netinet/in.h>
	
	if((clientFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		perror("client socket fail\n");
	
//	memset((char *)&clintaddr, 0, sizeof(clintaddr));
	bzero(&clintaddr, sizeof(clintaddr));
	clintaddr.sin_family = AF_INET;
	clintaddr.sin_port = htons(30001);
	clintaddr.sin_addr.s_addr = htons(INADDR_ANY);

//	serveraddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1",

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(ASSERVERPORT);
//  inet_aton(ASSERVERADDR, &serveraddr.sin_addr);//将a.b.c.d => 二进制
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(connect(clientFd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
		perror("connect error\n");
	else 
		printf("connect success\n");
	
	int outchars, inchars;
	while(scanf("%d", &inchars)){
		char buf[] = "What's the time?\n";
		outchars = sizeof(buf);
//		buf[99] = '\0'; 
		(void) write(clientFd, buf, outchars);
		
/*		for(inchars = 0; inchars < outchars; inchars += n){
			n = read(clientFd, &buf[inchars], outchars - inchars);
		}
*/
		time_t now;
		read(clientFd, (char *)&now, sizeof(now));
		now = ntohl((unsigned long)now);
		now -= UNIXPOCH;
		printf("The time is %s\n", ctime(&now));
	}
}
