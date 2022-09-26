/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#define ESP_ZB_PACKED_STRUCT __attribute__ ((packed))

typedef uint8_t esp_zb_64bit_addr_t[8];
typedef esp_zb_64bit_addr_t esp_zb_ieee_addr_t;
typedef void (*esp_zb_zcl_cluster_init_t)(void);
typedef void (*esp_zb_callback_t)(uint8_t param);

/**
 * @brief The Zigbee address union consist of 16 bit short address and 64 bit long address.
 *
 */
typedef union {
    uint16_t  addr_short;                           /*!< Zigbee short address */
    esp_zb_ieee_addr_t addr_long;                   /*!< Zigbee long address */
} esp_zb_addr_u;

/** Enum of the Zigbee ZCL address type
 * @brief Possible address types of devices from which ZCL message is received.
 * @anchor esp_zb_zcl_address_type_t
 */
typedef enum {
    ESP_ZB_ZCL_ADDR_TYPE_SHORT = 0U,
    ESP_ZB_ZCL_ADDR_TYPE_IEEE_GPD = 1U,
    ESP_ZB_ZCL_ADDR_TYPE_SRC_ID_GPD = 2U,
    ESP_ZB_ZCL_ADDR_TYPE_IEEE = 3U,
} esp_zb_zcl_address_type_t;

/**
 * @brief Type to represent source address of ZCL message
 * @note Address type refer @ref esp_zb_zcl_address_type_t
 */
