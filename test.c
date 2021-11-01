#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>                 // Required for the GPIO functions
#include <linux/interrupt.h>            // Required for the IRQ code
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Guillem Serra Cazorla");
MODULE_DESCRIPTION("Practica 1 Fase 1 ASO");
MODULE_VERSION("1.0");
 
static unsigned int gpioLED_A = 20;       ///< hard coding the LED gpio for this example to P9_23 (GPIO49)
static unsigned int gpioLED_B = 16;
static unsigned int gpioButton_A_On = 21;   ///< hard coding the button gpio for this example to P9_27 (GPIO115)
static unsigned int gpioButton_A_Off = 13;
static unsigned int gpioButton_B_On = 19;
static unsigned int gpioButton_B_Off = 26;



static unsigned int irqNumber_A_On;          ///< Used to share the IRQ number within this file
static unsigned int irqNumber_B_On;          ///< Used to share the IRQ number within this file
static unsigned int irqNumber_A_Off;          ///< Used to share the IRQ number within this file
static unsigned int irqNumber_B_Off;          ///< Used to share the IRQ number within this file

static unsigned int numberPresses = 0;  ///< For information, store the number of button presses
static bool     ledA = 0;          ///< Is the LED on or off? Used to invert its state (off by default)
static bool     ledB = 0;

