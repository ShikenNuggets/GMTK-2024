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

		App::GetSceneManager().AddScene(new TestScene());

		App::GetPhysics().SetWorldGravity(-20.0f);
	}

	void DefineInputs(){
		Axis horizontal = Axis(SID("Horizontal"));
		horizontal.AddButtonAxis(ButtonAxis(ButtonID::Keyboard_A, ButtonID::Keyboard_D));
		horizontal.AddButtonAxis(ButtonAxis(ButtonID::Keyboard_Arrow_Left, ButtonID::Keyboard_Arrow_Right));
		horizontal.AddAxisID(AxisID::Gamepad_LeftStick_Horizontal);
		App::GetInput().DefineAxis(horizontal);

		Axis vertical = Axis(SID("Vertical"));
		vertical.AddButtonAxis(ButtonAxis(ButtonID::Keyboard_W, ButtonID::Keyboard_S));
		vertical.AddButtonAxis(ButtonAxis(ButtonID::Keyboard_Arrow_Up, ButtonID::Keyboard_Arrow_Down));
		vertical.AddAxisID(AxisID::Gamepad_LeftStick_Vertical);
		App::GetInput().DefineAxis(vertical);

		Button jump = Button(SID("Jump"));
		jump.AddButtonID(ButtonID::Keyboard_Space);
		jump.AddButtonID(ButtonID::Gamepad_Face_Down);
		App::GetInput().DefineButton(jump);
	}

	void DefineMaterials(){
		App::GetMaterialCache().AddMaterial(SID("Invalid"), new ColorMaterial(Gadget::Color::Pink(), SID("ColorShader"))); //TODO - The engine should add this on its own

		App::GetMaterialCache().AddMaterial(SID("BrickMaterial"), new DiffuseTextureMaterial(SID("CubeTexture"), SID("UnlitShader")));
		App::GetMaterialCache().AddMaterial(SID("GlassMaterial"), new DiffuseTextureMaterial(SID("GlassTexture"), SID("UnlitShader")));
		App::GetMaterialCache().AddMaterial(SID("HamsterMaterial"), new DiffuseTextureMaterial(SID("HamsterTexture"), SID("UnlitShader")));
	}
};