#ifndef DEFSYSSIGNALANDDATA_H
#define DEFSYSSIGNALANDDATA_H

#include "systemdatamanager.h"
#include "math.h"

#define INP_GROUP                     4
#define PLC_GROUP                     4
#define PLC_NUM_GRP                   8
#define PLC_ALL_NUM                       (PLC_NUM_GRP*PLC_GROUP)
#define MOTOR_NUM                     16
#define AXIS_MAX                      MOTOR_NUM
#define CRD_AXIS_MAX                  6

#define REAL_AXIS_NUM                 3

//==============================================================M Signal Start==============================================================================//
#define CMD_M_SADDR    768
#define CFM_M_SADDR    1024
#define ALM_M_SADDR    1536

//M Signal Write from PLC
#define Set_MDI_PLC          TheSysData()->SetMSignalByte(0,1)
#define Set_AUTO_PLC         TheSysData()->SetMSignalByte(0,2)
#define Set_MANUAL_PLC       TheSysData()->SetMSignalByte(0,4)
#define Set_HOME_PLC(value)    TheSysData()->SetMSignalByte(0,8)
#define Set_HANDWHEEL_PLC(value)    TheSysData()->SetMSignalByte(0,16)
#define Set_STEP_PLC(value)    TheSysData()->SetMSignalByte(0,32)

#define Set_DEBUG_PLC(value)        TheSysData()->SetMSignal(9,value)
#define Set_SingleSeg_PLC(value)    TheSysData()->SetMSignal(10,value)//单程序段信号
#define Set_SkipSeg_PLC(value)    TheSysData()->SetMSignal(11,value)//可选程序段跳过信号
#define Set_DRN_PLC(value)    TheSysData()->SetMSignal(12,value)//空运行信号
#define Set_LOCK_PLC(value)    TheSysData()->SetMSignal(13,value) //全轴机床锁住信号

//MAX AXIS NUM=16
//use: JOG HOME STEP HANDWHEEL
#define Set_ClearAxisSel_PLC()        TheSysData()->SetMSignalWord(16,0)   //+
#define Set_SelPosAxis_PLC(axisNo)    TheSysData()->SetBitMSignal2Byte(16,axisNo)   //手动/回零 轴 +方向选择信号
#define Set_SelNegAxis_PLC(axisNo)    TheSysData()->SetBitMSignal2Byte(32,axisNo)   //手动/回零 轴 -方向选择信号
#define Set_SelExcPosAxis_PLC(axisNo) TheSysData()->SetMSignalWord(16,WordBit(axisNo))   //单步/手轮 轴 +方向选择信号
#define Set_SelExcNegAxis_PLC(axisNo) TheSysData()->SetMSignalWord(16,WordBit(16+axisNo))   //单步/手轮 轴 -方向选择信号
#define Set_MANUAL_POS_PLC(value)     TheSysData()->SetMSignal(48,value)
#define Set_MANUAL_NEG_PLC(value)     TheSysData()->SetMSignal(49,value)

#define Set_HANDWHEEL001_PLC(value)   TheSysData()->SetMSignal(52,value)
#define Set_HANDWHEEL010_PLC(value)   TheSysData()->SetMSignal(53,value)
#define Set_HANDWHEEL100_PLC(value)   TheSysData()->SetMSignal(54,value)
#define Set_HANDWHEEL_EMG_PLC(value)  TheSysData()->SetMSignal(55,value)
#define Set_HANDWHEEL_ALRM_PLC(value) TheSysData()->SetMSignal(56,value)

#define Set_STEP001_PLC(value)        TheSysData()->SetMSignal(58,value)
#define Set_STEP010_PLC(value)        TheSysData()->SetMSignal(59,value)
#define Set_STEP100_PLC(value)        TheSysData()->SetMSignal(60,value)

#define Set_ST_PLC(value)             TheSysData()->SetMSignal(61,value)//自动运行启动信号
#define Set_SP_PLC(value)             TheSysData()->SetMSignal(62,value)//进给保持信号
#define Set_ESP_PLC(value)            TheSysData()->SetMSignal(63,value)//紧急停止信号
#define Set_ERS_PLC(value)            TheSysData()->SetMSignal(64,value)//外部复位信号
#define Set_SRN_PLC(value)            TheSysData()->SetMSignal(65,value)//程序再启动信号
#define Set_AFL_PLC(value)            TheSysData()->SetMSignal(66,value)//辅助功能锁住信号
#define Set_RELEASE_PLC(value)        TheSysData()->SetMSignal(67,value) //超程释放信号

//grp 4(0~3)
#define Set_END_PLC(grp,value)        TheSysData()->SetMSignal(70+grp*8,value) //M30程序结束信号
#define Set_M02END_PLC(grp,value)     TheSysData()->SetMSignal(71+grp*8,value) //M02程序结束信号
#define Set_MSP_PLC(grp,value)        TheSysData()->SetMSignal(72+grp*8,value) //M01触发的进给保持启动信号
#define Set_FIN_PLC(grp,value)        TheSysData()->SetMSignal(73+grp*8,value) //all辅助功能结束信号
#define Set_MFIN_PLC(grp,value)		  TheSysData()->SetMSignal(74+grp*8,value) //M辅助功能结束信号
#define Set_MFIN2_PLC(grp,value)	  TheSysData()->SetMSignal(75+grp*8,value) //第二M辅助功能结束信号
#define Set_SFIN_PLC(grp,value)		  TheSysData()->SetMSignal(76+grp*8,value) //spindle功能结束信号
#define Set_TFIN_PLC(grp,value)		  TheSysData()->SetMSignal(77+grp*8,value) //tool功能结束信号

#define Set_DEC_PLC(value)		      TheSysData()->SetMSignal2Byte(112,value) //参考点返回用减速信号
#define Set_DEC_AXIS(axisNo)	      TheSysData()->SetBitMSignal2Byte(112,axisNo) //参考点返回用减速信号
#define Set_ClearDEC_AXIS(axisNo)	  TheSysData()->ClearBitMSignal2Byte(112,axisNo) //参考点返回用减速信号

#define Set_ClearLP_PLC(axisNo)	      TheSysData()->ClearMSignal2Byte(144,axisNo) //clear超程信号（硬）*+L1~*+L16
#define Set_ClearLN_PLC(axisNo)	      TheSysData()->ClearMSignal2Byte(144,axisNo) //clear超程信号（硬）*+L1~*+L16
#define Set_LP_PLC(axisNo)		      TheSysData()->SetBitMSignal2Byte(144,axisNo) //超程信号（硬）*+L1~*+L16
#define Set_LN_PLC(axisNo)		      TheSysData()->SetBitMSignal2Byte(160,axisNo) //超程信号（硬）*-L1~*-L16

//M Signal Write from CMD
#define Set_MDI_CMD                   TheSysData()->SetMSignalByte(CMD_M_SADDR,1)
#define Set_AUTO_CMD                  TheSysData()->SetMSignalByte(CMD_M_SADDR,2)
#define Set_MANUAL_CMD                TheSysData()->SetMSignalByte(CMD_M_SADDR,4)
#define Set_HOME_CMD                  TheSysData()->SetMSignalByte(CMD_M_SADDR,8)

#define Set_DEBUG_CMD(value)          TheSysData()->SetMSignal(CMD_M_SADDR+9,value)
#define Set_SingleSeg_CMD(value)      TheSysData()->SetMSignal(CMD_M_SADDR+10,value)//单程序段信号
#define Set_SkipSeg_CMD(value)        TheSysData()->SetMSignal(CMD_M_SADDR+11,value)//可选程序段跳过信号
#define Set_DRN_CMD(value)            TheSysData()->SetMSignal(CMD_M_SADDR+12,value)//空运行信号
#define Set_LOCK_CMD(value)           TheSysData()->SetMSignal(CMD_M_SADDR+13,value) //全轴机床锁住信号

#define Set_ClearAxisSel_CMD()        TheSysData()->SetMSignalWord(CMD_M_SADDR+16,0)   //+
#define Set_SelPosAxis_CMD(axisNo)    TheSysData()->SetBitMSignal2Byte(CMD_M_SADDR+16,axisNo)   //手动/回零 轴 +方向选择信号
#define Set_SelNegAxis_CMD(axisNo)    TheSysData()->SetBitMSignal2Byte(CMD_M_SADDR+32,axisNo)   //手动/回零 轴 -方向选择信号
#define Set_KillAxis_CMD(axisNo)	  TheSysData()->SetBitMSignal2Byte(CMD_M_SADDR+48,axisNo) //clear enable

#define Set_ST_CMD(value)             TheSysData()->SetMSignal(CMD_M_SADDR+70,value)//自动运行启动信号
#define Set_SP_CMD(value)             TheSysData()->SetMSignal(CMD_M_SADDR+71,value)//进给保持信号

#define Set_INIT_CMD(value)           TheSysData()->SetMSignal(CMD_M_SADDR+75,value)//init
#define Set_RESTRAT_CMD(value)        TheSysData()->SetMSignal(CMD_M_SADDR+76,value)//RESTRAT信号
#define Set_ERS_CMD(value)            TheSysData()->SetMSignal(CMD_M_SADDR+77,value)//复位信号
#define Set_SRN_CMD(value)            TheSysData()->SetMSignal(CMD_M_SADDR+78,value)//程序再启动信号
#define Set_AFL_CMD(value)            TheSysData()->SetMSignal(CMD_M_SADDR+79,value)//辅助功能锁住信号
#define Set_ESP_CMD(value)            TheSysData()->SetMSignal(CMD_M_SADDR+80,value)//急停信号

#define Set_SETUP_INTERP_CMD(i,value) TheSysData()->SetMSignal(CFM_M_SADDR+88+i,value) //setup interp i
#define Set_DISA_INTERP_CMD(i,value)  TheSysData()->SetMSignal(CMD_M_SADDR+92+i,value) //disable

//4 group*8=32 2ms/8ms/32ms/100ms
#define Set_DISA_PLC_CMD(group,no)    TheSysData()->SetBitMSignalByte(CMD_M_SADDR+96+group*8,no) //clear enable
#define Set_ENA_PLC_CMD(group,no)     TheSysData()->ClearBitMSignalByte(CMD_M_SADDR+96+group*8,no) //enable
#define Set_PAUSE_PLC_CMD(group,no)   TheSysData()->SetBitMSignalByte(CMD_M_SADDR+128+group*8,no) //pause
#define Set_RESUME_PLC_CMD(group,no)  TheSysData()->ClearBitMSignalByte(CMD_M_SADDR+128+group*8,no) //RESUME

//M Signal Read
//PLC M Signal
#define CHECK_MODEL_PLC      TheSysData()->GetMSignalByte(0)
#define MDI_PLC          (TheSysData()->GetMSignalByte(0)==1)
#define AUTO_PLC         (TheSysData()->GetMSignalByte(0)==2)
#define MANUAL_PLC       (TheSysData()->GetMSignalByte(0)==4)
#define HOME_PLC         (TheSysData()->GetMSignalByte(0)==8)
#define HANDWHEEL_PLC    (TheSysData()->GetMSignalByte(0)==16)
#define STEP_PLC         (TheSysData()->GetMSignalByte(0)==32)

#define DEBUG_PLC        TheSysData()->GetMSignal(9)
#define SingleSeg_PLC    TheSysData()->GetMSignal(10)//单程序段信号
#define SkipSeg_PLC      TheSysData()->GetMSignal(11)//可选程序段跳过信号
#define DRN_PLC          TheSysData()->GetMSignal(12)//空运行信号
#define LOCK_PLC         TheSysData()->GetMSignal(13) //全轴机床锁住信号

//MAX 16 AXIS
//use: JOG HOME STEP HANDWHEEL
#define SelPosAxis_PLC(axisNo)    TheSysData()->GetBitMSignal2Byte(16,axisNo)   //手动/回零 轴 +方向选择信号
#define SelNegAxis_PLC(axisNo)    TheSysData()->GetBitMSignal2Byte(32,axisNo)   //手动/回零 轴 -方向选择信号
#define SelExcPosAxis_PLC(axisNo)    (TheSysData()->GetMSignalWord(16)==WordBit(axisNo))   //单步/手轮 轴 +方向选择信号
#define SelExcNegAxis_PLC(axisNo)    (TheSysData()->GetMSignalWord(16)==WordBit(16+axisNo))   //单步/手轮 轴 -方向选择信号
#define MANUAL_POS_PLC      TheSysData()->GetMSignal(48)
#define MANUAL_NEG_PLC      TheSysData()->GetMSignal(49)

#define HANDWHEEL001_PLC    ((TheSysData()->GetMSignalByte(52)&0x70)==0x10)
#define HANDWHEEL010_PLC    ((TheSysData()->GetMSignalByte(53)&0x70)==0x20)
#define HANDWHEEL100_PLC    ((TheSysData()->GetMSignalByte(54)&0x70)==0x40)
#define HANDWHEEL_EMG_PLC   TheSysData()->GetMSignal(55)
#define HANDWHEEL_ALRM_PLC  TheSysData()->GetMSignal(56)

#define STEP001_PLC         ((TheSysData()->GetMSignal(58)&0x38)==0x08)
#define STEP010_PLC         ((TheSysData()->GetMSignal(59)&0x38)==0x10)
#define STEP100_PLC         ((TheSysData()->GetMSignal(60)&0x38)==0x20)

