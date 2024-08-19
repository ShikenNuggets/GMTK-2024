#pragma once

#include <Gadget.h>

#include "Misc/GrowState.h"

using namespace Gadget;

//TODO - This whole class could be replaced by a parent/child object relationship
//Most child objects should obey the rotation of their parent, but in this case we don't
class HamsterController : public GameLogicComponent{
public:
	HamsterController(GameObject* parent_) : GameLogicComponent(SID("HamsterController"), parent_), initialScale(1.0f), ball(nullptr), currentOffset(defaultOffset), isChangingState(false), stateChangeTimer(0.0f), stateChangeTime(0.0f), targetOffset(), isMoving(false), startRotationX(0.0f), startedMovingTime(0.0f){}

	virtual void OnStart(){
		ball = App::GetSceneManager().CurrentScene()->FindWithTag(SID("Ball"));
		GADGET_BASIC_ASSERT(parent != nullptr);

		initialScale = parent->GetScale().x;
		startRotationX = parent->GetRotation().ToEuler().x;

		GameLogicComponent::OnStart();
	}

	virtual void OnUpdate(float deltaTime_){
		if(ball == nullptr || parent == nullptr){
			return;
		}

		//TODO - Some kind of generic timer construct could reduce the amount of boilerplate needed for things like this
		if(isChangingState){
			stateChangeTimer += deltaTime_;
			if(stateChangeTimer >= stateChangeTime){
				currentOffset = targetOffset;
				isChangingState = false;
			}else{
				currentOffset = Vector3::Lerp(oldOffset, targetOffset, stateChangeTimer / stateChangeTime);
			}
		}

		parent->SetPosition(ball->GetPosition() + currentOffset);
		parent->SetScale(ball->GetScale() * initialScale);

		if(App::GetInput().GetAxis(SID("Horizontal")) != 0.0f || App::GetInput().GetAxis(SID("Vertical")) != 0.0f){
			if(!isMoving){
				isMoving = true;
				startedMovingTime = App::GetTime().TimeSinceStartup();
			}
		}else{
			isMoving = false;
		}

		if(isMoving){
			float rotAngle = startRotationX + (Math::Sin(500 * App::GetTime().TimeSinceStartup() - startedMovingTime) * 5.0f);
			Euler rotation = parent->GetRotation().ToEuler();
			rotation.x = rotAngle;
			parent->SetRotation(rotation);
		}else{
			Euler rotation = parent->GetRotation().ToEuler();
			rotation.x = Math::Lerp(rotation.x, startRotationX, deltaTime_); //This is not really correct but it gives us a better result than the alternative
			parent->SetRotation(rotation);
		}

		GameLogicComponent::OnUpdate(deltaTime_);
	}

	virtual void OnGrowStateChangeBegins(GrowState state_, float stateChangeTime_){
		GADGET_BASIC_ASSERT(stateChangeTime_ > 0.0f);
		GADGET_BASIC_ASSERT(!isChangingState);

		switch(state_){
			case Small:
				targetOffset = shrinkOffset;
				break;
			case Normal:
				targetOffset = defaultOffset;
				break;
			case Big:
				targetOffset = growOffset;
				break;
			default:
				GADGET_ASSERT_NOT_IMPLEMENTED;
				break;
		}

		oldOffset = currentOffset;
		stateChangeTime = stateChangeTime_;
		stateChangeTimer = 0.0f;
		isChangingState = true;
	}

private:
	static constexpr Vector3 defaultOffset = Vector3(0.0f, -0.81f, 0.0f);
	static constexpr Vector3 shrinkOffset = Vector3(0.0f, -0.081f, 0.0f);
	static constexpr Vector3 growOffset = Vector3(0.0f, -4.1f, 0.0f);

	float initialScale;
	GameObject* ball;
	Vector3 currentOffset;
	
	bool isChangingState;
	float stateChangeTimer;
	float stateChangeTime;
	Vector3 oldOffset;
	Vector3 targetOffset;

	bool isMoving;
	float startRotationX;
	float startedMovingTime;
};