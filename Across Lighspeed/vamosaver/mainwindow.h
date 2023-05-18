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
#include <limits>

const int screen_size_x = 800;
const int screen_size_y = 600;

const int screen_half_x = screen_size_x / 2;
const int screen_half_y = screen_size_y / 2;


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

    int MAP_WIDTH = 500;
    int MAP_HEIGHT = 400;

    int world_scale = 30;
    bool tiled_flag = false;

    float camera_x_pos = 0;
    float camera_z_pos = 0;
    float camera_angle = 0;
    int camera_movement_speed = 10;
    float camera_rotation_speed = 0.1;

    QGraphicsScene *Scene;

    Ui::MainWindow *ui;
    QTimer *m_time;
    QImage *m_mapImage = new QImage(QImage(MAP_WIDTH, MAP_HEIGHT, QImage::Format_RGB32));
};
#endif // MAINWINDOW_H
