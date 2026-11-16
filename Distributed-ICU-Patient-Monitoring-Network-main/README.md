# Distributed ICU Patient Monitoring Network

## Project Overview

The **Distributed ICU Patient Monitoring Network** is an embedded-systems project designed to demonstrate how patient vital-sign information can be acquired, processed, and communicated between a patient-side monitoring unit and a central monitoring unit.

The project is organized around a transmitter (TX) and receiver (RX) architecture. The patient-side unit interfaces with monitoring hardware and sends the acquired information through a communication link. The receiving unit collects the transmitted information and can display or forward it for monitoring.

> **Important:** This README documents the architecture and source files visible in this repository. Confirm the exact board revision, sensor connections, CAN bit rate, UART baud rate, measured parameters, and storage implementation against the final hardware and source code before treating them as fixed specifications.

## Objectives

- Demonstrate embedded patient-vital monitoring.
- Interface a MAX30102 pulse-oximetry sensor using I2C.
- Implement SpO2-related processing in software.
- Separate patient-side transmission and receiving-side processing.
- Use CAN communication drivers for data exchange.
- Provide UART support for serial debugging or output.
- Keep peripheral drivers and application logic in separate source files.

## System Architecture

```text
      PATIENT-SIDE UNIT (TX)
  +----------------------------+
  | MAX30102 sensor             |
  | I2C interface                |
  | SpO2 processing              |
  | ADC / other input interfaces |
  | CAN transmitter              |
  +--------------+-------------+
                 |
                 | CAN bus
                 v
      CENTRAL UNIT (RX)
  +----------------------------+
  | CAN receiver                |
  | Receive and interpret data  |
  | UART serial output          |
  | Monitoring / data display   |
  +----------------------------+
```

The diagram is a functional overview. Actual wiring, additional sensors, and the exact division of processing between TX and RX should follow the implemented firmware.

## Hardware and Interfaces

| Component / interface | Purpose |
|---|---|
| ARM7 / LPC21xx-family target | Embedded controller indicated by the source headers; verify the exact part number used on the board |
| MAX30102 | Optical pulse-oximetry sensor interface |
| I2C | Communication between the controller and MAX30102 |
| CAN | Communication between transmitter and receiver units |
| UART | Serial output and debugging |
| ADC | Analog input acquisition where used by the application |
| EEPROM / non-volatile storage | Include only if the final firmware actually writes and reads patient records |

### MAX30102

The MAX30102 is an optical sensor module commonly used to acquire red and infrared photoplethysmography (PPG) samples. The project includes sensor initialization and SpO2-related source files.

SpO2 and heart-rate values depend on the sensor configuration, signal quality, calibration, and processing algorithm. This project is an educational embedded-systems demonstration and is **not a certified medical device**. Do not use it for diagnosis or clinical decisions.

## Software Modules

The repository currently contains the following source files:

| File | Responsibility (based on filename and module role) |
|---|---|
| `main_main.c.c` | Main application entry point; verify whether this is the TX application |
| `rx_main.c` | Receiver-side application entry point |
| `can_driver.c` | CAN controller initialization and transmission-side driver functions |
| `can_rec_driver.c` | CAN receive-side driver functions |
| `i2c_driver (6).c` | I2C communication driver |
| `max_init.c.c` | MAX30102 initialization/configuration |
| `max30102.h` | MAX30102 declarations and definitions |
| `spo2.c` | SpO2-related processing |
| `spo2.h` | SpO2 declarations |
| `adc_driver (1).c` | ADC peripheral driver |
| `uart_driver.c` | UART driver |
| `uart0_driver.c` | UART0-specific driver support |
| `header.h` | Common declarations and project definitions |
| `header (6).h` | Additional header file; compare with `header.h` and consider consolidating duplicate/variant headers |

File responsibilities should be checked against the function definitions before changing or documenting implementation details.

## Repository Structure

```text
Distributed-ICU-Patient-Monitoring-Network/
├── adc_driver (1).c
├── can_driver.c
├── can_rec_driver.c
├── header (6).h
├── header.h
├── i2c_driver (6).c
├── main_main.c.c
├── max30102.h
├── max_init.c.c
├── rx_main.c
├── spo2.c
├── spo2.h
├── uart0_driver.c
└── uart_driver.c
```

## Development Environment

