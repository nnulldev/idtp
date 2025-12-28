// SPDX-License-Identifier: Apache-2.0.
// Copyright (C) 2025-present idtp project and contributors.

//! Inertial Measurement Unit Data Transfer Protocol frame implementation.

#ifndef IDTP_IDTP_H
#define IDTP_IDTP_H

#include <idtp/idtp_header.h>

#ifdef __cplusplus
extern "C" {
#endif

/// IDTP network packet max size in bytes. It includes size of IDTP header,
/// payload and packet trailer.
#define IDTP_PACKET_MAX_SIZE (1024)

/// IDTP network packet min size in bytes.
#define IDTP_PACKET_MIN_SIZE (IDTP_HEADER_SIZE + IDTP_TRAILER_SIZE)

/// IDTP network packet payload max size in bytes.
#define IDTP_PAYLOAD_MAX_SIZE ( \
    IDTP_PACKET_MAX_SIZE - IDTP_HEADER_SIZE - IDTP_TRAILER_SIZE \
)

/// Inertial Measurement Unit Data Transfer Protocol frame struct.
typedef struct {
    /// IDTP network packet header.
    IdtpHeader header;
    /// Value that containing IMU data.
    uint8_t payload[IDTP_PAYLOAD_MAX_SIZE];
    /// IDTP payload size in bytes.
    size_t payload_size;
} IdtpFrame;

/// @brief Create new IDTP frame object.
///
/// @return New IDTP frame.
IdtpFrame idtp_frame_create(void);

/// @brief Set IDTP header.
///
/// @param [out] self given IDTP frame to change.
/// @param [in] header given IDTP header to set.
void idtp_frame_set_header(IdtpFrame *self, const IdtpHeader *header);

/// @brief Set IDTP payload.
///
/// @param [out] self given IDTP frame to change.
/// @param [in] payload given IDTP payload bytes to set.
/// @param [in] size given IDTP payload size in bytes.
void idtp_frame_set_payload(IdtpFrame *self, const uint8_t *payload, size_t size);

/// @brief Pack into raw IDTP network packet.
///
/// @param [out] self given IDTP frame to change.
/// @param [in] buffer given buffer to store raw IDTP packet.
///
/// @warning Buffer size should be enough to store whole IDTP packet.
void idtp_frame_pack(const IdtpFrame *self, uint8_t *buffer);

/// @brief Convert byte slice to IDTP frame.
///
/// @param [in] bytes given byte array to convert (big-endian byte order).
/// @param [in] size given number of bytes.
///
/// @return IDTP frame struct from byte array.
IdtpFrame idtp_frame_from_bytes(const uint8_t *bytes, size_t size);

#ifdef __cplusplus
    }
#endif

#endif // IDTP_IDTP_H
