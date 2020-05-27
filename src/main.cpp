#include <iostream>

#include "../include/vocabulary.h"

int main(int argc, char *argv[])
{
	vocabulary v;

	v.load_vocab();

	v.load_history();

	while(!v.is_done())
		v.ask();

	std::cout << "Congratulations: All done" << std::endl;

	return 0;
}

