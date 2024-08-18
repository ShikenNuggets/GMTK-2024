#pragma once

#include <Gadget.h>

#include "GameLogic/BallController.h"

using namespace Gadget;

class BallObject : public GameObject{
public:
	BallObject(const Vector3& startPosition_ = Vector3::Zero()) : GameObject(SID("Ball")){
		GADGET_BASIC_ASSERT(startPosition_.IsValid());
		SetPosition(startPosition_);
		AddComponent(new RenderComponent(GetGUID(), SID("SphereModel"), SID("GlassMaterial")));
		AddComponent(new SphereCollider(this, 1.0f));
		AddComponent(new Rigidbody(this, 1.0f, true));
		AddComponent(new BallController(this));
		AddTag(SID("Ball"));
	}
};