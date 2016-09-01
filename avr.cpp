/* -------------------------------------------------------------------------- */
/* avr.cpp																	  */
/* CL21																		  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							日付		氏名			  */
/* -------------------------------------------------------------------------- */
/* 000000	新規作成							2016/06/30	田中 翔吾		  */
/* -------------------------------------------------------------------------- */
#include "avr.h"

/* -------------------------------------------------------------------------- */
/* 関数名		: delay_ms													  */
/* 機能名		: ディレイ(ms)												  */
/* 機能概要		: 引数で渡された時間(ms)待機する							  */
/* 引数			: SINT			: ms		: 待機時間(ms)					  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/06/14	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void delay_ms( SINT ms )
{
	if( ms != 0){
		while( ms-- ){
			_delay_ms( 1 );
		}
	}
}

/* -------------------------------------------------------------------------- */
/* 関数名		: delay_us													  */
/* 機能名		: ディレイ(μs)												  */
/* 機能概要		: 引数で渡された時間(μs)待機する							  */
/* 引数			: SINT			: ms		: 待機時間(μs)					  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/06/14	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void delay_us( SINT us )
{
	us /= 10;
	if( us != 0 ){
		while( us-- ){
			_delay_us( 10 );
		}
	}
}

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
UCHR GetRegState( volatile UCHR reg, UCHR bitno )
{
	/* ---------------------------------------------------------------------- */
	/* 変数定義      												  	      */
	/* ---------------------------------------------------------------------- */
	UCHR	cState	= LOW;						/* 状態						  */

	/* ---------------------------------------------------------------------- */
	/* メイン処理     												  	      */
	/* ---------------------------------------------------------------------- */
	cState = reg & ( 1 << bitno );
	cState >>= bitno;
		
	return cState;
}	

/* -------------------------------------------------------------------------- */
/* 関数名		: MoveServo													  */
/* 機能名		: サーボ動作												  */
/* 機能概要		: 引数で渡されたサーボを指定角度に回転させる	 			  */
/* 引数			: volatile	UCHR*	: portx		: ポート出力レジスタ(PORTx)	  */
/*				: 			UCHR	: bitno		: ビット番号				  */
/*				: 			SINT	: angle		: 角度						  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/06/15	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void MoveServo( volatile UCHR* portx, UCHR bitno, SINT angle )
{
	/* ---------------------------------------------------------------------- */
	/* 変数定義      												  	      */
	/* ---------------------------------------------------------------------- */
	SINT	iDuty	= 0;						/* 回転Duty					  */
	SINT	iElaps	= 0;						/* Elaps					  */

	/* ---------------------------------------------------------------------- */
	/* メイン処理     												  	      */
	/* ---------------------------------------------------------------------- */
	/* 回転Duty比の算出 */
	iDuty = ( SRVO_MAX - SRVO_MIN ) / 180.0;	/* 1°あたりのDuty比率		  */
	iDuty *= angle;								/* 指定角度のDuty比率		  */
	iDuty += SRVO_MIN;							/* 指定角度のDuty比			  */
		
	/* ---------------------------------------------------------------------- */
	/* PWM		     												  	      */
	/* ---------------------------------------------------------------------- */
	/* Elaps時間繰り返し ---------------------------------------------------- */
	for( iElaps = 0; iElaps < 30; iElaps++ ){
		High( *portx, bitno );					/* H出力					  */
		delay_us( iDuty );
		
		Low( *portx, bitno );					/* L出力					  */
		delay_us( SRVO_CYCLE - iDuty );
	
	}

}

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
void SetADC( volatile UCHR* ddrx, volatile UCHR* pinx, UCHR bitno )
{
	/* 入力設定 */
	Low( *ddrx, bitno );						/* [I N]	 				  */
	High( *pinx, bitno );
	
	/* ADMUX設定 */
	Low( ADMUX, REFS1 );						/* 基準電圧(5V)				  */
	High( ADMUX, REFS0 );						/* 基準電圧(5V)				  */
	Low( ADMUX, ADLAR );						/* A/D変換結果右揃え		  */
	ADMUX |= bitno;								/* 入力チャネル				  */
	
	/* ADCSRA設定 */
	High( ADCSRA, ADEN );						/* A/D変換許可				  */
	 							
}

/* -------------------------------------------------------------------------- */
/* 関数名		: GetADC													  */
/* 機能名		: A/D変換値取得												  */
/* 機能概要		: A/D変換し、結果を返す。									  */
/* 引数			: なし														  */
/* 戻り値		: USHT			: sValue	: A/D変換値						  */
/* 作成日		: 2016/06/29	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
USHT GetADC( void )
{
	/* ---------------------------------------------------------------------- */
	/* 変数宣言		      												      */
	/* ---------------------------------------------------------------------- */
	SSHT sValue = 0;							/* A/D変換値				  */
	
	/* ---------------------------------------------------------------------- */
	/* A／D変換		      												      */
	/* ---------------------------------------------------------------------- */
	High( ADCSRA, ADSC );						/* A/D変換開始				  */
	
	/* 変換終了まで待機 ----------------------------------------------------- */
	while ( GetRegState( ADCSRA, ADSC ) == HIGH );
	
	delay_ms( 10 );								/* 変換安定待ち				  */
		
	sValue = ADC & ADC_MSK;						/* A/D変換値取得			  */
	
	return sValue;
}

/* 割込み関連関数 ----------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
