#include "interpolation.h"
#include "ncprogpreprocess.h"
#include "interpsegdata.h"
#include "DefSysSignalAndData.h"
#ifdef Q_OS_LINUX
#include <dlfcn.h>
#elif Q_OS_WIN32
#include <dlfcn.h>
#endif

namespace InterpCtrl
{
    class Pimpl
    {
    public:
        Pimpl(Interpolation *ori);
        ~Pimpl();
        void Init();
        InterpInit PInterpInit;
        PreProcess PInterpPre;
        CoarseInterp PInterpCoarse;
        ElaborateInterp PInterpElaborate;

    public:
        InterpPara         _ctrlPara;
        ItpProcessState    _proState;
        ItpCoarseState     _coarseState;
        ItpElaborateState  _elaborateState;
#ifdef Q_OS_LINUX
        void *pdlHandle;
#elif Q_OS_WIN32
        HINSTANCE pdlHandle;
#endif
        const Interpolation* const owner;
    };
    Pimpl::Pimpl(Interpolation *ori)
        :owner(ori)
    {
        pdlHandle = NULL;
        PInterpInit = NULL;
        PInterpPre = NULL;
        PInterpCoarse = NULL;
        PInterpElaborate = NULL;

        Init();
    }
    Pimpl::~Pimpl()
    {
    }
    void Pimpl::Init()
    {
        unsigned int groupNo = owner->_GroupNo;
        _ctrlPara._GroupNo=groupNo;
        _ctrlPara.PROG_AXIS=ReadI_AXIS_NUM_ITP(groupNo);
        _ctrlPara.LOOKBUF=ReadI_LOOKBUF_ITP(groupNo);         //前瞻缓冲区设定段数
        _ctrlPara.LOOKBUF_LEN=ReadI_LOOKBUF_LEN_ITP(groupNo);            //前瞻缓冲区长度限制
        _ctrlPara.LOOK_TIME=ReadI_LOOK_TIME_ITP(groupNo);       //前瞻限定时间
        _ctrlPara.CONTOUR_ACCURACY=ReadI_CONTOUR_ACCURACY_ITP(groupNo);       //轮廓精度
        _ctrlPara.ARRIVE_ACCURACY=ReadI_ARRIVE_ACCURACY_ITP(groupNo);        //到位精度
        _ctrlPara.SMALLLINES_LEN=ReadI_SMALLLINES_LEN_ITP(groupNo);         //小线段判定长度
        _ctrlPara.SMALLLINES_ANGLE=ReadI_SMALLLINES_ANGLE_ITP(groupNo);    //拐角过渡角度限制
        _ctrlPara.ARC_R_ERR=ReadI_ARC_R_ERR_ITP(groupNo);              //圆弧半径误差限制
        _ctrlPara.FEED_LIMIT=ReadI_FEED_LIMIT_ITP(groupNo);             //进给速度限制
        _ctrlPara.ACC_LIMIT=ReadI_ACC_LIMIT_ITP(groupNo);              //加速度限制
        _ctrlPara.JERK_LIMIT=ReadI_JERK_LIMIT_ITP(groupNo);       //小线段限定角度
        _ctrlPara.SMALLLINES_OMIT_LEN=ReadI_SMALLLINES_OMIT_LEN_ITP(groupNo);    //小线段限定可忽略(合并)长度
        _ctrlPara.SMALLLINES_CURVES_LEN=ReadI_SMALLLINES_CURVES_LEN_ITP(groupNo);  //小线段限定曲线长度
        _ctrlPara.TRANS_ANGLE=ReadI_TRANS_ANGLE_ITP(groupNo);            //跃度限制
        _ctrlPara.STRATEGIES_SEL=ReadI_STRATEGIES_SEL_ITP(groupNo);  //strategies(策略) 1--速度优先  2--精度优先  3--均衡控制
        _ctrlPara.ALG_PARA0=ReadI_ALG_PARA_ITP(groupNo,0);
        _ctrlPara.ALG_PARA1=ReadI_ALG_PARA_ITP(groupNo,1);
        _ctrlPara.ALG_PARA2=ReadI_ALG_PARA_ITP(groupNo,2);
        _ctrlPara.ALG_PARA3=ReadI_ALG_PARA_ITP(groupNo,3);
        _ctrlPara.ALG_PARA4=ReadI_ALG_PARA_ITP(groupNo,4);
        _ctrlPara.ALG_PARA5=ReadI_ALG_PARA_ITP(groupNo,5);
        _ctrlPara.ALG_PARA6=ReadI_ALG_PARA_ITP(groupNo,6);
        _ctrlPara.ALG_PARA7=ReadI_ALG_PARA_ITP(groupNo,7);
        _ctrlPara.ALG_PARA8=ReadI_ALG_PARA_ITP(groupNo,8);
        _ctrlPara.ALG_PARA9=ReadI_ALG_PARA_ITP(groupNo,9);

        for(unsigned int i=0; i<*_ctrlPara.PROG_AXIS; i++)
        {
            unsigned int motorNo=ReadI_AXIS_MOTOR_ITP(owner->_GroupNo,i,0);
            float* ptcp;
            TheSysData()->GetAxisPtcp(motorNo,&ptcp);         //螺距补偿值--指向一纬数组,个数=(螺距补偿终点-螺距补偿起点)/螺距补偿间隔+1
            _ctrlPara.pAxisDef[i][0]._MotorNo=motorNo;
            _ctrlPara.pAxisDef[i][0].PROGNAME=ReadI_NAME_MOTOR(motorNo);           //编程名字:X/Y/Z/A/B/C/U/V/W
            _ctrlPara.pAxisDef[i][0].CLEARANCE=ReadI_CLEAR_MOTOR(motorNo);          //clearance (间隙值)
            _ctrlPara.pAxisDef[i][0].TRAVEL=ReadI_TRAVEL_MOTOR(motorNo);             //travel (有效行程)
            _ctrlPara.pAxisDef[i][0].START_PTCP=ReadI_START_PTCP_MOTOR(motorNo);         //pitch compensation start pos (螺距补偿起点)
            _ctrlPara.pAxisDef[i][0].END_PTCP=ReadI_END_PTCP_MOTOR(motorNo);           //pitch compensation end pos (螺距补偿终点)
            _ctrlPara.pAxisDef[i][0].DIS_PTCP=ReadI_DIS_PTCP_MOTOR(motorNo);           //pitch compensation distance (螺距补偿间隔)
            _ctrlPara.pAxisDef[i][0].ACC_L_PTCP=ReadI_ACC_L_PTCP_MOTOR(motorNo);         //螺距补偿加速度限制
            _ctrlPara.pAxisDef[i][0].JERK_L_PTCP=ReadI_JERK_LIMIT_ITP(motorNo);        //螺距补偿跃度限制
            _ctrlPara.pAxisDef[i][0].VALUE_PTCP=ptcp;
            _ctrlPara.pAxisDef[i][0].FEEDSPEED_L=ReadI_FEEDSPEED_L_MOTOR(motorNo);        //最大进给速度
            _ctrlPara.pAxisDef[i][0].ACC_L=ReadI_ACC_L_MOTOR(motorNo);              //最大加速度
            _ctrlPara.pAxisDef[i][0].JERK_L=ReadI_JERK_L_MOTOR(motorNo);             //最大跃度
            _ctrlPara.pAxisDef[i][0].G00SPEED_L=ReadI_G00SPEED_L_MOTOR(motorNo);         //G00速度
            _ctrlPara.pAxisDef[i][0].LOWSPEED_SL=ReadI_LOWSPEED_SL_MOTOR(motorNo);        //速度平滑-限制低速

            if(ReadI_AXIS_MOTOR_ITP(owner->_GroupNo,i,1))
            {
                motorNo=ReadI_AXIS_MOTOR_ITP(owner->_GroupNo,i,1);
                TheSysData()->GetAxisPtcp(motorNo,&ptcp);         //螺距补偿值--指向一纬数组,个数=(螺距补偿终点-螺距补偿起点)/螺距补偿间隔+1
                _ctrlPara.pAxisDef[i][1]._MotorNo=motorNo;
                _ctrlPara.pAxisDef[i][1].PROGNAME=ReadI_NAME_MOTOR(motorNo);           //编程名字:X/Y/Z/A/B/C/U/V/W
                _ctrlPara.pAxisDef[i][1].CLEARANCE=ReadI_CLEAR_MOTOR(motorNo);          //clearance (间隙值)
                _ctrlPara.pAxisDef[i][1].TRAVEL=ReadI_TRAVEL_MOTOR(motorNo);             //travel (有效行程)
                _ctrlPara.pAxisDef[i][1].START_PTCP=ReadI_START_PTCP_MOTOR(motorNo);         //pitch compensation start pos (螺距补偿起点)
                _ctrlPara.pAxisDef[i][1].END_PTCP=ReadI_END_PTCP_MOTOR(motorNo);           //pitch compensation end pos (螺距补偿终点)
                _ctrlPara.pAxisDef[i][1].DIS_PTCP=ReadI_DIS_PTCP_MOTOR(motorNo);           //pitch compensation distance (螺距补偿间隔)
                _ctrlPara.pAxisDef[i][1].ACC_L_PTCP=ReadI_ACC_L_PTCP_MOTOR(motorNo);         //螺距补偿加速度限制
                _ctrlPara.pAxisDef[i][1].JERK_L_PTCP=ReadI_JERK_LIMIT_ITP(motorNo);        //螺距补偿跃度限制
                _ctrlPara.pAxisDef[i][1].VALUE_PTCP=ptcp;
                _ctrlPara.pAxisDef[i][1].FEEDSPEED_L=ReadI_FEEDSPEED_L_MOTOR(motorNo);        //最大进给速度
                _ctrlPara.pAxisDef[i][1].ACC_L=ReadI_ACC_L_MOTOR(motorNo);              //最大加速度
                _ctrlPara.pAxisDef[i][1].JERK_L=ReadI_JERK_L_MOTOR(motorNo);             //最大跃度
                _ctrlPara.pAxisDef[i][1].G00SPEED_L=ReadI_G00SPEED_L_MOTOR(motorNo);         //G00速度
                _ctrlPara.pAxisDef[i][1].LOWSPEED_SL=ReadI_LOWSPEED_SL_MOTOR(motorNo);        //速度平滑-限制低速
            }
            else
            {
                _ctrlPara.pAxisDef[i][1]._MotorNo=UNKNOWN;
            }
        }
        _proState._GroupNo=groupNo;
        _proState.FEED_RATE=ReadI_FEED_RATE_ITP(groupNo);
        _proState.PROG_COMPLETE=ReadI_PROG_STATE_ITP(groupNo);
        _proState.ERR_NO=ReadI_ALARM_NO_ITP(groupNo);
        _proState.LOOK_LEN=ReadI_LOOK_LEN_ITP(groupNo);
        _proState.LOOK_SEG=ReadI_LOOK_SEG_ITP(groupNo);
        _proState.LOOK_SSPEED=ReadI_LOOK_SSPEED_ITP(groupNo);

        _coarseState._GroupNo=groupNo;
        _coarseState.FEED_RATE=ReadI_FEED_RATE_ITP(groupNo);
        _coarseState.PROG_SPEED=ReadI_PROG_SPEED_ITP(groupNo);
        _coarseState.ABS_MODAL=ReadI_ABS_MODAL_ITP(groupNo);
        _coarseState.CHAMFERING_ROUNDED_MODAL=ReadI_CHAMFERING_ROUNDED_MODAL_ITP(groupNo);
        _coarseState.CORNER_LOOP_MODAL=ReadI_CORNER_LOOP_MODAL_ITP(groupNo);
        _coarseState.MOTION_MODAL=ReadI_MOTION_MODAL_ITP(groupNo);
        _coarseState.M_CODE=ReadI_MCODE_MODAL_ITP(groupNo);
        _coarseState.FILE_NO=ReadI_FILE_NO_ITP(groupNo);
        _coarseState.SEG_NO=ReadI_SEG_NO_ITP(groupNo);
        _coarseState.SEG_NUM=ReadI_WORK_SEG_ITP(groupNo);
        _coarseState.REAL_FSPEED=ReadI_REAL_FSPEED_ITP(groupNo);
        _coarseState.SURPLUS_LEN=ReadI_SURPLUS_LEN_ITP(groupNo);
        _coarseState.SURPLUS_LEN_AXIS0=ReadI_SURPLUS_LEN_AXIS_ITP(groupNo,0);
        _coarseState.SURPLUS_LEN_AXIS1=ReadI_SURPLUS_LEN_AXIS_ITP(groupNo,1);
        _coarseState.SURPLUS_LEN_AXIS2=ReadI_SURPLUS_LEN_AXIS_ITP(groupNo,2);
        _coarseState.SURPLUS_LEN_AXIS3=ReadI_SURPLUS_LEN_AXIS_ITP(groupNo,3);
        _coarseState.SURPLUS_LEN_AXIS4=ReadI_SURPLUS_LEN_AXIS_ITP(groupNo,3);
        _coarseState.SURPLUS_LEN_AXIS5=ReadI_SURPLUS_LEN_AXIS_ITP(groupNo,4);
        _coarseState.THEORY_ERR=ReadI_THEORY_ERR_ITP(groupNo);

        _elaborateState._GroupNo=groupNo;
        _elaborateState.OUPUT_NO=ReadI_OUTPUT_NO_ITP(groupNo);                  //精插补输出点号(1~6),-1 表示无效点,5 表示插补输出已经完成----当前阶段(当前插值曲线或多项式)
        _elaborateState.OUPUT_MAIN_AXIS_POS0=ReadI_OUTPUT_AXIS_POS_ITP(groupNo,0,0);    //主动轴0的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_MAIN_AXIS_POS1=ReadI_OUTPUT_AXIS_POS_ITP(groupNo,0,1);    //主动轴1的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_MAIN_AXIS_POS2=ReadI_OUTPUT_AXIS_POS_ITP(groupNo,0,2);    //主动轴2的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_MAIN_AXIS_POS3=ReadI_OUTPUT_AXIS_POS_ITP(groupNo,0,3);    //主动轴3的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_MAIN_AXIS_POS4=ReadI_OUTPUT_AXIS_POS_ITP(groupNo,0,4);    //主动轴4的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_MAIN_AXIS_POS5=ReadI_OUTPUT_AXIS_POS_ITP(groupNo,0,5);    //主动轴5的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_SLAVE_AXIS_POS0=ReadI_OUTPUT_SLAVEAXIS_POS_ITP(groupNo,0,0);    //从动轴0的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_SLAVE_AXIS_POS1=ReadI_OUTPUT_SLAVEAXIS_POS_ITP(groupNo,0,1);    //从动轴1的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_SLAVE_AXIS_POS2=ReadI_OUTPUT_SLAVEAXIS_POS_ITP(groupNo,0,2);    //从动轴2的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_SLAVE_AXIS_POS3=ReadI_OUTPUT_SLAVEAXIS_POS_ITP(groupNo,0,3);    //从动轴3的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_SLAVE_AXIS_POS4=ReadI_OUTPUT_SLAVEAXIS_POS_ITP(groupNo,0,4);    //从动轴4的插补输出点坐标(含补偿值)
        _elaborateState.OUPUT_SLAVE_AXIS_POS5=ReadI_OUTPUT_SLAVEAXIS_POS_ITP(groupNo,0,5);    //从动轴5的插补输出点坐标(含补偿值)

        _elaborateState.REAL_POS_AXIS0=ReadI_POS_AXIS_MODAL(groupNo,0);          //轴0的实际插补坐标(不含补偿值),主动轴代表从动轴
        _elaborateState.REAL_POS_AXIS1=ReadI_POS_AXIS_MODAL(groupNo,1);          //轴1的实际插补坐标(不含补偿值),主动轴代表从动轴
        _elaborateState.REAL_POS_AXIS2=ReadI_POS_AXIS_MODAL(groupNo,2);          //轴2的实际插补坐标(不含补偿值),主动轴代表从动轴
        _elaborateState.REAL_POS_AXIS3=ReadI_POS_AXIS_MODAL(groupNo,3);          //轴3的实际插补坐标(不含补偿值),主动轴代表从动轴
        _elaborateState.REAL_POS_AXIS4=ReadI_POS_AXIS_MODAL(groupNo,4);          //轴4的实际插补坐标(不含补偿值),主动轴代表从动轴
        _elaborateState.REAL_POS_AXIS5=ReadI_POS_AXIS_MODAL(groupNo,5);          //轴5的实际插补坐标(不含补偿值),主动轴代表从动轴

        _elaborateState.CTRL_LASER=ReadI_OUTPUT_CTRL_LASER(groupNo);
        _elaborateState.LASER_CTRL_P=ReadI_OUTPUT_LASER_CTRL_PARA_ITP(groupNo,0,0);            //激光器的输出参数--激光功率
        _elaborateState.LASER_CTRL_Q=ReadI_OUTPUT_LASER_CTRL_PARA_ITP(groupNo,0,1);            //激光器的输出参数--频率
        _elaborateState.LASER_CTRL_R=ReadI_OUTPUT_LASER_CTRL_PARA_ITP(groupNo,0,2);            //激光器的输出参数--占空比
        _elaborateState.LASER_CTRL_PRE=ReadI_OUTPUT_LASER_CTRL_PARA_ITP(groupNo,0,3);          //激光器的输出参数--辅助气体气压
    }

