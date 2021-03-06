//
// Created by veli on 2/16/19.
//

#ifndef TREBLESHOT_TRANSFERWINDOW_H
#define TREBLESHOT_TRANSFERWINDOW_H

#include <QDialog>
#include <ui_ShowTransferDialog.h>
#include <src/database/object/TransferGroup.h>
#include <src/model/TransferObjectModel.h>
#include <src/model/FlawedTransferModel.h>

namespace Ui {
    class ShowTransferDialog;
}

class ShowTransferDialog : public QDialog {
Q_OBJECT

public:
    explicit ShowTransferDialog(QWidget *parentWindow, groupid groupId);

    ~ShowTransferDialog() override;

public slots:

    void addDevices();

    void assigneeChanged(int index);

    void changeSavePath();

    void globalTaskStarted(groupid groupId, const QString &deviceId, int type);

    void globalTaskFinished(groupid groupId, const QString &deviceId, int type);

    void removeTransfer();

    void checkGroupIntegrity(const SqlSelection &change, ChangeType type);

    void retryReceiving();

    void saveDirectory();

    void sendToDevices(groupid groupId, QList<NetworkDevice> devices);

    void showFiles();

    void startTransfer();

    void taskToggle();

    void transferItemActivated(const QModelIndex& modelIndex);

    void transferBitChange(groupid groupId, const QString &deviceId, int type, qint64 bit, qint64 fileSessionSize);

    void transferFileChange(groupid groupId, const QString &deviceId, int type);

    void updateAssignees();

    void updateButtons();

    void updateStats();

protected:
    Ui::ShowTransferDialog *m_ui;
    TransferObjectModel *m_objectModel;
    FlawedTransferModel *m_errorsModel;
    TransferGroup m_group;
    TransferGroupInfo m_groupInfo;
    QList<AssigneeInfo> m_assigneeList;
    qint64 m_fileSessionSize = 0;
};


#endif //TREBLESHOT_TRANSFERWINDOW_H
