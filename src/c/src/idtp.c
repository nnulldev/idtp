// SPDX-License-Identifier: Apache-2.0.
// Copyright (C) 2025-present idtp project and contributors.

//! Inertial Measurement Unit Data Transfer Protocol frame implementation.

#include <idtp/idtp.h>
#include <string.h>

IdtpFrame idtp_frame_create(void) {
    const IdtpFrame frame = (IdtpFrame) {
        .header = idtp_header_create(),
        .payload = {0},
        .payload_size = 0,
    };

    return frame;
}

void idtp_frame_set_header(IdtpFrame *self, const IdtpHeader *header) {
    self->header = *header;
}

void idtp_frame_set_payload(IdtpFrame *self, const uint8_t *payload, const size_t size) {
    if (size <= IDTP_PAYLOAD_MAX_SIZE) {
        memcpy(self->payload, payload, size);
        self->payload_size = size;
    }
}

void idtp_frame_pack(const IdtpFrame *self, uint8_t *buffer) {
    size_t lower_range = 0;

    IdtpHeader header = self->header;
    idtp_header_convert_endian(&header);

    memcpy(&buffer[lower_range], &header, IDTP_HEADER_SIZE);
    lower_range += IDTP_HEADER_SIZE;

    memcpy(&buffer[lower_range], self->payload, self->payload_size);
    lower_range += self->payload_size;

    memcpy(&buffer[lower_range], &IDTP_TRAILER, IDTP_TRAILER_SIZE);
}

IdtpFrame idtp_frame_from_bytes(const uint8_t *bytes, const size_t size) {
    IdtpFrame frame = {0};
    frame.header = idtp_header_from_bytes(bytes);
    frame.payload_size = size - IDTP_PACKET_MIN_SIZE;
    memcpy(frame.payload, &bytes[IDTP_HEADER_SIZE], frame.payload_size);

    return frame;
}
