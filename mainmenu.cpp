#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QMessageBox>
#include <QtDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenu) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentIndex(0);
  game = new Widget;
  connect(game, SIGNAL(goBack()), this, SLOT(goMainMenu()));
  ui->stackedWidget->insertWidget(1, game);
  setFixedSize(440, 302);
  move(300, 80);
}

MainMenu::~MainMenu() { delete ui; }

void MainMenu::on_pushButton_clicked() {
  setStyleSheet("QMainWindow{background-color: black;}");
  ui->stackedWidget->setCurrentIndex(1);
  setFixedSize(620, 640);
  move(300, 40);
}

void MainMenu::goMainMenu() {
  delete game;
  ui->stackedWidget->setCurrentIndex(0);
  setFixedSize(440, 302);
  game = new Widget;
  connect(game, SIGNAL(goBack()), this, SLOT(goMainMenu()));
  ui->stackedWidget->insertWidget(1, game);
  move(300, 80);
  setStyleSheet(
      "QMainWindow{background-color: gray;} QWidget{background-color: "
      "grey;}QPushButton{background-color: white;color: black;font-size: "
      "28pt;border: 2px solid black;border-radius: "
      "10px;}QPushButton:hover{border: 2px solid red;color: red;}");
}

void MainMenu::on_pushButton_3_clicked() { exit(0); }

void MainMenu::on_pushButton_2_clicked() {
  QMessageBox::information(nullptr, "Information",
                           "Created by Oleh Hubernator, Group K-28");
}
