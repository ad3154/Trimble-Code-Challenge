/*******************************************************************************
** @file       SuspectParameterNumberParser.h
** @author     Adrian Del Grosso
** @date       Feb 09 2022
*******************************************************************************/
#pragma once

/* Includes ------------------------------------------------------------------*/
#include "CANMessage.h"
#include "SuspectParameterNumber.h"

#include <fstream>
#include <list>
#include <string>

/* Local Forward Declarations ------------------------------------------------*/

/* Exported Constants --------------------------------------------------------*/

/* Exported Types ------------------------------------------------------------*/

/* Exported Classes ----------------------------------------------------------*/
class SuspectParameterNumberParserClass
{
public:
	enum PARAMETER_GROUP_NUMBER_ENUM
	{
		PGN_TORQUE_SPEED_CONTROL_1 = 0x0,
		PGN_TRANSMISSION_CONTROL_1 = 0x100,
		PGN_EXTERNAL_BRAKE_REQUEST = 0x400,
		PGN_GENERAL_PURPOSE_VALVE_PRESSURE = 0x700,
		PGN_AUXILIARY_INPUT_OUTPUT_STATUS_5 = 0x800,
		PGN_PROPRIETARY_METHOD_IDENTIFICATION = 0x9B00,
		PGN_AUXILIARY_INPUT_OUTPUT_STATUS_7 = 0x9C00,
		PGN_AUXILIARY_INPUT_OUTPUT_STATUS_6 = 0x9D00,
		PGN_AUXILIARY_INPUT_OUTPUT_STATUS_4 = 0xA500,
		PGN_AUXILIARY_INPUT_OUTPUT_STATUS_3 = 0xA600,
		PGN_AUXILIARY_INPUT_OUTPUT_STATUS_2 = 0xA700,
		PGN_TEXT_DISPLAY = 0xA800,
		PGN_FORWARD_LANE_IMAGE_COMMAND = 0xA900,
		PGN_TIRE_PRESSURE_REFERENCE_SETTING = 0xAE00,
		PGN_CONTINUOUS_TORQUE_AND_SPEED_LIMIT_REQUEST = 0xCF00,
		PGN_CAB_ILLUMINATION_MESSAGE = 0xD000,
		PGN_AIR_SUSPENSION_CONTROL_6 = 0xD100,
		PGN_AIR_SUSPENSION_CONTROL_2 = 0xD200,
		PGN_TIME_DATE_ADJUST = 0xD500,
		PGN_ANTI_THEFT_STATUS = 0xDC00,
		PGN_ANTI_THEFT_REQUEST = 0xDD00,
		PGN_RESET = 0xDE00,
		PGN_CAB_MESSAGE_1 = 0xE000,
		PGN_ELECTRONIC_RETARDER_CONTROLLER_1 = 0xF000,
		PGN_ELECTRONIC_BRAKE_CONTROLLER_1 = 0xF001,
		PGN_ELECTRONIC_TRANSMISSION_CONTROLLER_1 = 0xF002,
		PGN_ELECTRONIC_ENGINE_CONTROLLER_2 = 0xF003,
		PGN_ELECTRONIC_ENGINE_CONTROLLER_1 = 0xF004,
		PGN_ELECTRONIC_TRANSMISSION_CONTROLLER_2 = 0xF005,
		PGN_ELECTRONIC_AXLE_CONTROLLER_1 = 0xF006,
		PGN_FORWARD_LANE_IMAGE_URGENT_MSG = 0xF007,
		PGN_HYDRAULIC_PRESSURE_GOVERNOR_INFO = 0xF008,
		PGN_VEHICLE_DYNAMIC_STABILITY_CONTROL_2 = 0xF009,
		PGN_ENGINE_GAS_FLOW_RATE = 0xF00A,
		PGN_ELECTRONIC_STEERING_CONTROL = 0xF00B,
		PGN_ELECTRONIC_TRANSMISSION_CONTROLLER_8 = 0xF00C,
		PGN_LAND_LEVELING_SYSTEM_OPERATIONAL_INFORMATION = 0xF00D,
		PGN_AFTERTREATMENT_1_INTAKE_GAS_1 = 0xF00E,
		PGN_AFTERTREATMENT_1_OUTLET_GAS_1 = 0xF00F,
		PGN_AFTERTREATMENT_2_INTAKE_GAS_1 = 0xF010,
		PGN_AFTERTREATMENT_2_OUTLET_GAS_1 = 0xF011,
		PGN_FIFTH_WHEEL_SMART_SYSTEMS_1 = 0xF012,
		PGN_SLOPE_SENSOR_INFORMATION = 0xF013,
		PGN_BLADE_INFORMATION = 0xF014,
		PGN_CYLINDER_COMBUSTION_STATUS = 0xF016,
		PGN_ENGINE_KNOCK_LEVEL_1 = 0xF017,
		PGN_ENGINE_KNOCK_LEVEL_2 = 0xF018,
		PGN_ENGINE_KNOCK_LEVEL_3 = 0xF019,
		PGN_ENGINE_THROTTLE___FUEL_ACTUATOR_CONTROL_COMMAND = 0xF01A,
		PGN_STEERING_ANGLE_SENSOR_INFORMATION = 0xF01D,
		PGN_ENGINE_SPEED_SENSOR_INFORMATION = 0xF021,
		PGN_AFTERTREATMENT_1_SCR_DOSING_SYSTEM_INFORMATION_1 = 0xF023,
		PGN_AFTERTREATMENT_1_SCR_DOSING_SYSTEM_REQUESTS_1 = 0xF024,
		PGN_AFTERTREATMENT_1_SCR_AMMONIA_INFORMATION = 0xF025,
		PGN_AFTERTREATMENT_2_SCR_DOSING_SYSTEM_INFORMATION_1 = 0xF026,
		PGN_AFTERTREATMENT_2_SCR_DOSING_SYSTEM_REQUESTS_1 = 0xF027,
		PGN_AFTERTREATMENT_2_SCR_AMMONIA_INFORMATION = 0xF028,
		PGN_EXTENDED_JOYSTICK_MESSAGE_10 = 0xFD23,
		PGN_BASIC_JOYSTICK_MESSAGE_10 = 0xFD24,
		PGN_EXTENDED_JOYSTICK_MESSAGE_9 = 0xFD25,
		PGN_BASIC_JOYSTICK_MESSAGE_9 = 0xFD26,
		PGN_EXTENDED_JOYSTICK_MESSAGE_8 = 0xFD27,
		PGN_BASIC_JOYSTICK_MESSAGE_8 = 0xFD28,
		PGN_EXTENDED_JOYSTICK_MESSAGE_7 = 0xFD29,
		PGN_BASIC_JOYSTICK_MESSAGE_7 = 0xFD2A,
		PGN_EXTENDED_JOYSTICK_MESSAGE_6 = 0xFD2B,
		PGN_BASIC_JOYSTICK_MESSAGE_6 = 0xFD2C,
		PGN_EXTENDED_JOYSTICK_MESSAGE_5 = 0xFD2D,
		PGN_BASIC_JOYSTICK_MESSAGE_5 = 0xFD2E,
		PGN_EXTENDED_JOYSTICK_MESSAGE_4 = 0xFD2F,
		PGN_BASIC_JOYSTICK_MESSAGE_4 = 0xFD30,
		PGN_JOYSTICK_LAMP_COMMAND_MESSAGE = 0xFD31,
		PGN_AFTERTREATMENT_2_SCR_REAGENT_SUPPLY_INFORMATION = 0xFD33,
		PGN_AFTERTREATMENT_2_SCR_REAGANT_TANK_2_INFORMATION = 0xFD34,
		PGN_AFTERTREATMENT_2_SCR_REAGANT_TANK_1_INFORMATION = 0xFD35,
		PGN_AFTERTREATMENT_2_SCR_REAGENT_INFORMATION = 0xFD36,
		PGN_AFTERTREATMENT_2_SCR_SERVICE_INFORMATION = 0xFD37,
		PGN_AFTERTREATMENT_2_SCR_EXHAUST_GAS_TEMPERATURE = 0xFD38,
		PGN_AFTERTREATMENT_2_SCR_EXHAUST_GAS_PRESSURES = 0xFD39,
		PGN_AFTERTREATMENT_2_SCR_DOSING_SYSTEM_REQUESTS_2 = 0xFD3A,
		PGN_AFTERTREATMENT_2_SCR_DOSING_SYSTEM_INFORMATION_2 = 0xFD3B,
		PGN_AFTERTREATMENT_1_SCR_REAGENT_SUPPLY_INFORMATION = 0xFD3C,
		PGN_AFTERTREATMENT_1_SCR_REAGANT_TANK_2_INFORMATION = 0xFD3D,
		PGN_AFTERTREATMENT_1_SCR_EXHAUST_GAS_TEMPERATURE = 0xFD3E,
		PGN_AFTERTREATMENT_1_SCR_EXHAUST_GAS_PRESSURES = 0xFD3F,
		PGN_AFTERTREATMENT_1_SCR_DOSING_SYSTEM_REQUESTS_2 = 0xFD40,
		PGN_AFTERTREATMENT_1_SCR_DOSING_SYSTEM_INFORMATION_2 = 0xFD41,
		PGN_AFTERTREATMENT_2_FUEL_CONTROL_2 = 0xFD44,
		PGN_AFTERTREATMENT_2_THREE_WAY_CATALYTIC_CONVERTER = 0xFD45,
		PGN_AFTERTREATMENT_1_THREE_WAY_CATALYTIC_CONVERTER = 0xFD46,
		PGN_TRANSMISSION_MODE_LABELS = 0xFD47,
		PGN_ENGINE_EXHAUST_BANK_2_O2_FUEL_TRIM = 0xFD48,
		PGN_ENGINE_EXHAUST_BANK_1_O2_FUEL_TRIM = 0xFD49,
		PGN_AFTERCOOLER_COOLANT_CONTROL_VALVE_COMMAND = 0xFD51,
		PGN_ENGINE_COOLANT_CONTROL_VALVE_COMMAND = 0xFD52,
		PGN_ENGINE_AVERAGE_INFORMATION = 0xFD53,
		PGN_AFTERTREATMENT_1_FUEL_CONTROL_2 = 0xFD65,
		PGN_ENGINE_TEMPERATURE_4 = 0xFD66,
		PGN_ZERO_NET_VEHICLE_WEIGHT_CHANGE = 0xFD67,
		PGN_GROSS_COMBINATION_VEHICLE_WEIGHT = 0xFD68,
		PGN_AXLE_GROUP_CALIBRATION_WEIGHTS = 0xFD69,
		PGN_AXLE_GROUP_WEIGHT = 0xFD6A,
		PGN_AVAILABLE_AXLE_GROUP_WEIGHTS = 0xFD6B,
		PGN_AFTERTREATMENT_2_AIR_CONTROL_2 = 0xFD6C,
		PGN_AFTERTREATMENT_1_AIR_CONTROL_2 = 0xFD6D,
		PGN_AFTERTREATMENT_1_SCR_SERVICE_INFORMATION = 0xFD6E,
		PGN_ELECTRONIC_ENGINE_CONTROLLER_8 = 0xFD6F,
		PGN_DOOR_RAMP_CONTROL = 0xFD70,
		PGN_BRAKE_ACTUATOR_STROKE_STATUS = 0xFD71,
		PGN_ENGINE_SPARK_VOLTAGE_6 = 0xFD72,
		PGN_ENGINE_SPARK_VOLTAGE_5 = 0xFD73,
		PGN_ENGINE_SPARK_VOLTAGE_4 = 0xFD74,
		PGN_ENGINE_SPARK_VOLTAGE_3 = 0xFD75,
		PGN_ENGINE_SPARK_VOLTAGE_2 = 0xFD76,
		PGN_ENGINE_SPARK_VOLTAGE_1 = 0xFD77,
		PGN_AFTERTREATMENT_2_TRIP_INFORMATION = 0xFD78,
		PGN_AFTERTREATMENT_1_TRIP_INFORMATION = 0xFD79,
		PGN_AFTERTREATMENT_2_SERVICE = 0xFD7A,
		PGN_AFTERTREATMENT_1_SERVICE = 0xFD7B,
		PGN_DIESEL_PARTICULATE_FILTER_CONTROL_1 = 0xFD7C,
		PGN_ADAPTIVE_FRONT_LIGHTING_SYSTEM_STATUS = 0xFD7E,
		PGN_ENGINE_CONFIGURATION_2 = 0xFD7F,
		PGN_EGR_COOLER_BYPASS = 0xFD81,
		PGN_TRANSFER_CASE_INFORMATION = 0xFD83,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_9 = 0xFD84,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_8 = 0xFD85,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_7 = 0xFD86,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_6 = 0xFD87,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_5 = 0xFD88,
		PGN_VEHICLE_DIRECTION_SPEED_2 = 0xFD89,
		PGN_SAE_J2012_DTC_DISPLAY = 0xFD8A,
		PGN_AFTERTREATMENT_2_GAS_PARAMETERS = 0xFD8B,
		PGN_AFTERTREATMENT_1_GAS_PARAMETERS = 0xFD8C,
		PGN_ADVERTISED_ENGINE_TORQUE_CURVE = 0xFD90,
		PGN_ENGINE_OPERATING_INFORMATION = 0xFD92,
		PGN_ELECTRONIC_ENGINE_CONTROLLER_7 = 0xFD94,
		PGN_TRANSMISSION_FLUIDS_2 = 0xFD95,
		PGN_AFTERTREATMENT_1_HISTORICAL_INFORMATION = 0xFD98,
		PGN_AFTERTREATMENT_2_HISTORICAL_INFORMATION = 0xFD99,
		PGN_AFTERTREATMENT_1_SCR_REAGENT_INFORMATION = 0xFD9B,
		PGN_SENSOR_ELECTRICAL_POWER_2 = 0xFD9C,
		PGN_SENSOR_ELECTRICAL_POWER_1 = 0xFD9D,
		PGN_AFTERTREATMENT_2_AIR_CONTROL_1 = 0xFD9E,
		PGN_AFTERTREATMENT_1_AIR_CONTROL_1 = 0xFD9F,
		PGN_AFTERTREATMENT_2_FUEL_CONTROL_1 = 0xFDA0,
		PGN_AFTERTREATMENT_1_FUEL_CONTROL_1 = 0xFDA1,
		PGN_FUEL_INFORMATION_3_GASEOUS = 0xFDA2,
		PGN_ELECTRONIC_ENGINE_CONTROLLER_6 = 0xFDA3,
		PGN_PTO_DRIVE_ENGAGEMENT = 0xFDA4,
		PGN_DOOR_CONTROL_2 = 0xFDA5,
		PGN_WIRELESS_COMMUNICATIONS_MESSAGE_2 = 0xFDA8,
		PGN_WIRELESS_COMMUNICATIONS_MESSAGE_1 = 0xFDA9,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_4 = 0xFDAA,
		PGN_FIFTH_WHEEL_SMART_SYSTEMS_2 = 0xFDAE,
		PGN_AFTERTREATMENT_2_INTERMEDIATE_GAS = 0xFDAF,
		PGN_AFTERTREATMENT_2_OUTLET_GAS_2 = 0xFDB0,
		PGN_AFTERTREATMENT_2_INTAKE_GAS_2 = 0xFDB1,
		PGN_AFTERTREATMENT_1_INTERMEDIATE_GAS = 0xFDB2,
		PGN_AFTERTREATMENT_1_OUTLET_GAS_2 = 0xFDB3,
		PGN_AFTERTREATMENT_1_INTAKE_GAS_2 = 0xFDB4,
		PGN_TIRE_PRESSURE_REFERENCE_INFORMATION = 0xFDB9,
		PGN_FAREBOX_STATUS = 0xFDBA,
		PGN_FAREBOX_POINT_OF_SALE = 0xFDBB,
		PGN_FAREBOX_SERVICE_DETAIL = 0xFDBC,
		PGN_SIGNAL_PREEMPTION = 0xFDBD,
		PGN_TRANSIT_ROUTE = 0xFDBE,
		PGN_TRANSIT_MILEPOST = 0xFDBF,
		PGN_PASSENGER_COUNTER = 0xFDC0,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_3 = 0xFDC1,
		PGN_ELECTRONIC_BRAKE_CONTROLLER_5 = 0xFDC4,
		PGN_ECU_IDENTIFICATION_INFORMATION = 0xFDC5,
		PGN_COLD_START_AIDS = 0xFDC6,
		PGN_OFF_HIGHWAY_ENGINE_CONTROL_SELECTION_STATES = 0xFDC7,
		PGN_OPERATOR_PRIMARY_INTERMEDIATE_SPEED_CONTROL_STATE = 0xFDC8,
		PGN_ELECTRONIC_CONTROL_MODULE_INFORMATION = 0xFDC9,
		PGN_INTERMEDIATE_SPEED_CONTROL = 0xFDCA,
		PGN_OFF_HIGHWAY_ENGINE_CONTROL_SELECTION = 0xFDCB,
		PGN_OPERATORS_EXTERNAL_LIGHT_CONTROLS_MESSAGE = 0xFDCC,
		PGN_OPERATOR_WIPER_AND_WASHER_CONTROLS_MESSAGE = 0xFDCD,
		PGN_INLET_EXHAUST_CONDITIONS_2 = 0xFDD0,
		PGN_FMS_STANDARD_INTERFACE_IDENTITY_CAPABILITIES = 0xFDD1,
		PGN_ECU_PERFORMANCE = 0xFDD2,
		PGN_TURBOCHARGER_INFORMATION_6 = 0xFDD3,
		PGN_CAB_MESSAGE_3 = 0xFDD4,
		PGN_ELECTRONIC_ENGINE_CONTROLLER_5 = 0xFDD5,
		PGN_BASIC_JOYSTICK_MESSAGE_1 = 0xFDD6,
		PGN_EXTENDED_JOYSTICK_MESSAGE_1 = 0xFDD7,
		PGN_BASIC_JOYSTICK_MESSAGE_2 = 0xFDD8,
		PGN_EXTENDED_JOYSTICK_MESSAGE_2 = 0xFDD9,
		PGN_BASIC_JOYSTICK_MESSAGE_3 = 0xFDDA,
		PGN_EXTENDED_JOYSTICK_MESSAGE_3 = 0xFDDB,
		PGN_MARINE_CONTROL_INFORMATION = 0xFDDC,
		PGN_FRONT_WHEEL_DRIVE_STATUS = 0xFDDF,
		PGN_AMBIENT_CONDITIONS_2 = 0xFDE0,
		PGN_CAB_A_C_CLIMATE_SYSTEM_INFORMATION = 0xFDE1,
		PGN_SUPPLY_PRESSURE_DEMAND = 0xFDE2,
		PGN_EQUIPMENT_OPERATION_AND_CONTROL = 0xFDE3,
		PGN_EQUIPMENT_PERFORMANCE_DATA = 0xFDE4,
		PGN_MAXIMUM_VEHICLE_SPEED_LIMIT_STATUS = 0xFDE5,
		PGN_HYDRAULIC_BRAKING_SYSTEM = 0xFDE6,
		PGN_EXHAUST_TEMPERATURE = 0xFE07,
		PGN_LIGHTING_DATA = 0xFE40,
		PGN_LIGHTING_COMMAND = 0xFE41,
		PGN_ELECTRONIC_TRANSMISSION_CONTROLLER_7 = 0xFE4A,
		PGN_TRANSMISSION_CONFIGURATION_2 = 0xFE4B,
		PGN_MILITARY_LIGHTING_COMMAND = 0xFE4C,
		PGN_TOTAL_AVERAGED_INFORMATION = 0xFE4D,
		PGN_DOOR_CONTROL_1 = 0xFE4E,
		PGN_VEHICLE_DYNAMIC_STABILITY_CONTROL_1 = 0xFE4F,
		PGN_BATTERY_TEMPERATURE = 0xFE50,
		PGN_ADAPTIVE_CRUISE_CONTROL_OPERATOR_INPUT = 0xFE51,
		PGN_VEHICLE_ELECTRICAL_POWER_3 = 0xFE52,
		PGN_RETARDER_CONTINUOUS_TORQUE_AND_SPEED_LIMIT = 0xFE53,
		PGN_ENGINE_CONTINUOUS_TORQUE_AND_SPEED_LIMIT = 0xFE54,
		PGN_GASEOUS_FUEL_PROPERTIES = 0xFE55,
		PGN_AFTERTREATMENT_1_SCR_REAGENT_TANK_1_INFORMATION = 0xFE56,
		PGN_AIR_SUSPENSION_CONTROL_5 = 0xFE57,
		PGN_AIR_SUSPENSION_CONTROL_4 = 0xFE58,
		PGN_AIR_SUSPENSION_CONTROL_3 = 0xFE59,
		PGN_AIR_SUSPENSION_CONTROL_1 = 0xFE5A,
		PGN_FORWARD_LANE_IMAGE = 0xFE5B,
		PGN_BATTERY_MAIN_SWITCH_INFORMATION = 0xFE66,
		PGN_CLIMATE_CONTROL_CONFIGURATION = 0xFE67,
		PGN_VEHICLE_FLUIDS = 0xFE68,
		PGN_ENGINE_TEMPERATURE_3 = 0xFE69,
		PGN_ENGINE_FUEL_LUBE_SYSTEMS = 0xFE6A,
		PGN_DRIVERS_IDENTIFICATION = 0xFE6B,
		PGN_TACHOGRAPH = 0xFE6C,
		PGN_HEATER_INFORMATION = 0xFE6D,
		PGN_HIGH_RESOLUTION_WHEEL_SPEED = 0xFE6E,
		PGN_ADAPTIVE_CRUISE_CONTROL = 0xFE6F,
		PGN_COMBINATION_VEHICLE_WEIGHT = 0xFE70,
		PGN_LASER_TRACER_POSITION = 0xFE71,
		PGN_LASER_LEVELING_SYSTEM_BLADE_CONTROL = 0xFE72,
		PGN_LASER_RECEIVER_MAST_POSITION = 0xFE73,
		PGN_MODIFY_LEVELING_SYSTEM_CONTROL_SET_POINT = 0xFE74,
		PGN_LASER_LEVELING_SYSTEM_VERTICAL_DEVIATION = 0xFE75,
		PGN_LASER_LEVELING_SYSTEM_VERTICAL_POSITION_DISPLAY_DATA = 0xFE76,
		PGN_AUXILIARY_PRESSURES = 0xFE77,
		PGN_TIRE_PRESSURE_CONTROL_UNIT_MODE_AND_STATUS = 0xFE78,
		PGN_TIRE_PRESSURE_CONTROL_UNIT_TARGET_PRESSURES = 0xFE79,
		PGN_TIRE_PRESSURE_CONTROL_UNIT_CURRENT_PRESSURES = 0xFE7A,
		PGN_COMBUSTION_TIME_1 = 0xFE7B,
		PGN_COMBUSTION_TIME_2 = 0xFE7C,
		PGN_COMBUSTION_TIME_3 = 0xFE7D,
		PGN_COMBUSTION_TIME_4 = 0xFE7E,
		PGN_COMBUSTION_TIME_5 = 0xFE7F,
		PGN_COMBUSTION_TIME_6 = 0xFE80,
		PGN_FUEL_INFORMATION_2_GASEOUS = 0xFE81,
		PGN_IGNITION_TIMING_1 = 0xFE82,
		PGN_IGNITION_TIMING_2 = 0xFE83,
		PGN_IGNITION_TIMING_3 = 0xFE84,
		PGN_IGNITION_TIMING_4 = 0xFE85,
		PGN_IGNITION_TIMING_5 = 0xFE86,
		PGN_IGNITION_TIMING_6 = 0xFE87,
		PGN_IGNITION_TRANSFORMER_SECONDARY_OUTPUT_1 = 0xFE88,
		PGN_IGNITION_TRANSFORMER_SECONDARY_OUTPUT_2 = 0xFE89,
		PGN_IGNITION_TRANSFORMER_SECONDARY_OUTPUT_3 = 0xFE8A,
		PGN_GASEOUS_FUEL_PRESSURE = 0xFE8B,
		PGN_AUXILIARY_ANALOG_INFORMATION = 0xFE8C,
		PGN_VEHICLE_ELECTRICAL_POWER_2 = 0xFE8D,
		PGN_SERVICE_2 = 0xFE8E,
		PGN_SUPPLY_PRESSURE_2 = 0xFE8F,
		PGN_ENGINE_TORQUE_HISTORY = 0xFE90,
		PGN_FUEL_LEAKAGE = 0xFE91,
		PGN_ENGINE_INFORMATION = 0xFE92,
		PGN_ENGINE_ELECTRICAL_SYSTEM_MODULE_INFORMATION = 0xFE93,
		PGN_ENGINE_AUXILIARY_COOLANT = 0xFE94,
		PGN_REBUILD_INFORMATION = 0xFE95,
		PGN_TURBOCHARGER_WASTEGATE = 0xFE96,
		PGN_TURBOCHARGER_INFORMATION_5 = 0xFE97,
		PGN_TURBOCHARGER_INFORMATION_4 = 0xFE98,
		PGN_TURBOCHARGER_INFORMATION_3 = 0xFE99,
		PGN_TURBOCHARGER_INFORMATION_2 = 0xFE9A,
		PGN_TURBOCHARGER_INFORMATION_1 = 0xFE9B,
		PGN_MAIN_BEARING_TEMPERATURE_3 = 0xFE9C,
		PGN_MAIN_BEARING_TEMPERATURE_2 = 0xFE9D,
		PGN_MAIN_BEARING_TEMPERATURE_1 = 0xFE9E,
		PGN_EXHAUST_PORT_TEMPERATURE_5 = 0xFE9F,
		PGN_EXHAUST_PORT_TEMPERATURE_4 = 0xFEA0,
		PGN_EXHAUST_PORT_TEMPERATURE_3 = 0xFEA1,
		PGN_EXHAUST_PORT_TEMPERATURE_2 = 0xFEA2,
		PGN_EXHAUST_PORT_TEMPERATURE_1 = 0xFEA3,
		PGN_ENGINE_TEMPERATURE_2 = 0xFEA4,
		PGN_INTAKE_MANIFOLD_INFORMATION_2 = 0xFEA5,
		PGN_INTAKE_MANIFOLD_INFORMATION_1 = 0xFEA6,
		PGN_ALTERNATOR_TEMPERATURE = 0xFEA7,
		PGN_ARTICULATION_CONTROL = 0xFEA8,
		PGN_EXHAUST_OXYGEN_1 = 0xFEA9,
		PGN_ALTERNATE_FUEL_2 = 0xFEAA,
		PGN_ELECTRONIC_TRANSMISSION_CONTROLLER_6 = 0xFEAB,
		PGN_WHEEL_BRAKE_LINING_REMAINING_INFORMATION = 0xFEAC,
		PGN_WHEEL_APPLICATION_PRESSURE_HIGH_RANGE_INFORMATION = 0xFEAD,
		PGN_AIR_SUPPLY_PRESSURE = 0xFEAE,
		PGN_FUEL_CONSUMPTION_GASEOUS = 0xFEAF,
		PGN_TRIP_TIME_INFORMATION_2 = 0xFEB0,
		PGN_ECU_HISTORY = 0xFEB1,
		PGN_FUEL_INFORMATION_1_GASEOUS = 0xFEB2,
		PGN_FUEL_INFORMATION_LIQUID = 0xFEB3,
		PGN_TRIP_TIME_INFORMATION_1 = 0xFEB4,
		PGN_TRIP_SHUTDOWN_INFORMATION = 0xFEB5,
		PGN_TRIP_VEHICLE_SPEED_CRUISE_DISTANCE_INFORMATION = 0xFEB6,
		PGN_ENGINE_SPEED_LOAD_FACTOR_INFORMATION = 0xFEB7,
		PGN_TRIP_FUEL_INFORMATION_GASEOUS = 0xFEB8,
		PGN_TRIP_FUEL_INFORMATION_LIQUID = 0xFEB9,
		PGN_TRIP_DISTANCE_INFORMATION = 0xFEBA,
		PGN_TRIP_FAN_INFORMATION = 0xFEBB,
		PGN_COMPRESSION_SERVICE_BRAKE_INFORMATION = 0xFEBC,
		PGN_FAN_DRIVE = 0xFEBD,
		PGN_ELECTRONIC_ENGINE_CONTROLLER_4 = 0xFEBE,
		PGN_WHEEL_SPEED_INFORMATION = 0xFEBF,
		PGN_SERVICE_INFORMATION = 0xFEC0,
		PGN_HIGH_RESOLUTION_VEHICLE_DISTANCE = 0xFEC1,
		PGN_ELECTRONIC_RETARDER_CONTROLLER_2 = 0xFEC2,
		PGN_ELECTRONIC_TRANSMISSION_CONTROLLER_5 = 0xFEC3,
		PGN_ELECTRONIC_TRANSMISSION_CONTROLLER_4 = 0xFEC5,
		PGN_ELECTRONIC_TRANSMISSION_CONTROLLER_3 = 0xFEC7,
		PGN_ALTERNATOR_INFORMATION = 0xFED5,
		PGN_AUXILIARY_INPUT_OUTPUT_STATUS_1 = 0xFED9,
		PGN_SOFTWARE_IDENTIFICATION = 0xFEDA,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_2 = 0xFEDB,
		PGN_IDLE_OPERATION = 0xFEDC,
		PGN_TURBOCHARGER = 0xFEDD,
		PGN_AIR_START_PRESSURE = 0xFEDE,
		PGN_ELECTRONIC_ENGINE_CONTROLLER_3 = 0xFEDF,
		PGN_VEHICLE_DISTANCE = 0xFEE0,
		PGN_RETARDER_CONFIGURATION = 0xFEE1,
		PGN_TRANSMISSION_CONFIGURATION = 0xFEE2,
		PGN_ENGINE_CONFIGURATION_1 = 0xFEE3,
		PGN_SHUTDOWN = 0xFEE4,
		PGN_ENGINE_HOURS_REVOLUTIONS = 0xFEE5,
		PGN_TIME_DATE = 0xFEE6,
		PGN_VEHICLE_HOURS = 0xFEE7,
		PGN_VEHICLE_DIRECTION_SPEED = 0xFEE8,
		PGN_FUEL_CONSUMPTION_LIQUID = 0xFEE9,
		PGN_VEHICLE_WEIGHT = 0xFEEA,
		PGN_COMPONENT_IDENTIFICATION = 0xFEEB,
		PGN_VEHICLE_IDENTIFICATION = 0xFEEC,
		PGN_CRUISE_CONTROL_VEHICLE_SPEED_SETUP = 0xFEED,
		PGN_ENGINE_TEMPERATURE_1 = 0xFEEE,
		PGN_ENGINE_FLUID_LEVEL_PRESSURE_1 = 0xFEEF,
		PGN_POWER_TAKEOFF_INFORMATION = 0xFEF0,
		PGN_CRUISE_CONTROL_VEHICLE_SPEED = 0xFEF1,
		PGN_FUEL_ECONOMY_LIQUID = 0xFEF2,
		PGN_VEHICLE_POSITION = 0xFEF3,
		PGN_TIRE_CONDITION = 0xFEF4,
		PGN_AMBIENT_CONDITIONS = 0xFEF5,
		PGN_INLET_EXHAUST_CONDITIONS_1 = 0xFEF6,
		PGN_VEHICLE_ELECTRICAL_POWER_1 = 0xFEF7,
		PGN_TRANSMISSION_FLUIDS_1 = 0xFEF8,
		PGN_AXLE_INFORMATION = 0xFEF9,
		PGN_BRAKES = 0xFEFA,
		PGN_RETARDER_FLUIDS = 0xFEFB,
		PGN_DASH_DISPLAY = 0xFEFC,
		PGN_ALTERNATE_FUEL_1 = 0xFEFD,
		PGN_AUXILIARY_WATER_PUMP_PRESSURE = 0xFEFE,
		PGN_WATER_IN_FUEL_INDICATOR = 0xFEFF
	};

	explicit SuspectParameterNumberParserClass(std::string aOutputFilePath);
	~SuspectParameterNumberParserClass();

	void AddSuspectParameterNumberFilter(
	  SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN);

	bool ParseFilteredMessageToLog(CANMessageClass &apCANMessage);

	static bool GetIsSuspectParameterNumberChildOfParameterGroupNumber(PARAMETER_GROUP_NUMBER_ENUM aPGN, SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN);

private:
	uint32_t extractRawSuspectParameterNumberData(CANMessageClass &apCANMessage, SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM aSPN);
	std::list<SuspectParameterNumberClass::SUSPECT_PARAMETER_NUMBER_ENUM> mFilterList;
	std::ofstream mFile;
};

/* Exported Functions --------------------------------------------------------*/

/* Exported Data -------------------------------------------------------------*/
