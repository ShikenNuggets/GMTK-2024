#pragma once

#include <Gadget.h>

#include "GrowState.h"

using namespace Gadget;

//TODO - This whole class could be replaced by a parent/child object relationship
//Most child objects should obey the rotation of their parent, but in this case we don't
class HamsterController : public GameLogicComponent{
public:
	HamsterController(GameObject* parent_) : GameLogicComponent(SID("HamsterController"), parent_), initialScale(1.0f), ball(nullptr), currentOffset(defaultOffset), isChangingState(false), stateChangeTimer(0.0f), stateChangeTime(0.0f), targetOffset(){}

	virtual void OnStart(){
		ball = App::GetSceneManager().CurrentScene()->FindWithTag(SID("Ball"));
		GADGET_BASIC_ASSERT(parent != nullptr);
		GADGET_BASIC_ASSERT(ball != nullptr);

		initialScale = parent->GetScale().x;

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
	static constexpr Vector3 defaultOffset = Vector3(0.0f, -0.8f, 0.0f);
	static constexpr Vector3 shrinkOffset = Vector3(0.0f, -0.08f, 0.0f);
	static constexpr Vector3 growOffset = Vector3(0.0f, -9.0f, 0.0f);

	float initialScale;
	GameObject* ball;
	Vector3 currentOffset;
	
	bool isChangingState;
	float stateChangeTimer;
	float stateChangeTime;
	Vector3 oldOffset;
	Vector3 targetOffset;
};