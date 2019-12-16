#ifndef MAINMENU_H
#define MAINMENU_H

#include "widget.h"
#include <QWidget>

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget {
  Q_OBJECT

  Widget *game;

public:
  explicit MainMenu(QWidget *parent = nullptr);
  ~MainMenu();

private slots:
  void on_pushButton_clicked();
  void goMainMenu();

  void on_pushButton_3_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::MainMenu *ui;
};

#endif // MAINMENU_H
