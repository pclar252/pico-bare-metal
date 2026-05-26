#include <emblib/reg.h>
#include <emblib/timer.h>
#include <stdint.h>

static inline volatile uint32_t *timer_reg(uint32_t offset) { return (volatile uint32_t *)(EM_TIMER0_BASE + offset); }

void em_timer0_intr_clr(uint8_t alarm) { em_reg_write(timer_reg(EM_TIMER0_INTR), (1u << alarm)); }

void em_timer0_inte_set(uint8_t alarm) { em_reg_set(timer_reg(EM_TIMER0_INTE), (1u << alarm)); }

void em_timer0_schedule_abs(uint8_t alarm, uint32_t time) {
  em_reg_write(timer_reg(EM_TIMER0_ALARM_BASE + alarm * EM_TIMER_ALARM_STRIDE), time);
}

void em_timer0_schedule_rel(uint8_t alarm, uint32_t delta) {
  uint32_t cur_time = em_reg_read(timer_reg(EM_TIMER0_TIMERAWL));
  em_reg_write(timer_reg(EM_TIMER0_ALARM_BASE + alarm * EM_TIMER_ALARM_STRIDE), cur_time + delta);
}
