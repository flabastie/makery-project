/*
 * alert function
 */

 #include "Timer.h"

 void alert(){
  if(alert_state == 0){
    buzzer_low();
    alert_state = 1;
    int afterEvent = t.after(10000, doAfter);
  }
 }


void doAfter()
{
  alert_state = 0;
}

