#include "game.h"
#include "selector.h"
#include "selectormundos.h"
#include "ui_game.h"



Game::Game(int Nave, int Mundo, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{

    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, false);
    ui->graphicsView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    if (Mundo == 1)
    {
        escenario = new background(":/escenarios/BigBlueNoBackG.png", 1000, 1000);
        escenario->setCamera_x_pos(2411);
        escenario->setCamera_z_pos(3253);
        Musica = new QSound(":/Music/Guilty-Gear-Mays-Theme-Blue-Water-Blue-Sky.wav");
    }
    else if(Mundo == 2)
    {
        escenario = new background(":/escenarios/MuteCity1NoBackG.png", 4637, 1517);
        escenario->setCamera_x_pos(2377);
        escenario->setCamera_z_pos(2987);
        Musica = new QSound(":/MusicaSabrosa/F-Zero-X-OST-Dream-Chaser.wav");

    }
    else if(Mundo == 3)
    {
        escenario = new background(":/escenarios/MuteCity2NoBackG.png", 2278, 3074);
        escenario->setCamera_x_pos(2374);
        escenario->setCamera_z_pos(3210);
        Musica = new QSound(":/MusicaSabrosa/F-Zero-X-OST-Drivin-Through-on-Max.wav");
    }
    else if(Mundo == 4)
    {
        escenario = new background(":/escenarios/PortTown1NoBackG.png", 3366, 2093);
        escenario->setCamera_x_pos(3373);
        escenario->setCamera_z_pos(2201);
        Musica = new QSound(":/Musica45/Pizza Tower OST - Unexpectancy, Part 3 (Final Boss).wav");
    }
    else if(Mundo == 5)
    {
        escenario = new background(":/escenarios/FireFieldNoBackG.jpg", 1901, 3094);
        escenario->setCamera_x_pos(1898);
        escenario->setCamera_z_pos(3211);
        Musica = new QSound(":/Musica45/The Original -Faust’s Theme-.wav");
    }

    Musica->play();
    Musica->setLoops(QSound::Infinite);

    Scene = new QGraphicsScene(0, 0, escenario->getScreen_size_x() - 2, escenario->getScreen_size_y() - 2);
    setFixedSize(escenario->getScreen_size_x() + 20, escenario->getScreen_size_y() + 20);

    ui->graphicsView->setScene(Scene);
    ui->graphicsView->setBackgroundBrush(escenario->actualizar());

    Speed = 0;

    AgregarNave(Nave);

    BarraDeVida = new QProgressBar();
    BarraDeVida->setValue(70);

    AgregarVida();
    AgregarTimer();

    temporizador = new QTimer(this);
    temporizador->setInterval(100);
    connect(temporizador, SIGNAL(timeout()), this, SLOT(ActualizarTemporizador()));

    temporizador->start(100);

    m_timer=new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(main_movement()));
    m_timer->start(10);
}

Game::~Game()
{
    delete ui;
    delete m_timer;
    delete Scene;
    delete character;
}

void Game::main_movement()
{

    if(movement_Left)
    {
        escenario->turn_Left();
    }
    if (movement_Right)
    {
        escenario->turn_Right();
    }
    if(movement_Up && Speed < 20)
    {
        Speed += 0.2;
        character->moveUp();
    }
    else if(movement_Down && Speed > -10)
    {
        Speed -= 0.2;
    }
    else if (Speed != 0)
    {
        if (Speed > 0)
        {
            Speed -= 0.1;
        }
        else
        {
            Speed += 0.1;
        }
    }
    escenario->setCamera_movement_speed(Speed);
    escenario->Fowards();
    ui->graphicsView->setBackgroundBrush(escenario->actualizar());

}

void Game::RecibirElementos()
{

}

void Game::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        movement_Left=true;
    }
    else if(ev->key()==Qt::Key_D)
    {
        movement_Right=true;
    }
    else if(ev->key()==Qt::Key_W)
    {
        movement_Up=true;
    }
    else if(ev->key()==Qt::Key_S)
    {
        movement_Down=true;
    }
    if(ev->key()==Qt::Key_Shift)
    {
        character->turbo();
        Speed *= 2;
        escenario->setCamera_movement_speed(0.135);
        BarraDeVida->setValue(BarraDeVida->value()-10);
    }
}

void Game::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_A)
    {
        movement_Left=false;
    }
    else if(ev->key()==Qt::Key_D)
    {
        movement_Right=false;
    }
    else if(ev->key()==Qt::Key_W)
    {
        movement_Up=false;
    }
    else if(ev->key()==Qt::Key_S)
    {
        movement_Down=false;
    }
    if(ev->key()==Qt::Key_Shift)
    {
        character->uytieso();
        Speed /= 2;
        escenario->setCamera_movement_speed(0.085);
    }
}

void Game::AgregarNave(int Nave)
{
    const char *N1 = ":/naves/AcelerandoNaveAzul.png";
    const char *N2 = ":/naves/AcelerandoNaveMorada";
    const char *N3 = ":/naves/AcelerandoNaveAmarilla.png";
    const char *N4 = ":/naves/AcelerandoNaveRoja.png";

    if(Nave == 1){
        character = new Sprites(N1, 64, 33);
        Scene->addItem(character);
        character->setPos(336, 450);
        character->changecurrentpixmap(0,0);
        character->set_ampliar(2);
    }
    else if(Nave == 2){
        character = new Sprites(N2, 64, 33);
        Scene->addItem(character);
        character->setPos(336, 450);
        character->changecurrentpixmap(0,0);
        character->set_ampliar(2);
    }
    else if(Nave == 3){
        character = new Sprites(N3, 64, 33);
        Scene->addItem(character);
        character->setPos(336, 450);
        character->changecurrentpixmap(0,0);
        character->set_ampliar(2);
    }
    else if(Nave == 4){
        character = new Sprites(N4, 64, 33);
        Scene->addItem(character);
        character->setPos(336, 450);
        character->changecurrentpixmap(0,0);
        character->set_ampliar(2);
    }
}

void Game::AgregarVida()
{
    BarraDeVida->setMinimum(0);
    BarraDeVida->setMaximum(100);
    BarraDeVida->setTextVisible(false);

    BarraDeVida->setStyleSheet(
        "QProgressBar {"
        "    background-color: black;"
        "    border: 2px solid white;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "}"

        "QProgressBar::chunk {"
        "    background-color: green;"
        "    width: 10px;" // Ajusta el ancho del "chunk" según tus necesidades
        "}"
        );

    ProxyBarraDeVida = new QGraphicsProxyWidget();
    ProxyBarraDeVida->setWidget(BarraDeVida);

    ProxyBarraDeVida->setPos(590,10);
    Scene->addItem(ProxyBarraDeVida);



}

void Game::ActualizarTemporizador()
{
    TiempoRestante--;
    int minutos = TiempoRestante / 60;
    int segundos = TiempoRestante & 60;

    QString tiempoTexto = QString("%1:%2").arg(minutos, 2, 10, QChar('0')).arg(segundos, 2, 10, QChar('0'));
    ui->lcdNumber->setStyleSheet("QLCDNumber { font-family: TimesNewRoman; font-size: 24px; font-weight: bold; }");



    ui->lcdNumber->display(tiempoTexto);

    if(TiempoRestante==0){
        close();

    }
    else if(BarraDeVida->value() == 0){
        close();

    }
}

void Game::AgregarTimer()
{
    ui->lcdNumber->setDigitCount(5);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdNumber->setStyleSheet("color: white");

    ActualizarTemporizador();
}
