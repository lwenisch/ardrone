#ifndef _communication_
#define _communication_

#define MSG_LENGTH 1000
#include "Vector.h"
#include "stdbool.h"


typedef struct Type_Message {
    char m_sender[MSG_LENGTH];
    int m_length;
    char m_message[MSG_LENGTH];
} Type_Message;

typedef struct SAMPLING_PORT_STATUS_TYPE {
    int MAX_MESSAGE_SIZE;
    bool PORT_DIRECTION;
    int REFRESH_PERIOD;
    int LAST_MSG_VALIDITY;
} SAMPLING_PORT_STATUS_TYPE;

typedef struct COMMUNICATION_VECTOR {
    char* emetteur;
    vector vsamp_socket; //int
    vector vqueuing_socket; //int
    vector vsamp_port; //int
    vector vqueuing_port; //int
} COMMUNICATION_VECTOR;

typedef struct Navdata_def {
  int    tag;					  /*!< Navdata block ('option') identifier */
  int    size;					  /*!< set this to the size of this structure */

  int    ctrl_state;             /*!< Flying state (landed, flying, hovering, etc.) defined in CTRL_STATES enum. */
  int    vbat_flying_percentage; /*!< battery voltage filtered (mV) */

  float   theta;                  /*!< UAV's pitch in milli-degrees */
  float   phi;                    /*!< UAV's roll  in milli-degrees */
  float   psi;                    /*!< UAV's yaw   in milli-degrees */

  int     altitude;               /*!< UAV's altitude in centimeters */

  float   vx;                     /*!< UAV's estimated linear velocity */
  float   vy;                     /*!< UAV's estimated linear velocity */
  float   vz;                     /*!< UAV's estimated linear velocity */

  int    num_frames;
} Navdata_def; 

#endif
