/*
 * Pid_PWM.h
 *
 * Created: 26/01/2023 11:03:50
 *  Author: Enrico
 */ 


#ifndef PID_PWM_H_
#define PID_PWM_H_

extern void PID();
extern void PWM();
extern void Set_Velocita();
extern void avanti();
extern void indietro();
extern void sinistra();
extern void destra();
extern void stop_tutto();
extern void delay_movimento(int c);
extern void cubetto();
extern void Set_Servo( int duty_5);



#endif /* PID_PWM_H_ */