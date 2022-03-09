
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Reference Voltage Generation using DAC of PIC18F57Q43 Microcontroller

## Related Documentation

- [PIC18F57Q43 Data Sheet](https://www.microchip.com/DS40002147)

## Objective

This application example highlights the usage of 8-bit DAC of PIC18F57Q43 as a reference voltage to CMP. This can be used in level sensing applications using voltage comparator. Two reference voltages, a lower reference voltage of 0.75 V and a higher reference voltage of 2.75 V are generated by changing DAC output dynamically upon switch press. On-board LED toggles on each switch press event.

![block_diagram](images/block_diagram.png)

In this application, DAC is configured to use VDD as the positive reference and ground as the negative reference. On each switch press event, DAC data register is updated to generate the respective reference voltage. TMR4  is used in monostable mode to automate the switch debouncing. 

A triangular wave of 3V peak to peak is generated using function generator which is connected to the negative channel of CMP. DAC output is connected to the positive channel of CMP. The CMP is configured in inverted polarity so that when triangular wave input is less than reference voltage, comparator gives a logic low output. When triangular wave input is greater than reference voltage, comparator gives a logic high output. Using the two reference voltages provided by DAC, two voltage levels can be detected using comparator. The reference voltage by DAC, function generator output and comparator output can be observed on oscilloscope/logic analyzer.

## Software Used

- MPLAB® X IDE [v6.00.0 or newer](https://www.microchip.com/mplab/mplab-x-ide)
- XC8 Compiler [v2.35.0 or newer](https://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) [v5.1.0 or newer](https://www.microchip.com/mplab/mplab-code-configurator)
- Microchip PIC18F-Q series Device Support [v1.13.211 or newer](https://packs.download.microchip.com/)

## Hardware Used

- [PIC18F57Q43 Curiosity Nano Evaluation Kit](https://www.microchip.com/en-us/development-tool/DM164150)
- Logic analyzer/Oscilloscope
- Function Generator

## Hardware Setup

![hardware_setup](images/hardware_setup.png)

This demo is implemented using PIC18F57Q43 Curiosity Nano Evaluation Kit. Connect function generator output to pin RA0 of CNANO. Connect the same point to one of the analog channels of logic analyzer. Connect pin RA4 to a digital channel and pin RA2 to another analog channel of logic analyzer. The negative terminal of each channel, function generator GND and CNANO ground are connected for common GND. 

## Pin Connection Table

|Microcontroller Pin| Signal Description | 
|:------------------:|:-----------------:|
| RA0| CMP IN0- | 
| RA4 |CMP Output | 
| RA2 | DAC1 Buffered Output | 
| RB4 | SW0 | 
| RF3 | LED0 | 

## Demo Operation

Upon power-up the onboard LED of CNANO is turned ON. Observe the results in logic analyzer/oscilloscope. By default, the reference voltage generated by DAC is lower reference voltage of 0.75V. When function generator output is above 0.75 V, comparator output is logic high and when it is less than 0.75 V, comparator gives a logic low output.

![demo1](images/demo1.png)

Now press the on-board switch. The LED toggles and reference voltage generated by DAC changes to 2.75 V. Observe the results again in logic analyzer/oscilloscope. Now, when the function generator output is above 2.75 V, comparator output is logic high and when it is less than 2.75 V, comparator gives a logic low output.

![demo2](images/demo2.png)

## Peripheral Configuration

This section explains how to configure the peripherals using MPLAB X IDE with MCC plugin for recreation of the project. 

Refer [Software Used section] (https://github.com/microchip-pic-avr-examples/pic18f57q43-dac-reference-voltage-generation-mplab-mcc/blob/master/README.md#software-used)to install required tools to recreate the project.

Additional Links: [MCC Melody Technical Reference](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=MCC.MELODY.INTRODUCTION&version=latest&redirect=true)

| Peripherals               | Configuration                                                                                                                                                                                                                                                                                                                                                                                                  | Usage                                                                         |
|---------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------|
|    <br>Clock Control      |    <br>Clock source - HFINTOSC<br>HF Internal Clock - 4MHz<br>Clock Divider   – 4                                                                                                                                                                                                                                                                                                         |    <br>1 MHz System  clock                                                                     |
|    <br>TMR4               |    <br>Enable Timer<br>Control Mode - Monostable <br>External Reset Source - T4CKIPPS pin<br>Start/Reset Option - Starts on falling edge on TMR_ers<br>Clock Source - MFINTOSC_31.25KHz<br>Polarity - Rising edge<br>Prescaler - 1:64<br>Postscaler - 1:1<br>Time Period - 0.1s<br>TMR Interrupt Enabled<br>                                                                                                                                                                   |    <br>Used in monostable mode to  automate switch debouncing  |
|    <br>DAC1               |    <br>Enable DAC<br>Vdd - 3.3<br>DAC Positive reference selection - VDD<br>DAC Negative reference selection - VSS<br>DAC Output Enable Selection - DACOUT1 Enabled and DACOUT2 Disabled<br>   <br>     |    <br>Used to generate reference voltages to CMP<br>   <br>                            |
|    <br>CMP                |   <br>Enable Comparator<br>Enable Synchronous Mode - asynchronous<br>Positive Input Selection - DACOUT<br>Negative Input Selection - CIN0-<br>Output Polarity - inverted<br> <br> |    <br>Used for lower and higher reference voltage detection<br>   <br>     |

- **System Settings**

![system_settings](images/system_settings.png)

<br />

- **Add DAC, CMP and TMR4 peripherals**

![peripherals](images/peripherals.png)

<br />

- **DAC**
 
![dac](images/dac.png)

<br />

- **CMP**
 
![cmp](images/cmp.png)

<br />

- **TMR4**
 
![tmr4_1](images/tmr4_1.png)

<br />

![tmr4_2](images/tmr4_2.png)

<br />

 **Pin Grid View**
 
1.	Verify DAC output on pin RA2,CMP input (C1Inx-) on RA0 and CMP output on  RA4
2.	Configure T4IN on pin RB4 
3.	Configure pin RF3 as output for LED

![pin_grid1](images/pin_grid1.png)

<br />

![pin_grid2](images/pin_grid2.png)

<br />

- **Pins**

1.	Verify weak pull up is enabled on Pin RB4
2.	Rename pin RF3 to LED0

![pins](images/pins.png)

<br />

## Summary

A lower and higher reference voltages are generated using DAC peripheral of PIC18F57Q43 microcontroller which can be used for level sensing application using CMP.
