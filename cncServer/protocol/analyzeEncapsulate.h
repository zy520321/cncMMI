#ifndef ANALYZEENCAPSULATE_H
#define ANALYZEENCAPSULATE_H

enum DATA_TYPE
{
	//bool,float
	DATA_TYPE_bool,
	DATA_TYPE_float
};

#define DATA_TYPE_LENGTH 2
#define DATA_LENGTH 20
#define DATA_ID_MASTER_LENGTH 2
#define DATA_ID_MINOR_LENGTH 2
#define DATA_FORMAT_LENGTH 2
#define DATA_ADDR_LENGTH 6
#define DATA_CONTENT_LENGTH 8
#define DATA_ACK_OR_ERR_LENGTH 2

#define ADDR_TYPE_I "I*"
#define ADDR_TYPE_M "M*"
#define ADDR_TYPE_D "D*"

#define RW_CMD_R "RR"
#define RW_CMD_W "WW"

typedef struct DATA_FORMAT
{
    char masterID[DATA_ID_MASTER_LENGTH];
    char rw[DATA_ID_MINOR_LENGTH];//操作命令,读写
	char content[DATA_TYPE_LENGTH];//M,D,X,Y,Z等
    DATA_TYPE type;//bool,float(通过地址类型也可判断数据类型)
	union
	{
		int iData;
		float fData;
	}data;
	int startPosition;//M6000话，就是6000
    int ret;//错误号:非0,定义错误（超时，读写失败）
}ADDR_INFO;


#define IS_I_DATA(a) (strncmp(a, ADDR_TYPE_I, 2) == 0 ? true : false)
#define IS_M_DATA(a) (strncmp(a, ADDR_TYPE_M, 2) == 0 ? true : false)
#define IS_D_DATA(a) (strncmp(a, ADDR_TYPE_D, 2) == 0 ? true : false)

#define IS_READ(a) (strncmp(a, RW_CMD_R, 2) == 0 ? true : false)
#define IS_WRITE(a) (strncmp(a, RW_CMD_W, 2) == 0 ? true : false)

#define IS_BOOL_DATA(a) (a == DATA_TYPE_bool ? true : false)
#define IS_FLOAT_DATA(a) (a == DATA_TYPE_float ? true : false)

int parseData(/*in*/char * buf, /*in*/int size, /*out*/struct DATA_FORMAT * data, /*out*/int * counts);

int getPacketCounts(/*in*/int size);
int getAckPacketCounts(int size);
int analyze(/*in*/const char * buf, /*in*/int size, /*out*/struct DATA_FORMAT * data, /*in*/int counts);
int encapsulate(/*in*/struct DATA_FORMAT * data,/*in*/ int counts, /*out*/char * buf, /*in*/int size, bool ack = false);

typedef int (*transterData)(ADDR_INFO * addr, int counts, void * pVoid);

#endif 
