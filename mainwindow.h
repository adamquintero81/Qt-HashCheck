//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void open();
  void check();

private:
  Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
