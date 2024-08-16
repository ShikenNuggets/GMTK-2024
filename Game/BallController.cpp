#include "BallController.h"

#include "HamsterController.h"

void BallController::OnGrowStateChangeBegins(GrowState state) const{
	auto hmcs = App::GetSceneManager().CurrentScene()->GetAllComponentsInScene<HamsterController>();
	for(auto* hmc : hmcs){
		hmc->OnGrowStateChangeBegins(state, scaleTime);
	}
}