#include "analyzeEncapsulate.h"

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

float hexToFloat(char* ch);

long floatToHex(float HEX)//浮点数到十六进制转换
{
	return *( long *)&HEX;
}
int getPacketCounts(/*in*/int size)
{
    return  (size + 1) / (DATA_LENGTH + 1);
}

int getAckPacketCounts(int size)
{
    return  (size + 1) / (DATA_LENGTH + DATA_ACK_OR_ERR_LENGTH + 1);
}

float BinarytoInt(char *ch,int num)
{
    int retint = 0,i = 0;
    for(i = 0;i< num;i++)
    {
        retint = retint + (ch[i] == '1' ? 1:0) * pow(2,(num-1-i));
    }
    return (float)retint;
}

float BinarytoSmallNumber(char *ch,int num)
{
    float retf = 0.0;
    int i = 0;
    for(i = 0;i<num;i++)
    {
        retf = retf +  (ch[i] == '1'?1:0) * pow(2,(-(i + 1)) ) ;

    }
    return retf;
}


/*格式：
 *主标识（2） + 副标识（2） + 类型（2） + 地址（6） + 数据内容（8）
 *00 RR M* 060000 00000000（读取M60000的内容，RR读，WW写）；目前主副标识为0.
 *多个之间用“;”隔开。
 */

/*应答包格式：
 *AC/ER(2) + 主标识（2） + 副标识（2） + 类型（2） + 地址（6） + 应答数据或错误号（8）
 */
//对数据进行解析，同时分析数据的正确性（格式）
int analyze(const char * buf, int size, struct DATA_FORMAT * data, int counts)
{
	//size的大小和counts存在一定的关系，即size = *counts * DATA_LENGTH + *counts -1;
	//data内存空间是外部申请维护还是内部维护？
    if (NULL == buf || NULL == data ||
            size < (counts * DATA_LENGTH + counts -1) )
	{
		//error
		return -1;
	}
    const char * tmp = buf;
    int num = counts;
    char value[8] = {0};
    bool isErrorData;
	for (int i = 0; i < num; i++)
	{
        isErrorData = false;
		if (';' == tmp[0])
		{
			tmp += 1;
		}

        if (0 == strncmp(tmp, "ER", DATA_ACK_OR_ERR_LENGTH))
        {
            isErrorData = true;
            tmp += DATA_ACK_OR_ERR_LENGTH;
        }
        else if (0 == strncmp(tmp, "AC", DATA_ACK_OR_ERR_LENGTH))
        {
            tmp += DATA_ACK_OR_ERR_LENGTH;
        }

        tmp += DATA_ID_MASTER_LENGTH;

        memcpy((data + i)->rw, tmp, DATA_ID_MINOR_LENGTH);
        tmp += DATA_ID_MINOR_LENGTH;

        memcpy((data + i)->content, tmp, DATA_TYPE_LENGTH);

        if ('M' == tmp[0] || ('D' == tmp[0]))//待补充完整，各类型，如X,Y等
		{
			(data + i)->type = DATA_TYPE_bool;
		}
        else // if (('I' == tmp[0])
		{
			(data + i)->type = DATA_TYPE_float;
		}
		tmp += DATA_FORMAT_LENGTH;

        memset(value, 0, 8);
		memcpy(value, tmp, DATA_ADDR_LENGTH);
		(data + i)->startPosition = atoi(value) ;

		tmp += DATA_ADDR_LENGTH;
        memset(value, 0, 8);
		memcpy(value, tmp, DATA_CONTENT_LENGTH);

        if (DATA_TYPE_bool == (data + i)->type || isErrorData)
		{
			(data + i)->data.iData = atoi(value);
		}
		else
		{
			(data + i)->data.fData = hexToFloat(value);
		}

        if (isErrorData)
        {
            (data + i)->ret = (data + i)->data.iData;
        }
        else
            (data + i)->ret = 0;

		tmp += DATA_CONTENT_LENGTH;
	}
    return 0;
}

