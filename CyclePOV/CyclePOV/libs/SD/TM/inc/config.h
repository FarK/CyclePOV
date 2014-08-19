#ifndef CONFIG_H_
#define CONFIG_H_

#define FATFS_USE_DETECT_PIN		0
#define FATFS_SDIO_4BIT				1

#define FATFS_USE_WRITEPROTECT_PIN	0

#define FATFS_USE_DETECT_PIN_RCC	RCC_AHB1Periph_GPIOC
#define FATFS_USE_DETECT_PIN_PORT	GPIOC
#define FATFS_USE_DETECT_PIN_PIN	GPIO_Pin_6

// IRQ PRIORITIES
/* If the priority is above configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY,
 * the IRQ can't be preempted by the kernel interruptions.
 * On the other hand, if the priority is lower,
 * the kernel interruptions may preempt it.
 * (See FreeRTOSConfig.h)
 */
#define SDIO_IRQ_PRIORITY		0xA
#define SDIO_DMA_IRQ_PRIORITY	0xB

/* Set higher velocity for transmissions
 * (I've tried with 24MHz, but it didn't work)
 *
 * SDIO_CK = SDIOCLK / (SDIO_TRANSFER_CLK_DIV + 2)
 * SDIOCLK = 48MHz (fixed)
 */
#define SDIO_TRANSFER_CLK_DIV         ((uint8_t)1)

#endif /* CONFIG_H_ */
