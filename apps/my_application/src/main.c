#include <zephyr/drivers/uart.h>
#include <string.h>

/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_NODELABEL(usart1)

// Use alias if you want your code to be portable between boards
// #define UART_DEVICE_NODE DT_ALIAS(test_uart)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

int main(void)
{
    if (!device_is_ready(uart_dev)) {
        return -ENODEV;
    }

    // Disable both RX and TX of the UART
    uart_irq_rx_disable(uart_dev);
    uart_irq_tx_disable(uart_dev);

    // Set the ISR callback for each character
    uart_irq_callback_set(uart_dev, uart_isr_cb);

    // Enable the RX of the UART dev
    uart_irq_rx_enable(uart_dev);

    while (1) {
            k_msleep(1000);
    }
    return 0;
}