int encapsulate(struct DATA_FORMAT * data, int counts, char * buf, int size, bool ack)
{
	if (NULL == data || counts <= 0 || NULL == buf || NULL == size ||
        counts * DATA_LENGTH > size)
	{
		//error
		return -1;
	}
    memset(buf, 0, size);

	int i = 0;
	char * tmp = buf;
	char value[12] = {0};//clear 0
	long num = 0;
    bool read = true;
		 
	for (; i < counts; i++)
    {
		if (i != 0)
		{
			* tmp = ';';
            tmp++;
		}
        if (ack)
        {
            memcpy(tmp, (data + i)->ret == 0 ? "AC" : "ER", DATA_ACK_OR_ERR_LENGTH);
            tmp += DATA_ACK_OR_ERR_LENGTH;
        }

        //master head
        memcpy(tmp, "00", DATA_ID_MASTER_LENGTH);
        tmp += DATA_ID_MASTER_LENGTH;

        //minor head
        memcpy(tmp, (data + i)->rw , DATA_ID_MINOR_LENGTH);
        tmp += DATA_ID_MINOR_LENGTH;

		memcpy(tmp, (data + i)->content, DATA_TYPE_LENGTH);
        tmp += DATA_FORMAT_LENGTH;

        memset(value, 0, 12);
		sprintf(value, "%06d", (data + i)->startPosition);
		memcpy(tmp, value, DATA_ADDR_LENGTH);
        tmp += DATA_ADDR_LENGTH;

        memset(value, 0, 12);
        if (DATA_TYPE_bool == (data + i)->type || (data + i)->ret != 0)
		{
			sprintf(value, "%08d", (data + i)->data.iData);
		}
		else
		{
			num = floatToHex((data + i)->data.fData);
			sprintf(value, "%08x", num);
		}
        memcpy(tmp, value, DATA_CONTENT_LENGTH);
		tmp += DATA_CONTENT_LENGTH;
	}
    return counts * ( ack ? DATA_LENGTH + 2 : DATA_LENGTH) + counts - 1;
}

