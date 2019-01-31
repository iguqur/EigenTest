#include "GraphicsScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <Eigen/Dense>
#include "GraphicsCoordinateAxisItem.h"

using namespace std;

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    addItem(new GraphicsCoordinateAxisItem);

    const qreal Width = 100;
    QPolygonF arrowPolygon;
    arrowPolygon << QPointF(Width / 2, 0) << QPointF(0, -Width / 2)  // 中心点为0度，从箭头定点顺时针开始画的
                 << QPointF(0, -Width / 5) << QPointF(-Width / 2, -Width / 5)
                 << QPointF(-Width / 2, Width / 5) << QPointF(0, Width / 5)
                 << QPointF(0, Width / 2);

    m_pArrowA = new QGraphicsPolygonItem(arrowPolygon);
    m_pArrowA->setBrush(QColor(Qt::red));
    addItem(m_pArrowA);
    m_pArrowB = new QGraphicsPolygonItem(arrowPolygon);
    m_pArrowB->setBrush(QColor(Qt::blue));
    addItem(m_pArrowB);

    const Eigen::Vector3d arrayAPose(0, 0, -90 * DEG_TO_RAD);
    const Eigen::Vector3d arrayBOffset(100, 100, -90 * DEG_TO_RAD);
    Eigen::Vector3d arrayBPose(0, 0, 0);

    // 已知a在世界坐标系中的位置、b相对于a的位置，求b在世界坐标系的位置
    Eigen::Affine2d tf(Eigen::Translation2d(arrayAPose.head<2>()) * Eigen::Rotation2Dd(arrayAPose[2]));
    arrayBPose.head<2>() = tf * arrayBOffset.head<2>();
    arrayBPose[2] = arrayAPose[2] + arrayBOffset[2];

    m_pArrowA->setPos(arrayAPose[0], arrayAPose[1]);
    m_pArrowA->setRotation(arrayAPose[2] * RAD_TO_DEG);
    m_pArrowB->setPos(arrayBPose[0], arrayBPose[1]);
    m_pArrowB->setRotation(arrayBPose[2] * RAD_TO_DEG);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    emit cursorChanged(mouseEvent->pos(), mouseEvent->scenePos(), mouseEvent->screenPos());

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
