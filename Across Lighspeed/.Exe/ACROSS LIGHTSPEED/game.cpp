#include "game.h"
#include "selector.h"
#include "selectormundos.h"
#include "ui_game.h"
#include "vector"
#include "QDebug"

using namespace std;

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

    checkpointsCompletados = 0;

    MundoSeleccionado = Mundo;
    GenerarCheckpoints();

    if (Mundo == 1)
    {
        escenario = new background(":/escenarios/BigBlueNoBackG.png", 1000, 1000);
        escenario->setCamera_x_pos(2411);
        escenario->setCamera_z_pos(3253);
    }
    else if(Mundo == 2)
    {
        escenario = new background(":/escenarios/MuteCity1NoBackG.png", 4637, 1517);
        escenario->setCamera_x_pos(2377);
        escenario->setCamera_z_pos(2987);

    }
    else if(Mundo == 3)
    {
        escenario = new background(":/escenarios/MuteCity2NoBackG.png", 2278, 3074);
        escenario->setCamera_x_pos(2374);
        escenario->setCamera_z_pos(3210);
    }
    else if(Mundo == 4)
    {
        escenario = new background(":/escenarios/PortTown1NoBackGc.png", 3366, 2093);
        escenario->setCamera_x_pos(3397);
        escenario->setCamera_z_pos(2201);
    }
    else if(Mundo == 5)
    {
        escenario = new background(":/escenarios/FireFieldNoBackG.jpg", 1901, 3094);
        escenario->setCamera_x_pos(1898);
        escenario->setCamera_z_pos(3211);
    }

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

    temporizador->start(1000);

    m_timer=new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(main_movement()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(VerificarCheckpoints()));
    m_timer->start(10);


}

Game::~Game()
{
    delete ui;
    delete m_timer;
    delete Scene;
    delete character;
    delete final;
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
        Speed -= 0.3;
    }
    else if (Speed != 0)
    {
        if (Speed > 0)
        {
            Speed -= 0.2;
        }
        else
        {
            Speed += 0.1;
        }
    }
    escenario->setCamera_movement_speed(Speed);
    escenario->Fowards(BarraDeVida);
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
    BarraDeVida->setValue(100);
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

void Game::VerificarCheckpoints()
{
    // Suponiendo que tienes una variable "jugador" que representa al jugador
    int jugadorX = escenario->getCamera_x_pos();
    int jugadorY = escenario->getCamera_z_pos();

    // Obtén el siguiente checkpoint que el jugador debe pasar
    Checkpoint siguienteCheckpoint = checkpoints.front();

    // Verifica si el jugador ha pasado por el checkpoint actual
    if (jugadorX >= siguienteCheckpoint.x &&
        jugadorX <= siguienteCheckpoint.x + siguienteCheckpoint.width &&
        jugadorY >= siguienteCheckpoint.y &&
        jugadorY <= siguienteCheckpoint.y + siguienteCheckpoint.height) {
        checkpoints.erase(checkpoints.begin()); // Elimina el checkpoint actual de la lista
        checkpointsCompletados++;

    }
}

void Game::GenerarCheckpoints()
{
    if(MundoSeleccionado == 1)
    {
        // Checkpoint en la mitad del mapa
        Checkpoint checkpointMitad;
        checkpointMitad.x = 3905;
        checkpointMitad.y =  1052;
        checkpointMitad.width = 1300;
        checkpointMitad.height =  1300;
        checkpointMitad.id = 1;
        checkpoints.push_back(checkpointMitad);

        // Checkpoint en la línea de meta
        Checkpoint checkpointMeta;
        checkpointMeta.x = 2360;
        checkpointMeta.y = 3000;
        checkpointMeta.width = 2300;
        checkpointMeta.height = 2300;
        checkpointMeta.id = 2;
        checkpoints.push_back(checkpointMeta);
    }
    else if(MundoSeleccionado == 2)
    {
        // Checkpoint en la mitad del mapa
        Checkpoint checkpointMitad;
        checkpointMitad.x = 4542;
        checkpointMitad.y =  291;
        checkpointMitad.width = 1300;
        checkpointMitad.height =  1300;
        checkpointMitad.id = 1;
        checkpoints.push_back(checkpointMitad);

        // Checkpoint en la línea de meta
        Checkpoint checkpointMeta;
        checkpointMeta.x = 2357;
        checkpointMeta.y = 2797;
        checkpointMeta.width = 1300;
        checkpointMeta.height = 1300;
        checkpointMeta.id = 2;
        checkpoints.push_back(checkpointMeta);
    }
    else if(MundoSeleccionado == 3)
    {
        // Checkpoint en la mitad del mapa
        Checkpoint checkpointMitad;
        checkpointMitad.x = 5354;
        checkpointMitad.y =  472;
        checkpointMitad.width = 1300;
        checkpointMitad.height =  1300;
        checkpointMitad.id = 1;
        checkpoints.push_back(checkpointMitad);

        // Checkpoint en la línea de meta
        Checkpoint checkpointMeta;
        checkpointMeta.x = 2331;
        checkpointMeta.y = 3048;
        checkpointMeta.width = 1300;
        checkpointMeta.height = 1300;
        checkpointMeta.id = 2;
        checkpoints.push_back(checkpointMeta);
    }
    else if(MundoSeleccionado == 4)
    {
        // Checkpoint en la mitad del mapa
        Checkpoint checkpointMitad;
        checkpointMitad.x = 5997;
        checkpointMitad.y =  1023;
        checkpointMitad.width = 1300;
        checkpointMitad.height =  1300;
        checkpointMitad.id = 1;
        checkpoints.push_back(checkpointMitad);

        // Checkpoint en la línea de meta
        Checkpoint checkpointMeta;
        checkpointMeta.x = 3350;
        checkpointMeta.y = 2066;
        checkpointMeta.width = 1300;
        checkpointMeta.height = 1300;
        checkpointMeta.id = 2;
        checkpoints.push_back(checkpointMeta);
    }
    else if(MundoSeleccionado == 5)
    {
        // Checkpoint en la mitad del mapa
        Checkpoint checkpointMitad;
        checkpointMitad.x = 4867;
        checkpointMitad.y =  1054;
        checkpointMitad.width = 1300;
        checkpointMitad.height =  1300;
        checkpointMitad.id = 1;
        checkpoints.push_back(checkpointMitad);

        // Checkpoint en la línea de meta
        Checkpoint checkpointMeta;
        checkpointMeta.x = 1889;
        checkpointMeta.y = 3058;
        checkpointMeta.width = 1300;
        checkpointMeta.height = 1300;
        checkpointMeta.id = 2;
        checkpoints.push_back(checkpointMeta);
    }
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
        temporizador->stop();
        final = new GameOver(1);
        final->show();

    }
    else if(BarraDeVida->value() <= 0){
        close();
        temporizador->stop();
        final = new GameOver(0);
        final->show();
    }
    else if(checkpointsCompletados == 2)
    {
        close();
        temporizador->stop();
        final = new GameOver(2);
        final->show();
    }
}

void Game::AgregarTimer()
{
    ui->lcdNumber->setDigitCount(5);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdNumber->setStyleSheet("color: white");
    ActualizarTemporizador();
}

