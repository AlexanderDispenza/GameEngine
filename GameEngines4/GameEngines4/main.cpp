#include "Engine/Core/CoreEngine.h"
#include "GAME/Game1.h"

int main(int argc, char* argv[])
{
	CoreEngine::GetInstance()->SetGameInterface(new Game1);

	if (!CoreEngine::GetInstance()->OnCreate("Engine Window", 800, 600)) 
	{
		std::cout << ("Engine failed to be created") << std::endl;
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}