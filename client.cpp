#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

using namespace std;
char socketPath[]="/tmp/lab4";


int main(){

	//DECLARING THE VARIABLES
	struct sockaddr_un addr;
	char buffer[100];
	int clientFD,n;
	bool isRunning=true;

	//socket()
	if((clientFD=socket(AF_UNIX,SOCK_STREAM,0))==-1)
	{
		cout<<"Socket Cannot be made"<<strerror(errno)<<endl;

	}

	memset(&addr,0,sizeof(addr));
	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path,socketPath,sizeof(addr.sun_path)-1);


	//connect()
	if(connect(clientFD,(struct sockaddr*)&addr,sizeof(addr))==-1)
	{
		cout<<"Connection cannot be made"<<strerror(errno)<<endl;
		close(clientFD);
	}

	while(isRunning)
	{
		n=read(clientFD,buffer,sizeof(buffer));
		if(strncmp("Pid",buffer,3)==0){
			cout<<"A request for client's pid has been recieved"<<endl;
			char pid[32];
			sprintf(pid,"%d",getpid());
			if((n=write(clientFD,pid,sizeof(pid)))==-1)
			{
				cout<<"WriteError:"<<strerror(errno)<<endl;
				unlink(socketPath);
				close(clientFD);
			}



		}
		if(strncmp("Sleep",buffer,5)==0){

			cout<<"the client is going to sleep for 5 seconds"<<endl;
			sleep(5);
			char temp[100];
			sprintf(temp,"%s","Done");
			if((n=write(clientFD,temp,sizeof(temp)))==-1)
			{
				cout<<"WriteError:"<<strerror(errno)<<endl;
				unlink(socketPath);
				close(clientFD);
			}
			



		}
		if(strncmp("Quit",buffer,4)==0){
			
			isRunning=false;
			cout<<"the client is quitting"<<endl;

		}

	}

	close(clientFD);

	return 0;




}
