#include "CoreEngine.h"
#include "Debugger.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine()
{
	window = nullptr;
	isRunning = false;
	fps = 144;
	gameInterface = nullptr;
	currentSceneNum = 0; 
}

CoreEngine::~CoreEngine()
{
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debugger::DebugInit();
	Debugger::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	if (!window->OnCreate(name_, width_, height_))
	{
		Debugger::FatalError("Window failed to initialize ", "CoreEngine.cpp ", __LINE__);
		isRunning = false;
	}

	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");

	if (gameInterface) 
	{
		if (!gameInterface->OnCreate()) 
		{
			Debugger::FatalError("GameInterface failed to initialize! ", "CoreEngine.cpp ", __LINE__);
		}

	}

	timer.Start();

	Debugger::Info("Engine launched successfully ", "CoreEngine.cpp ", __LINE__);
	
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning)
	{
		timer.UpdateFrameTick();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning) 
	{
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}


void CoreEngine::EventHandler()
{
	// checks if there is a pending event 
	while (SDL_PollEvent(&eventWindow) > 0) 
	{
		// if the event is the close button then set isRunning to false
		if (eventWindow.type == SDL_QUIT) 
		{
			isRunning = false;
		}
	}
}


CoreEngine* CoreEngine::GetInstance()
{
	if (engineInstance.get() == nullptr) 
	{
		engineInstance.reset(new CoreEngine());
	}
	return engineInstance.get();
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

int CoreEngine::GetCurrentScene()
{
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void CoreEngine::Exit()
{
	isRunning = false;
}

void CoreEngine::Update(const float deltaTime_)
{
	EventHandler();
	if (gameInterface)
	{
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Rend Game
	if (gameInterface) 
	{
		gameInterface->Render();
	}
	SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;

	SDL_Quit();
	exit(0);
}

