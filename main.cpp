

// Includes
#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "stdio.h"

// objects
Gamepad pad;
N5110 lcd;

void check_buttons();

int main()
{
    lcd.init();
    lcd.setContrast(0.5);
    pad.init();

    lcd.backLightOn();
    lcd.printString("Hello Gamepad!",0,0);
    lcd.refresh();
    pad.tone(1000.0,2.0);

    // 10 seconds to tune contrast
    for (int i = 0; i < 1000; i++) {
        lcd.setContrast( pad.read_pot1());
        wait_ms(10);
    }

    // Flash LEDs for 2 seconds
    for (int i = 0; i < 10; i++) {
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);
    }

    // Fade LEDs
    for (float x = 0.0f; x <= 1.0f ; x+=0.1f) {
        pad.leds(x);
        wait(0.2);
    }

    // Turn off LEDs
    pad.leds_off();

    // Then turn on one-by-one
    for (int n = 1; n <= 6; n++) {
        pad.led(n,0.5);
        wait(0.5);
    }

    // Turn off LEDs
    pad.leds_off();

    // Now keep looping
    while(1) {
        pad.leds_off();
        lcd.clear();   
        // can tweak contrast
        lcd.setContrast( pad.read_pot1());

        // read buttons 
        check_buttons();

        // Draw big circle
        lcd.drawCircle(WIDTH/2,HEIGHT/2,20,FILL_TRANSPARENT);  // x,y,radius,transparent with outline
        // then draw a smaller one based on the joystick position
        Vector2D coord = pad.get_mapped_coord();
        float x = coord.x;
        float y = coord.y;
        lcd.drawCircle(WIDTH/2+int(20*x),HEIGHT/2-int(20*y),3,FILL_TRANSPARENT);
        
        // update the display
        lcd.refresh();
        // 5 frames per second
        wait(1.0f/5.0f);
    }
}

void check_buttons()
{
    // here we check if a button pressed
    // if so, print on the LCD, flash an LED and make a beep
    if ( pad.A_pressed())  {
        lcd.printChar('A',0,0);
        pad.led(1,0.5);
        pad.tone(1000.0,0.2);
        printf("A pressed\n");
    }
    if ( pad.B_pressed())  {
        lcd.printChar('B',0,1);
        pad.led(2,0.5);
        pad.tone(1000.0,0.2);
        printf("B pressed\n");
    }
    if ( pad.X_pressed())  {
        lcd.printChar('X',0,2);
        pad.led(3,0.5);
        pad.tone(1000.0,0.2);
        printf("X pressed\n");
    }
    if ( pad.Y_pressed() ) {
        lcd.printChar('Y',0,3);
        pad.led(4,0.5);
        pad.tone(1000.0,0.2);
        printf("Y pressed\n");
    }
    if ( pad.start_pressed()) {
        lcd.printChar('S',78,2);
        pad.led(5,0.5);
        pad.tone(1000.0,0.2);
        printf("Start pressed\n");
    }


}