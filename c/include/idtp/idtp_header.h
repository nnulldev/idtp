// SPDX-License-Identifier: Apache-2.0.
// Copyright (C) 2025-present idtp project and contributors.

//! IDTP header related declarations.

#ifndef IDTP_IDTP_HEADER_H
#define IDTP_IDTP_HEADER_H

#include <idtp/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

/// IDTP version information struct.
typedef struct {
    /// Increments after incompatible API changes were made.
    uint8_t major;
    /// Increments after adding functionality in a backwards-compatible manner.
    uint8_t minor;
    /// Increments after backwards-compatible bug fixes were made.
    uint8_t patch;
} IdtpVersion;

/// IDTP protocol version number that increments after incompatible API
/// changes were made.
#define IDTP_VERSION_MAJOR (1)

/// IDTP protocol version number that increments after adding functionality in
/// a backwards-compatible manner.
#define IDTP_VERSION_MINOR (0)

/// IDTP protocol version number that increments after backwards-compatible bug
/// fixes were made.
#define IDTP_VERSION_PATCH (0)

/// Current IDTP version.
#define IDTP_VERSION (IdtpVersion) { \
    IDTP_VERSION_MAJOR, \
    IDTP_VERSION_MINOR, \
    IDTP_VERSION_PATCH  \
}

/// IDTP operating mode.
typedef enum {
    /// IDTP-N (Normal mode) - operating mode with general protection.
    /// Error detection provided by checksum only.
    ///
    /// Detects simple errors like single-bit errors and some small
    /// burst errors. However, it's less effective against more complex or
    /// patterned errors.
    ///
    /// Only `checksum` field of IDTP header is used. The `crc` field is unused
    /// and filled with zeros.
    IDTP_MODE_NORMAL = 0x00,
    /// IDTP-S (Safety mode) - operating mode with more complex protection.
    /// Error detection provided by checksum and CRC (Cyclic Redundancy Check).
    ///
    /// CRC is effective at detecting common error patterns,
    /// including single-bit errors, burst errors, and many random errors.
    /// The effectiveness depends on the choice of generator polynomial.
    ///
    /// Both `checksum` and `crc` fields of IDTP header are used.
    IDTP_MODE_SAFETY = 0x01,
    /// Unknown mode value. No special handling required.
    IDTP_MODE_UNKNOWN = 0xff,
} IdtpMode;

/// Size of IDTP preamble in bytes.
#define IDTP_PREAMBLE_SIZE (4)

/// Size of IDTP trailer in bytes.
#define IDTP_TRAILER_SIZE (4)

/// Value to signal the start of a new IDTP packet.
extern const uint8_t IDTP_PREAMBLE[IDTP_PREAMBLE_SIZE];

/// Value to signal the end of a new IDTP packet.
extern const uint8_t IDTP_TRAILER[IDTP_TRAILER_SIZE];

/// IDTP header struct.
typedef struct PACKED {
    /// Value to signal the start of a new IDTP packet.
    uint8_t preamble[IDTP_PREAMBLE_SIZE];
    /// Protocol version in format MAJOR.MINOR.PATCH.
    IdtpVersion version;
    /// Protocol operating mode.
    uint8_t mode;
    /// IMU device identifier.
    uint16_t device_id;
    /// Value to used for simple error detection.
    uint16_t checksum;
    /// Timestamp from the IMU's MCU internal clock.
    uint32_t timestamp;
    /// Sequence number of IDTP packet sent.
    uint32_t sequence;
    /// Cyclic Redundancy Check - value to used for complex error detection.
    uint32_t crc;
    /// Size of packet payload in bytes.
    uint32_t payload_size;
    /// Packet payload type.
    uint8_t payload_type;
    /// Reserved field.
    uint8_t reserved[3];
} IdtpHeader;

/// Size of IDTP header in bytes.
#define IDTP_HEADER_SIZE (sizeof(IdtpHeader))

/// @brief Create new IDTP header object.
///
/// @return New IDTP header.
IdtpHeader idtp_header_create(void);

/// @brief Convert IDTP header byte order.
///
/// @param [out] header given IDTP header object to change.
void idtp_header_convert_endian(IdtpHeader *header);

/// @brief Set IDTP header from raw bytes.
///
/// @param [in] bytes given IDTP header bytes array pointer.
///
/// @return IDTP header from raw bytes.
IdtpHeader idtp_header_from_bytes(const uint8_t *bytes);

#ifdef __cplusplus
}
#endif

#endif // IDTP_IDTP_HEADER_H
