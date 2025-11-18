#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Compiler/Compiler/RuntimeConfig.h"
#include "QString"
#include <sstream>
#include <QMessageBox>
#include <QTime>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (QFile::exists("input.in"))
    {
        QFile file("input.in");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            ui->input->appendPlainText(line);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


//prime loader reference code
/*int isPrime(int n)
{
    int sign; int test;
    sign = test = 2;
    while (test < n){
        if (n / test * test == n)
    {    sign = 0; break; }
    test = test + 1;
    }
    return sign;
}

void main()
{
    int i;
    i = 2;
    outString("There are 25 primes less than 100\n");
    while (i < 101){
    if (isPrime(i)) { outInt(i); outString(" "); }
    i = i + 1;
    }
}
*/

void MainWindow::on_pushButton_clicked()
{
    compiler = nullptr;
    runtime = nullptr;
    QString qinput = ui->input->toPlainText();
    std::string input = qinput.toStdString();
    //save input
    QFile file("input.in");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(QString::fromStdString(input).toUtf8());
    file.close();

    input += "void out(int ch)@ \n";
    input += "int getChar(string str, int pos)@ \n";
    input += "int getSize(string str)@ \n";
    input += "void outString(string str){\
        int size; \
        size = getSize(str); \
        int i; i = 0; \
        while(i < size) { out(getChar(str, i)); i = i + 1; }}\n";
    input += "void outInts(int n){ if (n) { outInts(n / 10); out(n - n / 10 * 10 + '0'); }}\n";
    input += "void outInt(int n){ if (n == 0) out('0'); if (n < 0) { out('-'); n = 0 - n; } if(n) outInts(n); }\n";
    input += " @EOF";
    QMessageBox::about(NULL, "About", "Start Running!");
    std::stringstream in, infoOut, synOut, semOut, genOut;
    in << input;
    compiler = std::make_shared<Loonguage::Compiler>(in, infoOut, synOut, semOut, genOut);
    compiler->parse();
    QString qinfoOut = QString::fromStdString(infoOut.str());
    QString qsynOut = QString::fromStdString(synOut.str());
    QString qsemOut = QString::fromStdString(semOut.str());
    QString qgenOut = QString::fromStdString(genOut.str());
    ui->infoOut->setPlainText(qinfoOut);
    ui->lexSynOut->setPlainText(qsynOut);
    ui->semOut->setPlainText(qsemOut);
    model = new QStandardItemModel();
    for (const auto& code : compiler->codes)
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
    if (compiler != nullptr && compiler->runable)
    {
        config.endian = config.BIG;
        config.width = config.x64;
        config.memorySize = 16384;
        config.inoutSize = 16384;
        config.stdIn = ui->stdIn->toPlainText().toStdString();
        //if (runtime != nullptr)
        //    delete runtime;
        runtime = std::make_shared<Loonguage::RunTime>(config, compiler->codes, compiler->strTable, compiler->strPosition);
        updateData();
    }
    else
        QMessageBox::about(NULL, "About", "No executable program!");
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
    ui->rcxVal->display(QString::number(runtime->regs[Reg::rin]));
    ui->rdxVal->display(QString::number(runtime->regs[Reg::rot]));
    ui->insVal->display(QString::number(runtime->regs[Reg::ins]));
    ui->rtmVal->display(QString::number(runtime->regs[Reg::rtm]));
    ui->zSign->display(QString::number(runtime->Z));
    ui->sSign->display(QString::number(runtime->S));
    ui->stdOut->setPlainText(QString::fromStdString(runtime->stdOut()));
    QModelIndex index = model->index(runtime->currentCode, 0);
    ui->codeOut->setCurrentIndex(index);
    QStandardItemModel* stackModel = new QStandardItemModel;
    std::vector<int> stack = runtime->getStack();
    for (auto num : stack)
    {
        QStandardItem *item = new QStandardItem(QString::number(num));
        stackModel->appendRow(item);
    }
    ui->stack->setModel(stackModel);
}

void MainWindow::on_allStep_clicked()
{
    if (runtime != nullptr)
    {
        int t = 0;
        qint64 t1 = QDateTime::currentDateTime().toMSecsSinceEpoch();
        while (!runtime->tick())
            //updateData();
            t++;
        qint64 t2 = QDateTime::currentDateTime().toMSecsSinceEpoch();
        QString mes = QString("Successfully done! %1 instructions executed in %2 ms.").arg(t).arg(t2 - t1);
        QMessageBox::about(NULL, "About", mes);
        updateData();
    }
}

