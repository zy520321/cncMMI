#ifndef HELP_H
#define HELP_H

enum TEXT_DATA_TYPE{XML, CS_R, CS_W, CS_LOCAL_R, CS_LOCAL_W};//client server

typedef bool (* CallBackGetData)(char * objectName, TEXT_DATA_TYPE type, void * pVoid, char * buf, int size);


#endif // HELP_H
