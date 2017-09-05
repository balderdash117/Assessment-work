#include "SceneGraphApp.h"

int main() {
	
	auto app = new SceneGraphApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}