#define ST_PLC          TheSysData()->GetMSignal(61)//自动运行启动信号
#define SP_PLC          TheSysData()->GetMSignal(62)//进给保持信号
#define ESP_PLC         TheSysData()->GetMSignal(63)//紧急停止信号
#define ESP_ADDR_PLC    TheSysData()->GetMSignalAddr(63)//紧急停止信号
#define ERS_PLC         TheSysData()->GetMSignal(64)//外部复位信号
#define SRN_PLC         TheSysData()->GetMSignal(65)//程序再启动信号
#define AFL_PLC         TheSysData()->GetMSignal(66)//辅助功能锁住信号
#define RELEASE_PLC     TheSysData()->GetMSignal(67)//超程释放信号

#define END_PLC(grp)        TheSysData()->GetMSignal(70+grp*8) //M30程序结束信号
#define M02END_PLC(grp)     TheSysData()->GetMSignal(71+grp*8) //M02程序结束信号
#define MSP_PLC(grp)        TheSysData()->GetMSignal(72+grp*8) //M01触发的进给保持启动信号
#define FIN_PLC(grp)        TheSysData()->GetMSignal(73+grp*8) //all辅助功能结束信号
#define MFIN_PLC(grp)		TheSysData()->GetMSignal(74+grp*8) //M辅助功能结束信号
#define MFIN2_PLC(grp)		TheSysData()->GetMSignal(75+grp*8) //第二M辅助功能结束信号
#define SFIN_PLC(grp)		TheSysData()->GetMSignal(76+grp*8) //spindle功能结束信号
#define TFIN_PLC(grp)		TheSysData()->GetMSignal(77+grp*8) //tool功能结束信号

#define DEC_PLC				TheSysData()->GetMSignal2Byte(112) //参考点返回用减速信号
#define DEC_AXIS(axisNo)	TheSysData()->GetBitMSignal2Byte(112,axisNo) //参考点返回用减速信号

#define LP_PLC(axisNo)		TheSysData()->GetBitMSignal2Byte(144,axisNo) //超程信号（硬）*+L1~*+L16
#define LN_PLC(axisNo)		TheSysData()->GetBitMSignal2Byte(160,axisNo) //超程信号（硬）*-L1~*-L16

//CMD M Signal
#define CHECK_MODEL_CMD    TheSysData()->GetMSignalByte(CMD_M_SADDR)
#define MDI_CMD            (TheSysData()->GetMSignalByte(CMD_M_SADDR)==1)
#define AUTO_CMD           (TheSysData()->GetMSignalByte(CMD_M_SADDR)==2)
#define MANUAL_CMD         (TheSysData()->GetMSignalByte(CMD_M_SADDR)==4)
#define HOME_CMD           (TheSysData()->GetMSignalByte(CMD_M_SADDR)==8)

#define DEBUG_CMD          TheSysData()->GetMSignal(CMD_M_SADDR+9)
#define SingleSeg_CMD      TheSysData()->GetMSignal(CMD_M_SADDR+10)//单程序段信号
#define SkipSeg_CMD        TheSysData()->GetMSignal(CMD_M_SADDR+11)//可选程序段跳过信号
#define DRN_CMD            TheSysData()->GetMSignal(CMD_M_SADDR+12)//空运行信号
#define LOCK_CMD           TheSysData()->GetMSignal(CMD_M_SADDR+13) //全轴机床锁住信号

#define PROG_READY_CMD     TheSysData()->GetMSignal(CMD_M_SADDR+14)//程序准备好

#define SelPosAxis_CMD(axisNo)  TheSysData()->GetBitMSignalWord(CMD_M_SADDR+16,axisNo)   //手动/回零 轴 +方向选择信号
#define SelNegAxis_CMD(axisNo)  TheSysData()->GetBitMSignalWord(CMD_M_SADDR+16,axisNo)   //手动/回零 轴 -方向选择信号
#define KillAxis_CMD(axisNo)    TheSysData()->GetBitMSignal2Byte(CMD_M_SADDR+48,axisNo) //clear enable

#define ST_CMD        TheSysData()->GetMSignal(CMD_M_SADDR+70)//自动运行启动信号
#define SP_CMD        TheSysData()->GetMSignal(CMD_M_SADDR+71)//进给保持信号

#define INIT_CMD      TheSysData()->GetMSignal(CMD_M_SADDR+75)//init复位信号
#define RESTRAT_CMD   TheSysData()->GetMSignal(CMD_M_SADDR+76)//RESTRAT信号
#define ERS_CMD       TheSysData()->GetMSignal(CMD_M_SADDR+77)//复位信号
#define SRN_CMD       TheSysData()->GetMSignal(CMD_M_SADDR+78)//程序再启动信号
#define AFL_CMD       TheSysData()->GetMSignal(CMD_M_SADDR+79)//辅助功能锁住信号
#define ESP_CMD       TheSysData()->GetMSignal(CMD_M_SADDR+80)//急停信号

#define SETUP_INTERP_CMD(i)  TheSysData()->GetMSignal(CMD_M_SADDR+88+i) //setup interp i
#define DISA_INTERP_CMD(i)   TheSysData()->GetMSignal(CMD_M_SADDR+92+i) //disable Interp i

//4 group*8=32 2ms/8ms/32ms/100ms
#define DISA_PLC_CMD(group,no)   TheSysData()->GetBitMSignalByte(CMD_M_SADDR+96+group*8,no) //clear enable
#define PAUSE_PLC_CMD(group,no)   TheSysData()->GetBitMSignalByte(CMD_M_SADDR+128+group*8,no) //pause

//M Signal Write from CFM
#define FM_SCHK(value)	           TheSysData()->SetMSignal(CFM_M_SADDR+0,value)//语法检查中图形预览
#define FM_ESP(value)              TheSysData()->SetMSignal(CFM_M_SADDR+1,value)	//EmergencyState
#define ReadFM_ESP                 TheSysData()->GetMSignal(CFM_M_SADDR+1)
#define FM_CHG_MODEL_HMI(value)    TheSysData()->SetMSignal(CFM_M_SADDR+2,value)
#define ReadFM_CHG_MODEL_HMI       TheSysData()->GetMSignal(CFM_M_SADDR+2)
#define FM_OPC(value)              TheSysData()->SetMSignal(CFM_M_SADDR+3,value)	//自动运行信号发生改变
#define ReadFM_OPC                 TheSysData()->GetMSignal(CFM_M_SADDR+3)
#define FM_SPL(value)              TheSysData()->SetMSignal(CFM_M_SADDR+4,value)	//进给保持
#define ReadFM_SPL                 TheSysData()->GetMSignal(CFM_M_SADDR+4)
#define FM_STL(value) 	           TheSysData()->SetMSignal(CFM_M_SADDR+5,value)	//循环起动
#define ReadFM_STL                 TheSysData()->GetMSignal(CFM_M_SADDR+5)
#define FM_SA(value)	           TheSysData()->SetMSignal(CFM_M_SADDR+6,value)	//伺服准备好信号
#define ReadFM_SA                  TheSysData()->GetMSignal(CFM_M_SADDR+6)
#define FM_OP(value)	           TheSysData()->SetMSignal(CFM_M_SADDR+7,value)	//自动运行信号
#define ReadFM_OP                  TheSysData()->GetMSignal(CFM_M_SADDR+7)

#define FM_AL(value)	           TheSysData()->SetMSignal(CFM_M_SADDR+8,value)	//报警信号
#define ReadFM_AL                  TheSysData()->GetMSignal(CFM_M_SADDR+8)
#define FM_RST(value)	           TheSysData()->SetMSignal(CFM_M_SADDR+9,value)	//复位信号
#define ReadFM_RST		           TheSysData()->GetMSignal(CFM_M_SADDR+9)	        //复位信号
#define FM_RST_RUNNING(value)	   TheSysData()->SetMSignal(CFM_M_SADDR+10,value)	//复位执行中信号
#define ReadFM_RST_RUNNING		   TheSysData()->GetMSignal(CFM_M_SADDR+10)	        //复位执行中信号
#define FM_PRF(value)	           TheSysData()->SetMSignal(CFM_M_SADDR+11,value)	//程序结束
#define FM_ENB(value)	           TheSysData()->SetMSignal(CFM_M_SADDR+12,value)	//主轴使能信号
#define FM_MA(value)	           TheSysData()->SetMSignal(CFM_M_SADDR+15,value)   //准备就绪信号
#define ReadFM_MA		           TheSysData()->GetMSignal(CFM_M_SADDR+15)         //准备就绪信号

#define FM_RPDO(value)	 TheSysData()->SetMSignal(CFM_M_SADDR+17,value) //快速定位信号
#define FM_SRNMV(value)  TheSysData()->SetMSignal(CFM_M_SADDR+20,value)	//程序再启动信号
#define FM_CUT(value)	 TheSysData()->SetMSignal(CFM_M_SADDR+22,value) //切削进给信号
#define FM_MDRN(value)	 TheSysData()->SetMSignal(CFM_M_SADDR+23,value)	//空运行检测信号
//READ
#define ReadFM_RPDO	     TheSysData()->GetMSignal(CFM_M_SADDR+17)   //快速定位信号
#define ReadFM_SRNMV     TheSysData()->GetMSignal(CFM_M_SADDR+20)	//程序再启动信号
#define ReadFM_CUT	     TheSysData()->GetMSignal(CFM_M_SADDR+22)   //切削进给信号
#define ReadFM_MDRN  	 TheSysData()->GetMSignal(CFM_M_SADDR+23)	//空运行检测信号

#define FM_MODEL(value)  TheSysData()->SetMSignalByte(CFM_M_SADDR+24,value)	//方式选择检测信号

#define FM_MMDI		     TheSysData()->SetMSignalByte(CFM_M_SADDR+24,1)	    //选择MDI手动数据输入确认信号
#define FM_MMEM	         TheSysData()->SetMSignalByte(CFM_M_SADDR+24,2)	    //选择自动运行确认信号
#define FM_MJOG		     TheSysData()->SetMSignalByte(CFM_M_SADDR+24,4)	    //手动连续进给选择确认信号
#define FM_MZRO		     TheSysData()->SetMSignalByte(CFM_M_SADDR+24,8)	    //机械回零选择检测信号
#define FM_MWHEEL	     TheSysData()->SetMSignalByte(CFM_M_SADDR+24,16)	//手脉进给选择确认信号
#define FM_MINC		     TheSysData()->SetMSignalByte(CFM_M_SADDR+24,32)	//增量进给选择确认信号
//READ
#define ReadFM_MODEL     TheSysData()->GetMSignalByte(CFM_M_SADDR+24)	//方式选择检测信号

#define ReadFM_MMDI		     (TheSysData()->GetMSignalByte(CFM_M_SADDR+24)==1)	//选择MDI手动数据输入确认信号
#define ReadFM_MMEM	         (TheSysData()->GetMSignalByte(CFM_M_SADDR+24)==2)	//选择自动运行确认信号
#define ReadFM_MJOG		     (TheSysData()->GetMSignalByte(CFM_M_SADDR+24)==4)	//手动连续进给选择确认信号
#define ReadFM_MZRO		     (TheSysData()->GetMSignalByte(CFM_M_SADDR+24)==8)	//机械回零选择检测信号
#define ReadFM_MWHEEL	     (TheSysData()->GetMSignalByte(CFM_M_SADDR+24)==16)	//手脉进给选择确认信号
#define ReadFM_MINC		     (TheSysData()->GetMSignalByte(CFM_M_SADDR+24)==32)	//增量进给选择确认信号

#define FM_MDEBUG(value)	 TheSysData()->SetMSignal(CFM_M_SADDR+34,value)	    //DEBUG选择确认信号
#define ReadFM_MDEBUG	     TheSysData()->GetMSignal(CFM_M_SADDR+34)	        //DEBUG选择确认信号

#define FM_MBDT(value)	       TheSysData()->SetMSignal(CFM_M_SADDR+35,value)   //跳过任选程序段检测信号
#define FM_MMLK(value)	       TheSysData()->SetMSignal(CFM_M_SADDR+36,value)	 //全轴机床锁住确认信号
#define FM_MSBK(value)	       TheSysData()->SetMSignal(CFM_M_SADDR+38,value)	 //单程序段确认信号
#define FM_MAFL(value)	       TheSysData()->SetMSignal(CFM_M_SADDR+39,value)	 //辅助功能锁住确认信号
#define FM_MREF(value)	       TheSysData()->SetMSignal(CFM_M_SADDR+40,value)	 //手动返回参考点确认信号

#define ReadFM_MBDT	           TheSysData()->GetMSignal(CFM_M_SADDR+35)  //跳过任选程序段检测信号
#define ReadFM_MMLK	           TheSysData()->GetMSignal(CFM_M_SADDR+36)	 //全轴机床锁住确认信号
#define ReadFM_MSBK	           TheSysData()->GetMSignal(CFM_M_SADDR+38)	 //单程序段确认信号
#define ReadFM_MAFL	           TheSysData()->GetMSignal(CFM_M_SADDR+39)	 //辅助功能锁住确认信号
#define ReadFM_MREF  	       TheSysData()->GetMSignal(CFM_M_SADDR+40)	 //手动返回参考点确认信号

#define FM_SERVO_DO(on)          TheSysData()->SetMSignal(CFM_M_SADDR+45,on)  //SERVER ON
#define FM_NCBUF_DO(on)          TheSysData()->SetMSignal(CFM_M_SADDR+46,on)  //NC BUF ON
#define ReadFM_SERVO_DO          TheSysData()->GetMSignal(CFM_M_SADDR+45)
#define ReadFM_NCBUF_DO          TheSysData()->GetMSignal(CFM_M_SADDR+46)

