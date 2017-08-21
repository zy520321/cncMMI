#include "systemdatamanager.h"
#include <vector>
#include "DefSysSignalAndData.h"

namespace SystemData
{
    const unsigned char SigBit[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
    const unsigned char SigReBit[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};

    const unsigned short Sig16Bit[16]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
                                      0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};
    const unsigned short SigRe16Bit[16]={0xFFFE,0xFFFD,0xFFFB,0xFFF7,0xFFEF,0xFFDF,0xFFBF,0xFF7F,
                                        0xFEFF,0xFDFF,0xFBFF,0xF7FF,0xEFFF,0xDFFF,0xBFFF,0x7FFF};

    const unsigned int WordBit[32]={0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,0x00000040,0x00000080,
                                   0x00000100,0x00000200,0x00000400,0x00000800,0x00001000,0x00002000,0x00004000,0x00008000,
                                   0x00010000,0x00020000,0x00040000,0x00080000,0x00100000,0x00200000,0x00400000,0x00800000,
                                   0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000};
    const unsigned int WordReBit[32]={0xFFFFFFFE,0xFFFFFFFD,0xFFFFFFFB,0xFFFFFFF7,0xFFFFFFEF,0xFFFFFFDF,0xFFFFFFBF,0xFFFFFF7F,
                                     0xFFFFFEFF,0xFFFFFDFF,0xFFFFFBFF,0xFFFFF7FF,0xFFFFEFFF,0xFFFFDFFF,0xFFFFBFFF,0xFFFF7FFF,
                                     0xFFFEFFFF,0xFFFDFFFF,0xFFFBFFFF,0xFFF7FFFF,0xFFEFFFFF,0xFFDFFFFF,0xFFBFFFFF,0xFF7FFFFF,
                                     0xFEFFFFFF,0xFDFFFFFF,0xFBFFFFFF,0xF7FFFFFF,0xEFFFFFFF,0xDFFFFFFF,0xBFFFFFFF,0x7FFFFFFF};

    struct Sig
    {
    public:
        Sig()
        {
            vByte=0;
        };
        unsigned char vByte;

        inline unsigned char GetByte(){return vByte;};
        inline void SetByte(unsigned char vSet){vByte=vSet;};

        inline bool GetBit(unsigned int iBit){return vByte&SigBit[iBit];};
        inline void ClearBit(unsigned int iBit){vByte=vByte&SigReBit[iBit];};
        inline void SetBit(unsigned int iBit){vByte=vByte|SigBit[iBit];};

        Sig& operator=(Sig& x)
        {
            this->vByte = x.vByte;
            return *this;
        }
        Sig& operator=(unsigned char x)
        {
            vByte = x;
            return *this;
        }
    };

    struct Data
    {
        union Format
        {
            unsigned int dUnInt;
            int dInt;
            float dFloat;
        };
    public:
        Data()
        {
            value.dUnInt=0;
        };

        Format value;

        inline void GetWord(unsigned int *target){if(NULL==target) return; *target=value.dUnInt;};
        inline void GetWord(int *target){if(NULL==target) return; *target=value.dInt;};
        inline void GetWord(float *target){if(NULL==target) return; *target=value.dFloat;};
        inline float GetWordF(){return value.dFloat;};
        inline unsigned int GetWordU(){return value.dUnInt;};
        inline int GetWordInt(){return value.dInt;};
        inline float* GetWordFAddr(){return &value.dFloat;};
        inline unsigned int* GetWordIAddr(){return &value.dUnInt;};
        inline int* GetWordIntAddr(){return &value.dInt;};

        inline void SetWord(unsigned int  vSet){value.dUnInt=vSet;};
        inline void SetWord(int vSet){value.dInt=vSet;};
        inline void SetWord(float vSet){value.dFloat=vSet;};

        Data& operator=(Data& x)
        {
            this->value.dUnInt = x.value.dUnInt;
            return *this;
        }
        Data& operator=(unsigned int x)
        {
            value.dUnInt = x;
            return *this;
        }
    };

