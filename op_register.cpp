#include "op_register.h"
#include "ui_op_register.h"

op_register::op_register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::op_register)
{
    ui->setupUi(this);
}

op_register::~op_register()
{
    delete ui;
}

void op_register::on_tabWidget_tabBarClicked(int index)
{
    if(index==2){
        this->close();
    }
}

void op_register::on_stor_add_clicked()
{
    FILE *open=fopen("D:\\Study-file\\_C\\C_pro\\storage\\storage.txt","a");
    fprintf(open,"\n%s %s %s %s",ui->stor_code->currentText().toUtf8().constData(),ui->stor_name->text().toUtf8().constData(),ui->locate->text().toUtf8().constData(),ui->phone_num->text().toUtf8().constData());
    fclose(open);
}
