#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Compiler/Compiler/RunTime.h"
#include "Compiler/Compiler/Compiler.h"
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_nextStep_clicked();

    void on_allStep_clicked();

private:
    Ui::MainWindow *ui;
    void updateData();
    Loonguage::RunTimeConfig config;
    std::shared_ptr<Loonguage::RunTime> runtime;
    std::shared_ptr<Loonguage::Compiler> compiler;
    QStandardItemModel* model;
};
#endif // MAINWINDOW_H
