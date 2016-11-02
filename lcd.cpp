/* -------------------------------------------------------------------------- */
/* lcd.cpp																	  */
/*																			  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴							日付		氏名			  */
/* -------------------------------------------------------------------------- */
/* 000000	新規作成							2016/10/26	田中 翔吾		  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル	    												  	  */
/* -------------------------------------------------------------------------- */
#include "lcd.h"

/* -------------------------------------------------------------------------- */
/* 関数名		: InitLCD													  */
/* 機能名		: LCD初期化													  */
/* 機能概要		: LCDのポートの初期設定を行う。								  */
/* 引数			: なし														  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void InitLCD( void )
{
	SCHR i = 0;		
		
	/* PORT INIT ------------------------------------------------------------ */
	pinMode( LCD_DB0, _OUTPUT_ );				/* [OUT]DB0(7)			 	  */
	pinMode( LCD_DB1, _OUTPUT_ );				/* [OUT]DB1(8)			 	  */
	pinMode( LCD_DB2, _OUTPUT_ );				/* [OUT]DB2(9)			 	  */
	pinMode( LCD_DB3, _OUTPUT_ );				/* [OUT]DB3(10)			 	  */
	pinMode( LCD_DB4, _OUTPUT_ );				/* [OUT]DB4(11)			 	  */
	pinMode( LCD_DB5, _OUTPUT_ );				/* [OUT]DB5(12)			 	  */
	pinMode( LCD_DB6, _OUTPUT_ );				/* [OUT]DB6(13)			 	  */
	pinMode( LCD_DB7, _OUTPUT_ );				/* [OUT]DB7(14)			 	  */
	
	pinMode( LCD_CS1, _OUTPUT_ );				/* [OUT]CS1(15)				  */
	pinMode( LCD_CS2, _OUTPUT_ );				/* [OUT]CS2(16)				  */
	pinMode( LCD_RS, _OUTPUT_);					/* [OUT]RS(4)				  */
	pinMode( LCD_RW, _OUTPUT_);					/* [OUT]RS(5)				  */
	pinMode( LCD_E, _OUTPUT_);					/* [OUT]RS(6)				  */
	
	/* OUTPUT INIT　( Set L-Level ) ----------------------------------------  */
	pinLevel( LCD_DB0, _LOW_ );
	pinLevel( LCD_DB1, _LOW_ );
	pinLevel( LCD_DB2, _LOW_ );
	pinLevel( LCD_DB3, _LOW_ );
	pinLevel( LCD_DB4, _LOW_ );
	pinLevel( LCD_DB5, _LOW_ );
	pinLevel( LCD_DB6, _LOW_ );
	pinLevel( LCD_DB7, _LOW_ );
	
	pinLevel( LCD_CS1, _LOW_ );	
	pinLevel( LCD_CS2, _LOW_ );	
	pinLevel( LCD_RS, _LOW_ );	
	pinLevel( LCD_RW, _LOW_ );	
	pinLevel( LCD_E, _LOW_ );	
	
	/* DISPLAY INIT --------------------------------------------------------- */
	for( i = 0; i <= 1; i++ ){
		SelectScreen( i ? LCD_RIGHT : LCD_LEFT );
		WriteCommand( 0x3F );					/* Display ON				  */
		WriteCommand( 0xC0 );					/* Display Start Line		  */
	}
	
}

