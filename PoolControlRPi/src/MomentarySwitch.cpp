/*
 * MomentarySwitch.cpp
 *
 *  Created on: Jun 28, 2020
 *      Author: dmounday
 */
#include "plog/Log.h"
#include "MomentarySwitch.h"
namespace pentair_control {

MomentarySwitch::MomentarySwitch(const std::string& id, const std::string& label, unsigned switcher_pin,
		unsigned button_pin, unsigned led_pin ):
	RelaySwitcher(id, label, switcher_pin, led_pin),
	momentary_(button_pin, GPIO::GPIO_PULL::DOWN, MIN_TRIGGER_INTERVAL, MIN_HOLD_INTERVAL),
	button_pin_ {button_pin},
	button_pushed_{false}
{
	// Lambda that sets the button_pushed boolean. Just an extra check on the state.
	momentary_.f_pushed = [this](){
		PLOG(plog::debug)<< "pushed";
		this->button_pushed_=true;
	};
	//
	// Lambda function to handle when momentary button is released.
	// If equipment is on then switch off, else switch on.
	momentary_.f_released = [this](std::chrono::nanoseconds nanosec){
		PLOG(plog::debug)<< "released";
		if ( button_pushed_ ){
			button_pushed_ = false;
			if ( State() == RelayState::OFF ){
			  PLOG(plog::info)<< Name() << ": "<< "Button ON";
				SwitchOn();
				return;
			}
			if ( State() == RelayState::ON ){
			  PLOG(plog::info)<< Name() << ": "<< "Button OFF";
				SwitchOff();
			}
		}
	};
	momentary_.start();
}

MomentarySwitch::~MomentarySwitch() {
	SwitchOff();
	momentary_.stop();
}
} // namespace pentair_control

