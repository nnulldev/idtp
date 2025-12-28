// SPDX-License-Identifier: Apache-2.0.
// Copyright (C) 2025-present idtp project and contributors.

//! IDTP frame implementation tests.

#include <gtest/gtest.h>
#include <idtp/idtp.h>

TEST(IdtpFrameTest, SetHeaderUpdatesHeader) {
    IdtpFrame frame = idtp_frame_create();
    const IdtpHeader header = idtp_header_create();
    idtp_frame_set_header(&frame, &header);

    EXPECT_EQ(memcmp(&frame.header, &header, sizeof(IdtpHeader)), 0);
}

#define TEST_PAYLOAD_SIZE (10)

TEST(IdtpFrameTest, SetPayload) {
    uint8_t payload_data[TEST_PAYLOAD_SIZE];

    for (size_t i = 0; i < TEST_PAYLOAD_SIZE; i++)
        payload_data[i] = i;

    IdtpFrame frame = idtp_frame_create();
    idtp_frame_set_payload(&frame, payload_data, TEST_PAYLOAD_SIZE);

    EXPECT_EQ(frame.payload_size, TEST_PAYLOAD_SIZE);
    EXPECT_EQ(memcmp(frame.payload, payload_data, TEST_PAYLOAD_SIZE), 0);
}

TEST(IdtpFrameTest, SetPayloadIgnoresTooLargeData) {
    IdtpFrame frame = idtp_frame_create();
    constexpr uint8_t big_payload[IDTP_PAYLOAD_MAX_SIZE+1] { };
    constexpr size_t too_large_size = IDTP_PAYLOAD_MAX_SIZE + 1;

    idtp_frame_set_payload(&frame, big_payload, too_large_size);
    EXPECT_LE(frame.payload_size, IDTP_PAYLOAD_MAX_SIZE);
}

TEST(IdtpFrameTest, PackCorrectly) {
    IdtpFrame frame = idtp_frame_create();
    const IdtpHeader header = idtp_header_create();
    idtp_frame_set_header(&frame, &header);

    const uint8_t payload_data[5] = { 1, 2, 3, 4, 5 };
    idtp_frame_set_payload(&frame, payload_data, 5);

    uint8_t buffer[IDTP_PACKET_MAX_SIZE] {};
    idtp_frame_pack(&frame, buffer);

    IdtpHeader header_in_buffer;
    memcpy(&header_in_buffer, buffer, sizeof(IdtpHeader));

    EXPECT_EQ(memcmp(&header_in_buffer, &header, IDTP_HEADER_SIZE), 0);
    EXPECT_EQ(memcmp(&buffer[IDTP_HEADER_SIZE], payload_data, 5), 0);
    EXPECT_EQ(memcmp(&buffer[IDTP_HEADER_SIZE + 5], &IDTP_TRAILER, IDTP_TRAILER_SIZE), 0);
}

TEST(IdtpFrameTest, FromBytesCreatesFrameCorrectly) {
    const uint8_t BYTES[] = {
        // Header.
        0x49, 0x44, 0x54, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12,
        0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // Payload.
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
        // Trailer.
        0x50, 0x54, 0x44, 0x49,
    };

    uint8_t payload[10] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a };

    IdtpFrame frame = idtp_frame_from_bytes(BYTES, sizeof(BYTES));
    uint8_t packed_buffer[sizeof(BYTES)] {};
    idtp_frame_pack(&frame, packed_buffer);

    puts("Frame bytes:");
    for (const auto byte : packed_buffer)
        printf("%02x ", byte);
    putchar('\n');

    puts("Raw bytes:");
    for (const auto byte : BYTES)
        printf("%02x ", byte);
    putchar('\n');

    puts("Frame payload:");
    for (size_t i = 0; i < sizeof(payload); i++)
        printf("%02x ", frame.payload[i]);
    putchar('\n');

    puts("Raw payload:");
    for (const auto byte : payload)
        printf("%02x ", byte);
    putchar('\n');

    EXPECT_EQ(frame.payload_size, sizeof(payload));
    EXPECT_EQ(memcmp(frame.payload, payload, frame.payload_size), 0);
}
