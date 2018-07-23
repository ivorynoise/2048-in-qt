#ifndef QGAMEOVERWINDOW_H
#define QGAMEOVERWINDOW_H

#include <QWidget>

#include "qresetbutton.h"

class QGameOverWindow : public QWidget
{
    Q_OBJECT
public:
    explicit QGameOverWindow(QWidget *parent = 0);
    QResetButton* getResetButton() const;

signals:

public slots:

private:
    QResetButton *reset;

};

#endif // QGAMEOVERWINDOW_H
