/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "scenemanager_p.h"

QT_BEGIN_NAMESPACE

namespace Qt3D {

namespace Render {

SceneManager::SceneManager() : QResourcesManager<RenderScene,
                                                 QUuid,
                                                 8,
                                                 Qt3D::ArrayAllocatingPolicy,
                                                 Qt3D::ObjectLevelLockingPolicy>()
{
}

void SceneManager::addSceneData(const QString &source, const QUuid &sceneUuid)
{
    m_pendingJobs.append(LoadSceneJobPtr(new LoadSceneJob(source, sceneUuid)));
}

QVector<LoadSceneJobPtr> SceneManager::pendingSceneLoaderJobs()
{
    QVector<LoadSceneJobPtr> copy = m_pendingJobs;
    m_pendingJobs.clear();
    return copy;
}

void SceneManager::addLoadedSceneTree(const QString &source, QEntity *tree)
{
    SceneManager::WriteLocker lock(this);
    m_loadedSceneTrees.insert(source, tree);
}

QEntity *SceneManager::sceneTreeFromSource(const QString &source)
{
    SceneManager::ReadLocker lock(this);
    return m_loadedSceneTrees.value(source);
}

} // Render

} // Qt3D

QT_END_NAMESPACE
