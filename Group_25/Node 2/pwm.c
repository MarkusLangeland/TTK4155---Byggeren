
#include "pwm.h"
#include "sam.h"

#define MCK         84E6
#define PERIOD		20E-3
#define CPRDA       (int) (PERIOD * MCK / DIVA)
#define DIVA        84
#define CLK_A       1E6

#define DUTY_CYCLE_MIN 0.045 //min is 0.9
#define DUTY_CYCLE_MAX 0.105 //max is set to 2.1

static const uint32_t CLK_PRESCALAR = 1024;
static const double F_CHANNEL_5_CLOCK = MCK / DIVA;
static const uint32_t CPRD = PERIOD * MCK / DIVA;
static const double MIN_DUTY_CYCLE = 0.9 / 20;
static const double MAX_DUTY_CYCLE = 2.1 / 20;
#define WMH6 6
#define WMH5 5

#include "pwm.h"
#include "sam.h"

void pwm_init() {
	//wPC19 corresponds to pin44 on the shield
	PIOC->PIO_ABSR |= PIO_PC19B_PWMH5 ;

	PIOC->PIO_PDR |= PIO_PC19B_PWMH5;
	
	//PWM ID is 36
	PMC->PMC_PCER1 |= 1 << 4; 

	PWM->PWM_ENA = PWM_ENA_CHID5;
	
	PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(DIVA);
	
	PWM->PWM_CH_NUM[WMH5].PWM_CMR = PWM_CMR_CPRE_CLKA;
	
	PWM->PWM_CH_NUM[WMH5].PWM_CPRD = PWM_CPRD_CPRD(CPRDA);
}


void pwm_set_duty_cycle(float duty_cycle) {
	//Set maximum and minimum duty_cycle.
	duty_cycle = duty_cycle < DUTY_CYCLE_MIN ? DUTY_CYCLE_MIN : duty_cycle;
	duty_cycle = duty_cycle > DUTY_CYCLE_MAX ? DUTY_CYCLE_MAX : duty_cycle;
	
	PWM->PWM_CH_NUM[5].PWM_CDTY = PWM_CDTY_CDTY( (int)(PWM->PWM_CH_NUM[5].PWM_CPRD*(1 - duty_cycle)) );
}
