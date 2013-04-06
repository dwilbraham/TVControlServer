#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "controller.h"

using namespace TVControlServer;

int main(int argc, char* argv[])
{
//	Controller controller = Controller();
	static const int bufferLen = 100;
	char readBuffer[bufferLen];

	struct sockaddr_in addr;
	struct sockaddr_in client;
	socklen_t addrlen;
	ssize_t n;
	int sockfd, commfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(22222);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	listen(sockfd, 5);

	memset(&client, 0, sizeof(client));
	addrlen = sizeof(client);
	commfd = accept(sockfd, (struct sockaddr*)&client, &addrlen);
	if(commfd < 0)
	{
		perror("accept");
		return(1);
	}

	close(sockfd);
	std::string welcomeMessage = PACKAGE_STRING;
	welcomeMessage.push_back('\n');
	write(commfd, welcomeMessage.c_str(), welcomeMessage.length());

	n = read(commfd, readBuffer, bufferLen);
	readBuffer[n] = '\0';

	std::cout << "readBuffer = \"" << readBuffer << "\"" << std::endl;
	
//	controller.powerOnTV();
//	sleep(10);
}
