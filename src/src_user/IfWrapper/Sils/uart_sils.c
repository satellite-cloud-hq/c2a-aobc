#pragma section REPRO
#include <src_core/IfWrapper/uart.h>
#include "../../Settings/port_config.h"

#ifdef USE_SCI_COM_UART
#include "uart_sils_sci_if.h"
#endif

#ifdef USE_KBLE_MOBC_UART
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
  int UART_init_kble(void* my_uart_v);
  int UART_rx_kble(void* my_uart_v, void* data_v, int buffer_size);
  int UART_tx_kble(void* my_uart_v, void* data_v, int data_size);
  int UART_reopen_kble(void* my_uart_v, int reason);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif

int OBC_C2A_SendFromObc(int port_id, unsigned char* buffer, int offset, int count);
int OBC_C2A_ReceivedByObc(int port_id, unsigned char* buffer, int offset, int count);

int UART_init(void* my_uart_v)
{
#if defined(USE_KBLE_MOBC_UART)
  UART_Config* my_uart = (UART_Config*)my_uart_v;

  if (my_uart->ch == PORT_CH_UART_MOBC)
  {
    return UART_init_kble(my_uart_v);
  }
#else
  (void) my_uart_v;
#endif
  return 0;
}

int UART_rx(void* my_uart_v, void* data_v, int buffer_size)
{
  UART_Config* my_uart = (UART_Config*)my_uart_v;

#if defined(USE_KBLE_MOBC_UART)
  if (my_uart->ch == PORT_CH_UART_MOBC)
  {
    return UART_rx_kble(my_uart_v, data_v, buffer_size);
  }
  else
  {
    return OBC_C2A_ReceivedByObc(my_uart->ch, (unsigned char*)data_v, 0, buffer_size);
  }
#elif defined(USE_SCI_COM_UART)
  if (my_uart->ch == PORT_CH_UART_MOBC)
  {
    return SILS_SCI_UART_IF_rx((unsigned char*)data_v, buffer_size);
  }
  else
  {
    return OBC_C2A_ReceivedByObc(my_uart->ch, (unsigned char*)data_v, 0, buffer_size);
  }
#else
  return OBC_C2A_ReceivedByObc(my_uart->ch, (unsigned char*)data_v, 0, buffer_size);
#endif
}

int UART_tx(void* my_uart_v, void* data_v, int data_size)
{
  UART_Config* my_uart = (UART_Config*)my_uart_v;

#if defined(USE_KBLE_MOBC_UART)
  if (my_uart->ch == PORT_CH_UART_MOBC)
  {
    return UART_tx_kble(my_uart_v, data_v, data_size);
  }
  else
  {
    int result = OBC_C2A_SendFromObc(my_uart->ch, (unsigned char*)data_v, 0, data_size);

    if (result < 0) return -1;
  }
#elif defined(USE_SCI_COM_UART)
  if (my_uart->ch == PORT_CH_UART_MOBC)
  {
    SILS_SCI_UART_IF_tx((unsigned char*)data_v, data_size);
  }
  else
  {
    int result = OBC_C2A_SendFromObc(my_uart->ch, (unsigned char*)data_v, 0, data_size);

    if (result < 0) return -1;
  }
#else
  int result = OBC_C2A_SendFromObc(my_uart->ch, (unsigned char*)data_v, 0, data_size);

  if (result < 0) return -1;
#endif

  return 0;
}

int UART_reopen(void* my_uart_v, int reason)
{
  (void) my_uart_v;
  (void) reason;
  return 0;
}

#pragma section
