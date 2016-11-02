/* -------------------------------------------------------------------------- */
/* avr.h																	  */
/* CL21																		  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							日付		氏名			  */
/* -------------------------------------------------------------------------- */
/* 000000	新規作成							2016/06/28	田中 翔吾		  */
/* -------------------------------------------------------------------------- */
#ifndef		AVR_LIBRARY_H_
#define		AVR_LIBRARY_H_

#ifndef		F_CPU
#define		F_CPU 8000000UL						/* 8MHz発振					  */
#endif

/* -------------------------------------------------------------------------- */
/* includeファイル	    												  	  */
/* -------------------------------------------------------------------------- */
#include <avr/io.h>								/* AVR入出力				  */
#include <util/delay.h>							/* ディレイ関数				  */
#include <avr/interrupt.h>						/* 割込みヘッダ				  */

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
/* マクロ定義			    												  */
/* -------------------------------------------------------------------------- */
#define High(reg,bitno)	( reg |=  ( 1 << bitno ) )	/* Px_nにHighを設定		  */
#define Low(reg,bitno)	( reg &= ~( 1 << bitno ) )	/* Px_nにLowを設定		  */
#define Rev(reg,bitno)	( reg ^=  ( 1 << bitno ) )	/* Px_nを反転			  */

#define pinLevel(pin,lv)	( pin( PORT, lv ) )		/* 出力レベル(H/L)を設定  */
#define pinMode(pin,mode)	( pin( DDR, mode ) )	/* 入出力方向(I/O)を設定  */

/* H/L Level ( lv ) --------------------------------------------------------- */
#define _HIGH_		High							/* High( 1 )			  */
#define _LOW_		Low								/* Low ( 0 )			  */
#define _REV_		Rev								/* Reverse( 反転 ) 		  */

/* I/O Mode ( mode ) -------------------------------------------------------- */
#define _INPUT_		Low								/* 入力					  */
#define _OUTPUT_	High							/* 出力					  */

/* 出力レベル(H/L)設定 ------------------------------------------------------ */
#define ON(pin)			( pin( PORT, High ) )		/* High					  */
#define OFF(pin)		( pin( PORT, Low ) )		/* Low					  */

/* 入出力方向(I/O)を設定 ---------------------------------------------------- */
#define INPUT(pin)		( pin( DDR, Low ) )			/* 入力					  */
#define OUTPUT(pin)		( pin( DDR, High ) )		/* 出力					  */

/* B_PORT ------------------------------------------------------------------- */
#define PinB0(reg,lv)	( lv( ( reg ## B ), 0 ) )
#define PinB1(reg,lv)	( lv( ( reg ## B ), 1 ) )
#define PinB2(reg,lv)	( lv( ( reg ## B ), 2 ) )
#define PinB3(reg,lv)	( lv( ( reg ## B ), 3 ) )
#define PinB4(reg,lv)	( lv( ( reg ## B ), 4 ) )
#define PinB5(reg,lv)	( lv( ( reg ## B ), 5 ) )
#define PinB6(reg,lv)	( lv( ( reg ## B ), 6 ) )
#define PinB7(reg,lv)	( lv( ( reg ## B ), 7 ) )

/* C_PORT ------------------------------------------------------------------- */
#define PinC0(reg,lv)	( lv( ( reg ## C ), 0 ) )
#define PinC1(reg,lv)	( lv( ( reg ## C ), 1 ) )
#define PinC2(reg,lv)	( lv( ( reg ## C ), 2 ) )
#define PinC3(reg,lv)	( lv( ( reg ## C ), 3 ) )
#define PinC4(reg,lv)	( lv( ( reg ## C ), 4 ) )
#define PinC5(reg,lv)	( lv( ( reg ## C ), 5 ) )
#define PinC6(reg,lv)	( lv( ( reg ## C ), 6 ) )
#define PinC7(reg,lv)	( lv( ( reg ## C ), 7 ) )

/* D_PORT ------------------------------------------------------------------- */
#define PinD0(reg,lv)	( lv( ( reg ## D ), 0 ) )
#define PinD1(reg,lv)	( lv( ( reg ## D ), 1 ) )
#define PinD2(reg,lv)	( lv( ( reg ## D ), 2 ) )
#define PinD3(reg,lv)	( lv( ( reg ## D ), 3 ) )
#define PinD4(reg,lv)	( lv( ( reg ## D ), 4 ) )
#define PinD5(reg,lv)	( lv( ( reg ## D ), 5 ) )
#define PinD6(reg,lv)	( lv( ( reg ## D ), 6 ) )
#define PinD7(reg,lv)	( lv( ( reg ## D ), 7 ) )

