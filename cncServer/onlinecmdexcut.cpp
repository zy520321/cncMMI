#include "onlinecmdexcut.h"
#include "systemdatamanager.h"
#include "serverthreadctrl.h"
#include "plcmainctrl.h"
#include "interpolation.h"
#include "DefSysSignalAndData.h"
#include "interpsegdata.h"
#include "alarm.h"
#include "ncprogpreprocess.h"

void ClearErr()
{
    SysAlarm::Alarm::GetAlarmEngine()->InitBuf();
    FM_AL(0);
}
void ErrRepot(int errNo)
{
    D_ALARM(errNo);
    SysAlarm::Alarm::GetAlarmEngine()->AddErr(errNo);
}
void ErrRepot(int errNo,int line,int prog)
{
    D_ALARM(errNo);
    SysAlarm::Alarm::GetAlarmEngine()->AddErr(errNo,line,prog);
}
bool GetErr(QString& errMsg)
{
    return SysAlarm::Alarm::GetAlarmEngine()->GetBufStr(errMsg);
}

using namespace SystemData;
namespace WorkModel
{
    class Ipmpl
    {
    public:
        Ipmpl(int interpNum=1);
        ~Ipmpl();
        bool ProcessInterpChg();
        bool ProcessPlcChg();
        void CNCStateCheck();
        void CNCWorkModelProcess();

        void SetFeedrateZero(float rate);
        void ResetCNCStatusAction();
        void ESPAlarmToStop();
        void ESPAlarmToStopAction();
        void CNCChgCtrlStyleOK();
        void ChangCtrlStyle();

        bool AutoStartAndPause();
        bool AutoStart();
        void AutoPause();
        bool AutoRunStateAction();

