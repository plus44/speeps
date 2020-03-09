/******************************************************************************
 * Project: epd
 *
 * Interface for controlling the EPD display with useful data
 *
 * Written by Mihnea Rusu, 07/03/2020
 ******************************************************************************/

#ifndef EPD_DRIVER_EPDISP_H
#define EPD_DRIVER_EPDISP_H

/*******************************************************************************
 * USER INCLUDES
 ******************************************************************************/
#include "driver/epdhw.h"
#include "driver/epdrv.h"

/*******************************************************************************
 * PUBLIC DEFINES
 ******************************************************************************/
/* None */

/*******************************************************************************
 * PUBLIC STRUCTURE DECLARATIONS
 ******************************************************************************/
struct epdisp
{
        /** EPD hardware device */
        struct epdhw *hw;

        /* EPD display driver */
        const struct epdrv *drv;

        /** Is the display initialized? */
        uint8_t is_init;
};

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************/
/**
 * Allocate memory for the EPD display structure
 *
 * \param epdisp EPD display structure
 *
 * \returns 0 if success, -errno if failure
 */
int epdisp_alloc(struct epdisp **epdisp);

/**
 * Initialize the EPD display
 *
 * \param epdisp EPD display
 *
 * \returns 0 if success, -errno if failure
 */
int epdisp_init(struct epdisp *epdisp);

/**
 * Deinitialize the EPD display
 *
 * \param epdisp EPD display
 */
void epdisp_deinit(struct epdisp *epdisp);

/**
 * Free memory that was previously allocated for the EPD display structure
 *
 * \param epdisp EPD display structure
 */
void epdisp_free(struct epdisp *epdisp);

#endif /* EPD_DRIVER_EPDISP_H */

/******************************** END OF FILE *********************************/
