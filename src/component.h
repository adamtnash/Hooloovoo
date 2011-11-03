#ifndef COMPONENT_H
#define COMPONENT_H

#include <QtXml>
#include <QSharedPointer>
#include <QKeyEvent>
class GameObject;

class Component : public QObject
{
    Q_OBJECT
public:
    Component(GameObject* parentObject);

    bool deserialize(const QDomElement & specs);
    QDomElement serialize(QDomDocument *doc);

    GameObject* getParentObject() {return m_parentObject;}

    virtual QSet<QString> getEditProperties() {return QSet<QString>();}
    virtual void prepareForSerialization() {}
    virtual void keyPressEvent(QKeyEvent* ke) {}
    virtual void keyReleaseEvent(QKeyEvent* ke) {}
    virtual bool allowMultipleComponents() {return true;}

protected:
    GameObject* m_parentObject;
};

#endif // COMPONENT_H