    public:
        bool _systemRunning;
        ServerThreadCtrl* serverCtrl;
        PLCMainCtrl* plcCtrl;
        InterpCtrl::Interpolation* interpCtrl[4];
        int _realInterpNum;
    };
    Ipmpl::Ipmpl(int interpNum)
    {
        ClearErr();
        serverCtrl = new ServerThreadCtrl();
        plcCtrl = new PLCMainCtrl();
        _realInterpNum=interpNum;
        if(_realInterpNum>4)
            _realInterpNum=4;
        else if(_realInterpNum<1)
            _realInterpNum=1;
        for(int i=0; i<_realInterpNum; i++)
        {
            interpCtrl[i] = new InterpCtrl::Interpolation(i);
        }
        _systemRunning=false;
    }
    Ipmpl::~Ipmpl()
    {
        delete serverCtrl;
    }
    bool Ipmpl::ProcessInterpChg()
    {
        for(int i=0; i<_realInterpNum; i++)
        {
            if(DISA_INTERP_CMD(i)&&!ReadFM_DISA_ITP(i))
            {
                if(interpCtrl[i]->isRunning())
                    interpCtrl[i]->terminate();
                else
                    FM_DISA_ITP(i,1);
            }
            else if((!DISA_INTERP_CMD(i)&&ReadFM_DISA_ITP(i))||(!DISA_INTERP_CMD(i)&&!ReadFM_DISA_ITP(i)))
            {
                if(!interpCtrl[i]->isRunning())
                    interpCtrl[i]->start();
                else
                    FM_DISA_ITP(i,0);
            }
        }
        return true;
    }
    //====================================================================================================
    //函数说明:   CNC状态检查
    //    无参数 :   包括如下处理
    //====================================================================================================
    void Ipmpl::CNCStateCheck()
    {
        static unsigned int count=0;
        if(ESP_PLC)
        {
            if(!ReadFM_ESP)
            {
                count=0;
                FM_ESP(1);
                SetFeedrateZero(0);
                D_STCHG_CTRL(STOP_NOW_MODEL);
                D_STATE_CHG(RUN_STYLE_CHG_ESP);
            }
        }
        else if((++count)%4==0)
        {
            if(ERS_PLC||ERS_CMD||ReadFM_RST)
            {
                Set_ERS_PLC(0);
                Set_ERS_CMD(0);
                FM_RST(0);
                FM_AL(0);
                I_INIT_ITP(0,INTERP_RESET);
                SetFeedrateZero(0);
                D_STCHG_CTRL(DEC_STOP_MODEL);
                FM_SPL(0);
                D_RESET_TIME(104);
                D_STATE_CHG(RUN_STYLE_CHG_RESET);
                //MST
            }
            else if(ReadD_ALARM&&!ReadFM_AL)
            {
                FM_AL(1);
                SetFeedrateZero(0);
                D_STCHG_CTRL(DEC_STOP_MODEL);
                D_STATE_CHG(RUN_STYLE_CHG_ALRAM);
            }

            if(ReadD_STATE_CHG==RUN_STYLE_CHG_NONE)
            {
                if((ReadFM_MODEL!=CHECK_MODEL_PLC&&CHECK_MODEL_PLC>0&&ReadD_CTRL_PATH==0)
                 ||(ReadFM_MODEL!=CHECK_MODEL_CMD&&CHECK_MODEL_CMD>0&&ReadD_CTRL_PATH==1))
                {
                    D_CtrlStyleCheck(20);
                    if(ReadFM_MZRO)
                    {
                        if(ReadFM_MV)
                            D_STCHG_CTRL(DEC_STOP_MODEL);
                        else
                            D_STCHG_CTRL(CHG_NOW_MODEL);
                    }
                    else if(ReadFM_MWHEEL||ReadFM_MINC)
                    {
                        if(ReadI_MANUAL_INTERP_FINISHED_ITP(0)==2)
                            D_STCHG_CTRL(PULSE_SEND_TO_FINISH_MODEL);
                        else
                            D_STCHG_CTRL(CHG_NOW_MODEL);
                    }
                    else
                        D_STCHG_CTRL(REVERSE_MODEL);

                    if((MDI_PLC&&ReadD_CTRL_PATH==0)||(MDI_CMD&&ReadD_CTRL_PATH==1))
                        D_STATE_CHG(RUN_STYLE_CHG_MDI);
                    else if((AUTO_PLC&&ReadD_CTRL_PATH==0)||(AUTO_CMD&&ReadD_CTRL_PATH==1))
                        D_STATE_CHG(RUN_STYLE_CHG_AUTO);
                    else if((HOME_PLC&&ReadD_CTRL_PATH==0)||(HOME_CMD&&ReadD_CTRL_PATH==1))
                    {
                        if(0==ReadFM_MV&&FIN_PLC(0))
                            D_STCHG_CTRL(CHG_NOW_MODEL);
                        else if(ReadFM_OP)
                            D_STCHG_CTRL(PROG_RUN_TO_FINISH_MODEL);
                        else
                            D_STCHG_CTRL(DEC_STOP_MODEL);

                        D_STATE_CHG(RUN_STYLE_CHG_MACHZERO);
                    }
                    else
                    {
                        if((MANUAL_PLC&&ReadD_CTRL_PATH==0)||(MANUAL_CMD&&ReadD_CTRL_PATH==1))
                            D_STATE_CHG(RUN_STYLE_CHG_JOG);
                        else if(HANDWHEEL_PLC)
                            D_STATE_CHG(RUN_STYLE_CHG_WHEEL);
                        else if(STEP_PLC)
                            D_STATE_CHG(RUN_STYLE_CHG_STEP);

                        if(ReadFM_SPL)
                        {//暂停状态
                            D_STCHG_CTRL(CHG_NOW_MODEL);
                            if(ReadD_AUTO_ISR_CHECK == 0)
                            {
                                D_AUTO_ISR_CHECK(1);
                                D_PAUSE_CTRL_STYLE(ReadFM_MODEL);
                            }
                            else if(ReadD_AUTO_ISR_CHECK == 1)
                                D_AUTO_ISR_CHECK(2);
                        }
                        else if(ReadFM_OP)
                        { //自动运行中状态
                            D_STCHG_CTRL(DEC_STOP_MODEL);

                            if(ReadD_AUTO_ISR_CHECK == 0)
                            {
                                D_AUTO_ISR_CHECK(1);
                                D_PAUSE_CTRL_STYLE(ReadFM_MODEL);
                            }
                            else if(ReadD_AUTO_ISR_CHECK == 1)
                                D_AUTO_ISR_CHECK(2);
                        }
                        else if(ReadFM_MV>0)//轴移动中
                            D_STCHG_CTRL(DEC_STOP_MODEL);
                        else//直接切换
                            D_STCHG_CTRL(CHG_NOW_MODEL);
                    }
                    if(ReadD_STCHG_CTRL==REVERSE_MODEL)
                    {
                        if((MDI_PLC&&ReadFM_MMEM)||(AUTO_PLC&&ReadFM_MMDI))
                        {
                            if(ReadFM_MV || !FIN_PLC(0))
                            {//轴移动中
                                if(ReadFM_OP && !(*ReadI_G28_CTRL_ITP(0) == 2 && !*ReadI_ZERO_SET_STATE_ITP(0)))
                                    D_STCHG_CTRL(PROG_RUN_TO_FINISH_MODEL);
                                else
                                    D_STCHG_CTRL(DEC_STOP_MODEL);
                            }
                            else//直接切换
                                D_STCHG_CTRL(CHG_NOW_MODEL);
                        }
                        else
                        {
                            if(ReadD_PAUSE_CTRL_STYLE == CHECK_MODEL_PLC)
                            {//检查到是要返回的自动运行模式
                                if(ReadFM_MV)//轴移动中
                                    D_STCHG_CTRL(DEC_STOP_MODEL);
                                else//直接切换
                                    D_STCHG_CTRL(CHG_NOW_MODEL);
                            }
                            else
                            {
                                D_AUTO_ISR_CHECK(0); //取消手动干预
                                if(ReadFM_MV)//轴移动中
                                    D_STCHG_CTRL(DEC_STOP_MODEL);
                                else//直接切换
                                    D_STCHG_CTRL(CHG_NOW_MODEL);
                            }
                        }
                    }
                    if(ReadD_STCHG_CTRL==DEC_STOP_MODEL)
                        SetFeedrateZero(0);
                    else if(ReadD_STCHG_CTRL==PROG_RUN_TO_FINISH_MODEL)
                    {
                        SetFeedrateZero(2);
                    }
                }
            }

            if(ReadFM_MMDI||ReadFM_MMEM)
            {
                if(ReadI_AUTO_INTERP_FINISHED_ITP(0)==2&&ReadFM_CANDO_ITP(0)&&ReadFM_OP)
                {
                    if(*ReadI_RECEIVED_SEG_COUNT_SYS==*ReadI_GOT_SEG_COUNT_SYS&&0==*ReadI_PRE_SEG_NUM_ITP(0))
                    {
                        if(!END_PLC(0)&&!M02END_PLC(0))
                            I_AUTO_INTERP_FINISHED_ITP(0,-1);
                        else
                            I_AUTO_INTERP_FINISHED_ITP(0,1);

                        SetFeedrateZero(1);
                        FM_CANDO_ITP(0,0);
                        FM_SPL(0);//取消CNC循环休止中
                        FM_STL(0);
                        FM_OP(0);//取消CNC循环
                    }
                }

                if(ReadD_STATE_CHG==RUN_STYLE_CHG_NONE)
                {
                    if(!AutoStartAndPause())
                    {
                        if(!ReadFM_MDEBUG && ((DEBUG_PLC&&ReadD_CTRL_PATH==0)||(DEBUG_CMD&&ReadD_CTRL_PATH==1)))
                            D_STATE_CHG(RUN_STYLE_CHG_DEBUG_ON);
                        else if(!ReadFM_MSBK&&((SingleSeg_PLC&&ReadD_CTRL_PATH==0)||(SingleSeg_CMD&&ReadD_CTRL_PATH==1)))
                            D_STATE_CHG(RUN_STYLE_CHG_SINGLE_ON);
                        else if(!ReadFM_MAFL&&((AFL_PLC&&ReadD_CTRL_PATH==0)||(AFL_CMD&&ReadD_CTRL_PATH==1)))
                            D_STATE_CHG(RUN_STYLE_CHG_MSTLOCK_ON);
                        else if(ReadFM_MDEBUG && ((!DEBUG_PLC&&ReadD_CTRL_PATH==0)||(!DEBUG_CMD&&ReadD_CTRL_PATH==1)))
                            D_STATE_CHG(RUN_STYLE_CHG_DEBUG_OFF);
                        else if(ReadFM_MSBK&&((!SingleSeg_PLC&&ReadD_CTRL_PATH==0)||(!SingleSeg_CMD&&ReadD_CTRL_PATH==1)))
                            D_STATE_CHG(RUN_STYLE_CHG_SINGLE_OFF);
                        else if(ReadFM_MAFL&&((!AFL_PLC&&ReadD_CTRL_PATH==0)||(!AFL_CMD&&ReadD_CTRL_PATH==1)))
                            D_STATE_CHG(RUN_STYLE_CHG_MSTLOCK_OFF);
                    }
                }
            }
            if(ReadD_STATE_CHG==RUN_STYLE_CHG_NONE)
            {
                if(!ReadFM_MDRN && ((DRN_PLC&&ReadD_CTRL_PATH==0)||(DRN_CMD&&ReadD_CTRL_PATH==1)))
                    D_STATE_CHG(RUN_STYLE_CHG_DRN_ON);
                else if(!ReadFM_MMLK  && ((LOCK_PLC&&ReadD_CTRL_PATH==0)||(LOCK_CMD&&ReadD_CTRL_PATH==1)))
                    D_STATE_CHG(RUN_STYLE_CHG_MCLOCK_ON);
                else if(ReadFM_MDRN && ((!DRN_PLC&&ReadD_CTRL_PATH==0)||(!DRN_CMD&&ReadD_CTRL_PATH==1)))
                    D_STATE_CHG(RUN_STYLE_CHG_DRN_OFF);
                else if(ReadFM_MMLK  && ((!LOCK_PLC&&ReadD_CTRL_PATH==0)||(!LOCK_CMD&&ReadD_CTRL_PATH==1)))
                    D_STATE_CHG(RUN_STYLE_CHG_MCLOCK_OFF);
            }
        }
    }
    //====================================================================================================
    //函数说明:   复位状态内部动作的处理
    //====================================================================================================
    void Ipmpl::ResetCNCStatusAction()
    {
        if(ReadI_AUTO_INTERP_FINISHED_ITP(0)==2)
        {
            if(!END_PLC(0)&&!M02END_PLC(0))
                I_AUTO_INTERP_FINISHED_ITP(0,-1);
            else
                I_AUTO_INTERP_FINISHED_ITP(0,1);
        }
        if(ReadI_AUTO_INTERP_FINISHED_ITP(0)==1)
            I_WORK_SEG_ITP(0,0);

        I_MANUAL_INTERP_FINISHED_ITP(0,1);
        ManualCurrentAxis(0,-1);

        for(unsigned int i = 0; i < *ReadI_AXIS_NUM_ITP(0); i++)
        {
            ManualAxisSelect(0,i,0);
            ManualAxisComplete(0,i,1);

            if(ReadZeroDecAutoSignal(0,i)!= 4)
                ZeroDecAutoSignal(0,i,0);
        }

        D_CtrlStyleCheck(0);
        HandIsrPointStartFlag(0,0);
        I_PRE_SEG_NUM_ITP(0,0);
        I_PROG_STATE_ITP(0,1);
        I_STATE_ITP(0,1);

        Set_FIN_PLC(0,1);

        if(ReadFM_OP&&ReadI_ROT_BUF_STATE_SYS)
            NcProgProcess::GetNcEngine()->InitData(0);

        //Logic_Empty(&LogicBuf);
        //Servo_Empty(NcData.Servodata);
        FM_HardLimitCheck(0);

        SetFeedrateZero(1);
        FM_CANDO_ITP(0,0);
        I_AUTO_INTERP_FINISHED_ITP(0,1);
        I_MANUAL_INTERP_FINISHED_ITP(0,1);

        I_INIT_ITP(0,INTERP_RESET);
        FM_SERVO_DO(0);
        FM_NCBUF_DO(0);
        FM_CANDO_ITP(0,0);

        ClearErr();
        FM_SPL(0);//取消CNC循环休止中
        FM_STL(0);
        FM_OP(0);//取消CNC循环
        FM_MA(1);
    }
    //====================================================================================================
    //函数说明:    插补减速处理
    //====================================================================================================
    void Ipmpl::SetFeedrateZero(float rate)
    {
        float OutputOvrd;

        D_DEC_RATE(rate);

        OutputOvrd = rate*ReadD_FEED_RATE;
        I_FEED_RATE_ITP(0,OutputOvrd);
    }
    //====================================================================================================
    //函数说明:    急停动作的处理
    //====================================================================================================
    void Ipmpl::ESPAlarmToStopAction()
    {
        FM_SERVO_DO(0);
        FM_NCBUF_DO(0);
        FM_CANDO_ITP(0,0);

        Set_FIN_PLC(0,1);//all辅助功能结束信号
        Set_MFIN_PLC(0,1);//M辅助功能结束信号
        Set_SFIN_PLC(0,1);//spindle功能结束信号
        Set_TFIN_PLC(0,1);//tool功能结束信号

        FM_SPL(0);
        FM_STL(0);//取消PMC循环启动中的状态
        FM_OP(0);//取消CNC循环

        I_INIT_ITP(0,INTERP_EMERGENCY);
        ErrRepot(EMERGENCY);
        //Logic_Empty(&LogicBuf);
        //Servo_Empty(NcData.Servodata);
        //InitMachineZeroVar(1);
    }
    //===========================================================================================//
    //函数说明:     循环启动与暂停的处理
    //===========================================================================================//
    bool Ipmpl::AutoStartAndPause()
    {
        //自动运行方式下检测启动和暂停
        if(!ReadFM_STL&&((ST_PLC&&ReadD_CTRL_PATH==0)||(ST_CMD&&ReadD_CTRL_PATH==1)))
        {
            FM_STL(0);
            return AutoStart();
        }
        else if(ReadFM_STL&&((SP_PLC&&ReadD_CTRL_PATH==0)||(SP_CMD&&ReadD_CTRL_PATH==1)))
        {
            if(ReadI_INIT_ITP(0)!= INTERP_FEED_HOLD && ReadI_INIT_ITP(0)!= INTERP_CYCLE_START)
            {
                AutoPause();
                return true;
            }
        }
        return false;
    }
    //====================================================================================================
    //函数说明:    自动运行的启动
    //  无参数
    //====================================================================================================
    bool Ipmpl::AutoStart(void)
    {
        unsigned char AutoRunStartState = 0;

        AutoRunStartState += ReadFM_RST;
        AutoRunStartState += ReadFM_STL;
        AutoRunStartState += (1 - ReadFM_MA);
        AutoRunStartState += ReadFM_MV;
        AutoRunStartState += ((SRN_PLC&&ReadD_CTRL_PATH==0)||(SRN_CMD&&ReadD_CTRL_PATH==1));
        AutoRunStartState += ESP_PLC;
        AutoRunStartState += ((SP_PLC&&ReadD_CTRL_PATH==0)||(SP_CMD&&ReadD_CTRL_PATH==1));

        if(ReadFM_OP && (!ReadFM_SPL && !(ReadI_AUTO_INTERP_FINISHED_ITP(0)==1||ReadI_AUTO_INTERP_FINISHED_ITP(0)==-1)))
            AutoRunStartState += 1;

        //以下情况忽略循环启动信号
        //电子手轮控制中是否不能执行暂停?(后面完善)
        if(!(ReadFM_MMEM || ReadFM_MMDI)|| AutoRunStartState||!ReadFM_PROG_READY_ITP(0))
            return false;

        //以下为CNC设计者自己添加的处理，如译码插补的启动等。
        CNC_Single_Seg_WaitStart(0,ReadFM_MSBK);
        FM_RST(0);
        FM_SERVO_DO(AutoRunStateAction());
        if(ReadI_ROT_BUF_STATE_SYS)
            NcProgProcess::GetNcEngine()->slotBufConnect(ReadFM_SERVO_DO);
        return ReadFM_SERVO_DO;
    }

