#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QMainWindow>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QKeyEvent>
#include <QTimer>
#include <cmath>
#include <QGraphicsScene>

const int screen_size_x = 612;
const int screen_size_y = 612;

const int screen_half_x = screen_size_x / 2;
const int screen_half_y = screen_size_y / 2;

QT_BEGIN_NAMESPACE
namespace Ui { class background; }
QT_END_NAMESPACE

class background : public QMainWindow
{
    Q_OBJECT

public:
    background(QWidget *parent = nullptr);
    ~background();

protected:
    void actualizar();

public slots:
    void animar();

private:
    Ui::background *ui;

    QGraphicsScene *Scene; QTimer *m_time;

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    bool moverIx1;
    bool moverDx1;
    bool moverUy1;
    bool moverDy1;

    int MAP_WIDTH = 1; int BACK_WIDTH = 1;
    int MAP_HEIGHT = 1; int BACK_HEIGHT = 1;

    int world_scale = 40;
    bool tiled_flag = false;

    float camera_x_pos = 2000;
    float camera_z_pos = 2000;
    float camera_angle = 0;
    int camera_movement_speed = 20;
    float camera_rotation_speed = 0.075;

    QImage *m_mapImage = new QImage(QImage(MAP_WIDTH, MAP_HEIGHT, QImage::Format_RGB16));
    QImage *m_backImage = new QImage(QImage(BACK_WIDTH, BACK_HEIGHT, QImage::Format_RGB16));
};
#endif // BACKGROUND_H
