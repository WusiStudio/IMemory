#include "../include/IMemory.h"
#include <iostream>


int main( int argc, char ** argv )
{

	ws::gcWorker main;
	ws::gc & tGc = ws::gc::instance ();
	{
		ws::gcWorker haha;

		ws::object & tObj = ws::object::Create ();
		std::cout << "tObj.quote: " << tObj.quote () << ", tObj.frequency: " << tObj.frequency () << std::endl;

		ws::object & tObj2 = ws::object::Create ();
		tObj2.retain ();
		std::cout << "tObj2.quote: " << tObj2.quote () << ", tObj2.frequency: " << tObj2.frequency () << std::endl;

	}

	ws::object & tObj3 = ws::object::Create ();
	std::cout << "tObj3.quote: " << tObj3.quote () << ", tObj3.frequency: " << tObj3.frequency () << std::endl;
	ws::object & tObj4 = ws::object::Create ();
	std::cout << "tObj4.quote: " << tObj4.quote () << ", tObj4.frequency: " << tObj4.frequency () << std::endl;

	std::getchar ();

    return 0;
}