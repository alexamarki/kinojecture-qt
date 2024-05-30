#ifndef HOVERPUSHBUTTON_H
#define HOVERPUSHBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QEnterEvent>

class HoverPushButton : public QPushButton {
    Q_OBJECT

public:
    explicit HoverPushButton(QWidget *parent = nullptr);

signals:
    void hovered();
    void unhovered();

protected:
    void enterEvent(QEnterEvent *event) override;

    void leaveEvent(QEvent *event) override;
};

#endif // HOVERPUSHBUTTON_H