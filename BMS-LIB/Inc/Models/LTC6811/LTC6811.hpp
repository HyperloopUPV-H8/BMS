/*
 * LTC6811.hpp
 *
 *  Created on: Dec 19, 2022
 *      Author: aleja
 */

#pragma once

#include <bitset>

#include "ST-LIB.hpp"
#include "Battery/Battery.hpp"
#include "PEC15/PEC15.hpp"

using std::views::iota;
using std::bitset;

class LTC6811 {
public:
	enum DISCHARGE_TIME : uint8_t {
		DISABLED = 0,
		HALF_MINUTE = 1,
		ONE_MINUTE = 2,
		TWO_MINUTES = 3,
		THREE_MINUTES = 4,
		FOUR_MINUTES = 5,
		FIVE_MINUTES = 6,
		TEN_MINUTES = 7,
		FIFTEEN_MINUTES = 8,
		TWENTY_MINUTES = 9,
		THIRTY_MINUTES = 10,
		FORTY_MINUTES = 11,
		ONE_HOUR = 12,
		SEVENTY_FIVE_MINUTES = 13,
		NINETY_MINUTES = 14,
		TWO_HOURS = 15

	};

	static const uint8_t REGISTER_GROUPS = 4;
	static const uint8_t DATA_REGISTER_LENGTH = 6;
	static const uint8_t COMMAND_LENGTH = 2;
	static const uint8_t COMMAND_DATA_LENGTH = DATA_REGISTER_LENGTH + PEC15::LENGTH;

	class configuration {
	private:
		array<bitset<8>, 6> register_group;
	public:
		configuration();

		void set_gpio(uint8_t gpio, bool state);
		void set_references(bool state);
		void set_adc_optimal_mode(bool state);
		void set_discharge_timer(bool state);
		void set_cell_discharging(uint8_t cell, bool state);
		void set_discharge_timeout_value(DISCHARGE_TIME discharge_timer);
		void set_adc_undervoltage(float adc_voltage);
		void set_adc_overvoltage(float adc_voltage);

		bool is_gpio_on(uint8_t gpio_pin);
		bool is_references_on();
		bool is_adc_optimal_mode();
		bool is_discharge_timer_enabled();
		bool is_cell_discharging(uint8_t cell);
		uint8_t get_discharge_timeout_value();
		float get_adc_undervoltage();
		float get_adc_overvoltage();
	};

	LTC6811();

	configuration peripheral_configuration;
	voltage_register_group cell_voltages[REGISTER_GROUPS];
	voltage_register_group temperatures[2];
	Battery battery1;
	Battery battery2;
};