The source code uses C and ARM/LPC21xx-style peripheral register headers. The exact compiler, IDE project configuration, target part number, clock settings, and programmer depend on the development board and project setup.

Typical development requirements:

- ARM7/LPC21xx-compatible development board.
- Toolchain/IDE configured for the exact MCU (for example, the toolchain used in your lab).
- CAN transceiver hardware for each CAN node.
- MAX30102 module and appropriate I2C wiring.
- USB-to-UART adapter or serial terminal, if UART output is used.
- Suitable power supply and common ground between connected modules.

## Build and Run

1. Open the project in the IDE/toolchain configured for your exact LPC21xx target.
2. Select the correct target MCU and clock configuration.
3. Add the required source and header files to the transmitter build.
4. Build and resolve any missing-header, duplicate-definition, or linker errors.
5. Program the transmitter board.
6. Build the receiver application separately using `rx_main.c` and the receiver-side drivers.
7. Program the receiver board.
8. Connect the CAN transceivers and CAN bus with the correct termination.
9. Connect the MAX30102 to the configured I2C pins.
10. Open a serial terminal with the UART settings configured in the firmware.
11. Power the units and verify sensor acquisition, CAN transmission/reception, and serial output.

**Do not assume default pin numbers or baud rates.** Read the pin-multiplexing and UART/CAN initialization code and match the physical wiring to those settings.

## Testing Checklist

- [ ] MCU starts correctly and executes the application.
- [ ] I2C bus is initialized successfully.
- [ ] MAX30102 responds to the expected device address.
- [ ] Sensor samples are acquired consistently.
- [ ] SpO2/heart-rate processing receives valid samples.
- [ ] CAN transmitter sends the expected frame identifier and payload.
- [ ] Receiver accepts the expected CAN frames.
- [ ] Received values are decoded correctly.
- [ ] UART output is readable and matches the received data.
- [ ] Invalid, missing, or disconnected sensor data is handled safely.
- [ ] If persistent storage is implemented, write/read and power-cycle tests pass.

## Troubleshooting

**MAX30102 is not detected**
- Check sensor power and ground.
- Verify SDA/SCL wiring and pin multiplexing.
- Confirm I2C clock configuration and sensor address.
- Check pull-up resistors and I2C timing.

**No CAN data is received**
- Check CAN transceiver power and wiring.
- Ensure both nodes use matching CAN bit rates.
- Verify CANH/CANL polarity and common ground.
- Check bus termination and acceptance filters.
- Confirm the transmitter frame ID matches the receiver configuration.

**UART output is unreadable**
- Check TX/RX wiring and common ground.
- Confirm the terminal baud rate, data bits, parity, and stop bits match firmware.
- Verify the UART peripheral clock and pin selection.

**Build errors**
- Confirm the selected MCU header matches the target.
- Check that every required source file is included exactly once.
- Resolve duplicate or inconsistent header files.
- Check function prototypes and matching declarations/definitions.

## Limitations and Safety

- This is an academic/educational embedded project, not a medical-grade monitoring system.
- Sensor-derived values can be inaccurate due to motion, poor contact, ambient light, and other conditions.
- No clinical accuracy, alarm reliability, or regulatory certification is claimed.
- Do not connect this prototype to real patient-care workflows or use its output to make treatment decisions.

## Future Enhancements

- Add robust packet framing, validation, and error handling.
- Add patient/device identifiers and timestamps to transmitted records.
- Add communication timeout and sensor-disconnection detection.
- Add configurable alert thresholds after appropriate validation.
- Add non-volatile patient-record storage only after confirming the memory design and data-integrity requirements.
- Add a central dashboard and secure data logging.
- Document exact wiring diagrams, pin assignments, CAN IDs, and test results.

## Contributors

Add the verified project contributors and their roles here.

- Project / Group: **Group 11**
- Contributor: **Vignesh Kumar S.P. (V25BE10V6)**
- Other team members: **[Add the remaining verified team members and IDs]**
- Guide / Institution: **[Enter guide and institution, if applicable]**

## License

No license is specified in this repository at the time this README was prepared. Add a `LICENSE` file if you intend to publish the project with reuse permissions.

## Acknowledgements

This project was developed as an embedded-systems learning project involving sensor interfacing, peripheral drivers, data processing, and communication between embedded nodes.
