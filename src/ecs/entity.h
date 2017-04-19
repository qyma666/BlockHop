#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <vector>
#include <string>
#include "component.h"

class Entity {
public:
    /*
     * A entity holds references to components which in turn allow
     * it to be subscribed to specific systems. It is basically the
     * connecting block which we worry about when creating a game.
     * An entity does not need to exported as there are no derived
     * types, instead they are created through the ECSManager.
     */
    Entity();
    ~Entity();

    /*
     * Functions for adding/removing components from entities.
     * Should be used to enable/disable functionality of an
     * entity.
     */
    void addComponent(Component* comp);
    void removeComponent(std::string compName);

    /*
     * Helpers for retrieving components attached to an entity
     */
    std::vector<std::string> getComponents();
    template <typename T>
    T* getComponent(std::string compName) {
        std::vector<Component*>::iterator it = std::find_if(subbedComponents.begin(), subbedComponents.end(), [&compName](Component*& o) {
            return (o->getName() == compName);
        });

        if (it != subbedComponents.end())
            return static_cast<T*>(*it);
        return nullptr;
    }
private:
    void subscribeToSystems();
    std::vector<Component*> subbedComponents;
};

#endif // ENTITY_H_INCLUDED