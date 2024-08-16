#pragma once

#include <Gadget.h>

#include "TestScene.h"

using namespace Gadget;

class HamsterGame : public GameInterface{
public:
	HamsterGame() : GameInterface("HamsterGame"){}

	void LoadGame(){
		DefineInputs();
		DefineMaterials();

		App::GetInstance().GetSceneManager().AddScene(new TestScene());
	}

	void DefineInputs(){
	}

	void DefineMaterials(){
		App::GetMaterialCache().AddMaterial(SID("Invalid"), new ColorMaterial(Gadget::Color::Pink(), SID("ColorShader"))); //TODO - The engine should add this on its own

		App::GetMaterialCache().AddMaterial(SID("BrickMaterial"), new DiffuseTextureMaterial(SID("CubeTexture"), SID("UnlitShader")));
		App::GetMaterialCache().AddMaterial(SID("GlassMaterial"), new DiffuseTextureMaterial(SID("GlassTexture"), SID("UnlitShader")));
		App::GetMaterialCache().AddMaterial(SID("HamsterMaterial"), new DiffuseTextureMaterial(SID("HamsterTexture"), SID("UnlitShader")));
	}
};