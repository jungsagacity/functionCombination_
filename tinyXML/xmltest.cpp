/*
   Test program for TinyXML.
*/


#ifdef TIXML_USE_STL
	#include <iostream>
	#include <sstream>
	using namespace std;
#else
	#include <stdio.h>
#endif

#if defined( WIN32 ) && defined( TUNE )
	#include <crtdbg.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#endif

#include "tinyxml.h"


int main()
{

	//
	// We start with the 'demoStart' todo list. Process it. And
	// should hopefully end up with the todo list as illustrated.
	//
	const char* demoStart =
		"<?xml version=\"1.0\"  standalone='no' >\n"
		"<!-- Our to do list data -->"
		"<ToDo>\n"
		"<!-- Do I need a secure PDA? -->\n"
		"<Item priority=\"1\" distance='close'> Go to the <bold>Toy store!</bold></Item>"
		"<Item priority=\"2\" distance='none'> Do bills   </Item>"
		"<Item priority=\"2\" distance='far &amp; back'> Look for Evil Dinosaurs! </Item>"
		"<jun>12</jun>"
		"</ToDo>";


		//--------------------------------------------------------------------------------------
		// Write to a file and read it back, to check file I/O.

		TiXmlDocument doc( "demotest.xml" );
		doc.Parse( demoStart );

		if ( doc.Error() )
		{
			printf( "Error in %s: %s\n", doc.Value(), doc.ErrorDesc() );
			exit( 1 );
		}
		doc.SaveFile();
		

		//--------------------------------------------------------------------------------------
		TiXmlDocument doc_( "demotest.xml" );
		bool loadOkay = doc_.LoadFile();

		if ( !loadOkay )
		{
			printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
			exit( 1 );
		}

		printf( "** Demo doc read from disk: ** \n\n" );
		printf( "** Printing via doc.Print **\n" );
		doc_.Print( stdout );




	return 0;
}
