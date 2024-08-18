#pragma once

#include <Game/Scene.h>
#include <Physics/SphereCollider.h>

#include "Objects/BallObject.h"
#include "Objects/CameraObject.h"
#include "Objects/HamsterObject.h"

using namespace Gadget;

class TestScene : public Scene{
public:
	TestScene() : Scene(SID("TestScene")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();

		CreateObject(new CameraObject(Vector3(0.0f, 2.0f, 10.0f), true));

		for(int i = -3; i < 3; i++){
			for(int j = -3; j < 3; j++){
				GameObject* floor = new GameObject(SID("Floor"));
				floor->SetPosition(i * 5.0f, 0.0f, j * 5.0f);
				floor->SetScale(5.0f, 0.1f, 5.0f);
				floor->AddComponent(new RenderComponent(floor->GetGUID(), SID("CubeModel"), SID("BrickMaterial")));
				floor->AddComponent(new CubeCollider(floor));
				CreateObject(floor);
			}
		}

		CreateObject(new HamsterObject());

		//TODO - Engine should force transparent objects to be rendered *after* opaque ones, and in order from distance to the camera (farthest to nearest)
		CreateObject(new BallObject(Vector3(0.0f, 5.0f, 0.0f)));
	}
};