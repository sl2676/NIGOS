# NIGOS: Kernel for AArch64



## Overview

**NIGOS** (Kernel for AArch64) is a kernel developed for AArch64 (ARM64) architectures. It encompasses core operating system components such as task management, memory handling, and interrupt processing. 

## Key Features

- **AArch64 Compatibility**: Supports 64-bit ARM architectures, ensuring functionality on modern ARM-based devices.
- **Task Management**: Implements basic scheduling algorithms to manage CPU utilization and process responsiveness.
- **Memory Management**: Provides mechanisms for memory allocation and protection to maintain system stability.
- **Interrupt Handling**: Manages hardware and software interrupts to ensure reliable and efficient operation.



## Technical Specifications

- **Language**: C, Assembly (ARM64)
- **Build System**: Makefile
- **Compiler**: GNU Compiler Collection (GCC) for AArch64
- **Linker**: GNU Linker (LD)
- **Emulation**: QEMU for testing and development
- **Version Control**: Git


## Getting Started

### Requirements

- **Hardware**: A system with an AArch64 (ARM64) bit architecture.
- **Software**:
  - GNU Compiler Collection (GCC) for AArch64
  - GNU Make
  - QEMU for system emulation
  - Git


### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/NIGOS.git
   cd NIGOS
   ```
2. **Install dependencies**
   - Debian Systems
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential gcc-aarch64-linux-gnu qemu-system-aarch64 git
   ```
   - MacOS
   ```bash
   brew tap osx-cross/arm
   brew install aarch64-elf-gcc qemu
   ```

## Building the Kernel

1. **Clean Previous Builds**
   ```bash
   make clean
   ```
2. **Compile the Kernel**
   ```bash
   make
   ```
4. **Run the Kernel in QEMU**
   ```bash
   make run 
   ```
