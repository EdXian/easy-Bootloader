#include "atmel_start.h"
#include "atmel_start_pins.h"
#include <string.h>
#include "boot.h"

#define MAJOR_VER 1
#define MINOR_VER 2
#define PATCH_NUM 3


#define BL_FLASH_IO   FLASH_0
#define BL_USART_IO   EDBG_COM
#define IS_BOOT_MODE (pin_mode == BOOT_MODE)
#define BOOT_PIN boot_pin
#define BUSY_PIN busy_pin

#define BOOTLOADER_VERSION						"v1.00\n"
#define BOOTLOADER_TIME							""__DATE__" "__TIME__"\n"

#define cpu_irq_enable()				\
do {                                \
	__DMB();                        \
	__enable_irq();                 \
} while (0)

#define cpu_irq_disable()				\
do {                                \
	__disable_irq();                \
	__DMB();                        \
} while (0)

#define MIN(a, b)           (((a) < (b)) ?  (a) : (b))


void uart_recv(uint8_t* str,uint16_t len);
uint8_t message_decode(uint8_t* buf,uint8_t msg_id);
uint8_t packet_parser(uint8_t* buf,uint8_t data,parse_state_t* ps);

void bootloader_handle_getcid_cmd(bl_get_id_t cmd);
void bootloader_handle_getver_cmd(bl_get_ver_t cmd);
void bootloader_handle_mem_write_cmd(bl_mem_write_t cmd);
void bootloader_handle_mem_read_cmd(bl_mem_read_t cmd);
void bootloader_handle_reset_cmd(bl_reset_t cmd);


volatile uint32_t sp;
uint8_t flash_read_buf[200];
uint8_t pdata[PACK_LEN];
uint8_t buf;
//gpio_toggle_pin_level(LED0);
parse_state_t ps;
uint8_t msg_id;



bl_get_ver_t	get_ver_cmd;	  //ok	
bl_get_id_t		get_id_cmd;       //ok
bl_jump_app_t	jump_app_cmd;	  //ok
bl_mem_erase_t	mem_erase_cmd;    //ok
bl_mem_write_t	mem_write_cmd;    //test ok
bl_mem_read_t	mem_read_cmd;     //test ok
bl_reset_t      reset_cmd;		  //ok
bl_verify_t		verify_cmd;		  //ok

uint8_t test_data[200];

header_t head;


uint8_t pin_mode;
uint8_t cmd[]={0x30, 0x55, 0x05, 0x03, 0x5d, 0x00, 0x00, 0x00};
int main(void)
{
	uint8_t recv_char;

	atmel_start_init();

	usart_sync_enable(&EDBG_COM);
	
	pin_mode = gpio_get_pin_level(BOOT_PIN); //ensure pin mode
	pin_mode = gpio_get_pin_level(BOOT_PIN);
	
	
	bl_get_ver_encode(NULL,&get_ver_cmd,sizeof(get_ver_cmd));
	bl_get_id_encode(NULL,&get_id_cmd,sizeof(get_id_cmd));
	
	//bl_verify_encode(NULL,&verify_cmd,sizeof(verify_cmd));
	//memcpy(test_data,&verify_cmd,sizeof(verify_cmd));
	/*
	mem_write_cmd.start_addr = 0x4000;
	mem_write_cmd.length = 128;
	for (uint8_t i=0;i<128;i++)
	{
		mem_write_cmd.data[i] = i;
	}
	bl_mem_write_encode(NULL,&mem_write_cmd,sizeof(mem_write_cmd));
	memcpy(test_data,&mem_write_cmd,sizeof(mem_write_cmd));
	*/
	
	mem_read_cmd.start_addr = 0x4000;
	mem_read_cmd.end_addr = 0x4080;
	bl_mem_read_encode(NULL,&mem_read_cmd,sizeof(mem_read_cmd));
	
	
	
	pin_mode = gpio_get_pin_level(BOOT_PIN); //ensure pin mode
	pin_mode = gpio_get_pin_level(BOOT_PIN);
	memset(pdata,0,200);
	while (1)
	{
		pin_mode = gpio_get_pin_level(BOOT_PIN);
		if(IS_BOOT_MODE){
			/*
			memset(pdata,0,200);
			
			for(uint8_t i=0;i<sizeof(cmd);i++){
				buf = cmd[i];
				//uart_recv(&test_data[i] , 1);
				msg_id = packet_parser(pdata,buf,&ps);
				if (msg_id)
				{
				message_decode(pdata,msg_id);	
				}
				
			}*/
			
			uart_recv(&buf,1);
			msg_id = packet_parser(pdata,buf,&ps);
			if (msg_id)
			{
				gpio_set_pin_level(BUSY_PIN,false);
				message_decode(pdata,msg_id);
				memset(pdata,0,200);
				sp+=1;
				gpio_set_pin_level(BUSY_PIN,true);
			}
				
			//can_bootloader_run
			//spi_bootloader_run
		}else{
			jump_to_application();
		}

	}
}

