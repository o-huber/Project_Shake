#ifndef WIDGET_H
#define WIDGET_H

#include "food.h"
#include "snake.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLCDNumber>
#include <QTimer>
#include <QVector>
#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

  QGridLayout *layout;
  QGraphicsScene *scene;
  QGraphicsView *viewer;
  QTimer *animation;
  snakeHead *head;
  QVector<snakeBody *> tail;
  snakeBody *tmp;
  food *Food;
  QGraphicsTextItem *gameOverText;
  QGraphicsTextItem *scoreText;
  int score;

public:
  Widget(QWidget *parent = nullptr);
  ~Widget() override;
  void addTail();
  void newGame();

signals:
  void dead();
  void goBack();

public slots:
  void moveNow();
  void newFood();
  void gameOver();

  // QWidget interface
protected:
  void keyPressEvent(QKeyEvent *event) override;
};

#endif // WIDGET_H
