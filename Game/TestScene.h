#pragma once

#include <Game/Scene.h>
#include <Physics/SphereCollider.h>

#include "BallController.h"
#include "HamsterController.h"

using namespace Gadget;

class TestScene : public Scene{
public:
	TestScene() : Scene(SID("TestScene")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();

		GameObject* camera = new GameObject(SID("CameraObj"));
		camera->SetPosition(0.0f, 2.0f, 10.0f);
		camera->AddComponent(new CameraComponent(camera));
		camera->AddTag(SID("Camera"));
		CreateObject(camera);

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

		GameObject* hamster = new GameObject(SID("Hamster"));
		hamster->SetPosition(0.0f, 0.0f, 0.0f);
		hamster->Rotate(90.0f, 0.0f, 180.0f);
		hamster->SetScale(25.0f);
		hamster->AddComponent(new RenderComponent(hamster->GetGUID(), SID("HamsterModel"), SID("HamsterMaterial")));
		hamster->AddComponent(new HamsterController(hamster));
		CreateObject(hamster);

		//TODO - Engine should force transparent objects to be rendered *after* opaque ones, and in order from distance to the camera (farthest to nearest)
		GameObject* ball = new GameObject(SID("Ball"));
		ball->SetPosition(0.0f, 5.0f, 0.0f);
		ball->AddComponent(new RenderComponent(ball->GetGUID(), SID("SphereModel"), SID("GlassMaterial")));
		ball->AddComponent(new SphereCollider(ball, 1.0f));
		ball->AddComponent(new Rigidbody(ball, 1.0f, true));
		ball->AddComponent(new BallController(ball));
		ball->AddTag(SID("Ball"));
		CreateObject(ball);
	}
};