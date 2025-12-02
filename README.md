# IDTP - Inertial Measurement Unit (IMU) Data Transfer Protocol
<hr>

**Inertial Measurement Unit Data Transfer Protocol (IDTP)** - network protocol
used for transferring IMU data. This protocol is suitable for usage in areas
of robotics, unmanned vehicles, wearable devices etc.

There are few implementations in different programming languages:
- `C`
- `Rust`

Rust crate was designed for use on `embedded systems`.
C library need a little modification in order to use it on embedded systems.

<hr>

## Overview

- IDTP frame:

<div style="background-color: white; display: inline-block;">
  <img src="res/idtp_frame.png" alt="IDTP frame image">
</div>

- IDTP header:

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
