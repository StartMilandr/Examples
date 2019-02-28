#ifndef __mldr124_CORDIC_h
#define __mldr124_CORDIC_h
#include "cm4ikmcu.h"
/* =========================================================================================================================== */
/* ================                                            CRD                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief CRD description (CRD)
  */
#if __ARMCC_VERSION<6000000	
#pragma anon_unions
#endif
typedef struct {                                /*!< (@ 0x400B3000) CRD Structure                                              */
  
  union {
    __IOM uint32_t CTRL;                        /*!< (@ 0x00000000) Registr upravlenija modulem                                */
    
    struct {
      __IOM uint32_t IN_MODE    : 1;            /*!< [0..0] Rezhim povorota: 0 – Povorot vhodnogo vektora (x;y)
                                                     na ugol α. Na vyhode poluchaetsja novyj, povernutyj vektor
                                                     (x;y), ugol α obnuljaetsja 1 – Povorot vhodnogo vektora
                                                     (x;y) do osi OH. Na vyhode poluchaetsja ishodnyj ugol vektora
                                                     α, i dlina ishodnogo vektora v koordinate x (deformirovannoe
                                                     znachenie)                                                                */
      __IM  uint32_t            : 3;
      __IOM uint32_t IN_FORMAT  : 3;            /*!< [6..4] Format rabochih dannyh: 000 – 32 bita, plavajuszaja
                                                     tochka 001 – 16 bit, plavajuszaja tochka 010 – 32 bita,
                                                     celochislennyj rezhim                                                     */
      __IM  uint32_t            : 1;
      __IOM uint32_t CRD_EN     : 1;            /*!< [8..8] Vkljuchenie modulja: 1 – vkljuchit' modul' 0 – vykljuchit'
                                                     modul' Vkljuchenie kontroliruetsja po bitu CRD_RDY (sm.
                                                     statusnyj registr CRD_STATUS)                                             */
      __IM  uint32_t            : 7;
      __IOM uint32_t IN_LVL_VAL : 5;            /*!< [20..16] Uroven' zapolnenija vhodnogo FIFO dlja vyrabotki signala
                                                     IN_FIFO_LVL (sm. statusnyj registr CRD_STATUS). Diapazon
                                                     znachenie [0;31]                                                          */
      __IM  uint32_t            : 3;
      __IOM uint32_t OUT_LVL_VAL : 5;           /*!< [28..24] Uroven' zapolnenija vyhodnogo FIFO dlja vyrabotki signala
                                                     OUT_FIFO_LVL (sm. statusnyj registr CRD_STATUS). Diapazon
                                                     znachenie [0;31]                                                          */
    } CTRL_b;
  } ;
  
  union {
    __IOM uint32_t STATUS;                      /*!< (@ 0x00000004) Registr statusa modulja                                    */
    
    struct {
      __IOM uint32_t CRD_RDY    : 1;            /*!< [0..0] Gotovnost' modulja k rabote: 0 – Modul' ne gotov k
                                                     rabote, vykljuchen 1 – Modul' gotov k rabote, vkljuchen                 */
      __IOM uint32_t IN_PRGR    : 1;            /*!< [1..1] Flag nalichija dannyh v obrabotke, dannyj flag raven
                                                     1 kogda vo vhodnom FIFO est' dannye ili dannye obrabatyvajutsja
                                                     v jadre modulja. Kak tol'ko dannye budut obrabotany i vhodnoe
                                                     FIFO opusteet flag stanovitsja 0                                          */
      __IOM uint32_t OUT_NCLR   : 1;            /*!< [2..2] Flag nalichija ne zabrannyh dannyh, dannyj flag raven
                                                     1 kogda dannye obrabatyvajutsja v jadre modulja ili vyhodnoe
                                                     FIFO ne pusto, po okonchaniju obrabotki i vyborke vseh
                                                     dannyh iz vyhodnogo FIFO flag stanovitsja 0                               */
      __IM  uint32_t            : 1;
      __IOM uint32_t IN_FIFO_EMPTY : 1;         /*!< [4..4] Vhodnoe FIFO pusto, dannyj flag nahodit'sja v 1, kogda
                                                     v FIFO net dannyh                                                         */
      __IOM uint32_t IN_FIFO_FULL : 1;          /*!< [5..5] Vhodnoe FIFO zapolneno, dannyj flag nahoditsja v 1, kogda
                                                     FIFO polnost'ju zapolneno, zapisyvaemye dannye pri vystavlennom
                                                     flage otbrasyvajutsja, pri popytke zapisi vystavljaetsja
                                                     flag IN_FIFO_OVR                                                          */
      __IOM uint32_t IN_FIFO_LVL : 1;           /*!< [6..6] Vo vhodnom FIFO dannyh bol'she zadannogo kolichestva,
                                                     dannyj flag vystavljaetsja v 1 kogda kolichestvo dannyh
                                                     sohranennyh v FIFO bol'she IN_LVL_VAL (sm. kontrol'nyj
                                                     registr CRD_CTRL)                                                         */
      __IOM uint32_t IN_FIFO_OVR : 1;           /*!< [7..7] Vhodnoe FIFO perepolneno. Dannyj flag vystavljaetsja
                                                     v 1 pri popytke zapisi dannyh v zapolnennoe FIFO, kogda
                                                     vystavlen flag IN_FIFO_FULL. Dannye zapisyvaemye v ehtot
                                                     moment otbrasyvajutsja, i dannyj flag vystavljaetsja v
                                                     1. Flag snimaetsja pri udachnoj zapisi v FIFO, to est'
                                                     pri ocherednoj zapisi v ne zapolnennoe FIFO                               */
      __IOM uint32_t OUT_FIFO_EMPTY : 1;        /*!< [8..8] Vyhodnoe FIFO pusto, dannyj flag nahodit'sja v 1, kogda
                                                     v FIFO net dannyh                                                         */
      __IOM uint32_t OUT_FIFO_FULL : 1;         /*!< [9..9] Vyhodnoe FIFO zapolneno, dannyj flag nahoditsja v 1,
                                                     kogda FIFO polnost'ju zapolneno                                           */
      __IOM uint32_t OUT_FIFO_LVL : 1;          /*!< [10..10] V vyhodnom FIFO dannyh bol'she zadannogo kolichestva,
                                                     dannyj flag vystavljaetsja v 1 kogda kolichestvo dannyh
                                                     sohranennyh v FIFO bol'she OUT_LVL_VAL (sm. kontrol'nyj
                                                     registr CRD_CTRL)                                                         */
      __IOM uint32_t OUT_FIFO_OVR : 1;          /*!< [11..11] Popytka chtenija iz pustogo FIFO. Dannyj flag vystavljaetsja
                                                     v 1 pri popytke chtenija dannyh iz pustogo FIFO, kogda
                                                     vystavlen flag OUT_FIFO_EMPTY. Iz FIFO budut schitany proshlye
                                                     dannye, a flag budet vystavlen v 1. Flag snimaetsja pri
                                                     udachnom chtenii iz FIFO, to est' pri ocherednom chtenii
                                                     iz ne pustogo FIFO                                                        */
    } STATUS_b;
  } ;
  
  union {
    __IOM uint32_t INTF;                        /*!< (@ 0x00000008) Registr flagov preryvanij                                  */
    
    struct {
      __IOM uint32_t IN_FIFO_EMPTY_IF : 1;      /*!< [0..0] Vhodnoe FIFO pusto, flag otrazhaet sostojanie bita IN_FIFO_EMPTY
                                                     (sm. statusnyj registr CRD_STATUS), stavit'sja i snimaetsja
                                                     s pojavlenie i snjatiem bita IN_FIFO_EMPTY                                */
      __IOM uint32_t IN_FIFO_NLVL_IF : 1;       /*!< [1..1] Vhodnoe FIFO zapolneno ne vyshe ukazannogo urovnja, flag
                                                     otrazhaet inversiju sostojanija bita IN_FIFO_LVL (sm. statusnyj
                                                     registr CRD_STATUS). Flag v 1 kogda IN_FIFO_LVL v 0 i naoborot            */
      __IOM uint32_t IN_FIFO_NFULL_IF : 1;      /*!< [2..2] Vhodnoe FIFO zapolneno ne polnost'ju, flag otrazhaet
                                                     inversiju sostojanija bita IN_FIFO_FULL (sm. statusnyj
                                                     registr CRD_STATUS). Flag v 1 kogda IN_FIFO_FULL v 0 i
                                                     naoborot                                                                  */
      __IOM uint32_t IN_FIFO_OVR_IF : 1;        /*!< [3..3] Vhodnoe FIFO perepolneno, flag vystavljaetsja pri vozniknovenii
                                                     dannoj situacii, pri pojavlenii bita IN_FIFO_OVR (sm. statusnyj
                                                     registr CRD_STATUS), flag snimaetsja zapis'ju 1 v dannyj
                                                     bit                                                                       */
      __IOM uint32_t OUT_FIFO_NEMPTY_IF : 1;    /*!< [4..4] Vyhodnoe FIFO ne pusto, flag otrazhaet inversiju sostojanija
                                                     bita OUT_FIFO_EMPTY (sm. statusnyj registr CRD_STATUS).
                                                     Flag v 1 kogda OUT_FIFO_EMPTY v 0 i naoborot                              */
      __IOM uint32_t OUT_FIFO_LVL_IF : 1;       /*!< [5..5] Vyhodnoe FIFO zapolneno vyshe zadannogo urovnja, flag
                                                     otrazhaet sostojanie bita OUT_FIFO_LVL (sm. statusnyj registr
                                                     CRD_STATUS), stavit'sja i snimaetsja s pojavlenie i snjatiem
                                                     bita OUT_FIFO_LVL                                                         */
      __IOM uint32_t OUT_FIFO_FULL_IF : 1;      /*!< [6..6] Vyhodnoe FIFO zapolneno polnost'ju, flag otrazhaet sostojanie
                                                     bita OUT_FIFO_FULL (sm. statusnyj registr CRD_STATUS),
                                                     stavit'sja i snimaetsja s pojavlenie i snjatiem bita OUT_FIFO_FULL        */
      __IOM uint32_t OUT_FIFO_OVR_IF : 1;       /*!< [7..7] Proizvedeno chtenie iz pustogo FIFO, flag vystavljaetsja
                                                     pri vozniknovenii dannoj situacii, pri pojavlenii bita
                                                     OUT_FIFO_OVR (sm. statusnyj registr CRD_STATUS), flag snimaetsja
                                                     zapis'ju 1 v dannyj bit                                                   */
      __IOM uint32_t PROC_CMPL_IF : 1;          /*!< [8..8] Obrabotka dannyh zavershena, flag vystavljaetsja po vozniknoveniju
                                                     dannoj situacii, pri snjatii bita IN_PRGR (sm. statusnyj
                                                     registr CRD_STATUS), flag snimaetsja zapis'ju 1 v dannyj
                                                     bit                                                                       */
    } INTF_b;
  } ;
  
  union {
    __IOM uint32_t INTE;                        /*!< (@ 0x0000000C) Registr razreshenija preryvanij                            */
    
    struct {
      __IOM uint32_t IN_FIFO_EMPTY_IE : 1;      /*!< [0..0] Vhodnoe FIFO pusto, flag otrazhaet sostojanie bita IN_FIFO_EMPTY
                                                     (sm. statusnyj registr CRD_STATUS), stavit'sja i snimaetsja
                                                     s pojavlenie i snjatiem bita IN_FIFO_EMPTY                                */
      __IOM uint32_t IN_FIFO_NLVL_IE : 1;       /*!< [1..1] Vhodnoe FIFO zapolneno ne vyshe ukazannogo urovnja, flag
                                                     otrazhaet inversiju sostojanija bita IN_FIFO_LVL (sm. statusnyj
                                                     registr CRD_STATUS). Flag v 1 kogda IN_FIFO_LVL v 0 i naoborot            */
      __IOM uint32_t IN_FIFO_NFULL_IE : 1;      /*!< [2..2] Vhodnoe FIFO zapolneno ne polnost'ju, flag otrazhaet
                                                     inversiju sostojanija bita IN_FIFO_FULL (sm. statusnyj
                                                     registr CRD_STATUS). Flag v 1 kogda IN_FIFO_FULL v 0 i
                                                     naoborot                                                                  */
      __IOM uint32_t IN_FIFO_OVR_IE : 1;        /*!< [3..3] Vhodnoe FIFO perepolneno, flag vystavljaetsja pri vozniknovenii
                                                     dannoj situacii, pri pojavlenii bita IN_FIFO_OVR (sm. statusnyj
                                                     registr CRD_STATUS), flag snimaetsja zapis'ju 1 v dannyj
                                                     bit                                                                       */
      __IOM uint32_t OUT_FIFO_NEMPTY_IE : 1;    /*!< [4..4] Vyhodnoe FIFO ne pusto, flag otrazhaet inversiju sostojanija
                                                     bita OUT_FIFO_EMPTY (sm. statusnyj registr CRD_STATUS).
                                                     Flag v 1 kogda OUT_FIFO_EMPTY v 0 i naoborot                              */
      __IOM uint32_t OUT_FIFO_LVL_IE : 1;       /*!< [5..5] Vyhodnoe FIFO zapolneno vyshe zadannogo urovnja, flag
                                                     otrazhaet sostojanie bita OUT_FIFO_LVL (sm. statusnyj registr
                                                     CRD_STATUS), stavit'sja i snimaetsja s pojavlenie i snjatiem
                                                     bita OUT_FIFO_LVL                                                         */
      __IOM uint32_t OUT_FIFO_FULL_IE : 1;      /*!< [6..6] Vyhodnoe FIFO zapolneno polnost'ju, flag otrazhaet sostojanie
                                                     bita OUT_FIFO_FULL (sm. statusnyj registr CRD_STATUS),
                                                     stavit'sja i snimaetsja s pojavlenie i snjatiem bita OUT_FIFO_FULL        */
      __IOM uint32_t OUT_FIFO_OVR_IE : 1;       /*!< [7..7] Proizvedeno chtenie iz pustogo FIFO, flag vystavljaetsja
                                                     pri vozniknovenii dannoj situacii, pri pojavlenii bita
                                                     OUT_FIFO_OVR (sm. statusnyj registr CRD_STATUS), flag snimaetsja
                                                     zapis'ju 1 v dannyj bit                                                   */
      __IOM uint32_t PROC_CMPL_IE : 1;          /*!< [8..8] Obrabotka dannyh zavershena, flag vystavljaetsja po vozniknoveniju
                                                     dannoj situacii, pri snjatii bita IN_PRGR (sm. statusnyj
                                                     registr CRD_STATUS), flag snimaetsja zapis'ju 1 v dannyj
                                                     bit                                                                       */
    } INTE_b;
  } ;
  __IOM uint32_t  IN_X;                         /*!< (@ 0x00000010) Registr zapisi koordinaty X vektora                        */
  __IOM uint32_t  IN_Y;                         /*!< (@ 0x00000014) Registr zapisi koordinaty Y vektora                        */
  __IOM uint32_t  IN_A;                         /*!< (@ 0x00000018) Registr zapisi znachenija ugla α                          */
  __IOM uint32_t  IN_SEQ;                       /*!< (@ 0x0000001C) Registr posledovatel'noj zapisi                            */
  __IOM uint32_t  OUT_X;                        /*!< (@ 0x00000020) Registr chtenija koordinaty X vektora rezul'tata           */
  __IOM uint32_t  OUT_Y;                        /*!< (@ 0x00000024) Registr chtenija koordinaty Y vektora rezul'tata           */
  __IOM uint32_t  OUT_A;                        /*!< (@ 0x00000028) Registr chtenija znachenija ugla α                        */
  __IOM uint32_t  OUT_SEQ;                      /*!< (@ 0x0000002C) Registr posledovatel'nogo chtenija                         */
  __IOM uint32_t  IN_ADDR;                      /*!< (@ 0x00000030) Registr vybora adresa zapisi                               */
  __IOM uint32_t  OUT_ADDR;                     /*!< (@ 0x00000034) Registr vybora adresa chtenija                             */
} CRD_Type;                                     /*!< Size = 56 (0x38)                                                          */


#define CRD_BASE                    0x400B3000UL
#define CRD                         ((CRD_Type*)               CRD_BASE)

#endif // __mldr124_CORDIC_h
