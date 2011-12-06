#include "commandcomponent.h"

CommandComponent::CommandComponent(GameObject *parentObject) :
    Component(parentObject)
{
    this->setObjectName("Command Component");

    m_command = GameCore::ChangeLevel;
    m_parameter = "";
}

CommandComponent::~CommandComponent()
{

}

QSet<QString> CommandComponent::getEditProperties()
{
    QSet<QString> properties;
    properties << "tag" << "command" << "parameter";
    return properties;
}

void CommandComponent::effectSendCommand()
{
    GameCore::getInstance().issueCommand(m_command, m_parameter);
}