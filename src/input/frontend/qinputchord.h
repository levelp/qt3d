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

#ifndef QT3DINPUT_QINPUTCHORD_H
#define QT3DINPUT_QINPUTCHORD_H

#include <Qt3DInput/qt3dinput_global.h>
#include <Qt3DCore/qnode.h>
#include <Qt3DInput/qabstractaggregateactioninput.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {

class QAbstractPhysicalDevice;
class QInputChordPrivate;

class QT3DINPUTSHARED_EXPORT QInputChord : public Qt3DInput::QAbstractAggregateActionInput
{
    Q_OBJECT
    Q_PROPERTY(int tolerance READ tolerance WRITE setTolerance NOTIFY toleranceChanged)

public:
    explicit QInputChord(Qt3DCore::QNode *parent = Q_NULLPTR);
    ~QInputChord();

    int tolerance() const;

public Q_SLOTS:
    void setTolerance(int tolerance);

Q_SIGNALS:
    void toleranceChanged(int tolerance);

protected:
    void copy(const Qt3DCore::QNode *ref) Q_DECL_OVERRIDE;

private:
    Q_DECLARE_PRIVATE(QInputChord)
    QT3D_CLONEABLE(QInputChord)
};

} // Qt3DInput

QT_END_NAMESPACE

#endif // QT3DINPUT_QINPUTCHORD_H
