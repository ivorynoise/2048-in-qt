#ifndef QRESETBUTTON_H
#define QRESETBUTTON_H

#include <QLabel>
#include <QPushButton>
class QResetButton : public QPushButton
//        public QLabel
{
    Q_OBJECT
public:
    QResetButton(QWidget *parent = nullptr);

signals:
    void clicked();

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // QRESETBUTTON_H
