#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int fd;
	char filename[2000],filebuffer[2000];
	struct sockaddr_in servaddr;
	
	if((fd = socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("Socket Creation failed..");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr,0,sizeof(servaddr));
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	printf("Enter textfile Name to send : \n");
	scanf("%s",filename);
	sendto(fd,filename,strlen(filename),0,(struct sockaddr*)&servaddr,sizeof(struct sockaddr));
	
	FILE *fp;
	fp = fopen(filename,"r");
	
	if(fp)
	{
		printf("Reading file Contents...\n");
		fseek(fp,0,SEEK_END);
		size_t file_size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		if(fread(filebuffer,file_size,1,fp)<=0)
		{
			printf("Unable to copy file into Buffer...\n");
			exit(1);
		}
		
	}
	else
	{
		printf("Cannot open the File...\n");
		exit(0);
	}
	
	printf("FILE CONTENTS TO SEND : %s\n",filebuffer);
	if(sendto(fd,filebuffer,strlen(filebuffer),0,(struct sockaddr*)&servaddr,sizeof(struct sockaddr))<0)
	{
		printf("File Was Not Sent...\n");
	}
	
	else
	{
		printf("File Sent\n");
	}
	fclose(fp);
}
