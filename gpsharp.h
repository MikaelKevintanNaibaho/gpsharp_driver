#ifndef GPSHARP_H
#define GPSHARP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <math.h>

#define SPI_DEVICE "/dev/spidev0.0" // SPI device file
#define SPI_MODE SPI_MODE_0
#define SPI_BITS 8
#define SPI_SPEED 1000000 // clock speed SPI 1MHz
#define VREF 5

int spi_open(const char *device);
int spi_close(int file);
int spi_init(const char *device);

uint16_t read_adc_gpsharp(int channel, int spi_fd);
double adc_to_distance(uint16_t adc_value);

#endif // GHSHARP_H
