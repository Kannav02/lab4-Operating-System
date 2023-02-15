#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>



using namespace std;

char socketPath[]="/tmp/lab4";

int main()
{
	//declaring the dependancies variables first of all
	struct sockaddr_un addr;
	char buf[100];
	int serverFD,cl,n;
	bool isRunning=true;

	//socket()
	if((serverFD=socket(AF_UNIX,SOCK_STREAM,0))<0)
	{
		cout<<"ServerError:"<<strerror(errno)<<endl;
		exit(-1);

	}

	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path,socketPath,sizeof(addr.sun_path)-1);
	unlink(socketPath);



	//bind()
	if((bind(serverFD,(struct sockaddr*)&addr,sizeof(addr)==-1)))
	{
		cout<<"BindingError:"<<strerror(errno)<<endl;
		exit(-1);

	}

	//listen()

	if((listen(serverFD,5))==-1)
	{
		cout<<"ListeningError:"<<strerror(errno)<<endl;
		exit(-1);
	}

	//accept()




	if((cl=accept(serverFD,NULL,NULL))==-1)
	{
		cout<<"ServerAcceptError:"<<strerror(errno)<<endl;
		unlink(socketPath);
		close(serverFD);
		exit(-1);

	}



	//Write the command pid to the client
	char command[32]="Pid";

	n=write(cl,&command,sizeof(command));
	if(n==-1)
	{
		cout<<"Cannot Write"<<strerror(errno)<<endl;
		unlink(socketPath);
		close(cl);
		close(serverFD);
		exit(-1);

	};
	cout<<"The server requests the client's Pid"<<endl;

	n=read(cl,&buf,sizeof(buf));
	if(n==-1)
	{
		cout<<"Cannot read"<<strerror(errno)<<endl;
		unlink(socketPath);
		close(cl);
		close(serverFD);
		exit(-1);

	}
	else
	{
		cout<<"Server:  this client has pid "<<buf<<endl;
	}

	//sending sleep command
	sprintf(command,"%s","Sleep");
	n=write(cl,&command,sizeof(command));
	if(n==-1)
	{
		cout<<"Cannot Write"<<strerror(errno)<<endl;
		unlink(socketPath);
		close(cl);
		close(serverFD);
		exit(-1);

	};
	cout<<"the server requests the client to sleep"<<endl;
	if((n=read(cl,&buf,sizeof(buf)))==-1)
	{
		cout<<"Cannot read"<<strerror(errno)<<endl;
		unlink(socketPath);
		close(cl);
		close(serverFD);
		exit(-1);
	};
	if(strcmp("Done",buf)==0){
		//sending quit command
		sprintf(command,"%s","Quit");
		n=write(cl,&command,sizeof(command));
		if(n==-1)
		{
			cout<<"Cannot Write"<<strerror(errno)<<endl;
			unlink(socketPath);
			close(cl);
			close(serverFD);
			exit(-1);

		};
		cout<<"the server requests the client to quit"<<endl;


		unlink(socketPath);
		close(cl);
		close(serverFD);
	}



















}