typedef struct esp_zb_zcl_addr_s {
    esp_zb_zcl_address_type_t addr_type;            /*!< address type see esp_zb_zcl_address_type_t */
    union {
        uint16_t short_addr;            /*!< Zigbee short address */
        uint32_t src_id;                /*!< Source ID of ZGPD */
        esp_zb_ieee_addr_t ieee_addr;   /*!< Full IEEE-address of ZGPD */
    } u;                                /*!< Union of the address */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_addr_t;

/**
 * @brief Type to represent ZCL attribute definition structure
 * @note Access define refer to zcl_attr_access
 */
typedef struct esp_zb_zcl_attr_s {
    uint16_t id;                        /*!< Attribute id */
    uint8_t type;                       /*!< Attribute type see zcl_attr_type */
    uint8_t access;                     /*!< Attribute access options according to zcl_attr_access */
    void *data_p;                       /*!< Pointer to attribute data */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_attr_t;

/**
 * @brief Type to represent ZCL cluster definition structure
 * @note Cluster id refer to zcl_cluster_id and attribute define see @ref esp_zb_zcl_attr_s
 */
typedef struct esp_zb_zcl_cluster_s {
    uint16_t cluster_id;                        /*!< ZCL 16-bit cluster id. Refer zcl_cluster_id */
    uint16_t attr_count;                        /*!< Attributes number supported by the cluster */
    esp_zb_zcl_attr_t *attr_desc_list;          /*!< List of cluster attributes esp_zb_zcl_attr_t */
    uint8_t role_mask;                          /*!< Cluster role, refer to zcl_cluster_role */
    uint16_t manuf_code;                        /*!< Manufacturer code for cluster and its attributes */
    esp_zb_zcl_cluster_init_t cluster_init;     /*!< cluster init callback function */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_cluster_t;

/**
 * @brief Type to represent type signed int_24
 * @note Internal use
 */
typedef struct esp_zb_int24_s {
    uint16_t low;               /*!< Low 16-bit of the value */
    int8_t   high;              /*!< High 8-bit of the value with signed */
} ESP_ZB_PACKED_STRUCT
esp_zb_int24_t;

/**
 * @brief Type to represent type unsigned int_24
 * @note Internal use
 */
typedef struct esp_zb_uint24_s {
    uint16_t low;               /*!< Low 16-bit of the value */
    uint8_t high;               /*!< High 8-bit of the value */
} ESP_ZB_PACKED_STRUCT
esp_zb_uint24_t;

/**
 * @brief Type to represent type unsigned int_48
 * @note Internal use
 */
typedef struct esp_zb_uint48_s {
    uint32_t low;               /*!< Low 32-bit of the value */
    uint16_t high;              /*!< High 16-bit of the value */
} ESP_ZB_PACKED_STRUCT
esp_zb_uint48_t;

/**
 * @brief Type to represent type signed int_48
 * @note Internal use
 */
typedef struct esp_zb_int48_s {
    uint32_t low;               /*!< Low 32-bit of the value */
    int16_t high;               /*!< High 16-bit of the value with signed */
} ESP_ZB_PACKED_STRUCT
esp_zb_int48_t;

/**
 * @brief Union of the ZCL attribute value
 * @note Internal use
 */
union esp_zb_zcl_attr_var_u {
    uint8_t u8;         /*!< Unsigned 8-bit int of integer */
    int8_t s8;          /*!< Signed 8-bit int of integer */
    uint16_t u16;       /*!< Unsigned 16-bit of integer */
    int16_t s16;        /*!< Signed 16-bit of integer */
    esp_zb_uint24_t u24;/*!< Unsigned 24-bit of the integer */
    esp_zb_int24_t s24; /*!< Signed 24-bit of the integer */
    uint32_t u32;       /*!< Unsigned 32-bit of the integer */
    int32_t s32;        /*!< Signed 32-bit of the integer */
    esp_zb_uint48_t u48;/*!< Unsigned 48-bit of the integer */
    uint8_t data_buf[4];/*!< Data array */
};

/**
 * @brief Type to represent ZCL attribute reporting info structure
 * @note Internal use
 */
typedef struct esp_zb_zcl_reporting_info_s {
    uint8_t direction;              /*!< Direction: report is send or received */
    uint8_t ep;                     /*!< Endpoint number */
    uint16_t cluster_id;            /*!< Cluster ID for reporting */
    uint8_t cluster_role;           /*!< Cluster rolo server/client */
    uint16_t attr_id;               /*!< Attribute ID for reporting */
    uint8_t flags;                  /*!< Flags to inform status of reporting */
    uint32_t run_time;              /*!< Time to run next reporting activity */
    union {
        struct {
            uint16_t min_interval; /*!< Actual minimum reporting interval */
            uint16_t max_interval; /*!< Actual maximum reporting interval */
            union esp_zb_zcl_attr_var_u delta; /*!< Actual reportable change */
            union esp_zb_zcl_attr_var_u reported_value; /*!< The last reported value */
            uint16_t def_min_interval; /*!< Default minimum reporting interval */
            uint16_t def_max_interval; /*!< Default maximum reporting interval */
        }
        send_info;  /*!< send_info is stored on cluster server side (as usual) and describes how
                  attribute should be reported */
        struct {
            uint16_t timeout; /*!< Timeout period */
        }
        recv_info; /*!< recv_info is stored on cluster client side (as usual) and describes how
                 attribute report is received */
    }
    u;            /*!< Union of the report info*/

    struct {
        uint16_t short_addr; /*!< Destination short address */
        uint8_t  endpoint;   /*!< Destination endpoint */
        uint16_t profile_id; /*!< Profile id */
    }
    dst;        /*!< Union of the ZCL destination */
}
esp_zb_zcl_reporting_info_t;

/**
 * @brief Structure of Alarm variables
 * @note Internal use
 */
typedef struct esp_zb_zcl_cvc_alarm_variables_s {
    uint8_t endpoint_id;                /*!< Endpoint id */
    uint16_t cluster_id;                /*!< Cluster id */
    uint16_t attribute_id;              /*!< Attribute id */
    uint8_t alarm_buf_id;               /*!< Alarm buffer id */
    bool is_used;                       /*!< Is Used flag */
} ESP_ZB_PACKED_STRUCT
esp_zb_zcl_cvc_alarm_variables_t;

/**
 * @brief Structure of simple descriptor request of ZCL command
 */
typedef struct esp_zb_af_simple_desc_1_1_s {
    uint8_t    endpoint;                        /*!< Endpoint */
    uint16_t   app_profile_id;                  /*!< Application profile identifier */
    uint16_t   app_device_id;                   /*!< Application device identifier */
    uint32_t    app_device_version: 4;          /*!< Application device version */
    uint32_t    reserved: 4;                    /*!< Reserved */
    uint8_t    app_input_cluster_count;         /*!< Application input cluster count */
    uint8_t    app_output_cluster_count;        /*!< Application output cluster count */
    uint16_t   app_cluster_list[2];             /*!< Application input and output cluster list */
} ZB_PACKED_STRUCT
esp_zb_af_simple_desc_1_1_t;

/**
 * @brief Type to represent ZCL endpoint definition structure
 * @note  The esp_zb_zcl_reporting_info_t defines see @ref esp_zb_zcl_reporting_info_s
* @note  The esp_zb_af_simple_desc_1_1_t defines see @ref esp_zb_af_simple_desc_1_1_s
 */
typedef struct esp_zb_endpoint_s {
    uint8_t ep_id;                              /*!< Endpoint ID */
    uint16_t profile_id;                        /*!< Application profile, which implemented on endpoint */
    esp_zb_callback_t device_handler;           /*!< endpoint specific callback, handles all commands for this endpoint. If set, it will be called to handle callback,like esp_zb_add_read_attr_resp_cb */
    esp_zb_callback_t identify_handler;         /*!< Identify notification callback. If set, it will be called on identification start and stop indicating start event with a non-zero argument*/
    uint8_t reserved_size;                      /*!< Unused parameter (reserved for future use) */
    void *reserved_ptr;                         /*!< Unused parameter (reserved for future use) */
    uint8_t cluster_count;                      /*!< Number of supported clusters */
    esp_zb_zcl_cluster_t *cluster_desc_list;    /*!< Supported clusters list */
    esp_zb_af_simple_desc_1_1_t *simple_desc;   /*!< Simple descriptor */
    uint8_t rep_info_count;                     /*!< Number of reporting info slots */
    esp_zb_zcl_reporting_info_t *reporting_info; /*!< Attributes reporting information */
    uint8_t cvc_alarm_count;          /*!< Number of continuous value change alarm slots */
    esp_zb_zcl_cvc_alarm_variables_t *cvc_alarm_info;   /*!< pointer to the cvc alarm structure */
} ESP_ZB_PACKED_STRUCT
esp_zb_endpoint_t;

/******************* attribute list *******************/
/**
 * @brief The esp-zigbee data model of list of attribute.
 *
 * @note An attribute list groups up a single cluster.
 */
typedef struct esp_zb_attribute_list_s {
    esp_zb_zcl_attr_t   attribute;              /*!< A single attribute */
    uint16_t     cluster_id;                    /*!< A cluster id assigned to this attribute */
    struct esp_zb_attribute_list_s *next;       /*!< A pointer to next attribute */
} esp_zb_attribute_list_t;

/******************* cluster list *******************/
/**
 * @brief The esp-zigbee data model of list of cluster.
 *
 */
typedef struct esp_zb_cluster_list_s {
    esp_zb_zcl_cluster_t cluster;               /*!< A single cluster */
    struct esp_zb_cluster_list_s *next;         /*!< A pointer to next cluster */
} esp_zb_cluster_list_t;

/******************* endpoint list *******************/
/**
 * @brief The esp-zigbee data model of list of endpoint.
 *
 */
typedef struct esp_zb_ep_list_s {
    esp_zb_endpoint_t endpoint;                 /*!< A single endpoint */
    struct esp_zb_ep_list_s *next;              /*!< A pointer to next endpoint */
} esp_zb_ep_list_t;

/****************** standard clusters *********************/
/**
 * @brief Zigbee standard mandatory attribute for basic cluster.
 *
 */
typedef struct esp_zb_basic_cluster_cfg_s {
    uint8_t  zcl_version;                       /*!<  ZCL version */
    uint8_t  power_source;                      /*!<  The sources of power available to the device */
} esp_zb_basic_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for identify cluster.
 *
 */
typedef struct esp_zb_identify_cluster_cfg_s {
    uint16_t  identify_time;                    /*!<  The remaining length of the time that identify itself */
} esp_zb_identify_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for groups cluster.
 *
 */
typedef struct esp_zb_groups_cluster_cfg_s {
    uint8_t  groups_name_support_id;            /*!<  The indication of group names are supported or not */
} esp_zb_groups_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for scenes cluster.
 *
 */
typedef struct esp_zb_scenes_cluster_cfg_s {
    uint8_t  scenes_count;                      /*!<  The number of scenes currently in the scene table */
    uint8_t  current_scene;                     /*!<  Scene ID that invoked */
    uint16_t current_group;                     /*!<  Group ID that invoked */
    bool  scene_valid;                          /*!<  Indication of the associated with current scene and group valid or not*/
    uint8_t  name_support;                      /*!<  The indication of group names are supported or not */
} esp_zb_scenes_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for on_off cluster.
 *
 */
typedef struct esp_zb_on_off_cluster_cfg_s {
    bool  on_off;                               /*!<  On Off state of the device */
} esp_zb_on_off_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for level cluster.
 *
 */
typedef struct esp_zb_level_cluster_cfg_s {
    uint8_t  current_level;                     /*!<  Current level of the device */
} esp_zb_level_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for color cluster.
 *
 */
typedef struct esp_zb_color_cluster_cfg_s {
    uint16_t current_x;                         /*!<  The current value of the normalized chromaticity value x */
    uint16_t current_y;                         /*!<  The current value of the normalized chromaticity value y */
    uint8_t  color_mode;                        /*!<  The mode which attribute determines the color of the device */
    uint8_t  options;                           /*!<  The bitmap determines behavior of some cluster commands */
    uint8_t  enhanced_color_mode;               /*!<  The enhanced-mode which attribute determines the color of the device */
    uint16_t color_capabilities;                /*!<  Specifying the color capabilities of the device support the color control cluster */
} esp_zb_color_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for time cluster.
 *
 */
typedef struct esp_zb_time_cluster_cfg_s {
    uint16_t time;                              /*!<  The time value of the a real time clock */
    uint16_t time_status;                       /*!<  The time status holds a number of bit field of status */
} esp_zb_time_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for shade config cluster.
 *
 */
typedef struct esp_zb_shade_config_cluster_cfg_s {
    uint8_t     status;                             /*!<  The status attribute indicates the status of a number of shade function */
    uint16_t    closed_limit;                       /*!<  The attribute indicates most closed position that shade can move to */
    uint8_t     mode;                               /*!<  The attribute indicates the current operating mode */
} esp_zb_shade_config_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for door lock cluster.
 *
 */
typedef struct esp_zb_door_lock_cluster_cfg_s {
    uint8_t lock_state;                         /*!<  The attribute indicates the state of lock */
    uint8_t lock_type;                          /*!<  The attribute indicates different type of the lock type */
    bool    actuator_enabled;                   /*!<  The attribute indicates if the lock is currently able (Enabled) or not able (Disabled) to process remote lock */
} esp_zb_door_lock_cluster_cfg_t;

/**
 * @brief Zigbee standard mandatory attribute for temperature measurement cluster.
 *
 */
typedef struct esp_zb_temperature_meas_cluster_cfg_s {
    int16_t measured_value;                     /*!<  The attribute indicates the temperature in degrees Celsius */
    int16_t min_value;                          /*!<  The attribute indicates minimum value of the measured value */
    int16_t max_value;                          /*!<  The attribute indicates maximum value of the measured value */
} esp_zb_temperature_meas_cluster_cfg_t;

/****************** standard device config *********************/
/**
 * @brief Zigbee HA standard on-off light device clusters.
 *
 */
typedef struct esp_zb_on_off_light_cfg_s {
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
    esp_zb_groups_cluster_cfg_t     groups_cfg;     /*!<  Groups cluster configuration */
    esp_zb_scenes_cluster_cfg_t     scenes_cfg;     /*!<  Scenes cluster configuration */
    esp_zb_on_off_cluster_cfg_t     on_off_cfg;     /*!<  On off cluster configuration */
} esp_zb_on_off_light_cfg_t;

/**
 * @brief Zigbee HA standard on-off switch device clusters.
 *
 */
typedef struct esp_zb_on_off_switch_cfg_s {
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
} esp_zb_on_off_switch_cfg_t;

/**
 * @brief Zigbee HA standard color dimmable light device clusters.
 *
 */
typedef struct esp_zb_color_dimmable_light_cfg_s {
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
    esp_zb_groups_cluster_cfg_t     groups_cfg;     /*!<  Groups cluster configuration */
    esp_zb_scenes_cluster_cfg_t     scenes_cfg;     /*!<  Scenes cluster configuration */
    esp_zb_on_off_cluster_cfg_t     on_off_cfg;     /*!<  On off cluster configuration */
    esp_zb_level_cluster_cfg_t      level_cfg;      /*!<  Level cluster configuration */
    esp_zb_color_cluster_cfg_t      color_cfg;      /*!<  Color cluster configuration */
} esp_zb_color_dimmable_light_cfg_t;

/**
 * @brief Zigbee HA standard color dimmable switch device clusters.
 *
 */
typedef struct esp_zb_color_dimmable_switch_cfg_s {
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
} esp_zb_color_dimmable_switch_cfg_t;

/**
 * @brief Zigbee HA standard mains power outlet clusters.
 *
 */
typedef struct esp_zb_mains_power_outlet_cfg_s {
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
    esp_zb_groups_cluster_cfg_t     groups_cfg;     /*!<  Groups cluster configuration */
    esp_zb_scenes_cluster_cfg_t     scenes_cfg;     /*!<  Scenes cluster configuration */
    esp_zb_on_off_cluster_cfg_t     on_off_cfg;     /*!<  On off cluster configuration */
} esp_zb_mains_power_outlet_cfg_t;

/**
 * @brief Zigbee HA standard shade clusters.
 *
 */
typedef struct esp_zb_shade_cfg_s {
    esp_zb_basic_cluster_cfg_t          basic_cfg;          /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t       identify_cfg;       /*!<  Identify cluster configuration */
    esp_zb_groups_cluster_cfg_t         groups_cfg;         /*!<  Groups cluster configuration */
    esp_zb_scenes_cluster_cfg_t         scenes_cfg;         /*!<  Scenes cluster configuration */
    esp_zb_on_off_cluster_cfg_t         on_off_cfg;         /*!<  On off cluster configuration */
    esp_zb_level_cluster_cfg_t          level_cfg;          /*!<  Level cluster configuration */
    esp_zb_shade_config_cluster_cfg_t   shade_cfg;          /*!<  Shade config cluster configuration */
} esp_zb_shade_cfg_t;

/**
 * @brief Zigbee HA standard shade controller device clusters.
 *
 */
typedef struct esp_zb_shade_controller_cfg_s {
    esp_zb_basic_cluster_cfg_t      basic_cfg;      /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;   /*!<  Identify cluster configuration */
} esp_zb_shade_controller_cfg_t;

/**
 * @brief Zigbee HA standard door lock clusters.
 *
 */
typedef struct esp_zb_door_lock_cfg_s {
    esp_zb_basic_cluster_cfg_t      basic_cfg;          /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;       /*!<  Identify cluster configuration */
    esp_zb_groups_cluster_cfg_t     groups_cfg;         /*!<  Groups cluster configuration */
    esp_zb_scenes_cluster_cfg_t     scenes_cfg;         /*!<  Scenes cluster configuration */
    esp_zb_door_lock_cluster_cfg_t  door_lock_cfg;      /*!<  Door Lock cluster configuration */
} esp_zb_door_lock_cfg_t;

/**
 * @brief Zigbee HA standard door lock controller clusters.
 *
 */
typedef struct esp_zb_door_lock_controller_cfg_s {
    esp_zb_basic_cluster_cfg_t      basic_cfg;          /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t   identify_cfg;       /*!<  Identify cluster configuration */
} esp_zb_door_lock_controller_cfg_t;

/**
 * @brief Zigbee HA standard temperature sensor clusters.
 *
 */
typedef struct esp_zb_temperature_sensor_cfg_s {
    esp_zb_basic_cluster_cfg_t                  basic_cfg;          /*!<  Basic cluster configuration */
    esp_zb_identify_cluster_cfg_t               identify_cfg;       /*!<  Identify cluster configuration */
    esp_zb_temperature_meas_cluster_cfg_t       temp_meas_cfg;      /*!<  Temperature measurement cluster configuration */
} esp_zb_temperature_sensor_cfg_t;

#ifdef __cplusplus
}
#endif
