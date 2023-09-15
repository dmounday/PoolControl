/*
 * MomentarySwitch.h
 *
 *  Created on: Jun 28, 2020
 *      Author: dmounday
 */

#ifndef SRC_MOMENTARYSWITCH_H_
#define SRC_MOMENTARYSWITCH_H_

#include "RelaySwitcher.h"
namespace pentair_control {

constexpr std::chrono::nanoseconds MIN_TRIGGER_INTERVAL {std::chrono::nanoseconds(2*1000*1000)};
constexpr std::chrono::nanoseconds MIN_HOLD_INTERVAL {std::chrono::nanoseconds(500*1000*1000)};

/**
 * @brief MomentarySwitch class is derived from RelaySwither and is used 
 * if the is a momnetary push button switch configured to control the equipment.
 * 
 */
class MomentarySwitch: public RelaySwitcher {
public:
/**
 * @brief Construct a new Momentary Switch object for the equipment id.
 * 
 * @param id Name of equipment i.e. "MainPump"
 * @param label logging label.
 * @param switcher_pin GPIO pin that controls relay.
 * @param button_pin GPIO pin that monitors the push button.
 * @param led_pin status LED GPIO pin.
 */
	MomentarySwitch(const std::string& id, const std::string& label, unsigned switcher_pin, unsigned button_pin,
			unsigned led_pin = 0);
	virtual ~MomentarySwitch();

private:
	GPIO::PushButton     momentary_;
	unsigned button_pin_; 	// GPIO pin for momentary switch
	bool button_pushed_;
};
}
#endif /* SRC_MOMENTARYSWITCH_H_ */
