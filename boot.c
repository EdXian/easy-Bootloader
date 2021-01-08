#include "boot.h"
uint32_t sum32(uint8_t*data, uint16_t len){
	uint32_t sum = 0x0000;
	uint16_t i;
	for(i=0;i<len;i++){
		sum+= data[i];
	}
	return sum;
}
uint32_t check_function(uint8_t* pack,uint16_t len){
	return sum32(pack, len);
}

void header_config(header_t* pack,
uint8_t header,
uint8_t len,
uint8_t packet_type){
	
	pack->header = header;
	pack->len = len;
	pack->packet_type = packet_type;

}
void err_config(err_t* pack,
header_t header,
uint32_t checksum){
	
	pack->header = header;
	pack->checksum = checksum;

}
void err_ack_config(err_ack_t* pack,
header_t header,
uint32_t checksum){
	
	pack->header = header;
	pack->checksum = checksum;

}
void bl_get_ver_config(bl_get_ver_t* pack,
header_t header,
uint32_t checksum){
	
	pack->header = header;
	pack->checksum = checksum;

}
void bl_get_ver_ack_config(bl_get_ver_ack_t* pack,
header_t header,
uint8_t major,
uint8_t minor,
uint8_t patch,
uint32_t checksum){
	
	pack->header = header;
	pack->major = major;
	pack->minor = minor;
	pack->patch = patch;
	pack->checksum = checksum;

}
void bl_get_id_config(bl_get_id_t* pack,
header_t header,
uint32_t checksum){
	
	pack->header = header;
	pack->checksum = checksum;

}
void bl_get_id_ack_config(bl_get_id_ack_t* pack,
header_t header,
uint32_t chip_id,
uint32_t checksum){
	
	pack->header = header;
	pack->chip_id = chip_id;
	pack->checksum = checksum;

}
void bl_jump_app_config(bl_jump_app_t* pack,
header_t header,
uint32_t addr,
uint32_t checksum){
	
	pack->header = header;
	pack->addr = addr;
	pack->checksum = checksum;

}
void bl_jump_app_ack_config(bl_jump_app_ack_t* pack,
header_t header,
uint8_t valid,
uint32_t checksum){
	
	pack->header = header;
	pack->valid = valid;
	pack->checksum = checksum;

}
void bl_mem_erase_config(bl_mem_erase_t* pack,
header_t header,
uint32_t start_addr,
uint32_t end_addr,
uint32_t checksum){
	
	pack->header = header;
	pack->start_addr = start_addr;
	pack->end_addr = end_addr;
	pack->checksum = checksum;

}
void bl_mem_erase_ack_config(bl_mem_erase_ack_t* pack,
header_t header,
uint8_t valid,
uint32_t checksum){
	
	pack->header = header;
	pack->valid = valid;
	pack->checksum = checksum;

}
void bl_mem_write_config(bl_mem_write_t* pack,
header_t header,
uint32_t start_addr,
uint8_t length,
uint8_t data[128],
uint32_t checksum){
	
	pack->header = header;
	pack->start_addr = start_addr;
	pack->length = length;
	pack->data[128] = data[128];
	pack->checksum = checksum;

}
void bl_mem_write_ack_config(bl_mem_write_ack_t* pack,
header_t header,
uint8_t valid,
uint32_t checksum){
	
	pack->header = header;
	pack->valid = valid;
	pack->checksum = checksum;

}
void bl_mem_read_config(bl_mem_read_t* pack,
header_t header,
uint32_t start_addr,
uint32_t end_addr,
uint32_t checksum){
	
	pack->header = header;
	pack->start_addr = start_addr;
	pack->end_addr = end_addr;
	pack->checksum = checksum;

}
void bl_mem_read_ack_config(bl_mem_read_ack_t* pack,
header_t header,
uint8_t valid,
uint8_t read_length,
uint8_t data[128],
uint32_t checksum){
	
	pack->header = header;
	pack->valid = valid;
	pack->read_length = read_length;
	pack->data[128] = data[128];
	pack->checksum = checksum;

}
void bl_reset_config(bl_reset_t* pack,
header_t header,
uint32_t checksum){
	
	pack->header = header;
	pack->checksum = checksum;

}
void bl_reset_ack_config(bl_reset_ack_t* pack,
header_t header,
uint8_t valid,
uint32_t checksum){
	
	pack->header = header;
	pack->valid = valid;
	pack->checksum = checksum;

}
void bl_verify_config(bl_verify_t* pack,
header_t header,
uint32_t start_addr,
uint32_t end_addr,
uint32_t verify_code,
uint32_t checksum){
	
	pack->header = header;
	pack->start_addr = start_addr;
	pack->end_addr = end_addr;
	pack->verify_code = verify_code;
	pack->checksum = checksum;

}
void bl_verify_ack_config(bl_verify_ack_t* pack,
header_t header,
uint8_t valid,
uint32_t checksum){
	
	pack->header = header;
	pack->valid = valid;
	pack->checksum = checksum;

}


uint16_t err_encode(uint8_t* data, err_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_ERR_ID;
	pack->header.len = sizeof(err_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(err_t) -4));
	return sizeof(err_t);
}


uint16_t err_ack_encode(uint8_t* data, err_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_ERR_ACK_ID;
	pack->header.len = sizeof(err_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(err_ack_t) -4));
	return sizeof(err_ack_t);
}


uint16_t bl_get_ver_encode(uint8_t* data, bl_get_ver_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_GET_VER_ID;
	pack->header.len = sizeof(bl_get_ver_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_ver_t) -4));
	return sizeof(bl_get_ver_t);
}


