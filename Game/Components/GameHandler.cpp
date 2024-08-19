#include "GameHandler.h"

#include "GameLogic/BallController.h"
#include "Objects/CameraObject.h"

void GameHandler::TriggerGameOver(){
	GADGET_BASIC_ASSERT(parent != nullptr);
	auto gameplayCanvas = parent->GetSceneComponent<GameplayCanvasSceneComponent>();
	if(gameplayCanvas != nullptr){
		gameplayCanvas->OnGameOver();
	}

	GameObject* go = parent->FindWithTag(SID("Camera"));
	CameraObject* cam = dynamic_cast<CameraObject*>(go);
	if(cam != nullptr){
		cam->OnGameOver();
	}

	GameObject* ballGo = parent->FindWithTag(SID("Ball"));
	BallController* ballControl = ballGo->GetComponent<BallController>();
	if(ballControl != nullptr){
		ballControl->OnGameOver();
	}
}