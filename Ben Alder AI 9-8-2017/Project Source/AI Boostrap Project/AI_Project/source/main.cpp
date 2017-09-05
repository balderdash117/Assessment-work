#include "AI_ProjectApp.h"

int main() {
	
	auto app = new AI_ProjectApp();
	app->run("AIE", 1600, 1268, false);
	delete app;

	return 0;
}