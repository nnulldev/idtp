# IDTP - Inertial Measurement Unit (IMU) Data Transfer Protocol

## Overview
**Inertial Measurement Unit Data Transfer Protocol (IDTP)** - lightweight protocol designed for high-performance and reliable IMU data transmission between microcontrollers and host systems. It is tailored for autonomous navigation,  wearable devices & robotics where low latency, and data integrity are paramount.

There are few implementations in different programming languages:

- `C` -  Portable (only `stdint.h` & `string.h` headers are used), zero-allocation C library. Easy to integrate into any MCU vendor HAL.
- `Rust` - Fully `no_std` compatible, zero-allocation crate without external dependencies but Rust `core` library. Designed specifically for memory-safe embedded environments.

## Core features

- `Dual-layer error detection`: supports `Normal` (checksum-based) and `Safety` (checksum + CRC-32) modes. This allows for a compromise between CPU overhead and maximum integrity in noisy environments.

- `Time-critical accuracy`: built-in `timestamp` fields ensure that sensor fusion and trajectory estimation algorithms receive precise measurement times without transmission latency issues.

- `Cross-platform design`: optimized for communication between systems written in C and Rust.

<hr>

IDTP frame:

<div style="background-color: white; display: inline-block;">
  <img src="res/idtp_frame.png" alt="IDTP frame image">
</div>

IDTP header:

<div style="background-color: white; display: inline-block;">
  <img src="res/idtp_header.png" alt="IDTP header image">
</div>

## License

Copyright (C) 2025-present idtp project and contributors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

## Documentation
For complete technical implementation of protocol
read [specification](docs/SPECIFICATION.md).