#include "sdk_project_config.h"
#include <stdio.h>

char txBuff[64];
int len;
uint16_t adcValue,voltage;

int main(void)
{
    CLOCK_DRV_Init(&clockMan1_InitConfig0);
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    LPUART_DRV_Init(INST_LPUART_1,&lpUartState0,&lpuart_0_InitConfig0);
    ADC_Init(&adc_pal_1_instance, &adc_pal_1_config);
    ADC_StartGroupConversion(&adc_pal_1_instance, 0u);

    while (1)
    {
        adcValue = adc_pal_1_results0[0];
        voltage = (adcValue * 3300) / 4095;
        len = sprintf(txBuff,"ADC = %4d   Voltage = %4d mV\r\n",adcValue,voltage);
        LPUART_DRV_SendData(INST_LPUART_1,(uint8_t *)txBuff,len);
        OSIF_TimeDelay(500);
    }
}
