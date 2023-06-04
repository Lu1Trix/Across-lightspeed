#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QGraphicsScene>
#include <cmath>
#include <vector>

class background
{
public:
    background();
    background(QString map_direcction);
    ~background();
    QBrush actualizar();

    void Fowards();
    void Backwards();
    void turn_Left();
    void turn_Right();

    int getCamera_movement_speed() const;
    void setCamera_movement_speed(int newCamera_movement_speed);

    float getCamera_x_pos() const;
    void setCamera_x_pos(float newCamera_x_pos);

    float getCamera_z_pos() const;
    void setCamera_z_pos(float newCamera_z_pos);

    float getCamera_angle() const;
    void setCamera_angle(float newCamera_angle);

    float getCamera_rotation_speed() const;
    void setCamera_rotation_speed(float newCamera_rotation_speed);

    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *newScene);

    int getScreen_size_x() const;

    int getScreen_size_y() const;

    void Cargar(QString m_map);


    QColor getReferencia() const;
    void setReferencia(const QColor &newReferencia);

private:
    int MAP_WIDTH;
    int MAP_HEIGHT;

    int world_scale = 25;

    float camera_movement_speed = 15;
    float camera_rotation_speed = 0.085;

    float camera_x_pos = 3396;
    float camera_z_pos = 331;
    float camera_angle = 0;

    int screen_size_x = 800;
    int screen_size_y = 600;

    int screen_half_x = screen_size_x / 2;
    int screen_half_y = screen_size_y / 2;

    bool tiled_flag = false;

    QColor referencia;

    QImage *m_mapImage = new QImage(QImage(MAP_WIDTH, MAP_HEIGHT, QImage::Format_RGB16));
    QImage *Default = new QImage(screen_size_x, screen_size_y, (QImage::Format_RGB16));

};

#endif // BACKGROUND_H
