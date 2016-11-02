/* -------------------------------------------------------------------------- */
/* avr.h																	  */
/* CL21																		  */
/*																			  */
/* -------------------------------------------------------------------------- */
/* �ԍ�		�X�V����							���t		����			  */
/* -------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2016/06/28	�c�� �Č�		  */
/* -------------------------------------------------------------------------- */
#ifndef		AVR_LIBRARY_H_
#define		AVR_LIBRARY_H_

#ifndef		F_CPU
#define		F_CPU 8000000UL						/* 8MHz���U					  */
#endif

/* -------------------------------------------------------------------------- */
/* include�t�@�C��	    												  	  */
/* -------------------------------------------------------------------------- */
#include <avr/io.h>								/* AVR���o��				  */
#include <util/delay.h>							/* �f�B���C�֐�				  */
#include <avr/interrupt.h>						/* �����݃w�b�_				  */

/* -------------------------------------------------------------------------- */
/* typedef��`																  */
/* -------------------------------------------------------------------------- */
#ifndef _TYPEDEF
#define _TYPEDEF
typedef 		 char	SCHR;					/* char�^					  */
typedef unsigned char	UCHR;					/* unsigned char�^			  */
typedef 		 short	SSHT;					/* short�^					  */
typedef unsigned short	USHT;					/* unsigned short�^			  */
typedef 		 long	SLNG;					/* long�^					  */
typedef unsigned long	ULNG;					/* unsigned long�^			  */
typedef 		 int	SINT;					/* int�^					  */
typedef unsigned int	UINT;					/* unsigned int�^			  */
typedef			 double	DBLE;					/* double�^					  */
#endif

/* -------------------------------------------------------------------------- */
/* �}�N����`			    												  */
/* -------------------------------------------------------------------------- */
#define High(reg,bitno)	( reg |=  ( 1 << bitno ) )	/* Px_n��High��ݒ�		  */
#define Low(reg,bitno)	( reg &= ~( 1 << bitno ) )	/* Px_n��Low��ݒ�		  */
#define Rev(reg,bitno)	( reg ^=  ( 1 << bitno ) )	/* Px_n�𔽓]			  */

#define pinLevel(pin,lv)	( pin( PORT, lv ) )		/* �o�̓��x��(H/L)��ݒ�  */
#define pinMode(pin,mode)	( pin( DDR, mode ) )	/* ���o�͕���(I/O)��ݒ�  */

/* H/L Level ( lv ) --------------------------------------------------------- */
#define _HIGH_		High							/* High( 1 )			  */
#define _LOW_		Low								/* Low ( 0 )			  */
#define _REV_		Rev								/* Reverse( ���] ) 		  */

/* I/O Mode ( mode ) -------------------------------------------------------- */
#define _INPUT_		Low								/* ����					  */
#define _OUTPUT_	High							/* �o��					  */

/* �o�̓��x��(H/L)�ݒ� ------------------------------------------------------ */
#define ON(pin)			( pin( PORT, High ) )		/* High					  */
#define OFF(pin)		( pin( PORT, Low ) )		/* Low					  */

/* ���o�͕���(I/O)��ݒ� ---------------------------------------------------- */
#define INPUT(pin)		( pin( DDR, Low ) )			/* ����					  */
#define OUTPUT(pin)		( pin( DDR, High ) )		/* �o��					  */

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
/* �萔��`			      												      */
/* -------------------------------------------------------------------------- */
#define HIGH			(    1 )				/* H���x��					  */
#define LOW				(    0 )				/* L���x��					  */
#define SWT_OFF			( HIGH )				/* �X�C�b�`OFF���			  */
#define SWT_ON			(  LOW )				/* �X�C�b�`ON���			  */

/* A/D�ϊ��֌W�萔 ---------------------------------------------------------- */
#define ADC_MSK			( 0x03FF )				/* A/D�ϊ����ʗp�}�X�N(10Bit) */

/* �|�[�g-------------------------------------------------------------------- */
enum PORT{
	B_PORT,
	C_PORT,
	D_PORT
};

