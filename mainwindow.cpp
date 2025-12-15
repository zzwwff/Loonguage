#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Compiler/Compiler/RuntimeConfig.h"
#include "QString"
#include <sstream>
#include <QMessageBox>
#include <QTime>
#include <QFile>
#include <QRegularExpression>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Loonguage)
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
    QRegularExpression regExp("[0-9]*");
    QRegularExpressionValidator *pattern = new QRegularExpressionValidator(regExp, this);
    ui->memorySizeInput->setValidator(pattern);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QStandardItemModel* MainWindow::setListView(QListView* view, std::vector<Loonguage::Code> codes)
{
    QStandardItemModel* model = new QStandardItemModel();
    for (const auto& code : codes)
    {
        std::stringstream stream;
        code.dump(stream);
        std::string str = stream.str();
        if (str.back() == '\n') str.pop_back();
        QStandardItem *item = new QStandardItem(QString::fromStdString(str));
        model->appendRow(item);
    }

    view->setModel(model);
    return model;
}

//Compiling button
void MainWindow::on_pushButton_clicked()
{
    //clear existed resources
    compiler = nullptr;
    runtime = nullptr;
    if (codeSource == AUTO)
    {
        setListView(ui->codeShow, std::vector<Loonguage::Code>());
        bitstream = nullptr;
    }
    codeOutView = setListView(ui->codeOut, std::vector<Loonguage::Code>());

    QString qinput = ui->input->toPlainText();
    std::string input = qinput.toStdString();
    if (input.find('@') != std::string::npos)
    {
        QMessageBox::about(NULL, "About", "禁止输入\"@\"!");
        return;
    }
    //save input
    QFile file("input.in");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(QString::fromStdString(input).toUtf8());
    file.close();

    input += ui->input2->toPlainText().toStdString();
    QMessageBox::about(NULL, "About", "Start Running!");
    std::stringstream in, infoOut, synOut, semOut, genOut;
    in << input;
    compiler = std::make_shared<Loonguage::Compiler>(in, infoOut, synOut, semOut, genOut);
    bool sign = compiler->parse(memorySize);
    QString qinfoOut = QString::fromStdString(infoOut.str());
    QString qsynOut = QString::fromStdString(synOut.str());
    QString qsemOut = QString::fromStdString(semOut.str());
    QString qgenOut = QString::fromStdString(genOut.str());
    ui->infoOut->setPlainText(qinfoOut);
    ui->lexSynOut->setPlainText(qsynOut);
    ui->semOut->setPlainText(qsemOut);
    if (sign)
    {
        codeOutView = setListView(ui->codeOut, compiler->codes);
        if (codeSource == AUTO)
        {
            setListView(ui->codeShow, compiler->codes);
            bitstream = std::make_shared<Loonguage::BitStream>(*compiler);
        }
    }
}

