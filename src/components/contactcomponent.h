#ifndef CONTACTCOMPONENT_H
#define CONTACTCOMPONENT_H

#include "component.h"
#include "physicscomponent.h"

class ContactComponent : public Component
{
    Q_OBJECT
    Q_PROPERTY(QString contactTagRequirement READ getTagRequirement WRITE setTagRequirement)

public:
    explicit ContactComponent(GameObject *parentObject);

    QSet<QString> getEditProperties();

    void setTagRequirement(QString tag) {m_tagRequirement = tag;}
    QString getTagRequirement() {return m_tagRequirement;}

private:
    PhysicsComponent* m_physicsComponent;

    QString m_tagRequirement;

    QSet<int> m_newContacts;
    QSet<int> m_removedContacts;
    QSet<int> m_contacts;

signals:
    void causeEnterContact();
    void causeLeaveContact();
    void causeNoContact();

public slots:

    void enterContact(int contactObjectID);
    void leaveContact(int contactObjectID);
    void checkForAddedPhysicsComponent(Component* c);
    void checkForRemovedPhysicsComponent(Component* c);
    void contactCheck();
};

#endif // CONTACTCOMPONENT_H
