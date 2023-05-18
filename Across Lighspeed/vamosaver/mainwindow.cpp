#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_mapImage->load(":/Imagenes/SuperMarioKartMapMushroomCup1.jpg");

    MAP_WIDTH = m_mapImage->width();
    MAP_HEIGHT = m_mapImage->height();
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    moverIx1=false;
    moverDx1=false;
    moverUy1=false;
    moverDy1=false;

    ui->graphicsView->show();

    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    Scene = new QGraphicsScene(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);

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
    QImage Default(SCREEN_WIDTH, SCREEN_HEIGHT, (QImage::Format_RGB32));
    // Calculate the angle based on time
    float cosValue = cosf(angle);
    float sinValue = sinf(angle);

    for (int y = 0; y < SCREEN_HEIGHT/2; ++y)
        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
        {
            // Calculate the position in the map
            float mapX = SCREEN_WIDTH / 2 - x;
            float mapY = FOCAL_LEN + y;
            float mapZ = SCREEN_HEIGHT / 2 - y + 0.01;

            mapX = (mapX * cosValue - mapY * sinValue);
            mapY = (mapX * sinValue + mapY * cosValue);


            int mapPixelX = static_cast<int>((mapX / mapZ) * SCALE) ;
            int mapPixelY = static_cast<int>((mapY / mapZ + movement) * SCALE) ;

            // Wrap the map coordinates
            mapPixelX = (mapPixelX + MAP_WIDTH) % MAP_WIDTH;
            mapPixelY = (mapPixelY + MAP_HEIGHT) % MAP_HEIGHT;

            if (mapPixelX < 0) mapPixelX *= -1;
            if (mapPixelY < 0) mapPixelY *= -1;

            // Get the color from the map and set it in the painter
            QColor color = m_mapImage->pixelColor(mapPixelX, mapPixelY);
            Default.setPixelColor(x,SCREEN_HEIGHT-y - 1, color);

        }
    }
    ui->graphicsView->setBackgroundBrush(QBrush(Default));;
}

void MainWindow::animar()
{
    if(moverIx1)
    {
    angle -= 0.01;
    this->actualizar();
    }
    if(moverDx1)
    {
    angle += 0.01;
    this->actualizar();
    }
    if(moverUy1)
    {
    movement += 0.5;
    this->actualizar();
    }
    if(moverDy1)
    {
    movement -= 0.5;
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


