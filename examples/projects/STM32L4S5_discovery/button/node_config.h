/******************************************************************************
 * @file node_config.h
 * @brief This file allow you to use standard preprocessor definitions to
 *        configure your project, Luos and Luos HAL libraries
 *
 *   # Introduction
 *     This file is for the luos user. You may here configure your project and
 *     define your custom Luos service and custom Luos command for your product
 *
 *     Luos libraries offer a minimal standard configuration to optimize
 *     memory usage. In some case you have to modify standard value to fit
 *     with your need concerning among of data transiting through the network
 *     or network speed for example
 *
 *     Luos libraries can be use with a lot a MCU family. Luos compagny give you
 *     a default configuration, for specific MCU family, in robus_hal_config.h.
 *     This configuration can be modify here to fit with you design by
 *     preprocessor definitions of MCU Hardware needs
 *
 *   # Usage
 *      This file should be place a the root folder of your project and include
 *      where build flag preprocessor definitions are define in your IDE
 *      -include node_config.h
 *
 * @author Luos
 * @version 0.0.0
 ******************************************************************************/
#ifndef _NODE_CONFIG_H_
#define _NODE_CONFIG_H_

/*******************************************************************************
 * PROJECT DEFINITION
 *******************************************************************************/

/*******************************************************************************
 * LUOS LIBRARY DEFINITION
 *******************************************************************************
 *    Define                | Default Value              | Description
 *    :---------------------|------------------------------------------------------
 *    MAX_SERVICE_NUMBER    |              5             | Service number in the node
 *    MSG_BUFFER_SIZE       | 3*SIZE_MSG_MAX (405 Bytes) | Size in byte of the Luos buffer TX and RX
 *    MAX_MSG_NB            |   2*MAX_SERVICE_NUMBER     | Message number in Luos buffer
 *    MAX_RTB_ENTRY         |             40             | Max entries in the routing table
 *    NBR_PORT              |              2             | PTP Branch number Max 8
 *    NBR_RETRY             |             10             | Send Retry number in case of NACK or collision
 ******************************************************************************/

#define MAX_SERVICE_NUMBER 1
#define MAX_MSG_NB         5

/*******************************************************************************
 * LUOS HAL LIBRARY DEFINITION
*******************************************************************************
 *    Define                  | Description
 *    :-----------------------|-----------------------------------------------
 *    MCUFREQ                 | Put your the MCU frequency (value in Hz)
 *    TIMERDIV                | Timer divider clock (see your clock configuration)
 *    USE_CRC_HW              | define to 0 if there is no Module CRC in your MCU
 *    USE_TX_IT               | define to 1 to not use DMA transfert for Luos Tx
 *
 *    PORT_CLOCK_ENABLE       | Enable clock for port
 *    PTPx                    | A,B,C,D etc. PTP Branch Pin/Port/IRQ
 *    TX_LOCK_DETECT          | Disable by default use if not busy flag in USART Pin/Port/IRQ
 *    RX_EN                   | Rx enable for driver RS485 always on Pin/Port
 *    TX_EN                   | Tx enable for driver RS485 Pin/Port
 *    COM_TX                  | Tx USART Com Pin/Port/Alternate
 *    COM_RX                  | Rx USART Com Pin/Port/Alternate
 *    PINOUT_IRQHANDLER       | Callback function for Pin IRQ handler

 *    LUOS_COM_CLOCK_ENABLE   | Enable clock for USART
 *    LUOS_COM                | USART number
 *    LUOS_COM_IRQ            | USART IRQ number
 *    LUOS_COM_IRQHANDLER     | Callback function for USART IRQ handler

 *    LUOS_DMA_CLOCK_ENABLE   | Enable clock for DMA
 *    LUOS_DMA                | DMA number
 *    LUOS_DMA_CHANNEL        | DMA channel (depending on MCU DMA may need special config)

 *    LUOS_TIMER_CLOCK_ENABLE | Enable clock for Timer
 *    LUOS_TIMER              | Timer number
 *    LUOS_TIMER_IRQ          | Timer IRQ number
 *    LUOS_TIMER_IRQHANDLER   | Callback function for Timer IRQ handler
******************************************************************************/
#define MCUFREQ  120000000 // MCU frequence
#define TIMERDIV 1         // clock divider for timer clock chosen

/*******************************************************************************
 * PINOUT CONFIG
 ******************************************************************************/

#define PORT_CLOCK_ENABLE()           \
    do                                \
    {                                 \
        __HAL_RCC_GPIOA_CLK_ENABLE(); \
        __HAL_RCC_GPIOB_CLK_ENABLE(); \
        __HAL_RCC_GPIOD_CLK_ENABLE(); \
    } while (0U)

// PTP pin definition
#define PTPA_PIN  GPIO_PIN_14
#define PTPA_PORT GPIOD
#define PTPA_IRQ  EXTI15_10_IRQn

#define PTPB_PIN  GPIO_PIN_0
#define PTPB_PORT GPIOB
#define PTPB_IRQ  EXTI0_IRQn

#define RX_EN_PIN  GPIO_PIN_4
#define RX_EN_PORT GPIOB

#define TX_EN_PIN  GPIO_PIN_3
#define TX_EN_PORT GPIOA

#define COM_TX_PIN  GPIO_PIN_0
#define COM_TX_PORT GPIOA
#define COM_TX_AF   GPIO_AF8_UART4

#define COM_RX_PIN  GPIO_PIN_1
#define COM_RX_PORT GPIOA
#define COM_RX_AF   GPIO_AF8_UART4

/*******************************************************************************
 * COM CONFIG
 ******************************************************************************/

#define LUOS_COM_CLOCK_ENABLE() __HAL_RCC_UART4_CLK_ENABLE()
#define LUOS_COM                UART4
#define LUOS_COM_IRQ            UART4_IRQn
#define LUOS_COM_IRQHANDLER()   UART4_IRQHandler()
/*******************************************************************************
 * DMA CONFIG
 ******************************************************************************/
#define LUOS_DMA_CLOCK_ENABLE()         \
    do                                  \
    {                                   \
        __HAL_RCC_DMA1_CLK_ENABLE();    \
        __HAL_RCC_DMAMUX1_CLK_ENABLE(); \
    } while (0U)

#define LUOS_DMA         DMA1
#define LUOS_DMA_CHANNEL LL_DMA_CHANNEL_1
#define LUOS_DMA_REQUEST LL_DMAMUX_REQ_UART4_TX
/*******************************************************************************
 * COM TIMEOUT CONFIG
 ******************************************************************************/

/*******************************************************************************
 * FLASH CONFIGURATION FOR APP WITH BOOTLOADER
 ********************************************************************************
 *    Define                | Default Value              | Description
 *    :---------------------|------------------------------------------------------
 *    BOOT_START_ADDRESS    | FLASH_BASE = 0x8000000     | Start address of Bootloader in flash
 *    SHARED_MEMORY_ADDRESS | 0x0800C000                 | Start address of shared memory to save boot flag
 *    APP_START_ADDRESS     | 0x0800C800                 | Start address of application with bootloader
 *    APP_END_ADDRESS       | FLASH_END                  | End address of application with bootloader
 ******************************************************************************/
#define APP_START_ADDRESS (uint32_t)0x0800D000

#endif /* _NODE_CONFIG_H_ */
