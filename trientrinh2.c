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

// cau hinh led tai chan PA5
void GPIO_Config_LED()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// cau hinh nut nhan tai chan PA6
void GPIO_Config_Button()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // keo len noi, nhan xuong se ve 0
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main(void)
{
    GPIO_Config_LED();
    GPIO_Config_Button();

    uint8_t ledState = 0; // bien luu trang thai led

    while (1)
    {
        // kiem tra nut nhan tai PA6
        if ((GPIOA->IDR & GPIO_Pin_6) == 0) // muc 0 = nut nhan
        {
            delay_ms(20); // chong doi phim
            if ((GPIOA->IDR & GPIO_Pin_6) == 0) // neu van giu
            {
                ledState = !ledState; // dao trang thai LED
                if (ledState)
                    GPIO_SetBits(GPIOA, GPIO_Pin_5);
                else
                    GPIO_ResetBits(GPIOA, GPIO_Pin_5);

                // doi den khi nha nut roi moi cho bam tiep
                while ((GPIOA->IDR & GPIO_Pin_6) == 0);
            }
        }
    }
}