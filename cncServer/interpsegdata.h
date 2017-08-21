#ifndef INTERPSEGDATA_H
#define INTERPSEGDATA_H

#define Miniumnum      0.0001
#define MaxChgSpeed    0.1
#define UNKNOWN        99999999
//轴参数定义
struct AxisPara
{
    unsigned int _MotorNo;     //
    unsigned int* PROGNAME;    //编程名字:X/Y/Z/A/B/C/U/V/W
    float* CLEARANCE;          //clearance (间隙值)
    float* TRAVEL;             //travel (有效行程)
    float* START_PTCP;         //pitch compensation start pos (螺距补偿起点)
    float* END_PTCP;           //pitch compensation end pos (螺距补偿终点)
    float* DIS_PTCP;           //pitch compensation distance (螺距补偿间隔)
    float* VALUE_PTCP;         //螺距补偿值--指向一纬数组,个数=(螺距补偿终点-螺距补偿起点)/螺距补偿间隔+1
    float* ACC_L_PTCP;         //螺距补偿加速度限制
    float* JERK_L_PTCP;        //螺距补偿跃度限制

    float* FEEDSPEED_L;        //最大进给速度
    float* ACC_L;              //最大加速度
    float* JERK_L;             //最大跃度
    float* G00SPEED_L;         //G00速度
    float* LOWSPEED_SL;        //速度平滑-限制低速
};
//插补阶段所用参数数据
struct InterpPara
{
    unsigned int _GroupNo;
    unsigned int* PROG_AXIS;
    unsigned int* LOOKBUF;         //前瞻缓冲区设定段数
    float* LOOKBUF_LEN;            //前瞻缓冲区长度限制
    unsigned int* LOOK_TIME;       //前瞻限定时间
    float* CONTOUR_ACCURACY;       //轮廓精度
    float* ARRIVE_ACCURACY;        //到位精度
    float* SMALLLINES_LEN;         //小线段判定长度
    float* SMALLLINES_ANGLE;       //小线段限定角度
    float* SMALLLINES_OMIT_LEN;    //小线段限定可忽略(合并)长度
    float* SMALLLINES_CURVES_LEN;  //小线段限定曲线长度
    float* TRANS_ANGLE;            //拐角过渡角度限制
    float* ARC_R_ERR;              //圆弧半径误差限制
    float* FEED_LIMIT;             //进给速度限制
    float* ACC_LIMIT;              //加速度限制
    float* JERK_LIMIT;             //跃度限制
    unsigned int* STRATEGIES_SEL;  //strategies(策略) 1--速度优先  2--精度优先  3--均衡控制
    float* ALG_PARA0;           //算法参数0
    float* ALG_PARA1;           //算法参数1
    float* ALG_PARA2;           //算法参数2
    float* ALG_PARA3;           //算法参数3
    float* ALG_PARA4;           //算法参数4
    float* ALG_PARA5;           //算法参数5
    float* ALG_PARA6;           //算法参数6
    float* ALG_PARA7;           //算法参数7
    float* ALG_PARA8;           //算法参数8
    float* ALG_PARA9;           //算法参数9
    AxisPara pAxisDef[6][2];   //轴参数定义,mainAxisDef[axis][0](主动轴),mainAxisDef[axis][1](主动轴对应的从动轴),axis实际个数=*REAL_AXIS
                                   //从动轴使用前请判断指针是否有效，无效的表示该从动轴不存在
};
//预处理阶段所用参数状态数据
struct ItpProcessState
{
    unsigned int _GroupNo;
  //para
    unsigned int CTRL_TYPE;              //控制类型： 0--停止 1--循环启动  2--程序单步启动 3--循环执行
    float* FEED_RATE;              //执行倍率
  //state
    unsigned int* PROG_COMPLETE;         //所有程序已经完成处理
    unsigned int* ERR_NO;                //出错编号,0--表示没有出错
    unsigned int* LOOK_SEG;              //实际前瞻指令数,0--缓冲区处理完成
    float* LOOK_LEN;                     //实际前瞻长度
    float* LOOK_SSPEED;                  //前瞻起始速度
};
//粗插补阶段所用参数状态数据
struct ItpCoarseState
{
    unsigned int _GroupNo;