    //====================================================================================================
    //函数说明:    自动运行启动内部状态处理
    //  无参数
    //====================================================================================================
    bool Ipmpl::AutoRunStateAction()
    {
        if(ReadD_AUTO_ISR_CHECK == 0)
        {
            if(ReadFM_SPL)
            {
                SetFeedrateZero(1);
                FM_STL(1);//CNC循环启动中
                FM_SPL(0);//取消CNC循环休止中
                if(*ReadI_STATE_ITP(0)|| !ReadFM_MSBK)
                {
                    CNCSegLoopStartFlag(0,1);
                    SingleSegStopFlag(0,0);
                }

                if(ReadI_ManualInterventionFlag(0) == 1)
                {
                    //PreHandIsrReturnInterpDataProcess();
                    ManualInterventionFlag(0,0);
                }

                HandIsrSegEndForPauseFlag(0,0);
                FM_CANDO_ITP(0,1);
                I_INIT_ITP(0,INTERP_CYCLE_START);

                if(ReadI_PauseMoveStartFlag(0))
                {
                    if(ReadI_ROT_BUF_STATE_SYS)
                        NcProgProcess::GetNcEngine()->InitData(2);
                    I_INIT_ITP(0,INTERP_RESET_START+2*ReadFM_MSBK);
                    D_DecodeResetFlag_ITP(0,0);
                    D_RE_DECODE_ITP(0,0);
                    PauseMoveStartFlag(0,0);
                }
            }
            else if(!ReadFM_CAN_DECODE_ITP(0))
            {
                if(ReadI_ROT_BUF_STATE_SYS)
                    NcProgProcess::GetNcEngine()->InitData(2);

                I_PROG_STATE_ITP(0,0);
                Set_END_PLC(0,0);
                Set_M02END_PLC(0,0);

                if(ReadD_RE_DECODE_ITP(0)==0)
                {
                    CNCSegLoopStartFlag(0,1);
                    SingleSegStopFlag(0,0);

                    FM_STL(1);//CNC循环启动中
                    FM_SPL(0);//取消CNC循环休止中
                    FM_OP(1);//CNC循环运行中
                }

                SetFeedrateZero(1);
                I_INIT_ITP(0,INTERP_RESET_START+2*ReadFM_MSBK);
                D_DecodeResetFlag_ITP(0,1);
                D_RE_DECODE_ITP(0,0);
                FM_CAN_DECODE_ITP(0,1);
                FM_CANDO_ITP(0,1);
            }
        }
        else
        {
            if(ReadD_RE_DECODE_ITP(0))
            {//如在重新译码时候实施了手动干预等操作，仍需初始化插补 and decode 环境
                I_INIT_ITP(0,INTERP_RESET_START+2*ReadFM_MSBK);
                D_DecodeResetFlag_ITP(0,1);
            }
            else
            {
                I_INIT_ITP(0,INTERP_CYCLE_START+2*ReadFM_MSBK);
            }

            if(ReadFM_MSBK && *ReadI_STATE_ITP(0)==0)
                CNCSegLoopStartFlag(0,0);
            else if(!ReadFM_MSBK && *ReadI_STATE_ITP(0)==0)
                CNCSegLoopStartFlag(0,1);
            else if(*ReadI_STATE_ITP(0))
                CNCSegLoopStartFlag(0,1);

            SingleSegStopFlag(0,0);
            SetFeedrateZero(1);
            FM_STL(1);//CNC循环启动中
            FM_SPL(0);//取消CNC循环休止中
            FM_OP(1);//CNC循环运行中

            if(ReadI_ManualInterventionFlag(0) == 1)
            {
                //PreHandIsrReturnInterpDataProcess();
                ManualInterventionFlag(0,0);
                D_AUTO_ISR_CHECK(0);
            }

             FM_CANDO_ITP(0,1);

            //手动干预或者手轮单步中断返回时如果译码已经进行完将不再译码
            if(!ReadD_RE_DECODE_ITP(0))
                FM_CAN_DECODE_ITP(0,1 - ReadD_DecodeOverCurTimes_ITP(0));
            else
            {
                FM_CAN_DECODE_ITP(0,1);
                I_STATE_ITP(0,1);
            }
        }
        return ReadFM_CANDO_ITP(0);
    }

