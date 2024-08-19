#pragma once

#include <Gadget.h>

#include "Components/GameHandler.h"
#include "Components/GameplayCanvasSceneComponent.h"
#include "Objects/BallObject.h"
#include "Objects/CameraObject.h"
#include "Objects/CerealBoxObject.h"
#include "Objects/FloorObject.h"
#include "Objects/HamsterObject.h"
#include "Objects/RampObject.h"

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

		//12 blocks afterwards
		static constexpr size_t numPlatforms = 20;
		int extraOffset = 0;
		for(size_t i = 0; i < numPlatforms; i++){
			const float platformDistance = 200.0f * i;
			const float platformPos = -400.0f - platformDistance - extraOffset;
			extraOffset += 20;
			
			CreateObject(new FloorObject(
				Vector3(0.0f, 0.0f, platformPos + 15.0f),
				Quaternion::Identity(),
				Vector3(levelWidth, 1.0f, 100.0f),
				SID("BrickMaterial")
			));

			const bool ramp = i % 2 == 0 || i == numPlatforms - 1;
			if(ramp){
				CreateObject(new RampObject(0.0f, platformPos));
			}else if(i < numPlatforms / 2){
				const float rand1 = Random::Range(-0.5f, 0.5f);
				const float rand2 = Random::Range(-0.5f, 0.5f);
				const float rand3 = Random::Range(-0.5f, 0.5f);
				const float rand4 = Random::Range(-0.5f, 0.5f);
				const float rand5 = Random::Range(-0.5f, 0.5f);

				CreateObject(new CerealBoxObject(17.5f + rand1, platformPos));
				CreateObject(new CerealBoxObject(8.5f + rand2, platformPos));
				CreateObject(new CerealBoxObject(0.0f + rand3, platformPos));
				CreateObject(new CerealBoxObject(-8.5f + rand4, platformPos));
				CreateObject(new CerealBoxObject(-17.5f + rand5, platformPos));
			}else{
				const float rand1 = Random::Range(-0.5f, 0.5f);
				const float rand2 = Random::Range(-0.5f, 0.5f);
				const float rand3 = Random::Range(-0.5f, 0.5f);
				const float rand4 = Random::Range(-0.5f, 0.5f);
				const float rand5 = Random::Range(-0.5f, 0.5f);
				const float rand6 = Random::Range(-1.0f, 1.0f);
				const float rand7 = Random::Range(-1.0f, 1.0f);
				const float rand8 = Random::Range(-1.0f, 1.0f);
				const float rand9 = Random::Range(-1.0f, 1.0f);
				const float rand10 = Random::Range(-1.0f, 1.0f);

				CreateObject(new CerealBoxObject(17.5f + rand1, platformPos + 25.0f));
				CreateObject(new CerealBoxObject(8.5f + rand2, platformPos + 25.0f));
				CreateObject(new CerealBoxObject(0.0f + rand3, platformPos + 25.0f));
				CreateObject(new CerealBoxObject(-8.5f + rand4, platformPos + 25.0f));
				CreateObject(new CerealBoxObject(-17.5f + rand5, platformPos + 25.0f));

				CreateObject(new CerealBoxObject(17.5f + rand6, platformPos - 25.0f));
				CreateObject(new CerealBoxObject(8.5f + rand7, platformPos - 25.0f));
				CreateObject(new CerealBoxObject(0.0f + rand8, platformPos - 25.0f));
				CreateObject(new CerealBoxObject(-8.5f + rand9, platformPos - 25.0f));
				CreateObject(new CerealBoxObject(-17.5f + rand10, platformPos - 25.0f));
			}
		}

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

		CreateObject(new CerealBoxObject(17.5f, -37.5f)); //Right of sink
		CreateObject(new CerealBoxObject(17.5f, 55.0f * -5.0f)); //After stove gap 1
		CreateObject(new CerealBoxObject(8.5f, 55.0f * -5.0f)); //After stove gap 2
		CreateObject(new CerealBoxObject(0.0f, 55.0f * -5.0f)); //After stove gap 3
		CreateObject(new CerealBoxObject(-8.5f, 55.0f * -5.0f)); //After stove gap 4
		CreateObject(new CerealBoxObject(-17.5f, 55.0f * -5.0f)); //After stove gap 5

		GameObject* dirLight = new GameObject(SID("DirLight"));
		dirLight->AddComponent(new DirectionalLightComponent(dirLight, Vector3(0.8f, -1.0f, -0.5f).Normalized()));
		CreateObject(dirLight);

		CreateObject(new RampObject(0.0f, -125.0f));
		CreateObject(new FloorObject(
			Vector3(-15.0f, 5.0f, -160.0f),
			Quaternion::Identity(),
			Vector3(levelWidth / 2.0f, 10.0f, 1.0f)
		));

		CreateObject(new FloorObject(
			Vector3(15.0f, 5.0f, -160.0f),
			Quaternion::Identity(),
			Vector3(levelWidth / 2.0f, 10.0f, 1.0f)
		));

		CreateObject(new HamsterObject());
		CreateObject(new BallObject(Vector3(0.0f, 5.0f, 0.0f))); //This must be the last object we create!!!

		AddSceneComponent(new GameHandler(this));
		AddSceneComponent(new GameplayCanvasSceneComponent(this, SID("MainCanvas")));
		AddSceneComponent(new SkyboxComponent(this, SID("KitchenSky")));
	}

private:
	static constexpr float levelWidth = 45.0f;
};