void uart_bootloader_run(void){
	memset(pdata,0,200);
	for(uint8_t i=0;i<sizeof(mem_erase_cmd);i++){
		buf = test_data[i];
		//uart_recv(&test_data[i] , 1);
		msg_id = packet_parser(pdata,buf,&ps);
		message_decode(pdata,msg_id);
	}
}

void uart_recv(uint8_t* str,uint16_t len){
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&BL_USART_IO, &io);
	usart_sync_enable(&BL_USART_IO);
	io_read(io, str, len);
}

void uart_send(uint8_t* data, uint16_t len){
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&BL_USART_IO, &io);
	usart_sync_enable(&BL_USART_IO);
	io_write(io, data, len);
}


bl_get_ver_t	get_ver_cmd;
bl_get_id_t		get_id_cmd;
bl_jump_app_t	jump_app_cmd;
bl_mem_erase_t	mem_erase_cmd;
bl_mem_write_t	mem_write_cmd;
bl_mem_read_t	mem_read_cmd;
bl_reset_t      reset_cmd;
bl_verify_t		verify_cmd;

uint8_t message_decode(uint8_t* buf,uint8_t msg_id){
	switch (msg_id)
	{
		
		case PACK_BL_GET_VER_ID:
			memcpy(&get_ver_cmd,buf,sizeof(get_ver_cmd));
			bootloader_handle_getver_cmd(get_ver_cmd);
			break;
		
		case PACK_BL_GET_ID_ID:
			memcpy(&get_id_cmd,buf,sizeof(get_id_cmd));
			bootloader_handle_getcid_cmd(get_id_cmd);
			break;
			
		case PACK_BL_JUMP_APP_ID:
			memcpy(&jump_app_cmd,buf,sizeof(jump_app_cmd));
			bootloader_handle_jump_to_address(jump_app_cmd);
			break;
			
		case PACK_BL_MEM_ERASE_ID:
			memcpy(&mem_erase_cmd,buf,sizeof(mem_erase_cmd));			
			bootloader_flash_erase_cmd(mem_erase_cmd);
			break;
			
		case PACK_BL_MEM_WRITE_ID:
			memcpy(&mem_write_cmd,buf,sizeof(mem_write_cmd));
			bootloader_handle_mem_write_cmd(mem_write_cmd);
			break;
			
		case PACK_BL_MEM_READ_ID:
			memcpy(&mem_read_cmd,buf,sizeof(mem_read_cmd));
			bootloader_handle_mem_read_cmd(mem_read_cmd);
			break;
			
		case PACK_BL_RESET_ID:
			memcpy(&reset_cmd,buf,sizeof(reset_cmd));
			bootloader_handle_reset_cmd(reset_cmd);
			break;

		case PACK_BL_VERIFY_ID:
			memcpy(&verify_cmd,buf,sizeof(verify_cmd));
			bootloader_handle_verify_cmd(verify_cmd);
			break;
	}
}

void sw_reset_handler(void){
	//bootloader_handle_reset();

	void (*app_start_address)(void);
	//flash_read(&BL_FLASH_IO,0x5e00,(uint8_t*)&boot_label,sizeof(bootloader_label_t));
	app_start_address = *(uint32_t *)(0x0000 + 4);
	// To check the app is stored in Flash
	//if (app_start_address == 0xFFFFFFFF) {
	///* Stay in Bootloader */
	//return;
	//}
	__set_MSP(*(uint32_t *) 0x0000); //set the main stack pointer as app address
	//__DMB();
	SCB->VTOR = ((uint32_t)0x0000 & SCB_VTOR_TBLOFF_Msk);  //rebase the vector table
	//SCB->VTOR = (uint32_t*) APP_START_ADDRESS;
	//__DSB();
	//bx lr  to app address
	asm("bx %0"::"r"(app_start_address));

}

