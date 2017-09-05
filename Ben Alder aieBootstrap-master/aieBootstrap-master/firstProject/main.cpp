#include "firstProjectApp.h"

int main() {
	
	auto app = new firstProjectApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}