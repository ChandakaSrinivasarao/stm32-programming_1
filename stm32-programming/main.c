#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

void vTaskFunction(void *pvParameters) {
    while(1) {
        printf("Hello-FreeRTOS");
    }
}

int main(void) {
    // Hardware initialization
    xTaskCreate(vTaskFunction, "Task", 1000, NULL, 1, NULL);
    vTaskStartScheduler();  // This should never return
    while(1);
}