    //====================================================================================================
    //函数说明:    自动运行的暂停
    //  无参数
    //====================================================================================================
    void Ipmpl::AutoPause()
    {
        D_STATE_CHG(RUN_STYLE_CHG_PAUSE);
        SetFeedrateZero(0);
        I_INIT_ITP(0,INTERP_FEED_HOLD);
    }

    void Ipmpl::CNCWorkModelProcess()
    {
        if(ReadD_RESET_TIME>8)
        {
            D_RESET_TIME(ReadD_RESET_TIME-8);
            if(ReadD_RESET_TIME<8)
                D_RESET_TIME(0);
            else
                return;
        }
        unsigned char state=0;
        state+=(!FIN_PLC(0)&&ReadFM_OP);
        state+=(ReadD_STCHG_CTRL==PULSE_SEND_TO_FINISH_MODEL && !ReadI_MANUAL_INTERP_FINISHED_ITP(0));
        state+=(ReadD_STCHG_CTRL == PROG_RUN_TO_FINISH_MODEL && !(ReadI_MANUAL_INTERP_FINISHED_ITP(0)==1||ReadI_MANUAL_INTERP_FINISHED_ITP(0)==-1));
        state+=((ReadD_DEC_RATE <= Miniumnum || ReadD_STCHG_CTRL==DEC_STOP_MODEL) && ( *ReadI_REAL_FSPEED_ITP(0)>=MaxChgSpeed||ReadFM_MV));

        //方式转换
        if(state)
        {//如果是减速停则必须减速到不再运动
            return;
        }
        if(ReadD_CtrlStyleCheck> 0)
        {
            D_CtrlStyleCheck(ReadD_CtrlStyleCheck-1);
            if(ReadD_CtrlStyleCheck>0)
                return;
        }

        bool CncViewModelChg=false;

        switch(ReadD_STATE_CHG)
        {
        case RUN_STYLE_CHG_NONE://:  没有改变运行方式
            break;

        case RUN_STYLE_CHG_RESET://:  进行复位操作
            ResetCNCStatusAction();
            break;

        case RUN_STYLE_CHG_PAUSE:    //:  进行暂停操作
            FM_STL(0);//取消PMC循环启动中的状态
            FM_SPL(1);//设置PMC循环休止中的状态
            break;

        case RUN_STYLE_CHG_AUTO:     //:  改变到自动方式
        case RUN_STYLE_CHG_MDI:      //:  改变到MDI方式
            CncViewModelChg=true;
            FM_SERVO_DO(0);

            if(!ReadD_AUTO_ISR_CHECK)
            {
                FM_NCBUF_DO(0);
                FM_SPL(0);//取消CNC循环休止中的状态
            }
            if(ReadD_STATE_CHG==RUN_STYLE_CHG_AUTO)
                FM_MMEM;
            else
                FM_MMDI;

            I_MANUAL_INTERP_FINISHED_ITP(0,1);
            break;

        case RUN_STYLE_CHG_MACHZERO: //:  改变到机械回零方式
            CncViewModelChg=true;
            break;

        case RUN_STYLE_CHG_WHEEL:    //:  改变到手轮方式
            CncViewModelChg=true;
            break;

        case RUN_STYLE_CHG_STEP:     //:  改变到单步方式
            CncViewModelChg=true;
            break;

        case RUN_STYLE_CHG_JOG:      //:  改变到手动方式
            CncViewModelChg=true;
            break;

        case RUN_STYLE_CHG_DEBUG_ON: //: 打开DEBUG方式
                    break;
        case RUN_STYLE_CHG_DRN_ON:   //: 打开空运行方式
                    break;
        case RUN_STYLE_CHG_MCLOCK_ON:  //: 打开机床锁
                    break;
        case RUN_STYLE_CHG_MSTLOCK_ON: //: 打开辅助锁
                    break;
        case RUN_STYLE_CHG_SINGLE_ON:  //: 打开单段
                    break;
        case RUN_STYLE_CHG_DEBUG_OFF:  //: 关闭DEBUG方式
                    break;
        case RUN_STYLE_CHG_DRN_OFF:    //: 关闭空运行方式
                    break;
        case RUN_STYLE_CHG_MCLOCK_OFF: //: 关闭机床锁
                    break;
        case RUN_STYLE_CHG_MSTLOCK_OFF://: 关闭辅助锁
                    break;
        case RUN_STYLE_CHG_SINGLE_OFF: //: 关闭单段
                    break;

        case RUN_STYLE_CHG_ALRAM:      //: 报警减速处理
            if(!ReadFM_HardLimitCheck
               || !(ReadFM_MJOG|| ReadFM_MWHEEL|| ReadFM_MINC))
            {
                FM_CANDO_ITP(0,0);
                I_INIT_ITP(0,INTERP_ALARM);
            }

            FM_STL(0);//取消PMC循环启动中的状态
            FM_SPL(0);
            FM_OP(0);//取消CNC循环
            break;

        case RUN_STYLE_CHG_ESP:        //: 急停处理
            ESPAlarmToStopAction();
            break;

        case RUN_STYLE_CHG_RE_DECODE:  //: 重新译码的处理
            break;

        case RUN_STYLE_CHG_RE_START:   //: 重新启动的处理
            break;
        }
        if(CncViewModelChg)
        {
            FM_CANDO_ITP(0,0);
            if(ReadD_AUTO_ISR_CHECK)
            {
                FM_SPL(1);//设置PMC循环休止中的状态
                FM_STL(0);
                ChangCtrlStyle();
            }
            else
            {
                if(ReadD_STCHG_CTRL==PROG_RUN_TO_FINISH_MODEL)
                    ChangCtrlStyle();
                else
                    CNCChgCtrlStyleOK();
                D_STCHG_CTRL(WITHOUT_CTRL);
            }
        }
        D_STATE_CHG(RUN_STYLE_CHG_NONE);
        D_STCHG_CTRL_STAGE(COMPLETED_CTRL);
    }
    //====================================================================================================
    //函数说明:   CNC运行方式切换完成时的完全处理
    //====================================================================================================
    void Ipmpl::CNCChgCtrlStyleOK()
    {
        ChangCtrlStyle();
        FM_SPL(0);//取消CNC循环休止中
        FM_OP(0);//取消CNC循环
        I_INIT_ITP(0,INTERP_RESET);
        ManualInterventionFlag(0,0);
    }
    //====================================================================================================
    //函数说明:   CNC运行方式切换时的处理
    //====================================================================================================
    void Ipmpl::ChangCtrlStyle()
    {
        for(unsigned int i = 0; i < *ReadI_AXIS_NUM_ITP(0); i++)
        {
            ManualAxisSelect(0,i,0);
            ManualAxisComplete(0,i,1);

            if(ReadZeroDecAutoSignal(0,i)!= 4)
                ZeroDecAutoSignal(0,i,0);
        }

        FM_SCHK(0);
        HandIsrSegEndForPauseFlag(0,0);
        FM_CHG_MODEL_HMI(1); //切换方式的标志,界面要刷新
        FM_MF(0,MFIN_PLC(0));
        FM_SF(0,SFIN_PLC(0));
        FM_TF(0,TFIN_PLC(0));
        FIN_PLC(1);
        FM_RST(0);
    }

