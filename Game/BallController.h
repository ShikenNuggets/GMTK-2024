#pragma once

#include <Gadget.h>

using namespace Gadget;

class BallController : public GameLogicComponent{
public:
	BallController(GameObject* parent_) : GameLogicComponent(SID("BallController"), parent_), rb(nullptr), jumpCooldownTimer(0.0f), currentState(GrowState::Normal){}

	virtual void OnStart(){
		GADGET_BASIC_ASSERT(parent != nullptr);

		rb = parent->GetComponent<Rigidbody>();
		GADGET_BASIC_ASSERT(rb != nullptr);
		rb->SetMaxVelocity(Vector3(10.0f, Math::Infinity, 10.0f));
		rb->SetBrakingSpeed(5.0f);

		cameraObj = App::GetSceneManager().CurrentScene()->FindWithTag(SID("Camera"));
		GADGET_BASIC_ASSERT(cameraObj != nullptr);

		GameLogicComponent::OnStart();
	}

	virtual void OnUpdate(float deltaTime_){
		GameLogicComponent::OnUpdate(deltaTime_);
		if(rb == nullptr || cameraObj == nullptr){
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

		//Jumping
		jumpCooldownTimer -= deltaTime_;
		if(App::GetInput().GetButtonDown(SID("Jump")) && jumpCooldownTimer <= 0.0f){
			Vector3 oldVelocity = rb->GetVelocity();
			rb->SetVelocity(oldVelocity.x, 0.0f, oldVelocity.z);

			rb->AddForce(Vector3::Up() * jumpForce);
			jumpCooldownTimer = jumpCooldownTime;
		}

		if(App::GetInput().GetButtonDown(SID("Grow"))){
			switch(currentState){
				case GrowState::Small:
					currentState = GrowState::Normal;
					break;
				case GrowState::Normal:
					currentState = GrowState::Big;
					break;
				default:
					break;
			}
		}else if(App::GetInput().GetButtonDown(SID("Shrink"))){
			switch(currentState){
				case BallController::GrowState::Normal:
					currentState = GrowState::Small;
					break;
				case BallController::GrowState::Big:
					currentState = GrowState::Normal;
					break;
				default:
					break;
			}
		}

		OnChangeGrowState(currentState);
	}

private:
	static constexpr float moveSpeed = 15.0f;
	static constexpr float jumpForce = 12'500.0f;
	static constexpr float jumpCooldownTime = 1.5f;

	static constexpr float defaultSize = 1.0f;
	static constexpr float shrinkSize = 0.1f;
	static constexpr float growSize = 10.0f;

	enum class GrowState{
		Small = 0,
		Normal = 1,
		Big = 2
	};

	void OnChangeGrowState(GrowState state){
		switch(state){
			case GrowState::Small:
				parent->SetScale(shrinkSize);
				break;
			case GrowState::Normal:
				parent->SetScale(defaultSize);
				break;
			case GrowState::Big:
				parent->SetScale(growSize);
				break;
			default:
				GADGET_ASSERT_NOT_IMPLEMENTED;
				break;
		}

		currentState = state;
	}

	GameObject* cameraObj;
	Rigidbody* rb;
	float jumpCooldownTimer;
	GrowState currentState;
};