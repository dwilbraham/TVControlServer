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

size_t readLine(int sock, std::string& line, size_t maxlen)
{
	int n, rc;
	char c;

	for (n = 1; n < maxlen; n++) {
		if ((rc = read(sock, &c, 1)) == 1)
		{
			if (c == '\r' || c == '\n')
				break;
			line.push_back(c);
		}
		else if (rc == 0)
		{
			if (n == 1)
				return 0; /* EOF, no data read */
			else
				break;    /* EOF, some data was read */
		}
		else
			return -1;    /* error */
	}
	return n;
}

int main(int argc, char* argv[])
{
	Controller controller = Controller();
	static const int bufferLen = 100;

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

	int i;
	for (i = 1; i < 5; i++)
	{
		std::string line;
		n = readLine(commfd, line, bufferLen);
		std::cout << "line = " << line << std::endl;
		if(line == "on")
		{
			controller.powerOnTV();
			std::string msg = "TV is now on\n";
			write(commfd, msg.c_str(), msg.length());
		}
		else if(line == "off")
		{
			controller.powerOffTV();
			std::string msg = "TV is now off\n";
			write(commfd, msg.c_str(), msg.length());
		}
		else
		{
			std::string msg = "UNKNOWN COMMAND = " + line + '\n';
			write(commfd, msg.c_str(), msg.length());
			write(2, msg.c_str(), msg.length());
		}
	}

	std::cout << "i = " << i << std::endl;
}
