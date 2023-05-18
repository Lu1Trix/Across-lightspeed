#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <cmath>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const int FOCAL_LEN = 250;
const int SCALE = 25;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void actualizar();

public slots:
    void animar();

private:

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    bool moverIx1;
    bool moverDx1;
    bool moverUy1;
    bool moverDy1;

    float angle = 0;
    float movement = 0;

    int MAP_WIDTH = 1600;
    int MAP_HEIGHT = 900;

    QGraphicsScene *Scene;

    Ui::MainWindow *ui;
    QTimer *m_time;
    QImage *m_mapImage = new QImage(QImage(MAP_WIDTH, MAP_HEIGHT, QImage::Format_RGB32));
};
#endif // MAINWINDOW_H
