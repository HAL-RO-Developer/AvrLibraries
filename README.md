#AvrLibraries
## Macro

### `#define High( reg, bitno )`
__レジスタの任意ビットをHigh(1)にします。__ 

例) PORTB0をHighにする。  
`High( PORTB, 0 );`

### `#define Low( reg, bitno )`
__レジスタの任意ビットをLow(0)にします。__

例) DDRD2をLowにする。  
`Low( DDRD, 2 );`

### `#define Rev( reg, bitno )`
__レジスタの任意ビットを反転します。__

例) PORTB0を反転する。  
`Rev( PORTB, 0 );`

## Function

### `void delay_ms( SINT ms )`
__引数で渡された時間(単位：ms)待機します。__

例) 10ms待機させる。  
`delay_ms( 10 );`

### `void delay_us( SINT us )`
__引数で渡された時間(単位：μs)待機します。__

例) 0.2ms(200μs)待機させる。  
`delay_us( 200 );`

### `UCHR GetRegState( volatile UCHR reg, UCHR bitno )`
__レジスタの任意ビットの状態(L/H)を取得します。__

例) A2ポート(PC2)につながっているプッシュボタンの状態を取得する。  
`state = GetRegState( PINC, 2 );`

### `void SetADC( volatile UCHR* ddrx, volatile UCHR* pinx, UCHR bitno )`
__任意ポートにA/D変換の設定を行います。__

例) A3ポート(PC3)にA/D変換設定を行う。  
`SetADC( &DDRC, &PINC, 3 );`

### `USHT GetADC( void )`

__A/D変換の結果を返します。__  
__この関数を呼ぶ前に必ずA/D変換の設定をしておいてください。__

例) A3ポート(PC3)にA/D変換設定を行い、結果をad_valに代入する。  
`SetADC( &DDRC, &PINC, 3 );`  
`ad_val = GetADC();`

### `SetTimerInterrupt( DBLE ms )`

__タイマ割込みのレジスタ設定および割込み許可を行います。__

例) 100ms間隔でタイマ割込みを動作させる。  
`SetTimerInterrupt( 100 );`

### `SetExternalInterrupt( enum PORT port, UCHR bitno )`

__外部割込みのレジスタ設定および割込み許可を行います。__

例) A0スイッチ(PC0)に外部割込み(PIN変化割込み)を動作させる。  
`SetExternalInterrupt( C_PORT, 0 );`