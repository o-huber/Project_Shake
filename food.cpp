#include "food.h"
#include "snake.h"

food::food(qreal x, qreal y) : QGraphicsEllipseItem(0, 0, 20, 20) {
  setBrush(QBrush(QColor(Qt::red)));
  setPos(x, y);
}

int food::type() const { return Type; }

void food::advance(int phase) {
  if (!phase) {
    if (data(0).toBool())
      delete this;
  }
}
