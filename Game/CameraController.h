#pragma once

#include <Gadget.h>

#include "GrowState.h"

using namespace Gadget;

class CameraController : public GameLogicComponent{
public:
	CameraController(GameObject* parent_) : GameLogicComponent(SID("CameraController"), parent_), ball(nullptr), currentOffset(defaultOffset), isChangingState(false), stateChangeTimer(0.0f), stateChangeTime(0.0f), oldOffset(defaultOffset), targetOffset(defaultOffset){}

	virtual void OnStart(){
		ball = App::GetSceneManager().CurrentScene()->FindWithTag(SID("Ball"));
		GADGET_BASIC_ASSERT(parent != nullptr);
		GADGET_BASIC_ASSERT(ball != nullptr);

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

		Vector3 newPos = ball->GetPosition() + currentOffset;
		newPos.y = Math::Clamp(currentOffset.y, Math::Infinity, newPos.y);
		parent->SetPosition(newPos);

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
	static constexpr Vector3 defaultOffset = Vector3(0.0f, 3.0f, 10.0f);
	static constexpr Vector3 shrinkOffset = Vector3(0.0f, 1.0f, 3.0f);
	static constexpr Vector3 growOffset = Vector3(0.0f, 10.0f, 30.0f);

	GameObject* ball;
	Vector3 currentOffset;

	bool isChangingState;
	float stateChangeTimer;
	float stateChangeTime;
	Vector3 oldOffset;
	Vector3 targetOffset;
};