#pragma once

#include <Game/Scene.h>
#include <Physics/SphereCollider.h>

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
		CreateObject(camera);

		GameObject* floor = new GameObject(SID("Floor"));
		floor->SetScale(10.0f, 0.01f, 10.0f);
		floor->AddComponent(new RenderComponent(floor->GetGUID(), SID("CubeModel"), SID("BrickMaterial")));
		floor->AddComponent(new CubeCollider(floor));
		CreateObject(floor);

		GameObject* hamster = new GameObject(SID("Hamster"));
		hamster->SetPosition(0.0f, 0.0f, 0.0f);
		hamster->Rotate(90.0f, 0.0f, 180.0f);
		hamster->SetScale(25.0f);
		hamster->AddComponent(new RenderComponent(hamster->GetGUID(), SID("HamsterModel"), SID("HamsterMaterial")));
		CreateObject(hamster);

		//TODO - Auto-render transparent objects *after* opaque ones, and in order from distance to the camera
		GameObject* ball = new GameObject(SID("Ball"));
		ball->SetPosition(0.0f, 5.0f, 0.0f);
		ball->AddComponent(new RenderComponent(ball->GetGUID(), SID("SphereModel"), SID("GlassMaterial")));
		ball->AddComponent(new SphereCollider(ball));
		ball->AddComponent(new Rigidbody(ball, 1.0f, true));
		CreateObject(ball);
	}
};