  //para
    bool               SKIP_FLAG;              //跳过信号是否有效
    bool               MCODE_UNCOMPLETE;       //M代码是否未处理完成
    unsigned int       CTRL_TYPE;              //控制状态： 0--急停 1--循环执行  2--减速停  3--当前程序段执行完即刻停
    float* FEED_RATE;              //执行倍率
  //state
    unsigned int* SEG_NUM;               //已处理段数
    unsigned int* SEG_NO;                //正在(粗)插补的段号 N
    unsigned int* FILE_NO;               //正在插补的文件号 O
    int* M_CODE;                         //等待处理的M代码,-1表示无
    unsigned int* ABS_MODAL;                //
    unsigned int* MOTION_MODAL;             //
    unsigned int* CHAMFERING_ROUNDED_MODAL; //
    unsigned int* CORNER_LOOP_MODAL;        //

    float* SURPLUS_LEN;                 //剩余进给距离,0 表示当前段插补已经完成
    float* SURPLUS_LEN_AXIS0;           //轴1的剩余进给距离
    float* SURPLUS_LEN_AXIS1;           //轴2的剩余进给距离
    float* SURPLUS_LEN_AXIS2;           //轴3的剩余进给距离
    float* SURPLUS_LEN_AXIS3;           //轴4的剩余进给距离
    float* SURPLUS_LEN_AXIS4;           //轴5的剩余进给距离
    float* SURPLUS_LEN_AXIS5;           //轴6的剩余进给距离
    float* THEORY_ERR;                  //理论误差
    float* PROG_SPEED;                  //编程速度
    float* REAL_FSPEED;                 //实际进给速度
};
//精插补阶段所用参数状态数据
struct ItpElaborateState
{
    unsigned int _GroupNo;
    int* OUPUT_NO;                  //精插补输出点号(1~6),-1 表示无效点,5 表示插补输出已经完成----当前阶段(当前插值曲线或多项式)
    float* OUPUT_MAIN_AXIS_POS0;    //主动轴0的插补输出点坐标(含补偿值)
    float* OUPUT_MAIN_AXIS_POS1;    //主动轴1的插补输出点坐标(含补偿值)
    float* OUPUT_MAIN_AXIS_POS2;    //主动轴2的插补输出点坐标(含补偿值)
    float* OUPUT_MAIN_AXIS_POS3;    //主动轴3的插补输出点坐标(含补偿值)
    float* OUPUT_MAIN_AXIS_POS4;    //主动轴4的插补输出点坐标(含补偿值)
    float* OUPUT_MAIN_AXIS_POS5;    //主动轴5的插补输出点坐标(含补偿值)
    float* OUPUT_SLAVE_AXIS_POS0;    //从动轴0的插补输出点坐标(含补偿值)
    float* OUPUT_SLAVE_AXIS_POS1;    //从动轴1的插补输出点坐标(含补偿值)
    float* OUPUT_SLAVE_AXIS_POS2;    //从动轴2的插补输出点坐标(含补偿值)
    float* OUPUT_SLAVE_AXIS_POS3;    //从动轴3的插补输出点坐标(含补偿值)
    float* OUPUT_SLAVE_AXIS_POS4;    //从动轴4的插补输出点坐标(含补偿值)
    float* OUPUT_SLAVE_AXIS_POS5;    //从动轴5的插补输出点坐标(含补偿值)

    float* REAL_POS_AXIS0;          //轴0的实际插补坐标(不含补偿值),主动轴代表从动轴，从动轴不单独设置插补坐标(不含补偿值).
    float* REAL_POS_AXIS1;          //轴1的实际插补坐标(不含补偿值),主动轴代表从动轴，从动轴不单独设置插补坐标(不含补偿值).
    float* REAL_POS_AXIS2;          //轴2的实际插补坐标(不含补偿值),主动轴代表从动轴，从动轴不单独设置插补坐标(不含补偿值).
    float* REAL_POS_AXIS3;          //轴3的实际插补坐标(不含补偿值),主动轴代表从动轴，从动轴不单独设置插补坐标(不含补偿值).
    float* REAL_POS_AXIS4;          //轴4的实际插补坐标(不含补偿值),主动轴代表从动轴，从动轴不单独设置插补坐标(不含补偿值).
    float* REAL_POS_AXIS5;          //轴5的实际插补坐标(不含补偿值),主动轴代表从动轴，从动轴不单独设置插补坐标(不含补偿值).

