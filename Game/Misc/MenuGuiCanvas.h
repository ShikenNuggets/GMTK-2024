#pragma once

#include <Gadget.h>

using namespace Gadget;

static constexpr const char* gCredits1 = "Created and Developed by Carter Rennick";

static constexpr const char* gCredits2 = "Made with GadgetEngine";
static constexpr const char* gCredits3 = "additional Technologies:"; //TODO - Upper case A doesn't render???
static constexpr const char* gCredits4 = "asset Importer (assimp)";
static constexpr const char* gCredits5 = "Bullet Physics SDK (bullet3)";
static constexpr const char* gCredits6 = "FMOD by Firelight Technologies";
static constexpr const char* gCredits7 = "FreeType";
static constexpr const char* gCredits8 = "JSON for Modern CPP by Niels Lohmann"; //TODO - + doesn't render???
static constexpr const char* gCredits9 = "Simple DirectMedia Layer 2 (SDL2) by Sam Lantinga";

static constexpr const char* gCredits10 = "Music";
static constexpr const char* gCredits11 = "Grand Dark Waltz Trio Vivace by Kevin MacLeod (incompetech.com)"; //TODO - Quotes don't render
static constexpr const char* gCredits12 = "Sergios Magic Dustbin by Kevin MacLeod (incompetech.com)"; //TODO - ' doesn't render

static constexpr const char* gCredits13 = "additional art:";
static constexpr const char* gCredits14 = "QubiCone";
static constexpr const char* gCredits15 = "petergoldsmith";
static constexpr const char* gCredits16 = "printable_models";

