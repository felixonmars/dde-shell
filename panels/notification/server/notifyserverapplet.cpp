// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "notifyserverapplet.h"
#include "notificationmanager.h"
#include "dbusadaptor.h"
#include "pluginfactory.h"

namespace notification {

Q_LOGGING_CATEGORY(notificationLog, "dde.shell.notification")

NotifyServerApplet::NotifyServerApplet(QObject *parent)
        : DApplet(parent)
{

}

bool NotifyServerApplet::load()
{
    return DApplet::load();
}

bool NotifyServerApplet::init()
{
    DApplet::init();

    m_manager = new NotificationManager(this);
    if (!m_manager->registerDbusService()) {
        qWarning(notificationLog) << QString("Can't register Notifications to the D-Bus object.");
        return false;
    }

    new DbusAdaptor(m_manager);
    new DDENotificationDbusAdaptor(m_manager);

    connect(m_manager, &NotificationManager::notificationStateChanged, this, &NotifyServerApplet::notificationStateChanged);
    return true;
}

void NotifyServerApplet::actionInvoked(qint64 id, uint bubbleId, const QString &actionKey)
{
    m_manager->actionInvoked(id, bubbleId, actionKey);
}

void NotifyServerApplet::notificationClosed(qint64 id, uint bubbleId, uint reason)
{
    m_manager->notificationClosed(id, bubbleId, reason);
}

void NotifyServerApplet::notificationReplaced(qint64 id)
{
    m_manager->notificationReplaced(id);
}

QVariant NotifyServerApplet::appValue(const QString &appId, int configItem)
{
    return m_manager->GetAppInfo(appId, configItem);
}

D_APPLET_CLASS(NotifyServerApplet)

}

#include "notifyserverapplet.moc"
