#pragma once

#include <Gadget.h>

using namespace Gadget;

class CerealBoxObject : public GameObject{
public:
	CerealBoxObject(float x_, float z_) : GameObject(SID("CerealBox")){
		SetPosition(Vector3(x_, 7.5f, z_));
		SetRotation(-90.0f, 0.0f, 0.0f);
		AddComponent(new RenderComponent(GetGUID(), SID("CerealBoxModel"), SID("CerealBoxMaterial")));
		AddComponent(new Rigidbody(this, 25.0f, true));
		AddComponent(new CubeCollider(this, 4.0f, 2.2f, 4.5f));
	}
};