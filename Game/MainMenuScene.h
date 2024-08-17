#pragma once

#include <Gadget.h>

#include "CameraObject.h"

using namespace Gadget;

class MainMenuScene : public Scene{
public:
	MainMenuScene() : Scene(SID("MainMenu")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();

		//TODO - GuiAnchor parameter does nothing
		//TODO - GUI left/right position makes no sense
		GuiTextElement* titleText = new GuiTextElement(SID("TitleText"), "[Title]", SID("ArialFont"), Vector2(0.0f, 0.8f), Vector2(0.5f, 0.2f), GuiAnchor::Center);
		GuiButton* startButton = new GuiButton(SID("StartButton"), "Start", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, 0.25f), Vector2(0.2f, 0.1f), GuiAnchor::Center);
		GuiButton* creditsButton = new GuiButton(SID("CreditsButton"), "Credits", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.1f), GuiAnchor::Center);
		GuiButton* quitButton = new GuiButton(SID("QuitButton"), "Quit", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, -0.25f), Vector2(0.2f, 0.1f), GuiAnchor::Center);

		startButton->SetOnClickCallback([](ButtonID id_, const Vector2& v){ App::GetSceneManager().RequestSceneLoad(SID("TestScene")); });
		creditsButton->SetOnClickCallback([](ButtonID id_, const Vector2& v_){});
		quitButton->SetOnClickCallback([](ButtonID id_, const Vector2& v){ App::CloseGame(); });

		GuiCanvas* canvas = new GuiCanvas(SID("MainCanvas"));
		canvas->AddElement(titleText);
		canvas->AddElement(startButton);
		canvas->AddElement(creditsButton);
		canvas->AddElement(quitButton);

		AddSceneComponent(new CanvasSceneComponent(this, canvas));

		CreateObject(new CameraObject(Vector3::Zero(), false));
	}
};