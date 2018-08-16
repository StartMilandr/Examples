#ifndef SD_CARD_H
#define SD_CARD_H

#include <stdint.h>
#include <stdbool.h>

typedef enum 
{
  SD_Resp_No   = 0,
  SD_Resp_48  = 48,
  SD_Resp_138 = 138,
} SD_ResponceLength;

#define SD_CMD_LEN    48
#define SD_BLOCK_512  512

//  Статус выполнения команды к CD карте
typedef enum 
{
  BRD_SD_CMD_OK,
  BRD_SD_CMD_TimeoutSend,
  BRD_SD_CMD_TimeoutRead,
} BRD_SD_CMD_Result;

//  Временные задержки при работе с картой
typedef struct
{
  uint32_t SD_SendCMD_Timout_ms;        //  100 ms
  uint32_t SD_BeforeRead_Delay_ms;      //    2 ms
  uint32_t SD_ReadResp_Timout_ms;       //  100 ms
  uint32_t SD_ChangeRate_Timout_ms;     //    2 ms
  uint32_t SD_ReadBlock_Timout_ms;      //  100 ms
  uint32_t SD_WriteBlock_Timout_ms;     // 1000 ms
} BRD_SDDrv_Timeouts;

//  Параметры зависят от текущей тактовой частоты

//    Значения для SD_CLK_BRG_Detect и SD_CLK_BRG_Transfer
#define SDIO_BRG_div4     1
#define SDIO_BRG_div8     2
#define SDIO_BRG_div16    3
#define SDIO_BRG_div32    4
#define SDIO_BRG_div64    5
#define SDIO_BRG_div128   6
#define SDIO_BRG_div256   7

typedef struct  
{
  uint32_t        SysTimerPeriod_1ms;         // Value to get 1ms timer period    
  uint32_t        SD_CLK_BRG_Detect;          // HCLK/BRG = CLK_freq    100KHz.. 400KHz
  uint32_t        SD_CLK_BRG_Transfer;        // HCLK/BRG = CLK_freq < 25MHz 
  
  uint32_t        SD_PowerOn_Delay_ms;        //     2 ms  
  uint32_t        SD_WaitStatus_Timout_ms;    //   500 ms  
  uint32_t        SD_Erase_Timout_ms;         // 30000 ms  
} BRD_SD_ClockCfg;

/* ----- MMC/SDC command ----- */
#define CMD0  (0)             // GO_IDLE_STATE
#define CMD1  (1)             // SEND_OP_COND (MMC)
#define CMD2  (2)             // ALL_SEND_CID
#define CMD3  (3)             // SEND_RELATIVE_ADDR
#define ACMD6 (6|0x80)        // SET_BUS_WIDTH (SDC)
#define CMD7  (7)             // SELECT_CARD
#define CMD8  (8)             // SEND_IF_COND
#define CMD9  (9)             // SEND_CSD
#define CMD10 (10)            // SEND_CID
#define CMD12 (12)            // STOP_TRANSMISSION
#define CMD13 (13)            // SEND_STATUS
#define ACMD13  (13|0x80)     // SD_STATUS (SDC)
#define CMD16 (16)            // SET_BLOCKLEN
#define CMD17 (17)            // READ_SINGLE_BLOCK
#define CMD18 (18)            // READ_MULTIPLE_BLOCK
#define CMD23 (23)            // SET_BLK_COUNT (MMC)
#define ACMD23  (23|0x80)     // SET_WR_BLK_ERASE_COUNT (SDC)
#define CMD24 (24)            // WRITE_BLOCK
#define CMD25 (25)            // WRITE_MULTIPLE_BLOCK
#define CMD32 (32)            // ERASE_ER_BLK_START
#define CMD33 (33)            // ERASE_ER_BLK_END
#define CMD38 (38)            // ERASE
#define ACMD41  (41|0x80)     // SEND_OP_COND (SDC)
#define CMD55 (55)            // APP_CMD

/* Card type flags (CardType) */
#define CT_MMC    0x01    /* MMC ver 3 */
#define CT_SD1    0x02    /* SD ver 1 */
#define CT_SD2    0x04    /* SD ver 2 */
#define CT_SDC    (CT_SD1|CT_SD2) /* SD */
#define CT_BLOCK  0x08    /* Block addressing */


// ------------------  Command code for disk_ioctrl funсtion --------------
typedef enum
{
/* Generic ioctl command (defined for FatFs) */
  SDC_CTRL_SYNC			    = 0,	/* Flush disk cache (for write functions) */
  SDC_GET_SECTOR_COUNT	= 1,	/* Get media size (for only f_mkfs()) */
  SDC_GET_SECTOR_SIZE		= 2,	/* Get sector size (for multiple sector size (_MAX_SS >= 1024)) */
  SDC_GET_BLOCK_SIZE		= 3,	/* Get erase block size (for only f_mkfs()) */
  SDC_CTRL_ERASE_SECTOR	= 4,	/* Force erased a block of sectors (for only _USE_ERASE) */

/* Generic ioctl command */
  SDC_CTRL_POWER			  = 5,	/* Get/Set power status */
  SDC_CTRL_LOCK			    = 6,	/* Lock/Unlock media removal */
  SDC_CTRL_EJECT			  = 7,	/* Eject media */

/* MMC/SDC specific ioctl command */
  SDC_MMC_GET_TYPE		  = 10,	/* Get card type */
  SDC_MMC_GET_CSD			  = 11,	/* Get CSD */
  SDC_MMC_GET_CID			  = 12,	/* Get CID */
  SDC_MMC_GET_OCR			  = 13,	/* Get OCR */
  SDC_MMC_GET_SDSTAT		= 14,	/* Get SD status */

/* ATA/CF specific ioctl command */
  SDC_ATA_GET_REV			  = 20,	/* Get F/W revision */
  SDC_ATA_GET_MODEL		  = 21,	/* Get model name */
  SDC_ATA_GET_SN			  = 22,	/* Get serial number */

/* NAND specific ioctl command */
  SDC_NAND_FORMAT			  = 30	/* Create physical format */
} SD_Card_IO_Ctrl;

