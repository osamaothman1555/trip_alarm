/*
	trip_alarm.cpp
	Purpose: Embedded system acting as a burgler trip alarm
 
	@author Osama Othman
	@version 1.3 11/04/2021
*/


#include "mbed.h"


// Alarm_tune object controls the speaker to produce a tune
class Alarm_tune{
    private:
    PwmOut sound;
     int a, T;
     float  freq, interrupt_period;
   
    public:
  
  	/*
	intialises Sensor object
	@param speak The PWM pin on microcontroller.
	*/
    Alarm_tune(PinName speak):sound(speak) {
        };
        
    ~Alarm_tune(){
        };
        
	void set_frequency(int frequency){
		freq = frequency;
		};

    // Produces a tune on the speaker using PWM sound connected to speaker
    void tune(){
		sound.write(0.5);
		sound.period(0.000111);
		wait(0.04);
		sound.period(0.000143);
		wait(0.04);
		sound.write(0);
		};
};//end of class


// Sensor object receives optical Sensor data and controls speaker through Alarm_tune object
class Sensor{
    
    private:
    int rise, fall;
    DigitalOut LED; 
    AnalogIn TCRTana; 
    Ticker led_control;    
    Ticker sampler; 
    float voltage; 
    float VDD; 
    Alarm_tune alarm;
     
    public:
	/*
	intialises Sensor object
	@param Digi_out The digital out pin of the LED.
	@param Ana_in The analogue in pin of the optical Sensor.
	@param compare_time The period of the ticker that performs action based on voltage.
	@param sample_time The period of the ticker that updates the voltage of the Sensor.
	*/
    Sensor( PinName Digi_out, PinName Ana_in, float compare_time, float sample_time): 
    LED(Digi_out), rise(0), fall(0), TCRTana(Ana_in), voltage(0), alarm(PA_11){
    // ticker that calls compare_voltage function to check if object is close every certain period
    led_control.attach(callback(this,&Sensor::compare_voltage), compare_time);
    
    // ticker that calls  sample function to sample and update the Sensors voltage
    sampler.attach(callback(this,&Sensor::sample), sample_time);
    
    // intialising the Sensor and LED
    VDD = 3.3;
    LED = 0;
    };
    
    void toggle_v2(){
        LED = !LED;
    }
       
    // checks the voltage of the Sensor
    void sample(){
        voltage = TCRTana.read()*VDD;
    };
    
    // function to turn on alarm when object is close i.e. voltage is above 1.6V
    void compare_voltage(){
      
      if(voltage > 1.6){ 
      alarm.tune();
      toggle_v2();
      }
      else{ LED = 0; }
    };
     
};//end of class

//PinName Digi_out, PinName Ana_in, float compare_time, float sample_time

int main() {
    Sensor TCRT5000( PC_8, PC_5, 0.01,0.00001 ); // 3 male to female, cn10, cn10, cn7, note use 200 ohm for led by using potntionmeter on breadboard
    
    // while loop that keeps the program going
    while(1) {
        
    }
}
