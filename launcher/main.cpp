#include <stdio.h>
#include "platform.h"

int main (int argc, char *argv[])
{
	Kernel::Platform::Initialise(argc, argv);
	Kernel::Platform::Shutdown();
	return 0;
}