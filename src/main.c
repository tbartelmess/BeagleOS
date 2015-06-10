int main() {
    /* volatile short* const UART0 = (volatile short*)0x44E09000;      /\* UART0 register *\/ */
    /* volatile short* const UART_LSR_UART = UART0 + 0x14; */
    /* volatile short* const UART_THR = UART0 + 0x0; */

    /* while (!(*UART_LSR_UART & 0x20)); */
    /* *UART_THR = 'E'; */
    int i = 0;
    for (int j = 0; j < 10000; j++)
        i++;

    return i;
}
