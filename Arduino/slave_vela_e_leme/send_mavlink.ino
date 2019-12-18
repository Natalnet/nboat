//envia dados para a pixhawk usando o protocolo MAVLINK
void send_mavlink(int param, float data){

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  switch(param){
    case corrente_leme:
    {
      mavlink_msg_param_set_pack(1, 1, &msg, 1, 1, "RUDDER_CURRENT", data, MAV_VAR_FLOAT);
    }
    break;

    case corrente_vela:
    {
      mavlink_msg_param_set_pack(1, 1, &msg, 1, 1, "SAIL_CURRENT", data, MAV_VAR_FLOAT);
    }
    break;

    case posicao_leme:
    {
      mavlink_msg_param_set_pack(1, 1, &msg, 1, 1, "RUDDER_ANGLE", data, MAV_VAR_FLOAT);
    }
    break;

    case posicao_vela:
    {
      mavlink_msg_param_set_pack(1, 1, &msg, 1, 1, "SAIL_ANGLE", data, MAV_VAR_FLOAT);
    }
    break;

    case motor_leme:
    {
      mavlink_msg_param_set_pack(1, 1, &msg, 1, 1, "RUDDER_MOTOR", data, MAV_VAR_FLOAT);
    }
    break;

    case motor_vela:
    {
      mavlink_msg_param_set_pack(1, 1, &msg, 1, 1, "SAIL_MOTOR", data, MAV_VAR_FLOAT);
    }
    break;
  }  
 
  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
 
  // Send the message with the standard UART send function
  ss.write(buf, len);
  
  //delay(50);
}
