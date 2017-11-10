#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qtime>
#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //func list
    void openFile();
    void saveFile();
    void lexicalAnalysis();
    void aboutDialog();

private:
    Ui::MainWindow *ui;

    //var list
    const QString TextEditSrcInitString = "<p style=\"color:gray\">点击<b>打开</b>按钮打开源文件...</p>";

    QString qstringTextEditSrc;     //src窗口文本
    QString qstringTextEditDest;    //dest窗口文本
    QString qstringTextEditMsg;     //msg窗口文本
};

#endif // MAINWINDOW_H
