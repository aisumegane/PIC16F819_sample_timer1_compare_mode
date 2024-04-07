/*
 * File:   register_setup.c
 * Author: �XMEGANE
 *
 * Created on 2024/03/27, 21:17
 */


#include <xc.h>

/*header*/
#include "grobal_macro.h"
#include "register_setup.h"

/*grobal val*/


/*global func prototype*/
void pic819_register_setup_byte_set(void);
void pic819_register_setup(void);

void oscillator_setup(void);
void option_reg_setup(void);
void interrupt_setup(void);
void io_port_setup(void);
void ad_converter_setup();

void timer0_setup();
void timer1_setup();

void pic819_register_setup(void)
{         
    /*�����݋֎~*/
    INTCONbits.GIE = CLEAR;         // �O���[�o�����荞�݋֎~
    INTCONbits.PEIE = CLEAR;        // ���t�F���������݋֎~
    
    
    oscillator_setup();         /*�������U��ݒ�*/
    option_reg_setup();         /*�I�v�V�����ݒ�*/
    interrupt_setup();          /*�����ݐݒ�*/
    io_port_setup();            /*IO�|�[�g�ݒ�*/
    ad_converter_setup();       /*AD�R���o�[�^�ݒ�*/
    
    timer0_setup();             /*Timer0�ݒ�*/
    timer1_setup();             /*Timer1�ݒ�*/
}

void oscillator_setup(void)
{   /* OSCCON */    /*datasheet P.40*/  /*�������U��g�p�A8MHz�ɐݒ�*/
    OSCCONbits.IRCF2 = SET;
    OSCCONbits.IRCF1 = SET;
    OSCCONbits.IRCF0 = SET;
}

void option_reg_setup(void)
{   /*OPTION_REG*//*datasheet P.19*//*WDT�^�C�}�A�|�[�g�����ꕔ�ݒ�*/
    OPTION_REGbits.nRBPU   = CLEAR;    /* PORT-B Pull-up Enable bit (1:Disable / 0:Enable) */
    OPTION_REGbits.INTEDG  = SET;      /* RB0/INT pin Interrupt Edge Select bit (1:rising edge / 0:falling edge) */
    OPTION_REGbits.T0CS    = CLEAR;    /* TMR0 Clock Source Select bit (1:T0CKI pin / 0:Internal (CKLO)) */
    OPTION_REGbits.T0SE    = CLEAR;    /* TMR0 Source Edge Select bit(1:high-to-low transition on T0CKI / 0:low-to-high transition on T0CKI) */
    OPTION_REGbits.PSA     = CLEAR;    /* Prescaler Assignment bit (1:assigned to WDT / 0:assigned to Timer0) */
    OPTION_REGbits.PS2     = SET;    /* Prescaler Rate Select bit (PS2,1,0) */
    OPTION_REGbits.PS1     = CLEAR;
    OPTION_REGbits.PS0     = CLEAR;
    
    /*timer0�ݒ�*/
    TMR0 = 160;
}

void interrupt_setup(void)
{   /*INTCON*/    /*PIE1*/    /*datasheet P.20~21*/
    
    /*�����݋����Z�b�g*/
    /*INTCON*/
    INTCONbits.GIE = CLEAR;   /*�����݃x�N�^��1�����Ȃ��̂ł����֎~���Ƃ������ɂ���*/
    INTCONbits.PEIE = CLEAR;
    INTCONbits.TMR0IE = SET;
    INTCONbits.INTE = CLEAR;
    INTCONbits.RBIE = CLEAR;
    
    /*PIE1*/
    PIE1bits.ADIE = CLEAR;
    PIE1bits.SSPIE = CLEAR;
    PIE1bits.CCP1IE = SET;
    PIE1bits.TMR2IE = CLEAR;
    PIE1bits.TMR1IE = CLEAR;
    
    /*PIE2*/
    PIE2bits.EEIE = CLEAR;
    
    /*�����ݗv���t���O���Z�b�g*/
    /*INTCON*/
    INTCONbits.TMR0IF = CLEAR;
    INTCONbits.RBIF = CLEAR;
    
    /*PIR1*/
    PIR1bits.ADIF = CLEAR;
    PIR1bits.SSPIF = CLEAR;
    PIR1bits.CCP1IF = CLEAR;
    PIR1bits.TMR2IF = CLEAR;
    PIR1bits.TMR1IF = CLEAR;
    
    /*PIR2*/
    PIR2bits.EEIF = CLEAR;
}

