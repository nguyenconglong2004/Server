#include "ActiveServer.h"


Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mousePos = QCursor::pos();

    int x = sk.init_and_connect();
    if (x == 1) ui.label_1->setText("False");
    if (x == 2) ui.label_2->setText("False");
    if (x == 3) ui.label_3->setText(QString :: number(sk.data[0]));
    if (x == 4) ui.label_4->setText("False");
    if (x == 5) ui.label_5->setText("False");
    mouseUpdateTimer = new QTimer(this);
    connect(mouseUpdateTimer, &QTimer::timeout, this, &Server::moveMouse);
    mouseUpdateTimer->start(10); // Cập nhật mỗi 10ms
}

Server::~Server()
{
    sk.break_up();
}
void Server::moveMouse() {
    if (sk.recieve() == 1) {
        QPoint currentPos = QCursor::pos();
        for (int i = 0; i < 3; i++) {
            DataEvent[i] = sk.data[i];
        }
        QCursor::setPos(DataEvent[1], DataEvent[2]);
        ui.movePos->setText("Mouse Move Pos: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));
        int type = DataEvent[0];
        if (type == 0) {
            //ui.Double_click->setText("Type = X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));
        }
        else {
            if (type == 1) {
                ui.Press->setText("Mouse Press L: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));
                mouse_event(MOUSEEVENTF_LEFTDOWN, currentPos.x(), currentPos.y(), 0, 0);
                //mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                //SendInput(1, &mouseInput, sizeof(INPUT));

            }
            else if (type == 2) {
                ui.Press->setText("Mouse Press R: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));
                mouse_event(MOUSEEVENTF_RIGHTDOWN, currentPos.x(), currentPos.y(), 0, 0);
                //mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
                //SendInput(1, &mouseInput, sizeof(INPUT));
            }
            else if (type == 3) {
                ui.Release->setText("Mouse Release L: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));
                mouse_event(MOUSEEVENTF_LEFTUP, currentPos.x(), currentPos.y(), 0, 0);
                //mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                //SendInput(1, &mouseInput, sizeof(INPUT));
            }
            else if (type == 4) {
                ui.Release->setText("Mouse Release R: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));
                mouse_event(MOUSEEVENTF_RIGHTUP, currentPos.x(), currentPos.y(), 0, 0);
                //mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
                //SendInput(1, &mouseInput, sizeof(INPUT));
            }
            else if (type == 5) {
                ui.Double_click->setText("Mouse DOuble Click: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]));
            }
            else if(type == 6) {
                ui.Double_click->setText("NO MOUSE EVENT: X: " + QString::number(DataEvent[1]) + "Y: " + QString::number(DataEvent[2]) + "   " + QString::number(DataEvent[0]));
            }
            else if (type == 7 || type == 8) {
                //INPUT keyInput;
                //keyInput.type = INPUT_KEYBOARD;
                //keyInput.ki.time = 0;
                //keyInput.ki.dwExtraInfo = 0;
                //keyInput.ki.wVk = DataEvent[1];
                //SendInput(0, &keyInput, sizeof(keyInput));
                //keyInput.ki.dwFlags = KEYEVENTF_KEYUP;
                //SendInput(0, &keyInput, sizeof(keyInput));
                keybd_event(DataEvent[1], 0, 0, 0);
                keybd_event(DataEvent[1], 0, KEYEVENTF_KEYUP, 0);
                //INPUT keyInput;
                //keyInput.type = INPUT_KEYBOARD;
                //keyInput.ki.time = 0;
                //keyInput.ki.dwExtraInfo = 0;
                //keyInput.ki.wVk = DataEvent[1];
                //SendInput(0, &keyInput, sizeof(keyInput));
            }
        }
    }
}
void Server::keyPressEvent(QKeyEvent* event) {
    //ui.key_press->setText(QChar(event->key()));
}