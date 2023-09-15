/*
 * Switcher.h
 *
 *  Created on: Jun 27, 2020
 *      Author: dmounday
 */

#ifndef SRC_RELAYSWITCHER_H_
#define SRC_RELAYSWITCHER_H_
#include <chrono>
#include <memory>

#include <boost/property_tree/ptree.hpp>
#include <cppgpio.hpp>

#include "EquipmentBase.h"

namespace pentair_control {
namespace pt = boost::property_tree;

inline const std::string ON {"ON"};
inline const std::string OFF {"OFF"};
inline const std::string Error{"Error"};

class RelaySwitcher;
using RelayPtr = std::shared_ptr<RelaySwitcher>;
/**
 * @brief RelaySwitcher class derived from EquipmentBase
 * 
 */
class RelaySwitcher: public EquipmentBase {

public:
	enum class RelayState {
		ON,
		OFF,
		ERROR
	};
	enum class SwitchRequest {
		ON,
		OFF
	};
	enum class ForceState {
		FORCE_REQUIRED,
		ABORT_REQUEST
	};
	/// Identifies a set of RelaySwither states that must exist before a change of
	/// relay state is allowed. For example a request to set IC40 on requires that mainPump is currently on.
	/// Required state of RelaySwitchers before a switch change is made. If foreceState is set
	/// to FORCE_REQUIRED the associated RelaySwitcher is changed.
	///
  /// SwitchRequest on/off from OnConditions/OffCondictions property.
  ///requiredState  The required state and ForceState of the relay.
  ///  property: on/off: SwitchRequest ON/OFF and ForceRquired
  ///  Property: require_on: SwitchRequest ON and ABORT_REQUEST
	struct RequiredState {
		std::shared_ptr<RelaySwitcher> 			relaySwitch;	// depends on condition of this RelaySwitcher.
		SwitchRequest				onOff;			// requested action
		RelayState        	requiredState;	// must be in this state to switch.
		ForceState					forceState;		// force relay to required state.
	};

	//Relay switch and GPIO control pin. led_pin specifies the control pin
	//for the LED pilot light.
	//

/**
 * @brief Construct a new Relay Switcher object for named equipment with GPIO pin
 * number and logging label.
 * 
 * @param name Name of equipment i.e. "MainPump"
 * @param label loggin label
 * @param pin   GPIO pin number.
 * @param led_pin GPIO of status LED if present.
 */
	RelaySwitcher(const std::string& name, const std::string& label, unsigned pin,
				 unsigned led_pin = 0);
	virtual ~RelaySwitcher();
  /**
   * @brief switch on equipment.
   * 
   */
	void SwitchOn()override final;
  /**
   * @brief switch off equipment
   * 
   */
	void SwitchOff()override final;
  /**
   * @brief Stop equipment and any associted timers.
   * 
   */
	void Stop() override;
  /**
   * @brief Configure any required on/off states.
   * 
   */
	void RequiredStates(const Equipment&, const pt::ptree& );
  /**
   * @brief state of relay.
   * 
   * @return RelayState 
   */
	inline RelayState State() const {return state_;}
  /**
   * @brief relay state as a string.
   * 
   * @return const std::string& 
   */
	const std::string& StateStr() const;
  /**
   * @brief Time point to turn equipment on.
   * 
   * @return std::chrono::system_clock::time_point 
   */
	inline std::chrono::system_clock::time_point OnTime()const {return on_time_;}
  /**
   * @brief time point to turn equipment off.
   * 
   * @return std::chrono::system_clock::time_point 
   */
	inline std::chrono::system_clock::time_point OffTime()const {return off_time_;}
  /**
   * @brief Get the Status List object
   * 
   * @return StatusList Return status as a vector of string pairs.
   */
	virtual StatusList GetStatusList();
  /**
   * @brief logging label
   * 
   * @return const std::string& 
   */
	inline const std::string& Label()const {return label_;};
  inline void setAuxStatus(std::pair<std::string, std::string> aux){ auxStatus_ = aux;  };
private:
	bool CheckConditions(SwitchRequest );
	unsigned pin_;			// GPIO pin for equipment control
	unsigned pilot_pin_;		// GPIO pin for optional pilot LED
	enum RelayState state_;
	GPIO::DigitalOut switch_; //
	GPIO::DigitalOut pilot_;	// optional pilot light
	std::vector<RequiredState> required_states_;

	std::chrono::system_clock::time_point on_time_;
	std::chrono::system_clock::time_point off_time_;
	std::string label_;
  std::pair<std::string, std::string> auxStatus_{std::make_pair(std::string(), std::string())}; // set by scheduling if needed.
};

} // namespace
#endif /* SRC_RELAYSWITCHER_H_ */