void io_port_setup(void)
{   /*TRISA,TRISB,PORTA,PORTB*/ /*datasheet P.4(�s���z�u)*/ /*datasheet P.41*/  /*datasheet P.45*/  /*datasheet P.56(�I�v�V����)*/
    /*TRISA*/   /*1:���� / 0:�o��*/
#if 0
    TRISAbits.TRISA0 = SET;
    TRISAbits.TRISA1 = SET;
    TRISAbits.TRISA2 = SET;
    TRISAbits.TRISA3 = SET;
    
    TRISAbits.TRISA4 = SET;
    TRISAbits.TRISA5 = SET;
    TRISAbits.TRISA6 = SET;
    TRISAbits.TRISA7 = SET;
    
    /*TRISB*/   /*1:���� / 0:�o��*/
    TRISBbits.TRISB0 = SET;
    TRISBbits.TRISB1 = SET;
    TRISBbits.TRISB2 = SET;
    TRISBbits.TRISB3 = SET;
    
    TRISBbits.TRISB4 = SET;
    TRISBbits.TRISB5 = SET;
    TRISBbits.TRISB6 = SET;
    TRISBbits.TRISB7 = SET;
    
    /*PORTA*/   /*1:H���x���o�� / 0:L���x���o��*/ 
    PORTAbits.RA0 = CLEAR;
    PORTAbits.RA1 = CLEAR;
    PORTAbits.RA2 = CLEAR;
    PORTAbits.RA3 = CLEAR;
    
    PORTAbits.RA4 = CLEAR;
    PORTAbits.RA5 = CLEAR;
    PORTAbits.RA6 = CLEAR;
    PORTAbits.RA7 = CLEAR;
    
    /*PORTB*/   /*1:H���x���o�� / 0:L���x���o��*/
    PORTBbits.RB0 = CLEAR;
    PORTBbits.RB1 = CLEAR;
    PORTBbits.RB2 = CLEAR;
    PORTBbits.RB3 = CLEAR;
    
    PORTBbits.RB4 = CLEAR;
    PORTBbits.RB5 = CLEAR;
    PORTBbits.RB6 = CLEAR;
    PORTBbits.RB7 = CLEAR;
    
#else
    TRISAbits.TRISA0 = CLEAR;
    TRISAbits.TRISA1 = CLEAR;
    TRISAbits.TRISA2 = CLEAR;
    TRISAbits.TRISA3 = CLEAR;
    
    TRISAbits.TRISA4 = CLEAR;
    TRISAbits.TRISA5 = CLEAR;
    TRISAbits.TRISA6 = CLEAR;
    TRISAbits.TRISA7 = CLEAR;
    
    /*TRISB*/   /*1:���� / 0:�o��*/
    TRISBbits.TRISB0 = CLEAR;
    TRISBbits.TRISB1 = CLEAR;
    TRISBbits.TRISB2 = CLEAR;
    TRISBbits.TRISB3 = CLEAR;
    
    TRISBbits.TRISB4 = CLEAR;
    TRISBbits.TRISB5 = CLEAR;
    TRISBbits.TRISB6 = CLEAR;
    TRISBbits.TRISB7 = CLEAR;
    
    /*PORTA*/   /*1:H���x���o�� / 0:L���x���o��*/ 
    PORTAbits.RA0 = CLEAR;
    PORTAbits.RA1 = CLEAR;
    PORTAbits.RA2 = CLEAR;
    PORTAbits.RA3 = CLEAR;
    
    PORTAbits.RA4 = CLEAR;
    PORTAbits.RA5 = CLEAR;
    PORTAbits.RA6 = CLEAR;
    PORTAbits.RA7 = CLEAR;
    
    /*PORTB*/   /*1:H���x���o�� / 0:L���x���o��*/
    PORTBbits.RB0 = CLEAR;
    PORTBbits.RB1 = CLEAR;
    PORTBbits.RB2 = CLEAR;
    PORTBbits.RB3 = CLEAR;
    
    PORTBbits.RB4 = CLEAR;
    PORTBbits.RB5 = CLEAR;
    PORTBbits.RB6 = CLEAR;
    PORTBbits.RB7 = CLEAR;
#endif
}

