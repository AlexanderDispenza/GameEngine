#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
#include "Timer.h"
#include "GameInterface.h"
#include "Scene.h"
#include "Debugger.h"
#include <memory>

class CoreEngine
{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;
	
	bool OnCreate(std::string name_, int width_, int height_);

	void Run();
	bool GetIsRunning() const;

	void EventHandler();

	static CoreEngine* GetInstance();

	void SetGameInterface(GameInterface* gameInterface_);

	int GetCurrentScene();
	void SetCurrentScene(int sceneNum_);

	void Exit();

private:
	CoreEngine();
	~CoreEngine();

	SDL_Event eventWindow;

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;
};
#endif