/// Function prototype for the custom IRQ handler function -- see below for the implementation
static irq_handler_t  ebbgpio_irq_handler_buttonLedA_ON(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t  ebbgpio_irq_handler_buttonLedA_OFF(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t  ebbgpio_irq_handler_buttonLedB_ON(unsigned int irq, void *dev_id, struct pt_regs *regs);
static irq_handler_t  ebbgpio_irq_handler_buttonLedB_OFF(unsigned int irq, void *dev_id, struct pt_regs *regs);

 

static int __init ebbgpio_init(void){
   int result = 0;
   printk(KERN_INFO "GPIO_TEST: Initializing the GPIO_TEST LKM\n");
   // Is the GPIO a valid GPIO number (e.g., the BBB has 4x32 but not all available)
   if (!gpio_is_valid(gpioLED_A) || !gpio_is_valid(gpioLED_B)){
      printk(KERN_INFO "GPIO_TEST: invalid LED GPIO\n");
      return -ENODEV;
   }
   // Going to set up the LED. It is a GPIO in output mode and will be on by default
   ledA = false;
   gpio_request(gpioLED_A, "sysfs");          // gpioLED is hardcoded to 49, request it
   gpio_direction_output(gpioLED_A, ledA);   // Set the gpio to be in output mode and on
// gpio_set_value(gpioLED, ledOn);          // Not required as set by line above (here for reference)
   gpio_export(gpioLED_A, false);             // Causes gpio49 to appear in /sys/class/gpio
                     // the bool argument prevents the direction from being changed
   ledB = false;
   gpio_request(gpioLED_B, "sysfs");          // gpioLED is hardcoded to 49, request it
   gpio_direction_output(gpioLED_B, ledB);   // Set the gpio to be in output mode and on
// gpio_set_value(gpioLED, ledOn);          // Not required as set by line above (here for reference)
   gpio_export(gpioLED_B, false);             // Causes gpio49 to appear in /sys/class/gpio
                     // the bool argument prevents the direction from being changed
   gpio_request(gpioButton_A_On, "sysfs");       // Set up the gpioButton
   gpio_direction_input(gpioButton_A_On);        // Set the button GPIO to be an input
   gpio_set_debounce(gpioButton_A_On, 200);      // Debounce the button with a delay of 200ms
   gpio_export(gpioButton_A_On, false);          // Causes gpio115 to appear in /sys/class/gpio
                     // the bool argument prevents the direction from being changed

   gpio_request(gpioButton_A_Off, "sysfs");       // Set up the gpioButton
   gpio_direction_input(gpioButton_A_Off);        // Set the button GPIO to be an input
   gpio_set_debounce(gpioButton_A_Off, 200);      // Debounce the button with a delay of 200ms
   gpio_export(gpioButton_A_Off, false);          // Causes gpio115 to appear in /sys/class/gpio
                     // the bool argument prevents the direction from being changed

   gpio_request(gpioButton_B_On, "sysfs");       // Set up the gpioButton
   gpio_direction_input(gpioButton_B_On);        // Set the button GPIO to be an input
   gpio_set_debounce(gpioButton_B_On, 200);      // Debounce the button with a delay of 200ms
   gpio_export(gpioButton_B_On, false);          // Causes gpio115 to appear in /sys/class/gpio
                     // the bool argument prevents the direction from being changed

   gpio_request(gpioButton_B_Off, "sysfs");       // Set up the gpioButton
   gpio_direction_input(gpioButton_B_Off);        // Set the button GPIO to be an input
   gpio_set_debounce(gpioButton_B_Off, 200);      // Debounce the button with a delay of 200ms
   gpio_export(gpioButton_B_Off, false);          // Causes gpio115 to appear in /sys/class/gpio
                     // the bool argument prevents the direction from being changed
 
   // GPIO numbers and IRQ numbers are not the same! This function performs the mapping for us
   irqNumber_A_On = gpio_to_irq(gpioButton_A_On);
   
   // This next call requests an interrupt line
   result = request_irq(irqNumber_A_On,             // The interrupt number requested
                        (irq_handler_t) ebbgpio_irq_handler_buttonLedA_ON, // The pointer to the handler function below
                        IRQF_TRIGGER_RISING,   // Interrupt on rising edge (button press, not release)
                        "ebb_gpio_handler_buttonLedA_ON",    // Used in /proc/interrupts to identify the owner
                        NULL);                 // The *dev_id for shared interrupt lines, NULL is okay
   
    // GPIO numbers and IRQ numbers are not the same! This function performs the mapping for us
   irqNumber_B_On = gpio_to_irq(gpioButton_B_On);
   
   // This next call requests an interrupt line
   result = request_irq(irqNumber_B_On,             // The interrupt number requested
                        (irq_handler_t) ebbgpio_irq_handler_buttonLedB_ON, // The pointer to the handler function below
                        IRQF_TRIGGER_RISING,   // Interrupt on rising edge (button press, not release)
                        "ebb_gpio_handler_buttonLedB_ON",    // Used in /proc/interrupts to identify the owner
                        NULL);   

    // GPIO numbers and IRQ numbers are not the same! This function performs the mapping for us
   irqNumber_A_Off = gpio_to_irq(gpioButton_A_Off);
   
   // This next call requests an interrupt line
   result = request_irq(irqNumber_A_Off,             // The interrupt number requested
                        (irq_handler_t) ebbgpio_irq_handler_buttonLedA_OFF, // The pointer to the handler function below
                        IRQF_TRIGGER_RISING,   // Interrupt on rising edge (button press, not release)
                        "ebb_gpio_handler_buttonLed_A_OFF",    // Used in /proc/interrupts to identify the owner
                        NULL);   


    // GPIO numbers and IRQ numbers are not the same! This function performs the mapping for us
   irqNumber_B_Off = gpio_to_irq(gpioButton_B_Off);
   
   // This next call requests an interrupt line
   result = request_irq(irqNumber_B_Off,             // The interrupt number requested
                        (irq_handler_t) ebbgpio_irq_handler_buttonLedB_OFF, // The pointer to the handler function below
                        IRQF_TRIGGER_RISING,   // Interrupt on rising edge (button press, not release)
                        "ebb_gpio_handler_buttonLedB_OFF",    // Used in /proc/interrupts to identify the owner
                        NULL);   
 
   printk(KERN_INFO "GPIO_TEST: The interrupt request result is: %d\n", result);
   return result;
}
 

static void __exit ebbgpio_exit(void){
   printk(KERN_INFO "GPIO_TEST: The button was pressed %d times\n", numberPresses);
   gpio_set_value(gpioLED_A, 0);        
   gpio_set_value(gpioLED_B, 0);       // Turn the LED off, makes it clear the device was unloaded
   gpio_unexport(gpioLED_A);   
   gpio_unexport(gpioLED_B);                 // Unexport the LED GPIO
   free_irq(irqNumber_A_On, NULL);               // Free the IRQ number, no *dev_id required in this case
   free_irq(irqNumber_B_On, NULL);
   free_irq(irqNumber_A_Off, NULL);
   free_irq(irqNumber_B_Off, NULL);

   gpio_unexport(gpioButton_A_On);               // Unexport the Button GPIO
   gpio_unexport(gpioButton_A_Off);               // Unexport the Button GPIO
   gpio_unexport(gpioButton_B_On);               // Unexport the Button GPIO
   gpio_unexport(gpioButton_B_Off);               // Unexport the Button GPIO

   gpio_free(gpioLED_A);                      // Free the LED GPIO
   gpio_free(gpioLED_B);                   // Free the Button GPIO
   gpio_free(gpioButton_A_On);
   gpio_free(gpioButton_A_Off);
   gpio_free(gpioButton_B_On);
   gpio_free(gpioButton_B_Off);
   printk(KERN_INFO "GPIO_TEST: Goodbye from the LKM!\n");
}
 

static irq_handler_t ebbgpio_irq_handler_buttonLedB_ON(unsigned int irq, void *dev_id, struct pt_regs *regs){
   ledB = true;                          // Invert the LED state on each button press
   gpio_set_value(gpioLED_B, ledB);          // Set the physical LED accordingly

   //TODO: Change log
   printk(KERN_INFO "GPIO_ButtonB_ON: Interrupt! LED B on True\n");
   numberPresses++;                         // Global counter, will be outputted when the module is unloaded
   return (irq_handler_t) IRQ_HANDLED;      // Announce that the IRQ has been handled correctly
}

static irq_handler_t ebbgpio_irq_handler_buttonLedB_OFF(unsigned int irq, void *dev_id, struct pt_regs *regs){
   ledB = false;                          // Invert the LED state on each button press
   gpio_set_value(gpioLED_B, ledB); 
   
   //TODO: Change log
   printk(KERN_INFO "GPIO_ButtonB_OFF: Interrupt! LED B on False\n");
   numberPresses++;                         // Global counter, will be outputted when the module is unloaded
   return (irq_handler_t) IRQ_HANDLED;      // Announce that the IRQ has been handled correctly
}

static irq_handler_t ebbgpio_irq_handler_buttonLedA_ON(unsigned int irq, void *dev_id, struct pt_regs *regs){
   ledA = true;                          // Invert the LED state on each button press
   gpio_set_value(gpioLED_A, ledA);          // Set the physical LED accordingly

   //TODO: Change log
   printk(KERN_INFO "GPIO_ButtonA_ON: Interrupt! LED A on True\n");
   numberPresses++;                         // Global counter, will be outputted when the module is unloaded
   return (irq_handler_t) IRQ_HANDLED;      // Announce that the IRQ has been handled correctly
}

static irq_handler_t ebbgpio_irq_handler_buttonLedA_OFF(unsigned int irq, void *dev_id, struct pt_regs *regs){
   ledA = false;                          // Invert the LED state on each button press
   gpio_set_value(gpioLED_A, ledA);          // Set the physical LED accordingly

   //TODO: Change log
   printk(KERN_INFO "GPIO_ButtonA_OFF: Interrupt! LED A on False\n");
   numberPresses++;                         // Global counter, will be outputted when the module is unloaded
   return (irq_handler_t) IRQ_HANDLED;      // Announce that the IRQ has been handled correctly
}
 

module_init(ebbgpio_init);
module_exit(ebbgpio_exit);