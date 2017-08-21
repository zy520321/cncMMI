#ifndef SYSTEMDATAMANAGER_H
#define SYSTEMDATAMANAGER_H

#include <QObject>

#define XMAX_NUM 1024
#define YMAX_NUM 1024
#define AIMAX_NUM 64
#define AOMAX_NUM 64
#define MMAX_NUM 2048
#define DMAX_NUM 512
#define IMAX_NUM 4096
#define PMAX_NUM 4096

#define X_SIGNAL 0
#define AI_DATA  1
#define Y_SIGNAL 2
#define AO_DATA  3
#define M_SIGNAL 4
#define D_PARA   5
#define I_PARA   6
#define P_PARA   7

#define TheSysData()    SystemData::SysDataMag::GetSysData()

namespace SystemData
{
    class Pimpl;
    class SysDataMag : public QObject
    {
        Q_OBJECT
    private:
        explicit SysDataMag(QObject *parent = 0);
    public:
        ~SysDataMag();
        static SysDataMag* GetSysData();
        void InitData();

    public:
        bool GetXSignal(unsigned int no);
        bool GetYSignal(unsigned int no);
        bool GetMSignal(unsigned int no);
        unsigned char GetMSignalByte(unsigned int no);
        unsigned short GetMSignal2Byte(unsigned int no);
        unsigned int GetMSignalWord(unsigned int no);
        bool GetBitMSignalByte(unsigned int no,unsigned int bit);
        bool GetBitMSignal2Byte(unsigned int no,unsigned int bit);
        bool GetBitMSignalWord(unsigned int no,unsigned int bit);

        unsigned int GetAIData(unsigned int no);
        unsigned int GetAOData(unsigned int no);
        int GetDData(unsigned int no);
        unsigned int GetDDataU(unsigned int no);
        float GetDDataF(unsigned int no);
        unsigned int GetIData(unsigned int no);
        unsigned int* GetIDataAddr(unsigned int no);
        int GetIDataI(unsigned int no);
        int* GetIDataIAddr(unsigned int no);
        float GetIDataF(unsigned int no);
        float* GetIDataFAddr(unsigned int no);

        unsigned int GetPData(unsigned int no);

        void SetXSignal(unsigned int no,unsigned char value);
        void SetYSignal(unsigned int no,unsigned char value);
        void SetMSignal(unsigned int no,unsigned char value);
        void SetMSignalByte(unsigned int no,unsigned char value);
        void SetBitMSignalByte(unsigned int no,unsigned char bit);
        void ClearBitMSignalByte(unsigned int no,unsigned char bit);
        void SetMSignal2Byte(unsigned int no,unsigned short value);
        void SetBitMSignal2Byte(unsigned int no,unsigned short bit);
        void SetBitMSignal2Byte(unsigned int no,unsigned short bit,bool value);
        void ClearBitMSignal2Byte(unsigned int no,unsigned short bit);
        void SetMSignalWord(unsigned int no,unsigned int value);
        void SetBitMSignalWord(unsigned int no,unsigned int bit);
        void ClearBitMSignalWord(unsigned int no,unsigned int bit);

        void SetAIData(unsigned int no,unsigned int value);
        void SetAOData(unsigned int no,unsigned int value);
        void SetDData(unsigned int no,int value);
        void SetDDataU(unsigned int no,unsigned int value);
        void SetDDataF(unsigned int no,float value);
        void SetIData(unsigned int no,unsigned int value);
        void SetIDataI(unsigned int no,int value);
        void SetIDataF(unsigned int no,float value);
        void SetPData(unsigned int no,unsigned int value);
        void SetPData(unsigned int no,float value);

        void GetData(unsigned int type, unsigned int no, void *targeAddr);
        void GetData(int num, unsigned int *type, unsigned int *no, void **targeAddr);
        void SetData(int num, unsigned int *type, unsigned int *no, void **value);
        void SetData(unsigned int type, unsigned int no, void *value);

        //为指定轴设置螺距补偿表
        void SetAxisPtcp(unsigned int axisNo, float startPos, float endPos, unsigned int num,float *value);

        void GetAxisPtcp(unsigned int axisNo, float **valueAddr, float* startPos=NULL, float* endPos=NULL, unsigned int* num=NULL);

    signals:

    public slots:

    private:
        Pimpl *data;
    };
};


#endif // SYSTEMDATAMANAGER_H
