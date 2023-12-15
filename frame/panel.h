// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "dsglobal.h"
#include "containment.h"

#include <QQuickWindow>

DS_BEGIN_NAMESPACE

/**
 * @brief 插件集
 */
class DPanelPrivate;
class DS_SHARE DPanel : public DContainment
{
    Q_OBJECT
    D_DECLARE_PRIVATE(DPanel)
public:
    explicit DPanel(QObject *parent = nullptr);
    virtual ~DPanel() override;

    QQuickWindow *window() const;

    // 加载插件
    virtual bool load(const DAppletData &data = DAppletData()) override;
    // 初始化
    virtual bool init() override;

    static DPanel *qmlAttachedProperties(QObject *object);
};

DS_END_NAMESPACE

QML_DECLARE_TYPEINFO(DS_NAMESPACE::DPanel, QML_HAS_ATTACHED_PROPERTIES)