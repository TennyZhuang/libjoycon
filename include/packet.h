#ifndef PACKET_H
#define PACKET_H

#include "output_report.h"
#include "input_report.h"

struct PacketMCUReadComm
{
    struct Header header;
    uint8_t subcommand;
    struct MCUConfiguration conf;
    uint8_t crc;
    uint8_t padding;
};

void joycon_packet_mcu_read_ack_encode(uint8_t *buffer, uint8_t timer, uint8_t index);
void joycon_packet_mcu_read_req_encode(uint8_t *buffer, uint8_t timer, uint8_t index);

struct PacketMCUConf
{
    struct Header header;
    uint8_t subcommand;
    struct MCUConfiguration conf;
    uint8_t padding;
    uint8_t crc;
};

void joycon_packet_mcu_conf_mode(uint8_t *buffer, uint8_t timer, uint8_t mode);
void joycon_packet_mcu_conf_ir_mode(uint8_t *buffer, uint8_t timer, uint8_t mode, uint8_t number);
void joycon_packet_mcu_conf_registers(uint8_t *buffer, uint8_t timer, uint8_t number,
    uint16_t *addrs, uint8_t *vals);
// TODO: Add a version with va_list for joycon_packet_mcu_conf_registers

#endif
