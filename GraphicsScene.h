#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>

const double DEG_TO_RAD = M_PI / 180.0;
const double RAD_TO_DEG = 180.0 / M_PI;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = nullptr);

signals:
    void cursorChanged(const QPointF &pos, const QPointF &scenePos, const QPointF &screenPos);

public slots:

protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private slots:

private:

    QGraphicsPolygonItem *m_pArrowA = nullptr;
    QGraphicsPolygonItem *m_pArrowB = nullptr;
};



#endif // GRAPHICSSCENE_H