//=============   Card Responces ===================
typedef enum
{
  SD_State_Idle      = 0,
  SD_State_Ready     = 1,
  SD_State_Ident     = 2,
  SD_State_Standby   = 3,
  SD_State_Transf    = 4,
  SD_State_Data      = 5,
  SD_State_Receive   = 6,
  SD_State_Prog      = 7,
  SD_State_Dis       = 8,
  SD_State_Reserved1 = 9,
  SD_State_Reserved2 = 10,
  SD_State_Reserved3 = 11,
  SD_State_Reserved4 = 12,
  SD_State_Reserved5 = 13,
  SD_State_Reserved6 = 14,
  SD_State_Reserved7 = 15,
} SD_State;


#define SD_State_Offs_Status            9
#define SD_State_Msk_Idle              ((uint32_t)(SD_State_Idle     << SD_State_Offs_Status))
#define SD_State_Msk_Ready             ((uint32_t)(SD_State_Ready    << SD_State_Offs_Status))
#define SD_State_Msk_Ident             ((uint32_t)(SD_State_Ident    << SD_State_Offs_Status))
#define SD_State_Msk_Standby           ((uint32_t)(SD_State_Standby  << SD_State_Offs_Status))
#define SD_State_Msk_Transf            ((uint32_t)(SD_State_Transf   << SD_State_Offs_Status))
#define SD_State_Msk_Data              ((uint32_t)(SD_State_Data     << SD_State_Offs_Status))
#define SD_State_Msk_Receive           ((uint32_t)(SD_State_Receive  << SD_State_Offs_Status))
#define SD_State_Msk_Prog              ((uint32_t)(SD_State_Prog     << SD_State_Offs_Status))
#define SD_State_Msk_Disable           ((uint32_t)(SD_State_Dis      << SD_State_Offs_Status))

#define SD_State_Offs_ReadyForData      8
#define SD_State_Msk_ReadyForData      ((uint32_t)(1 << SD_State_Offs_ReadyForData))

typedef struct 
{
  uint32_t SD_R1_Reserv1        : 3;   //  0..2 bits
  bool     SD_R1_AKE_SEQ_ERR    : 1;   //  3 bit
  uint32_t SD_R1_Reserv2        : 1;   //  4 bit
  bool     SD_R1_APP_CMD        : 1;   //  5 bit
  uint32_t SD_R1_Reserv3        : 2;   //  6..7 bits
  bool     SD_R1_ReadyForData   : 1;   //  8 bit
  SD_State SD_R1_State          : 4;   //  9..12 bit
  bool     SD_R1_EraseReset     : 1;   //  13 bit
  bool     SD_R1_ECCDisable     : 1;   //  14 bit
  bool     SD_R1_WPEraseSkip    : 1;   //  15 bit
  bool     SD_R1_CSDOverwriteErr: 1;   //  16 bit
  uint32_t SD_R1_Reserv4        : 2;   //  17..18 bits
  bool     SD_R1_Error          : 1;   //  19 bit
  bool     SD_R1_CCError        : 1;   //  20 bit
  bool     SD_R1_ECCFailed      : 1;   //  21 bit
  bool     SD_R1_IllCommand     : 1;   //  22 bit
  bool     SD_R1_CRCErr         : 1;   //  23 bit
  bool     SD_R1_LockFailed     : 1;   //  24 bit
  bool     SD_R1_IsLocked       : 1;   //  25 bit
  bool     SD_R1_WPViolation    : 1;   //  26 bit
  bool     SD_R1_EraseParam     : 1;   //  27 bit
  bool     SD_R1_EraseSeqErr    : 1;   //  28 bit
  bool     SD_R1_BlockLenErr    : 1;   //  29 bit  
  bool     SD_R1_AddrErr        : 1;   //  30 bit
  bool     SD_R1_OutOfRange     : 1;   //  31 bit
} SD_RespR1_Bits;

typedef union 
{
    uint32_t        value;
    SD_RespR1_Bits  bits;
} SD_ResponceR1;

#define SD_RespR1_All_ErrorsMask    0xFDF90000
#define SD_RespR1_RW_ErrorsMask     0xC0580000

typedef struct 
{
  uint32_t SD_R3_Reserv1        : 15;  //  0..14 bits
  bool     SD_R3_2V7_2V8        : 1;   //  15 bit
  bool     SD_R3_2V8_2V9        : 1;   //  16 bit
  bool     SD_R3_2V9_3V0        : 1;   //  17 bit
  bool     SD_R3_3V0_3V1        : 1;   //  18 bit
  bool     SD_R3_3V1_3V2        : 1;   //  19 bit
  bool     SD_R3_3V2_3V3        : 1;   //  20 bit
  bool     SD_R3_3V3_3V4        : 1;   //  21 bit
  bool     SD_R3_3V4_3V5        : 1;   //  22 bit
  bool     SD_R3_3V5_3V6        : 1;   //  23 bit
  uint32_t SD_R3_Reserv2        : 6;   //  24..29 bits
  bool     SD_R3_CCS            : 1;   //  30 bit  - Card Capacity Status
  bool     SD_R3_Ready          : 1;   //  31 bit  - Готовность после инициализации
} SD_RespR3_Bits;

typedef union 
{
    uint32_t        value;
    SD_RespR3_Bits  bits;
} SD_ResponceR3;


















#endif //SD_CARD_H

