#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"

struct Bouncer {
	PhysBody*	cpbody;
	PhysBody*	flipperpbody;
	b2RevoluteJoint* joint;


	Bouncer() {};

};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	//void MoveLeft();
	//void MoveRight();

public:

	Bouncer	bouncers[4];

};