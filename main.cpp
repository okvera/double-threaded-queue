#include "CGame.h"
#include "CGraphics.h"
#include "CRenderQueue.h"

#include <thread>

int main(int argc, char** argv) 
{
	if (argc != 2)
	{
		std::cout << "Choose test number from 1 to 4 and come back\n";
		return -1;
	}

	CRenderQueue queue{};
	CGame game(&queue);
	CGraphics graphics(&queue);

	std::thread mainThread(&CGame::Send, &game, atoi(argv[1]));
	std::thread graphicsThread(&CGraphics::Receive, &graphics);

	std::cout << "Start!\n\n";

	mainThread.join();
	graphicsThread.join();

    std::cout << "\nFinish!\n";
	return 0;
}