    class Pimpl
    {
    public:
        Pimpl(){};
        ~Pimpl();
        void Init();

    public:
        Sig XSignal[XMAX_NUM/8];
        Data AIData[AIMAX_NUM];
        Sig YSignal[YMAX_NUM/8];
        Data AOData[AOMAX_NUM];
        Sig MSignal[MMAX_NUM/8];
        Data DPara[DMAX_NUM];
        Data IPara[IMAX_NUM];
        Data PPara[PMAX_NUM];
        float* AxisPtcp[AXIS_MAX];
        int AxisPtcpVarNum[AXIS_MAX];
    };
    Pimpl::~Pimpl()
    {
        for(int i=0; i<AXIS_MAX; i++)
        {
            if(NULL!=AxisPtcp[i])
                delete AxisPtcp[i];
        }
    }
    void Pimpl::Init()
    {
        for(int i=0; i<XMAX_NUM/8; i++)
            XSignal[i]=0;
        for(int i=0; i<AIMAX_NUM; i++)
            AIData[i]=0;
        for(int i=0; i<YMAX_NUM/8; i++)
            YSignal[i]=0;
        for(int i=0; i<AOMAX_NUM; i++)
            AOData[i]=0;
        for(int i=0; i<MMAX_NUM/8; i++)
            MSignal[i]=0;
        for(int i=0; i<DMAX_NUM; i++)
            DPara[i]=0;
        for(int i=0; i<IMAX_NUM; i++)
            IPara[i]=0;
        for(int i=0; i<PMAX_NUM; i++)
            PPara[i]=0;
        for(int i=0; i<AXIS_MAX; i++)
        {
            AxisPtcp[i]=NULL;
            AxisPtcpVarNum[i]=0;
        }
    }

    SysDataMag* SysDataMag::GetSysData()
    {
        static SysDataMag * theSysData=NULL;

        if(NULL==theSysData)
        {
            theSysData=new SysDataMag();
        }
        return theSysData;
    }
    SysDataMag::SysDataMag(QObject *parent) :
        QObject(parent)
    {
        data= new Pimpl();
    }
    SysDataMag::~SysDataMag()
    {
        delete data;
    }
    void SysDataMag::InitData()
    {
        data->Init();
    }

    void SysDataMag::SetAxisPtcp(unsigned int axisNo, float startPos, float endPos, unsigned int num,float *value)
    {
        if(num<1||axisNo>*ReadI_NUM_MOTOR||axisNo<1)
            return;
        unsigned int realAxis=axisNo-1;
        if(NULL!=data->AxisPtcp[realAxis])
        {
            delete data->AxisPtcp[realAxis];
        }
        data->AxisPtcpVarNum[realAxis]=num;
        data->AxisPtcp[realAxis] = new float[num];

        for(unsigned int i=0; i<num; i++)
        {
            data->AxisPtcp[realAxis][i]=value[i];
        }

        I_START_PTCP_MOTOR(realAxis,startPos);                //pitch compensation start pos (螺距补偿起点)
        I_END_PTCP_MOTOR(realAxis,endPos);                    //pitch compensation end pos (螺距补偿终点)
        I_DIS_PTCP_MOTOR(realAxis,(endPos-startPos)/num);     //pitch compensation distance (螺距补偿间隔)
    }
    void SysDataMag::GetAxisPtcp(unsigned int axisNo,float **valueAddr, float* startPos, float* endPos, unsigned int* num)
    {
        if(*num<1||axisNo>*ReadI_NUM_MOTOR||1>axisNo||data->AxisPtcp[axisNo-1])
            return;
        unsigned int realAxis=axisNo-1;
        *valueAddr=data->AxisPtcp[realAxis];

        float spos=*ReadI_START_PTCP_MOTOR(realAxis);                //pitch compensation start pos (螺距补偿起点)
        if(NULL!=startPos)
            *startPos=spos;
        float epos=*ReadI_END_PTCP_MOTOR(realAxis);                    //pitch compensation end pos (螺距补偿终点)
        if(NULL!=endPos)
            *endPos=epos;
        if(NULL!=num)
            *num=(spos-epos)/(*ReadI_DIS_PTCP_MOTOR(realAxis));     //pitch compensation distance (螺距补偿间隔)
    }

