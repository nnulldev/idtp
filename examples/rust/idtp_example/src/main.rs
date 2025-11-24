// SPDX-License-Identifier: Apache-2.0.
// Copyright (C) 2025-present idtp project and contributors.

//! IDTP usage example.

use idtp::{IDTP_PACKET_MIN_SIZE, IdtpFrame, IdtpHeader, Mode};
use std::{mem, process};

/// Example IDTP payload struct.
#[derive(Debug, Default, Clone, Copy)]
#[repr(C, packed)]
pub struct Payload {
    /// The value of the projection of the acceleration vector
    /// along the X axis (m/s^2).
    pub acc_x: f32,
    /// The value of the projection of the acceleration vector
    /// along the Y axis (m/s^2).
    pub acc_y: f32,
    /// The value of the projection of the acceleration vector
    /// along the Z axis (m/s^2).
    pub acc_z: f32,
    /// Angular velocity along the X axis (rad/s).
    pub gyr_x: f32,
    /// Angular velocity along the Y axis (rad/s).
    pub gyr_y: f32,
    /// Angular velocity along the Z axis (rad/s).
    pub gyr_z: f32,
}

/// Example payload size in bytes.
pub const PAYLOAD_SIZE: usize = size_of::<Payload>();

impl Payload {
    /// Convert payload to bytes.
    /// 
    /// # Returns
    /// - Payload byte array.
    pub fn as_bytes(&self) -> [u8; PAYLOAD_SIZE] {
        unsafe {
            mem::transmute::<Self, [u8; PAYLOAD_SIZE]>(*self)
        }
    }

    /// Convert a byte slice to a `Payload` struct.
    /// 
    /// # Parameters
    /// - `bytes` - given bytes to convert.
    /// 
    /// # Returns
    /// - Payload from bytes.
    pub fn from_bytes(bytes: &[u8; PAYLOAD_SIZE]) -> Self {
        unsafe {
            mem::transmute::<[u8; PAYLOAD_SIZE], Self>(*bytes)
        }
    }
}

/// Calculate checksum for network packet.
/// 
/// # Returns
/// - Checksum for network packet.
fn calculate_checksum() -> u16 {
    // Implement this function suitable for your needs.
    0x1234
}

fn main() {
    // 1) IDTP usage example - creation of raw IDTP network packet.
    // Fill custom payload with IMU sensors data.
    let payload = Payload {
        acc_x: 0.001,
        acc_y: 0.002,
        acc_z: 0.003,
        gyr_x: 0.004,
        gyr_y: 0.005,
        gyr_z: 0.006,
    };

    let payload_bytes = payload.as_bytes();

    // Fill IDTP header.
    // Prefer creating IdtpHeader instance using new() method because there
    // will be no need for you to set preamble and version manually.
    let mut header = IdtpHeader::new();

    // Handling Mode::Safety is almost the same,
    // but header.crc field should be calculated.
    header.mode = Mode::Normal;
    header.device_id = 0xABCD;
    header.checksum = calculate_checksum();
    header.timestamp = 0;
    header.sequence = 0;
    header.crc = 0;
    header.payload_size = payload_bytes.len() as u32;
    header.payload_type = 0;

    println!("Header: {header:#X?}");
    println!("Payload bytes: {payload_bytes:X?}");

    // Create IDTP packet manager instance.
    let mut idtp = IdtpFrame::new();

    idtp.set_header(&header);
    idtp.set_payload(&payload_bytes);

    // Get raw network packet bytes.
    const PACKET_SIZE: usize = IDTP_PACKET_MIN_SIZE + size_of::<Payload>();
    let mut raw_packet = [0u8; PACKET_SIZE];

    if let Err(msg) = idtp.pack(&mut raw_packet) {
        eprintln!("Error occured during packing raw packet: {msg}");
        process::exit(1);
    }
    else {
        println!("Raw IDTP packet: {raw_packet:X?}");
        // Handle this raw packet...
    }

    // 2) IDTP usage example - parsing IDTP from raw network packet.
    let idtp    = IdtpFrame::from(&raw_packet[..]);
    let header  = idtp.header();
    let payload = idtp.payload();

    println!("Header: {header:#X?}");
    println!("Payload: {payload:X?}");

    let mut buffer = [0u8; PAYLOAD_SIZE];
    buffer.copy_from_slice(payload);

    let payload = Payload::from_bytes(&buffer);
    println!("Payload: {payload:#X?}");

    // Handle this IDTP frame...
}