void ad_converter_setup(void)
{   /*ADCON0,ADCON1*/ /*datasheet P.83~84*/
    /*ADCON0*/
    ADCON0bits.ADCS1 = CLEAR;   /*ADCON1bits.ADCS2 check*/
    ADCON0bits.ADCS0 = CLEAR;   /*ADCON1bits.ADCS2 check*/
    
    ADCON0bits.CHS2 = CLEAR;    /*AD�ϊ������Ȃ炱�̐ݒ�͖��Ӗ��Ȃ̂ŁA�g��Ȃ��Ȃ�K���Ȓl�����Ă���*/
    ADCON0bits.CHS1 = CLEAR;
    ADCON0bits.CHS0 = CLEAR;
    
    ADCON0bits.GO_nDONE = CLEAR;    /* AD�ϊ������Ŏ����N���A */
    ADCON0bits.ADON = CLEAR;
    
    /*ADCON1*/
    ADCON1bits.ADFM = SET;  /*�E(16bit�̂���10bit�g�p�A���ʃr�b�g�񂹂ď�ʂ͎g��Ȃ�)*/
    ADCON1bits.ADCS2 = CLEAR;
    
    ADCON1bits.PCFG3 = CLEAR;
    ADCON1bits.PCFG2 = SET;
    ADCON1bits.PCFG1 = SET;
    ADCON1bits.PCFG0 = CLEAR;
}

void timer0_setup(void)
{   /*timer0�ɂ��Ă̓I�v�V�����Őݒ�*/
    option_reg_setup();
}

void timer1_setup(void)
{   /*T1CON*/ /*datasheet P.59*/
    /*T1CON*/
    T1CONbits.T1CKPS1 = SET;      /*(Fsoc/4)��8���� */ /* 2MHz/8 = 250kHz(0.000,004 sec) */
    T1CONbits.T1CKPS0 = SET;
    T1CONbits.T1OSCEN = CLEAR;      /*for external clock*/        
    T1CONbits.nT1SYNC = SET;        /*for external clock*/
    T1CONbits.TMR1CS = CLEAR;       /*Internal clock*/
    T1CONbits.TMR1ON = CLEAR;

    /*CCP1CON*/ /*datasheet P.67*/
    /*CCP1CONbits_t.CCP1X = SET/CLEAR;*/    /* ���[�h�p? ���Ɏg��Ȃ� */
    /*CCP1CONbits_t.CCP1Y = SET/CLEAR;*/    /* ���[�h�p? ���Ɏg��Ȃ� */
    CCP1CONbits.CCP1M3 = SET;
    CCP1CONbits.CCP1M2 = CLEAR;
    CCP1CONbits.CCP1M1 = SET;
    CCP1CONbits.CCP1M0 = SET;
    
    /*CCPR1H,CCPR1L*/
    /* ������g���ݒ� = 10ms = 0.000,004 sec * 25000(0x61A8) */
    /* 0�܂Ń��[���I�[�o�[(MAX�̎���0�𐔂���1�J�E���g����)�̂ŁA1���� */
    CCPR1H = 0x61;
    CCPR1L = 0xA7;
}