    void SysDataMag::GetData(int num, unsigned int *type, unsigned int *no, void **targeAddr)
    {
        for(int i=0; i<num; i++)
        {
            GetData(type[i],no[i],targeAddr[i]);
        }
    }
    void SysDataMag::SetData(int num, unsigned int *type, unsigned int *no, void **value)
    {
        for(int i=0; i<num; i++)
        {
            SetData(type[i],no[i],value[i]);
        }
    }

    void SysDataMag::GetData(unsigned int type, unsigned int no, void *targeAddr)
    {
        if(NULL==targeAddr)
            return;

        unsigned char *setBitAddr=(unsigned char *)targeAddr;
        unsigned int *setIntAddr=(unsigned int *)targeAddr;
        switch(type)
        {
        case X_SIGNAL:
            if(no>=XMAX_NUM)
                return;
            data->XSignal[no/8].GetBit(no%8) ? setBitAddr[0]=1 : setBitAddr[0]=0;
            break;
        case AI_DATA:
            if(no>=AIMAX_NUM)
                return;
            data->AIData[no].GetWord(setIntAddr);
            break;
        case Y_SIGNAL:
            if(no>=YMAX_NUM)
                return;
            data->YSignal[no/8].GetBit(no%8) ? setBitAddr[0]=1 : setBitAddr[0]=0;
            break;
        case AO_DATA:
            if(no>=AOMAX_NUM)
                return;
            data->AOData[no].GetWord(setIntAddr);
            break;
        case M_SIGNAL:
            if(no>=MMAX_NUM)
                return;
            data->MSignal[no/8].GetBit(no%8) ? setBitAddr[0]=1 : setBitAddr[0]=0;
            break;
        case D_PARA:
            if(no>=DMAX_NUM)
                return;
            data->DPara[no].GetWord(setIntAddr);
            break;
        case I_PARA:
            if(no>=IMAX_NUM)
                return;
            data->IPara[no].GetWord(setIntAddr);
            break;
        case P_PARA:
            if(no>=PMAX_NUM)
                return;
            data->PPara[no].GetWord(setIntAddr);
            break;
        default:
            break;
        }
    }

