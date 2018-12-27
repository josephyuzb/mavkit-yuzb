#include <mavkit/MavlinkDisplay.h>

#include <iostream>

//----------------------------------------------------------------------------//
MavlinkDisplay::MavlinkDisplay()
{}
//----------------------------------------------------------------------------//
MavlinkDisplay::~MavlinkDisplay()
{}
//----------------------------------------------------------------------------//
void MavlinkDisplay::append_listener(MavMessengerInterface* listener)
{}
//----------------------------------------------------------------------------//
void MavlinkDisplay::start()
{}
//----------------------------------------------------------------------------//
void MavlinkDisplay::join()
{}
//----------------------------------------------------------------------------//
bool MavlinkDisplay::send_message(mavlink_message_t &msg)
{
    mutex.lock();
    switch(msg.msgid)
    {
        case MAVLINK_MSG_ID_HEARTBEAT:
        {
           mavlink_heartbeat_t heartbeat;
           mavlink_msg_heartbeat_decode(&msg, &heartbeat);
           std::cout << "heartbeat" << std::endl;
        
           //access message specific fields
           std::cout << "    type:            "            << (uint)heartbeat.type << std::endl;
           std::cout << "    autopilot:       "       << (uint)heartbeat.autopilot << std::endl;
           std::cout << "    base_mode:       "       << (uint)heartbeat.base_mode << std::endl;
           std::cout << "    custom_mode:     "     << (uint)heartbeat.custom_mode << std::endl;
           std::cout << "    system_status:   "   << (uint)heartbeat.system_status << std::endl;
           std::cout << "    mavlink_version: " << (uint)heartbeat.mavlink_version << std::endl;
             break;
         }
        // case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
        // {
        //     mavlink_param_request_list_t param_request_list;
        //     mavlink_msg_param_request_list_decode(&msg, &param_request_list);
        //     std::cout << "param request list" << std::endl;
        //     break;
        // }
        case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
        {
        	mavlink_local_position_ned_t local_position_ned;
        	mavlink_msg_local_position_ned_decode(&msg, &local_position_ned);
        	std::cout << "position:" << std::endl;
        	std::cout << "	time_boot_ms:	" <<(uint)local_position_ned.time_boot_ms << std::endl;
        	std::cout << "	x:	" <<(uint)local_position_ned.x << std::endl;
        	std::cout << "	y:	" <<(uint)local_position_ned.y << std::endl;
        	std::cout << "	z:	" <<(uint)local_position_ned.z << std::endl;
        	std::cout << "	vx:	" <<(uint)local_position_ned.vx << std::endl;
        	std::cout << "	vy:	" <<(uint)local_position_ned.vy << std::endl;
        	std::cout << "	vz:	" <<(uint)local_position_ned.vz << std::endl;
        	break;
        }
        case MAVLINK_MSG_ID_ATTITUDE:
        {
        	mavlink_attitude_t atti_pack;
        	mavlink_msg_attitude_decode(&msg, &atti_pack);
        	std::cout << "attitude:" << std::endl;
        	std::cout << "	time_boot_ms:	" << atti_pack.time_boot_ms << std::endl;
        	std::cout << "	roll:	" << atti_pack.roll << std::endl;
        	std::cout << "	pitch:	" << atti_pack.pitch << std::endl;
        	std::cout << "	yaw:	" << atti_pack.yaw << std::endl;
        	std::cout << "	rollspeed:	" << atti_pack.rollspeed << std::endl;
        	std::cout << "	pitchspeed:	" << atti_pack.pitchspeed << std::endl;
        	std::cout << "	yawspeed:	" << atti_pack.yawspeed << std::endl;
        	break;
        }
        // case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:
        // {
        //     mavlink_request_data_stream_t request_data_stream;
        //     mavlink_msg_request_data_stream_decode(&msg, &request_data_stream);
        //     std::cout << "request data stream" << std::endl;
        //     break;
        // }
        // case MAVLINK_MSG_ID_NAMED_VALUE_FLOAT:
        // {
        //     mavlink_named_value_float_t named_value_float;
        //     mavlink_msg_named_value_float_decode(&msg, &named_value_float);
        //     std::cout << "named value float" << std::endl;
        //     break;
        // }
        // case MAVLINK_MSG_ID_STATUSTEXT:
        // {
        //     mavlink_statustext_t statustext;
        //     mavlink_msg_statustext_decode(&msg, &statustext);
        //     std::cout << "status text" << std::endl;
        //     std::cout << statustext.text << std::endl;
        //     break;
        // }
        default:
        {
            // std::cout << "Unsupported packet -> ";
            std::cout << "SYS: "     << (int)msg.sysid;
            std::cout << ", COMP: "   << (int)msg.compid;
            std::cout << ", SEQ: "    << (int)msg.seq;
            std::cout << ", LEN: "    << (int)msg.len;
            std::cout << ", MSG ID: " << (int)msg.msgid << std::endl;
            break;
        }
    }
    std::cout << "----------------------" << std::endl;
    mutex.unlock();

    return true;
}
//----------------------------------------------------------------------------//