    bool Ipmpl::ProcessPlcChg()
    {
        return true;
    }

    OnLineCmdExcut::OnLineCmdExcut()
    {
        data=NULL;
    }

    OnLineCmdExcut::~OnLineCmdExcut()
    {
        delete data;
    }

    void OnLineCmdExcut::run()
    {
        while(data->_systemRunning)
        {
            data->CNCStateCheck();
            data->ProcessInterpChg();
            if(ReadD_STATE_CHG != RUN_STYLE_CHG_NONE)
                data->CNCWorkModelProcess();      //CNC内部控制状态转换的处理,需要启动对应的模块和任务
            msleep(8);
        }
    }

    OnLineCmdExcut* OnLineCmdExcut::GetCmdExcut()
    {
        static OnLineCmdExcut* theCmdExc=NULL;
        if(NULL==theCmdExc)
        {
            theCmdExc = new OnLineCmdExcut();
        }
        return theCmdExc;
    }

    void OnLineCmdExcut::Init()
    {
        SystemData::SysDataMag::GetSysData()->InitData();
        data = new Ipmpl();
        data->serverCtrl->setCallBack(OnLineCmdExcut::transData, (void *)this);

        data->serverCtrl->startLoop();
        data->plcCtrl->start();
        char InterpPath[256];
        for(int i=0; i<data->_realInterpNum; i++)
        {
            if(data->interpCtrl[i]->InitLoadDLL(InterpPath))
            {
                Set_SETUP_INTERP_CMD(i,1);
                Set_DISA_INTERP_CMD(i,1);
            }
        }

        data->_systemRunning=true;
        FM_RST(1);
        Set_MDI_CMD;
        D_CTRL_PATH(1);
        start();
    }

