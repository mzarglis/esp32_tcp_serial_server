# esp32_tcp_serial_server
This sketch reads GPS NMEA messages from hardware serial UART2 on a esp32-wroom board and writes them to tcp client on port 23

Can point [ublox u-center](https://www.u-blox.com/en/product/u-center) to the ip address of esp32 on port 23 and it will parse
messages and give a graphical display, or just telnet to it to see the raw NMEA messages output from the gps module.
