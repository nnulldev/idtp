// SPDX-License-Identifier: Apache-2.0.
// Copyright (C) 2025-present idtp project and contributors.

//! Auxiliary declarations.

#ifndef IDTP_UTILS_H
#define IDTP_UTILS_H

#include <stdint.h>

/// Macro for packing structures. It instructs the compiler to pack
/// the structure members with no padding bytes between them.
#define PACKED __attribute__((packed))

/// @brief Change byte order in uint16 value.
///
/// @param [in] value given value to swap bytes.
///
/// @return New uint16 value with changed byte order.
uint16_t swap_uint16(uint16_t value);

/// @brief Change byte order in uint32 value.
///
/// @param [in] value given value to swap bytes.
///
/// @return New uint32 value with changed byte order.
uint32_t swap_uint32(uint32_t value);

#endif //IDTP_UTILS_H