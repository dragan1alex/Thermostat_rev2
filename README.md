# Thermostat rev2


DISCLAIMER:
This is a hobby project, it will be completed as the free time allows it :)


This is the second revision of the thermostat, it is an exercise to understand how a TFT panel works and how to interpret capacitive touch data.

Initially the project started as a pure LCD developement board, but one thing lead to another and now it has WiFi, a temperature + humidity sensor, SPI Flash, a relay and the LCD of course.

The project is based on the STM32F730 Arm® Cortex®-M7 microcontroller set up to run FreeRTOS as the main processor. 
It should have enough processing power to dynamically display some data, but not enough memory to manage a full resolution buffer (to make things interesting).

Besides that, a WiFi module (ESP-12F) is used purely as a network interface and web server, all the logic happens inside the STM.

ToDo: Implement the LCD driver once the LCD arrives, due to current events the shipments from China are slower than usual. 
Also implement an LCD control task, LCD display models and interface logic.

The written code can be found in /Core/Inc and /Core/Src. It is not yet docummented but I tried to make the functions self-explanatory.
