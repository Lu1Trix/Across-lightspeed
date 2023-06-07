
#include "background.h"

background::background(QString map_direcction, int X, int Y)
{
    m_mapImage->load(map_direcction);
    MAP_WIDTH = m_mapImage->width();
    MAP_HEIGHT = m_mapImage->height();
    referencia = m_mapImage->pixelColor(X, Y);

}
background::~background()
{
    delete m_mapImage;
}

int background::getCamera_movement_speed() const
{
    return camera_movement_speed;
}

void background::setCamera_movement_speed(int newCamera_movement_speed)
{
    camera_movement_speed = newCamera_movement_speed;
}

float background::getCamera_x_pos() const
{
    return camera_x_pos;
}

void background::setCamera_x_pos(float newCamera_x_pos)
{
    camera_x_pos = newCamera_x_pos;
}

float background::getCamera_z_pos() const
{
    return camera_z_pos;
}

void background::setCamera_z_pos(float newCamera_z_pos)
{
    camera_z_pos = newCamera_z_pos;
}

float background::getCamera_angle() const
{
    return camera_angle;
}

void background::setCamera_angle(float newCamera_angle)
{
    camera_angle = newCamera_angle;
}

float background::getCamera_rotation_speed() const
{
    return camera_rotation_speed;
}

void background::setCamera_rotation_speed(float newCamera_rotation_speed)
{
    camera_rotation_speed = newCamera_rotation_speed;
}

int background::getScreen_size_x() const
{
    return screen_size_x;
}

int background::getScreen_size_y() const
{
    return screen_size_y;
}

void background::Cargar(QString m_map)
{
    m_mapImage->load(m_map);
    MAP_WIDTH = m_mapImage->width();
    MAP_HEIGHT = m_mapImage->height();
    referencia = m_mapImage->pixelColor(1000, 1000);
}

QColor background::getReferencia() const
{
    return referencia;
}

void background::setReferencia(const QColor &newReferencia)
{
    referencia = newReferencia;
}

QBrush background::actualizar()
{

    float _X; float _Y; float _Z;   //Posicion en el espacio
    float _S; float _C;             //Valores seno y coseno del angulo
    float rx; float ry;             //Posición respecto al angulo
    float px; float py;             //Transformación lineal
    int tx; int ty;                 //Conversión a enteros

    bool flag;

    QColor *color = new QColor;

    for (int y = screen_half_y; y < screen_size_y; ++y)
    {
        for (int x = 0; x < screen_size_x; ++x)
        {
            _X = x - screen_half_x;
            _Y = y + 100;
            _Z = y - screen_half_y;

            if (_Z == 0.0) _Z = 1.0;

            _S = sinf(camera_angle);
            _C = cosf(camera_angle);

            rx = (_X * _C) + (_Y * _S);
            ry = (_X * -_S) + (_Y * _C);

            px = rx / _Z ;
            py = ry / _Z ;

            px = px * world_scale;
            py = py * world_scale;

            px = px + camera_x_pos;
            py = py + camera_z_pos;

            flag = false;

            if (px < 0.0) flag = true;
            if (px > MAP_WIDTH - 1) flag = true;
            if (py < 0.0) flag = true;
            if (py > MAP_HEIGHT - 1) flag = true;

            px = px + 0.5;
            py = py + 0.5;

            tx = static_cast<int>(px);
            ty = static_cast<int>(py);

            if (flag == false)
            {
                ty = MAP_HEIGHT - 1 - ty;
                *color = m_mapImage->pixelColor(tx, ty);
                Default->setPixelColor(x, y, *color);
            }
            else
            {
                *color = qRgb(0,0,0);
                Default->setPixelColor(x, y, *color);
            }
        }
    }
    delete color;
    return QBrush(*Default);

}

void background::Fowards()
{
    int _X = round(camera_x_pos + sinf(camera_angle)*camera_movement_speed + sinf(camera_angle)*65);
    int _Z = round(camera_z_pos + cosf(camera_angle)*camera_movement_speed + cosf(camera_angle)*65);


    int _AUX = camera_x_pos;

    if (m_mapImage->pixelColor(_X, MAP_HEIGHT-camera_z_pos)!= referencia)
    {
        camera_x_pos = camera_x_pos + sinf(camera_angle)*camera_movement_speed;
    }
    if (m_mapImage->pixelColor(_AUX,  MAP_HEIGHT-_Z) != referencia)
    {
        camera_z_pos = camera_z_pos + cosf(camera_angle)*camera_movement_speed;
    }
}

void background::Backwards()
{

    int _X = round(camera_x_pos - sinf(camera_angle)*camera_movement_speed - sinf(camera_angle)*100);
    int _Z = round(camera_z_pos - cosf(camera_angle)*camera_movement_speed - cosf(camera_angle)*100);

    int _AUX = camera_x_pos;

    if (m_mapImage->pixelColor(_X, MAP_HEIGHT-camera_z_pos) != referencia)
    {
        camera_x_pos = camera_x_pos - sinf(camera_angle)*camera_movement_speed;
    }
    if (m_mapImage->pixelColor(_AUX, MAP_HEIGHT-_Z) != referencia)
    {
        camera_z_pos = camera_z_pos - cosf(camera_angle)*camera_movement_speed;
    }

}

void background::turn_Left()
{
    camera_angle = camera_angle - camera_rotation_speed;
}

void background::turn_Right()
{

    camera_angle = camera_angle + camera_rotation_speed;
}
