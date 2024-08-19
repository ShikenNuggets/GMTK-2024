#pragma once

#include <Gadget.h>

#include "Misc/MenuGuiCanvas.h"
#include "Objects/CameraObject.h"

using namespace Gadget;

class MainMenuScene : public Scene{
public:
	MainMenuScene() : Scene(SID("MainMenu")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();

		MenuGuiCanvas* canvas = new MenuGuiCanvas();
		AddSceneComponent(new CanvasSceneComponent(this, canvas));
		AddSceneComponent(new SkyboxComponent(this, SID("KitchenSky")));

		CameraObject* cameraObj = new CameraObject(Vector3::Zero(), false, SID("MenuMusic"));
		cameraObj->Rotate(0.0f, 30.0f, 0.0f);
		CreateObject(cameraObj);

		GameObject* dirLight = new GameObject(SID("DirLight"));
		dirLight->Rotate(-65.0f, -15.0f, 0.0f);
		dirLight->AddComponent(new DirectionalLightComponent(dirLight));
		CreateObject(dirLight);

		HamsterObject* hamster = new HamsterObject(Vector3(-2.5f, -1.0f, -2.5f));
		hamster->Rotate(0.0f, 0.0f, -120.0f);
		CreateObject(hamster);

		CreateObject(new FloorObject(
			hamster->GetPosition() + Vector3(0.0f, -0.5f, 0.0f),
			Quaternion::Identity(),
			Vector3(2.5f, 1.0f, 2.5f)
		));
	}
};