/* Digital Port ------------------------------------------------------------ */
#define PORT_D0		PinD0
#define PORT_D1		PinD1
#define PORT_D2		PinD2
#define PORT_D3		PinD3
#define PORT_D4		PinD4
#define PORT_D5		PinD5
#define PORT_D6		PinD6
#define PORT_D7		PinD7
#define PORT_D8		PinB0
#define PORT_D9		PinB1
#define PORT_D10	PinB2
#define PORT_D11	PinB3
#define PORT_D12	PinB4
#define PORT_D13	PinB5

/* Anarog Port -------------------------------------------------------------- */
#define PORT_A0 	PinC0
#define PORT_A1 	PinC1
#define PORT_A2 	PinC2
#define PORT_A3 	PinC3
#define PORT_A4 	PinC4
#define PORT_A5 	PinC5

/* -------------------------------------------------------------------------- */
/* 定数定義			      												      */
/* -------------------------------------------------------------------------- */
#define HIGH			(    1 )				/* Hレベル					  */
#define LOW				(    0 )				/* Lレベル					  */
#define SWT_OFF			( HIGH )				/* スイッチOFF状態			  */
#define SWT_ON			(  LOW )				/* スイッチON状態			  */

/* A/D変換関係定数 ---------------------------------------------------------- */
#define ADC_MSK			( 0x03FF )				/* A/D変換結果用マスク(10Bit) */

/* ポート-------------------------------------------------------------------- */
enum PORT{
	B_PORT,
	C_PORT,
	D_PORT
};

/* -------------------------------------------------------------------------- */
/* プロトタイプ宣言															  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* 関数名		: delay_ms													  */
/* 機能名		: ディレイ(ms)												  */
/* 機能概要		: 引数で渡された時間(ms)待機する							  */
/* 引数			: SINT			: ms		: 待機時間(ms)					  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/06/14	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void delay_ms( SINT ms );

/* -------------------------------------------------------------------------- */
/* 関数名		: delay_us													  */
/* 機能名		: ディレイ(μs)												  */
/* 機能概要		: 引数で渡された時間(μs)待機する							  */
/* 引数			: SINT			: ms		: 待機時間(μs)					  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/06/14	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void delay_us( SINT us );

/* -------------------------------------------------------------------------- */
/* 関数名		: GetRegState												  */
/* 機能名		: レジスタ状態取得											  */
/* 機能概要		: レジスタの任意ビットの状態を取得する			 			  */
/* 引数			: volatile	UCHR	: reg		: レジスタ					  */
/*				: 			UCHR	: bitno		: ビット番号				  */
/* 戻り値		: 			UCHR	: LOW		: 0(Low)					  */
/* 				: 			UCHR	: HIGH		: 1(High)					  */
/* 作成日		: 2016/06/29	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
UCHR GetRegState( volatile UCHR reg, UCHR bitno );

/* A/D変換関連関数 ---------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* 関数名		: SetADC													  */
/* 機能名		: A/D変換設定												  */
/* 機能概要		: A/D変換の設定を行う										  */
/* 引数			: volatile	UCHR*	: ddrx		: ポート方向レジスタ(DDRx)	  */
/* 				: volatile	UCHR*	: pinx		: ポート入力レジスタ(PINx)	  */
/* 				: 			UCHR	: bitno		: ビット番号				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/06/29	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void SetADC( volatile UCHR* ddrx, volatile UCHR* pinx, UCHR bitno );

/* -------------------------------------------------------------------------- */
/* 関数名		: GetADC													  */
/* 機能名		: A/D変換値取得												  */
/* 機能概要		: A/D変換し、結果を返す。									  */
/* 引数			: なし														  */
/* 戻り値		: USHT			: sValue	: A/D変換値						  */
/* 作成日		: 2016/06/29	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
USHT GetADC( void );

/* 割込み関連関数 ---------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* 関数名		: SetTimerInterrupt											  */
/* 機能名		: タイマ割込み設定											  */
/* 機能概要		: タイマ割込みのレジスタ設定を行う。						  */
/* 引数			: DBLE			: ms		: 割込み間隔(ms)				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/09/07	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void SetTimerInterrupt( DBLE ms );

/* -------------------------------------------------------------------------- */
/* 関数名		: SetExternalInterrupt										  */
/* 機能名		: 外部割込み設定(両エッジ)									  */
/* 機能概要		: 外部割込みのレジスタ設定を行う。							  */
/* 引数			: enum PORT		: port			: ポート		 			  */
/* 				: UCHR			: bitno			: ビット番号				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/09/07	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void SetExternalInterrupt( enum PORT port , UCHR bitno );

#endif

/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
