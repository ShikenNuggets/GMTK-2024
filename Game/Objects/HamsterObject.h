#pragma once

#include <Gadget.h>

#include "GameLogic/HamsterController.h"

using namespace Gadget;

class HamsterObject : public GameObject{
public:
	HamsterObject(const Vector3& startPosition_ = Vector3::Zero()) : GameObject(SID("Hamster")){
		SetPosition(startPosition_);
		SetRotation(75.0f, 0.0f, 180.0f);
		SetScale(25.0f);
		AddComponent(new RenderComponent(GetGUID(), SID("HamsterModel"), SID("HamsterMaterial")));
		AddComponent(new HamsterController(this));
	}
};