#pragma once

#include <Gadget.h>

#include "CameraController.h"

using namespace Gadget;

class CameraObject : public GameObject{
public:
	CameraObject(const Vector3& startPosition_, bool controllable_) : GameObject(){
		SetPosition(startPosition_);
		SetRotation(-15.0f, 0.0f, 0.0f);
		AddComponent(new CameraComponent(this));
		AddComponent(new AudioListener(this));

		if(controllable_){
			AddComponent(new CameraController(this));
		}

		AddTag(SID("Camera"));
	}
};