//Interp i=(0~3)
#define FM_DISA_ITP(i,value)     TheSysData()->SetMSignal(CFM_M_SADDR+50+i*100,value)    //confirm disable interp thread 1
#define ReadFM_DISA_ITP(i)       TheSysData()->GetMSignal(CFM_M_SADDR+50+i*100)          //
#define FM_RUNNING_ITP(i,value)  TheSysData()->SetMSignal(CFM_M_SADDR+51+i*100,value)    //interp is running
#define ReadFM_RUNNING_ITP(i)    TheSysData()->GetMSignal(CFM_M_SADDR+51+i*100)          //
#define FM_CANDO_ITP(i,value)       TheSysData()->SetMSignal(CFM_M_SADDR+52+i*100,value)    //interp is allowed to perform
#define ReadFM_CANDO_ITP(i)         TheSysData()->GetMSignal(CFM_M_SADDR+52+i*100)          //
#define FM_PROG_READY_ITP(i,value)  TheSysData()->SetMSignal(CFM_M_SADDR+52+i*100,value)    //NO PROG IS READY
#define ReadFM_PROG_READY_ITP(i)    TheSysData()->GetMSignal(CFM_M_SADDR+52+i*100)          //
#define FM_CAN_DECODE_ITP(i,value)  TheSysData()->SetMSignal(CFM_M_SADDR+53+i*100,value)    //CAN DECODE
#define ReadFM_CAN_DECODE_ITP(i)    TheSysData()->GetMSignal(CFM_M_SADDR+53+i*100)          //
//MST处理
#define FM_MF(i,value)	      TheSysData()->SetMSignal(CFM_M_SADDR+56+i*100,value)	//辅助功能选通信号
#define FM_SF(i,value)	      TheSysData()->SetMSignal(CFM_M_SADDR+58+i*100,value)	//主轴速度选通信号
#define FM_TF(i,value)	      TheSysData()->SetMSignal(CFM_M_SADDR+59+i*100,value)	//刀具功能选通信号

#define FM_MSTA(i,value)      TheSysData()->SetMSignal(CFM_M_SADDR+62+i*100,value)  //向MST代码执行单元通知系统处于报警状态

#define ReadFM_MF(i)          TheSysData()->GetMSignal(CFM_M_SADDR+56+i*100)
#define ReadFM_SF(i)          TheSysData()->GetMSignal(CFM_M_SADDR+58+i*100)
#define ReadFM_TF(i)          TheSysData()->GetMSignal(CFM_M_SADDR+59+i*100)

#define FM_DM30(i,value)      TheSysData()->SetMSignal(CFM_M_SADDR+64+i*100,value)  //	M30解码信号
#define FM_DM2(i,value)       TheSysData()->SetMSignal(CFM_M_SADDR+65+i*100,value)  //	M02解码信号
#define FM_DM1(i,value)       TheSysData()->SetMSignal(CFM_M_SADDR+66+i*100,value)  //	M01解码信号
#define FM_DM0(i,value)       TheSysData()->SetMSignal(CFM_M_SADDR+67+i*100,value)  //	M00解码信号
#define FM_DM5(i,value)       TheSysData()->SetMSignal(CFM_M_SADDR+68+i*100,value)  //	M05解码信号
#define FM_DM3(i,value)       TheSysData()->SetMSignal(CFM_M_SADDR+69+i*100,value)  //	M03解码信号
#define FM_DM4(i,value)       TheSysData()->SetMSignal(CFM_M_SADDR+70+i*100,value)  //	M04解码信号

#define FM_SPALM(i,value)          TheSysData()->SetMSignal(CFM_M_SADDR+74+i*100,value)	    //主轴报警信号
#define FM_SST(i,value)		     TheSysData()->SetMSignal(CFM_M_SADDR+75+i*100,value)	    //主轴零速信号
#define FM_SARA(i,value)		     TheSysData()->SetMSignal(CFM_M_SADDR+76+i*100,value)	//主轴速度到达信号

#define FM_MCODE(i,value)          TheSysData()->SetMSignalWord(CFM_M_SADDR+80+i*100,value)	    //辅助功能代码信号
#define FM_SCODE(i,value)          TheSysData()->SetMSignalWord(CFM_M_SADDR+112+i*100,value)	//主轴功能代码信号
#define FM_TCODE(i,value)          TheSysData()->SetMSignalWord(CFM_M_SADDR+144+i*100,value)	//刀具功能代码信号

//PLC 4*8=32
#define FM_DISA_PLC(group,no)     TheSysData()->SetBitMSignalByte(CFM_M_SADDR+600+group*8,no)   //confirm disable plc
#define FM_ENA_PLC(group,no)      TheSysData()->ClearBitMSignalByte(CFM_M_SADDR+600+group*8,no) //confirm enable plc
#define FM_PAUSE_PLC(group,no)    TheSysData()->SetBitMSignalByte(CFM_M_SADDR+632+group*8,no)   //confirm pause plc
#define FM_RESUME_PLC(group,no)   TheSysData()->ClearBitMSignalByte(CFM_M_SADDR+632+group*8,no) //confirm resume plc

//All Axis(all motor) 16
#define FM_ZMEROING(axis,value)   TheSysData()->SetBitMSignal2Byte(CFM_M_SADDR+670,axis,value)     //参考点返回过程中信号
#define ReadFM_ZMEROING(axis)     TheSysData()->GetBitMSignal2Byte(CFM_M_SADDR+670,axis)           //Read参考点返回过程中信号

#define FM_MV(value)             TheSysData()->SetMSignal2Byte(CFM_M_SADDR+686,value)             //轴移动中信号	MV1~ MV16
#define FM_MV_AXIS(axis,value)   TheSysData()->SetBitMSignal2Byte(CFM_M_SADDR+686,axis,value)     //轴移动中信号	MV1~ MV16
#define ReadFM_MV                TheSysData()->GetMSignal2Byte(CFM_M_SADDR+686)                   //Read轴移动中信号	MV1~ MV16
#define ReadFM_MV_AXIS(axis)     TheSysData()->GetBitMSignal2Byte(CFM_M_SADDR+686,axis)           //Read轴移动中信号	MV1~ MV16

#define FM_MVD1(value)            TheSysData()->SetMSignal2Byte(CFM_M_SADDR+702,value)	           //轴移动方向信号
#define FM_MVD1_AXIS(axis,value)  TheSysData()->SetMBitSignal2Byte(CFM_M_SADDR+702,axis,value)     //轴移动方向信号
#define ReadFM_MVD1_AXIS(axis)    TheSysData()->GetBitMSignal2Byte(CFM_M_SADDR+702,axis)	       //Read轴移动方向信号

#define FM_ZRF(value)             TheSysData()->SetMSignal2Byte(CFM_M_SADDR+718,value)	           //参考点建立信号
#define FM_ZRF_AXIS(axis,value)   TheSysData()->SetMBitSignal2Byte(CFM_M_SADDR+718,axis,value)     //参考点建立信号
#define ReadFM_ZRF_AXIS(axis)     TheSysData()->GetBitMSignal2Byte(CFM_M_SADDR+718,axis)	       //Read参考点建立信号

#define FM_OT(value)		          TheSysData()->SetMSignal2Byte(CFM_M_SADDR+734,value)	       //行程限位到达信号（软）
#define FM_OT_N(value)		          TheSysData()->SetMSignal2Byte(CFM_M_SADDR+750,value)	       //行程限位到达信号（软）
#define FM_OT_AXIS(axis,value)	      TheSysData()->SetBitMSignal2Byte(CFM_M_SADDR+734,axis,value) //行程限位到达信号（软）
#define FM_OT_N_AXIS(axis,value)      TheSysData()->SetBitMSignal2Byte(CFM_M_SADDR+750,axis,value) //行程限位到达信号（软）
#define ReadFM_OT_AXIS(axis,value)	  TheSysData()->GetBitMSignal2Byte(CFM_M_SADDR+734,axis)	   //Read行程限位到达信号（软）
#define ReadFM_OT_N_AXIS(axis,value)  TheSysData()->GetBitMSignal2Byte(CFM_M_SADDR+750,axis)	   //Read行程限位到达信号（软）

#define FM_HardLimitCheck(value)	    TheSysData()->SetMSignal2Byte(CFM_M_SADDR+766,value)	       //行程硬限位检查
#define FM_HardLimitCheckA(axis,value)  TheSysData()->SetBitMSignal2Byte(CFM_M_SADDR+766,axis,value)
#define ReadFM_HardLimitCheck   	    TheSysData()->GetMSignal2Byte(CFM_M_SADDR+766)	               //行程硬限位检查
#define ReadFM_HardLimitCheckA(axis)	TheSysData()->GetBitMSignal2Byte(CFM_M_SADDR+766,axis)	       //Read行程硬限位检查
//==============================================================M Signal End===============================================================================//

//==============================================================D Data Start===============================================================================//
#define D_DEC_RATE(value)             TheSysData()->SetDDataF(0,value) //减速倍率
#define ReadD_DEC_RATE                TheSysData()->GetDDataF(0)
#define D_FEED_RATE(value)            TheSysData()->SetDData(1,value) //进给倍率
#define ReadD_FEED_RATE               TheSysData()->GetDData(1)
//运行方式发生改变
#define D_STATE_CHG(value)            TheSysData()->SetDDataU(2,value) //运行方式发生改变
#define ReadD_STATE_CHG               TheSysData()->GetDDataU(2)
//运行方式切换选项
#define RUN_STYLE_CHG_NONE                         0//:  没有改变运行方式
#define RUN_STYLE_CHG_RESET                        1//:  进行复位操作
#define RUN_STYLE_CHG_PAUSE                        4//:  进行暂停操作
#define RUN_STYLE_CHG_AUTO                         5//:  改变到自动方式
#define RUN_STYLE_CHG_MDI                          6//:  改变到MDI方式
#define RUN_STYLE_CHG_MACHZERO                     7//:  改变到机械回零方式
#define RUN_STYLE_CHG_WHEEL                        8//:  改变到手轮方式
#define RUN_STYLE_CHG_STEP                         9//:  改变到单步方式
#define RUN_STYLE_CHG_JOG                          10//:  改变到手动方式
#define RUN_STYLE_CHG_DEBUG_ON                     15//: 打开DEBUG方式
#define RUN_STYLE_CHG_DRN_ON                       16//: 打开空运行方式
#define RUN_STYLE_CHG_MCLOCK_ON                    17//: 打开机床锁
#define RUN_STYLE_CHG_MSTLOCK_ON                   18//: 打开辅助锁
#define RUN_STYLE_CHG_SINGLE_ON                    19//: 打开单段
#define RUN_STYLE_CHG_DEBUG_OFF                    25//: 关闭DEBUG方式
#define RUN_STYLE_CHG_DRN_OFF                      26//: 关闭空运行方式
#define RUN_STYLE_CHG_MCLOCK_OFF                   27//: 关闭机床锁
#define RUN_STYLE_CHG_MSTLOCK_OFF                  28//: 关闭辅助锁
#define RUN_STYLE_CHG_SINGLE_OFF                   29//: 关闭单段
#define RUN_STYLE_CHG_ALRAM                        35//: 报警减速处理
#define RUN_STYLE_CHG_ESP                          36//: 急停处理
#define RUN_STYLE_CHG_RE_DECODE                    37//: 重新译码的处理
#define RUN_STYLE_CHG_RE_START                     38//: 重新启动的处理

#define RUN_STYLE_CHG_REVERSE                      50//:  保留

//运行方式切换时的控制
#define D_STCHG_CTRL(value)            TheSysData()->SetDData(3,value) //运行方式发生改变时的控制选项
#define ReadD_STCHG_CTRL               TheSysData()->GetDData(3)
#define WITHOUT_CTRL                     -1
#define CHG_NOW_MODEL                     0
#define STOP_NOW_MODEL                    1
#define DEC_STOP_MODEL                    2
#define PROG_RUN_TO_FINISH_MODEL          3
#define PULSE_SEND_TO_FINISH_MODEL        4
#define REVERSE_MODEL                     999

//运行方式切换时的阶段
#define D_STCHG_CTRL_STAGE(value)            TheSysData()->SetDDataU(3,value) //运行方式发生改变时的控制选项
#define ReadD_STCHG_CTRL_STAGE               TheSysData()->GetDDataU(3)
//运行方式切换时的阶段选项
#define COMPLETED_CTRL                 0
#define STOPED_CTRL_STAGE              1
#define STOPPING_CTRL_STAGE            2
#define STOP_READY_CTRL_STAGE          3
#define PAUSE_CTRL_STAGE               4
#define RUNNING_CTRL_STAGE             5
#define START_RUN_CTRL_STAGE           6

#define D_AUTO_ISR_CHECK(value)       TheSysData()->SetDDataU(4,value) //自动运行暂停"检查"手动干预标志(单步、手轮、手动统称为手动)
#define ReadD_AUTO_ISR_CHECK          TheSysData()->GetDDataU(4)

#define D_PAUSE_CTRL_STYLE(value)     TheSysData()->SetDDataU(5,value)//自动运行暂停"检查"时的运行方式: MDI or AUTO
#define ReadD_PAUSE_CTRL_STYLE        TheSysData()->GetDDataU(5)

#define D_RESET_TIME(time)            TheSysData()->SetDDataU(6,time)//复位执行时间
#define ReadD_RESET_TIME              TheSysData()->GetDDataU(6)

#define D_CtrlStyleCheck(time)        TheSysData()->SetDDataU(7,time)//运行方式发生改变时的"检查"时间
#define ReadD_CtrlStyleCheck          TheSysData()->GetDDataU(7)

#define D_ALARM(no)                   TheSysData()->SetDDataU(10,no)//报警
#define ReadD_ALARM                   TheSysData()->GetDDataU(10)