/* -------------------------------------------------------------------------- */
/* 関数名		: ClearLCD													  */
/* 機能名		: LCDクリア													  */
/* 機能概要		: LCDの表示をクリア(消去)する。								  */
/* 引数			: なし														  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void ClearLCD( void )
{
	USHT col = 0;
	USHT row = 0;

	for( row = 0; row < 8; row++ ){
		for( col = 0; col < 128; col++ ){
			WriteLCD( row, col, 0x00 );
		}
	}
}

/* -------------------------------------------------------------------------- */
/* 関数名		: WriteCommand												  */
/* 機能名		: コマンド書き込み											  */
/* 機能概要		: LCDにコマンドを書き込む。									  */
/* 引数			: SCHR			: command		: コマンド(1byte)			  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void WriteCommand( SCHR command )
{
	pinLevel( LCD_RW, _LOW_ );
	pinLevel( LCD_RS, _LOW_ );
	SetDataBus( command );
	EnableLCD();
}	

/* -------------------------------------------------------------------------- */
/* 関数名		: WriteData													  */
/* 機能名		: データ書き込み											  */
/* 機能概要		: LCDにデータを書き込む。									  */
/* 引数			: SCHR			: data			: データ(1byte)				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void WriteData( SCHR data )
{
	pinLevel( LCD_RW, _LOW_ );
	pinLevel( LCD_RS, _HIGH_ );
	SetDataBus( data );
	EnableLCD();
}	

/* -------------------------------------------------------------------------- */
/* 関数名		: EnableLCD													  */
/* 機能名		: 書き込み実行												  */
/* 機能概要		: LCDへの書き込みを実行する。								  */
/* 引数			: なし														  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void EnableLCD( void )
{
	pinLevel( LCD_E, _HIGH_ );
	delay_us( 10 );
	pinLevel( LCD_E, _LOW_ );
}

/* -------------------------------------------------------------------------- */
/* 関数名		: SetDataBus												  */
/* 機能名		: データ振り分け											  */
/* 機能概要		: LCDの各データバスに値を設定する。							  */
/* 引数			: SCHR			: data			: データ(1byte)				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void SetDataBus( SCHR data )
{ 
	
	 ( ( data & 0x01 ) == 0x01 ) ? ON( LCD_DB0 ) : OFF( LCD_DB0 );
	 ( ( data & 0x02 ) == 0x02 ) ? ON( LCD_DB1 ) : OFF( LCD_DB1 );
	 ( ( data & 0x04 ) == 0x04 ) ? ON( LCD_DB2 ) : OFF( LCD_DB2 );
	 ( ( data & 0x08 ) == 0x08 ) ? ON( LCD_DB3 ) : OFF( LCD_DB3 );
	 ( ( data & 0x10 ) == 0x10 ) ? ON( LCD_DB4 ) : OFF( LCD_DB4 );
	 ( ( data & 0x20 ) == 0x20 ) ? ON( LCD_DB5 ) : OFF( LCD_DB5 );
	 ( ( data & 0x40 ) == 0x40 ) ? ON( LCD_DB6 ) : OFF( LCD_DB6 );
	 ( ( data & 0x80 ) == 0x80 ) ? ON( LCD_DB7 ) : OFF( LCD_DB7 );

}	

/* -------------------------------------------------------------------------- */
/* 関数名		: SelectScreen												  */
/* 機能名		: 画面選択													  */
/* 機能概要		: 使用するLCDの画面(CS1/CS2)を選択する。					  */
/* 引数			: SCHR			: lr			: LCD_LEFT (画面1)			  */
/* 				:				:				: LCD_RIGHT(画面2)		 	  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void SelectScreen( SCHR lr )
{
	if( lr == LCD_LEFT ){
		/* 画面1 */
		pinLevel( LCD_CS1, _HIGH_ );
		pinLevel( LCD_CS2, _LOW_ );
	}else if( lr == LCD_RIGHT ){
		/* 画面2 */
		pinLevel( LCD_CS1, _LOW_ );
		pinLevel( LCD_CS2, _HIGH_ );
	}
}	
/* -------------------------------------------------------------------------- */
/* 関数名		: WriteLCD													  */
/* 機能名		: LCD表示													  */
/* 機能概要		: 指定した位置にデータを表示する。							  */
/* 引数			: SCHR			: row			: 行(0～7)					  */
/* 				: SCHR			: col			: 列(0～127)				  */
/* 				: SCHR			: data			: データ(1byte)				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void WriteLCD( SCHR row, SCHR col, SCHR data )
{
	/* 画面選択 ------------------------------------------------------------- */
	if( col >= 64 ){
		/* 画面2 */
		col %= 64;
		SelectScreen( LCD_RIGHT );
	}else{
		/* 画面1 */
		SelectScreen( LCD_LEFT );
	}
	
	/* 行選択 --------------------------------------------------------------- */
	WriteCommand( row | 0xB8 );
	
	/* 列選択 --------------------------------------------------------------- */
	WriteCommand( col | 0x40 );
	
	/* データ書き込み ------------------------------------------------------- */
	WriteData( data );
	
}

