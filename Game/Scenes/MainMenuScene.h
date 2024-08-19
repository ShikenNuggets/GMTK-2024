#pragma once

#include <Gadget.h>

#include "Objects/CameraObject.h"

using namespace Gadget;

class MainMenuScene : public Scene{
public:
	MainMenuScene() : Scene(SID("MainMenu")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();

		//TODO - GuiAnchor parameter does nothing
		//TODO - GUI left/right position makes no sense
		GuiTextElement* titleText = new GuiTextElement(SID("TitleText"), "Weird Hamster Ball Game", SID("ArialFont"), Vector2(0.0f, 0.8f), Vector2(1.5f, 0.5f), GuiAnchor::Center);
		GuiButton* startButton = new GuiButton(SID("StartButton"), "Start", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, 0.25f), Vector2(0.2f, 0.1f), GuiAnchor::Center);
		GuiButton* creditsButton = new GuiButton(SID("CreditsButton"), "Credits", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.1f), GuiAnchor::Center);
		GuiButton* quitButton = new GuiButton(SID("QuitButton"), "Quit", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, -0.25f), Vector2(0.2f, 0.1f), GuiAnchor::Center);

		startButton->SetOnClickCallback([](ButtonID id_, const Vector2& v){ App::GetSceneManager().RequestSceneLoad(SID("KitchenScene")); });
		creditsButton->SetOnClickCallback([](ButtonID id_, const Vector2& v_){});
		quitButton->SetOnClickCallback([](ButtonID id_, const Vector2& v){ App::CloseGame(); });

		GuiCanvas* canvas = new GuiCanvas(SID("MainCanvas"));
		canvas->AddElement(titleText);
		canvas->AddElement(startButton);
		canvas->AddElement(creditsButton);
		canvas->AddElement(quitButton);

		AddSceneComponent(new CanvasSceneComponent(this, canvas));
		AddSceneComponent(new SkyboxComponent(this, SID("KitchenSky")));

		CameraObject* cameraObj = new CameraObject(Vector3::Zero(), false, SID("MenuMusic"));
		cameraObj->Rotate(0.0f, 30.0f, 0.0f);
		CreateObject(cameraObj);

		GameObject* dirLight = new GameObject(SID("DirLight"));
		dirLight->AddComponent(new DirectionalLightComponent(dirLight, Vector3(0.8f, -1.0f, -0.5f).Normalized()));
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