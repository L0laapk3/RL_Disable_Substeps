#include "SubstepPlugin.h"
#include <iostream>

BAKKESMOD_PLUGIN(SubStepPlugin, "Disable Substepping", "0.1", PLUGINTYPE_FREEPLAY)


void SubStepPlugin::setMaxPhysicsSubsteps() {
	if (!gameWrapper->IsInOnlineGame() && gameWrapper->IsInGame()) {
		if (defaultMaxPhysicsSubsteps == 0)
			defaultMaxPhysicsSubsteps = gameWrapper->GetEngine().GetMaxPhysicsSubsteps();
		gameWrapper->GetEngine().SetMaxPhysicsSubsteps(1);
		hasSetMaxPhysicsSubsteps = true;
		cvarManager->log("Disabled substepping");
	} else
		resetMaxPhysicsSubsteps();
}

void SubStepPlugin::resetMaxPhysicsSubsteps() {
	if (hasSetMaxPhysicsSubsteps) {
		gameWrapper->GetEngine().SetMaxPhysicsSubsteps(defaultMaxPhysicsSubsteps);
		hasSetMaxPhysicsSubsteps = false;
		cvarManager->log("Restored substepping");
	}
}

void SubStepPlugin::onLoad() {
	gameWrapper->HookEvent("Function TAGame.GameEvent_TA.OnInit", bind(&SubStepPlugin::GameCreated, this, std::placeholders::_1));
	gameWrapper->HookEvent("Function TAGame.GameEvent_TA.Destroyed", bind(&SubStepPlugin::GameDestroyed, this, std::placeholders::_1));
	setMaxPhysicsSubsteps();
}

void SubStepPlugin::onUnload() {
	resetMaxPhysicsSubsteps();
}


void SubStepPlugin::GameCreated(std::string eventName) {
	setMaxPhysicsSubsteps();
}
void SubStepPlugin::GameDestroyed(std::string eventName) {
	resetMaxPhysicsSubsteps();
}