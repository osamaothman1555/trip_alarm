#include "mbed.h"

class Alarm_tune{
    private:
    PwmOut sound;
     int a, T;
     float  freq, interrupt_period;
   
    public:
  
    // using ticker called in constructor the constructor, the speaker is turned off and on 
    // by calling toggle every half period. 
  
    Alarm_tune(PinName speak):sound(speak) {
        };
        
    ~Alarm_tune(){
        };
        
        void set_frequency(int frequency){
            freq = frequency;
            }
            
    // since we cant read the speaker input switching a variable that has the same value as speaker is used
    
    // produces a tune on the speaker using PWM 
    void tune(){
            sound.write(0.5);
            sound.period(0.000111);
            wait(0.04);
            sound.period(0.000143);
            wait(0.04);
            sound.write(0);
    }
};
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//end of class

class sensor{
    
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
    sensor( PinName Digi_out, PinName Ana_in, float compare_time, float sample_time): 
    LED(Digi_out), rise(0), fall(0), TCRTana(Ana_in), voltage(0), alarm(PA_11){
    // ticker that calls compare_voltage function to check if object is close every certain period
    led_control.attach(callback(this,&sensor::compare_voltage), compare_time);
    
    // ticker that calls  sample function to sample and update the sensors voltage
    sampler.attach(callback(this,&sensor::sample), sample_time);
    
    // intialising the sensor and LED
    VDD = 3.3;
    LED = 0;
    };
    
    void toggle_v2(){
        LED = !LED;
    }
        
    float get_voltage(){return TCRTana.read()*VDD;};
    
    // checks the voltage of the sensor
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
     
};
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//end of class

//PinName Digi_out, PinName Ana_in, float compare_time, float sample_time

int main() {
    sensor TCRT5000( PC_8, PC_5, 0.01,0.00001 ); // 3 male to female, cn10, cn10, cn7, note use 200 ohm for led by using potntionmeter on breadboard
    
    // while loop that keeps the program going
    while(1) {
        
    }
}
