/*******************************************************************************
 * Project: EPD
 *
 * Interface for driving the EPD hardware i.e. digital pin read/write and SPI.
 * This implementation of the interface is specific to the Raspberry Pi.
 *
 * Written by Mihnea Rusu, 02/08/2019
 ******************************************************************************/

/*******************************************************************************
 * SYSTEM HEADERS
 ******************************************************************************/
#include "errno.h"

/*******************************************************************************
 * LIBRARY HEADERS
 ******************************************************************************/
#include <bcm2835.h>

/*******************************************************************************
 * USER HEADERS
 ******************************************************************************/
#include "driver/epdhw.h"

/*******************************************************************************
 * PRIVATE VARIABLES
 ******************************************************************************/
static uint8_t spi_is_init_ = 0;

/*******************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 ******************************************************************************/
int epdhw_digital_write(
        uint16_t pin,
        uint8_t val
        )
{
        bcm2835_gpio_write(pin, val);
        return 0;
}

uint8_t epdhw_digital_read(
        uint16_t pin
        )
{
        return bcm2835_gpio_lev(pin);
}

int epdhw_spi_write_byte(
        struct epdhw *epdhw,
        uint8_t val
        )
{
        bcm2835_spi_transfer(val);
}

void epdhw_delay(
        uint32_t ms
        )
{
        bcm2835_delay(ms);
}

int epdhw_alloc(
        struct epdhw **epdhw
        )
{
        int i;
        int ret = 0;

        *epdhw = malloc(sizeof(*epdhw));
        if ((*epdhw) == NULL) {
                ret = -ENOMEM;
                goto epdhw_init_ret;
        }

        if (i == EPDHW_MAX_NUM_DEV) {
                /* TODO: Appropriate code */
                ret = -EINVAL;
                goto epdhw_init_free;
        }

        return ret;

epdhw_init_free:
        free(*epdhw);
        *epdhw = NULL;
epdhw_init_ret:
        return ret;
}

int epdhw_init(
        struct epdhw *epdhw
        )
{
        if (!epdhw->is_init) {
                bcm2835_gpio_fsel(epdhw->pin_rst , BCM2835_GPIO_FSEL_OUTP);
                bcm2835_gpio_fsel(epdhw->pin_dc  , BCM2835_GPIO_FSEL_OUTP);
                bcm2835_gpio_fsel(epdhw->pin_cs  , BCM2835_GPIO_FSEL_OUTP);
                bcm2835_gpio_fsel(epdhw->pin_busy, BCM2835_GPIO_FSEL_INPT);
        }

        return 0;
}

void epdhw_deinit(
        struct epdhw *epdhw
        )
{
        epdhw_digital_write(epdhw->pin_cs , 0);
        epdhw_digital_write(epdhw->pin_dc , 0);
        epdhw_digital_write(epdhw->pin_rst, 0);
}

void epdhw_free(
        struct epdhw **epdhw
        )
{
        if ((*epdhw) != NULL) {
                free(*epdhw);
                *epdhw = NULL;
        }
}

int epdhw_init_global()
{
        if (!spi_is_init_) {
                if (!bcm2835_init()) {
                        return -EACCESS;
                }

                /* Start spi interface, set spi pin for the reuse function */
                bcm2835_spi_begin();
                /* High first transmission */
                bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
                /* SPI mode 0 */
                bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
                /* Frequency */
                bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128);
        }
        return 0;
}

void epdhw_deinit_global()
{
        bcm2835_spi_end();
        bcm2835_close();
        spi_is_init_ == 0;
}

/******************************** END OF FILE *********************************/
