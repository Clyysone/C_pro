#ifndef KERNEL_LOGIC_H
#define KERNEL_LOGIC_H
#include<QMainWindow>


//操作员信息
 struct op_info{
    char op_code[20];//操作员编码
    char op_passwd[20];//操作员密码
    char op_name[20];//操作员姓名
    char stor_code[20];//操作员所属仓库编号
};
//仓库信息
struct Storage{
    char stor_code[20];//仓库编号
    char stor_name[20];//仓库名称
    char locate[20];//仓库位置
    char phone_num[20];//仓库电话
    struct Catalogue *head_cata;//指向商品信息头
};

//商品信息
 struct  Catalogue{
    char stor_code[20];//所属仓库
    char goods_code[20];//商品编码
    char goods_name[20];//商品名称
    char goods_type[20];//商品类型
    char  num_units[20];//商品数量单位
    char factory[20];//商品厂商
    struct Catalogue *next_cata;//指向下一个商品信息
    struct Record *head_reco;//指向出入记录信息头
};

//商品出入记录
struct Record{
    char reco_code[20];//流水号
    char stor_code[20];//出入仓库编号
    char goods_code[20];//出入库商品编号
    char date[20];//出入库时间
    char flag;//出入库标记，0表示出，1表示入
    int op_amount;//出入库数量
    char op_code[20];//出入库的操作员编号
    struct Record *next_reco;//指向下一个出入库记录
};

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
class my_class
{
public:
    //从文件中取出操作员信息数据(只取出符合的)
    bool op_fileout(char *filename)
    {
        op_info cur;
        FILE *op_f=fopen(filename,"r");
        if(op_f==NULL){
            printf("open fail:%s",filename);
            return 0;
        }
        while(fscanf(op_f,"%s %s %s %s",cur.op_code,cur.op_passwd,cur.op_name,cur.stor_code)!=EOF){
            if(strcmp(cur_code.toLatin1().data(),cur.op_code)==0&&strcmp(cur_pwd.toLatin1().data(),cur.op_passwd)==0){
                strcpy(cur_op_info.op_code,cur.op_code);
                strcpy(cur_op_info.op_passwd,cur.op_passwd);
                strcpy(cur_op_info.op_name,cur.op_name);
                strcpy(cur_op_info.stor_code,cur.stor_code);
            }
        }
        fclose(op_f);
        return 1;
    }
    //仓库信息取出(取出操作员对应的一个仓库)
    bool stor_fileout(char *filename)
    {
        Storage cur;
        FILE *stor_f=fopen(filename,"r");
        if(stor_f==NULL){
            printf("open fail:%s",filename);
            return 0;
        }
        while(fscanf(stor_f,"%s %s %s %s",cur.stor_code,cur.stor_name,cur.locate,cur.phone_num)!=EOF){
            if(strcmp(cur.stor_code,cur_op_info.stor_code)==0){
                strcpy(cur_stor.stor_code,cur.stor_code);
                strcpy(cur_stor.stor_name,cur.stor_name);
                strcpy(cur_stor.locate,cur.locate);
                strcpy(cur_stor.phone_num,cur.phone_num);
            }
        }
        fclose(stor_f);
        return 1;
    }
    //商品信息取出(将所有的数据载入到链表中)
    bool cata_fileout(char *filename)
    {
        Catalogue *head=(Catalogue *)malloc(sizeof(Catalogue));
        Catalogue *p;
        Catalogue *q;
        Catalogue cur;
        p=q=head;
        FILE *cata_f=fopen(filename,"r");
        if(cata_f==NULL){
            printf("open fail:%s",filename);
            return 0;
        }
        while(fscanf(cata_f,"%s %s %s %s %s %s",cur.stor_code,cur.goods_code,cur.goods_name,cur.goods_type,cur.num_units,cur.factory)!=EOF){
            if(strcmp(cur.stor_code,cur_stor.stor_code)==0){
                q=(Catalogue *)malloc(sizeof(Catalogue));
                strcpy(q->stor_code,cur.stor_code);
                strcpy(q->goods_code,cur.goods_code);
                strcpy(q->goods_name,cur.goods_name);
                strcpy(q->num_units,cur.num_units);
                strcpy(q->goods_type,cur.goods_type);
                strcpy(q->factory,cur.factory);
                p->next_cata=q;
                p=q;
            }
        }
        p->next_cata=NULL;
        fclose(cata_f);
        cur_stor.head_cata=head->next_cata;
        return  1;
    }
    //记录信息取出(返回头指针并将所有的数据载入到链表中)
    bool reco_fileout(char *filename)
    {
        Record *head=(Record *)malloc(sizeof(Record));
        Record *p;
        Record *q;
        Record cur;
        p=q=head;
        FILE *reco_f=fopen(filename,"r");
        if(reco_f==NULL){
            printf("open fail:%s",filename);
            return 0;
        }
        while(fscanf(reco_f,"%s %s %s %s %c %d %s",cur.reco_code,cur.stor_code,cur.goods_code,cur.date,&cur.flag,&cur.op_amount,cur.op_code)!=EOF){
            if(strcmp(cur.goods_code,cur_cata.goods_code)==0&&strcmp(cur.stor_code,cur_cata.stor_code)==0){
                q=(Record *)malloc(sizeof(Record));
                strcpy(q->reco_code,cur.reco_code);
                strcpy(q->stor_code,cur.stor_code);
                strcpy(q->goods_code,cur.goods_code);
                strcpy(q->date,cur.date);
                q->flag=cur.flag;
                q->op_amount=cur.op_amount;
                strcpy(q->op_code,cur.op_code);
                p->next_reco=q;
                p=q;
            }
        }
        p->next_reco=NULL;
        fclose(reco_f);
        cur_cata.head_reco=head->next_reco;
        return 1;
    }
    /*@@@@*****************************************************************@@@@*/
};
#endif // KERNEL_LOGIC_H
