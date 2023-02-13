/******************************************************************************
 * @file template
 * @brief App x8
 * @author Luos
 * @version 1.0.0
 ******************************************************************************/
#include <stdio.h>
#include "context.h"
#include "default_scenario.h"
#include "unit_test.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LUOS_TASK_NUMBER 3
#define TX_TASK_NUMBER   3

/*******************************************************************************
 * Variables
 ******************************************************************************/

default_scenario_t default_sc;
extern volatile uint8_t msg_buffer[MSG_BUFFER_SIZE];

// msg_t receive_msg[DUMMY_SERVICE_NUMBER];
uint8_t stream_Buffer1[STREAM_BUFFER_SIZE] = {0};
uint8_t stream_Buffer2[STREAM_BUFFER_SIZE] = {0};
streaming_channel_t Default_StreamChannel1;
streaming_channel_t Default_StreamChannel2;

/*******************************************************************************
 * Function
 ******************************************************************************/
extern void MsgAlloc_LuosTaskAlloc(ll_service_t *service_concerned_by_current_msg, msg_t *concerned_msg);

static void Reset_Streaming(void);
static void Detection(service_t *service);
static void App_1_MsgHandler(service_t *service, msg_t *msg);
static void App_2_MsgHandler(service_t *service, msg_t *msg);
static void App_3_MsgHandler(service_t *service, msg_t *msg);

/******************************************************************************
 * @brief Init scenario
 * @param None
 * @return None
 ******************************************************************************/
void Init_Context(void)
{
    RESET_ASSERT();
    Luos_Init();

    // Create services
    revision_t revision  = {.major = 1, .minor = 0, .build = 0};
    default_sc.App_1.app = Luos_CreateService(App_1_MsgHandler, VOID_TYPE, "Dummy_App_1", revision);
    default_sc.App_2.app = Luos_CreateService(App_2_MsgHandler, VOID_TYPE, "Dummy_App_2", revision);
    default_sc.App_3.app = Luos_CreateService(App_3_MsgHandler, VOID_TYPE, "Dummy_App_3", revision);

    Reset_Streaming();
    // Create stream channels
    Default_StreamChannel1 = Stream_CreateStreamingChannel(stream_Buffer1, STREAM_BUFFER_SIZE, 1);
    Default_StreamChannel2 = Stream_CreateStreamingChannel(stream_Buffer2, STREAM_BUFFER_SIZE, 1);

    // Detection
    Detection(default_sc.App_1.app);
    Luos_Loop();

    if (IS_ASSERT())
    {
        printf("[FATAL] Can't initialize scenario context\n");
        TEST_ASSERT_TRUE(IS_ASSERT());
    }
}

/******************************************************************************
 * @brief Reset context to init state
 * @param None
 * @return None
 ******************************************************************************/
void Reset_Context(void)
{
    RESET_ASSERT();
    Luos_ServicesClear();
    RoutingTB_Erase(); // Delete RTB
    Luos_Init();
    Reset_Streaming();
    if (IS_ASSERT())
    {
        printf("[FATAL] Can't reset scenario context\n");
        TEST_ASSERT_TRUE(IS_ASSERT());
    }
}

/******************************************************************************
 * @brief Launch a detection
 * @param Service who launches the detection
 * @return None
 ******************************************************************************/
static void Detection(service_t *service)
{
    search_result_t result;

    Luos_Detect(service);
    Luos_Loop();

    RTFilter_Reset(&result);
    printf("[INFO] %d services are active\n", result.result_nbr);
    TEST_ASSERT_EQUAL(DUMMY_SERVICE_NUMBER, result.result_nbr);
}

/******************************************************************************
 * @brief Create a streaming channel
 * @param None
 * @return None
 ******************************************************************************/
static void Reset_Streaming(void)
{
    // Stream Channel reset
    Stream_ResetStreamingChannel(&Default_StreamChannel1);
    Stream_ResetStreamingChannel(&Default_StreamChannel2);
    default_sc.streamChannel1 = &Default_StreamChannel1;
    default_sc.streamChannel2 = &Default_StreamChannel2;
    for (uint16_t i = 0; i < STREAM_BUFFER_SIZE; i++)
    {
        stream_Buffer1[i] = (uint8_t)(i);
        stream_Buffer2[i] = (uint8_t)(i);
    }
}
/******************************************************************************
 * @brief Loop Service App_1
 * @param None
 * @return None
 ******************************************************************************/
void App_1_Loop(void)
{
}

/******************************************************************************
 * @brief Loop Service App_2
 * @param None
 * @return None
 ******************************************************************************/
void App_2_Loop(void)
{
}

/******************************************************************************
 * @brief Loop Service App_3
 * @param None
 * @return None
 ******************************************************************************/
void App_3_Loop(void)
{
}

/******************************************************************************
 * @brief Msg Handler callback : save last message
 * @param service destination
 * @param Msg receive
 * @return None
 ******************************************************************************/
static void App_1_MsgHandler(service_t *service, msg_t *msg)
{
    memcpy(&default_sc.App_1.last_rx_msg, msg, sizeof(msg_t));
}

/******************************************************************************
 * @brief Msg Handler callback : save last message
 * @param service destination
 * @param Msg receive
 * @return None
 ******************************************************************************/
static void App_2_MsgHandler(service_t *service, msg_t *msg)
{
    memcpy(&default_sc.App_2.last_rx_msg, msg, sizeof(msg_t));
}

/******************************************************************************
 * @brief Msg Handler callback : save last message
 * @param service destination
 * @param Msg receive
 * @return None
 ******************************************************************************/
static void App_3_MsgHandler(service_t *service, msg_t *msg)
{
    memcpy(&default_sc.App_3.last_rx_msg, msg, sizeof(msg_t));
}
