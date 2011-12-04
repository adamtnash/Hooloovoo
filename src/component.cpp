#include "component.h"
#include "gameobject.h"

Component::Component(GameObject *parentObject) :
    //QObject(parentObject),
    m_parentObject(parentObject)
{
    m_tag = "";
    m_ID = parentObject->getAvailableComponentID();
}

QDomElement Component::serialize(QDomDocument *document)
{
    this->prepareForSerialization();

    QDomElement componentElement = document->createElement("component");

    componentElement.setAttribute("name", this->objectName());
    componentElement.setAttribute("id", m_ID);

    for (int i = 0; i<this->metaObject()->propertyCount(); i++)
    {
        QMetaProperty property = this->metaObject()->property(i);
        QString name = property.name();

        if (property.isValid() && property.type() != QVariant::Invalid && property.userType())
        {
            QVariant value = property.read(this);

            if (property.isEnumType())
            {
                QDomElement prop = document->createElement(name);
                prop.setAttribute("type", value.type());
                QVariant intValue = *reinterpret_cast<const int *>(value.constData());
                prop.setAttribute("value", intValue.toString());
                componentElement.appendChild(prop);
            }
            else if (value.type() == QVariant::StringList)
            {
                QDomElement prop = document->createElement(name);

                QStringList stringList = value.toStringList();
                foreach(QString s, stringList)
                {
                    QDomElement child = document->createElement("listitem");
                    child.setAttribute("value", s);
                    prop.appendChild(child);
                }

                prop.setAttribute("type", value.type());
                prop.setAttribute("count", stringList.count());
                componentElement.appendChild(prop);
            }
            else if (value.type() == QVariant::PointF)
            {
                QDomElement prop = document->createElement(name);
                prop.setAttribute("type", value.type());
                prop.setAttribute("x", value.toPointF().x());
                prop.setAttribute("y", value.toPointF().y());
                componentElement.appendChild(prop);
            }
            else
            {
                QDomElement prop = document->createElement(name);
                prop.setAttribute("type", value.type());
                prop.setAttribute("value", value.toString());
                componentElement.appendChild(prop);
            }
        }
    }
    return componentElement;
}

bool Component::deserialize(const QDomElement &objectElement)
{
    m_ID = objectElement.attribute("id", "-1").toInt();
    if (m_ID == -1)
    {
        m_ID = m_parentObject->getAvailableComponentID();
    }

    for (int i = 0; i<this->metaObject()->propertyCount(); i++)
    {
        QMetaProperty property = this->metaObject()->property(i);
        QString name = property.name();
        QDomElement prop = objectElement.firstChildElement(name);

        if (prop.hasAttribute("type") && prop.hasAttribute("value"))
        {
            QVariant value;
            value.setValue(prop.attribute("value"));

            if (property.isEnumType())
            {
                value.convert(QVariant::Int);
                property.write(this, value);
            }
            else if (value.convert((QVariant::Type)prop.attribute("type").toInt()))
            {
                property.write(this, value);
            }
        }
        else if (prop.hasAttribute("x") && prop.hasAttribute("y"))
        {
            QVariant value;
            QPointF point;
            point.setX(prop.attribute("x", "0").toDouble());
            point.setY(prop.attribute("y", "0").toDouble());
            value.setValue(point);
            property.write(this, value);
        }
        else if (prop.hasAttribute("type") && prop.hasAttribute("count"))
        {
            QVariant value;
            QStringList stringList;

            QDomElement child = prop.firstChildElement("listitem");
            while (!child.isNull())
            {
                stringList << child.attribute("value");
                child = child.nextSiblingElement("listitem");
            }

            value.setValue(stringList);
            property.write(this, value);
        }
    }

    return true;
}

QStringList Component::getCauseList()
{
    QMetaObject metaObject = *this->metaObject();
    QMetaMethod method;
    QStringList causeList;

    for (int i = 0; i<metaObject.methodCount(); i++)
    {
        method = metaObject.method(i);
        QString signature = metaObject.normalizedSignature(method.signature());
        if (method.methodType() == QMetaMethod::Signal && signature.startsWith("cause"))
        {
            causeList << signature;
        }
    }

    return causeList;
}

QStringList Component::getEffectList()
{
    QMetaObject metaObject = *this->metaObject();
    QMetaMethod method;
    QStringList effectList;

    for (int i = 0; i<metaObject.methodCount(); i++)
    {
        method = metaObject.method(i);
        QString signature = metaObject.normalizedSignature(method.signature());
        if (method.methodType() == QMetaMethod::Slot && signature.startsWith("effect"))
        {
            effectList << signature;
        }
    }

    return effectList;
}
