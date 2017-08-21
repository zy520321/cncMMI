#ifndef MYSQLINTERFACE_H
#define MYSQLINTERFACE_H

class MySqlInterface
{
public:
    virtual void initMySqlServer(char * ip, int port) = 0;
    virtual bool add(char * key, char * value) = 0;
    virtual bool del(char * key, char * value) = 0;
    virtual bool modify(char * key, char * value) = 0;
    virtual bool query(char * key, char * value) = 0;
};

#endif // MYSQLINTERFACE_H
