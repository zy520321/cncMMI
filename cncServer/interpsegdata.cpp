#include "interpsegdata.h"
#include "DefSysSignalAndData.h"
#include <memory.h>
#include <vector>
#include <utility>

bool _canInteractive=false;
int _interpSegBufFillNo;
int _interpSegBufGetNo;
int _interpSegBufRealBufNum;
int _interpSegBufGetBufNum;
const int _interpSegBufCapacity=1024;

InterpSegData _intepSegBuf[_interpSegBufCapacity];

void InitSegData(InterpSegData& seg)
{
    seg.group_id=0;   //目前只有一个通道

    seg.G_ABS=*ReadI_ABS_MODAL_ITP(seg.group_id); //90/91
    seg.G_MOTION=*ReadI_MOTION_MODAL_ITP(seg.group_id);  //0/1 ,2, 3, 12, 6
    seg.G_MOTION_0=0; //0/4
    seg.G_CHAMFERING_ROUNDED=*ReadI_CHAMFERING_ROUNDED_MODAL_ITP(seg.group_id); //34/33,35
    seg.G_HOME_RETURN=0; //0/28
    seg.G_PRECISE_STOP=0;//0/9
    seg.G_CORNER=0;  //0/61, 62, 64, 164
    seg.G_CORNER_LOOP=*ReadI_CORNER_LOOP_MODAL_ITP(seg.group_id); //174/173
    seg.G_PREVIEW_STOP=0;//0/31
    seg.G_GAS_PRESSURE=0; //0/88
    seg.G_GAP=0; //0/87
    seg.G_POWER_RAMP=0; //0/183/181
    seg.G_GAS_RAMP=0; //0/189/188
    seg.G_LASER=0;//0/82
    seg.M_CODE=-1; //-1(invalid) or >-1
    seg.N_CODE=-1;
}
int ParseNcSeg(QString& ori_str, InterpSegData& curSeg)
{
    int alarm_code=-1;
    InitSegData(curSeg);
    QString qstr=ori_str.toUpper();
    int size=qstr.size();

    int character=0,lastCha=0;

//词法分析
  //排除不支持的字符
    int temp=qstr.indexOf("//"); //去掉注释
    if(temp>-1)
        size=temp;

    int availableNum=0;
    bool letterSign[26];
    memset(letterSign,false,sizeof(letterSign));

    for(int i=0; i<size; i++)
    {
        char cur_c=qstr.at(i).toLatin1();
        if(cur_c>='A'&&cur_c<='Z')
        {
            if(letterSign[cur_c-'A']&&cur_c!='G')
            {//除了G以外不能重复出现
                alarm_code=2;
            }
            else
            {
                character=1;
                letterSign[cur_c-'A']=true;
            }
        }
        else if(cur_c=='.')
        {
            character=2;
        }
        else if(cur_c>='0'&&cur_c<='9')
        {
            character=3;
        }
        else if(cur_c=='#')
        {
            character=4;
        }
        else if(cur_c=='-')
        {
            character=4;
        }
        else if(cur_c==' ')
        {
            character=5;
        }
        else
        {
            if(!(cur_c==';'||cur_c=='\r'||cur_c=='\n'))
                alarm_code=2;
        }
        if(character==lastCha)
        {//不能重叠
            if(lastCha!=3&&lastCha!=5)
                alarm_code=2;
            else if(lastCha==5)
            {//去掉多余的空格
               qstr.remove(i,1);
               size--;
               i--;
            }
        }
        if(alarm_code==2)
            return alarm_code;
        if(character<5)
            availableNum++;

        lastCha=character;
    }
    if(availableNum<2)//无效的字符串
        return -1;

    int index,indexBlank=-1;
    std::vector<int> gCodeAll;
    QString getCeil;

    while((index=qstr.indexOf("G",indexBlank+1))>-1)
    {
        indexBlank=qstr.indexOf(" ",index+1);
        if(indexBlank==-1)
            indexBlank=size-1;
        getCeil=qstr.mid(index+1,indexBlank-index);
        if(getCeil.size()>0)
        {
            int Gcode=getCeil.toInt();
            gCodeAll.push_back(Gcode);
        }
        if(indexBlank==size-1)
            break;
    }
    QString checkLetter[13]={"X","Y","Z","F","C","R","I","J","K","P","Q","#C","#R"};
    typedef std::pair<bool*,double*> SData;
    unsigned char flagCounter[13];
    SData searchAll[13]={SData(&curSeg.X_Flag,&curSeg.X_Value),SData(&curSeg.Y_Flag,&curSeg.Y_Value),SData(&curSeg.Z_Flag,&curSeg.Z_Value),SData(&curSeg.F_Flag,&curSeg.F_Value)
                                 ,SData(&curSeg.C_Flag,&curSeg.C_Value),SData(&curSeg.R_Flag,&curSeg.R_Value),SData(&curSeg.I_Flag,&curSeg.I_Value)
                                 ,SData(&curSeg.J_Flag,&curSeg.J_Value),SData(&curSeg.K_Flag,&curSeg.K_Value)
                                 ,SData(&curSeg.P_Flag,&curSeg.P_Value),SData(&curSeg.Q_Flag,&curSeg.Q_Value)
                                 ,SData(&curSeg.C_gcr_Flag,&curSeg.C_gcr_Value),SData(&curSeg.R_gcr_Flag,&curSeg.R_gcr_Value)};

    for(int i=0; i<13; i++)
    {
        flagCounter[i]=0;
        if((index=qstr.indexOf(checkLetter[i]))>-1)
        {
            if(i==11||i==12)//"#C""#R"
                indexBlank=qstr.indexOf(" ",index+2);
            else
                indexBlank=qstr.indexOf(" ",index+1);

            if(indexBlank==-1)
                indexBlank=size-1;
            getCeil=qstr.mid(index+1,indexBlank-index);
            if(getCeil.size()>0)
            {
                flagCounter[i]=1;
                *searchAll[i].first=true;
                *searchAll[i].second=getCeil.toDouble();
            }
        }
    }

    if((index=qstr.indexOf("N"))>-1)
    {
        indexBlank=qstr.indexOf(" ",index+1);
        if(indexBlank==-1)
            indexBlank=size-1;
        getCeil=qstr.mid(index+1,indexBlank-index);
        if(getCeil.size()>0)
        {
            curSeg.N_CODE=getCeil.toInt();
        }
    }

    if((index=qstr.indexOf("O"))>-1)
    {
        indexBlank=qstr.indexOf(" ",index+1);
        if(indexBlank==-1)
            indexBlank=size-1;
        getCeil=qstr.mid(index+1,indexBlank-index);
        if(getCeil.size()>0)
        {
            curSeg.O_CODE=getCeil.toInt();
        }
    }

    if((index=qstr.indexOf("M"))>-1)
    {
        indexBlank=qstr.indexOf(" ",index+1);
        if(indexBlank==-1)
            indexBlank=size-1;
        getCeil=qstr.mid(index+1,indexBlank-index);
        if(getCeil.size()>0)
        {
            curSeg.M_CODE=getCeil.toInt();
        }
    }
//语法分析
    //排除不支持的GOCDE
    for(unsigned i=0; i<gCodeAll.size(); i++)
    {
        int curGcode=gCodeAll.at(i);
        bool g00=false,g90=false,g34=false,g174=false;
        switch (curGcode)
        {
            case G00:
                if(g00)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_MOTION=curGcode;
                g00=true;
                if(flagCounter[0])
                    flagCounter[0]=0;
                if(flagCounter[1])
                    flagCounter[1]=0;
                if(flagCounter[2])
                    flagCounter[2]=0;
                break;
            case G01:
                if(g00)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_MOTION=curGcode;
                g00=true;
                if(flagCounter[11]&&flagCounter[12])
                {
                    alarm_code=3;
                    return alarm_code;
                }
                if(flagCounter[0])
                    flagCounter[0]=0;
                if(flagCounter[1])
                    flagCounter[1]=0;
                if(flagCounter[2])
                    flagCounter[2]=0;
                if(flagCounter[3])
                    flagCounter[3]=0;

                if(flagCounter[11])
                    flagCounter[11]=0;
                else if(flagCounter[12])
                    flagCounter[12]=0;
                break;
            case G02:
            case G03:
                if(g00)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_MOTION=curGcode;
                if(!flagCounter[6]&&!flagCounter[7]&&!flagCounter[5])
                {
                    alarm_code=2;
                    return alarm_code;
                }

                if((flagCounter[11]&&flagCounter[12])
                 ||((flagCounter[6]||flagCounter[7])&&flagCounter[5]))
                {
                    alarm_code=3;
                    return alarm_code;
                }
                if(flagCounter[0])
                    flagCounter[0]=0;
                if(flagCounter[1])
                    flagCounter[1]=0;
                if(flagCounter[2])
                    flagCounter[2]=0;
                if(flagCounter[3])
                    flagCounter[3]=0;

                if(flagCounter[5])
                    flagCounter[5]=0;
                if(flagCounter[6])
                    flagCounter[6]=0;
                if(flagCounter[7])
                    flagCounter[7]=0;

                if(flagCounter[11])
                    flagCounter[11]=0;
                else if(flagCounter[12])
                    flagCounter[12]=0;
                g00=true;
                break;
            case G06:
            case G12:
                if(g00)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_MOTION=curGcode;
                if(!flagCounter[0]&&!flagCounter[1]&&!flagCounter[2])
                {
                    alarm_code=2;
                    return alarm_code;
                }
                if(flagCounter[0])
                    flagCounter[0]=0;
                if(flagCounter[1])
                    flagCounter[1]=0;
                if(flagCounter[2])
                    flagCounter[2]=0;
                if(flagCounter[3])
                    flagCounter[3]=0;
                g00=true;
                break;
            case G04:
                if(curSeg.G_MOTION_0>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_MOTION_0=G04;
                if(flagCounter[9])
                    flagCounter[9]=0;
                else if(flagCounter[0])
                    flagCounter[0]=0;
                else
                {
                    alarm_code=2;
                    return alarm_code;
                }
                break;
            case G09:
                if(curSeg.G_PRECISE_STOP>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_PRECISE_STOP=curGcode;
                break;
            case G28:
                if(curSeg.G_HOME_RETURN>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_HOME_RETURN=curGcode;
                if(!flagCounter[0]&&!flagCounter[1]&&!flagCounter[2])
                {
                    alarm_code=2;
                    return alarm_code;
                }
                if(flagCounter[0])
                    flagCounter[0]=0;
                if(flagCounter[1])
                    flagCounter[1]=0;
                if(flagCounter[2])
                    flagCounter[2]=0;
                break;
            case G31:
                if(curSeg.G_PREVIEW_STOP>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_PREVIEW_STOP=curGcode;
                if(!flagCounter[0]&&!flagCounter[1]&&!flagCounter[2])
                {
                    alarm_code=2;
                    return alarm_code;
                }
                if(flagCounter[0])
                    flagCounter[0]=0;
                if(flagCounter[1])
                    flagCounter[1]=0;
                if(flagCounter[2])
                    flagCounter[2]=0;
                if(flagCounter[3])
                    flagCounter[3]=0;
                if(flagCounter[9])
                    flagCounter[9]=0;
                break;
            case G33:
            case G34:
            case G35:
                if(g34)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_CHAMFERING_ROUNDED=curGcode;
                if(curGcode==G33)
                {
                    if(flagCounter[5])
                        flagCounter[5]=0;
                    else
                    {
                        alarm_code=2;
                        return alarm_code;
                    }
                }
                else if(curGcode==G35)
                {
                    if(flagCounter[4])
                        flagCounter[4]=0;
                    else
                    {
                        alarm_code=2;
                        return alarm_code;
                    }
                }
                g34=true;
                break;
            case G61:
            case G62:
            case G64:
            case G164:
                if(curSeg.G_CORNER>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_CORNER=curGcode;
                break;
            case G82:
                if(curSeg.G_LASER>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_LASER=curGcode;
                break;
            case G87:
                if(curSeg.G_GAP>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_GAP=curGcode;
                if(flagCounter[9])
                    flagCounter[9]=0;
                else
                {
                    alarm_code=2;
                    return alarm_code;
                }
                break;
            case G88:
                if(curSeg.G_CORNER>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_CORNER=curGcode;
                if(flagCounter[9])
                    flagCounter[9]=0;
                else
                {
                    alarm_code=2;
                    return alarm_code;
                }
                break;
            case G90:
            case G91:
                if(g90)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_ABS=curGcode;
                g90=true;
                break;
            case G173:
            case G174:
                if(g174)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_CORNER_LOOP=curGcode;
                if(curGcode==G173)
                {
                    if(flagCounter[5])
                        flagCounter[5]=0;
                    else
                    {
                        alarm_code=2;
                        return alarm_code;
                    }
                }
                g174=true;
                break;
            case G181:
            case G183:
                if(curSeg.G_POWER_RAMP>0||curSeg.G_GAS_RAMP>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_POWER_RAMP=curGcode;
                if(curGcode==G181)
                {
                    if(!flagCounter[5]||!flagCounter[9]||!flagCounter[10])
                    {
                        alarm_code=2;
                        return alarm_code;
                    }
                    if(flagCounter[5])
                        flagCounter[5]=0;
                    if(flagCounter[9])
                        flagCounter[9]=0;
                    if(flagCounter[10])
                        flagCounter[10]=0;
                }
                break;
            case G188:
            case G189:
                if(curSeg.G_POWER_RAMP>0||curSeg.G_GAS_RAMP>0)
                {
                    alarm_code=1;
                    return alarm_code;
                }
                curSeg.G_GAS_RAMP=curGcode;
                if(curGcode==G188)
                {
                    if(flagCounter[9])
                        flagCounter[9]=0;
                    else
                    {
                        alarm_code=2;
                        return alarm_code;
                    }
                }
                break;
            default:
                alarm_code=1;
                return alarm_code;
        }
    }
    for(int i=4; i<13; i++)
    {
        if(flagCounter[i])
        {
            alarm_code=4;
            return alarm_code;
        }
    }

    //
    qDebug("rot re: %s\n",ori_str.toLatin1().data());

    return 0;
}

void InitInterpSegBuf()
{
    memset(_intepSegBuf,0,sizeof(_intepSegBuf));
    _canInteractive=true;
}
void ChangeInterpSegBufState(bool isCanInteractive)
{
    _canInteractive=isCanInteractive;
}
bool IsCanGetInterpSegBuf()
{
    return _canInteractive;
}
bool IsInterpSegBufEmpty()
{
    return (_interpSegBufGetBufNum==_interpSegBufRealBufNum);
}
bool IsInterpSegBufFull()
{
    return ((_interpSegBufGetBufNum+_interpSegBufCapacity)==_interpSegBufRealBufNum);
}
bool GetInterpSegData(InterpSegData* getSeg)
{
    if(_interpSegBufGetBufNum<_interpSegBufRealBufNum)
    {
        memcpy(getSeg,&_intepSegBuf[_interpSegBufGetNo],sizeof(InterpSegData));
        _interpSegBufGetNo = (_interpSegBufGetNo+1) % _interpSegBufCapacity;
        _interpSegBufGetBufNum++;

        ABS_MODAL_ITP(getSeg->group_id,getSeg->G_ABS);   //
        MOTION_MODAL_ITP(getSeg->group_id,getSeg->G_MOTION);   //
        CHAMFERING_ROUNDED_MODAL_ITP(getSeg->group_id,getSeg->G_CHAMFERING_ROUNDED);   //
        CORNER_LOOP_MODAL_ITP(getSeg->group_id,getSeg->G_CORNER_LOOP);   //

        return true;
    }
    return false;
}
void FillInterpSegDataBuf(InterpSegData* seg)
{
    if(!_canInteractive)
        return;

    memcpy(&_intepSegBuf[_interpSegBufFillNo],seg,sizeof(InterpSegData));
    _interpSegBufFillNo = (_interpSegBufFillNo+1) % _interpSegBufCapacity;
    _interpSegBufRealBufNum++;
}
