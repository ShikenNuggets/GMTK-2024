#include "GameHandler.h"

#include "GameLogic/BallController.h"
#include "Objects/CameraObject.h"

void GameHandler::OnUpdate(float deltaTime_){
	if(App::GetInput().GetButtonDown(SID("Pause"))){
		if(!isPaused){
			Pause();
		}else{
			Unpause();
		}

		isPaused = !isPaused;
	}
}

void GameHandler::Pause(){
	App::GetTime().SetTimeScale(0.0f);

	GameObject* go = parent->FindWithTag(SID("Camera"));
	AudioSource* music = go->GetComponent<AudioSource>();
	if(music != nullptr){
		music->Pause(true);
	}

	GADGET_BASIC_ASSERT(parent != nullptr);
	auto gameplayCanvas = parent->GetSceneComponent<GameplayCanvasSceneComponent>();
	if(gameplayCanvas != nullptr){
		gameplayCanvas->EnablePauseUI(true);
	}
}

void GameHandler::Unpause(){
	App::GetTime().SetTimeScale(1.0f);

	GameObject* go = parent->FindWithTag(SID("Camera"));
	AudioSource* music = go->GetComponent<AudioSource>();
	if(music != nullptr){
		music->Pause(false);
	}

	GADGET_BASIC_ASSERT(parent != nullptr);
	auto gameplayCanvas = parent->GetSceneComponent<GameplayCanvasSceneComponent>();
	if(gameplayCanvas != nullptr){
		gameplayCanvas->EnablePauseUI(false);
	}
}

void GameHandler::TriggerEndTutorial(){
	GADGET_BASIC_ASSERT(parent != nullptr);
	auto gameplayCanvas = parent->GetSceneComponent<GameplayCanvasSceneComponent>();
	if(gameplayCanvas != nullptr){
		gameplayCanvas->OnEndTutorial();
	}
}

void GameHandler::TriggerWinState(){
	GADGET_BASIC_ASSERT(parent != nullptr);
	auto gameplayCanvas = parent->GetSceneComponent<GameplayCanvasSceneComponent>();
	if(gameplayCanvas != nullptr){
		gameplayCanvas->OnWinState();
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