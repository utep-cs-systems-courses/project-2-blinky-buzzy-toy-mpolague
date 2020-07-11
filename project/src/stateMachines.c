#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

//variables that help button 1 and 4 work
int song_H[] = {220,196,147,220,196,147,220,196,147,131,147,220,196};
int song_W[] = {392,294,370,330,294,261,392,247,440,294};
int i = 0;
int j = 0;

char toggle_red()/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;/* always changes an led */
}

char toggle_green()/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

//helper method
void _state_advance() /*alternating between toggling red & green*/
{
  char changed = 0;
  
  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}

void state_advance()
{
  switch(switch_state)
    {
    case 1:
      //Does not play song continuously
      buzzer_set_period(song_W[j++]);
      switch_state = 0;
      break;
    case 2:
      //lights don't work
      _state_advance();
      break;
    case 3:
      //This will stop any of the actions going on regardless of action
      buzzer_off();
      lights_off();
      break;
    case 4:
      //Does not play song continuously
      buzzer_set_period(song_H[i++]);
      switch_state = 0;
      break;
    }
  switch_state = 0;
}


