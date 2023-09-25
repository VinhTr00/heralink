/*
 * max1538.h
 *
 *  Created on: Sep 9, 2023
 *      Author: vinhtran
 */

#ifndef _MAX1538_H_
#define _MAX1538_H_

#include <stdint.h>
#include "shared_resource.h"

void Max1538_init(void);
BATSEL_MODE_E Max1538_release_mode_batsel(void);
MAX1538_STATE_E Max1538_release_state(void);
void Max1538_configure_state(MAX1538_STATE_E state);

#endif /* _MAX1538_H_ */
    