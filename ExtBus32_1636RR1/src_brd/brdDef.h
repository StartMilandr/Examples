#ifndef _BRD_DEF
#define _BRD_DEF

#include "brdSelect.h"

#if defined ( USE_BOARD_VE_91 )  || defined ( USE_BOARD_VE_94 )

  #include "brdDef_VE91.h"
   
#elif defined ( USE_BOARD_VE_92 )

  #include "brdDef_VE92.h"

#elif defined ( USE_BOARD_VE_93 )

  #include "brdDef_VE93.h"

#elif defined ( USE_BOARD_VE_1 )

  #include "brdDef_VE1.h"

#elif defined ( USE_BOARD_VE_3 )

  #include "brdDef_VE3.h"

#elif defined ( USE_BOARD_VE_4 ) 

  #include "brdDef_VE4.h"

#elif defined ( USE_BOARD_VE_8 )

  #include "brdDef_VE8.h"
  
#elif defined ( USE_BOARD_VC1 )

  #include "brdDef_VC1.h"

#endif

#endif // _BRD_DEF
