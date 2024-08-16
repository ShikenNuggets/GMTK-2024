#pragma once

#include <Gadget.h>

#include "TestScene.h"

class HamsterGame : public Gadget::GameInterface{
public:
	HamsterGame() : GameInterface("HamsterGame"){}

	void LoadGame(){
		Gadget::App::GetInstance().GetSceneManager().AddScene(new TestScene());
	}
};