void jump_to_application(void){

	void (*app_start_address)(void);
	//flash_read(&BL_FLASH_IO,0x5e00,(uint8_t*)&boot_label,sizeof(bootloader_label_t));
	app_start_address = *(uint32_t *)(0x6000 + 4);
	// To check the app is stored in Flash
	//if (app_start_address == 0xFFFFFFFF) {
	///* Stay in Bootloader */
	//return;
	//}
	__set_MSP(*(uint32_t *) 0x6000); //set the main stack pointer as app address
	//__DMB();
	SCB->VTOR = ((uint32_t)0x6000 & SCB_VTOR_TBLOFF_Msk);  //rebase the vector table
	//SCB->VTOR = (uint32_t*) APP_START_ADDRESS;
	//__DSB();
	//bx lr  to app address
	asm("bx %0"::"r"(app_start_address));
}

void bootloader_handle_jump_to_address(uint32_t address)
{
	uint32_t app_start_address;

	//clear all interrupt source
	for(uint8_t i=0;i<8;i++){
		NVIC->ICER[ i ] = 0xFFFFFFFF ;
	}
	for(uint8_t i=0;i<8;i++){
		NVIC->ICPR[ i ] = 0xFFFFFFFF ;
	}

	sp = __get_MSP();

	/* Rebase the Stack Pointer */
	__set_MSP(*(uint32_t *) address);

	/* Rebase the vector table base address */
	SCB->VTOR = ((uint32_t) address & SCB_VTOR_TBLOFF_Msk);

	/* Load the Reset Handler address of the application */
	app_start_address = *(uint32_t *)(address + 4);

	/* Jump to application Reset Handler in the application */
	asm("bx %0"::"r"(app_start_address));
}

void bootloader_handle_getver_cmd(bl_get_ver_t cmd)
{
	bl_get_ver_ack_t ack;
	ack.major = MAJOR_VER;
	ack.minor = MINOR_VER;
	ack.patch = PATCH_NUM; 
	bl_get_ver_ack_encode(NULL,&ack,sizeof(ack));
	uart_send(&ack,sizeof(ack));
}

void bootloader_handle_getcid_cmd(bl_get_id_t cmd){
	bl_get_id_ack_t ack;
	ack.chip_id = 0xffffffff;
	bl_get_id_ack_encode(NULL,&ack,sizeof(ack));
	uart_send(&ack,sizeof(ack));
}


void bootloader_handle_mem_read_cmd(bl_mem_read_t cmd){
	bl_mem_read_ack_t ack;
	int32_t ret;
	uint32_t start_addr = cmd.start_addr;
	uint32_t end_addr =  cmd.end_addr;
	
	uint32_t read_length =end_addr - start_addr;

	ret = flash_read(&BL_FLASH_IO,cmd.start_addr,flash_read_buf,read_length);
	switch (ret)
	{
		case ERR_BAD_ADDRESS:
			ack.valid = ERR_BAD_ADDRESS;
		break;
		
		case ERR_NONE:
			ack.valid = ERR_NONE;
		break;
	}
	memset(&ack.data[0],0,128);
	for (uint8_t i=0;i<128;i++)
	{
		ack.data[i] = flash_read_buf[i];
	}
	ack.read_length = 128;
	bl_mem_read_ack_encode(NULL,&ack,sizeof(ack));

	uart_send(&ack,sizeof(ack));
}


