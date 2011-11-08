#include "contactlistener.h"
#include "physicsmanager.h"
#include "physicscomponent.h"
#include <QDebug>

ContactListener::ContactListener(QObject *parent) :
    QObject(parent)
{
}

void ContactListener::BeginContact(b2Contact *contact)
{
    qDebug() << "New Contact";
    PhysicsManager* manager = PhysicsManager::getInstance();

    const b2Manifold* manifold = contact->GetManifold();
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    PhysicsComponent* componentA = manager->getComponent(fixtureA);
    PhysicsComponent* componentB = manager->getComponent(fixtureB);
    float32 x = manifold->localNormal.x;
    float32 y = manifold->localNormal.y;
    ContactType typeA = ContactUnknown;
    ContactType typeB = ContactUnknown;

    if (x<0)
    {
        typeA = typeA | ContactLeft;
        typeB = typeB | ContactRight;
    }
    if (x>0)
    {
        typeA = typeA | ContactRight;
        typeB = typeB | ContactLeft;
    }
    if (y<0)
    {
        typeA = typeA | ContactBottom;
        typeB = typeB | ContactTop;
    }
    if (y>0)
    {
        typeA = typeA | ContactTop;
        typeB = typeB | ContactBottom;
    }

    if (componentA)
        componentA->enterContact(componentB, typeA);
    if (componentB)
        componentB->enterContact(componentA, typeB);
}

void ContactListener::EndContact(b2Contact *contact)
{
    qDebug() << "End of Contact";
    PhysicsManager* manager = PhysicsManager::getInstance();

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    PhysicsComponent* componentA = manager->getComponent(fixtureA);
    PhysicsComponent* componentB = manager->getComponent(fixtureB);

    if (componentA)
        componentA->leaveContact(componentB);
    if (componentB)
        componentB->leaveContact(componentA);
}