    int OnLineCmdExcut::transData(ADDR_INFO *addrInfo, int counts, void * pVoid)
    {
        static int value = 1;
        if (value > 100)
        {
            value = 0;
        }
        if (NULL == addrInfo || NULL == pVoid)
        {
            printf("addrInfo or pVoid is NULL\n");
            return -1;
        }
        //从数据池中读取/写入相关数据
        int i = 0;
        OnLineCmdExcut * This = (OnLineCmdExcut *)pVoid;
        SysDataMag* dataManage = SystemData::SysDataMag::GetSysData();
        if (NULL == dataManage)
        {
            printf("can not get SysDataMag class!\n");
            return -1;
        }

        for (i = 0; i < counts; i++)
        {
            if (IS_I_DATA((addrInfo + i)->content))
            {
                if (IS_READ((addrInfo + i)->rw))//float??
                {
                    if (IS_BOOL_DATA((addrInfo->type)))
                    {
                        (addrInfo + i)->data.iData = dataManage->GetIData((addrInfo + i)->startPosition);
                    }
                    else
                        (addrInfo + i)->data.fData = dataManage->GetIDataF((addrInfo + i)->startPosition);
                }
                else
                    dataManage->SetIData((addrInfo + i)->startPosition,
                              IS_BOOL_DATA((addrInfo + i)->type) ? (addrInfo + i)->data.iData : (addrInfo + i)->data.fData);
            }
            else if (IS_M_DATA((addrInfo + i)->content))
            {
                if (IS_READ((addrInfo + i)->rw))
                {
                    (addrInfo + i)->data.iData += 1;
                }
                else
                    dataManage->SetMSignalByte((addrInfo + i)->startPosition, (addrInfo + i)->data.iData + '0');
            }
            else if (IS_D_DATA((addrInfo + i)->content))
            {
                if (IS_READ((addrInfo + i)->rw))
                {
                    if (IS_BOOL_DATA((addrInfo->type)))
                    {
                        (addrInfo + i)->data.iData = dataManage->GetDData((addrInfo + i)->startPosition);
                    }
                    else
                        (addrInfo + i)->data.fData = dataManage->GetDDataF((addrInfo + i)->startPosition);
                }
                else
                    dataManage->SetDData((addrInfo + i)->startPosition,
                              IS_BOOL_DATA((addrInfo + i)->type) ? (addrInfo + i)->data.iData : (addrInfo + i)->data.fData);
            }
            else
            {

            }
        }
        value++;
        return 0;
    }
}
