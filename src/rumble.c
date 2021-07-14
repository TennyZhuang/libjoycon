#include <rumble.h>

struct RumbleEncodedData joycon_rumble_encode(float freq, float amp)
{
    // The encoded hex freq varies from 64 (0x40) to 
    uint8_t encoded_hex_freq = (uint8_t)round(log2f(freq / 10.0f) * 32.0f);
    uint16_t hf = (encoded_hex_freq > 0x60 ? (encoded_hex_freq - 0x60) << 2 : 0);
    uint8_t lf = encoded_hex_freq - 0x40;

    uint8_t encoded_hex_amp = 0;
    // Saturate
    if (amp > 1.0f) amp = 1.0f;
    if (amp < 0.0f) amp = 0.0f;

    if (amp > 0.23f) encoded_hex_amp = (uint8_t)round(log2f(amp * 8.7f) * 32.0f);
    else if (amp > 0.12f) encoded_hex_amp = (uint8_t)round(log2f(amp * 17.0f) * 16.0f);

    uint16_t hf_amp = encoded_hex_amp << 1;
    uint16_t lf_amp = (encoded_hex_amp >> 1) + 0x40;

    // FIXME: Byte might have been swapped
    struct RumbleEncodedData data;
    data.data[0] = (uint8_t)(hf & 0xFF);
    data.data[1] = (uint8_t)hf_amp + ((hf >> 8) & 0xFF);
    data.data[2] = lf + ((lf_amp >> 8) & 0xFF);
    data.data[3] = (uint8_t)(lf_amp & 0xFF);
    return data;
}
