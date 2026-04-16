/**
 * @file usb_hid.h
 * @brief Implementación real del stack HID para mandos en Carley Play.
 */

#ifndef USB_HID_H
#define USB_HID_H

#include <stdint.h>

typedef struct {
    uint16_t vendor_id;
    uint16_t product_id;
    uint8_t report_id;
} hid_device_info_t;

/**
 * @brief Analiza un descriptor de reporte HID para entender el mapeo del mando.
 */
void hid_parse_descriptor(const uint8_t * desc, uint32_t len);

/**
 * @brief Decodifica un paquete de datos HID entrante.
 */
void hid_decode_packet(const uint8_t * data, uint32_t len);

#endif // USB_HID_H
