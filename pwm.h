/* -------------------------------------------------------------------------- */
/* pwm.h																	  */
/* CL21																		  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							日付		氏名			  */
/* -------------------------------------------------------------------------- */
/* 000000	新規作成							2016/09/07	田中 翔吾		  */
/* -------------------------------------------------------------------------- */
#ifndef		PWM_LIBRARY_H_
#define		PWM_LIBRARY_H_

#ifndef		F_CPU
#define		F_CPU 8000000UL						/* 8MHz発振					  */
#endif

/* -------------------------------------------------------------------------- */
/* includeファイル	    												  	  */
/* -------------------------------------------------------------------------- */
#include "avr.h"

/* -------------------------------------------------------------------------- */
/* typedef定義																  */
/* -------------------------------------------------------------------------- */
#ifndef _TYPEDEF
#define _TYPEDEF
typedef 		 char	SCHR;					/* char型					  */
typedef unsigned char	UCHR;					/* unsigned char型			  */
typedef 		 short	SSHT;					/* short型					  */
typedef unsigned short	USHT;					/* unsigned short型			  */
typedef 		 long	SLNG;					/* long型					  */
typedef unsigned long	ULNG;					/* unsigned long型			  */
typedef 		 int	SINT;					/* int型					  */
typedef unsigned int	UINT;					/* unsigned int型			  */
typedef			 double	DBLE;					/* double型					  */
#endif

/* -------------------------------------------------------------------------- */
/* 定数定義			      												      */
/* -------------------------------------------------------------------------- */
/* サーボモータ関連定数 ----------------------------------------------------- */
#define SRVO_CYCLE				( 20000 )		/* PWM周期(us)				  */
#define SRVO_MIN				(   360 )		/* 回転最小(右位置)			  */
#define SRVO_MAX				(  1980 )		/* 回転最大(左位置)			  */
#define SRVO_RIGHT				(     0 )		/* 右位置					  */
#define SRVO_CENTER				(    90 )		/* 中心位置					  */
#define SRVO_LEFT				(   180 )		/* 左位置					  */

#define SRVO_RANGE	( SRVO_MAX-SRVO_MIN )		/* 回転範囲(最大-最小)		  */
#define SRVO_RATIO	(    SRVO_RANGE/180 )		/* 1°あたりパルス幅		  */


/* -------------------------------------------------------------------------- */
/* プロトタイプ宣言															  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* 関数名		: AttachServo												  */
/* 機能名		: サーボモータ設定											  */
/* 機能概要		: 															  */
/* 引数			: volatile	UCHR*	: ddrx		: ポート方向レジスタ(DDRx)	  */
/* 				: 			UCHR	: bitno		: ビット番号				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/09/07	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void AttachServo( volatile UCHR* ddrx, UCHR bitno );

/* -------------------------------------------------------------------------- */
/* 関数名		: MoveServo												  */
/* 機能名		: サーボモータ動作											  */
/* 機能概要		: サーボモータを指定角に動かす								  */
/* 引数			: SINT			: degree		: 角度(°）					  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/09/07	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void MoveServo( SINT degree );

/* -------------------------------------------------------------------------- */
/* 関数名		: SetParamPWM												  */
/* 機能名		: PWMパラメータ設定											  */
/* 機能概要		: PWM周期とパルス幅(HIGHの時間)を設定する。					  */
/* 引数			: SINT			: cycle		: PWM周期(us)					  */
/* 				: SINT			: pulse		: パルス幅(us)					  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/09/07	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void SetParamPWM( SINT cycle_us, SINT pulse_us );

/* -------------------------------------------------------------------------- */
/* 関数名		: PWM														  */
/* 機能名		: PWM処理													  */
/* 機能概要		: PWMのHIGH/LOWの切り替えを行う。							  */
/* 引数			: volatile	UCHR*	: portx		: ポート出力レジスタ(PORTx)	  */
/* 				: 			UCHR	: bitno		: ビット番号				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/09/07	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void PWM( volatile UCHR* portx, UCHR bitno );

#endif

/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
