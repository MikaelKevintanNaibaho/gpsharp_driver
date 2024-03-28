#include "gpsharp.h"

int spi_open(const char *device)
{
    int spi_file_decriptor;
    // open spi device
    if ((spi_file_decriptor = open(device, O_RDWR)) < 0) {
        perror("failed to open SPI device\n");
        return -1;;
    }

    return spi_file_decriptor;
}

int spi_close(int spi_file_decriptor)
{
    if (spi_file_decriptor >= 0) {
        close(spi_file_decriptor);
    }
    return 0;
}
int spi_init(const char *device)
{
    int spi_fd = spi_open(device);
    if (spi_fd < 0) {
        perror("failed to open the device\n");
        exit(EXIT_FAILURE);
    }

    // set SPI mode
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, SPI_MODE) < 0) {
        perror("failed to set spi mode\n");
        exit(EXIT_FAILURE);
    }

    // set bits per word
    if (ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, SPI_BITS) < 0) {
        perror("failed to set bits per word\n");
        exit(EXIT_FAILURE);
    }

    // set clock speed
    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, SPI_SPEED) < 0) {
        perror("failed to set SPI clock speed\n");
        exit(EXIT_FAILURE);
    }

    return spi_fd;
}

uint16_t read_adc_gpsharp(int channel, int spi_fd)
{
    uint8_t tx_buf[3] = { 1, (8 + channel) << 4, 0 };
    uint8_t rx_buf[3];
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx_buf,
        .rx_buf = (unsigned long)rx_buf,
        .len = 3,
        .delay_usecs = 0,
        .speed_hz = SPI_SPEED,
        .bits_per_word = SPI_BITS,
    };

    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr) < 0) {
        perror("SPI tranfer failed..,\n");
        exit(EXIT_FAILURE);
    }

    // extract data ADC yang diterima
    return ((rx_buf[1] & 3) << 8) | rx_buf[2];
}

// gunakan rumus dari datasheet
double adc_to_distance(uint16_t adc_value)
{
    double voltage = (double)adc_value * VREF / 1023.0; // convert ADV ke voltage
    return 29.988 * pow(voltage, -1.173); // hitung distance
}