void bootloader_handle_mem_write_cmd(bl_mem_write_t cmd)
{
	uint32_t ret;
	bl_mem_write_ack_t ack;
	uint32_t write_address = cmd.start_addr;
	uint32_t write_length = cmd.length ;
	uint32_t *write_data_ptr = &cmd.data;
	ret = flash_write(&BL_FLASH_IO, write_address,(uint8_t*)write_data_ptr, write_length);
	delay_ms(1);   //wait for cpu stall	
	switch (ret)
	{
		case ERR_BAD_ADDRESS:
			ack.valid = ERR_BAD_ADDRESS;
			break;
		case ERR_DENIED:
			ack.valid = ERR_DENIED;
			break;
		case ERR_NONE:
			ack.valid = ERR_NONE;
			break;
	}
	bl_mem_write_ack_encode(NULL,&ack,sizeof(ack));

	uart_send(&ack,sizeof(ack));
}

void bootloader_flash_erase_cmd(bl_mem_erase_t cmd){
	uint32_t start = cmd.start_addr;
	uint32_t end  = cmd.end_addr;
	uint32_t page_size;
	uint32_t erase_pages;
	bl_mem_erase_ack_t ack;
	if (start > end)
	{
		return;
	}
	page_size = flash_get_page_size(&BL_FLASH_IO);
	erase_pages = ((end - start)/page_size)+1; 
	//flash_erase(&BL_FLASH_IO, start, erase_pages);
	
	ack.valid = BL_ACK;
	bl_mem_erase_ack_encode(NULL,&ack,sizeof(ack));
	uart_send(&ack,sizeof(ack));
	
	delay_ms(1);
}


void bootloader_handle_reset_cmd(bl_reset_t cmd){
	bl_reset_ack_t ack;
	ack.valid = 0x00;
	bl_reset_ack_encode(NULL,&ack,sizeof(ack));
	uart_send(&ack,sizeof(ack));
	gpio_set_pin_level(BUSY_PIN,true);
	SCB->AIRCR = (0x5FA<<SCB_AIRCR_VECTKEY_Pos)|SCB_AIRCR_SYSRESETREQ_Msk;
	// cortex M4 software reset
	//SCB_AIRCR = SCB_AIRCR_VECTKEY(0x5FA) | SCB_AIRCR_SYSRESETREQ_MASK;
}

void bootloader_handle_verify_cmd(bl_verify_t cmd){
	
}

uint8_t packet_parser(uint8_t* buf,uint8_t data,parse_state_t* ps){
	//need a struct to record FSM state
	err_t  err;
	uint8_t err_buf[10];
	uint32_t crc_val;
	uint8_t ret;
	uint8_t i=0;
	//uint8_t start_idx;
	
	buf[ps->rx_index] = data;
	
	switch (ps->state)
	{
		case PARSE_STATE_START:
		
		for (i=0;i<PACK_LEN;i++)
		{
			if(buf[i] == 0x55){
				ps->start_idx = i;
				break;
			}
		}
		if(buf[ps->start_idx] == 0x55)
		{
			ps->state = PARSE_STATE_LEN;
		}
		break;
		case PARSE_STATE_LEN:
		if(buf[ps->start_idx+1]<PACK_LEN)   //packet should be smaller than 255 bytes
		{
			ps->data_len = buf[ps->start_idx+1];
			ps->state = PARSE_STATE_DATA;
		}
		break;
		case PARSE_STATE_DATA:
		ps->now_idx++;
		if(ps->now_idx == ps->data_len)
		{
			ps->state = PARSE_STATE_CHECK;
			uint8_t ind = ps->start_idx + (ps->data_len+2) - PACK_CRC_LEN;
			uint8_t len = (ps->data_len+2)- PACK_CRC_LEN;
			crc_val =(uint32_t)(buf[ind+0]<<0)  +
			(uint32_t)(buf[ ind+1]<<8)  +
			(uint32_t)(buf[ ind+2]<<16) +
			(uint32_t)(buf[ ind+3]<<24);

			if(sum32(&buf[ps->start_idx],len) == crc_val){
				ps->start_idx = 0;
				ps->rx_index = 0;
				ps->now_idx = 0;
				ps->data_len = 0;
				ps->state = PARSE_STATE_START;
				return buf[ps->start_idx+2];
			}else{
				
				ps->rx_index = 0;
				ps->now_idx = 0;
				ps->data_len = 0;
				ps->state = PARSE_STATE_START;
				//send error ack
				err_encode(err_buf,&err,sizeof(err));
				uart_send(&err,sizeof(err));
			
			}
		}
		break;
	}
	ps->rx_index++;
	return 0;
}
