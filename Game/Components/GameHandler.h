#pragma once

#include <Gadget.h>

using namespace Gadget;

class GameHandler : public SceneComponent{
public:
	GameHandler(Scene* parent_) : SceneComponent(parent_){};

	virtual void OnUpdate(float deltaTime_) override;

	void Pause();
	void Unpause();

	void TriggerEndTutorial();
	void TriggerWinState();
	void TriggerGameOver();

	bool IsGameOver() const{ return isGameOver || isWinState; }
	bool IsWinState() const{ return isWinState; }

private:
	bool isGameOver = false;
	bool isWinState = false;
	bool isPaused = false;
};