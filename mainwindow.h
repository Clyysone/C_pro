#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<op_interface.h>
#include<op_register.h>
#include"kernel_logic.h"
extern QString oper_file;
extern QString stor_file;
extern QString cata_file;
extern QString reco_file;
extern QString cur_code;//（登录即唯一）仓库号
extern QString cur_pwd;
extern op_info   cur_op_info;
extern Storage   cur_stor;
extern Catalogue   cur_cata;
extern Record   cur_reco;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,public my_class
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_login_clicked();

    void on_exit_clicked();

private:
    Ui::MainWindow *ui;
    op_register *regis;
    QMessageBox *mybox;
     op_interface *oper;
};

#endif // MAINWINDOW_H