class MenuGuiCanvas : public GuiCanvas{
public:
	MenuGuiCanvas() : GuiCanvas(SID("MenuCanvas")){
		//-------------------------------------------------//
		//--------------------- Main ----------------------//
		//-------------------------------------------------//

		GuiTextElement* titleText = new GuiTextElement(SID("TitleText"), "Weird Hamster Ball Game", SID("ArialFont"), Vector2(0.0f, 0.8f), Vector2(1.5f, 0.5f), GuiAnchor::Center);
		GuiButton* startButton = new GuiButton(SID("StartButton"), "Start", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, 0.25f), Vector2(0.2f, 0.1f), GuiAnchor::Center);
		GuiButton* creditsButton = new GuiButton(SID("CreditsButton"), "Credits", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, 0.0f), Vector2(0.2f, 0.1f), GuiAnchor::Center);
		GuiButton* quitButton = new GuiButton(SID("QuitButton"), "Quit", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, -0.25f), Vector2(0.2f, 0.1f), GuiAnchor::Center);

		startButton->SetOnClickCallback([](ButtonID id_, const Vector2& v){ App::GetSceneManager().RequestSceneLoad(SID("KitchenScene")); });
		creditsButton->SetOnClickCallback([&](ButtonID id_, const Vector2& v_){ SwitchToCredits(); });
		quitButton->SetOnClickCallback([](ButtonID id_, const Vector2& v){ App::CloseGame(); });

		mainElements.Add(titleText);
		mainElements.Add(startButton);
		mainElements.Add(creditsButton);
		mainElements.Add(quitButton);

		for(auto* e : mainElements){
			AddElement(e);
		}

		//-------------------------------------------------//
		//-------------------- Credits --------------------//
		//-------------------------------------------------//

		GuiTextElement* creditsTitle = new GuiTextElement(SID("CreditsTitleText"), "Credits", SID("ArialFont"), Vector2(0.0f, 0.8f), Vector2(0.8f, 0.8f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText1 = new GuiTextElement(SID("CreditsText"), gCredits1, SID("ArialFont"), Vector2(0.0f, 0.5f), Vector2(1.5f, 1.5f), GuiAnchor::Center, Color::White(), false);
		
		GuiTextElement* creditsText2 = new GuiTextElement(SID("CreditsText"), gCredits2, SID("ArialFont"), Vector2(-1.0f, 0.3f), Vector2(1.0f, 1.0f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText3 = new GuiTextElement(SID("CreditsText"), gCredits3, SID("ArialFont"), Vector2(-1.0f, 0.15f), Vector2(0.8f, 0.8f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText4 = new GuiTextElement(SID("CreditsText"), gCredits4, SID("ArialFont"), Vector2(-1.0f, 0.05f), Vector2(0.8f, 0.8f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText5 = new GuiTextElement(SID("CreditsText"), gCredits5, SID("ArialFont"), Vector2(-1.0f, -0.05f), Vector2(0.8f, 0.8f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText6 = new GuiTextElement(SID("CreditsText"), gCredits6, SID("ArialFont"), Vector2(-1.0f, -0.15f), Vector2(0.8f, 0.8f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText7 = new GuiTextElement(SID("CreditsText"), gCredits7, SID("ArialFont"), Vector2(-1.0f, -0.25f), Vector2(0.4f, 0.4f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText8 = new GuiTextElement(SID("CreditsText"), gCredits8, SID("ArialFont"), Vector2(-1.0f, -0.35f), Vector2(0.8f, 0.8f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText9 = new GuiTextElement(SID("CreditsText"), gCredits9, SID("ArialFont"), Vector2(-1.0f, -0.45f), Vector2(0.8f, 0.8f), GuiAnchor::Center, Color::White(), false);
		
		GuiTextElement* creditsText10 = new GuiTextElement(SID("CreditsText"), gCredits10, SID("ArialFont"), Vector2(1.0f, 0.3f), Vector2(0.4f, 0.4f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText11 = new GuiTextElement(SID("CreditsText"), gCredits11, SID("ArialFont"), Vector2(1.0f, 0.15f), Vector2(1.25f, 1.25f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText12 = new GuiTextElement(SID("CreditsText"), gCredits12, SID("ArialFont"), Vector2(1.0f, 0.05f), Vector2(1.25f, 1.25f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText13 = new GuiTextElement(SID("CreditsText"), gCredits13, SID("ArialFont"), Vector2(1.0f, -0.25f), Vector2(0.8f, 0.8f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText14 = new GuiTextElement(SID("CreditsText"), gCredits14, SID("ArialFont"), Vector2(1.0f, -0.35f), Vector2(0.4f, 0.4f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText15 = new GuiTextElement(SID("CreditsText"), gCredits15, SID("ArialFont"), Vector2(1.0f, -0.45f), Vector2(0.5f, 0.5f), GuiAnchor::Center, Color::White(), false);
		GuiTextElement* creditsText16 = new GuiTextElement(SID("CreditsText"), gCredits16, SID("ArialFont"), Vector2(1.0f, -0.55f), Vector2(0.5f, 0.5f), GuiAnchor::Center, Color::White(), false);
		
		GuiButton* creditsBackButton = new GuiButton(SID("CreditsBackButton"), "Back", SID("ArialFont"), SID("ButtonTexture"), Vector2(0.0f, -0.5f), Vector2(0.2f, 0.1f), GuiAnchor::Center, false);

		creditsBackButton->SetOnClickCallback([&](ButtonID id_, const Vector2& v_){ SwitchToMain(); });

		creditsElements.Add(creditsTitle);
		creditsElements.Add(creditsText1);
		creditsElements.Add(creditsText2);
		creditsElements.Add(creditsText3);
		creditsElements.Add(creditsText4);
		creditsElements.Add(creditsText5);
		creditsElements.Add(creditsText6);
		creditsElements.Add(creditsText7);
		creditsElements.Add(creditsText8);
		creditsElements.Add(creditsText9);
		creditsElements.Add(creditsText10);
		creditsElements.Add(creditsText11);
		creditsElements.Add(creditsText12);
		creditsElements.Add(creditsText13);
		creditsElements.Add(creditsText14);
		creditsElements.Add(creditsText15);
		creditsElements.Add(creditsText16);
		creditsElements.Add(creditsBackButton);

		for(auto* e : creditsElements){
			AddElement(e);
		}

		SwitchToMain();
	}

private:
	void SwitchToMain(){
		for(auto* e : creditsElements){
			e->SetIsActive(false);
		}

		for(auto* e : mainElements){
			e->SetIsActive(true);
		}
	}

	void SwitchToCredits(){
		for(auto* e : mainElements){
			e->SetIsActive(false);
		}

		for(auto* e : creditsElements){
			e->SetIsActive(true);
		}
	}

	Array<GuiElement*> mainElements;
	Array<GuiElement*> creditsElements;
};