#include "BallController.h"

#include "CameraController.h"
#include "HamsterController.h"

void BallController::OnGrowStateChangeBegins(GrowState state) const{
	auto hmcs = App::GetSceneManager().CurrentScene()->GetAllComponentsInScene<HamsterController>();
	for(auto* hmc : hmcs){
		hmc->OnGrowStateChangeBegins(state, scaleTime);
	}

	auto cctrls = App::GetSceneManager().CurrentScene()->GetAllComponentsInScene<CameraController>();
	for(auto* cctrl : cctrls){
		cctrl->OnGrowStateChangeBegins(state, scaleTime);
	}
}