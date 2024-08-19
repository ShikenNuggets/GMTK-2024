#pragma once

#include <Gadget.h>

#include "Components/GameHandler.h"
#include "Components/GameplayCanvasSceneComponent.h"
#include "Misc/GrowState.h"

using namespace Gadget;

class BallController : public GameLogicComponent{
public:
	BallController(GameObject* parent_) : GameLogicComponent(SID("BallController"), parent_), cameraObj(nullptr), rb(nullptr), gameplayCanvas(nullptr), jumpCooldownTimer(0.0f), currentState(GrowState::Normal), canChangeState(true), gameOver(false), oldScale(sizes[GrowState::Normal]), targetScale(sizes[GrowState::Normal]), scaleTimer(0.0f), curMaxVelocity(minMaxVelocity){}

	virtual void OnStart(){
		GADGET_BASIC_ASSERT(parent != nullptr);

		rb = parent->GetComponent<Rigidbody>();
		GADGET_BASIC_ASSERT(rb != nullptr);
		rb->SetMaxVelocity(Vector3(minMaxVelocity, Math::Infinity, minMaxVelocity));
		rb->SetBrakingSpeed(7.5f);

		cameraObj = App::GetSceneManager().CurrentScene()->FindWithTag(SID("Camera"));
		GADGET_BASIC_ASSERT(cameraObj != nullptr);

		gameplayCanvas = App::GetSceneManager().CurrentScene()->GetSceneComponent<GameplayCanvasSceneComponent>();
		GADGET_BASIC_ASSERT(gameplayCanvas != nullptr);

		GameLogicComponent::OnStart();
	}