uint16_t bl_get_ver_ack_encode(uint8_t* data, bl_get_ver_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_GET_VER_ACK_ID;
	pack->header.len = sizeof(bl_get_ver_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_ver_ack_t) -4));
	return sizeof(bl_get_ver_ack_t);
}


uint16_t bl_get_id_encode(uint8_t* data, bl_get_id_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_GET_ID_ID;
	pack->header.len = sizeof(bl_get_id_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_id_t) -4));
	return sizeof(bl_get_id_t);
}


uint16_t bl_get_id_ack_encode(uint8_t* data, bl_get_id_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_GET_ID_ACK_ID;
	pack->header.len = sizeof(bl_get_id_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_get_id_ack_t) -4));
	return sizeof(bl_get_id_ack_t);
}


uint16_t bl_jump_app_encode(uint8_t* data, bl_jump_app_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_JUMP_APP_ID;
	pack->header.len = sizeof(bl_jump_app_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_jump_app_t) -4));
	return sizeof(bl_jump_app_t);
}


uint16_t bl_jump_app_ack_encode(uint8_t* data, bl_jump_app_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_JUMP_APP_ACK_ID;
	pack->header.len = sizeof(bl_jump_app_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_jump_app_ack_t) -4));
	return sizeof(bl_jump_app_ack_t);
}


uint16_t bl_mem_erase_encode(uint8_t* data, bl_mem_erase_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_MEM_ERASE_ID;
	pack->header.len = sizeof(bl_mem_erase_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_erase_t) -4));
	return sizeof(bl_mem_erase_t);
}


uint16_t bl_mem_erase_ack_encode(uint8_t* data, bl_mem_erase_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_MEM_ERASE_ACK_ID;
	pack->header.len = sizeof(bl_mem_erase_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_erase_ack_t) -4));
	return sizeof(bl_mem_erase_ack_t);
}


uint16_t bl_mem_write_encode(uint8_t* data, bl_mem_write_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_MEM_WRITE_ID;
	pack->header.len = sizeof(bl_mem_write_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_write_t) -4));
	return sizeof(bl_mem_write_t);
}


uint16_t bl_mem_write_ack_encode(uint8_t* data, bl_mem_write_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_MEM_WRITE_ACK_ID;
	pack->header.len = sizeof(bl_mem_write_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_write_ack_t) -4));
	return sizeof(bl_mem_write_ack_t);
}


uint16_t bl_mem_read_encode(uint8_t* data, bl_mem_read_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_MEM_READ_ID;
	pack->header.len = sizeof(bl_mem_read_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_read_t) -4));
	return sizeof(bl_mem_read_t);
}


uint16_t bl_mem_read_ack_encode(uint8_t* data, bl_mem_read_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_MEM_READ_ACK_ID;
	pack->header.len = sizeof(bl_mem_read_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_mem_read_ack_t) -4));
	return sizeof(bl_mem_read_ack_t);
}


uint16_t bl_reset_encode(uint8_t* data, bl_reset_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_RESET_ID;
	pack->header.len = sizeof(bl_reset_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_reset_t) -4));
	return sizeof(bl_reset_t);
}


uint16_t bl_reset_ack_encode(uint8_t* data, bl_reset_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_RESET_ACK_ID;
	pack->header.len = sizeof(bl_reset_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_reset_ack_t) -4));
	return sizeof(bl_reset_ack_t);
}


uint16_t bl_verify_encode(uint8_t* data, bl_verify_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_VERIFY_ID;
	pack->header.len = sizeof(bl_verify_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_verify_t) -4));
	return sizeof(bl_verify_t);
}


uint16_t bl_verify_ack_encode(uint8_t* data, bl_verify_ack_t* pack, uint16_t len){
	pack->header.header = 0x55;
	pack->header.packet_type = PACK_BL_VERIFY_ACK_ID;
	pack->header.len = sizeof(bl_verify_ack_t)-1-1;
	pack->checksum = check_function(pack, (sizeof(bl_verify_ack_t) -4));
	return sizeof(bl_verify_ack_t);
}

__attribute__ ((weak))
uint8_t packet_parser(uint8_t* buf,uint8_t data,parse_state_t* ps){
	//need a struct to record FSM state
	uint32_t crc_val;
	buf[ps->rx_index] = data;
	
	switch (ps->state)
	{
		case PARSE_STATE_START:
		if (buf[ps->rx_index] == 0x55)
		{
			ps->state = PARSE_STATE_LEN;
		}
		break;
		case PARSE_STATE_LEN:
		if(buf[ps->rx_index]<250)   //packet should be smaller than 255 bytes
		{
			ps->data_len = buf[ps->rx_index];
			ps->state = PARSE_STATE_DATA;
		}
		break;
		case PARSE_STATE_DATA:
		ps->now_idx++;
		if(ps->now_idx == ps->data_len)
		{
			ps->state = PARSE_STATE_CHECK;
			uint8_t ind = (ps->data_len+2) - PACK_CRC_LEN;
			
			
			
			crc_val =(uint32_t)(buf[ind+0]<<0)  +
			(uint32_t)(buf[ind+1]<<8)  +
			(uint32_t)(buf[ind+2]<<16) +
			(uint32_t)(buf[ind+3]<<24);
			

			if(sum32(buf,ind) == crc_val){
				ps->rx_index = 0;
				ps->now_idx = 0;
				ps->data_len = 0;
				ps->state = PARSE_STATE_START;
				return buf[2];
			}

		}
		break;
	}
	ps->rx_index++;
	return 0;
}

