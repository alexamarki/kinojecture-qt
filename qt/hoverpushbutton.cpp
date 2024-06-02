#include "hoverpushbutton.h"

HoverPushButton::HoverPushButton(QWidget *parent)
    : QPushButton(parent) {}

void HoverPushButton::enterEvent(QEnterEvent *event) {
    emit hovered();
    QPushButton::enterEvent(event);
}

void HoverPushButton::leaveEvent(QEvent *event) {
    emit unhovered();
    QPushButton::leaveEvent(event);
}