#include "widget.h"
#include <QApplication>
#include <mysql.h>
#include <QDebug>

struct table_info
{
    char plugin[32];
    char object[32];
    int addr;
    char dataArea[3];
    int dataType;
    char rw[3];
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const char user[] = "root";
    const char pswd[] = "123456";
    const char host[] = "10.0.11.57";
    const char table[] = "test";//mysql中数据库名称
    const char table1[] = "select plugin,object,addr,dataArea,dataType,rw from pluginObjectAddrs";//plugin,object,addr,dataArea,dataType,rw
    char value1[] = "insert into pluginObjectAddrs values('1','2',3,'4*',0,'6',null,null);";
    char query[] = "select * from pluginObjectAddrs where object like 'labelCoordExValueX'";
    MYSQL myCont;
    MYSQL_RES *result = NULL;
    MYSQL_ROW sql_row;
    int res;
    mysql_init(&myCont);
    char value = 1;
    mysql_options(&myCont,MYSQL_OPT_RECONNECT,(char*)&value);
    if (mysql_real_connect(&myCont, host, user, pswd, table, 0, NULL, 0))
    {
        /*
        res = mysql_real_query(&myCont, value1, strlen(value1));
        if (!res)
        {
            qDebug("insert data success!\n");
        }
        */
        res = mysql_query(&myCont, query);

        //res = mysql_query(&myCont,  table1);//查询
        if (!res)
        {
            result = mysql_store_result(&myCont);
            if (result)
            {
                struct table_info info;
                memset(&info, 0, sizeof(table_info));
                while (sql_row = mysql_fetch_row(result))//获取具体的数据
                {
                    strcpy(info.plugin, sql_row[0]);
                    strcpy(info.object, sql_row[1]);
                    info.addr = atoi(sql_row[2]);
                    strcpy(info.dataArea, sql_row[3]);
                    info.dataType = atoi(sql_row[4]);
                    strcpy(info.rw, sql_row[5]);
                    qDebug("info:%s,%s,%d,%s,%d,%s...\n", info.plugin, info.object, info.addr, info.dataArea,
                           info.dataType, info.rw);
                }
            }
        }
        else
        {
            //cout << "query sql failed!" << endl;
        }
    }
    else
    {
       // cout << "connect failed!" << endl;
    }
    if (result != NULL)
        mysql_free_result(result);
    mysql_close(&myCont);
    system("pause");
    return 0;
}
