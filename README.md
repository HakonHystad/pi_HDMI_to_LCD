# pi_HDMI_to_LCD
I2C driver for the HDMI port on the raspberry pi + an I2C driven 1602 LCD class

The I2C bus on raspberry pi's hdmi port is not reachable through the linux kernel since it is meant for the GPU, it is non the less reachable for the CPU so I made a "userspace" driver for it.
