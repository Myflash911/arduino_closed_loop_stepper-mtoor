#ifndef __CONFIG__H_
#define __CONFIG__H_


#define PIN_STEP_OUT 16 
#define PIN_IN_A     5
#define PIN_IN_B     4
#define PIN_EN_OUT   0
#define PIN_LED      2
#define PIN_STEP_IN  14
#define PIN_DIR_IN   12
#define PIN_EN_IN    13
#define PIN_DIR_OUT  15


//#define ENCODER_PULSES_PER_REV 256.0 //State change per Revolution (A+B) (AS5040)
#define ENCODER_PULSES_PER_REV 400.0 //State change per Revolution (A+B) (HN3806-AB-400N)


#define NEMA_MOTOR_FULL_STEPS 200.0
#define NEMA_MOTOR_MICROSTEPS 16
#define NEMA_MOTOR_PPR (NEMA_MOTOR_FULL_STEPS * NEMA_MOTOR_MICROSTEPS)


#define FLIP_ENCODER //enable if rotor position repairing is done wrong direction

#define ENABLE_PRINTS 1


  #define STEP_ERROR_MAX 40 //Start position repairing if position deviation is more than this
  #define STEP_ERROR_MIN 5 //Stop position repairing if position deviation is less than this
  #define STEP_MOTOR_REV_PER_SEC 3.5 //revolutions/second. Fixing speed

//Modes explained https://www.linearmotiontips.com/what-is-quadrature-encoding/
//#define X1_ENCODING   // 1x the resolution of the encoder
//#define X2_ENCODING //doubles the resolution of the encoder
#define X4_ENCODING //quadruples the resolution of the encoder

#ifdef X1_ENCODING
 #define ENCODER_RESOLUTION (ENCODER_PULSES_PER_REV)
#endif
#ifdef X2_ENCODING
 #define ENCODER_RESOLUTION (2*ENCODER_PULSES_PER_REV)
#endif
#ifdef X4_ENCODING
 #define ENCODER_RESOLUTION (4*ENCODER_PULSES_PER_REV)
#endif


#ifdef STEP_LOSS_COMPENSATION
  #ifdef LOAD_POSITION_CONTROL
    #error "Selected STEP_LOSS_COMPENSATION & LOAD_POSITION_CONTROL!!"
  #endif
#endif
#endif
