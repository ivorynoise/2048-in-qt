#include "qresetbutton.h"

// TODO see if is compile if I give *parent = 0 in definition
QResetButton::QResetButton(QWidget *parent) : QPushButton(parent)
{
    setText(" Try Again ");
    setStyleSheet("QResetButton { background-color: rgb(143,122,102);"\
                  "font: bold; color: white; }");
}

void QResetButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