    Interpolation::Interpolation(unsigned int goupNo,QObject *parent) :
        QThread(parent)
    {
        _GroupNo=goupNo;
        data = new Pimpl(this);
    }
    Interpolation::~Interpolation()
    {
        delete data;
    }
    bool Interpolation::InitLoadDLL(char* path)
    {
    #ifdef Q_OS_LINUX
        if(data->pdlHandle !=NULL)
        {
            dlclose(data->pdlHandle);
        }
        data->pdlHandle = dlopen(path,RTLD_LAZY);  // 加载指定的库
        char *pszErr = dlerror(); // 检查出错信息
        if(NULL==pszErr)
        {
            data->PInterpInit = (InterpInit)dlsym(data->pdlHandle,"InterpInit");  // 定位动态链接库中的函数；
            data->PInterpPre = (PreProcess)dlsym(data->pdlHandle,"PreProcess");  // 定位动态链接库中的函数；
            data->PInterpCoarse = (CoarseInterp)dlsym(data->pdlHandle,"CoarseInterp");  // 定位动态链接库中的函数；
            data->PInterpElaborate = (ElaborateInterp)dlsym(data->pdlHandle,"ElaborateInterp");  // 定位动态链接库中的函数；

            if(NULL==data->PInterpInit||NULL==data->PInterpPre||NULL==data->PInterpCoarse||NULL==data->PInterpElaborate)
            {
                dlclose(data->pdlHandle); // 系统动态链接库引用数减1
                return false;
            }
        }
        else
        {
            data->PInterpInit = NULL;
            data->PInterpPre = NULL;
            data->PInterpCoarse = NULL;
            data->PInterpElaborate = NULL;
        }
    #elif Q_OS_WIN32
        if(data->pdlHandle !=NULL)
        {
            FreeLibrary(data->pdlHandle);
        }
        data->pdlHandle = ::LoadLibrary(path);
        if(data->pdlHandle != NULL)
        {
            data->PInterpInit = (InterpInit)GetProcAddress(data->pdlHandle, "InterpInit");
            data->PInterpPre = (PreProcess)GetProcAddress(data->pdlHandle,"PreProcess");  // 定位动态链接库中的函数；
            data->PInterpCoarse = (CoarseInterp)GetProcAddress(data->pdlHandle,"CoarseInterp");  // 定位动态链接库中的函数；
            data->PInterpElaborate = (ElaborateInterp)GetProcAddress(data->pdlHandle,"ElaborateInterp");  // 定位动态链接库中的函数；

            if(NULL==data->PInterpInit||NULL==data->PInterpPre||NULL==data->PInterpCoarse||NULL==data->PInterpElaborate)
            {
                FreeLibrary(data->pdlHandle);
                return false;
            }
        }
        else
        {
            return false;
        }
    #endif

        return true;
    }
    void Interpolation::Stop()
    {
        FM_DISA_ITP(_GroupNo,0);
    }