#define D_CTRL_PATH(value)            TheSysData()->SetDDataU(11,value)//控制渠道：1--CMD  0--PLC
#define ReadD_CTRL_PATH               TheSysData()->GetDDataU(11)//控制渠道：1--CMD  0--PLC

#define D_RE_DECODE_ITP(i,value)      TheSysData()->SetDDataU(20+i,value)    //RE DECODE
#define ReadD_RE_DECODE_ITP(i)        TheSysData()->GetDDataU(20+i)          //

#define D_DecodeResetFlag_ITP(i,value)      TheSysData()->SetDDataU(24+i,value)    //RE DECODE FLAG
#define ReadD_DecodeResetFlag_ITP(i)        TheSysData()->GetDDataU(24+i)          //

#define D_DecodeOverCurTimes_ITP(i,value)       TheSysData()->SetDDataU(28+i,value)
#define ReadD_DecodeOverCurTimes_ITP(i)         TheSysData()->GetDDataU(28+i)          //

#define D_DEVICE_START_ADDR           (DMAX_NUM/2)
//LASER(LAS)
#define DLAS_ALM(value)               TheSysData()->SetDData(D_DEVICE_START_ADDR,value) //激光器报警号
#define ReadDLAS_ALM                  TheSysData()->GetDData(D_DEVICE_START_ADDR)
#define DLAS_P(value)                 TheSysData()->SetDData(D_DEVICE_START_ADDR+1,value) //激光器控制参数P
#define ReadDLAS_P                    TheSysData()->GetDData(D_DEVICE_START_ADDR+1)
#define DLAS_Q(value)                 TheSysData()->SetDData(D_DEVICE_START_ADDR+2,value) //激光器控制参数Q
#define ReadDLAS_Q                    TheSysData()->GetDData(D_DEVICE_START_ADDR+2)
#define DLAS_R(value)                 TheSysData()->SetDData(D_DEVICE_START_ADDR+3,value) //激光器控制参数R
#define ReadDLAS_R                    TheSysData()->GetDData(D_DEVICE_START_ADDR+3)
#define DLAS_POWER(value)             TheSysData()->SetDData(D_DEVICE_START_ADDR+4,value) //激光器实际功率
#define ReadDLAS_POWER                TheSysData()->GetDData(D_DEVICE_START_ADDR+4)

#define DLAS_TB_A_TPT(value)          TheSysData()->SetDData(D_DEVICE_START_ADDR+10,value) //涡轮泵轴承A段温度 turbopump bearing a temperature
#define ReadDLAS_TB_A_TPT             TheSysData()->GetDData(D_DEVICE_START_ADDR+10)
#define DLAS_TB_B_TPT(value)          TheSysData()->SetDData(D_DEVICE_START_ADDR+11,value) //涡轮泵轴承B段温度 turbopump bearing b temperature
#define ReadDLAS_TB_B_TPT             TheSysData()->GetDData(D_DEVICE_START_ADDR+11)
#define DLAS_CAV_PRE(value)           TheSysData()->SetDData(D_DEVICE_START_ADDR+12,value) //谐振腔压力 Cavity pressure
#define ReadDLAS_CAV_PRE              TheSysData()->GetDData(D_DEVICE_START_ADDR+12)
#define DLAS_LEAK_INIT_PRE(value)     TheSysData()->SetDData(D_DEVICE_START_ADDR+13,value) //检测漏气初始压力 Leak Detection of initial pressure
#define ReadDLAS_LEAK_INIT_PRE        TheSysData()->GetDData(D_DEVICE_START_ADDR+13)
#define DLAS_LEAK_FINAL_PRE(value)    TheSysData()->SetDData(D_DEVICE_START_ADDR+14,value) //检测漏气最终压力 Leak Detection final pressure
#define ReadDLAS_LEAK_FINAL_PRE       TheSysData()->GetDData(D_DEVICE_START_ADDR+14)
#define DLAS_LEAK_RATE(value)         TheSysData()->SetDData(D_DEVICE_START_ADDR+15,value) //漏气率
#define ReadDLAS_LEAK_RATE            TheSysData()->GetDData(D_DEVICE_START_ADDR+15)
#define DLAS_TBP_PARA(value)          TheSysData()->SetDData(D_DEVICE_START_ADDR+16,value) //涡轮泵测试结束参数值 turbopump para
#define ReadDLAS_TBP_PARA             TheSysData()->GetDData(D_DEVICE_START_ADDR+16)
#define DLAS_TBP_CF_PARA(value)       TheSysData()->SetDData(D_DEVICE_START_ADDR+17,value) //涡轮泵测试结束确认参数值
#define ReadDLAS_TBP_CF_PARA          TheSysData()->GetDData(D_DEVICE_START_ADDR+17)
#define DLAS_FLUSH_TIMES_SET(value)   TheSysData()->SetDData(D_DEVICE_START_ADDR+18,value) //冲洗次数参数值 Flush times
#define ReadDLAS_FLUSH_TIMES_SET      TheSysData()->GetDData(D_DEVICE_START_ADDR+18)
#define DLAS_FLUSH_TIMES(value)       TheSysData()->SetDData(D_DEVICE_START_ADDR+19,value) //冲洗次数
#define ReadDLAS_FLUSH_TIMES          TheSysData()->GetDData(D_DEVICE_START_ADDR+19)
#define DLAS_FLUSH_CP_SET(value)      TheSysData()->SetDData(D_DEVICE_START_ADDR+20,value) //冲洗完成参数值
#define ReadDLAS_FLUSH_CP_SET         TheSysData()->GetDData(D_DEVICE_START_ADDR+20)
#define DLAS_OFFGAS_MIN_PRE(value)    TheSysData()->SetDData(D_DEVICE_START_ADDR+21,value) //抽气压力最小设定值（10mbar) min setting as off-gas pressure
#define ReadDLAS_OFFGAS_MIN_PRE       TheSysData()->GetDData(D_DEVICE_START_ADDR+21)
#define DLAS_FOFFGAS_MAX_PRE(value)   TheSysData()->SetDData(D_DEVICE_START_ADDR+22,value) //快速抽气完成时最大设定压力（500mbar) max setting as fast off-gas pressure
#define ReadDLAS_FOFFGAS_MAX_PRE      TheSysData()->GetDData(D_DEVICE_START_ADDR+22)
#define DLAS_ENA_PRE_P(value)         TheSysData()->SetDData(D_DEVICE_START_ADDR+23,value) //PID比例阀使能压力设定值（135mbar)
#define ReadDLAS_ENA_PRE_P            TheSysData()->GetDData(D_DEVICE_START_ADDR+23)

//==============================================================D Data End=================================================================================//

//==============================================================I Data Start===============================================================================//
#define STATE_I_SADDR    2048
//==============================================================ctrl para start===================================================================//
// NC ROT BUF
#define I_NCPROG_ROTBUF(value)           TheSysData()->SetIData(0,value) //缓冲区大小
#define ReadI_NCPROG_ROTBUF              TheSysData()->GetIData(0)
#define I_ROTBUF_TIME(value)             TheSysData()->SetIData(1,value) //缓冲区处理时间
#define ReadI_ROTBUF_TIME                TheSysData()->GetIData(1)

#define PARA_NUM_ITP                     200
//Interp group(0~3)
#define I_AXIS_NUM_ITP(grp,num)          TheSysData()->SetIData(10+grp*PARA_NUM_ITP,num)      //编程轴数
#define I_AXIS_NAME_ITP(grp,no,name)     TheSysData()->SetIData(12+grp*PARA_NUM_ITP+no,name)      //控制轴1~6的编程名字(X/Y/Z/U/V/W/A/B/C)
#define I_AXIS_TYPE_ITP(grp,no,type)     TheSysData()->SetIData(18+grp*PARA_NUM_ITP+no,type)      //控制轴1~6的控制类型(直线轴1、旋转轴2、直线定位轴3、旋转定位轴4)
#define I_AXIS_MOTOR1_ITP(grp,no,motor)  TheSysData()->SetIData(24+grp*PARA_NUM_ITP+2*no,motor)   //控制轴1~6的主电机号 1~16 0无效
#define I_AXIS_MOTOR2_ITP(grp,no,motor)  TheSysData()->SetIData(30+grp*PARA_NUM_ITP+2*no+1,motor) //控制轴1~6的副电机号 1~16 0无效
#define I_XY_ANGLE_ITP(grp,ang)          TheSysData()->SetIDataF(36+grp*PARA_NUM_ITP,ang)      //控制轴X/Y角度
#define I_YZ_ANGLE_ITP(grp,ang)          TheSysData()->SetIDataF(37+grp*PARA_NUM_ITP,ang)      //控制轴Y/Z角度
#define I_ROT_X_ITP(grp,x)               TheSysData()->SetIDataF(38+grp*PARA_NUM_ITP,x)      //旋转轴心X偏差
#define I_ROT_Y_ITP(grp,y)               TheSysData()->SetIDataF(39+grp*PARA_NUM_ITP,y)      //旋转轴心Y偏差
#define I_ROT_Z_ITP(grp,z)               TheSysData()->SetIDataF(40+grp*PARA_NUM_ITP,z)      //旋转轴心Z偏差
#define I_ROT_TX_ITP(grp,x)              TheSysData()->SetIDataF(41+grp*PARA_NUM_ITP,x)      //旋转刀心X偏差
#define I_ROT_TY_ITP(grp,y)              TheSysData()->SetIDataF(42+grp*PARA_NUM_ITP,y)      //旋转刀心Y偏差
#define I_ROT_TZ_ITP(grp,z)              TheSysData()->SetIDataF(43+grp*PARA_NUM_ITP,z)      //旋转刀心Z偏差
#define I_MAC_TYPE_ITP(grp,type)         TheSysData()->SetIDataF(44+grp*PARA_NUM_ITP,type)      //控制类型选择: 1--3轴铣削  2--3轴激光切割  3--3轴龙门铣削  4--3轴龙门激光切割
                                                                                      //5--5轴铣削  6--5轴激光切割 7--5轴龙门铣削  8--5轴龙门激光切割
//Read
#define ReadI_AXIS_NUM_ITP(grp)         TheSysData()->GetIDataAddr(10+grp*PARA_NUM_ITP)      //编程轴数
#define ReadI_AXIS_NAME_ITP(grp,no)     TheSysData()->GetIDataAddr(12+grp*PARA_NUM_ITP+no)      //控制轴1~6的编程名字(X/Y/Z/U/V/W/A/B/C)
#define ReadI_AXIS_TYPE_ITP(grp,no)     TheSysData()->GetIData(18+grp*PARA_NUM_ITP+no)      //控制轴1~6的控制类型(直线轴1、旋转轴2、直线定位轴3、旋转定位轴4)
#define ReadI_AXIS_MOTOR_ITP(grp,no,slave)   TheSysData()->GetIData(24+grp*PARA_NUM_ITP+2*no+slave)   //控制轴1~6的主/副电机号 no --1~16 0无效, slave 0--主电机 1--副电机
#define ReadI_XY_ANGLE_ITP(grp)         TheSysData()->GetIDataF(36+grp*PARA_NUM_ITP)      //控制轴X/Y角度
#define ReadI_YZ_ANGLE_ITP(grp)         TheSysData()->GetIDataF(37+grp*PARA_NUM_ITP)      //控制轴Y/Z角度
#define ReadI_ROT_X_ITP(grp)            TheSysData()->GetIDataF(38+grp*PARA_NUM_ITP)      //旋转轴心X偏差
#define ReadI_ROT_Y_ITP(grp)            TheSysData()->GetIDataF(39+grp*PARA_NUM_ITP)      //旋转轴心Y偏差
#define ReadI_ROT_Z_ITP(grp)            TheSysData()->GetIDataF(40+grp*PARA_NUM_ITP)      //旋转轴心Z偏差
#define ReadI_ROT_TX_ITP(grp)           TheSysData()->GetIDataF(41+grp*PARA_NUM_ITP)      //旋转刀心X偏差
#define ReadI_ROT_TY_ITP(grp)           TheSysData()->GetIDataF(42+grp*PARA_NUM_ITP)      //旋转刀心Y偏差
#define ReadI_ROT_TZ_ITP(grp)           TheSysData()->GetIDataF(43+grp*PARA_NUM_ITP)      //旋转刀心Z偏差
#define ReadI_MAC_TYPE_ITP(grp)         TheSysData()->GetIDataF(44+grp*PARA_NUM_ITP)      //控制类型选择: 1--3轴铣削  2--3轴激光切割  3--3轴龙门铣削  4--3轴龙门激光切割
                                                                                      //5--5轴铣削  6--5轴激光切割 7--5轴龙门铣削  8--5轴龙门激光切割

#define I_MAC5_TYPE_ITP(grp,type)        TheSysData()->SetIData(45+grp*PARA_NUM_ITP,type)     //5轴控制类型
#define ReadI_MAC5_TYPE_ITP(grp)         TheSysData()->GetIData(45+grp*PARA_NUM_ITP)          //5轴控制类型

#define I_INIT_ITP(grp,state)            TheSysData()->SetIData(47+grp*PARA_NUM_ITP,state)         //插补任务是否初始化
#define ReadI_INIT_ITP(grp)              TheSysData()->GetIData(47+grp*PARA_NUM_ITP)               //插补任务是否初始化
enum InterpCtrlModel
{
    INTERP_INVALID = 0,
    INTERP_ALARM,
    INTERP_EMERGENCY,
    INTERP_RESET_START,
    INTERP_CYCLE_START,
    INTERP_RESET_SINGLE_START,
    INTERP_SINGLE_START,
    INTERP_FEED_HOLD,
    INTERP_RESET
};

