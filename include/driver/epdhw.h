/******************************************************************************
 * Project: epd
 *
 * Interface for driving the EPD hardware i.e. digital pin read/write and SPI.
 *
 * Written by Mihnea Rusu, 14/07/2019
 ******************************************************************************/

#ifndef EPD_DRIVER_EPDHW_H
#define EPD_DRIVER_EPDHW_H

/*******************************************************************************
 * PUBLIC DEFINES
 ******************************************************************************/
#define EPDHW_MAX_NUM_DEV               (100)

#define EPDHW_TRUE                      ((uint8_t)1)
#define EPDHW_FALSE                     ((uint8_t)0)

/* DEFAULT */
typedef uint8_t                         epd_byte_t;

/*******************************************************************************
 * PUBLIC STRUCTURE DECLARATIONS
 ******************************************************************************/
struct epdhw
{
        int pin_spi_miso;
        int pin_spi_mosi;
        int pin_spi_sck;
        int pin_rst;
        int pin_dc;
        int pin_cs;
        int pin_busy;

        uint8_t is_init;

        /* Must be < EPDHW_MAX_NUM_DEV */
        int dev_num;
};

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************/
/**
 * Write a single HIGH or LOW on a digital pin.
 *
 * \param pin Pin to write the value on
 * \param val 0 for LOW, 1 for HIGH
 *
 * \returns 0 if success, -errno if failure
 */
int epdhw_digital_write(uint16_t pin, epd_byte_t val);

/**
 * Read the value on a given digital pin.
 *
 * \param pin Pin to read the value from
 * 
 * \returns 0 if LOW, 1 if HIGH
 */
epd_byte_t epdhw_digital_read(uint16_t pin);

/**
 * Write a single byte using the SPI port.
 *
 * \param epdhw Interface on which to write
 * \param val Byte to write
 *
 * \returns 0 if success, -errno if failure
 */
int epdhw_spi_write_byte(struct epdhw *epdhw, epd_byte_t val);

/**
 * Delay for a number of milliseconds.
 *
 * \param ms Milliseconds to delay
 */
void epdhw_delay(uint32_t ms);

/**
 * Allocate memory for the EPD interface
 *
 * \param epdhw EPD interface
 *
 * \returns 0 if success, -errno if failure
 */
int epdhw_alloc(struct epdhw **epdhw);

/**
 * Initialize the EPD interface
 *
 * \param epdhw EPD interface
 *
 * \returns 0 if success, -errno if failure
 */
int epdhw_init(struct epdhw *epdhw);

/**
 * Deinitialize the EPD interface
 *
 * \param epdhw EPD interface
 */
void epdhw_deinit(struct epdhw *epdhw);

/**
 * Free memory that was previously allocated for the EPD interface
 *
 * \param epdhw EPD interface
 */
void epdhw_free(struct epdhw *epdhw);

/**
 * Initialize the global EPD hardware interface
 *
 * \returns 0 if success, -errno if failure.
 */
int epdhw_init_global();

/**
 * Deinitialize the global EPD hardware interface
 */
void epdhw_deinit_global();

#endif /* EPD_DRIVER_EPDHW_H */

/******************************** END OF FILE *********************************/
