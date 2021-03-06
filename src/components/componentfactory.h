#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <QString>
#include <QSharedPointer>
#include <QtXml>

#include "component.h"

class ComponentFactory
{
public:
    ComponentFactory();

    Component* createComponent(GameObject* parentObject, QString name);
    Component* createComponent(GameObject* parentObject, const QDomElement & specs);

    static QStringList availableComponents();
    static QString componentInfo(QString name);
};

#endif // COMPONENTFACTORY_H
