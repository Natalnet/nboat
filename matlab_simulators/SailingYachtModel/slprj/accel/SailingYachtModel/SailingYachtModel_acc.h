#include "__cf_SailingYachtModel.h"
#ifndef RTW_HEADER_SailingYachtModel_acc_h_
#define RTW_HEADER_SailingYachtModel_acc_h_
#ifndef SailingYachtModel_acc_COMMON_INCLUDES_
#define SailingYachtModel_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "SailingYachtModel_acc_types.h"
typedef struct { real_T B_0_0_0 [ 8 ] ; real_T B_0_1_0 [ 8 ] ; real_T B_0_3_0
; real_T B_0_5_0 [ 3 ] ; real_T B_0_6_0 [ 3 ] ; real_T B_0_7_0 [ 3 ] ; real_T
B_0_8_0 ; real_T B_0_10_0 [ 4 ] ; real_T B_0_11_0 [ 3 ] ; real_T B_0_12_0 [ 4
] ; real_T B_0_13_0 ; real_T B_0_14_0 ; real_T B_0_16_0 ; real_T B_0_17_0 ;
real_T B_0_18_0 [ 9 ] ; real_T B_0_19_0 [ 4 ] ; real_T B_0_20_0 [ 4 ] ;
real_T B_0_22_0 [ 3 ] ; real_T B_0_23_0 ; real_T B_0_24_0 [ 4 ] ; }
B_SailingYachtModel_T ; typedef struct { void * ToWorkspace_PWORK ; void *
VRSailingYachtAnimation_PWORK [ 16 ] ; struct { void * LoggedData ; }
delta_rt_PWORK ; struct { void * LoggedData ; } psi_tildet_PWORK ; struct {
int_T IcNeedsLoading ; } Integrator_IWORK ; char pad_Integrator_IWORK [ 4 ] ;
} DW_SailingYachtModel_T ; typedef struct { real_T Integrator_CSTATE [ 8 ] ;
} X_SailingYachtModel_T ; typedef struct { real_T Integrator_CSTATE [ 8 ] ; }
XDot_SailingYachtModel_T ; typedef struct { boolean_T Integrator_CSTATE [ 8 ]
; } XDis_SailingYachtModel_T ; struct P_SailingYachtModel_T_ { real_T P_0 [ 8
] ; real_T P_1 ; real_T P_2 ; real_T P_3 [ 3 ] ; real_T P_4 ; real_T P_5 ;
real_T P_6 [ 3 ] ; real_T P_7 ; real_T P_8 ; real_T P_9 ; real_T P_10 ;
real_T P_11 ; real_T P_12 [ 3 ] ; real_T P_13 ; real_T P_14 ; } ; extern
P_SailingYachtModel_T SailingYachtModel_rtDefaultP ;
#endif
