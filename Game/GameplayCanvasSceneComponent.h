#pragma once

#include <Gadget.h>

using namespace Gadget;

class GameplayCanvasSceneComponent : public CanvasSceneComponent{
public:
	GameplayCanvasSceneComponent(Scene* parent_, StringID name_) : CanvasSceneComponent(parent_, new GuiCanvas(name_)), jumpBar(nullptr), jumpBarTimer(0.0f), jumpBarTime(0.0f){
		jumpBar = new GuiTextureElement(SID("JumpBar"), SID("ButtonTexture"), Vector2(0.0f, -0.8f), Vector2(0.0f, jumpBarHeight), GuiAnchor::Center);
		GetCanvas().AddElement(jumpBar);
	}

	virtual void OnUpdate(float deltaTime_) override{
		CanvasSceneComponent::OnUpdate(deltaTime_);

		jumpBarTimer -= deltaTime_;
		if(jumpBarTimer <= 0.0f){
			jumpBar->SetSize(Vector2(0.0f, jumpBarHeight));
		}else{
			jumpBar->SetSize(Vector2(jumpBarFullWidth * (jumpBarTimer / jumpBarTime), jumpBarHeight));
		}
	}

	void StartJumpBar(float jumpBarTime_){
		GADGET_BASIC_ASSERT(Math::IsValidNumber(jumpBarTime_));
		jumpBarTime = jumpBarTime_;
		jumpBarTimer = jumpBarTime_;
	}

private:
	static constexpr float jumpBarFullWidth = 0.5f;
	static constexpr float jumpBarHeight = 0.01f;

	GuiTextureElement* jumpBar;
	float jumpBarTimer;
	float jumpBarTime;
};