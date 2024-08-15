#include <iostream>

#pragma warning(disable : 26819) //Kill unfixable warning from SDL2
#include <SDL.h>
#pragma warning(default : 26819)

#ifdef GADGET_DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#endif //GADGET_DEBUG

#include <Gadget.h>
#include <Memory/GlobalAllocator.h>

class SampleScene : public Gadget::Scene{
public:
	SampleScene() : Scene(SID("SampleScene")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();
	}
};

class SampleGame : public Gadget::GameInterface{
public:
	SampleGame() : GameInterface("SampleGame"){}

	void LoadGame(){
		Gadget::App::GetInstance().GetSceneManager().AddScene(new SampleScene());
	}
};

int main(int argc, char* argv[]){
#ifdef GADGET_DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // GADGET_DEBUG

	if(argc > 0){
		std::cout << "Launching with arguments:\n";
	}

	for(int i = 0; i < argc; i++){
		std::cout << argv[i] << "\n";
	}

	SampleGame game = SampleGame();

	try{
		Gadget::App::GetInstance().Run(game);
	}catch([[maybe_unused]] const std::runtime_error& e){
		_ASSERT(false);
	}

	Gadget::App::DeleteInstance();

	return 0;
}