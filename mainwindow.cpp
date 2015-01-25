//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->buttonCheck, SIGNAL(pressed()), this, SLOT(check()));
  connect(ui->buttonOpen, SIGNAL(pressed()), this, SLOT(open()));

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::open()
{
  QString pathEdit = ui->filePathEdit->text();

  QString path = QFileDialog::getOpenFileName(this, QString("Open File"), pathEdit);

  ui->filePathEdit->setText(path);
}

void MainWindow::check()
{
  QString path = ui->filePathEdit->text();

  QFile file(path);

  QByteArray hash;
  QString hStr , cStr;

  if(ui->radioMD5->isChecked())
    {
      QCryptographicHash crypto(QCryptographicHash::Md5);
      if(file.open(QFile::ReadOnly))
        {
          while(!file.atEnd())
            {
              crypto.addData(file.read(1024));
            }

        }
      file.close();

      hash = crypto.result();
      hStr = QString(hash.toHex());
      cStr = ui->comparisonStringEdit->text();
    }
  else
    if(ui->radioMD4->isChecked())
      {
        QCryptographicHash crypto(QCryptographicHash::Md4);
        if(file.open(QFile::ReadOnly))
          {
            while(!file.atEnd())
              {
                crypto.addData(file.read(1024));
              }

          }
        file.close();

        hash = crypto.result();
        hStr = QString(hash.toHex());
        cStr = ui->comparisonStringEdit->text();
      }
    else
      if(ui->radioSHA256->isChecked())
        {
          QCryptographicHash crypto(QCryptographicHash::Sha256);
          if(file.open(QFile::ReadOnly))
            {
              while(!file.atEnd())
                {
                  crypto.addData(file.read(1024));
                }

            }
          file.close();

          hash = crypto.result();
          hStr = QString(hash.toHex());
          cStr = ui->comparisonStringEdit->text();
        }
      else
        if(ui->radioSHA512->isChecked())
          {
            QCryptographicHash crypto(QCryptographicHash::Sha512);
            if(file.open(QFile::ReadOnly))
              {
                while(!file.atEnd())
                  {
                    crypto.addData(file.read(1024));
                  }

              }
            file.close();

            hash = crypto.result();
            hStr = QString(hash.toHex());
            cStr = ui->comparisonStringEdit->text();
          }

  qDebug() << hStr;
  if(hStr == cStr)
    {
      QMessageBox msgBox;
      msgBox.setText("Success! The file's hash matches the comparison string.");
      msgBox.exec();
    }
  else
    {
      QMessageBox msgBox;
      msgBox.setText("Failure! The file's hash DOES NOT match the comparison string.");
      msgBox.exec();
    }

}

