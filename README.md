# Embedded Serial Library

This project is a C Library that handles serial buffered communication in C. This Library can be ported to 
receive data from serial interfaces commonly used nowadays, such as: UART, USB VCP, SPI, CAN, I2C.

## How does it work?

There is a FIFO input that stores bytes received from the serial interface. When the reception of a complete packet is identified, the library calls the user's callback responsible for processing the command.
There is a FIFO output that holds commands that must be transmitted throught the serial interface. Users 
must implement the sendData callback responsible to send data throught the serial interface. It's also user responsability to call the callback every time the interface is ready to send more data.
