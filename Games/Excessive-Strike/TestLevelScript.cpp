#include "TestLevelScript.h"
#include "Core\EngineCore.h"
#include "PlayerScript.h"
#include "ExcessiveStrikeCommon.h"
#include "mymath\mymath.h"

Actor* test;
TestLevelScript::TestLevelScript()
{
	//Actor* ground = World.AddActor("box.DAE", 0);0000000000000000000000000000
	//Actor* ground = World.AddActor("box.DAE", 0);
	//Actor* ground = World.AddActor("Terminal/terminal_blender.dae", 0);
	//ground->SetTextureNormal("Human/images/normal.png");

	//ground->SetScale(mm::vec3(1, 1, 1));
	//ground->SetCollisionGroup(eES_CollisionGroup::GROUND);
	//ground->SetName("ground");

	//Sound.CreateMonoSound("PurgatorysMansion-mono.ogg", 1.f, true)->Start();

	//Add ground to
	//Actor* ground = World.AddActor("Terminal/terminal_blender.dae", 0);
	//ground->RotX(90);
	//ground->SetCollisionGroup(eES_CollisionGroup::GROUND);
	//ground->SetName("ground");

	//Add sky to game
	//Actor* sky = World.AddActor_Mesh("skybox.dae");
	//sky->SetScale(1000);
	//sky->RotX(90);

	//// Set up collision layers..
	Physics.SetLayerCollision(eES_CollisionGroup::PLAYER, eES_CollisionGroup::SHELL,  false);
	Physics.SetLayerCollision(eES_CollisionGroup::GROUND, eES_CollisionGroup::GROUND, false);
	Physics.SetLayerCollision(eES_CollisionGroup::SHELL,  eES_CollisionGroup::SHELL,  false);
	Physics.SetLayerCollision(eES_CollisionGroup::SHELL,  eES_CollisionGroup::PLAYER, false);
	Physics.SetLayerCollision(eES_CollisionGroup::BULLET, eES_CollisionGroup::SHELL,  false);
}

void TestLevelScript::Update(float deltaSeconds)
{
	playerScript.Update(deltaSeconds);

	//test->SetPos(test->GetPos() + mm::vec3(1, 0, 0) * deltaSeconds);
}