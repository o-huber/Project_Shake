#include "snake.h"
#include "food.h"
#include <QDebug>

snakeHead::snakeHead() : QGraphicsRectItem(0, 0, SNAKE_SIZE, SNAKE_SIZE) {
  setBrush(QBrush(QColor(Qt::blue)));
  // setVisible(false);
  xspeed = 0;
  yspeed = 0;
  setFlags(ItemIsFocusable | ItemIsMovable);
  pressed = false;
}

void snakeHead::keyPressEvent(QKeyEvent *event) {
  if (pressed == false) {
    if (event->key() == Qt::Key_Left && xspeed != 20) {
      xspeed = -20;
      yspeed = 0;
      pressed = true;
      setData(0, true);
    } else if (event->key() == Qt::Key_Right && xspeed != -20) {
      xspeed = 20;
      yspeed = 0;
      pressed = true;
      setData(0, true);
    } else if (event->key() == Qt::Key_Down && yspeed != -20) {
      xspeed = 0;
      yspeed = 20;
      pressed = true;
      setData(0, true);
    } else if (event->key() == Qt::Key_Up && yspeed != 20) {
      xspeed = 0;
      yspeed = -20;
      pressed = true;
      setData(0, true);
    }
  }
  if (event->key() == Qt::Key_Space)
    emit eated();
}

void snakeHead::advance(int phase) {
  if (!phase) {
    foreach (QGraphicsItem *item, collidingItems()) {
      if (item->type() == 777777) {
        if (this->pos() == item->pos()) {
          emit over();
          delete this;
        }
      }
      if (item->type() == food::Type) {
        if (this->pos() == item->pos()) {
          item->setVisible(false);
          item->setData(0, true);
          emit eated();
        }
      }
    }
  } else if (phase) {
    moveBy(xspeed, yspeed);
    if (pos().toPoint().x() == 500)
      setPos(0, pos().y());
    if (pos().toPoint().x() == -20)
      setPos(480, pos().y());
    if (pos().toPoint().y() == 500)
      setPos(pos().x(), 0);
    if (pos().toPoint().y() == -20)
      setPos(pos().x(), 480);
  }
  pressed = false;
}

void snakeHead::Move() {
  emit moved();
  emit adv();
}

snakeBody::snakeBody(QGraphicsRectItem *head)
    : QGraphicsEllipseItem(0, 0, 20, 20) {
  Type = 666666;
  setBrush(QBrush(QColor(0, 204, 102)));
  previous = head;
  head->setData(0, false);
  setData(0, true);
  setPos(previous->pos());
}

snakeBody::snakeBody(QGraphicsEllipseItem *prev)
    : QGraphicsEllipseItem(0, 0, 20, 20) {
  Type = 777777;
  setData(0, true);
  setBrush(QBrush(QColor(0, 204, 102)));
  previous = prev;
  setPos(previous->pos());
}

void snakeBody::MoveNow() { if(previous->data(0).toBool()){setPos(previous->pos().x(), previous->pos().y());} }

int snakeBody::type() const { return Type; }
