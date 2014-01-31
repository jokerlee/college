//header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <winsock.h>
#include <winbase.h>
#include "mmsystem.h"

//global constants
#define maxFloor 9  //最高楼层
#define maxWaitTime 60  //最大等待时间,超
#define stopTime 2  //停靠时间
#define runTime 3	//移动一层所需时间

//函数原型

//88888888888888888 控 制 函 数 888888888888888888888888

/*======================================
 *监视键盘按键，获得输入命令
 *无返回值,无参数
 */
void getInput( void );

/*======================================
 *基本控制函数,控制电梯动作
 *无返回值,无参数
 */
void control( void );

/*========================================
 *控制电梯停靠动作
 *dir为电梯当前方向，floor为电梯当前楼层
 */
void stop( int dir, int floor );

/*======================================
 *控制电梯移动动作
 *dir为电梯当前方向，floor为电梯当前楼层
 */
void move( int dir, int* floor );

/*=======================================
 *判断电梯在某层是否停靠
 *dir为电梯当前方向，floor为电梯当前楼层
 *返回新的电梯方向
 */
int isStop( int dir, int floor );

/*========================================
 *为电梯确定运行方向
 *dir为电梯当前方向，floor为电梯当前楼层
 *返回值真假代表是否停靠：1停靠，0不停靠
 */
int newDirection( int dir, int floor );

/*=======================================
 *控制电梯等待动作，一旦有新请求则跳出
 */
void waiting( void );

/*==========================================
 *判断电梯当前是否需要进入等待状态
 *返回值真假代表是否进入等待状态：1进入，0不进入
 */
int isWait( void );

/*打印提示信息*/
void splash( void );

/*==========================================
 *时间控制函数
 *传入向前推进的时间（秒）
 */
void putClock( int time );


//88888888888888888 动 画 函 数 888888888888888888888888

/*初始化图形界面*/
void initGraph( void );

/*============================================
 *电梯移动动画，控制电梯上移活下移一层
 *传入移动方向dir：1为向上， -1为向下
 */
void drawMove( int dir );

/*==============================================
 *控制电梯内部请求灯
 *传入请求楼层，及操作
 *floor的值为请求楼层，floor为正代表灯亮， floor为负代表灯灭
 */
void drawInRqstLight( int floor );

/*===========================================
 *控制电梯外部请求灯
 *传入请求楼层floor，请求方向dir，请求操作flg
 *flg为1代表灯亮，-1代表灯灭
 */
void drawOutRqstLight( int floor, int dir, int flg );

/*打印电梯状态信息*/
void drawInfo( char* );

/*控制电梯内部楼层指示灯*/
void showFloor( int floor );

/*控制电梯内部方向指示灯*/
void showDir( int dir );

/*显示退出屏幕*/
void drawExit( void );

/*电梯状态结构*/
typedef struct status
{
	/*电梯当前楼层 1~9*/
	int floor;
	/*电梯当前方向 -1为下, 0为空闲, 1为上*/	
	int dir;
	/*电梯当前内部请求 数组下标为请求楼层  0代表无请求 1代表有请求*/
	int inRqst[maxFloor+1];
}status;