#ifndef HELP_H
#define HELP_H

#ifndef GET_TEXT
#define GET_TEXT
enum TEXT_DATA_TYPE{XML, CS_R, CS_W, CS_LOCAL};//client server
typedef bool (* CallBackGetData)(char * objectName, TEXT_DATA_TYPE type, void * pVoid, char * buf, int size);
#endif

#endif // HELP_H
