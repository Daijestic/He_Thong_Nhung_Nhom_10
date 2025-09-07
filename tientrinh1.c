#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

// ham tao tre bang vong lap
void delay_ms(int time)
{
    for (int i = 0; i < time; i++)
    {
        for (int j = 0; j < 0x2AFF; j++);
    }
}

// cau hinh led tai chan PA5 va PA6
void GPIO_Config_LED()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main(void)
{
    GPIO_Config_LED();

    while (1)
    {
        // bat PA5, tat PA6
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);
        delay_ms(1000);

        // tat PA5, bat PA6
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        GPIO_SetBits(GPIOA, GPIO_Pin_6);
        delay_ms(1000);
    }
}