    void SysDataMag::SetData(unsigned int type, unsigned int no, void *value)
    {
        if(NULL==value)
            return;

        unsigned char *setBitAddr=(unsigned char *)value;
        unsigned int *setIntAddr=(unsigned int *)value;
        switch(type)
        {
        case X_SIGNAL:
            if(no>=XMAX_NUM)
                return;
            setBitAddr[0] ? data->XSignal[no/8].SetBit(no%8) : data->XSignal[no/8].ClearBit(no%8);
            break;
        case AI_DATA:
            if(no>=AIMAX_NUM)
                return;
            data->AIData[no].SetWord(setIntAddr[0]);
            break;
        case Y_SIGNAL:
            if(no>=YMAX_NUM)
                return;
            setBitAddr[0] ? data->YSignal[no/8].SetBit(no%8) : data->YSignal[no/8].ClearBit(no%8);
            break;
        case AO_DATA:
            if(no>=AOMAX_NUM)
                return;
            data->AOData[no].SetWord(setIntAddr[0]);
            break;
        case M_SIGNAL:
            if(no>=8*MMAX_NUM)
                return;
            setBitAddr[0] ? data->MSignal[no/8].SetBit(no%8) : data->MSignal[no/8].ClearBit(no%8);
            break;
        case D_PARA:
            if(no>=DMAX_NUM)
                return;
            data->DPara[no].SetWord(setIntAddr[0]);
            break;
        case I_PARA:
            if(no>=IMAX_NUM)
                return;
            data->IPara[no].SetWord(setIntAddr[0]);
            break;
        case P_PARA:
            if(no>=PMAX_NUM)
                return;
            data->PPara[no].SetWord(setIntAddr[0]);
            break;
        default:
            break;
        }
    }
    bool SysDataMag::GetXSignal(unsigned int no)
    {
        if(no>=XMAX_NUM)
            return false;
        return data->XSignal[no/8].GetBit(no%8);
    }
    bool SysDataMag::GetYSignal(unsigned int no)
    {
        if(no>=YMAX_NUM)
            return false;
        return data->YSignal[no/8].GetBit(no%8);
    }
    bool SysDataMag::GetMSignal(unsigned int no)
    {
        if(no>=MMAX_NUM)
            return false;
        return data->MSignal[no/8].GetBit(no%8);
    }
    unsigned char SysDataMag::GetMSignalByte(unsigned int no)
    {
        if(no>=MMAX_NUM)
            return 0;
        return data->MSignal[no/8].GetByte();
    }
    bool SysDataMag::GetBitMSignalByte(unsigned int no,unsigned int bit)
    {
        if(no>=MMAX_NUM)
            return 0;
        return data->MSignal[no/8].GetByte()&SigBit[bit];
    }
    unsigned short SysDataMag::GetMSignal2Byte(unsigned int no)
    {
        if(no>=MMAX_NUM)
            return 0;
        unsigned short value;
        value=data->MSignal[no/8+1].GetByte()<<8;
        value+=data->MSignal[no/8].GetByte();
        return value;
    }
    bool SysDataMag::GetBitMSignal2Byte(unsigned int no,unsigned int bit)
    {
        if(no>=MMAX_NUM)
            return 0;
        unsigned short value;
        value=data->MSignal[no/8+1].GetByte()<<8;
        value+=data->MSignal[no/8].GetByte();
        return value&Sig16Bit[bit];
    }
    unsigned int  SysDataMag::GetMSignalWord(unsigned int no)
    {
        if(no>=MMAX_NUM)
            return 0;
        unsigned int value;
        value=data->MSignal[no/8+3].GetByte()<<24;
        value+=data->MSignal[no/8+2].GetByte()<<16;
        value+=data->MSignal[no/8+1].GetByte()<<8;
        value+=data->MSignal[no/8].GetByte();
        return value;
    }
    bool SysDataMag::GetBitMSignalWord(unsigned int no,unsigned int bit)
    {
        if(no>=MMAX_NUM)
            return 0;
        unsigned int value;
        value=data->MSignal[no/8+3].GetByte()<<24;
        value+=data->MSignal[no/8+2].GetByte()<<16;
        value+=data->MSignal[no/8+1].GetByte()<<8;
        value+=data->MSignal[no/8].GetByte();
        return value&WordBit[bit];
    }

    unsigned int  SysDataMag::GetAIData(unsigned int no)
    {
        if(no>=AIMAX_NUM)
            return 0;
        return data->AIData[no].GetWordU();
    }
    unsigned int  SysDataMag::GetAOData(unsigned int no)
    {
        if(no>=AOMAX_NUM)
            return 0;
        return data->AOData[no].GetWordU();
    }
    int  SysDataMag::GetDData(unsigned int no)
    {
        if(no>=DMAX_NUM)
            return 0;
        return data->DPara[no].GetWordInt();
    }
    unsigned int  SysDataMag::GetDDataU(unsigned int no)
    {
        if(no>=DMAX_NUM)
            return 0;
        return data->DPara[no].GetWordU();
    }
    float  SysDataMag::GetDDataF(unsigned int no)
    {
        if(no>=DMAX_NUM)
            return 0;
        return data->DPara[no].GetWordF();
    }
    unsigned int  SysDataMag::GetIData(unsigned int no)
    {
        if(no>=IMAX_NUM)
            return 0;
        return data->IPara[no].GetWordU();
    }
    unsigned int*  SysDataMag::GetIDataAddr(unsigned int no)
    {
        if(no>=IMAX_NUM)
            return 0;
        return data->IPara[no].GetWordIAddr();
    }
    int  SysDataMag::GetIDataI(unsigned int no)
    {
        if(no>=IMAX_NUM)
            return 0;
        return data->IPara[no].GetWordU();
    }
    int*  SysDataMag::GetIDataIAddr(unsigned int no)
    {
        if(no>=IMAX_NUM)
            return 0;
        return data->IPara[no].GetWordIntAddr();
    }
    float  SysDataMag::GetIDataF(unsigned int no)
    {
        if(no>=IMAX_NUM)
            return 0;
        return data->IPara[no].GetWordF();
    }
    float*  SysDataMag::GetIDataFAddr(unsigned int no)
    {
        if(no>=IMAX_NUM)
            return 0;
        return data->IPara[no].GetWordFAddr();
    }

