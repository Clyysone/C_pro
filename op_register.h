#ifndef OP_REGISTER_H
#define OP_REGISTER_H

#include <QMainWindow>
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
class op_register;
}

class op_register : public QMainWindow,public my_class
{
    Q_OBJECT

public:
    explicit op_register(QWidget *parent = 0);
    ~op_register();

private slots:
    void on_tabWidget_tabBarClicked(int index);

    void on_stor_add_clicked();

private:
    Ui::op_register *ui;
};

#endif // OP_REGISTER_H
