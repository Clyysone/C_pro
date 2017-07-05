#include "op_interface.h"
#include "ui_op_interface.h"
#include <QStandardItemModel>
#include <QDebug>
op_interface::op_interface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::op_interface)
{
    ui->setupUi(this);
    box1=new QMessageBox(this);
    box1->show();
    box1->setText("登录成功!当前操作仓库为："+cur_code);
    ui->op_code->setText(cur_code);
    ui->op_name->setText(cur_op_info.op_name);
    ui->op_stor_code->setText(cur_op_info.stor_code);
    stor_fileout(stor_file.toLatin1().data());
    ui->stor_name->setText(cur_stor.stor_name);
    ui->stor_code->setText(cur_stor.stor_code);
    ui->phone_num->setText(cur_stor.phone_num);
    ui->locate_2->setText(cur_stor.locate);
    cata_fileout(cata_file.toLatin1().data());
    refresh_combox_cata();
    refresh_table_cata();
    refresh_table_count();
    connect(ui->goods_code,SIGNAL(currentIndexChanged(int)),this,SLOT(cata_display()));
    connect(ui->op_goods_code,SIGNAL(currentIndexChanged(int)),this,SLOT(record_select()));
    connect(ui->op_num,SIGNAL(currentIndexChanged(int)),this,SLOT(record_display()));
}

op_interface::~op_interface()
{
    delete ui;
}

void op_interface::on_exit_clicked()
{
    this->close();
    parentWidget()->show();
}

void op_interface::refresh_table_count()
{
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("商品编号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品名称")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("商品类型")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("当前库存")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("厂商名称")));
    ui->info_stat->setModel(model);
    Catalogue *p;
    Record *q;
    int i=0;
    p=cur_stor.head_cata;
    while(p){
        model->setItem(i,0,new QStandardItem(p->goods_code));
        model->setItem(i,1,new QStandardItem(p->goods_name));
        model->setItem(i,2,new QStandardItem(p->goods_type));
        strcpy(cur_cata.stor_code,p->stor_code);
        strcpy(cur_cata.goods_code,p->goods_code);
        strcpy(cur_cata.goods_name,p->goods_name);
        strcpy(cur_cata.goods_type,p->goods_type);
        strcpy(cur_cata.num_units,p->num_units);
        strcpy(cur_cata.factory,p->factory);
        reco_fileout(reco_file.toLatin1().data());
        int cur_num=0;
        q=cur_cata.head_reco;
        while(q){
            if(q->flag=='1')
                cur_num+=q->op_amount;
            else cur_num-=q->op_amount;;
            q=q->next_reco;
        }
        model->setItem(i,3,new QStandardItem(QString::number(cur_num)));
        model->setItem(i,4,new QStandardItem(p->factory));
        p=p->next_cata;
        i++;
    }
}

void op_interface::refresh_table_cata()
{
    QStandardItemModel *cata_model=new QStandardItemModel();
    cata_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("商品编号")));
    cata_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品名称")));
    cata_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("商品类型")));
    cata_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("数量单位")));
    cata_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("厂商名称")));
    ui->info_goods->setModel(cata_model);
    Catalogue *p;
    int i=0;
    p=cur_stor.head_cata;
    while(p){
        cata_model->setItem(i,0,new QStandardItem(p->goods_code));
        cata_model->setItem(i,1,new QStandardItem(p->goods_name));
        cata_model->setItem(i,2,new QStandardItem(p->goods_type));
        cata_model->setItem(i,3,new QStandardItem(p->num_units));
        cata_model->setItem(i,4,new QStandardItem(p->factory));
        p=p->next_cata;
        i++;
    }
}

void op_interface::refresh_combox_cata()
{
    ui->goods_code->clear();
    ui->goods_code->addItem("——请选择——");
    ui->goods_code->addItem("点我进行添加");
    ui->op_goods_code->clear();
    ui->op_goods_code->addItem("——请选择——");
    ui->stat_goods_code->clear();
    ui->op_num->clear();
    Catalogue *p;
    cata_fileout(cata_file.toLatin1().data());
    p=cur_stor.head_cata;
    while(p){
        ui->goods_code->addItem(p->goods_code);
        ui->op_goods_code->addItem(p->goods_code);
        ui->stat_goods_code->addItem(p->goods_code);
        p=p->next_cata;
    }
}

void op_interface::cata_display()
{
    if(ui->goods_code->currentIndex()==1){
        ui->goods_code->setEditable(1);
        ui->goods_name->clear();
        ui->goods_type->clear();
        ui->num_units->clear();
        ui->factory->clear();
    }
    else{
        ui->goods_code->setEditable(0);
        Catalogue *p;
        p=cur_stor.head_cata;
        while(p){
            if(strcmp(p->goods_code,ui->goods_code->currentText().toLatin1().data())==0){
                ui->goods_name->setText(p->goods_name);
                ui->goods_type->setText(p->goods_type);
                ui->num_units->setText(p->num_units);
                ui->factory->setText(p->factory);
                break;
            }
            p=p->next_cata;
        }
    }
}

