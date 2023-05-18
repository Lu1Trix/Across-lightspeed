#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_mapImage->load(":/Imagenes/F-ZeroMap01MuteCity1.jpg");

    MAP_WIDTH = m_mapImage->width();
    MAP_HEIGHT = m_mapImage->height();
    setFixedSize(screen_size_x, screen_size_y);

    moverIx1=false;
    moverDx1=false;
    moverUy1=false;
    moverDy1=false;

    ui->graphicsView->show();

    Scene = new QGraphicsScene(0,0,screen_size_x, screen_size_y);

    ui->graphicsView->setScene(Scene);

    m_time=new QTimer();

    connect(m_time,SIGNAL(timeout()),this,SLOT(animar()));

    m_time->start(50);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizar()
{
    float _X;
    float _Y;
    float _Z;
    float _S;
    float _C;
    float rx;
    float ry;
    float px;
    float py;
    bool flag;
    int tx;
    int ty;

    QImage Default(screen_size_x, screen_size_y, (QImage::Format_RGB32));

    for (int y = screen_half_y; y < screen_size_y; ++y)
    {
        for (int x = 0; x < screen_size_x; ++x)
        {
            _X = x - screen_half_x;
            _Y = y + 250;
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
                QColor color = m_mapImage->pixelColor(tx, ty);
                Default.setPixelColor(x, y, color);
            }
            else
            {
                QColor color(0,0,0);
                Default.setPixelColor(x, y, color);
            }
        }
    }


    ui->graphicsView->setBackgroundBrush(QBrush(Default));
}

void MainWindow::animar()
{
    float _S = sinf(camera_angle);
    float _C = cosf(camera_angle);
    float M_X = (0.0 * _C) + (1.0 * _S);
    float M_Z = (0.0 * -_S) + (1.0 * _C);

    M_X = M_X + camera_movement_speed;
    M_Z = M_Z + camera_movement_speed;



    if(moverIx1)
    {
    camera_angle = camera_angle - camera_rotation_speed;

    this->actualizar();
    }
    if(moverDx1)
    {
    camera_angle = camera_angle + camera_rotation_speed;
    this->actualizar();
    }
    if(moverUy1)
    {
    camera_z_pos = camera_z_pos + cosf(camera_angle)*camera_movement_speed;
    camera_x_pos = camera_x_pos + sinf(camera_angle)*camera_movement_speed;
    this->actualizar();
    }
    if(moverDy1)
    {
    camera_z_pos = camera_z_pos - cosf(camera_angle);
    camera_x_pos = camera_x_pos - sinf(camera_angle);
    this->actualizar();
    }
}
void MainWindow::keyPressEvent(QKeyEvent *ev)
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

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
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


