/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
 */

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
 */
#include "mcc_generated_files/system/system.h"
#define REFERENCE_VOL_1_VALUE (0x3A)  // DAC DATA Register value to generate 0.75V
#define REFERENCE_VOL_2_VALUE (0xD5)  // DAC DATA Register value to generate 2.75V

typedef enum 
{
    REFERENCE_VOLTAGE_1,
    REFERENCE_VOLTAGE_2
} ref_voltage_state_t;

typedef enum 
{
    PRESSED,
    RELEASED
} switch_state_t;

switch_state_t switchSW0 = RELEASED;
ref_voltage_state_t referenceVoltageState = REFERENCE_VOLTAGE_1;
void Timer4_UserInterruptHandler(void);

/*
    Main application
 */

int main(void) 
{
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    Timer4_OverflowCallbackRegister(Timer4_UserInterruptHandler);

    while (1) 
    {
        /* Checks if switch is pressed. The DAC output is used as a reference voltage to Comparator
         * and is given to it's positive input. By default the DAC reference voltage is 0.75V.
         * On switch press DAC data register is updated to generate a reference voltage of 2.75V.
         * On further switch press, DAC output is set to 0.75V and this process repeats.
         *
         * */
        if (switchSW0 == PRESSED)
        {
            LED0_Toggle();
            if (referenceVoltageState == REFERENCE_VOLTAGE_1) 
            {
                referenceVoltageState = REFERENCE_VOLTAGE_2;
                DAC1_SetOutput(REFERENCE_VOL_2_VALUE);
            } 
            else 
            {
                referenceVoltageState = REFERENCE_VOLTAGE_1;
                DAC1_SetOutput(REFERENCE_VOL_1_VALUE);
            }
            switchSW0 = RELEASED;
        }
    }
}

/*
  @Description
    Interrupt handler routine for Timer4 overflow to detect switch press
  @Preconditions
    None
  @Param
    None
  @Returns
    None      
 */
void Timer4_UserInterruptHandler(void) 
{
    switchSW0 = PRESSED;
}
