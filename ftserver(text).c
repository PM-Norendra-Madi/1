#include<sys/socket.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

#define maxlen 70000
#define mlen 100000

int main()
{
	char filename[100];
	char filebuffer[2000];
	int sd,connfd,len;
	
	for(int i=0;i<=100;i++)
	{
		filename[i] = '\0';
	}
	
	struct sockaddr_in servaddr,cliaddr;
	
	sd = socket(AF_INET,SOCK_DGRAM,0);
	
	if(sd==-1)
	{
		printf("Socket Not Created in Server\n");
		exit(0);
	}
	else
	{
		printf("Socket Created In Server\n");
	}
	
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	memset(&(servaddr.sin_zero),'\0',8);
	
	if(bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr))!=0)
	{
		printf("Not Binded...\n");
	}
	else
	{
		printf("Binded...\n");
	}
	
	len = sizeof(cliaddr);
	
	recvfrom(sd,filename,1024,0,(struct sockaddr*)&cliaddr,&len);
	printf("Name of the text file Recieved : %s\n",filename);
	FILE *fp;
	printf("Contents in Received text file : \n");
	recvfrom(sd,filebuffer,1024,0,(struct sockaddr*)&cliaddr,&len);
	printf("%s\n",filebuffer);
	int fsize = strlen(filebuffer);
	fp=fopen(filename,"w");
	
	if(fp)
	{
		fwrite(filebuffer,fsize,1,fp);
		printf("File Received Successfully..\n");
	}
	else
	{
		printf("Cannot Create Output File....\n");
	}
	
	memset(filename,'\0',sizeof(filename));
	fclose(fp);
	return(0);
	
}
