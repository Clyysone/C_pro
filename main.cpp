#include "mainwindow.h"
#include <QApplication>

QString oper_file="D:\\Study-file\\_C\\C_pro\\op_info\\op_info.txt";
QString stor_file="D:\\Study-file\\_C\\C_pro\\storage\\storage.txt";
QString cata_file="D:\\Study-file\\_C\\C_pro\\catalogue\\catalogue.txt";
QString reco_file="D:\\Study-file\\_C\\C_pro\\record\\record.txt";
QString cur_code;
QString cur_pwd;
op_info   cur_op_info;
Storage   cur_stor;
Catalogue   cur_cata;
Record   cur_reco;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
