#pragma once

#include <Gadget.h>

#include "Scenes/KitchenScene.h"
#include "Scenes/MainMenuScene.h"

using namespace Gadget;

class HamsterGame : public GameInterface{
public:
	HamsterGame() : GameInterface("HamsterGame"){}

	void LoadGame(){
		DefineInputs();
		DefineMaterials();

		App::GetSceneManager().AddScene(new MainMenuScene());
		App::GetSceneManager().AddScene(new KitchenScene());

		App::GetPhysics().SetWorldGravity(-25.0f);

		App::GetRenderer().SetCullFace(Renderer::CullFace::None);
	}

	void DefineInputs(){
		Axis horizontal = Axis(SID("Horizontal"));
		horizontal.AddButtonAxis(ButtonAxis(ButtonID::Keyboard_A, ButtonID::Keyboard_D));
		horizontal.AddButtonAxis(ButtonAxis(ButtonID::Keyboard_Arrow_Left, ButtonID::Keyboard_Arrow_Right));
		horizontal.AddAxisID(AxisID::Gamepad_LeftStick_Horizontal);
		App::GetInput().DefineAxis(horizontal);

		Axis vertical = Axis(SID("Vertical"));
		vertical.AddButtonAxis(ButtonAxis(ButtonID::Keyboard_S, ButtonID::Keyboard_W));
		vertical.AddButtonAxis(ButtonAxis(ButtonID::Keyboard_Arrow_Down, ButtonID::Keyboard_Arrow_Up));
		vertical.AddAxisID(AxisID::Gamepad_LeftStick_Vertical);
		vertical.Invert(true);
		App::GetInput().DefineAxis(vertical);

		Button jump = Button(SID("Jump"));
		jump.AddButtonID(ButtonID::Keyboard_Space);
		jump.AddButtonID(ButtonID::Gamepad_Face_Down);
		App::GetInput().DefineButton(jump);

		Button grow = Button(SID("Grow"));
		grow.AddButtonID(ButtonID::Keyboard_E);
		grow.AddButtonID(ButtonID::Gamepad_Shoulder_Right1);
		App::GetInput().DefineButton(grow);

		Button shrink = Button(SID("Shrink"));
		shrink.AddButtonID(ButtonID::Keyboard_Q);
		shrink.AddButtonID(ButtonID::Gamepad_Shoulder_Left1);
		App::GetInput().DefineButton(shrink);

		Button pause = Button(SID("Pause"));
		pause.AddButtonID(ButtonID::Keyboard_Escape);
		pause.AddButtonID(ButtonID::Keyboard_Tab);
		pause.AddButtonID(ButtonID::Keyboard_Keypad_Tab);
		pause.AddButtonID(ButtonID::Gamepad_Start);
		pause.AddButtonID(ButtonID::Gamepad_Select);
		App::GetInput().DefineButton(pause);
	}

	void DefineMaterials(){
		App::GetMaterialCache().AddMaterial(SID("Invalid"), new ColorMaterial(Gadget::Color::Pink(), SID("ColorShader"))); //TODO - The engine should add this on its own

		App::GetMaterialCache().AddMaterial(SID("BrickMaterial"), new DiffuseTextureMaterial(SID("CubeTexture"), SID("DefaultShader")));
		App::GetMaterialCache().AddMaterial(SID("GlassMaterial"), new DiffuseTextureMaterial(SID("GlassTexture"), SID("UnlitShader")));
		App::GetMaterialCache().AddMaterial(SID("HamsterMaterial"), new DiffuseTextureMaterial(SID("HamsterTexture"), SID("DefaultShader")));
		App::GetMaterialCache().AddMaterial(SID("SinkMaterial"), new DiffuseTextureMaterial(SID("StainlessSteelTexture"), SID("DefaultShader")));
		App::GetMaterialCache().AddMaterial(SID("CerealBoxMaterial"), new DiffuseTextureMaterial(SID("CerealBoxTexture"), SID("DefaultShader"))); //TODO - Make default shader the, uh, default
	}
};