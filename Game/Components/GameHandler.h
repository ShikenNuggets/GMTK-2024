#pragma once

#include <Gadget.h>

using namespace Gadget;

class GameHandler : public SceneComponent{
public:
	GameHandler(Scene* parent_) : SceneComponent(parent_), isGameOver(false){};

	void TriggerGameOver();

	bool IsGameOver() const{ return isGameOver; }

private:
	bool isGameOver;
};