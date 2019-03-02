//
// Created by veli on 2/9/19.
//

#ifndef TREBLESHOT_SEAMLESSCLIENT_H
#define TREBLESHOT_SEAMLESSCLIENT_H

#include <QtCore/QThread>
#include <QFile>
#include <src/util/Interrupter.h>
#include <src/database/object/TransferGroup.h>
#include <src/util/TransferUtils.h>

class SeamlessClient : public QThread, public Interrupter {
Q_OBJECT

    groupid m_groupId = 0;
    QString m_deviceId;
    int m_attemptsLeft = 2;

public:
    explicit SeamlessClient(const QString &deviceId, groupid groupId, QObject *parent = nullptr);

signals:

    void taskDone(groupid groupId, QString deviceId);

    void taskFailed(groupid groupId, QString deviceId, Reason reason);

protected:
    void run() override;
};


#endif //TREBLESHOT_SEAMLESSCLIENT_H
