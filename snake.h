#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsEllipseItem>
#include <QList>
#include <QPainter>
#include <QWidget>

#define SNAKE_SIZE 20

class snakeHead : public QObject, public QGraphicsRectItem {
  Q_OBJECT

  int xspeed, yspeed;
  bool pressed;
  bool started;
  bool flags[6];

public:
  snakeHead();

protected:
  void keyPressEvent(QKeyEvent *event) override;

  // QGraphicsItem interface
public:
  void advance(int phase) override;

signals:
  void moved();
  void adv();
  void eated();
  void over();

public slots:
  void Move();
};

class snakeBody : public QObject, public QGraphicsEllipseItem {
  Q_OBJECT
  QGraphicsItem *previous;
  int Type;
  bool flags[4];

public:
  snakeBody(QGraphicsEllipseItem *head);
  snakeBody(QGraphicsRectItem *prev);
  void MoveNow();

  // QGraphicsItem interface
public:
  int type() const override;
};

#endif // SNAKE_H
