#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "lexana.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //变量
    qstringTextEditSrc = TextEditSrcInitString;
    qstringTextEditDest = "";
    qstringTextEditMsg = QTime::currentTime().toString() + " " + "就绪";

    //界面
    ui->label_src->setText("源文件");
    ui->label_dest->setText("结果");
    ui->label_msg->setText("消息");
    ui->textEdit_src->setText(qstringTextEditSrc);
    ui->textEdit_dest->setText(qstringTextEditDest);
    ui->textEdit_msg->setText(qstringTextEditMsg);

    //事件
    connect(ui->action_open, QAction::triggered, this, &MainWindow::openFile);
    connect(ui->action_quit, QAction::triggered, this, &MainWindow::close);
    connect(ui->action_lexana, QAction::triggered, this, &MainWindow::lexicalAnalysis);
    connect(ui->action_about, QAction::triggered, this, &MainWindow::aboutDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    //qstringTextEditSrc = "";

    //获取文件路径
    QString fileName = QFileDialog::getOpenFileName(this, NULL, NULL, "*.c *.cpp *.txt");
    //打开文件
    QFile source(fileName);
    if(source.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //src
        qstringTextEditSrc = source.readAll();
        //msg
        qstringTextEditMsg += "\n" + QTime::currentTime().toString() + " 打开文件 " + fileName + " 成功!";
    }
    else
    {
        //msg
        qstringTextEditMsg += "\n" + QTime::currentTime().toString() + " 打开文件 " + fileName + " 失败!";
        //弹窗
        QMessageBox::critical(NULL, "错误", "打开文件失败!");
    }


    //show
    ui->textEdit_src->setText(qstringTextEditSrc);
    ui->textEdit_msg->setText(qstringTextEditMsg);
}

void MainWindow::lexicalAnalysis()
{
    ui->label_dest->setText("词法分析");
    qstringTextEditDest = "";
    qstringTextEditMsg += "\n" + QTime::currentTime().toString();

    LexicalAnalysis la(qstringTextEditSrc);
    la.lexAna(qstringTextEditDest, qstringTextEditMsg);

    ui->textEdit_dest->setText(qstringTextEditDest);
    ui->textEdit_msg->setText(qstringTextEditMsg);
}

void MainWindow::aboutDialog()
{
    QMessageBox::about(NULL, "关于", "<p>编译原理实验实验</p><p>作者: 丁鹏</p>");
}
