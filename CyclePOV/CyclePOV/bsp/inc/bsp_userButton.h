#ifndef BSP_USERBUTTON_H_
#define BSP_USERBUTTON_H_

void bsp_userButton_init();
void bsp_userButtonIRQ() __attribute__((weak));

#endif /* BSP_USERBUTTON_H_ */