float hexToFloat(char* ch) //传入８位１６进制　42F0E666
{
    if (NULL == ch)
    {
        return -1;
    }
    else if(!strcmp(ch, "00000000"))
    {
        return 0;
    }
    float returnData = 0.0;
    int max = 8,i = 0;
    char binary[32] = {0};
    char  tmp = '0';
    for(i = 0;i<max;i++)
    {
        tmp = ch[i];
        switch(tmp)
        {
        case '0':
            sprintf(binary+i*4,"%s","0000");
            break;
        case '\0':
            sprintf(binary+i*4,"%s","0000");
            break;
        case '1':
            sprintf(binary+i*4,"%s","0001");
            break;
        case '2':
            sprintf(binary+i*4,"%s","0010");
            break;
        case '3':
            sprintf(binary+i*4,"%s","0011");
            break;
        case '4':
            sprintf(binary+i*4,"%s","0100");
            break;
        case '5':
            sprintf(binary+i*4,"%s","0101");
            break;
        case '6':
            sprintf(binary+i*4,"%s","0110");
            break;
        case '7':
            sprintf(binary+i*4,"%s","0111");
            break;
        case '8':
            sprintf(binary+i*4,"%s","1000");
            break;
        case '9':
            sprintf(binary+i*4,"%s","1001");
            break;
        case 'A':
            sprintf(binary+i*4,"%s","1010");
            break;
        case 'B':
            sprintf(binary+i*4,"%s","1011");
            break;
        case 'C':
            sprintf(binary+i*4,"%s","1100");
            break;
        case 'D':
            sprintf(binary+i*4,"%s","1101");
            break;
        case 'E':
            sprintf(binary+i*4,"%s","1110");
            break;
        case 'F':
            sprintf(binary+i*4,"%s","1111");
            break;
        default :
            printf("default \n");
            break;
        }
    }
    char symbol = binary[0];
    char index[9] = {0};
    char effectiveNumber[24] = {0};
    memcpy(index,binary+1,8);
    memcpy(effectiveNumber,binary+9,23);
//	printf("symbol = %c,%s,%d\n",symbol,__FILE__,__LINE__);
//	printf("index = %s,%s,%d\n",index,__FILE__,__LINE__);
//	printf("effectiveNumber = %s,%s,%d\n",effectiveNumber,__FILE__,__LINE__);
    float indexnum = 0.0,smallNumVal = 0.0,decnum = 0.0;
    indexnum = BinarytoInt(index,8);
    int numofmove = indexnum - 127;
    if (numofmove > 0)
    {
    //	printf("(numofmove) = %d\n", (numofmove));
        char * dec = (char *) malloc(((numofmove) + 2) * sizeof(char));
        memset(dec, 0, ((numofmove) + 2));
        sprintf(dec, "%c", '1');
        memcpy(dec + 1, effectiveNumber, (numofmove));
        decnum = BinarytoInt(dec, (numofmove) + 1);
        char* smallNum = (char *) malloc(sizeof(char) * ((23 - (numofmove)) + 1));
        memset(smallNum, 0, ((23 - (numofmove)) + 1));
        sprintf(smallNum, "%s", effectiveNumber + (numofmove));
        smallNumVal = BinarytoSmallNumber(smallNum, (23 - numofmove));
        free(dec);
        dec = NULL;
        free(smallNum);
        smallNum = NULL;
    }
    else if (0 == numofmove)
    {
        smallNumVal = BinarytoSmallNumber(effectiveNumber, (23 - numofmove));
        decnum = 1;
    }
    else
    {
        //char* smallNum = (char *)malloc(sizeof(char) * ((23 \A3\AB\A1\A1(numofmove)) +1) );
        char* smallNum = (char*) malloc(sizeof(char) * (23 - numofmove + 1));
        memset(smallNum, 0, ((23 - (numofmove)) + 1));
        sprintf((smallNum - numofmove - 1), "%s", "1");
        //smallNUm[(fabs(numofmove) - 1)] = '1';
        sprintf((smallNum - numofmove), "%s", effectiveNumber);
    //	printf("smallNum = %s\n", smallNum);
        smallNumVal = BinarytoSmallNumber(smallNum, (23 - numofmove));
        decnum = 0;
        free(smallNum);
        smallNum = NULL;
    }
    returnData = decnum + smallNumVal;
    if (symbol == '1')
    {
        returnData = -returnData;
    }
   return returnData;
}

//将字符串中的16进制数转化为10进制数
unsigned int StrTo10(char * str)
{
	unsigned int value;
	char * temp = str;
	if (NULL == temp)
	{
		return 0;
	}
	value = 0;
	while (1)
	{
		if ((*temp >= '0') && (*temp <= '9'))
		{
			value = value*16 + (*temp - '0');
		}
		else if ((*temp >= 'A') && (*temp <= 'F'))
		{
			value = value*16 + (*temp - 'A') + 10;
		}
		else if ((*temp >= 'a') && (*temp <= 'f'))
		{
			value = value*16 + (*temp - 'a') + 10;
		}
		else
		{
			break;
		}
		temp++;
	}
	return value;
}
//test
//M#6000#1#
int parseData(char *buf, int size, DATA_FORMAT *data, int *counts)
{
    if (NULL == buf || size <= 0 || NULL == data)
    {
        return -1;
    }
    char * tmp = buf;
    char value[128];
    int i = 0;
    int count = 0;
    int length = 0;
    while (NULL != tmp && *tmp != '\0')
    {
        value[length] = *tmp;
        if ('#' == *tmp++)
        {
            i++;
            value[length] = '\0';
            if (1 == i)
            {
                memcpy((data + count)->content, value, DATA_TYPE_LENGTH);
            }
            else if (2 == i)
            {
                (data + count)->startPosition = atoi(value);
            }
            else if (3 == i)
            {
                (data + count)->data.iData = atoi(value);
            }
            (data + count)->type = DATA_TYPE_bool;
            length = 0;
        }
        else
        {
            length++;
        }

        if (';' == *tmp)
        {
           count++;
           tmp++;
           length = 0;
           i = 0;
        }
    }

    *counts = count + 1;
}