#define I_PRE_CTRL_STATE_ITP(grp,state)         TheSysData()->SetIData(48+grp*PARA_NUM_ITP,state)         //预处理控制状态
#define I_INTERP_CTRL_STATE_ITP(grp,state)      TheSysData()->SetIData(49+grp*PARA_NUM_ITP,state)         //插补控制状态
#define ReadI_PRE_CTRL_STATE_ITP(grp)           TheSysData()->GetIData(48+grp*PARA_NUM_ITP)         //预处理控制状态
#define ReadI_INTERP_CTRL_STATE_ITP(grp)        TheSysData()->GetIData(49+grp*PARA_NUM_ITP)         //插补控制状态

#define I_LOOKBUF_ITP(grp,segNum)          TheSysData()->SetIData(50+grp*PARA_NUM_ITP,segNum)  //前瞻缓冲区设定段数
#define I_LOOKBUF_LEN_ITP(grp,len)         TheSysData()->SetIDataF(51+grp*PARA_NUM_ITP,len)    //前瞻缓冲区长度限制
#define I_LOOK_TIME_ITP(grp,time)          TheSysData()->SetIData(52+grp*PARA_NUM_ITP,time)    //前瞻限定时间
#define I_CONTOUR_ACCURACY_ITP(grp,acc)    TheSysData()->SetIDataF(53+grp*PARA_NUM_ITP,acc)    //轮廓精度
#define I_ARRIVE_ACCURACY_ITP(grp,acc)     TheSysData()->SetIDataF(54+grp*PARA_NUM_ITP,acc)    //到位精度
#define I_SMALLLINES_LEN_ITP(grp,len)      TheSysData()->SetIDataF(55+grp*PARA_NUM_ITP,len)    //小线段判定长度
#define I_SMALLLINES_ANGLE_ITP(grp,ang)    TheSysData()->SetIDataF(56+grp*PARA_NUM_ITP,ang)    //小线段限定角度
#define I_SMALLLINES_OMIT_LEN_ITP(grp,len)    TheSysData()->SetIDataF(57+grp*PARA_NUM_ITP,len) //小线段限定可忽略(合并)长度
#define I_SMALLLINES_CURVES_LEN_ITP(grp,len)  TheSysData()->SetIDataF(58+grp*PARA_NUM_ITP,len) //小线段限定曲线长度
#define I_TRANS_ANGLE_ITP(grp,ang)         TheSysData()->SetIDataF(59+grp*PARA_NUM_ITP,ang)    //拐角过渡角度限制
#define I_ARC_R_ERR_ITP(grp,err)           TheSysData()->SetIDataF(60+grp*PARA_NUM_ITP,err)    //圆弧半径误差限制
#define I_FEED_LIMIT_ITP(grp,limit)        TheSysData()->SetIDataF(61+grp*PARA_NUM_ITP,limit)  //进给速度限制
#define I_ACC_LIMIT_ITP(grp,limit)         TheSysData()->SetIDataF(62+grp*PARA_NUM_ITP,limit)  //加速度限制
#define I_JERK_LIMIT_ITP(grp,limit)        TheSysData()->SetIDataF(63+grp*PARA_NUM_ITP,limit)  //跃度限制
#define I_STRATEGIES_SEL_ITP(grp,sel)      TheSysData()->SetIData(64+grp*PARA_NUM_ITP,sel)     //strategies(策略) 1--速度优先  2--精度优先  3--均衡控制
#define I_FEED_RATE_ITP(grp,rate)          TheSysData()->SetIDataF(65+grp*PARA_NUM_ITP,rate)    //执行倍率
//Read
#define ReadI_LOOKBUF_ITP(grp)             TheSysData()->GetIDataAddr(50+grp*PARA_NUM_ITP)     //前瞻缓冲区设定段数
#define ReadI_LOOKBUF_LEN_ITP(grp)         TheSysData()->GetIDataFAddr(51+grp*PARA_NUM_ITP)    //前瞻缓冲区长度限制
#define ReadI_LOOK_TIME_ITP(grp)           TheSysData()->GetIDataAddr(52+grp*PARA_NUM_ITP)     //前瞻限定时间
#define ReadI_CONTOUR_ACCURACY_ITP(grp)    TheSysData()->GetIDataFAddr(53+grp*PARA_NUM_ITP)    //轮廓精度
#define ReadI_ARRIVE_ACCURACY_ITP(grp)     TheSysData()->GetIDataFAddr(54+grp*PARA_NUM_ITP)    //到位精度
#define ReadI_SMALLLINES_LEN_ITP(grp)      TheSysData()->GetIDataFAddr(55+grp*PARA_NUM_ITP)    //小线段判定长度
#define ReadI_SMALLLINES_ANGLE_ITP(grp)    TheSysData()->GetIDataFAddr(56+grp*PARA_NUM_ITP)    //小线段限定角度
#define ReadI_SMALLLINES_OMIT_LEN_ITP(grp)    TheSysData()->GetIDataFAddr(57+grp*PARA_NUM_ITP) //小线段限定可忽略(合并)长度
#define ReadI_SMALLLINES_CURVES_LEN_ITP(grp)  TheSysData()->GetIDataFAddr(58+grp*PARA_NUM_ITP) //小线段限定曲线长度
#define ReadI_TRANS_ANGLE_ITP(grp)         TheSysData()->GetIDataFAddr(59+grp*PARA_NUM_ITP)    //拐角过渡角度限制
#define ReadI_ARC_R_ERR_ITP(grp)           TheSysData()->GetIDataFAddr(60+grp*PARA_NUM_ITP)    //圆弧半径误差限制
#define ReadI_FEED_LIMIT_ITP(grp)          TheSysData()->GetIDataFAddr(61+grp*PARA_NUM_ITP)    //进给速度限制
#define ReadI_ACC_LIMIT_ITP(grp)           TheSysData()->GetIDataFAddr(62+grp*PARA_NUM_ITP)    //加速度限制
#define ReadI_JERK_LIMIT_ITP(grp)          TheSysData()->GetIDataFAddr(63+grp*PARA_NUM_ITP)    //跃度限制
#define ReadI_STRATEGIES_SEL_ITP(grp)      TheSysData()->GetIDataAddr(64+grp*PARA_NUM_ITP)    //strategies(策略) 1--速度优先  2--精度优先  3--均衡控制
#define ReadI_FEED_RATE_ITP(grp)           TheSysData()->GetIDataFAddr(65+grp*PARA_NUM_ITP)    //执行倍率

#define I_SEL_ALGORITHM_ITP(grp,sel)       TheSysData()->SetIData(70+grp*PARA_NUM_ITP,sel)  //算法选择  0--不平滑 1--Hermit 2--Bspline 3--NURBS
#define I_ALG_PARA_ITP(grp,no,value)       TheSysData()->SetIDataF(71+grp*PARA_NUM_ITP+no,value)  //算法PARA no--1~10
#define ReadI_SEL_ALGORITHM_ITP(grp)       TheSysData()->GetIDataAddr(70+grp*PARA_NUM_ITP)  //算法选择  0--不平滑 1--Hermit 2--Bspline 3--NURBS
#define ReadI_ALG_PARA_ITP(grp,no)         TheSysData()->GetIDataFAddr(71+grp*PARA_NUM_ITP+no)  //算法PARA no--1~10

#define  ManualInterventionFlag(grp,on)         TheSysData()->SetIData(90+grp*PARA_NUM_ITP,on) //手动干预启动标志
#define  HandIsrSegEndForPauseFlag(grp,on)      TheSysData()->SetIData(91+grp*PARA_NUM_ITP,on)
#define  HandReturnPoint(grp,axis,pos)          TheSysData()->SetIData(92+grp*PARA_NUM_ITP+axis,pos)
#define  HandIsrPointStartFlag(grp,on)          TheSysData()->SetIData(104+grp*PARA_NUM_ITP,on)
#define  HandIsrStartPos(grp,axis,pos)          TheSysData()->SetIData(105+grp*PARA_NUM_ITP+axis,pos)//插补开始时的坐标
//READ
#define  ReadI_ManualInterventionFlag(grp)         TheSysData()->GetIData(90+grp*PARA_NUM_ITP) //手动干预启动标志
#define  ReadI_HandIsrSegEndForPauseFlag(grp)      TheSysData()->GetIData(91+grp*PARA_NUM_ITP)
#define  ReadI_HandReturnPoint(grp,axis)           TheSysData()->GetIData(92+grp*PARA_NUM_ITP+axis)
#define  ReadI_HandIsrPointStartFlag(grp)          TheSysData()->GetIData(104+grp*PARA_NUM_ITP)
#define  ReadI_HandIsrStartPos(grp,axis)           TheSysData()->GetIData(105+grp*PARA_NUM_ITP+axis)//插补开始时的坐标

#define  PauseMoveStartFlag(grp,on)             TheSysData()->SetIData(111+grp*PARA_NUM_ITP,on)//断点移动启动标志
#define  CNC_Single_Seg_WaitStart(grp,on)       TheSysData()->SetIData(112+grp*PARA_NUM_ITP,on)//单段时等待循环启动标志
#define  StepLength(grp,value)			        TheSysData()->SetIData(116+grp*PARA_NUM_ITP,on)//单步步长
#define  WheelStepLength(grp,value)		        TheSysData()->SetIData(117+grp*PARA_NUM_ITP,on)//手轮步长
#define  MachineZeroAxisNum(grp,num)            TheSysData()->SetIData(118+grp*PARA_NUM_ITP,on)//可同时回零的轴数
#define  ManualCurrentAxis(grp,on)              TheSysData()->SetIDataI(119+grp*PARA_NUM_ITP,on)//单步/手轮选定轴
#define  ManualAxisSelect(grp,axis,sel)         TheSysData()->SetIData(120+grp*PARA_NUM_ITP+axis,sel)//手动插补选定轴
#define  WheelAllLength(grp,value)              TheSysData()->SetIData(126+grp*PARA_NUM_ITP,value)//手轮进给量
#define  StepAllLength(grp,value)               TheSysData()->SetIData(132+grp*PARA_NUM_ITP,value)
//READ
#define  ReadI_PauseMoveStartFlag(grp)          TheSysData()->GetIData(111+grp*PARA_NUM_ITP)//断点移动启动标志
#define  ReadI_CNC_Single_Seg_WaitStart(grp)    TheSysData()->GetIData(112+grp*PARA_NUM_ITP)//单段时等待循环启动标志
#define  ReadI_StepLength(grp)			        TheSysData()->GetIData(116+grp*PARA_NUM_ITP)//单步步长
#define  ReadI_WheelStepLength(grp)		        TheSysData()->GetIData(117+grp*PARA_NUM_ITP)//手轮步长
#define  ReadI_MachineZeroAxisNum(grp)          TheSysData()->GetIData(118+grp*PARA_NUM_ITP)//可同时回零的轴数
#define  ReadI_ManualCurrentAxis(grp)           TheSysData()->GetIDataI(119+grp*PARA_NUM_ITP)//单步/手轮选定轴
#define  ReadI_ManualAxisSelect(grp,axis)       TheSysData()->GetIData(120+grp*PARA_NUM_ITP+axis)//手动插补选定轴
#define  ReadI_WheelAllLength(grp)              TheSysData()->GetIData(126+grp*PARA_NUM_ITP)//手轮进给量
#define  ReadI_StepAllLength(grp)               TheSysData()->GetIData(132+grp*PARA_NUM_ITP)

#define  CNCSegLoopStartFlag(grp,on)            TheSysData()->SetIData(133+grp*PARA_NUM_ITP,on)
#define  SingleSegStopFlag(grp,on)              TheSysData()->SetIData(134+grp*PARA_NUM_ITP,on)
#define  ReadI_CNCSegLoopStartFlag(grp)         TheSysData()->SetIData(133+grp*PARA_NUM_ITP)
#define  ReadI_SingleSegStopFlag(grp)           TheSysData()->SetIData(134+grp*PARA_NUM_ITP)