    unsigned int  SysDataMag::GetPData(unsigned int no)
    {
        if(no>=PMAX_NUM)
            return 0;
        return data->PPara[no].GetWordU();
    }

    void SysDataMag::SetXSignal(unsigned int no,unsigned char value)
    {
        if(no>=XMAX_NUM)
            return;
        value ? data->XSignal[no/8].SetBit(no%8) : data->XSignal[no/8].ClearBit(no%8);
    }
    void SysDataMag::SetYSignal(unsigned int no,unsigned char value)
    {
        if(no>=YMAX_NUM)
            return;
        value ? data->YSignal[no/8].SetBit(no%8) : data->YSignal[no/8].ClearBit(no%8);
    }
    void SysDataMag::SetMSignalByte(unsigned int no,unsigned char value)
    {
        if(no>=MMAX_NUM)
            return;
        data->MSignal[no/8].SetByte(value);
    }
    void SysDataMag::SetBitMSignalByte(unsigned int no,unsigned char bit)
    {
        if(no>=MMAX_NUM)
            return;
        unsigned char valueSet=data->MSignal[no/8].GetByte()|SigBit[bit];
        data->MSignal[no/8].SetByte(valueSet);
    }
    void SysDataMag::ClearBitMSignalByte(unsigned int no,unsigned char bit)
    {
        if(no>=MMAX_NUM)
            return;
        unsigned char valueSet=data->MSignal[no/8].GetByte()&SigReBit[bit];
        data->MSignal[no/8].SetByte(valueSet);
    }
    void SysDataMag::SetMSignal2Byte(unsigned int no,unsigned short value)
    {
        if(no>=MMAX_NUM-15)
            return;
        data->MSignal[no/8].SetByte(value&0xFF);
        data->MSignal[no/8+1].SetByte((value&0xFF00)>>8);
    }
    void SysDataMag::SetBitMSignal2Byte(unsigned int no,unsigned short bit)
    {
        if(no>=MMAX_NUM-15)
            return;
        unsigned short valueSet=(data->MSignal[no/8+1].GetByte()<<8)+data->MSignal[no/8].GetByte();
        valueSet|=Sig16Bit[bit];

        data->MSignal[no/8].SetByte(valueSet&0xFF);
        data->MSignal[no/8+1].SetByte((valueSet&0xFF00)>>8);
    }
    void SysDataMag::SetBitMSignal2Byte(unsigned int no,unsigned short bit,bool value)
    {
        if(no>=MMAX_NUM-15)
            return;
        unsigned short valueSet=(data->MSignal[no/8+1].GetByte()<<8)+data->MSignal[no/8].GetByte();
        if(value)
            valueSet|=Sig16Bit[bit];
        else
            valueSet&=SigRe16Bit[bit];

        data->MSignal[no/8].SetByte(valueSet&0xFF);
        data->MSignal[no/8+1].SetByte((valueSet&0xFF00)>>8);
    }
    void SysDataMag::ClearBitMSignal2Byte(unsigned int no,unsigned short bit)
    {
        if(no>=MMAX_NUM-15)
            return;
        unsigned short valueSet=(data->MSignal[no/8+1].GetByte()<<8)+data->MSignal[no/8].GetByte();
        valueSet&=SigRe16Bit[bit];

        data->MSignal[no/8].SetByte(valueSet&0xFF);
        data->MSignal[no/8+1].SetByte((valueSet&0xFF00)>>8);
    }
    void SysDataMag::SetMSignalWord(unsigned int no,unsigned int value)
    {
        if(no>=MMAX_NUM-31)
            return;
        data->MSignal[no/8].SetByte(value&0xFF);
        data->MSignal[no/8+1].SetByte((value&0xFF00)>>8);
        data->MSignal[no/8+2].SetByte((value&0xFF0000)>>16);
        data->MSignal[no/8+3].SetByte((value&0xFF000000)>>24);
    }
    void SysDataMag::SetBitMSignalWord(unsigned int no,unsigned int bit)
    {
        if(no>=MMAX_NUM-31)
            return;
        unsigned int valueSet=(data->MSignal[no/8+3].GetByte()<<24)+(data->MSignal[no/8+2].GetByte()<<16)+(data->MSignal[no/8+1].GetByte()<<8)
                +data->MSignal[no/8].GetByte();
        valueSet|=WordBit[bit];

        data->MSignal[no/8].SetByte(valueSet&0xFF);
        data->MSignal[no/8+1].SetByte((valueSet&0xFF00)>>8);
        data->MSignal[no/8+2].SetByte((valueSet&0xFF0000)>>16);
        data->MSignal[no/8+3].SetByte((valueSet&0xFF000000)>>24);
    }
    void SysDataMag::ClearBitMSignalWord(unsigned int no,unsigned int bit)
    {
        if(no>=MMAX_NUM-31)
            return;
        unsigned int valueSet=(data->MSignal[no/8+3].GetByte()<<24)+(data->MSignal[no/8+2].GetByte()<<16)+(data->MSignal[no/8+1].GetByte()<<8)
                +data->MSignal[no/8].GetByte();
        valueSet&=WordReBit[bit];

        data->MSignal[no/8].SetByte(valueSet&0xFF);
        data->MSignal[no/8+1].SetByte((valueSet&0xFF00)>>8);
        data->MSignal[no/8+2].SetByte((valueSet&0xFF0000)>>16);
        data->MSignal[no/8+3].SetByte((valueSet&0xFF000000)>>24);
    }
    void SysDataMag::SetMSignal(unsigned int no,unsigned char value)
    {
        if(no>=8*MMAX_NUM)
            return;
        value ? data->MSignal[no/8].SetBit(no%8) : data->MSignal[no/8].ClearBit(no%8);
    }
    void SysDataMag::SetAIData(unsigned int no,unsigned int value)
    {
        if(no>=AIMAX_NUM)
            return;
        data->AIData[no].SetWord(value);
    }
    void SysDataMag::SetAOData(unsigned int no,unsigned int value)
    {
        if(no>=AOMAX_NUM)
            return;
        data->AOData[no].SetWord(value);
    }
    void SysDataMag::SetDData(unsigned int no,int value)
    {
        if(no>=DMAX_NUM)
            return;
        data->DPara[no].SetWord(value);
    }
    void SysDataMag::SetDDataU(unsigned int no,unsigned int value)
    {
        if(no>=DMAX_NUM)
            return;
        data->DPara[no].SetWord(value);
    }
    void SysDataMag::SetDDataF(unsigned int no,float value)
    {
        if(no>=DMAX_NUM)
            return;
        data->DPara[no].SetWord(value);
    }
    void SysDataMag::SetIData(unsigned int no,unsigned int value)
    {
        if(no>=IMAX_NUM)
            return;
        data->IPara[no].SetWord(value);
    }
    void SysDataMag::SetIDataI(unsigned int no,int value)
    {
        if(no>=IMAX_NUM)
            return;
        data->IPara[no].SetWord(value);
    }
    void SysDataMag::SetIDataF(unsigned int no,float value)
    {
        if(no>=IMAX_NUM)
            return;
        data->IPara[no].SetWord(value);
    }
    void SysDataMag::SetPData(unsigned int no,unsigned int value)
    {
        if(no>=PMAX_NUM)
            return;
        data->PPara[no].SetWord(value);
    }
    void SysDataMag::SetPData(unsigned int no,float value)
    {
        if(no>=PMAX_NUM)
            return;
        data->PPara[no].SetWord(value);
    }
}
