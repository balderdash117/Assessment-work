#include "GameStateWalkthroughApp.h"

int main() {
	
	auto app = new GameStateWalkthroughApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}