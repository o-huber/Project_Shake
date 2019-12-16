#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
  qsrand(static_cast<uint>(time(nullptr)));
  layout = new QGridLayout(this);
  scene = new QGraphicsScene(0, 0, 500, 500, this);
  viewer = new QGraphicsView(scene, this);
  viewer->setBackgroundBrush(QBrush(Qt::black));
  setStyleSheet("background-color:black;");
  layout->addWidget(viewer, 0, 0);
  setFixedSize(620, 640);
  newGame();
}

Widget::~Widget() {}

void Widget::addTail() {
  tail.push_back(new snakeBody(tail.last()));
  scene->addItem(tail.last());
}

void Widget::newGame() {
  head = new snakeHead;
  head->setPos(250, 250);
  QGraphicsRectItem *rect = new QGraphicsRectItem(-1, -1, 502, 502);
  rect->setBrush(QBrush(QColor(Qt::black)));
  QPen *pen = new QPen(Qt::white);
  rect->setPen(*pen);
  scene->addItem(rect);
  scene->setBackgroundBrush(QBrush(Qt::black));
  animation = new QTimer(this);
  tail.push_back(new snakeBody(head));
  scene->addItem(tail.last());

  scene->addItem(head);
  head->setPos(240, 240);
  tail.last()->setPos(220, 240);
  tail.push_back(new snakeBody(tail.last()));
  scene->addItem(tail.last());
  tail.push_back(new snakeBody(tail.last()));
  scene->addItem(tail.last());
  tail.push_back(new snakeBody(tail.last()));
  scene->addItem(tail.last());
  tail.push_back(new snakeBody(tail.last()));
  scene->addItem(tail.last());
  animation->start(65);

  connect(animation, SIGNAL(timeout()), head, SLOT(Move()));
  connect(head, SIGNAL(adv()), scene, SLOT(advance()));
  connect(head, SIGNAL(moved()), this, SLOT(moveNow()));
  connect(head, SIGNAL(eated()), this, SLOT(newFood()));
  connect(head, SIGNAL(over()), this, SLOT(gameOver()));
  scene->addItem(new food(qrand() % 25 * 20, qrand() % 25 * 20));
  scene->setStickyFocus(true);
  head->setFocus();

  score = 0;
  scoreText = new QGraphicsTextItem(QString::number(score));
  scene->addItem(scoreText);
  scoreText->setPos(0, 510);
  scoreText->setHtml("        <!DOCTYPE html>"
                     "        <title>Text Example</title>"
                     "        <style>"
                     "div.container {"
                     "}"
                     "div.container p {"
                     "font-family: Arial;"
                     "font-size: 30px;"
                     "font-style: normal;"
                     "font-weight: bold;"
                     "    color: white;"
                     "    }"
                     "  </style>"

                     "    <div class=\"container\">"
                     "    <p>Score: " +
                     QString::number(score) +
                     "</p>"
                     " </div>");
}

void Widget::moveNow() {
  for (int i = tail.size() - 1; i >= 0; --i) {
    tail[i]->MoveNow();
  }
}

void Widget::newFood() {
  score += 10;
  scoreText->setHtml("        <!DOCTYPE html>"
                     "        <title>Text Example</title>"
                     "        <style>"
                     "div.container {"
                     "}"
                     "div.container p {"
                     "font-family: Arial;"
                     "font-size: 30px;"
                     "font-style: normal;"
                     "font-weight: bold;"
                     "    color: white;"
                     "    }"
                     "  </style>"

                     "    <div class=\"container\">"
                     "    <p>Score: " +
                     QString::number(score) +
                     "</p>"
                     " </div>");
  addTail();
  auto f = [&](int &x, int &y) {
    for (auto &i : tail)
      if (i->pos().toPoint().x() == x && i->pos().toPoint().y() == y) {
        return false;
      }
    return true;
  };
  int x, y;
  do {
    x = qrand() % 25 * 20;
    y = qrand() % 25 * 20;
  } while ((head->pos().toPoint().x() == x && head->pos().toPoint().y() == y) ||
           !f(x, y));
  scene->addItem(new food(x, y));
}

void Widget::gameOver() {
  gameOverText = new QGraphicsTextItem;

  gameOverText->setHtml("        <!DOCTYPE html>"
                        "        <title>Text Example</title>"
                        "        <style>"
                        "div.container {"
                        "}"
                        "div.container p {"
                        "font-family: Arial;"
                        "font-size: 50px;"
                        "font-style: normal;"
                        "font-weight: bold;"
                        " text-decoration: none;"
                        "    text-transform: none;"
                        "    color: white;"
                        "    }"
                        "  </style>"

                        "    <div class=\"container\">"
                        "    <p>Game Over</p>"
                        " </div>");
  gameOverText->setPos(120, scene->height() / 2 - 30);
  scene->addItem(gameOverText);
}

void Widget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape)
    emit goBack();
}