/* -------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾															  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* �֐���		: delay_ms													  */
/* �@�\��		: �f�B���C(ms)												  */
/* �@�\�T�v		: �����œn���ꂽ����(ms)�ҋ@����							  */
/* ����			: SINT			: ms		: �ҋ@����(ms)					  */
/* �߂�l		: �Ȃ�														  */
/* �쐬��		: 2016/06/14	�c�� �Č�									  */
/* -------------------------------------------------------------------------- */
void delay_ms( SINT ms );

/* -------------------------------------------------------------------------- */
/* �֐���		: delay_us													  */
/* �@�\��		: �f�B���C(��s)												  */
/* �@�\�T�v		: �����œn���ꂽ����(��s)�ҋ@����							  */
/* ����			: SINT			: ms		: �ҋ@����(��s)					  */
/* �߂�l		: �Ȃ�														  */
/* �쐬��		: 2016/06/14	�c�� �Č�									  */
/* -------------------------------------------------------------------------- */
void delay_us( SINT us );

/* -------------------------------------------------------------------------- */
/* �֐���		: GetRegState												  */
/* �@�\��		: ���W�X�^��Ԏ擾											  */
/* �@�\�T�v		: ���W�X�^�̔C�Ӄr�b�g�̏�Ԃ��擾����			 			  */
/* ����			: volatile	UCHR	: reg		: ���W�X�^					  */
/*				: 			UCHR	: bitno		: �r�b�g�ԍ�				  */
/* �߂�l		: 			UCHR	: LOW		: 0(Low)					  */
/* 				: 			UCHR	: HIGH		: 1(High)					  */
/* �쐬��		: 2016/06/29	�c�� �Č�									  */
/* -------------------------------------------------------------------------- */
UCHR GetRegState( volatile UCHR reg, UCHR bitno );

/* A/D�ϊ��֘A�֐� ---------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* �֐���		: SetADC													  */
/* �@�\��		: A/D�ϊ��ݒ�												  */
/* �@�\�T�v		: A/D�ϊ��̐ݒ���s��										  */
/* ����			: volatile	UCHR*	: ddrx		: �|�[�g�������W�X�^(DDRx)	  */
/* 				: volatile	UCHR*	: pinx		: �|�[�g���̓��W�X�^(PINx)	  */
/* 				: 			UCHR	: bitno		: �r�b�g�ԍ�				  */
/* �߂�l		: �Ȃ�														  */
/* �쐬��		: 2016/06/29	�c�� �Č�									  */
/* -------------------------------------------------------------------------- */
void SetADC( volatile UCHR* ddrx, volatile UCHR* pinx, UCHR bitno );

/* -------------------------------------------------------------------------- */
/* �֐���		: GetADC													  */
/* �@�\��		: A/D�ϊ��l�擾												  */
/* �@�\�T�v		: A/D�ϊ����A���ʂ�Ԃ��B									  */
/* ����			: �Ȃ�														  */
/* �߂�l		: USHT			: sValue	: A/D�ϊ��l						  */
/* �쐬��		: 2016/06/29	�c�� �Č�									  */
/* -------------------------------------------------------------------------- */
USHT GetADC( void );

/* �����݊֘A�֐� ---------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* �֐���		: SetTimerInterrupt											  */
/* �@�\��		: �^�C�}�����ݐݒ�											  */
/* �@�\�T�v		: �^�C�}�����݂̃��W�X�^�ݒ���s���B						  */
/* ����			: DBLE			: ms		: �����݊Ԋu(ms)				  */
/* �߂�l		: �Ȃ�														  */
/* �쐬��		: 2016/09/07	�c�� �Č�									  */
/* -------------------------------------------------------------------------- */
void SetTimerInterrupt( DBLE ms );

/* -------------------------------------------------------------------------- */
/* �֐���		: SetExternalInterrupt										  */
/* �@�\��		: �O�������ݐݒ�(���G�b�W)									  */
/* �@�\�T�v		: �O�������݂̃��W�X�^�ݒ���s���B							  */
/* ����			: enum PORT		: port			: �|�[�g		 			  */
/* 				: UCHR			: bitno			: �r�b�g�ԍ�				  */
/* �߂�l		: �Ȃ�														  */
/* �쐬��		: 2016/09/07	�c�� �Č�									  */
/* -------------------------------------------------------------------------- */
void SetExternalInterrupt( enum PORT port , UCHR bitno );

#endif

/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */
