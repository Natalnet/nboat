
//Code originally written by "hadogr" from Arduino Forums

//include the mavlink library
#include "mavlink.h"
//Baudrate
int bitRate = 57600;


void setup() {
  
  Serial.begin(bitRate);
}

void loop() {

 command_heartbeat();
 command_location(52.464217,-1.280222, 200);
}

void command_location(int32_t lat, int32_t lon, int32_t alt) {

  //TARGET DRONE
  uint8_t _target_system = 1; // Target drone id
  uint8_t _target_component = 100; // component id set to 100 for FLIR cameras

  uint16_t seq = 0; // Sequence is always set to 0
  uint8_t frame = MAV_FRAME_GLOBAL; // Set target frame to global default
  //uint16_t command = GLOBAL_POSITION_INT; // Specific command for Duo
  uint16_t command = 2; // Specific command for Duo
  uint8_t current = 2; // Guided mode waypoint
  uint8_t autocontinue = 0; // Always 0
  uint32_t upTime = 0; //time since system boot, ignored by camera
  int16_t velx = 1; //x speed
  int16_t vely = 1; //y speed
  int16_t velz = 1; //z speed
  uint16_t heading = 180; //heading

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  mavlink_msg_param_set_pack(1, 1, &msg, 1, 0, "CURRENT_EXTERNAL", 100., MAV_VAR_FLOAT);

  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  // Send the message (.write sends as bytes) 
  delay(1000);
  Serial.write(buf, len);
}

/************************************************************
* @brief Sends a heartbeat message every second.
* @param NONE
* @return void
*************************************************************/

void command_heartbeat() {

  //< ID 1 for this system
  int sysid = 1;                   
  //< The component sending the message.
  int compid = MAV_COMP_ID_MISSIONPLANNER;    
  
  // Define the system type, in this case ground control station
  uint8_t system_type = MAV_TYPE_GCS;
  uint8_t autopilot_type = MAV_AUTOPILOT_INVALID;
  
  uint8_t system_mode = 0; 
  uint32_t custom_mode = 0;                
  uint8_t system_state = 0;
  
  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  
  // Pack the message
  mavlink_msg_heartbeat_pack(sysid, compid, &msg, system_type, autopilot_type, system_mode, custom_mode, system_state);
  
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  // Send the message 
  Serial.write(buf, len);
  delay(5000);
}

/************************************************************
* @brief Sends a waypoint command
* @param NONE
* @return void
*************************************************************/

void command_waypoint() {

  //TARGET DRONE
  uint8_t _target_system = 1; // Target drone id
  uint8_t _target_component = 0; // Target component, 0 = all

  uint16_t seq = 0; // Sequence is always set to 0
  uint8_t frame = MAV_FRAME_GLOBAL; // Set target frame to global default
  uint16_t command = MAV_CMD_NAV_WAYPOINT; // Specific command for PX4 
  uint8_t current = 2; // Guided mode waypoint
  uint8_t autocontinue = 0; // Always 0
  float param1 = 0; // Loiter time
  float param2 = 1; // Acceptable range from target - radius in meters
  float param3 = 0; // Pass through waypoint
  float param4 = 0; // Desired yaw angle
  float x = 52.464217; // Latitude - degrees
  float y = -1.280222; // Longitude - degrees
  float z = 200; // Altitude - meters

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_mission_item_pack(1,1, &msg, _target_system, _target_component, seq, frame, command, current, autocontinue, param1, param2, param3, param4, x, y, z);

  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  // Send the message (.write sends as bytes) 
  delay(1000);
  Serial.write(buf, len);
}
