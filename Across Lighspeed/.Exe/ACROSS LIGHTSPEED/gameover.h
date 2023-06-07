#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameOver;
}
QT_END_NAMESPACE

class GameOver : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameOver(int X ,QWidget *parent = nullptr);
    ~GameOver();

private:
    Ui::GameOver *ui;
    QGraphicsScene *Scene;

};

#endif // GAMEOVER_H