//Run button
void MainWindow::on_pushButton_6_clicked()
{
    if (compiler != nullptr && compiler->runable)
    {
        config.endian = config.BIG;
        config.memorySize = memorySize;
        config.inoutSize = memorySize;
        config.stdIn = ui->stdIn->toPlainText().toStdString();
        //if (runtime != nullptr)
        //    delete runtime;
        runtime = std::make_shared<Loonguage::RunTime>(config, *compiler, ui->stdIn->toPlainText().toStdString());
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
    ui->rcxVal->display(QString::number(runtime->regs[Reg::rcx]));
    ui->rdxVal->display(QString::number(runtime->regs[Reg::rdx]));
    ui->rinVal->display(QString::number(runtime->regs[Reg::rin]));
    ui->rotVal->display(QString::number(runtime->regs[Reg::rot]));
    ui->rhiVal->display(QString::number(runtime->regs[Reg::rhi]));
    ui->rloVal->display(QString::number(runtime->regs[Reg::rlo]));
    ui->insVal->display(QString::number(runtime->regs[Reg::ins]));
    ui->rtmVal->display(QString::number(runtime->regs[Reg::rtm]));
    ui->stdOut->setPlainText(QString::fromStdString(runtime->stdOut()));
    QModelIndex index = codeOutView->index(runtime->currentCode, 0);
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


void MainWindow::on_generateTestBenchCodes_clicked()
{
    if (codeSource == MANUAL)
    {
        std::string input = ui->codeInput->toPlainText().toStdString();
        std::stringstream stream(input);
        bool signal = true;
        bitstream = std::make_shared<Loonguage::BitStream>(stream, signal, memorySize);
        if (!signal)
        {
            bitstream = nullptr;
            ui->testBenchCodes->setPlainText("汇编代码解析错误");
            return;
        }
        setListView(ui->codeShow, bitstream->codes);
    }
    if (bitstream == nullptr)
    {
        QMessageBox::about(NULL, "About", "No available codes!");
        return;
    }
    QString pattern = ui->pattern->toPlainText();
    QStandardItemModel* model = new QStandardItemModel();
    std::string output;
    //start from -1, -1 means print string constant allocation
    for (int i = -1; i < (int)bitstream->codes.size(); i++)
    {
        std::stringstream stream;
        bitstream->generateTestBench(stream, pattern.toStdString(), i);
        std::string str = stream.str();
        output += str;
    }
    ui->testBenchCodes->setPlainText(QString::fromStdString(output));
}


void MainWindow::on_radioButton_clicked()
{
    codeSource = MANUAL;
    ui->generateTestBenchCodes->setText("解析输入并生成TestBench测试代码");
    ui->codeInput->setPlainText("hlt");
    ui->codeInput->setReadOnly(false);
    ui->testBenchCodes->setPlainText("由于手动汇编代码可能会有复杂的格式问题，您应当认真检查预览窗口中的汇编代码是否与预期相符再复制输出!");
}


void MainWindow::on_radioButton_2_clicked()
{
    codeSource = AUTO;
    ui->generateTestBenchCodes->setText("生成TestBench测试代码");
    ui->codeInput->setPlainText("已关闭手动输入");
    ui->codeInput->setReadOnly(true);
    if (compiler != nullptr)
        bitstream = std::make_shared<Loonguage::BitStream>(*compiler);
    else bitstream = nullptr;
    if (compiler != nullptr)
        setListView(ui->codeShow, compiler->codes);
    ui->testBenchCodes->setPlainText("自动汇编代码由源码编译生成，请确认代码在最新修改后进行过编译!");
}




void MainWindow::on_memorySizeInput_textChanged(const QString &arg1)
{
    int num = arg1.toInt();
    if (num >= 16 && num <= 131072)
        memorySize = num;
}

//generate COE file
void MainWindow::on_pushButton_3_clicked()
{
    if (bitstream == nullptr)
    {
        QMessageBox::about(NULL, "About", "No available codes!");
        return;
    }
    QString fileString = QFileDialog::getSaveFileName(
        this,
        tr("保存文件"),
        QDir::currentPath() + "/data",
        tr("数据文件 (*.coe);")
    );;
    std::string data;
    std::stringstream ss(data);
    bitstream->generateCoe(ss);
    data = ss.str();
    QFile file(fileString);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(QString::fromStdString(data).toUtf8());
    file.close();
}


void MainWindow::on_writeUSB_clicked()
{
    if (bitstream == nullptr)
    {
        QMessageBox::about(NULL, "About", "No available codes!");
        return;
    }
    QString portName = ui->portName->toPlainText();
    wchar_t portname[255];
    memset(portname, 0, sizeof(portname));
    int length = portName.toWCharArray(portname);
    std::string res = bitstream->writeUSB(portname, length);
    if (res.size())
        QMessageBox::about(NULL, "About", res.c_str());
    else
        QMessageBox::about(NULL, "About", "成功写入!");
}