#define START_ADDR_MOT                     (10+PARA_NUM_ITP*INP_GROUP)
#define PARA_NUM_MOT                       40
//Motor no(0~15)
#define I_NUM_MOTOR(num)                   TheSysData()->SetIData(START_ADDR_MOT+0,num)          //控制电机数 3~16
#define I_NAME_MOTOR(no,name)              TheSysData()->SetIData(START_ADDR_MOT+1+no*40,name)   //name
#define I_PULSE_MOTOR(no,pulse)            TheSysData()->SetIDataI(START_ADDR_MOT+2+no*40,pulse)  //pulse equivalent (脉冲当量)
#define I_ZERO_MOTOR(no,value)             TheSysData()->SetIDataF(START_ADDR_MOT+3+no*40,value)  //零点偏移量
#define I_GEAR_MOTOR(no,ratio)             TheSysData()->SetIDataF(START_ADDR_MOT+4+no*40,ratio)  //gear ratio (齿轮比)
#define I_CLEAR_MOTOR(no,value)            TheSysData()->SetIDataF(START_ADDR_MOT+5+no*40,value)  //clearance (间隙值)
#define I_TRAVEL_MOTOR(no,value)           TheSysData()->SetIDataF(START_ADDR_MOT+6+no*40,value)  //travel (有效行程)
#define I_START_PTCP_MOTOR(no,value)       TheSysData()->SetIDataF(START_ADDR_MOT+7+no*40,value)  //pitch compensation start pos (螺距补偿起点)
#define I_END_PTCP_MOTOR(no,value)         TheSysData()->SetIDataF(START_ADDR_MOT+8+no*40,value)  //pitch compensation end pos (螺距补偿终点)
#define I_DIS_PTCP_MOTOR(no,value)         TheSysData()->SetIDataF(START_ADDR_MOT+9+no*40,value)  //pitch compensation distance (螺距补偿间隔)
#define I_ACC_L_PTCP_MOTOR(no,value)       TheSysData()->SetIDataF(START_ADDR_MOT+10+no*40,value)  //螺距补偿加速度限制
#define I_JERK_L_PTCP_MOTOR(no,value)      TheSysData()->SetIDataF(START_ADDR_MOT+11+no*40,value)  //螺距补偿跃度限制
#define I_HOME_TYPE_MOTOR(no,valueManualAxisSelect)        TheSysData()->SetIData(START_ADDR_MOT+12+no*40,value)  //回零方式
//Read
#define ReadI_NUM_MOTOR                  TheSysData()->GetIDataAddr(START_ADDR_MOT+0)          //控制电机数 3~16
#define ReadI_NAME_MOTOR(no)             TheSysData()->GetIDataAddr(START_ADDR_MOT+1+no*40)   //name
#define ReadI_PULSE_MOTOR(no)            TheSysData()->GetIDataIAddr(START_ADDR_MOT+2+no*40)  //pulse equivalent (脉冲当量)
#define ReadI_ZERO_MOTOR(no)             TheSysData()->GetIDataFAddr(START_ADDR_MOT+3+no*40)  //零点偏移量
#define ReadI_GEAR_MOTOR(no)             TheSysData()->GetIDataFAddr(START_ADDR_MOT+4+no*40)  //gear ratio (齿轮比)
#define ReadI_CLEAR_MOTOR(no)            TheSysData()->GetIDataFAddr(START_ADDR_MOT+5+no*40)  //clearance (间隙值)
#define ReadI_TRAVEL_MOTOR(no)           TheSysData()->GetIDataFAddr(START_ADDR_MOT+6+no*40)  //travel (有效行程)
#define ReadI_START_PTCP_MOTOR(no)       TheSysData()->GetIDataFAddr(START_ADDR_MOT+7+no*40)  //pitch compensation start pos (螺距补偿起点)
#define ReadI_END_PTCP_MOTOR(no)         TheSysData()->GetIDataFAddr(START_ADDR_MOT+8+no*40)  //pitch compensation end pos (螺距补偿终点)
#define ReadI_DIS_PTCP_MOTOR(no)         TheSysData()->GetIDataFAddr(START_ADDR_MOT+9+no*40)  //pitch compensation distance (螺距补偿间隔)
#define ReadI_ACC_L_PTCP_MOTOR(no)       TheSysData()->GetIDataFAddr(START_ADDR_MOT+10+no*40)  //螺距补偿加速度限制
#define ReadI_JERK_L_PTCP_MOTOR(no)      TheSysData()->GetIDataFAddr(START_ADDR_MOT+11+no*40)  //螺距补偿跃度限制
#define ReadI_HOME_TYPE_MOTOR(no)        TheSysData()->GetIData(START_ADDR_MOT+12+no*40)  //回零方式

#define I_FEEDSPEED_L_MOTOR(no,value)      TheSysData()->SetIDataF(START_ADDR_MOT+16+no*40,value)  //最大进给速度
#define I_ACC_L_MOTOR(no,value)            TheSysData()->SetIDataF(START_ADDR_MOT+17+no*40,value)  //最大加速度
#define I_JERK_L_MOTOR(no,value)           TheSysData()->SetIDataF(START_ADDR_MOT+18+no*40,value)  //最大跃度
#define I_G00SPEED_L_MOTOR(no,value)       TheSysData()->SetIDataF(START_ADDR_MOT+19+no*40,value)  //G00速度
#define I_LOWSPEED_SL_MOTOR(no,value)      TheSysData()->SetIDataF(START_ADDR_MOT+20+no*40,value)  //速度平滑-限制低速
#define I_LOWSPEED_H_MOTOR(no,value)       TheSysData()->SetIDataF(START_ADDR_MOT+21+no*40,value)  //回零低速
#define I_SPEEDSMOOTH_MOTOR(no,value)      TheSysData()->SetIData(START_ADDR_MOT+22+no*40,value)  //速度平滑time
#define I_POS_L_MOTOR(no,value)            TheSysData()->SetIDataF(START_ADDR_MOT+23+no*40,value)  //正向软限位
#define I_NEG_L_MOTOR(no,value)            TheSysData()->SetIDataF(START_ADDR_MOT+24+no*40,value)  //负向软限位
#define I_P_MOTOR(no,value)                TheSysData()->SetIData(START_ADDR_MOT+25+no*40,value)  //PID-比例
#define I_I_MOTOR(no,value)                TheSysData()->SetIData(START_ADDR_MOT+26+no*40,value)  //PID-积分
#define I_D_MOTOR(no,value)                TheSysData()->SetIData(START_ADDR_MOT+27+no*40,value)  //PID-微分
#define I_SPEED_FORWARD_MOTOR(no,value)    TheSysData()->SetIData(START_ADDR_MOT+28+no*40,value)  //速度前馈
#define I_ACC_FORWARD_MOTOR(no,value)      TheSysData()->SetIData(START_ADDR_MOT+29+no*40,value)  //加速度前馈
#define I_FATAL_ERR_MOTOR(no,value)        TheSysData()->SetIData(START_ADDR_MOT+30+no*40,value)  //致命跟随误差限制
#define I_ALARM_ERR_MOTOR(no,value)        TheSysData()->SetIData(START_ADDR_MOT+31+no*40,value)  //警戒跟随误差限制
//Read
#define ReadI_FEEDSPEED_L_MOTOR(no)      TheSysData()->GetIDataFAddr(START_ADDR_MOT+16+no*40)  //最大进给速度
#define ReadI_ACC_L_MOTOR(no)            TheSysData()->GetIDataFAddr(START_ADDR_MOT+17+no*40)  //最大加速度
#define ReadI_JERK_L_MOTOR(no)           TheSysData()->GetIDataFAddr(START_ADDR_MOT+18+no*40)  //最大跃度
#define ReadI_G00SPEED_L_MOTOR(no)       TheSysData()->GetIDataFAddr(START_ADDR_MOT+19+no*40)  //G00速度
#define ReadI_LOWSPEED_SL_MOTOR(no)      TheSysData()->GetIDataFAddr(START_ADDR_MOT+20+no*40)  //速度平滑-限制低速
#define ReadI_LOWSPEED_H_MOTOR(no)       TheSysData()->GetIDataFAddr(START_ADDR_MOT+21+no*40)  //回零低速
#define ReadI_SPEEDSMOOTH_MOTOR(no)      TheSysData()->GetIDataAddr(START_ADDR_MOT+22+no*40)  //速度平滑time(ms)
#define ReadI_POS_L_MOTOR(no)            TheSysData()->GetIDataFAddr(START_ADDR_MOT+23+no*40)  //正向软限位
#define ReadI_NEG_L_MOTOR(no)            TheSysData()->GetIDataFAddr(START_ADDR_MOT+24+no*40)  //负向软限位
#define ReadI_P_MOTOR(no)                TheSysData()->GetIDataAddr(START_ADDR_MOT+25+no*40)  //PID-比例
#define ReadI_I_MOTOR(no)                TheSysData()->GetIDataAddr(START_ADDR_MOT+26+no*40)  //PID-积分
#define ReadI_D_MOTOR(no)                TheSysData()->GetIDataAddr(START_ADDR_MOT+27+no*40)  //PID-微分
#define ReadI_SPEED_FORWARD_MOTOR(no)    TheSysData()->GetIDataAddr(START_ADDR_MOT+28+no*40)  //速度前馈
#define ReadI_ACC_FORWARD_MOTOR(no)      TheSysData()->GetIDataAddr(START_ADDR_MOT+29+no*40)  //加速度前馈
#define ReadI_FATAL_ERR_MOTOR(no)        TheSysData()->GetIDataAddr(START_ADDR_MOT+30+no*40)  //致命跟随误差限制
#define ReadI_ALARM_ERR_MOTOR(no)        TheSysData()->GetIDataAddr(START_ADDR_MOT+31+no*40)  //警戒跟随误差限制

#define START_ADDR_PLC                   (START_ADDR_MOT+MOTOR_NUM*PARA_NUM_MOT)
#define PARA_NUM_PLC                     10
//PLC group(1~4): 2ms, 8ms, 32ms, 100ms.
#define I_THNUM_PLC(grp,num)               TheSysData()->SetIData(START_ADDR_PLC+0+grp,num)              //每组实际线程数
#define I_PERIOD_TH_PLC(grp,no,period)     TheSysData()->SetIData(START_ADDR_PLC+10+grp*PARA_NUM_PLC*PLC_GROUP+no*PARA_NUM_PLC,period)  //每个线程设定周期
#define I_STEP_TH_PLC(grp,no,step)         TheSysData()->SetIData(START_ADDR_PLC+11+grp*PARA_NUM_PLC*PLC_GROUP+no*PARA_NUM_PLC,step)    //每个线程实际步数
#define I_BLOCK_TH_PLC(grp,no,block)       TheSysData()->SetIData(START_ADDR_PLC+12+grp*PARA_NUM_PLC*PLC_GROUP+no*PARA_NUM_PLC,step)    //每个线程实际模块数
#define ReadI_THNUM_PLC(grp)               TheSysData()->GetIData(START_ADDR_PLC+0+grp)              //每组实际线程数
#define ReadI_PERIOD_TH_PLC(grp,no)        TheSysData()->GetIData(START_ADDR_PLC+10+grp*PARA_NUM_PLC*PLC_GROUP+no*PARA_NUM_PLC)  //每个线程设定周期
#define ReadI_STEP_TH_PLC(grp,no)          TheSysData()->GetIData(START_ADDR_PLC+11+grp*PARA_NUM_PLC*PLC_GROUP+no*PARA_NUM_PLC)    //每个线程实际步数
#define ReadI_BLOCK_TH_PLC(grp,no)         TheSysData()->GetIData(START_ADDR_PLC+12+grp*PARA_NUM_PLC*PLC_GROUP+no*PARA_NUM_PLC)    //每个线程实际模块数

//=======================================================Alternative start================================================================//
#define START_ADDR_ALT                     (START_ADDR_PLC+PLC_ALL_NUM*PARA_NUM_PLC)
//  TOOL OR LASER
//either TOOL
#define I_TOOL_NUM_PLC(num)                TheSysData()->SetIData(START_ADDR_ALT+0,num)            //tool volume--max--64
#define I_TOOL_TYPE_PLC(type)              TheSysData()->SetIData(START_ADDR_ALT+1,type)           //tool type
#define I_TOOL_CHG_POS_PLC(pos)            TheSysData()->SetIDataF(START_ADDR_ALT+2,pos)            //tool change pos
#define I_TOOL_LEN_PLC(no,len)             TheSysData()->SetIDataF(START_ADDR_ALT+10+no*6,len)       //每把刀的:长度补偿值
#define I_TOOL_RAD_CP_PLC(no,cp)           TheSysData()->SetIDataF(START_ADDR_ALT+11+no*6,cp)        //每把刀的:半径补偿值(Radius compensation value)
#define I_TOOL_LEN_CRT_PLC(no,lenCrt)      TheSysData()->SetIDataF(START_ADDR_ALT+11+no*6,lenCrt)    //每把刀的:长度补偿修正值correction
#define I_TOOL_RAD_CP_CRT_PLC(no,cpCrt)    TheSysData()->SetIDataF(START_ADDR_ALT+12+no*6,cpCrt)     //每把刀的:半径补偿修正值(the correctionof Radius compensation value)
#define I_TOOL_LIFE_PLC(no,life)           TheSysData()->SetIData(START_ADDR_ALT+13+no*6,life)      //每把刀的:刀具寿命值
#define I_TOOL_LOSS_PLC(no,loss)           TheSysData()->SetIDataF(START_ADDR_ALT+14+no*6,loss)      //每把刀的:刀具磨损系数 loss factor
//or LASER
#define I_AIR_PRE_MIN_LASER(value)         TheSysData()->SetIData(START_ADDR_ALT+0,value)            //激光气体压力最大设定值
#define I_AIR_PRE_MAX_LASER(value)         TheSysData()->SetIData(START_ADDR_ALT+1,value)            //激光气体压力最小工作值
#define I_WORK_PRE_MIN_LASER(value)        TheSysData()->SetIData(START_ADDR_ALT+2,value)            //激光器工作压力最小设定值
#define I_WORK_PRE_MIN_ERR_LASER(value)    TheSysData()->SetIData(START_ADDR_ALT+4,value)            //激光器工作压力最小报警设定值
#define I_WORK_PRE_MAX_ERR_LASER(value)    TheSysData()->SetIData(START_ADDR_ALT+5,value)            //激光器工作压力最大报警设定值
#define I_POWER_PERC_LASER(value)          TheSysData()->SetIData(START_ADDR_ALT+6,value)            //激光器功率百分比
#define I_DUTY_CYCLE_PERC_LASER(value)     TheSysData()->SetIData(START_ADDR_ALT+7,value)            //激光器占空比百分比
#define I_PID_P_5_LASER(value)             TheSysData()->SetIData(START_ADDR_ALT+8,value)            //PID比例阀运算5%设定值
#define I_LEAK_PRE_LASER(value)            TheSysData()->SetIData(START_ADDR_ALT+9,value)            //允许泄漏压力设定值 Allowable leakage pressure set value
#define I_FLUSH_PER_LASER(value)           TheSysData()->SetIData(START_ADDR_ALT+10,value)            //冲洗压力参数值 Flushing pressure parameter values
#define I_WORK_PRE_LASER(value)            TheSysData()->SetIData(START_ADDR_ALT+11,value)            //激光器工作压力设定值 Lasers work pressure set value
#define I_BEAR_A_TEMPT_LASER(value)        TheSysData()->SetIData(START_ADDR_ALT+12,value)            //涡轮泵轴承A段温度设定值 turbopump bearing a temperature set value
#define I_BEAR_B_TEMPT_LASER(value)        TheSysData()->SetIData(START_ADDR_ALT+13,value)            //涡轮泵轴承B段温度设定值 turbopump bearing b temperature set value
#define I_BACK_AIR_PRE_LASER(value)        TheSysData()->SetIData(START_ADDR_ALT+14,value)            //回充气体压力设定值 Back to the air pressure set value
//Read
#define ReadI_AIR_PRE_MIN_LASER         TheSysData()->GetIData(START_ADDR_ALT+00)            //激光气体压力最大设定值
#define ReadI_AIR_PRE_MAX_LASER         TheSysData()->GetIData(START_ADDR_ALT+01)            //激光气体压力最小工作值
#define ReadI_WORK_PRE_MIN_LASER        TheSysData()->GetIData(START_ADDR_ALT+02)            //激光器工作压力最小设定值
#define ReadI_WORK_PRE_MIN_ERR_LASER    TheSysData()->GetIData(START_ADDR_ALT+04)            //激光器工作压力最小报警设定值
#define ReadI_WORK_PRE_MAX_ERR_LASER    TheSysData()->GetIData(START_ADDR_ALT+05)            //激光器工作压力最大报警设定值
#define ReadI_POWER_PERC_LASER          TheSysData()->GetIData(START_ADDR_ALT+06)            //激光器功率百分比
#define ReadI_DUTY_CYCLE_PERC_LASER     TheSysData()->GetIData(START_ADDR_ALT+07)            //激光器占空比百分比
#define ReadI_PID_P_5_LASER             TheSysData()->GetIData(START_ADDR_ALT+08)            //PID比例阀运算5%设定值
#define ReadI_LEAK_PRE_LASER            TheSysData()->GetIData(START_ADDR_ALT+09)            //允许泄漏压力设定值 Allowable leakage pressure set value
#define ReadI_FLUSH_PER_LASER           TheSysData()->GetIData(START_ADDR_ALT+10)            //冲洗压力参数值 Flushing pressure parameter values
#define ReadI_WORK_PRE_LASER            TheSysData()->GetIData(START_ADDR_ALT+11)            //激光器工作压力设定值 Lasers work pressure set value
#define ReadI_BEAR_A_TEMPT_LASER        TheSysData()->GetIData(START_ADDR_ALT+12)            //涡轮泵轴承A段温度设定值 turbopump bearing a temperature set value
#define ReadI_BEAR_B_TEMPT_LASER        TheSysData()->GetIData(START_ADDR_ALT+13)            //涡轮泵轴承B段温度设定值 turbopump bearing b temperature set value
#define ReadI_BACK_AIR_PRE_LASER        TheSysData()->GetIData(START_ADDR_ALT+14)            //回充气体压力设定值 Back to the air pressure set value