void op_interface::record_select()
{
    Catalogue *p;
    ui->op_type->setCurrentIndex(0);
    ui->op_amount->clear();
    ui->date->clear();
    p=cur_stor.head_cata;
    while(p){
        if(strcmp(p->goods_code,ui->op_goods_code->currentText().toLatin1().data())==0){
           strcpy(cur_cata.stor_code,p->stor_code);
           strcpy(cur_cata.goods_code,p->goods_code);
           strcpy(cur_cata.goods_name,p->goods_name);
           strcpy(cur_cata.goods_type,p->goods_type);
           strcpy(cur_cata.num_units,p->num_units);
           strcpy(cur_cata.factory,p->factory);
           break;
        }
        p=p->next_cata;
    }
    reco_fileout(reco_file.toLatin1().data());
    ui->op_num->clear();
    ui->op_num->addItem("——请选择——");
    ui->op_num->addItem("点我进行添加");
    QStandardItemModel *model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("流水号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("商品编号")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("处理类型")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("处理数量")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("处理时间")));
    ui->info_record->setModel(model);
    Record *q;
    QString str;
    int i=0;
    q=cur_cata.head_reco;
    while(q){
        ui->op_num->addItem(q->reco_code);
        if(q->flag=='1')
            str="入库";
        else str="出库";
        model->setItem(i,0,new QStandardItem(q->reco_code));
        model->setItem(i,1,new QStandardItem(q->goods_code));
        model->setItem(i,2,new QStandardItem(str));
        model->setItem(i,3,new QStandardItem(QString::number(q->op_amount)));
        model->setItem(i,4,new QStandardItem(q->date));
        q=q->next_reco;
        i++;
    }

}

void op_interface::record_display()
{
    if(ui->op_num->currentIndex()==1){
        ui->op_num->setEditable(1);
    }
    else{
        ui->op_num->setEditable(0);
        Record *p;
        p=cur_cata.head_reco;
        while(p){
            if(strcmp(p->reco_code,ui->op_num->currentText().toLatin1().data())==0){
                if(p->flag=='1')
                    ui->op_type->setCurrentIndex(1);
                else ui->op_type->setCurrentIndex(2);
                ui->op_amount->setText(QString::number(p->op_amount));
                ui->date->setText(p->date);
                break;
            }
            p=p->next_reco;
        }
    }
}

void op_interface::on_op_info_change_clicked()
{

}

void op_interface::on_op_passwd_change_clicked()
{

}

void op_interface::on_goods_add_clicked()
{
    Catalogue *p;
    int flag=0;
    p=cur_stor.head_cata;
    while(p->next_cata){
        if(strcmp(p->goods_code,ui->goods_code->currentText().toLatin1().data())==0){
            box1->show();
            box1->setText("已存在该商品");
            flag=1;
        }
        p=p->next_cata;
    }
    if(flag==0){
        FILE *fp=fopen(cata_file.toLatin1().data(),"a");
        fprintf(fp,"\n%s %s %s %s %s %s",
                p->stor_code,
                ui->goods_code->currentText().toUtf8().constData(),
                ui->goods_name->text().toUtf8().constData(),
                ui->goods_type->text().toUtf8().constData(),
               ui->num_units->text().toUtf8().constData(),
                ui->factory->text().toUtf8().constData());
        fclose(fp);
        ui->goods_code->setCurrentIndex(0);
        ui->goods_name->clear();
        ui->goods_type->clear();
       ui->num_units->clear();
        ui->factory->clear();
        box1->show();
        box1->setText("添加成功！");
    }
    refresh_combox_cata();
    refresh_table_cata();
    refresh_table_count();
}

void op_interface::on_goods_delete_clicked()
{
    FILE *fp=fopen(cata_file.toLatin1().data(),"r");
    FILE *temp=fopen("D:\\Study-file\\_C\\C_pro\\catalogue\\temp.txt","w");
    Catalogue temp_struc;
    while( fscanf(fp,"\n%s %s %s %s %s %s",temp_struc.stor_code,temp_struc.goods_code,temp_struc.goods_name,
                   temp_struc.goods_type,temp_struc.num_units,temp_struc.factory)!=EOF){
         if(strcmp(temp_struc.goods_code,ui->goods_code->currentText().toLatin1().data())!=0){
             fprintf(temp,"%s %s %s %s %s %s\n",temp_struc.stor_code,temp_struc.goods_code,temp_struc.goods_name,
                      temp_struc.goods_type,temp_struc.num_units,temp_struc.factory);
         }
    }
    fclose(fp);
    fclose(temp);
    ui->goods_name->clear();
    ui->goods_type->clear();
    ui->num_units->clear();
    ui->factory->clear();
    box1->show();
    box1->setText("删除成功！");
    remove(cata_file.toLatin1().data());
    rename("D:\\Study-file\\_C\\C_pro\\catalogue\\temp.txt",cata_file.toLatin1().data());
    refresh_combox_cata();
    refresh_table_cata();
    refresh_table_count();
}

void op_interface::on_goods_alter_clicked()
{
    FILE *fp=fopen(cata_file.toLatin1().data(),"r");
    FILE *temp=fopen("D:\\Study-file\\_C\\C_pro\\catalogue\\temp.txt","w");
    Catalogue temp_struc;
    while( fscanf(fp,"\n%s %s %s %s %s %s",temp_struc.stor_code,temp_struc.goods_code,temp_struc.goods_name,
                   temp_struc.goods_type,temp_struc.num_units,temp_struc.factory)!=EOF){
         if(strcmp(temp_struc.goods_code,ui->goods_code->currentText().toLatin1().data())!=0){
             fprintf(temp,"%s %s %s %s %s %s\n",temp_struc.stor_code,temp_struc.goods_code,temp_struc.goods_name,
                      temp_struc.goods_type,temp_struc.num_units,temp_struc.factory);
         }
         else{
             fprintf(temp,"%s %s %s %s %s %s\n",
                     temp_struc.stor_code,
                     ui->goods_code->currentText().toUtf8().constData(),
                     ui->goods_name->text().toUtf8().constData(),
                     ui->goods_type->text().toUtf8().constData(),
                     ui->num_units->text().toUtf8().constData(),
                     ui->factory->text().toUtf8().constData());
         }
    }
    fclose(fp);
    fclose(temp);
    ui->goods_name->clear();
    ui->goods_type->clear();
    ui->num_units->clear();
    ui->factory->clear();
    box1->show();
    box1->setText("修改成功！");
    remove(cata_file.toLatin1().data());
    rename("D:\\Study-file\\_C\\C_pro\\catalogue\\temp.txt",cata_file.toLatin1().data());
    refresh_combox_cata();
    refresh_table_cata();
    refresh_table_count();
}

void op_interface::on_stor_alter_clicked()
{

}

void op_interface::on_record_add_clicked()
{

}

void op_interface::on_record_delete_clicked()
{

}

void op_interface::on_record_alter_clicked()
{
    FILE *fp=fopen(reco_file.toLatin1().data(),"r");
    FILE *temp=fopen("D:\\Study-file\\_C\\C_pro\\record\\temp.txt","w");
    Record temp_struc;
    while( fscanf(fp,"\n%s %s %s %s %c %d %s",temp_struc.reco_code,temp_struc.stor_code,temp_struc.goods_code,
                   temp_struc.date,&temp_struc.flag,&temp_struc.op_amount,temp_struc.op_code)!=EOF){
         if(strcmp(temp_struc.reco_code,ui->op_num->currentText().toLatin1().data())!=0){
             fprintf(temp,"%s %s %s %s %c %d %s\n",temp_struc.reco_code,temp_struc.stor_code,temp_struc.goods_code,
                     temp_struc.date,temp_struc.flag,temp_struc.op_amount,temp_struc.op_code);
         }
         else{
             fprintf(temp,"%s %s %s %s %c %d %s\n",
                     ui->op_num->currentText().toUtf8().constData(),
                     temp_struc.stor_code,
                     ui->op_goods_code->currentText().toUtf8().constData(),
                     ui->date->text().toUtf8().constData(),
                     ((ui->op_type->currentIndex()==1)?'1':'2'),
                     ui->op_amount->text().toInt(),
                     ui->op_code->text().toUtf8().constData());
         }
    }
    fclose(fp);
    fclose(temp);
    //ui->op_num->setCurrentText(0);
    ui->date->clear();
    ui->op_type->setCurrentText(0);
    ui->op_amount->clear();
    box1->show();
    box1->setText("修改成功！");
    remove(reco_file.toLatin1().data());
    rename("D:\\Study-file\\_C\\C_pro\\record\\temp.txt",reco_file.toLatin1().data());
    refresh_combox_cata();
    refresh_table_cata();
    refresh_table_count();
}

void op_interface::on_select_clicked()
{
    Catalogue *p;
    Record *q;
    p=cur_stor.head_cata;
    while(p){
       if(strcmp(p->goods_code,ui->stat_goods_code->currentText().toLatin1().data())==0){
           ui->stat_goods_name->setText(p->goods_name);
           ui->stat_goods_type->setText(p->goods_type);
           strcpy(cur_cata.stor_code,p->stor_code);
           strcpy(cur_cata.goods_code,p->goods_code);
           strcpy(cur_cata.goods_name,p->goods_name);
           strcpy(cur_cata.goods_type,p->goods_type);
           strcpy(cur_cata.num_units,p->num_units);
           strcpy(cur_cata.factory,p->factory);
           reco_fileout(reco_file.toLatin1().data());
           int cur_num=0;
           q=cur_cata.head_reco;
           while(q){
               if(q->flag=='1')
                   cur_num+=q->op_amount;
               else cur_num-=q->op_amount;;
               q=q->next_reco;
           }

           ui->stat_goods_amount->setText(QString::number(cur_num));
           ui->stat_num_units->setText(p->num_units);
        }
       p=p->next_cata;
    }
}
