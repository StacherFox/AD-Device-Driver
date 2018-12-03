#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    FILE* fp ;
    char buffer[15];
    int raw1, raw2;
    float scale, voltage1, voltage2;

    fp = fopen("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", "r");
    if (!fp) { printf("Could not open source file\n"); exit(-1); }
    fscanf(fp, "%s", buffer);
    printf("Raw Voltage 1: %s\n", buffer);
    raw1 = atoi(buffer);
    fclose(fp);

    fp = fopen("/sys/bus/iio/devices/iio:device0/in_voltage1_raw", "r");
    if (!fp) { printf("Could not open source file\n"); exit(-1); }
    fscanf(fp, "%s", buffer);
    printf("Raw Voltage 2: %s\n", buffer);
    raw2 = atoi(buffer);
    fclose(fp);

    fp = fopen("/sys/bus/iio/devices/iio:device0/in_voltage0_scale", "r");
    if (!fp) { printf("Could not open source file\n"); exit(-1); }
    fscanf(fp, "%s", buffer);
    printf("Scale: %s\n", buffer);
    scale = atof(buffer);
    fclose(fp);

    voltage1 = raw1 * scale;
    voltage2 = raw2 * scale;

    sprintf(buffer, "%.1f", voltage1);
    printf("Voltage 1: %s mV\n", buffer);
    sprintf(buffer, "%.1f", voltage2);
    printf("Voltage 2: %s mV\n", buffer);
}