#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Compiler/Compiler/RuntimeConfig.h"
#include "QString"
#include <sstream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString qinput = ui->input->toPlainText();
    std::string input = qinput.toStdString();
    input += " @EOF";
    QMessageBox::about(NULL, "About", "Start Running!");
    std::stringstream in, infoOut, synOut, semOut, genOut;
    in << input;
    //if (compiler != nullptr)
    //    delete compiler;
    compiler = new Loonguage::Compiler(in, infoOut, synOut, semOut, genOut);
    compiler->parse();
    QString qinfoOut = QString::fromStdString(infoOut.str());
    QString qsynOut = QString::fromStdString(synOut.str());
    QString qsemOut = QString::fromStdString(semOut.str());
    QString qgenOut = QString::fromStdString(genOut.str());
    ui->infoOut->setPlainText(qinfoOut);
    ui->lexSynOut->setPlainText(qsynOut);
    ui->semOut->setPlainText(qsemOut);
    QStringList list;
    model = new QStandardItemModel();
    for (auto code : compiler->codes)
    {
        std::stringstream stream;
        code.dump(stream);
        std::string str = stream.str();
        if (str.back() == '\n') str.pop_back();
        QStandardItem *item = new QStandardItem(QString::fromStdString(str));
        model->appendRow(item);
    }

    ui->codeOut->setModel(model);
}


void MainWindow::on_pushButton_6_clicked()
{
    config.endian = config.BIG;
    config.width = config.x64;
    config.memorySize = 2048;
    //if (runtime != nullptr)
    //    delete runtime;
    runtime = new Loonguage::RunTime(config, (compiler->codes));
    updateData();
}


void MainWindow::on_nextStep_clicked()
{
    if (runtime != nullptr)
    {
        if (runtime->tick())
            QMessageBox::about(NULL, "About", "Successfully done!");
        updateData();
    }
}

void MainWindow::updateData()
{
    using Reg = Loonguage::Register::Registers;
    ui->rspVal->display(QString::number(runtime->regs[Reg::rsp]));
    ui->rfpVal->display(QString::number(runtime->regs[Reg::rfp]));
    ui->raxVal->display(QString::number(runtime->regs[Reg::rax]));
    ui->rbxVal->display(QString::number(runtime->regs[Reg::rbx]));
    ui->rcxVal->display(QString::number(runtime->regs[Reg::rcx]));
    ui->rdxVal->display(QString::number(runtime->regs[Reg::rdx]));
    ui->insVal->display(QString::number(runtime->regs[Reg::ins]));
    ui->rtmVal->display(QString::number(runtime->regs[Reg::rtm]));
    ui->zSign->display(QString::number(runtime->Z));
    ui->sSign->display(QString::number(runtime->S));
    QModelIndex index = model->index(runtime->currentCode, 0);
    ui->codeOut->setCurrentIndex(index);
}

void MainWindow::on_allStep_clicked()
{

    if (runtime != nullptr)
    {
        while (!runtime->tick());
        QMessageBox::about(NULL, "About", "Successfully done!");
        updateData();
    }
}