    void Interpolation::run()
    {
        unsigned int timeCount=0;

        *data->_elaborateState.OUPUT_NO=-1;

        while(!ReadFM_DISA_ITP(_GroupNo))
        {
            if(ReadI_INIT_ITP(_GroupNo)==INTERP_RESET)
            {
                I_INIT_ITP(_GroupNo,0);
                if(data->PInterpInit!=NULL)
                    data->PInterpInit(&data->_ctrlPara,GetInterpSegData,ErrRepot);
                I_AUTO_INTERP_FINISHED_ITP(_GroupNo,0);
                I_STATE_ITP(_GroupNo,1);
            }
            while(2==ReadI_AUTO_INTERP_FINISHED_ITP(_GroupNo)&&ReadFM_CANDO_ITP(_GroupNo))
            {
                if(timeCount%32==0&&ReadFM_DISA_ITP(_GroupNo))
                {
                    if(data->PInterpPre!=NULL)
                    {
                        if(ReadFM_STL)
                        {
                            if(*ReadI_STATE_ITP(_GroupNo))
                            {//当前段已经完成插补和输出
                                if(ReadFM_MSBK)
                                {
                                    if(2!=data->_proState.CTRL_TYPE)
                                        data->_proState.CTRL_TYPE = 2;
                                }
                                else
                                {
                                    if(1!=data->_proState.CTRL_TYPE)
                                        data->_proState.CTRL_TYPE = 1;
                                }
                            }
                            else
                            {
                                data->_proState.CTRL_TYPE = 3;
                            }
                        }
                        else
                        {
                            data->_proState.CTRL_TYPE = 0;
                        }

                        data->PInterpPre(&data->_proState);
                    }
                }

                if(timeCount%6==0&&ReadFM_DISA_ITP(_GroupNo))
                {
                    if(data->PInterpCoarse!=NULL)
                    {
                        if(ESP_PLC)
                            data->_coarseState.CTRL_TYPE = 0;
                        else if(*data->_coarseState.FEED_RATE<Miniumnum)
                             data->_coarseState.CTRL_TYPE = 2;
                        else
                             data->_coarseState.CTRL_TYPE = 1;
                        data->_coarseState.SKIP_FLAG = SkipSeg_PLC;
                        data->_coarseState.MCODE_UNCOMPLETE = !FIN_PLC(_GroupNo);

                        data->PInterpCoarse(&data->_coarseState);
                    }
                }

                if(data->PInterpElaborate!=NULL&&ReadFM_DISA_ITP(_GroupNo))
                    data->PInterpElaborate(&data->_elaborateState);

                if(*data->_coarseState.SURPLUS_LEN<Miniumnum&&!data->_coarseState.MCODE_UNCOMPLETE&&*data->_elaborateState.OUPUT_NO==-1)
                    I_STATE_ITP(_GroupNo,1);
                else
                    I_STATE_ITP(_GroupNo,0);

                if(!data->_coarseState.MCODE_UNCOMPLETE&&*data->_elaborateState.OUPUT_NO==-1
                   &&((*data->_proState.PROG_COMPLETE&&ReadFM_STL)
                     ||(!*data->_proState.PROG_COMPLETE&&!ReadFM_STL&&!ReadFM_SPL)))
                {
                    I_AUTO_INTERP_FINISHED_ITP(_GroupNo,1);
                }
                ++timeCount;
                msleep(1);
            }
            msleep(100);
        }
    }
}
