#include "background.h"
#include "ui_background.h"

background::background(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::background)
{
    ui->setupUi(this);

    juego = new Juego;
    juego->setSceneRect(0,0,ui->graphicsView->width()-2,ui->graphicsView->height()-2);
    ui->graphicsView->setScene(juego);

    Scene = new QGraphicsScene(0,0,screen_size_x, screen_size_y);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, false);

    ui->centralwidget->layout()->setContentsMargins(0,0,0,0);

    ui->graphicsView->setScene(Scene);

    m_mapImage->load(":/backgrounds/F-ZeroMap02BigBlue.jpg");
    MAP_WIDTH = m_mapImage->width();
    MAP_HEIGHT = m_mapImage->height();

    m_backImage->load(":/backgrounds/R.png");
    *m_backImage = m_backImage->scaled(screen_size_x, screen_half_y);
    BACK_WIDTH = m_backImage->width();
    BACK_HEIGHT = m_backImage->height();

    setFixedSize(screen_size_x, screen_size_y);

    moverIx1=false;
    moverDx1=false;
    moverUy1=false;
    moverDy1=false;

    m_time=new QTimer();
    connect(m_time,SIGNAL(timeout()),this,SLOT(animar()));
    m_time->start(0.025);

}

background::~background()
{
    delete m_mapImage;
    delete m_backImage;
    delete ui;
}

void background::actualizar()
{
    QImage *Default = new QImage(screen_size_x, screen_size_y, (QImage::Format_RGB16));

    //QPainter painter(this);

    // Calculate the angle

    //painter.setRenderHint(QPainter::Antialiasing, false);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    //painter.setCompositionMode(QPainter::CompositionMode_Source);

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
            _Y = y + 300;
            _Z = y - screen_half_y;

            if (_Z == 0.0) _Z = 1.0;

            _S = sinf(camera_angle);
            _C = cosf(camera_angle);

            rx = (_X * _C) + (_Y * _S);
            ry = (_X * -_S) + (_Y * _C);

            px = rx / _Z;
            py = ry / _Z;

            px = px * world_scale;
            py = py * world_scale;

            px = px + camera_x_pos;
            py = py +camera_z_pos;

            flag = false;

            if (tiled_flag == false)
            {
                if (px < 0.0) flag = true;
                if (px > MAP_WIDTH - 1) flag = true;
                if (py < 0.0) flag = true;
                if (py > MAP_HEIGHT - 1) flag = true;
            }
            else
            {
                px = fmod(abs(px), MAP_WIDTH-1);
                py = fmod(abs(py), MAP_HEIGHT-1);
            }

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
            px = fmod(abs(x), BACK_WIDTH);
            py = fmod(screen_size_y-y , BACK_HEIGHT);
            *color = m_backImage->pixelColor(px, py);
            Default->setPixelColor(x, screen_size_y - y, *color);
        }
    }
    ui->graphicsView->setBackgroundBrush(QBrush(*Default));
}
void background::animar()
{
    float _S = sinf(camera_angle);
    float _C = cosf(camera_angle);


    if (moverUy1 && moverDx1)
    {
        camera_angle = camera_angle + camera_rotation_speed;
        camera_z_pos = camera_z_pos + _C*camera_movement_speed;
        camera_x_pos = camera_x_pos + _S*camera_movement_speed;
        this->actualizar();

    }
    else if(moverUy1 && moverIx1)
    {
        camera_angle = camera_angle - camera_rotation_speed;
        camera_z_pos = camera_z_pos + _C*camera_movement_speed;
        camera_x_pos = camera_x_pos + _S*camera_movement_speed;
        this->actualizar();
    }
    else if(moverIx1)
    {
        camera_angle = camera_angle - camera_rotation_speed;
        this->actualizar();
    }
    else if (moverDx1)
    {
        camera_angle = camera_angle + camera_rotation_speed;
        this->actualizar();
    }
    else if(moverUy1)
    {
        camera_z_pos = camera_z_pos + _C*camera_movement_speed;
        camera_x_pos = camera_x_pos + _S*camera_movement_speed;
        this->actualizar();
    }
    else if(moverDy1)
    {
        camera_z_pos = camera_z_pos - _C*camera_movement_speed;
        camera_x_pos = camera_x_pos - _S*camera_movement_speed;
        this->actualizar();
    }

}
void background::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        moverIx1=true;
    }
    else if(ev->key()==Qt::Key_D)
    {
        moverDx1=true;
    }
    else if(ev->key()==Qt::Key_W)
    {
        moverUy1=true;
    }
    else if(ev->key()==Qt::Key_S)
    {
        moverDy1=true;
    }

}

void background::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        moverIx1=false;
    }
    else if(ev->key()==Qt::Key_D)
    {
        moverDx1=false;
    }
    else if(ev->key()==Qt::Key_W)
    {
        moverUy1=false;
    }
    else if(ev->key()==Qt::Key_S)
    {
        moverDy1=false;
    }

}

