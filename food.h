#ifndef FOOD_H
#define FOOD_H

#include <QBrush>
#include <QGraphicsEllipseItem>

class food : public QObject, public QGraphicsEllipseItem {
  Q_OBJECT

public:
  enum { Type = UserType + 1984 };
  food(qreal x, qreal y);

signals:
  void dead();

  // QGraphicsItem interface
public:
  int type() const override;

  // QGraphicsItem interface
public:
  void advance(int phase) override;
};

#endif // FOOD_H