	virtual void OnUpdate(float deltaTime_){
		GameLogicComponent::OnUpdate(deltaTime_);

		#ifdef GADGET_DEBUG
		if(App::GetInput().GetButtonDown(ButtonID::Keyboard_Escape)){
			App::CloseGame();
		}

		if(App::GetInput().GetButtonDown(ButtonID::Keyboard_R)){
			App::GetSceneManager().RequestReloadCurrentScene();
		}

		if(App::GetInput().GetButtonDown(ButtonID::Keyboard_M)){
			double curVolume = App::GetConfig().GetOptionFloat(EngineVars::Audio::musicVolumeKey);
			if(curVolume < 0.5){
				curVolume = 1.0;
			}else{
				curVolume = 0.0;
			}
			App::GetConfig().SetOption(EngineVars::Audio::sectionName, EngineVars::Audio::musicVolumeKey, curVolume);
		}

		if(App::GetInput().GetButtonDown(ButtonID::Keyboard_P)){
			GADGET_LOG(SID("HAMSTER"), std::to_string(parent->GetPosition().z));
		}
		#endif // GADGET_DEBUG

		if(gameOver || rb == nullptr || cameraObj == nullptr){
			return;
		}

		//Rolling
		float hor = App::GetInput().GetAxis(SID("Horizontal"));
		float ver = App::GetInput().GetAxis(SID("Vertical"));

		Vector3 direction = Vector3(hor, 0.0f, ver);
		float magnitude = 0.0f;
		if(Math::IsNearZero(hor) && Math::IsNearZero(ver)){
			direction = Vector3::Zero();
		}else{
			magnitude = direction.Magnitude();
			direction.Normalize();
			
		}

		rb->AddVelocity(direction * magnitude * moveSpeed * deltaTime_);

		if(currentState == GrowState::Big || rb->GetVelocity().z >= 0.0f){
			curMaxVelocity = Math::Clamp(minMaxVelocity, maxMaxVelocity, curMaxVelocity - (deltaTime_ * 10.0f));
		}else if(currentState == GrowState::Small || rb->GetVelocity().z < 0.0f){
			curMaxVelocity = Math::Clamp(minMaxVelocity, maxMaxVelocity, curMaxVelocity + (deltaTime_));
		}
		rb->SetMaxVelocity(Vector3(curMaxVelocity, Math::Infinity, curMaxVelocity));

		//Jumping
		jumpCooldownTimer -= deltaTime_;
		if(App::GetInput().GetButtonHeld(SID("Jump")) && jumpCooldownTimer <= 0.0f){
			Vector3 oldVelocity = rb->GetVelocity();
			rb->SetVelocity(oldVelocity.x, 0.0f, oldVelocity.z);

			float jumpForceToUse = jumpForce;
			if(currentState == GrowState::Big){
				jumpForceToUse /= 1.25f;
			}

			rb->AddVelocity(Vector3::Up() * jumpForceToUse); //TODO - Add Force appears to be framerate dependent
			jumpCooldownTimer = jumpCooldownTime;

			if(gameplayCanvas != nullptr){
				gameplayCanvas->StartJumpBar(jumpCooldownTime);
			}
		}

		//Growing and Shrinking
		if(App::GetInput().GetButtonDown(SID("Grow")) && currentState < GrowState::Big && canChangeState){
			canChangeState = false;
			oldScale = sizes[currentState];
			currentState = (GrowState)((int)currentState + 1);
			targetScale = sizes[currentState];
			scaleTimer = 0.0f;
			rb->SetMass(scales[currentState]);
			OnGrowStateChangeBegins(currentState);
		}else if(App::GetInput().GetButtonDown(SID("Shrink")) && currentState > GrowState::Small && canChangeState){
			canChangeState = false;
			oldScale = sizes[currentState];
			currentState = (GrowState)((int)currentState - 1);
			targetScale = sizes[currentState];
			scaleTimer = 0.0f;
			rb->SetMass(scales[currentState]);
			OnGrowStateChangeBegins(currentState);
		}

		if(!canChangeState){
			scaleTimer += deltaTime_;
			if(scaleTimer >= scaleTime){
				GADGET_BASIC_ASSERT(currentState <= GrowState::Big);
				parent->SetScale(targetScale);
				canChangeState = true;
			}else{
				parent->SetScale(Math::Lerp(oldScale, targetScale, scaleTimer / scaleTime));
			}
		}

		//Leave Tutorial Area
		if(parent->GetPosition().z < -200.0f){
			GameHandler* handler = App::GetSceneManager().CurrentScene()->GetSceneComponent<GameHandler>();
			GADGET_BASIC_ASSERT(handler != nullptr);
			if(handler != nullptr){
				handler->TriggerEndTutorial();
			}
		}

		//Game Over
		if(parent->GetPosition().y < gameOverHeight){
			GameHandler* handler = App::GetSceneManager().CurrentScene()->GetSceneComponent<GameHandler>();
			GADGET_BASIC_ASSERT(handler != nullptr);
			if(handler != nullptr){
				handler->TriggerGameOver();
			}

			gameOver = true;
		}

		//Win
		if(parent->GetPosition().z < -4650.0f){
			GameHandler* handler = App::GetSceneManager().CurrentScene()->GetSceneComponent<GameHandler>();
			GADGET_BASIC_ASSERT(handler != nullptr);
			if(handler != nullptr){
				handler->TriggerWinState();
			}
		}
	}

	GrowState GetGrowState() const{ return currentState; }

	void OnGameOver(){
		gameOver = true;
	}

private:
	static constexpr float moveSpeed = 15.0f;
	static constexpr float jumpForce = 18.0f;
	static constexpr float jumpCooldownTime = 1.5f;
	static constexpr float scaleTime = 0.25f;

	static constexpr float minMaxVelocity = 20.0f;
	static constexpr float maxMaxVelocity = 50.0f;

	static constexpr float gameOverHeight = -5.0f;

	//TODO - constexpr Gadget::StaticArray
	//TODO - Brace initializer for Gadget::StaticArray
	static constexpr std::array<float, 3> sizes{
		0.1f, //Shrink
		1.0f, //Normal
		5.0f, //Grow
	};

	static constexpr std::array<float, 3> scales{
		0.1f, //Shrink
		1.0f, //Normal
		100.0f, //Grow
	};

	GameObject* cameraObj;
	Rigidbody* rb;
	GameplayCanvasSceneComponent* gameplayCanvas;
	float jumpCooldownTimer;
	GrowState currentState;
	bool canChangeState;
	bool gameOver;

	float oldScale;
	float targetScale;
	float scaleTimer;
	float curMaxVelocity;

	void OnGrowStateChangeBegins(GrowState state) const;
};