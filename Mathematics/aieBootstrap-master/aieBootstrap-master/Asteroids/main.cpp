////////////////////////////////////////////////////////////////////////////////////////
////																				////
////				NAME:	Asteroids Project										////		
////																				////		
////				PURPOSE:	This be main yo										////
////																				////
////				AUTHOR: Ben Alder 3/14/17										////
////							With help from Jack B								////
////																				////
////////////////////////////////////////////////////////////////////////////////////////
#include "AsteroidsApp.h"
#include <time.h>

// Changes
//    1. Sprites added
//         a) Player, treasure and asteriods
//		   b) Background
//    2. Music added
//    3. Unique movement routine with scroll controlling rotation

int main() {
	srand((unsigned int)time(NULL));
	auto app = new AsteroidsApp();
	app->run("AIE", 2736, 1824, true);
	delete app;

	return 0;
}