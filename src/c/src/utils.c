// SPDX-License-Identifier: Apache-2.0.
// Copyright (C) 2025-present idtp project and contributors.

//! Auxiliary declarations.

#include <idtp/utils.h>

uint16_t swap_uint16(uint16_t value) {
    return (value >> 8) | (value << 8);
}

uint32_t swap_uint32(uint32_t value) {
    return ((value >> 24) & 0x000000FF) | ((value >> 8) & 0x0000FF00) |
           ((value << 8) & 0x00FF0000) | ((value << 24) & 0xFF000000);
}