//=======================================================Alternative end===================================================================//
//==============================================================ctrl para end=====================================================================//

//==============================================================ctrl state start==================================================================//
#define I_TIME_ON_SYS(time)              TheSysData()->SetIData(STATE_I_SADDR,time)        //开机时间
#define I_TIME_AUTORUN_SYS(time)         TheSysData()->SetIData(STATE_I_SADDR+1,time)      //自动运行时间
#define I_TIME_FEED_SYS(time)            TheSysData()->SetIData(STATE_I_SADDR+2,time)      //进给时间
#define ReadI_TIME_ON_SYS                TheSysData()->GetIData(STATE_I_SADDR)             //开机时间
#define ReadI_TIME_AUTORUN_SYS           TheSysData()->GetIData(STATE_I_SADDR+1)           //自动运行时间
#define ReadI_TIME_FEED_SYS              TheSysData()->GetIData(STATE_I_SADDR+2)           //进给时间
//NC ROT BUF
#define I_CAPACITY_SEG_SYS(seg)          TheSysData()->SetIData(STATE_I_SADDR+11,seg)      //容量
#define I_GOT_SEG_COUNT_SYS(seg)         TheSysData()->SetIData(STATE_I_SADDR+12,seg)      //已取走总段数
#define I_RECEIVED_SEG_COUNT_SYS(seg)    TheSysData()->SetIData(STATE_I_SADDR+13,seg)      //已接收的总段数
#define I_ROT_BUF_STATE_SYS(ok)          TheSysData()->SetIData(STATE_I_SADDR+14,ok)       //缓冲区是否已建立
#define I_ROT_BUF_FULL_SYS(isFull)       TheSysData()->SetIData(STATE_I_SADDR+15,isFull)   //缓冲区是否已满

#define ReadI_CAPACITY_SEG_SYS           TheSysData()->GetIDataAddr(STATE_I_SADDR+11)      //容量
#define ReadI_GOT_SEG_COUNT_SYS          TheSysData()->GetIDataAddr(STATE_I_SADDR+12)      //已取走总段数
#define ReadI_RECEIVED_SEG_COUNT_SYS     TheSysData()->GetIDataAddr(STATE_I_SADDR+13)      //已接收的总段数
#define ReadI_ROT_BUF_STATE_SYS          TheSysData()->GetIData(STATE_I_SADDR+14)          //缓冲区是否已建立
#define ReadI_ROT_BUF_FULL_SYS           TheSysData()->GetIData(STATE_I_SADDR+15)          //缓冲区是否已满

#define STATE_I_SADDR_ITP                (STATE_I_SADDR+20)
#define INP_PARA_NUM                     200
//每个通道 i=0~3
#define I_SEG_ALL_ITP(i,seg)               TheSysData()->SetIData(STATE_I_SADDR_ITP+0+INP_PARA_NUM*i,seg)          //程序总段数
#define I_PRE_SEG_NUM_ITP(i,num)           TheSysData()->SetIData(STATE_I_SADDR_ITP+1+INP_PARA_NUM*i,num)          //预处理后未取走的段数
#define I_PROG_STATE_ITP(i,state)          TheSysData()->SetIData(STATE_I_SADDR_ITP+2+INP_PARA_NUM*i,state)        //缓冲区处理/插补状态: 所有段是否插补完成
#define I_ALARM_NO_ITP(i,no)               TheSysData()->SetIData(STATE_I_SADDR_ITP+3+INP_PARA_NUM*i,no)           //报警号
#define I_LOOK_SEG_ITP(i,seg)              TheSysData()->SetIData(STATE_I_SADDR_ITP+4+INP_PARA_NUM*i,seg)          //实际前瞻指令数
#define I_LOOK_LEN_ITP(i,len)              TheSysData()->SetIDataF(STATE_I_SADDR_ITP+5+INP_PARA_NUM*i,len)          //实际前瞻长度
#define I_LOOK_SSPEED_ITP(i,speed)         TheSysData()->SetIDataF(STATE_I_SADDR_ITP+6+INP_PARA_NUM*i,speed)       //前瞻起始速度
#define I_WORK_SEG_ITP(i,seg)              TheSysData()->SetIData(STATE_I_SADDR_ITP+7+INP_PARA_NUM*i,seg)          //已加工段数
#define I_STATE_ITP(i,state)               TheSysData()->SetIData(STATE_I_SADDR_ITP+8+INP_PARA_NUM*i,state)        //插补状态: 当前段是否插补完成
#define I_SEG_NO_ITP(i,no)                 TheSysData()->SetIData(STATE_I_SADDR_ITP+9+INP_PARA_NUM*i,no)          //正在插补的段号
#define I_FILE_NO_ITP(i,no)                TheSysData()->SetIData(STATE_I_SADDR_ITP+10+INP_PARA_NUM*i,no)          //正在插补的文件号
#define I_TYPE_ITP(i,type)                 TheSysData()->SetIData(STATE_I_SADDR_ITP+11+INP_PARA_NUM*i,type)        //插补类型
#define I_SURPLUS_LEN_ITP(i,len)           TheSysData()->SetIDataF(STATE_I_SADDR_ITP+12+INP_PARA_NUM*i,len)         //剩余进给距离
#define I_SURPLUS_LEN_AXIS_ITP(i,axis,len) TheSysData()->SetIDataF(STATE_I_SADDR_ITP+13+INP_PARA_NUM*i+axis,len)    //剩余进给距离 axis 0~5
#define I_THEORY_ERR_ITP(i,err)            TheSysData()->SetIDataF(STATE_I_SADDR_ITP+19+INP_PARA_NUM*i,err)         //理论误差
#define I_PROG_SPEED_ITP(i,speed)          TheSysData()->SetIDataF(STATE_I_SADDR_ITP+20+INP_PARA_NUM*i,speed)       //编程速度
#define I_REAL_FSPEED_ITP(i,speed)         TheSysData()->SetIDataF(STATE_I_SADDR_ITP+21+INP_PARA_NUM*i,speed)       //实际进给速度
#define I_MANUAL_TYPE_ITP(i,type)          TheSysData()->SetIData(STATE_I_SADDR_ITP+22+INP_PARA_NUM*i,type)        //手动插补类型
#define I_MANUAL_STATE_ITP(i,state)        TheSysData()->SetIData(STATE_I_SADDR_ITP+23+INP_PARA_NUM*i,state)       //手动插补阶段
//no(0~7)
#define I_OUTPUT_AXIS_POS_ITP(i,no,axis,pos)   TheSysData()->SetIDataF(STATE_I_SADDR_ITP+24+INP_PARA_NUM*i+no*6+axis,pos)    //插补输出点: 主动轴坐标
#define I_OUTPUT_SLAVEAXIS_POS_ITP(i,no,axis,pos)   TheSysData()->SetIDataF(STATE_I_SADDR_ITP+66+INP_PARA_NUM*i+no*6+axis,pos)    //插补输出点: 从动轴坐标
#define I_OUTPUT_LASER_CTRL_PARA_ITP(i,no,pa,value) TheSysData()->SetIDataF(STATE_I_SADDR_ITP+108+INP_PARA_NUM*i+no*4+pa,value)    //插补输出: 激光器的输出参数
#define I_OUTPUT_NO_ITP(i,no)                  TheSysData()->SetIDataI(STATE_I_SADDR_ITP+136+INP_PARA_NUM*i,no)               //精插补输出点号
#define I_OUTPUT_CTRL_LASER(i,isCtrl)         TheSysData()->SetIData(STATE_I_SADDR_ITP+137+INP_PARA_NUM*i,isCtrl)             //是否控制激光器
#define I_SYNCH_DIFF_ITP(i,diff)              TheSysData()->SetIData(STATE_I_SADDR_ITP+138+INP_PARA_NUM*i,diff)             //同步轴差值
#define I_ZERO_SET_STATE_ITP(i,state)         TheSysData()->SetIData(STATE_I_SADDR_ITP+139+INP_PARA_NUM*i,state)           //零点建立状态： 已建立(1)
//Read
#define ReadI_SEG_ALL_ITP(i)                  TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+0+INP_PARA_NUM*i)         //程序总段数
#define ReadI_PRE_SEG_NUM_ITP(i)              TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+1+INP_PARA_NUM*i)         //预处理后未取走的段数
#define ReadI_PROG_STATE_ITP(i)               TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+2+INP_PARA_NUM*i)         //缓冲区处理状态: 所有段是否完成
#define ReadI_ALARM_NO_ITP(i)                 TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+3+INP_PARA_NUM*i)         //报警号
#define ReadI_LOOK_SEG_ITP(i)                 TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+4+INP_PARA_NUM*i)         //实际前瞻指令数
#define ReadI_LOOK_LEN_ITP(i)                 TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+5+INP_PARA_NUM*i)        //实际前瞻长度
#define ReadI_LOOK_SSPEED_ITP(i)              TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+6+INP_PARA_NUM*i)        //前瞻起始速度
#define ReadI_WORK_SEG_ITP(i)                 TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+7+INP_PARA_NUM*i)         //已加工段数
#define ReadI_STATE_ITP(i)                    TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+8+INP_PARA_NUM*i)         //插补状态: 当前段是否插补完成
#define ReadI_SEG_NO_ITP(i)                   TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+9+INP_PARA_NUM*i)         //正在插补的段号
#define ReadI_FILE_NO_ITP(i)                  TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+10+INP_PARA_NUM*i)        //正在插补的文件号
#define ReadI_TYPE_ITP(i)                     TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+11+INP_PARA_NUM*i)        //插补类型
#define ReadI_SURPLUS_LEN_ITP(i)              TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+12+INP_PARA_NUM*i)       //剩余进给距离
#define ReadI_SURPLUS_LEN_AXIS_ITP(i,axis)    TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+13+INP_PARA_NUM*i+axis)  //剩余进给距离 axis 0~5
#define ReadI_THEORY_ERR_ITP(i)               TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+19+INP_PARA_NUM*i)       //理论误差
#define ReadI_PROG_SPEED_ITP(i)               TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+20+INP_PARA_NUM*i)       //编程速度
#define ReadI_REAL_FSPEED_ITP(i)              TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+21+INP_PARA_NUM*i)       //实际进给速度
#define ReadI_MANUAL_TYPE_ITP(i)              TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+22+INP_PARA_NUM*i)        //手动插补类型
#define ReadI_MANUAL_STATE_ITP(i)             TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+23+INP_PARA_NUM*i)        //手动插补阶段
//no(0~7)
#define ReadI_OUTPUT_AXIS_POS_ITP(i,no,axis)   TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+24+INP_PARA_NUM*i+no*6+axis)   //插补输出: 主动轴坐标
#define ReadI_OUTPUT_SLAVEAXIS_POS_ITP(i,no,axis)   TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+66+INP_PARA_NUM*i+no*6+axis)    //插补输出点: 从动轴坐标
#define ReadI_OUTPUT_LASER_CTRL_PARA_ITP(i,no,para) TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+108+INP_PARA_NUM*i+no*4+para)   //插补输出: 激光器的输出参数
#define ReadI_OUTPUT_NO_ITP(i)                 TheSysData()->GetIDataIAddr(STATE_I_SADDR_ITP+136+INP_PARA_NUM*i)             //精插补输出点号
#define ReadI_OUTPUT_CTRL_LASER(i)            TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+137+INP_PARA_NUM*i)             //是否控制激光器
#define ReadI_SYNCH_DIFF_ITP(i)               TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+138+INP_PARA_NUM*i)             //同步轴差值
#define ReadI_ZERO_SET_STATE_ITP(i)           TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+139+INP_PARA_NUM*i)           //零点建立状态： 已建立(1)

