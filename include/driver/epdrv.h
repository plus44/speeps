/******************************************************************************
 * Project: epd
 *
 * Interface for controlling the EPD display with useful data
 *
 * Written by Mihnea Rusu, 07/03/2020
 ******************************************************************************/

#ifndef EPD_DRIVER_EPDRV_H
#define EPD_DRIVER_EPDRV_H

/*******************************************************************************
 * USER INCLUDES
 ******************************************************************************/
#include "driver/epdhw.h"

/*******************************************************************************
 * FORWARD DECLARATIONS
 ******************************************************************************/
struct epdisp;

/*******************************************************************************
 * PUBLIC ENUMERATION DECLARATIONS
 ******************************************************************************/
typedef enum {
        EPDRV_TYPE_UNKNOWN = 0,
        EPDRV_TYPE_MONOCHROME
} epdrv_type_t;

/*******************************************************************************
 * PUBLIC STRUCTURE DECLARATIONS
 ******************************************************************************/
struct epdrv
{
        int (*init)(struct edpisp*);
        int (*clear)(struct edpisp*);
        int (*display)(struct edpisp*, const epd_byte_t *const);
        int (*display_part)(struct edpisp*, const epd_byte_t *const);
        int (*sleep)(struct edpisp*);

        /* For future extension */
        epdrv_type_t type;
        void *extra;
};

#endif /* EPD_DRIVER_EPDRV_H */

/******************************** END OF FILE *********************************/
