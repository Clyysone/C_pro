#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mybox=new QMessageBox(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    cur_code= ui->code->currentText();
    cur_pwd=ui->passwd->text();
    if(ui->code->currentText()==NULL){
        mybox->show();
        mybox->setText("请输入编号!");
    }
    else if(ui->passwd->text()==NULL){
        mybox->show();
        mybox->setText("请输入密码!");
    }
    else if(ui->su->isChecked()==1){
         if(cur_code=="111"&&cur_pwd=="111"){
                 regis=new op_register(this);
                 regis->show();
         }
         else{
             mybox->show();
             mybox->setText("输入错误");
         }
    }
    else{
        if(op_fileout(oper_file.toLatin1().data())){
            oper=new op_interface(this);
            this->hide();
            oper->show();
        }
    }
}

void MainWindow::on_exit_clicked()
{
    this->close();
}



