#pragma once

#include <Gadget.h>

using namespace Gadget;

class GameHandler : public SceneComponent{
public:
	GameHandler(Scene* parent_) : SceneComponent(parent_), isGameOver(false){};

	void TriggerWinState();
	void TriggerGameOver();

	bool IsGameOver() const{ return isGameOver || isWinState; }
	bool IsWinState() const{ return isWinState; }

private:
	bool isGameOver;
	bool isWinState;
};