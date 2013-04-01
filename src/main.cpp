#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#include <iostream>

#include "controller.h"

using namespace TVControlServer;

int main(int argv, char ** argc)
{
	std::cout << "Hello world" << std::endl;
	Controller controller = Controller();
}
