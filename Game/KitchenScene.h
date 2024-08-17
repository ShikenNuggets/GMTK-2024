#pragma once

#include <Gadget.h>

using namespace Gadget;

class KitchenScene : public Scene{
public:
	KitchenScene() : Scene(SID("KitchenScene")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();


	}
};