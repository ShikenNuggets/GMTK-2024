#pragma once

#include <Gadget.h>

using namespace Gadget;

//TODO - This whole class could be replaced by a parent/child object relationship
//Most child objects should obey the rotation of their parent, but in this case we don't
class HamsterController : public GameLogicComponent{
public:
	HamsterController(GameObject* parent_) : GameLogicComponent(SID("HamsterController"), parent_), ball(nullptr){}

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

		parent->SetPosition(ball->GetPosition() + offset);
		parent->SetScale(ball->GetScale() * initialScale);

		GameLogicComponent::OnUpdate(deltaTime_);
	}

private:
	static constexpr Vector3 offset = Vector3(0.0f, -0.8f, 0.0f);

	float initialScale;
	GameObject* ball;
};