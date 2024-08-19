#pragma once

#include <Gadget.h>
#include <Graphics/GUI/FpsDisplayElement.h>
#include <Graphics/GUI/TimerDisplayElement.h>

#include "GameHandler.h"

using namespace Gadget;

class GameplayCanvasSceneComponent : public CanvasSceneComponent{
public:
	GameplayCanvasSceneComponent(Scene* parent_, StringID name_) : CanvasSceneComponent(parent_, new GuiCanvas(name_)), jumpBar(nullptr), jumpBarTimer(0.0f), jumpBarTime(0.0f){
		jumpBar = new GuiTextureElement(SID("JumpBar"), SID("ButtonTexture"), Vector2(0.0f, -0.8f), Vector2(0.0f, jumpBarHeight), GuiAnchor::Center);
		GetCanvas().AddElement(jumpBar);

		timer = new TimerDisplayElement(SID("Timer"), SID("ArialFont"), TimerDisplayElement::Type::TimerToZero, musicDuration, Vector2(0.0f, 0.8f), Gadget::Vector2(0.5f, 0.25f), GuiAnchor::Center);
		GetCanvas().AddElement(timer);

		auto fps = new FpsDisplayElement(SID("FPS"), SID("ArialFont"), Gadget::Vector2(1.65f, -0.95f), Gadget::Vector2(0.125f, 0.125f), Gadget::GuiAnchor::Center);
		fps->SetColor(Color::Yellow());
		GetCanvas().AddElement(fps);
	}

	virtual void OnUpdate(float deltaTime_) override{
		CanvasSceneComponent::OnUpdate(deltaTime_);

		jumpBarTimer -= deltaTime_;
		if(jumpBarTimer <= 0.0f){
			jumpBar->SetSize(Vector2(0.0f, jumpBarHeight));
		}else{
			jumpBar->SetSize(Vector2(jumpBarFullWidth * (jumpBarTimer / jumpBarTime), jumpBarHeight));
		}

		if(timer->GetTimer() <= musicDuration - finalWarningTime){
			timer->SetColor(Color::Red());
		}

		if(timer->GetTimer() <= 1.0f){
			parent->GetSceneComponent<GameHandler>()->TriggerGameOver();
		}

		if(gameOverTimerStarted){
			gameOverTimer += deltaTime_;

			if(gameOverTimer > 5.0f){
				App::GetSceneManager().RequestReloadCurrentScene();
				gameOverTimerStarted = false;
			}
		}

		if(winTimerStarted){
			gameOverTimer += deltaTime_;
			if(gameOverTimer > 5.0f){
				App::GetSceneManager().RequestSceneLoad(SID("MainMenu"));
				winTimerStarted = false;
			}
		}
	}

	void StartJumpBar(float jumpBarTime_){
		GADGET_BASIC_ASSERT(Math::IsValidNumber(jumpBarTime_));
		jumpBarTime = jumpBarTime_;
		jumpBarTimer = jumpBarTime_;
	}

	void OnWinState(){
		std::vector<GuiElement*> elements;
		GetCanvas().GetElements(elements);
		for(auto* e : elements){
			e->SetIsActive(false);
		}

		GetCanvas().AddElement(new GuiTextElement(SID("WinText"), "You Win!", SID("ArialFont"), Vector2(0.0f, 0.8f), Gadget::Vector2(1.0f, 0.5f), GuiAnchor::Center));
		winTimerStarted = true;
	}

	void OnGameOver(){
		std::vector<GuiElement*> elements;
		GetCanvas().GetElements(elements);
		for(auto* e : elements){
			e->SetIsActive(false);
		}

		gameOverTimerStarted = true;
	}

private:
	static constexpr float musicDuration = 145.538f;
	static constexpr float finalWarningTime = 106.596f;

	static constexpr float jumpBarFullWidth = 0.5f;
	static constexpr float jumpBarHeight = 0.01f;

	GuiTextureElement* jumpBar;
	TimerDisplayElement* timer;
	float jumpBarTimer;
	float jumpBarTime;

	bool gameOverTimerStarted = false;
	bool winTimerStarted = false;
	float gameOverTimer = 0.0f;
};