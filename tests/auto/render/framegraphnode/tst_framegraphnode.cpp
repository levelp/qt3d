/****************************************************************************
**
** Copyright (C) 2015 Paul Lemire paul.lemire350@gmail.com
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

#include <QtTest/QTest>
#include <Qt3DCore/private/qbackendnode_p.h>
#include <Qt3DRender/private/framegraphnode_p.h>
#include <Qt3DRender/private/managers_p.h>

class MyFrameGraphNode : public Qt3DRender::Render::FrameGraphNode
{
public:
    void updateFromPeer(Qt3DCore::QNode *) Q_DECL_FINAL {}

protected:
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &) Q_DECL_FINAL {}
};

class tst_FrameGraphNode : public QObject
{
    Q_OBJECT
public:
    tst_FrameGraphNode(QObject *parent = Q_NULLPTR)
        : QObject(parent)
    {}

    ~tst_FrameGraphNode()
    {}

    void setIdInternal(Qt3DRender::Render::FrameGraphNode *node, const Qt3DCore::QNodeId &id)
    {
        Qt3DCore::QBackendNodePrivate::get(node)->m_peerUuid = id;
    }

private Q_SLOTS:

    void checkInitialState()
    {
        // GIVEN
        MyFrameGraphNode n;

        // THEN
        QCOMPARE(n.nodeType(), Qt3DRender::Render::FrameGraphNode::InvalidNodeType);
        QVERIFY(n.isEnabled());
        QVERIFY(n.peerUuid().isNull());
        QVERIFY(n.manager() == Q_NULLPTR);
        QVERIFY(n.parentId().isNull());
        QVERIFY(n.childrenIds().empty());
    }

    void checkPropertyChanges()
    {
        // GIVEN
        QScopedPointer<Qt3DRender::Render::FrameGraphNode> n(new MyFrameGraphNode());

        // WHEN
        n->setEnabled(false);
        // THEN
        QCOMPARE(n->isEnabled(), false);

        // WHEN
        QScopedPointer<Qt3DRender::Render::FrameGraphManager> manager(new Qt3DRender::Render::FrameGraphManager());
        n->setFrameGraphManager(manager.data());
        // THEN
        QCOMPARE(n->manager(), manager.data());

        // WHEN
        const Qt3DCore::QNodeId parentId = Qt3DCore::QNodeId::createId();
        // THEN
        QVERIFY(!parentId.isNull());

        // WHEN
        n->setParentId(parentId);
        // THEN
        QCOMPARE(n->parentId(), parentId);

        // WHEN
        const Qt3DCore::QNodeId childId = Qt3DCore::QNodeId::createId();
        QScopedPointer<Qt3DRender::Render::FrameGraphNode> c(new MyFrameGraphNode());
        setIdInternal(c.data(), childId);
        manager->appendNode(c.data());
        n->appendChildId(childId);
        // THEN
        QCOMPARE(n->childrenIds().count(), 1);

        // WHEN
        n->appendChildId(childId);
        // THEN
        QCOMPARE(n->childrenIds().count(), 1);
    }

    void checkParentChange()
    {
        // GIVEN
        QScopedPointer<Qt3DRender::Render::FrameGraphManager> manager(new Qt3DRender::Render::FrameGraphManager());
        const Qt3DCore::QNodeId parentId = Qt3DCore::QNodeId::createId();
        const Qt3DCore::QNodeId childId = Qt3DCore::QNodeId::createId();
        Qt3DRender::Render::FrameGraphNode *parent1 = new MyFrameGraphNode();
        Qt3DRender::Render::FrameGraphNode *child = new MyFrameGraphNode();

        setIdInternal(parent1, parentId);
        setIdInternal(child, childId);

        manager->appendNode(parent1);
        manager->appendNode(child);

        parent1->setFrameGraphManager(manager.data());
        child->setFrameGraphManager(manager.data());

        // THEN
        QVERIFY(parent1->childrenIds().isEmpty());
        QVERIFY(child->parentId().isNull());

        // WHEN
        parent1->appendChildId(childId);
        // THEN
        QCOMPARE(child->parentId(), parentId);
        QCOMPARE(child->parent(), parent1);
        QCOMPARE(parent1->childrenIds().count(), 1);
        QCOMPARE(parent1->childrenIds().first(), childId);
        QCOMPARE(parent1->children().count(), parent1->childrenIds().count());
        QCOMPARE(parent1->children().first(), child);

        // WHEN
        parent1->appendChildId(childId);
        // THEN
        QCOMPARE(child->parentId(), parentId);
        QCOMPARE(child->parent(), parent1);
        QCOMPARE(parent1->childrenIds().count(), 1);
        QCOMPARE(parent1->childrenIds().first(), childId);
        QCOMPARE(parent1->children().count(), parent1->childrenIds().count());
        QCOMPARE(parent1->children().first(), child);

        // WHEN
        parent1->removeChildId(childId);
        // THEN
        QVERIFY(child->parentId().isNull());
        QVERIFY(child->parent() == Q_NULLPTR);
        QCOMPARE(parent1->childrenIds().count(), 0);
        QCOMPARE(parent1->children().count(), parent1->childrenIds().count());
    }
};

QTEST_APPLESS_MAIN(tst_FrameGraphNode)

#include "tst_framegraphnode.moc"
