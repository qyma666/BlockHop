//
// Created by Jono on 28/06/2018.
//

#include "ClickedTrigger.h"
#include "../ecs/ecsManager.h"
#include "../systems/MouseButtonSystem.h"
#include "../components/TransformComponent.h"
#include "../components/TimeoutComponent.h"
#include <GLFW/glfw3.h>

TRIGGER_EXPORT(ClickedTrigger, "clickedTrigger");

std::map<Entity*, HitData> ClickedTrigger::hitEntities;
int ClickedTrigger::indicatorAccumulator = 0;

ClickedTrigger::ClickedTrigger(){
	// Register all functions that handle actions
//	addAction("box2", EXACT, static_cast<RunTrigFunc>(&ClickedTrigger::runBox2));
	addAction("phys", INEXACT, static_cast<RunTrigFunc>(&ClickedTrigger::doForce));
}
ClickedTrigger::~ClickedTrigger(){}

void ClickedTrigger::setValues(json inValues) {
	force = inValues["force"];
}

void ClickedTrigger::runSystemFunction(SystemBase* sys) {
	auto physicsSystem = static_cast<PhysicsSystem*>(sys);

	hitEntities.clear();

	auto mouseButtonSystem = ECSManager::get().findSystem<MouseButtonSystem>();
	int b = 0;
	if(mouseButtonSystem->isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		b = 1;
	}
	else if(mouseButtonSystem->isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		b = -1;
	}
	if(b != 0)
	{
		Entity* cameraEntity = ECSManager::get().findEntity("Camera");
		auto cameraTransform = cameraEntity->getComponent<TransformComponent>();
		glm::vec3 startGlm = cameraTransform->getPosition();
		glm::vec3 directionGlm = cameraTransform->getForward();
		glm::vec3 endGlm = startGlm + directionGlm*50.0f;

		btVector3 directionBt(directionGlm.x, directionGlm.y, directionGlm.z);
		btVector3 startBt(startGlm.x, startGlm.y, startGlm.z);
		btVector3 endBt(endGlm.x, endGlm.y, endGlm.z);
		btCollisionWorld::ClosestRayResultCallback closestResult(startBt, endBt);

		physicsSystem->dynamicsWorld->rayTest(startBt, endBt, closestResult);

		if(closestResult.hasHit())
		{
			auto rigidBody = (btRigidBody *) btRigidBody::upcast(closestResult.m_collisionObject);
			auto ent = (Entity*) rigidBody->getUserPointer();

			btVector3 worldHit = closestResult.m_hitPointWorld;
			btVector3 localHit = worldHit - rigidBody->getCenterOfMassTransform().getOrigin();

			HitData hd;
			hd.direction = directionBt * b;
			hd.localPoint = localHit;
			hitEntities[ent] = hd;

			// Get Entity "PickPos"
			// Set position worldHit
			std::string indicatorName = "RaycastIndicator";
			indicatorName += std::to_string(indicatorAccumulator);
			auto indicator = ECSManager::get().findEntity(indicatorName);
			if(indicator)
			{
				auto indicatorTransform = indicator->getComponent<TransformComponent>();
				indicatorTransform->setPosition(glm::vec3(worldHit.x(),worldHit.y(),worldHit.z()));
			}
			else
			{
				std::vector<std::string> comps = {
					"transformComponent",
					"animatedModelComponent"
				};
				std::vector<std::string> trigs = {};

				json tj = {
					{"position",{worldHit.x(),worldHit.y(),worldHit.z()}},
					{"rotation",{1, 0, 0, 0}},
					{"scale",{0.1, 0.1, 0.1}}
				};
				json aj = {{"filename","./assets/models/Sphere/sphere.fbx"}};
				std::vector<json> compData = {tj,aj};

				std::vector<json> trigData = {};

				ECSManager::get().createEntity(indicatorName, comps, compData, trigs, trigData);
			}
		}
	}
}

bool ClickedTrigger::entityCheck(SystemBase* sys, Entity* ent) {
	return hitEntities.find(ent) != hitEntities.end();
}

void ClickedTrigger::doForce(SystemBase* sys, Entity* ent) {
	auto physicsSystem = static_cast<PhysicsSystem*>(sys);

	HitData h = hitEntities[ent];

	auto rigidBody = physicsSystem->findRigidBody(ent);
	rigidBody->activate();
	rigidBody->applyForce(h.direction * force, h.localPoint);
}