/* -------------------------------------------------------------------------- */
/* 関数名		: WriteChar													  */
/* 機能名		: 文字表示													  */
/* 機能概要		: 指定した位置に文字(1文字)を表示する。						  */
/* 引数			: 		SCHR	 : row			: 行(0～7)					  */
/* 				: 		SCHR	 : col			: 列(0～15)					  */
/* 				: const SCHR	 : chr			: 文字(半角)				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void WriteChar( SCHR row, SCHR col, const SCHR chr )
{
	SCHR i = 0;
		
	for( i = 0; i < 5; i++ ){
		WriteLCD( row, ( 8 * col ) + i, pgm_read_byte( &Font[chr-' '][i] ) );
	}
}

/* -------------------------------------------------------------------------- */
/* 関数名		: WriteString												  */
/* 機能名		: 文字列表示												  */
/* 機能概要		: 指定した位置から文字列(MAX16文字)を表示する。				  */
/* 引数			: 		SCHR	 : row			: 行(0～7)					  */
/* 				: 		SCHR 	 : col			: 列(0～15)					  */
/* 				: const SCHR*	 : str			: 文字列(半角)				  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void WriteString( SCHR row, SCHR col, const SCHR* str )
{		
	while( *str != '\0' && col < 16 ){
		WriteChar( row, col, *str );
		col++;
		str++;
	}
}

/* -------------------------------------------------------------------------- */
/* 関数名		: WriteAlignString											  */
/* 機能名		: 文字列表示												  */
/* 機能概要		: 指定した行に指定した位置揃えで文字列(MAX16文字)を表示する。 */
/* 引数			: 		SCHR	 : row			: 行(0～7)					  */
/* 				: const SCHR*	 : str			: 文字列(半角)				  */
/* 				: 		SCHR	 : align		: 位置揃え					  */
/*				:				 :				:  _LEFT_ALIGN_   (左揃え)	  */
/*				:				 :				:  _CENTER_ALIGN_ (中央揃え)  */
/*				:				 :				:  _RIGHT_ALIGN_  (右揃え)	  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void WriteAlignString( SCHR row, const SCHR* str, SCHR align )
{
	SCHR	len = 0;
	
	/* 文字列長計算 */
	for( len = 0; *(str + len ) != '\0'; len++ );
	
	/* 表示 */	
	switch( align ){
		case _ALIGN_LEFT_:						/* 左揃え					  */
			WriteString( row, 0, str );
			break;
		case _ALIGN_CENTER_:					/* 中央揃え					  */
			WriteString( row, ( 16 - len ) / 2, str );
			break;
		case _ALIGN_RIGHT_:						/* 右揃え					  */
			WriteString( row, (16 - len ), str );
			break;
		default:								/* その他（→エラー表示）	  */
			WriteAlignString( 0, "ERROR!!", _ALIGN_CENTER_ );
			break;
	}
}

/* -------------------------------------------------------------------------- */
/* 関数名		: DrawBMP													  */
/* 機能名		: BMP画像表示												  */
/* 機能概要		: LCDにモノクロBMP画像(64x128)を表示する					  */
/* 引数			: const uint8_t* : bmp			: BMP画像					  */
/* 				: 		UCHR	 : mode			: 表示モード				  */
/*				:				 :				:  _NORMAL_   (通常表示)	  */
/*				:				 :				:  _REVERSE_  (反転表示)	  */
/* 戻り値		: なし														  */
/* 作成日		: 2016/10/26	田中 翔吾									  */
/* -------------------------------------------------------------------------- */
void DrawBMP( const uint8_t* bmp, UCHR mode )
{
	USHT col = 0;
	USHT row = 0;

	for( row = 0; row < 8; row++ ){
		for( col = 0; col < 128; col++ ){
			switch( mode ){
				case _NORMAL_:					/* 通常表示					  */
					WriteLCD( row, col, pgm_read_byte( bmp ) );
					break;
				case _REVERSAL_:				/* 反転表示					  */
					WriteLCD( row, col, ~( pgm_read_byte( bmp ) ) );
					break;
				default:						/* その他（→エラー表示）	  */
					WriteAlignString( 0, "ERROR!!", _ALIGN_CENTER_ );
					break;
			}
			bmp++;	
		}
	}
	
}