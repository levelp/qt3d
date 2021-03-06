/****************************************************************************
**
** Copyright (C) 2016 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QT3DINPUT_INPUT_INPUTCHORD_H
#define QT3DINPUT_INPUT_INPUTCHORD_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <Qt3DCore/qbackendnode.h>
#include <Qt3DCore/qnodeid.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {

namespace Input {

class Q_AUTOTEST_EXPORT InputChord : public Qt3DCore::QBackendNode
{
public:
    InputChord();
    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;
    void cleanup();

    inline QVector<Qt3DCore::QNodeId> inputs() const { return m_inputs; }
    inline int tolerance() const { return m_tolerance; }
    inline qint64 startTime() const { return m_startTime; }
    void setStartTime(qint64 time);
    inline bool isEnabled() const { return m_enabled; }
    void reset();
    bool actionTriggered(Qt3DCore::QNodeId input);
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e) Q_DECL_OVERRIDE;
private:
    QVector<Qt3DCore::QNodeId> m_inputs;
    QVector<Qt3DCore::QNodeId> m_inputsToTrigger;
    int m_tolerance;
    qint64 m_startTime;
    bool m_enabled;
};

} // namespace Input

} // namespace Qt3DInput

QT_END_NAMESPACE

#endif // QT3DINPUT_INPUT_INPUTCHORD_H
