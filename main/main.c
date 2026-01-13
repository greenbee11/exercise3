/*
Eric Greenberg
1/13/25
Turns on an LED every other time the button is pressed, as long as the other button is pressed
Needs two buttons and an LED

*/


#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define LED_PIN         // Choose your LED pin
#define BUTTON_PIN       // Choose your button pin

void app_main(void) {

    // TO-DO: Configure LED output
    // TO-DO: Configure Button input
    // gpio_reset_pin(), gpio_set_direction(), gpio_pullup_dis(), and gpio_pulldown_dis() and gpio_intr_disable()
    gpio_reset_pin(GPIO_NUM_10);
    gpio_set_direction(GPIO_NUM_10, GPIO_MODE_OUTPUT);
    gpio_pullup_dis(GPIO_NUM_10);
    gpio_pulldown_dis(GPIO_NUM_10);
    gpio_intr_disable(GPIO_NUM_10);

    gpio_reset_pin(GPIO_NUM_4);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
    gpio_pullup_en(GPIO_NUM_4);

    gpio_reset_pin(GPIO_NUM_5);
    gpio_set_direction(GPIO_NUM_5, GPIO_MODE_INPUT);
    gpio_pullup_en(GPIO_NUM_5);

    bool bstate = false;   // Button state (true = pressed, false = not pressed)
    bool lstate = false;   // LED state (true = ON, false = OFF)
    bool pressed;
    bool pressedtwo;


    while (1) {
    // TO-DO: Implement LED toggle and button logic here
        // vTaskDelay(500 / portTICK_PERIOD_MS); //Use appropriate loop delays
        // gpio_set_level(GPIO_NUM_10, 0);
        // vTaskDelay(500 / portTICK_PERIOD_MS);
        // gpio_set_level(GPIO_NUM_10, 1);

        pressed = gpio_get_level(GPIO_NUM_4) == 0;     // Input active low button
        pressedtwo = gpio_get_level(GPIO_NUM_5) == 0;

        if (!bstate && pressed && pressedtwo) {                  // Released button, is now pressed
            bstate = true;                           // Remember button is pressed  
        }
   
        if (bstate && !pressed && pressedtwo) {                  // Pressed button, is now released
            lstate = !lstate;                        // Toggle LED state  
            bstate = false;                          // Remember button is released
        }
        gpio_set_level(GPIO_NUM_10, lstate);
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
