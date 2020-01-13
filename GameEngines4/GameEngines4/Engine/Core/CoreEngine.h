#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
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

private:
	CoreEngine();
	~CoreEngine();

	SDL_Event eventWindow;

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	void Update(float deltaTime_);
	void Render();
	void OnDestroy();

	Window* window;
	bool isRunning;
};
#endif

