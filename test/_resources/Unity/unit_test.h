#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#undef _WEAKED
#define _WEAKED __attribute__((weak))

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../../.pio/libdeps/native/Unity/src/unity.h"
#include "luos_hal.h"
#include "robus_hal.h"
#include "luos_engine.h"
#include "luos_utils.h"
#include "robus_struct.h"
#include <setjmp.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifdef _WIN32
    #define _SETJMP  __builtin_setjmp
    #define _LONGJMP __builtin_longjmp
#else
    #define _SETJMP  setjmp
    #define _LONGJMP longjmp
#endif

extern jmp_buf err_ctx;
extern bool try_state;

#ifndef UNIT_TEST_RUN
    #define UNIT_TEST_RUN(f) RUN(#f, f)
#endif

/* This structure is used for unit test assert
 */
typedef struct
{
    uint8_t enable; // enable = 0 to disable asserts
    uint8_t state;  // state = 1 when an assert has occured
    uint32_t file_size;
    uint32_t line_size;
    msg_t msg;
} ut_luos_assert_t;

#define TRY           \
    try_state = true; \
    if (!_SETJMP(err_ctx))

#define CATCH else

/*******************************************************************************
 * Function
 ******************************************************************************/
void RESET_ASSERT(void);
void ASSERT_ACTIVATION(uint8_t activation);
bool IS_ASSERT(void);
void NEW_TEST_CASE(char *title);
void NEW_STEP(char *title);
void RUN(const char *name, void (*f)(void));
void NEW_STEP_IN_LOOP(char message[], uint32_t index);
void setUp(void);
void tearDown(void);

#endif // UNIT_TEST_H
