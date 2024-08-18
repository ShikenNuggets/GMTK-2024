#include "GameHandler.h"

#include "BallController.h"
#include "CameraObject.h"

void GameHandler::TriggerGameOver(){
	auto gameplayCanvas = parent->GetSceneComponent<GameplayCanvasSceneComponent>();
	if(gameplayCanvas != nullptr){
		gameplayCanvas->OnGameOver();
	}

	GameObject* go = parent->FindWithTag(SID("Camera"));
	CameraObject* cam = dynamic_cast<CameraObject*>(go);
	if(cam != nullptr){
		cam->OnGameOver();
	}
}