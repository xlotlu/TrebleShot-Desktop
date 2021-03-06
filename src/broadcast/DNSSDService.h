//
// Created by veli on 3/6/19.
//

#ifndef TREBLESHOT_BONJOURSERVICE_H
#define TREBLESHOT_BONJOURSERVICE_H

#include <KDNSSD/DNSSD/PublicService>
#include <KDNSSD/DNSSD/ServiceBrowser>
#include <src/util/NetworkDeviceLoader.h>

class DNSSDService : public QObject {
Q_OBJECT

public:
    explicit DNSSDService(QObject* parent = nullptr);

    ~DNSSDService() override;

    void start();

public slots:
    
    void serviceFound(KDNSSD::RemoteService::Ptr service);

protected:
    KDNSSD::PublicService *m_serviceBroadcast;
    KDNSSD::ServiceBrowser *m_serviceBrowser;
};


#endif //TREBLESHOT_BONJOURSERVICE_H
