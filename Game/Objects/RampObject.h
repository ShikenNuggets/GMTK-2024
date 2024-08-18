#pragma once

#include <Gadget.h>

using namespace Gadget;

class RampObject : public GameObject{
public:
	RampObject(float x_, float z_) : GameObject(SID("Ramp")){
		SetPosition(x_, 0.0f, z_);
		AddComponent(new RenderComponent(GetGUID(), SID("RampModel"), SID("BrickMaterial")));
		AddComponent(new MeshCollider(this, SID("RampModel"), ColliderShape::ConvexMesh));
	}
};