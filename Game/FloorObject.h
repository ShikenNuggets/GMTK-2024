#pragma once

#include <Gadget.h>

using namespace Gadget;

class FloorObject : public GameObject{
public:
	FloorObject(const Vector3& pos_, const Quaternion& rot_ = Quaternion::Identity(), const Vector3& scale_ = Vector3::Fill(1.0f), StringID material = SID("BrickMaterial")) : GameObject(SID("Floor")){
		SetPosition(pos_);
		SetRotation(rot_);
		SetScale(scale_);
		AddComponent(new RenderComponent(GetGUID(), SID("CubeModel"), material));
		AddComponent(new CubeCollider(this));
	}
};