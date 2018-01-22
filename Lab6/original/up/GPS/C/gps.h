#ifndef gps_header
#define gps_header

#include "stm32f4xx_hal.h"
#include "usart.h"
#include "stdlib.h"
#include "string.h"

typedef struct gps_state {
	UART_HandleTypeDef* uart;
	uint8_t line_buffer[100];
	uint8_t writer_position;
	uint8_t reader_position;
	uint8_t field_buffer[30];
	uint8_t field_position;

	uint8_t date_day;
	uint8_t date_mounth;
	uint8_t date_year;
	uint8_t time_hour;
	uint8_t time_min;
	uint8_t time_sec;

	double latitude;
	char latitude_direction;
	double longitude;
	char longitude_direction;
	double altitude;

	double speed_knots;
	double speed_kilometers;

	uint8_t satelites_number;
	uint8_t quality;
	double dop;
	double hdop;
	double vdop;
} gps_state;

gps_state gps_init(UART_HandleTypeDef* _uart);
void gps_recv_char(gps_state* state, uint8_t recv_char);
void gps_read_field(gps_state* state);
void gps_process_line(gps_state* state);
void gps_process_gprmc(gps_state* state);
void gps_process_gpvtg(gps_state* state);
void gps_process_gpgga(gps_state* state);
void gps_process_gpgsa(gps_state* state);

#endif
