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
    void moveMouse();
    void keyPressEvent(QKeyEvent* event);
    ~Server();
private:
    int DataEvent[3] = { 0 };
    QPoint mousePos;
    Socket sk;
    QTimer* mouseUpdateTimer;
    Ui::ActiveServerClass ui;
};