//逻辑指令
#define I_CODE_LOG_ITP(i,code)                TheSysData()->SetIData(STATE_I_SADDR_ITP+140+INP_PARA_NUM*i,code)         //具体指令号
#define I_STATE_LOG_ITP(i,state)              TheSysData()->SetIData(STATE_I_SADDR_ITP+141+INP_PARA_NUM*i,state)        //指令执行状态
#define I_MOVE_CODE_LOG_ITP(i,code)           TheSysData()->SetIData(STATE_I_SADDR_ITP+142+INP_PARA_NUM*i,code)         //发送的运动指令
#define I_MOVE_STATE_LOG_ITP(i,state)         TheSysData()->SetIData(STATE_I_SADDR_ITP+143+INP_PARA_NUM*i,state)        //运动指令执行状态
#define ReadI_CODE_LOG_ITP(i)                 TheSysData()->GetIData(STATE_I_SADDR_ITP+140+INP_PARA_NUM*i)              //具体指令号
#define ReadI_STATE_LOG_ITP(i)                TheSysData()->GetIData(STATE_I_SADDR_ITP+141+INP_PARA_NUM*i)              //指令执行状态
#define ReadI_MOVE_CODE_LOG_ITP(i)            TheSysData()->GetIData(STATE_I_SADDR_ITP+142+INP_PARA_NUM*i)              //发送的运动指令
#define ReadI_MOVE_STATE_LOG_ITP(i)           TheSysData()->GetIData(STATE_I_SADDR_ITP+143+INP_PARA_NUM*i)              //运动指令执行状态

#define I_MANUAL_INTERP_FINISHED_ITP(i,state)         TheSysData()->SetIDataI(STATE_I_SADDR_ITP+148+INP_PARA_NUM*i,state)  //插补状态: 所有段是否完成或被中止
#define ReadI_MANUAL_INTERP_FINISHED_ITP(i)           TheSysData()->GetIDataI(STATE_I_SADDR_ITP+148+INP_PARA_NUM*i)         //插补状态: 未发生(0) 完成(1) 被中止(-1) 运动中(2)

#define I_AUTO_INTERP_FINISHED_ITP(i,state)         TheSysData()->SetIDataI(STATE_I_SADDR_ITP+149+INP_PARA_NUM*i,state)   //程序处理+插补状态: 所有段是否完成或被中止
#define ReadI_AUTO_INTERP_FINISHED_ITP(i)           TheSysData()->GetIDataI(STATE_I_SADDR_ITP+149+INP_PARA_NUM*i)         //插补状态: 未发生(0) 完成(1) 被中止(-1) 运动中(2)

//axis 0~5 CRD_AXIS_MAX
#define POS_AXIS_MODAL_ITP(i,axis,pos)        TheSysData()->SetIDataF(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+axis,pos)     //每个轴的实际插补坐标(不含各种补偿值)
//modal g code
#define ABS_MODAL_ITP(i,abs)                  TheSysData()->SetIData(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX,abs)   //
#define MOTION_MODAL_ITP(i,motion)            TheSysData()->SetIData(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+1,motion)   //
#define CHAMFERING_ROUNDED_MODAL_ITP(i,crr)   TheSysData()->SetIData(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+2,crr)   //
#define CORNER_LOOP_MODAL_ITP(i,cor)          TheSysData()->SetIData(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+3,cor)   //
#define MCODE_MODAL_ITP(i,mcode)              TheSysData()->SetIDataI(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+4,mcode)   //
#define G28_CTRL_ITP(i,state)                 TheSysData()->SetIData(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+5,state)   //

//READ
#define ReadI_POS_AXIS_MODAL(i,axis)            TheSysData()->GetIDataFAddr(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+axis)     //每个轴的实际插补坐标(不含各种补偿值)
#define ReadI_ABS_MODAL_ITP(i)                  TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX)     //
#define ReadI_MOTION_MODAL_ITP(i)               TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+1)   //
#define ReadI_CHAMFERING_ROUNDED_MODAL_ITP(i)   TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+2)   //
#define ReadI_CORNER_LOOP_MODAL_ITP(i)          TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+3)   //
#define ReadI_MCODE_MODAL_ITP(i)                TheSysData()->GetIDataIAddr(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+4)   //
#define ReadI_G28_CTRL_ITP(i)                   TheSysData()->GetIDataAddr(STATE_I_SADDR_ITP+150+INP_PARA_NUM*i+CRD_AXIS_MAX+5)   //

#define  ManualAxisComplete(i,axis,ok)        TheSysData()->SetIData(STATE_I_SADDR_ITP+170+i*PARA_NUM_ITP+axis,ok)//手动插补完成
#define  ZeroDecAutoSignal(i,axis,on)         TheSysData()->SetIData(STATE_I_SADDR_ITP+176+i*PARA_NUM_ITP+axis,on)//回零减速标志
// 1:回零高速段
// 2: 回零低速段
// 3: Z脉冲捕捉阶段
// 4: Z脉冲捕获完成
// 5: Z零点回退阶段
#define  ZeroGetZplusFlag(i,axis,set)         TheSysData()->SetIData(STATE_I_SADDR_ITP+182+i*PARA_NUM_ITP+axis,set)//Z脉冲获取标志

#define  ReadManualAxisComplete(i,axis)        TheSysData()->GetIData(STATE_I_SADDR_ITP+170+i*PARA_NUM_ITP+axis)//手动插补完成
#define  ReadZeroDecAutoSignal(i,axis)         TheSysData()->GetIData(STATE_I_SADDR_ITP+176+i*PARA_NUM_ITP+axis)//回零减速标志
#define  ReadZeroGetZplusFlag(i,axis)         TheSysData()->GetIData(STATE_I_SADDR_ITP+182+i*PARA_NUM_ITP+axis)//Z脉冲获取标志

#define STATE_I_SADDR_PLC                     (STATE_I_SADDR_ITP+INP_PARA_NUM*INP_GROUP)
//PLC i=0~31
#define I_TH_STATE_PLC(i,state)               TheSysData()->SetIData(STATE_I_SADDR_PLC+0+i*6,state)          //PLC每个线程的执行状态:循环执行中、单步调试中、I/O强制中、停止中
#define I_TH_ALARM_NO_PLC(i,no)               TheSysData()->SetIData(STATE_I_SADDR_PLC+1+i*6,no)             //出错号
#define I_TH_BLOCK_PLC(i,block)               TheSysData()->SetIData(STATE_I_SADDR_PLC+2+i*6,block)          //当前模块号
#define I_TH_CODE_PLC(i,code)                 TheSysData()->SetIData(STATE_I_SADDR_PLC+3+i*6,code)           //当前指令序号
#define ReadI_TH_STATE_PLC(i)                 TheSysData()->GetIData(STATE_I_SADDR_PLC+0+i*6)          //PLC每个线程的执行状态:循环执行中、单步调试中、I/O强制中、停止中
#define ReadI_TH_ALARM_NO_PLC(i)              TheSysData()->GetIData(STATE_I_SADDR_PLC+1+i*6)          //出错号
#define ReadI_TH_BLOCK_PLC(i)                 TheSysData()->GetIData(STATE_I_SADDR_PLC+2+i*6)          //当前模块号
#define ReadI_TH_CODE_PLC(i)                  TheSysData()->GetIData(STATE_I_SADDR_PLC+3+i*6)          //当前指令序号

#define STATE_I_SADDR_MOT                     (STATE_I_SADDR_PLC+200)
#define MOT_PARA_NUM                          20
//motor
#define I_PITCH_NO_MOT(motor,no)              TheSysData()->SetIData(STATE_I_SADDR_MOT+0+MOT_PARA_NUM*motor,no)          //螺距补偿段号
#define I_PITCH_SURPLUS_MOT(motor,value)      TheSysData()->SetIDataF(STATE_I_SADDR_MOT+1+MOT_PARA_NUM*motor,value)       //螺距补偿余量
#define I_PITCH_FEED_MOT(motor,value)         TheSysData()->SetIDataF(STATE_I_SADDR_MOT+2+MOT_PARA_NUM*motor,value)       //补偿进给量
#define I_CLEARANCE_SURPLUS_MOT(motor,value)  TheSysData()->SetIDataF(STATE_I_SADDR_MOT+3+MOT_PARA_NUM*motor,value)       //补偿进给量
#define I_CLEARANCE_FEED_MOT(motor,value)     TheSysData()->SetIDataF(STATE_I_SADDR_MOT+4+MOT_PARA_NUM*motor,value)       //补偿进给量
#define I_REAL_FEED_MOT(motor,speed)          TheSysData()->SetIDataF(STATE_I_SADDR_MOT+5+MOT_PARA_NUM*motor,speed)       //实际速度
#define I_REAL_ACC_MOT(motor,acc)             TheSysData()->SetIDataF(STATE_I_SADDR_MOT+6+MOT_PARA_NUM*motor,acc)         //实际加速度
#define I_REAL_JERK_MOT(motor,jerk)           TheSysData()->SetIDataF(STATE_I_SADDR_MOT+7+MOT_PARA_NUM*motor,jerk)        //实际跃度
#define I_REAL_POS_MOT(motor,pos)             TheSysData()->SetIDataF(STATE_I_SADDR_MOT+8+MOT_PARA_NUM*motor,pos)         //实际位置
#define I_REAL_DIFF_MOT(motor,diff)           TheSysData()->SetIData(STATE_I_SADDR_MOT+9+MOT_PARA_NUM*motor,diff)        //跟随误差
#define I_ALARM_NO_MOT(motor,no)              TheSysData()->SetIData(STATE_I_SADDR_MOT+10+MOT_PARA_NUM*motor,no)         //报警号
#define I_THEORY_POS_MOT(motor,pos)           TheSysData()->SetIDataF(STATE_I_SADDR_MOT+11+MOT_PARA_NUM*motor,pos)        //理论位置
#define I_THEORY_SPEED_MOT(motor,speed)       TheSysData()->SetIDataF(STATE_I_SADDR_MOT+12+MOT_PARA_NUM*motor,speed)      //理论速度
//Read
#define ReadI_PITCH_NO_MOT(motor)             TheSysData()->GetIData(STATE_I_SADDR_MOT+0+MOT_PARA_NUM*motor)        //螺距补偿段号
#define ReadI_PITCH_SURPLUS_MOT(motor)        TheSysData()->GetIDataF(STATE_I_SADDR_MOT+1+MOT_PARA_NUM*motor)        //螺距补偿余量
#define ReadI_PITCH_FEED_MOT(motor)           TheSysData()->GetIDataF(STATE_I_SADDR_MOT+2+MOT_PARA_NUM*motor)        //补偿进给量
#define ReadI_CLEARANCE_SURPLUS_MOT(motor)    TheSysData()->GetIDataF(STATE_I_SADDR_MOT+3+MOT_PARA_NUM*motor)        //补偿进给量
#define ReadI_CLEARANCE_FEED_MOT(motor)       TheSysData()->GetIDataF(STATE_I_SADDR_MOT+4+MOT_PARA_NUM*motor)        //补偿进给量
#define ReadI_REAL_FEED_MOT(motor)            TheSysData()->GetIDataF(STATE_I_SADDR_MOT+5+MOT_PARA_NUM*motor)        //实际速度
#define ReadI_REAL_ACC_MOT(motor)             TheSysData()->GetIDataF(STATE_I_SADDR_MOT+6+MOT_PARA_NUM*motor)        //实际加速度
#define ReadI_REAL_JERK_MOT(motor)            TheSysData()->GetIDataF(STATE_I_SADDR_MOT+7+MOT_PARA_NUM*motor)        //实际跃度
#define ReadI_REAL_POS_MOT(motor)             TheSysData()->GetIDataF(STATE_I_SADDR_MOT+8+MOT_PARA_NUM*motor)        //实际位置
#define ReadI_REAL_DIFF_MOT(motor)            TheSysData()->GetIData(STATE_I_SADDR_MOT+9+MOT_PARA_NUM*motor)        //跟随误差
#define ReadI_ALARM_NO_MOT(motor)             TheSysData()->GetIData(STATE_I_SADDR_MOT+10+MOT_PARA_NUM*motor)       //报警号
#define ReadI_THEORY_POS_MOT(motor)           TheSysData()->GetIDataF(STATE_I_SADDR_MOT+11+MOT_PARA_NUM*motor)       //理论位置
#define ReadI_THEORY_SPEED_MOT(motor)         TheSysData()->GetIDataF(STATE_I_SADDR_MOT+12+MOT_PARA_NUM*motor)       //理论速度

//==============================================================ctrl state end====================================================================//

//==============================================================D Data End=================================================================================//

#endif // DEFSYSSIGNALANDDATA_H
