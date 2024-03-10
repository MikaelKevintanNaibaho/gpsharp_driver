#include "gpsharp.h"

int main (void)
{
    int spi_fd;
    uint16_t adc_value;
    double distance;

    //init
    spi_fd = spi_init(SPI_DEVICE);


    while (1){
        //read adc from channel 0
        adc_value = read_adc_gpsharp(0, spi_fd);

        //calcaulate ditance
        distance = adc_to_distance(adc_value);

        //Print ADC value and distance
        printf("ADC Value: %d, Distance: %.2f cm\n", adc_value, distance);
    }

    spi_close(spi_fd);

    return 0;
    

}