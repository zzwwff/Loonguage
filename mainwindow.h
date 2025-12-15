#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include "Compiler/Compiler/RunTime.h"
#include "Compiler/Compiler/Compiler.h"
#include <QStandardItemModel>
#include "Compiler/Compiler/BitStream.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Loonguage;
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

    void on_generateTestBenchCodes_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_memorySizeInput_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_writeUSB_clicked();

private:

    enum CodeSource{
        MANUAL,
        AUTO
    } codeSource = AUTO;

    Ui::Loonguage *ui;
    void updateData();
    Loonguage::RunTimeConfig config;
    std::shared_ptr<Loonguage::RunTime> runtime;
    std::shared_ptr<Loonguage::Compiler> compiler;
    std::shared_ptr<Loonguage::BitStream> bitstream;
    int memorySize = 16384;
    QStandardItemModel* codeShowView;
    QStandardItemModel* codeOutView;

    QStandardItemModel* setListView(QListView*, std::vector<Loonguage::Code>);
};
#endif // MAINWINDOW_H