## Instruction Tracing Output
```asm
IN: 
0x40000000:  580000c0  ldr      x0, #0x40000018
0x40000004:  aa1f03e1  mov      x1, xzr
0x40000008:  aa1f03e2  mov      x2, xzr
0x4000000c:  aa1f03e3  mov      x3, xzr
0x40000010:  58000084  ldr      x4, #0x40000020
0x40000014:  d61f0080  br       x4

Trace 0: 0x1082f0180 [00004000/0000000040000000/00000521/ff020000] 
 PC=0000000040000000 X00=0000000000000000 X01=0000000000000000
X02=0000000000000000 X03=0000000000000000 X04=0000000000000000
X05=0000000000000000 X06=0000000000000000 X07=0000000000000000
X08=0000000000000000 X09=0000000000000000 X10=0000000000000000
X11=0000000000000000 X12=0000000000000000 X13=0000000000000000
X14=0000000000000000 X15=0000000000000000 X16=0000000000000000
X17=0000000000000000 X18=0000000000000000 X19=0000000000000000
X20=0000000000000000 X21=0000000000000000 X22=0000000000000000
X23=0000000000000000 X24=0000000000000000 X25=0000000000000000
X26=0000000000000000 X27=0000000000000000 X28=0000000000000000
X29=0000000000000000 X30=0000000000000000  SP=0000000000000000
PSTATE=400003c5 -Z-- EL1h
----------------
IN: 
0x40080000:  58000100  ldr      x0, #0x40080020
0x40080004:  9100001f  mov      sp, x0
0x40080008:  58000100  ldr      x0, #0x40080028
0x4008000c:  d518c000  msr      vbar_el1, x0

Trace 0: 0x1082f0380 [00004000/0000000040080000/00000521/ff020000] 
 PC=0000000040080000 X00=0000000044000000 X01=0000000000000000
X02=0000000000000000 X03=0000000000000000 X04=0000000040080000
X05=0000000000000000 X06=0000000000000000 X07=0000000000000000
X08=0000000000000000 X09=0000000000000000 X10=0000000000000000
X11=0000000000000000 X12=0000000000000000 X13=0000000000000000
X14=0000000000000000 X15=0000000000000000 X16=0000000000000000
X17=0000000000000000 X18=0000000000000000 X19=0000000000000000
X20=0000000000000000 X21=0000000000000000 X22=0000000000000000
X23=0000000000000000 X24=0000000000000000 X25=0000000000000000
X26=0000000000000000 X27=0000000000000000 X28=0000000000000000
X29=0000000000000000 X30=0000000000000000  SP=0000000000000000
PSTATE=400003c5 -Z-- EL1h
----------------
IN: 
0x40080010:  94000070  bl       #0x400801d0

Trace 0: 0x1082f0600 [00004000/0000000040080010/00000521/ff020000] 
 PC=0000000040080010 X00=0000000040000030 X01=0000000000000000
X02=0000000000000000 X03=0000000000000000 X04=0000000040080000
X05=0000000000000000 X06=0000000000000000 X07=0000000000000000
X08=0000000000000000 X09=0000000000000000 X10=0000000000000000
X11=0000000000000000 X12=0000000000000000 X13=0000000000000000
X14=0000000000000000 X15=0000000000000000 X16=0000000000000000
X17=0000000000000000 X18=0000000000000000 X19=0000000000000000
X20=0000000000000000 X21=0000000000000000 X22=0000000000000000
X23=0000000000000000 X24=0000000000000000 X25=0000000000000000
X26=0000000000000000 X27=0000000000000000 X28=0000000000000000
X29=0000000000000000 X30=0000000000000000  SP=0000000040125390
PSTATE=400003c5 -Z-- EL1h
----------------
IN: 
0x400801d0:  a9bf7bfd  stp      x29, x30, [sp, #-0x10]!
0x400801d4:  910003fd  mov      x29, sp
0x400801d8:  94000022  bl       #0x40080260

Linking TBs 0x1082f0600 index 0 -> 0x1082f0780
Trace 0: 0x1082f0780 [00004000/00000000400801d0/00000521/ff020000] 
 PC=00000000400801d0 X00=0000000040000030 X01=0000000000000000
X02=0000000000000000 X03=0000000000000000 X04=0000000040080000
X05=0000000000000000 X06=0000000000000000 X07=0000000000000000
X08=0000000000000000 X09=0000000000000000 X10=0000000000000000
X11=0000000000000000 X12=0000000000000000 X13=0000000000000000
X14=0000000000000000 X15=0000000000000000 X16=0000000000000000
X17=0000000000000000 X18=0000000000000000 X19=0000000000000000
X20=0000000000000000 X21=0000000000000000 X22=0000000000000000
X23=0000000000000000 X24=0000000000000000 X25=0000000000000000
X26=0000000000000000 X27=0000000000000000 X28=0000000000000000
X29=0000000000000000 X30=0000000040080014  SP=0000000040125390
PSTATE=400003c5 -Z-- EL1h
----------------
IN: 
0x40080260:  d65f03c0  ret      

Linking TBs 0x1082f0780 index 0 -> 0x1082f0980
Trace 0: 0x1082f0980 [00004000/0000000040080260/00000521/ff020000] 
 PC=0000000040080260 X00=0000000040000030 X01=0000000000000000
X02=0000000000000000 X03=0000000000000000 X04=0000000040080000
X05=0000000000000000 X06=0000000000000000 X07=0000000000000000
X08=0000000000000000 X09=0000000000000000 X10=0000000000000000
X11=0000000000000000 X12=0000000000000000 X13=0000000000000000
X14=0000000000000000 X15=0000000000000000 X16=0000000000000000
X17=0000000000000000 X18=0000000000000000 X19=0000000000000000
X20=0000000000000000 X21=0000000000000000 X22=0000000000000000
X23=0000000000000000 X24=0000000000000000 X25=0000000000000000
X26=0000000000000000 X27=0000000000000000 X28=0000000000000000
X29=0000000040125380 X30=00000000400801dc  SP=0000000040125380
PSTATE=400003c5 -Z-- EL1h
----------------
IN: 
0x400801dc:  90000000  adrp     x0, #0x40080000
0x400801e0:  913a6000  add      x0, x0, #0xe98
0x400801e4:  94000028  bl       #0x40080284
```
### Kernel Log Messages
```yaml
Trace 0:

Kernel is running!

Adding idle task...
Initializing task...
Task added successfully!

Adding Task 1...
Initializing task...
Task added successfully!

Adding Task 2...
Initializing task...
Task added successfully!

Starting Scheduler...

Task States:

Task 0
state: 0

Task 1
state: 0

Task 2
state: 0

Switching from Task 1 to Task 0

Restoring SP for Task 0: 1075327656

Executing Task 0

Idle task running.

Task States:
Task 0 state: 1
Task 1 state: 0
Task 2 state: 0
Switching from Task 0 to Task 1
```
