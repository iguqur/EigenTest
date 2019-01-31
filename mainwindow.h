#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GraphicsScene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCursorChanged(const QPointF &pos, const QPointF &scenePos, const QPointF &screenPos);

private:
    Ui::MainWindow *ui;

    GraphicsScene *m_pGraphicsScene = nullptr;
};

#endif // MAINWINDOW_H
