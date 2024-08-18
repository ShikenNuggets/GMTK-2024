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
			Vector3(9.0f, 1.0f, 50.0f),
			SID("BrickMaterial")
		));

		//Sink Right
		CreateObject(new FloorObject(
			Vector3(17.5f, 0.0f, -37.5f),
			Quaternion::Identity(),
			Vector3(9.0f, 1.0f, 50.0f),
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
		faucet->AddComponent(new MeshCollider(faucet, SID("FaucetModel"), ColliderShape::ConvexMesh));
		CreateObject(faucet);

		GameObject* sink = new GameObject(SID("Sink"));
		sink->SetPosition(0.0f, -7.0f, -37.5f);
		sink->Rotate(-90.0f, 0.0f, 0.0f);
		sink->SetScale(12.25f, 25.0f, 7.5f);
		sink->AddComponent(new RenderComponent(sink->GetGUID(), SID("SinkModel"), SID("SinkMaterial")));
		CreateObject(sink);

		GameObject* cerealBox = new GameObject(SID("CerealBox"));
		cerealBox->SetPosition(Vector3(17.5f, 7.5f, -37.5f));
		cerealBox->Rotate(-90.0f, 0.0f, 0.0f);
		cerealBox->AddComponent(new RenderComponent(cerealBox->GetGUID(), SID("CerealBoxModel"), SID("CerealBoxMaterial")));
		cerealBox->AddComponent(new Rigidbody(cerealBox, 25.0f, true));
		cerealBox->AddComponent(new CubeCollider(cerealBox, 4.0f, 2.2f, 4.5f));
		CreateObject(cerealBox);
		
		GameObject* pointLight = new GameObject(SID("PointLight"));
		pointLight->SetPosition(sink->GetPosition() + Vector3(0.0f, -5.0f, 0.0f));
		pointLight->AddComponent(new PointLightComponent(pointLight));
		CreateObject(pointLight);

		GameObject* dirLight = new GameObject(SID("DirLight"));
		dirLight->AddComponent(new DirectionalLightComponent(dirLight, Vector3(0.8f, -1.0f, -0.5f).Normalized()));
		CreateObject(dirLight); //TODO - Forgot to add this earlier and nothing complained, check for undeleted objects on shutdown

		GameObject* ramp = new GameObject(SID("Ramp"));
		ramp->SetPosition(0.0f, 0.0f, -125.0f);
		ramp->AddComponent(new RenderComponent(ramp->GetGUID(), SID("RampModel"), SID("BrickMaterial")));
		ramp->AddComponent(new MeshCollider(ramp, SID("RampModel"), ColliderShape::ConvexMesh));
		CreateObject(ramp);

		CreateObject(new HamsterObject());
		CreateObject(new BallObject(Vector3(0.0f, 5.0f, 0.0f))); //This must be the last object we create!!!

		AddSceneComponent(new GameHandler(this));
		AddSceneComponent(new GameplayCanvasSceneComponent(this, SID("MainCanvas")));
		AddSceneComponent(new SkyboxComponent(this, SID("KitchenSky")));
	}

private:
	static constexpr float levelWidth = 45.0f;
};