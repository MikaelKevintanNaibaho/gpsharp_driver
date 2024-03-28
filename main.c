#include "gpsharp.h"

int main(void) {
    int spi_fd;

    // Ensure SPI is initialized before attempting communication
    spi_fd = spi_init(SPI_DEVICE);
    if (spi_fd < 0) {
        perror("Failed to initialize SPI communication");
        return 1;
    }

    while (1) {
        // Read ADC from channel 0
        uint16_t adc_value = read_adc_gpsharp(0, spi_fd);

        // Calculate distance
        double distance = adc_to_distance(adc_value);

        // Print ADC value and distance
        printf("ADC Value: %d, Distance: %.2f cm\n", adc_value, distance);
    }

    spi_close(spi_fd);

    return 0;
}
