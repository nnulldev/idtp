// SPDX-License-Identifier: Apache-2.0.
// Copyright (C) 2025-present idtp project and contributors.

//! IDTP header related declarations.

#include <idtp/idtp_header.h>
#include <string.h>

const uint8_t IDTP_PREAMBLE[IDTP_PREAMBLE_SIZE] = { 'I', 'D', 'T', 'P' };
const uint8_t IDTP_TRAILER[IDTP_TRAILER_SIZE]   = { 'P', 'D', 'T', 'I' };

void idtp_header_convert_endian(IdtpHeader *header) {
    header->device_id    = swap_uint16(header->device_id);
    header->checksum     = swap_uint16(header->checksum);
    header->timestamp    = swap_uint32(header->timestamp);
    header->sequence     = swap_uint32(header->sequence);
    header->crc          = swap_uint32(header->crc);
    header->payload_size = swap_uint32(header->payload_size);
}

IdtpHeader idtp_header_create(void) {
    IdtpHeader header = {0};

    memset(&header, 0, sizeof(IdtpHeader));
    memcpy(&header.preamble, IDTP_PREAMBLE, IDTP_PREAMBLE_SIZE);
    header.version = IDTP_VERSION;
    header.mode    = IDTP_MODE_NORMAL;
    idtp_header_convert_endian(&header);

    return header;
}

IdtpHeader idtp_header_from_bytes(const uint8_t *bytes) {
    IdtpHeader header = {0};
    memcpy(&header, (IdtpHeader *)bytes, IDTP_HEADER_SIZE);
    idtp_header_convert_endian(&header);

    return header;
}
