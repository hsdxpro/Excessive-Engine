#pragma once

#include "InputCore.h"
#include "GameWorld.h"

#include "GraphicsCore.h"
#include "PhysicsCore.h"
#include "SoundCore.h"
#include "NetworkCore.h"
#include "Common.h"

class Script
{
public:
	virtual void Update(float deltaSeconds)	{}
};