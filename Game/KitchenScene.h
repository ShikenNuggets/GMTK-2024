#pragma once

#include <Gadget.h>

#include "BallObject.h"
#include "CameraObject.h"
#include "FloorObject.h"
#include "GameplayCanvasSceneComponent.h"
#include "HamsterObject.h"

using namespace Gadget;

class KitchenScene : public Scene{
public:
	KitchenScene() : Scene(SID("KitchenScene")){}

protected:
	static constexpr std::array<std::array<int, 9>, 55> tiles = {
		std::array<int, 9>{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();

		CreateObject(new CameraObject(Vector3(0.0f, 2.0f, 10.0f), true, SID("LevelMusic")));

		for(int i = 0; i < 55; i++){
			for(int j = 0; j < 9; j++){
				if(tiles[i][j] == 0){
					continue;
				}

				CreateObject(new FloorObject(
					Vector3((j * 5.0f) - 20.0f, 0.0f, i * -5.0f),
					Quaternion::Identity(),
					Vector3(5.0f, 1.0f, 5.0f),
					SID("BrickMaterial")
				));
			}
		}

		GameObject* faucet = new GameObject(SID("Faucet"));
		faucet->SetPosition(-18.0f, 5.0f, -30.0f);
		faucet->SetRotation(90.0f, -90.0f, 180.0f);
		faucet->AddComponent(new RenderComponent(faucet->GetGUID(), SID("FaucetModel"), SID("SinkMaterial")));
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

		HamsterObject* hm = new HamsterObject();
		CreateObject(new HamsterObject());
		//This must be the last object we create
		CreateObject(new BallObject(Vector3(0.0f, 5.0f, 0.0f)));

		AddSceneComponent(new GameplayCanvasSceneComponent(this, SID("MainCanvas")));
		AddSceneComponent(new SkyboxComponent(this, SID("KitchenSky")));
	}
};