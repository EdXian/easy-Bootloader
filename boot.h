#include "stdint.h"
#ifndef __BOOT_H_
#define __BOOT_H_
/* MSG_ID macros */
#define	BL_GET_VER	0x51
#define	BL_GET_HELP	0x52
#define	BL_GET_CID	0x53
#define	BL_GET_RDP_STATUS	0x54
#define	BL_GO_TO_ADDR	0x55
#define	BL_FLASH_ERASE	0x56
#define	BL_MEM_WRITE	0x57
#define	BL_EN_RW_PROTECT	0x58
#define	BL_MEM_READ	0x59
#define	BL_READ_SECTOR_P_STATUS	0x5A
#define	BL_READ_LABEL	0x5B
#define	BL_DIS_R_W_PROTECT	0x5C
#define	BL_RESET_MCU	0x5D
/* PARAM macros */
#define	PACK_LEN	200
#define	BOOT_MODE	0
#define	CRC_CHECK_LENGTH	128
#define	BL_FLASH_IO	FLASH_0
#define	BL_USART_IO	USART_0
#define	IS_BOOT_MODE	(pin_mode == BOOT_MODE)
#define	BL_ACK	0XA5
#define	BL_NACK	0X7F
/* CHIP_ID macros */
#define	CHIPID_W0	((uint32_t*)( 0x008061FC))
#define	CHIPID_W1	((uint32_t*)( 0x00806010))
#define	CHIPID_W2	((uint32_t*)( 0x00806014))
#define	CHIPID_W3	((uint32_t*)( 0x00806018))
/* MEMORY_MAP macros */
#define	BL_START_ADDRESS	0x00000000
#define	BL_END_ADDRESS	0x00002000
#define	APP_START_ADDRESS	0x6000
#define	APP_END_ADDRESS	0x37FFF
#define	APP_SIZE	(APP_END_ADDRESS-APP_START_ADDRESS)
#define	BACKUP_APP_START_ADDRESS	0x42000
#define	BACKUP_APP_END_ADDRESS	0x73FFF
#define	BACKUP_APP_SIZE	(BACKUP_APP_END_ADDRESS-BACKUP_APP_START_ADDRESS)

/* MEMORY_MAP enumeration */




enum parser{
	PARSE_STATE_START=0,
	PARSE_STATE_LEN=1,
	PARSE_STATE_DATA=2,
	PARSE_STATE_CHECK =3
};

typedef struct parse_state{
	uint8_t now_idx;
	uint8_t rx_index;
	uint8_t state;
	uint8_t data_len;
}parse_state_t;



#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct header_struct{

	uint8_t header;
	uint8_t len;
	uint8_t packet_type;

}header_t;

#define PACK_ERR_ID 1
#define PACK_ERR_LEN sizeof(err_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct err_struct{

	header_t header;
	uint32_t checksum;

}err_t;

#define PACK_ERR_ACK_ID 2
#define PACK_ERR_ACK_LEN sizeof(err_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct err_ack_struct{

	header_t header;
	uint32_t checksum;

}err_ack_t;

#define PACK_BL_GET_VER_ID 3
#define PACK_BL_GET_VER_LEN sizeof(bl_get_ver_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_ver_struct{

	header_t header;
	uint32_t checksum;

}bl_get_ver_t;

#define PACK_BL_GET_VER_ACK_ID 4
#define PACK_BL_GET_VER_ACK_LEN sizeof(bl_get_ver_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_ver_ack_struct{

	header_t header;
	uint8_t major;
	uint8_t minor;
	uint8_t patch;
	uint32_t checksum;

}bl_get_ver_ack_t;

#define PACK_BL_GET_ID_ID 5
#define PACK_BL_GET_ID_LEN sizeof(bl_get_id_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_id_struct{

	header_t header;
	uint32_t checksum;

}bl_get_id_t;

#define PACK_BL_GET_ID_ACK_ID 6
#define PACK_BL_GET_ID_ACK_LEN sizeof(bl_get_id_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_get_id_ack_struct{

	header_t header;
	uint32_t chip_id;
	uint32_t checksum;

}bl_get_id_ack_t;

#define PACK_BL_JUMP_APP_ID 7
#define PACK_BL_JUMP_APP_LEN sizeof(bl_jump_app_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_jump_app_struct{

	header_t header;
	uint32_t addr;
	uint32_t checksum;

}bl_jump_app_t;

#define PACK_BL_JUMP_APP_ACK_ID 8
#define PACK_BL_JUMP_APP_ACK_LEN sizeof(bl_jump_app_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_jump_app_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_jump_app_ack_t;

#define PACK_BL_MEM_ERASE_ID 9
#define PACK_BL_MEM_ERASE_LEN sizeof(bl_mem_erase_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_erase_struct{

	header_t header;
	uint32_t start_addr;
	uint32_t end_addr;
	uint32_t checksum;

}bl_mem_erase_t;

#define PACK_BL_MEM_ERASE_ACK_ID 10
#define PACK_BL_MEM_ERASE_ACK_LEN sizeof(bl_mem_erase_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_erase_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_mem_erase_ack_t;

#define PACK_BL_MEM_WRITE_ID 11
#define PACK_BL_MEM_WRITE_LEN sizeof(bl_mem_write_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_write_struct{

	header_t header;
	uint32_t start_addr;
	uint8_t length;
	uint8_t data[128];
	uint32_t checksum;

}bl_mem_write_t;

#define PACK_BL_MEM_WRITE_ACK_ID 12
#define PACK_BL_MEM_WRITE_ACK_LEN sizeof(bl_mem_write_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_write_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_mem_write_ack_t;

#define PACK_BL_MEM_READ_ID 13
#define PACK_BL_MEM_READ_LEN sizeof(bl_mem_read_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_read_struct{

	header_t header;
	uint32_t start_addr;
	uint32_t end_addr;
	uint32_t checksum;

}bl_mem_read_t;

#define PACK_BL_MEM_READ_ACK_ID 14
#define PACK_BL_MEM_READ_ACK_LEN sizeof(bl_mem_read_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_mem_read_ack_struct{

	header_t header;
	uint8_t valid;
	uint8_t length;
	uint8_t data[128];
	uint32_t checksum;

}bl_mem_read_ack_t;

#define PACK_BL_RESET_ID 15
#define PACK_BL_RESET_LEN sizeof(bl_reset_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_reset_struct{

	header_t header;
	uint32_t checksum;

}bl_reset_t;

#define PACK_BL_RESET_ACK_ID 16
#define PACK_BL_RESET_ACK_LEN sizeof(bl_reset_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_reset_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_reset_ack_t;

#define PACK_BL_VERIFY_ID 17
#define PACK_BL_VERIFY_LEN sizeof(bl_verify_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_verify_struct{

	header_t header;
	uint32_t start_addr;
	uint32_t end_addr;
	uint32_t verify_code;
	uint32_t checksum;

}bl_verify_t;

#define PACK_BL_VERIFY_ACK_ID 18
#define PACK_BL_VERIFY_ACK_LEN sizeof(bl_verify_ack_t)
#define PACK_CRC_LEN 4

#pragma pack(1)
#pragma scalar_storage_order little-endian
typedef struct bl_verify_ack_struct{

	header_t header;
	uint8_t valid;
	uint32_t checksum;

}bl_verify_ack_t;


#endif
