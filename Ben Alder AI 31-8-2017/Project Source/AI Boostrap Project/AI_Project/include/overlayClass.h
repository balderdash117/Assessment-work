#pragma once

class overlayClass
{
public:

	static void update();

	static bool getGraphShowing();

protected:

	static bool m_showingGraph;

private:

	overlayClass();

	~overlayClass();

};
