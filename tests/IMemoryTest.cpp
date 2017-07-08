#include "../include/IMemory.h"
#include <iostream>
#include <vector>
#include <ctime>


int main( int argc, char ** argv )
{ IMSTACK

	double start, end;
	
	ws::gc & tGc = ws::gc::instance ();
	{ IMSTACK

		ws::object & tObj = ws::object::Create ();
		LOG.info ( "tObj.quote: {0}, tObj.frequency: {1}", tObj.quote (), tObj.frequency () );

		ws::object & tObj2 = ws::object::Create ();
		tObj2.retain ();
		LOG.info ( "tObj2.quote: {0}, tObj2.frequency: {1}", tObj2.quote (), tObj2.frequency () );

		std::vector< ws::object * > tObjList;
		start = clock ();
		for (int i = 0; i < 100000; ++i)
		{
			ws::object & ttObj = ws::object::Create ();
			tObjList.push_back ( &ttObj );
		}
		end = clock ();
		LOG.info ( "pass1 create 100000 object time: {0, F4}", (end - start) / CLOCKS_PER_SEC );
	}

	IMGCMake

	std::vector< ws::object * > tObjList;
	start = clock ();
	for (int i = 0; i < 100000; ++i)
	{
		ws::object & ttObj = ws::object::Create ();
		tObjList.push_back ( &ttObj );
	}
	end = clock ();
	LOG.info ( "pass2 create 100000 object time: {0, F4}", (end - start) / CLOCKS_PER_SEC );

	ws::object & tObj3 = ws::object::Create ();
	LOG.info ( "tObj3.quote: {0}, tObj3.frequency: {1}", tObj3.quote (), tObj3.frequency () );
	ws::object & tObj4 = ws::object::Create ();
	LOG.info ( "tObj4.quote: {0}, tObj4.frequency: {1}", tObj4.quote (), tObj4.frequency () );

	IMGCMake

	std::getchar ();

    return 0;
}