    unsigned int* CTRL_LASER;      //是否控制激光
    float* LASER_CTRL_P;            //激光器的输出参数--激光功率
    float* LASER_CTRL_Q;            //激光器的输出参数--频率
    float* LASER_CTRL_R;            //激光器的输出参数--占空比
    float* LASER_CTRL_PRE;          //激光器的输出参数--辅助气体气压
};

#define G00 0
#define G01 1
#define G02 2
#define G03 3
#define G04 4
#define G06 6
#define G09 9
#define G12 12
#define G28 28
#define G31 31
#define G33 33
#define G34 34
#define G35 35
#define G61 61
#define G62 62
#define G64 64
#define G82 82
#define G87 87
#define G88 88
#define G90 90
#define G91 91
#define G164 164
#define G173 173
#define G174 174
#define G181 181
#define G183 183
#define G188 188
#define G189 189

struct InterpSegData
{
    int group_id;
    int segNo;

    unsigned int G_ABS; //90/91
    int G_MOTION;  //0/1 ,2, 3, 12, 6
    int G_MOTION_0; //0/4
    int G_CHAMFERING_ROUNDED; //34/33,35
    int G_HOME_RETURN; //0/28
    int G_PRECISE_STOP;//0/9
    int G_CORNER;  //0/61, 62, 64, 164
    int G_CORNER_LOOP; //174/173
    int G_PREVIEW_STOP;//0/31
    int G_GAS_PRESSURE; //0/88
    int G_GAP; //0/87
    int G_POWER_RAMP; //0/183/181
    int G_GAS_RAMP; //0/189/188
    int G_LASER;//0/82
    int M_CODE; //-1(invalid) or >-1
    int N_CODE;
    int O_CODE;

    bool X_Flag;
    bool Y_Flag;
    bool Z_Flag;
    bool F_Flag;

    bool C_Flag;
    bool R_Flag;
    bool I_Flag;
    bool J_Flag;

    bool K_Flag;
    bool P_Flag;
    bool Q_Flag;
    bool C_gcr_Flag;
    bool R_gcr_Flag;

    double X_Value;
    double Y_Value;
    double Z_Value;
    double F_Value;

    double C_Value;
    double R_Value;
    double I_Value;
    double J_Value;
    double K_Value;
    double P_Value;
    double Q_Value;
    double C_gcr_Value;
    double R_gcr_Value;
};
#include <QString>

bool IsInterpSegBufEmpty();
bool IsInterpSegBufFull();
int ParseNcSeg(QString& ori_str, InterpSegData& curSeg);
void InitSegData(InterpSegData& seg);
void InitInterpSegBuf();
void ChangeInterpSegBufState(bool isCanInteractive);
bool IsCanGetInterpSegBuf();
void FillInterpSegDataBuf(InterpSegData* seg);
bool GetInterpSegData(InterpSegData* getSeg);
void ErrRepot(int errNo);
void ErrRepot(int errNo,int line,int prog);

//插补初始化函数
//para: 1 系统参数/轴参数，2 读取插补数据段的函数指针，3 报错的函数指针
typedef void (*InterpInit)(InterpPara* para , bool (*GetInterpData)(InterpSegData* seg),void (*Errer)(int errNum));
//预处理函数
//para: ProcessState是预处理阶段所用参数数据结构，里面既有系统变量值，也有需要预处理更新的变量
typedef bool (*PreProcess)(ItpProcessState * state);
//粗插补函数
//para: CoarseState是粗插补阶段所用参数数据结构，里面既有系统变量值，也有需要粗插补更新的变量
typedef bool (*CoarseInterp)(ItpCoarseState * state);
//插补函数
//para: ElaborateState是精插补阶段所用参数数据结构，精插补计算出的各轴输出位置、激光器控制参数以及插补状态均更新到这个指针里。这个函数里需要包含补偿和纠错处理
typedef bool (*ElaborateInterp)(ItpElaborateState * state);

#endif // INTERPSEGDATA_H
