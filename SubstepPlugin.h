#pragma once
#pragma comment( lib, "pluginsdk.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"

class SubStepPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
	int defaultMaxPhysicsSubsteps = 0;
	bool hasSetMaxPhysicsSubsteps = false;

	void setMaxPhysicsSubsteps();
	void resetMaxPhysicsSubsteps();

	void GameCreated(std::string eventName);
	void GameDestroyed(std::string eventName);

public:
	virtual void onLoad();
	virtual void onUnload();
};

