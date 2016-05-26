#include "protectableasyncclient.h"
#include "message.h"

#include <QDebug>

using namespace linquitto;

ProtectableAsyncClient::ProtectableAsyncClient(): AsyncClient(), m_handle(nullptr)
{
   int ret = MQTTAsync_create(&m_handle,
                              "tcp://localhost:1883",
                              "ProtectableAsyncTest",
                              MQTTCLIENT_PERSISTENCE_NONE,
                              nullptr);
   if(ret != MQTTASYNC_SUCCESS) {
       throw "ProtectableAsyncClient creation failed!";
   }
}

ProtectableAsyncClient::~ProtectableAsyncClient()
{
    MQTTAsync_destroy(&m_handle);
    qDebug() << "ProtectableAsyncClient dtor.";
}

bool ProtectableAsyncClient::isConnected() const
{
    if(m_handle != nullptr) {
        return MQTTAsync_isConnected(m_handle) == 1;
    } else {
        return false;
    }
}

QString ProtectableAsyncClient::getClientId() const
{
    throw "Not yet implemented!";
}

void ProtectableAsyncClient::setCallback(EventCallback &callback)
{
    throw "Not yet implemented!";
}

void ProtectableAsyncClient::connect(const ConnectOptions &connOpt)
{
    MQTTAsync_connect(m_handle, connOpt.getRawOptions());
}

void ProtectableAsyncClient::disconnect(const DisconnectOptions &disconnOpt)
{
    MQTTAsync_disconnect(m_handle, disconnOpt.getRawOptions());
}

void ProtectableAsyncClient::publish(const QString &topic, const Message &message, ResponseOptions &responseOpt)
{
    std::string destTopic = topic.toStdString();
    MQTTAsync_sendMessage(m_handle,
                          destTopic.c_str(),
                          message.getRawMessage(),
                          responseOpt.getRawOptions());
}

void ProtectableAsyncClient::subscribe(const QString &topic, int qos, ResponseOptions &responseOpt)
{
    throw "Not yet implemented!";
}

void ProtectableAsyncClient::unsubscribe(const QString &topic, ResponseOptions &responseOpt)
{
    throw "Not yet implemented!";
}

