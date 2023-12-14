#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ActiveServer.h"
#include "socket.h"
#include <QTimer>
#include <QCursor>
#include <QMouseEvent>

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    void EventRecieve();
    void keyPressEvent(QKeyEvent* event);
    ~Server();
private:
    int DataEvent[3] = { 0 };
    // DataEvent[0] = 0->8, 0->6 mouse, 7->8 kb
    // DataEvent[1] = x neu la chuot, Virtual Key neu la phim
    // DataEvent[2] = y neu la chuot, 0 neu la phim
    QPoint mousePos;
    Socket sk;
    QTimer* mouseUpdateTimer;
    Ui::ActiveServerClass ui;
};
