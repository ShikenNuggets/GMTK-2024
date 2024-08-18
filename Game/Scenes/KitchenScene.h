#pragma once

#include <Gadget.h>

#include "Components/GameHandler.h"
#include "Components/GameplayCanvasSceneComponent.h"
#include "Objects/BallObject.h"
#include "Objects/CameraObject.h"
#include "Objects/FloorObject.h"
#include "Objects/HamsterObject.h"

using namespace Gadget;

class KitchenScene : public Scene{
public:
	KitchenScene() : Scene(SID("KitchenScene")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();

		CreateObject(new CameraObject(Vector3(0.0f, 2.0f, 10.0f), true, SID("LevelMusic")));

		//First section
		CreateObject(new FloorObject(
			Vector3(0.0f, 0.0f, -5.0f),
			Quaternion::Identity(),
			Vector3(levelWidth, 1.0f, 15.0f),
			SID("BrickMaterial")
		));

		//Sink Left
		CreateObject(new FloorObject(
			Vector3(-17.5f, 0.0f, -37.5f),
			Quaternion::Identity(),
			Vector3(10.0f, 1.0f, 50.0f),
			SID("BrickMaterial")
		));

		//Sink Right
		CreateObject(new FloorObject(
			Vector3(17.5f, 0.0f, -37.5f),
			Quaternion::Identity(),
			Vector3(10.0f, 1.0f, 50.0f),
			SID("BrickMaterial")
		));

		//Section Before Stove Gap
		CreateObject(new FloorObject(
			Vector3(0.0f, 0.0f, -117.5f),
			Quaternion::Identity(),
			Vector3(levelWidth, 1.0f, 110.0f),
			SID("BrickMaterial")
		));

		//Section After Stove Gap
		CreateObject(new FloorObject(
			Vector3(0.0f, 0.0f, 55.0f * -5.0f),
			Quaternion::Identity(),
			Vector3(levelWidth, 1.0f, 55.0f),
			SID("BrickMaterial")
		));

		GameObject* faucet = new GameObject(SID("Faucet"));
		faucet->SetPosition(-18.0f, 5.0f, -30.0f);
		faucet->SetRotation(90.0f, -90.0f, 180.0f);
		faucet->AddComponent(new RenderComponent(faucet->GetGUID(), SID("FaucetModel"), SID("SinkMaterial")));
		faucet->AddComponent(new CubeCollider(faucet, 10.0f, 2.5f, 50.0f));
		CreateObject(faucet);

		GameObject* sink = new GameObject(SID("Sink"));
		sink->SetPosition(0.0f, -7.0f, -37.5f);
		sink->Rotate(-90.0f, 0.0f, 0.0f);
		sink->SetScale(12.25f, 25.0f, 7.5f);
		sink->AddComponent(new RenderComponent(sink->GetGUID(), SID("SinkModel"), SID("SinkMaterial")));
		CreateObject(sink);

		GameObject* pointLight = new GameObject(SID("PointLight"));
		pointLight->SetPosition(sink->GetPosition() + Vector3(0.0f, -5.0f, 0.0f));
		pointLight->AddComponent(new PointLightComponent(pointLight));
		CreateObject(pointLight);

		GameObject* dirLight = new GameObject(SID("DirLight"));
		dirLight->AddComponent(new DirectionalLightComponent(dirLight, Vector3(0.8f, -1.0f, -0.5f).Normalized()));
		CreateObject(dirLight); //TODO - Forgot to add this earlier and nothing complained, check for undeleted objects on shutdown

		GameObject* ramp1 = new GameObject(SID("Ramp1"));
		ramp1->SetPosition(0.0f, -2.5f, -125.0f);
		ramp1->Rotate(30.0f, 0.0f, 0.0f);
		ramp1->SetScale(10.0f, 10.0f, 25.0f);
		ramp1->AddComponent(new RenderComponent(ramp1->GetGUID(), SID("CubeModel"), SID("BrickMaterial")));
		ramp1->AddComponent(new CubeCollider(ramp1));
		CreateObject(ramp1);

		GameObject* ramp2 = new GameObject(SID("Ramp2"));
		ramp2->SetPosition(0.0f, -2.5f, -140.0f);
		ramp2->Rotate(-30.0f, 0.0f, 0.0f);
		ramp2->SetScale(10.0f, 10.0f, 25.0f);
		ramp2->AddComponent(new RenderComponent(ramp2->GetGUID(), SID("CubeModel"), SID("BrickMaterial")));
		ramp2->AddComponent(new CubeCollider(ramp2));
		CreateObject(ramp2);

		GameObject* ramp3 = new GameObject(SID("Ramp3"));
		ramp3->SetPosition(0.0f, -2.5f, -155.0f);
		ramp3->Rotate(15.0f, 0.0f, 0.0f);
		ramp3->SetScale(10.0f, 10.0f, 25.0f);
		ramp3->AddComponent(new RenderComponent(ramp3->GetGUID(), SID("CubeModel"), SID("BrickMaterial")));
		ramp3->AddComponent(new CubeCollider(ramp3));
		CreateObject(ramp3);

		GameObject* rampObstacle1 = new GameObject(SID("RampObstacle1"));
		rampObstacle1->SetPosition(-3.0f, 7.5f, -165.0f);
		rampObstacle1->SetScale(5.0f, 10.0f, 1.0f);
		rampObstacle1->AddComponent(new RenderComponent(rampObstacle1->GetGUID(), SID("CubeModel"), SID("BrickMaterial")));
		rampObstacle1->AddComponent(new CubeCollider(rampObstacle1));
		CreateObject(rampObstacle1);

		GameObject* rampObstacle2 = new GameObject(SID("RampObstacle2"));
		rampObstacle2->SetPosition(3.0f, 7.5f, -165.0f);
		rampObstacle2->SetScale(5.0f, 10.0f, 1.0f);
		rampObstacle2->AddComponent(new RenderComponent(rampObstacle2->GetGUID(), SID("CubeModel"), SID("BrickMaterial")));
		rampObstacle2->AddComponent(new CubeCollider(rampObstacle2));
		CreateObject(rampObstacle2);

		HamsterObject* hm = new HamsterObject();
		CreateObject(new HamsterObject());
		CreateObject(new BallObject(Vector3(0.0f, 5.0f, 0.0f))); //This must be the last object we create!!!

		AddSceneComponent(new GameHandler(this));
		AddSceneComponent(new GameplayCanvasSceneComponent(this, SID("MainCanvas")));
		AddSceneComponent(new SkyboxComponent(this, SID("KitchenSky")));
	}

private:
	static constexpr float levelWidth = 45.0f;
};