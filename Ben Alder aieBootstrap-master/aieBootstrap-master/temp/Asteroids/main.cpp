#include "AsteroidsApp.h"

int main() {
	
	auto app = new AsteroidsApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}