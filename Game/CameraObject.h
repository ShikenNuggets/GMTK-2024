#pragma once

#include <Gadget.h>

#include "CameraController.h"

using namespace Gadget;

class CameraObject : public GameObject{
public:
	CameraObject(const Vector3& startPosition_, bool controllable_, StringID music_ = StringID::None) : GameObject(){
		SetPosition(startPosition_);
		SetRotation(-15.0f, 0.0f, 0.0f);
		AddComponent(new CameraComponent(this));
		AddComponent(new AudioListener(this));

		if(controllable_){
			AddComponent(new CameraController(this));
		}

		if(music_ != StringID::None){
			AddComponent(new AudioSource(this, music_, SoundType::_2D, VolumeChannel::Music, SoundPlayMode::PlayOnce));
		}

		AddTag(SID("Camera"));
	}

	void OnGameOver(){
		CameraController* camera = GetComponent<CameraController>();
		if(camera != nullptr){
			camera->OnGameOver();
		}
	}
};