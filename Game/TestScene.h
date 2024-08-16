#pragma once

class TestScene : public Gadget::Scene{
public:
	TestScene() : Scene(SID("TestScene")){}

protected:
	virtual void SetToDefaultState() override{
		Scene::SetToDefaultState();
	}
};