/*
 * File:   interrupt.c
 * Author: �XMEGANE
 *
 * Created on 2024/03/27, 23:38
 */

/* �\�[�X�t�@�C���܂����Ŏg�����W�X�^�֘A�̊֐��͂����Œ�` */
/* �悭�g�����̈ȊO�̓��W�X�^���ł��ɂ��� */

/*�\�[�X���ʋL���Fgf*/

#include <xc.h>
#include "grobal_macro.h"
#include "grobal_function.h"

void gf_enable_interrupt(void);    /*�����݋��֐�*/
void gf_disable_interrupt(void);   /*�����݋֎~�֐�*/
void gf_timer1_start(void);        /*timer1 ����J�n�֐�*/
void gf_timer1_stop(void);         /*timer1 �����~�֐�*/



void gf_enable_interrupt(void)
{   /*interrup.c�ł͎g���Ȃ�(���G���g�����g?)*/
    INTCONbits.GIE = SET;         // �O���[�o�����荞�݋���
    INTCONbits.PEIE = SET;        // ���t�F���������݋��� 
}

void gf_disable_interrupt(void)
{   /*interrupt.c�ł͎g���Ȃ�(���G���g�����g?)*/
    INTCONbits.GIE = CLEAR;         // �O���[�o�����荞�݋֎~
    INTCONbits.PEIE = CLEAR;        // ���t�F���������݋֎~
}

void gf_timer1_start(void)
{   /*����N���Ŋ����ݗv�������Ȃ����m�F���邱��*/
    T1CONbits.TMR1ON = SET;
}

void gf_timer1_stop(void)
{   /*����N���Ŋ����ݗv�������Ȃ����m�F���邱��*/
    T1CONbits.TMR1ON = CLEAR;
}