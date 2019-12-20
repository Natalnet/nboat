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
#endif
#include "SailingYachtModel_acc_types.h"
typedef struct { real_T B_0_0_0 [ 8 ] ; real_T B_0_3_0 ; real_T B_0_4_0 ;
real_T B_0_7_0 ; real_T B_0_8_0 ; real_T B_0_9_0 ; real_T B_0_13_0 ; real_T
B_0_14_0 [ 9 ] ; real_T B_0_1_0 [ 8 ] ; real_T B_0_5_0 [ 2 ] ; real_T
B_0_10_0 ; } B_SailingYachtModel_T ; typedef struct { void *
ToWorkspace_PWORK ; void * ToWorkspace1_PWORK ; void * ToWorkspace3_PWORK ;
struct { int_T IcNeedsLoading ; } Integrator_IWORK ; int_T
rudderanglesaturation_MODE ; } DW_SailingYachtModel_T ; typedef struct {
real_T Integrator_CSTATE [ 8 ] ; } X_SailingYachtModel_T ; typedef struct {
real_T Integrator_CSTATE [ 8 ] ; } XDot_SailingYachtModel_T ; typedef struct
{ boolean_T Integrator_CSTATE [ 8 ] ; } XDis_SailingYachtModel_T ; typedef
struct { real_T Integrator_CSTATE [ 8 ] ; } CStateAbsTol_SailingYachtModel_T
; typedef struct { real_T rudderanglesaturation_UprLim_ZC ; real_T
rudderanglesaturation_LwrLim_ZC ; } ZCV_SailingYachtModel_T ; typedef struct
{ ZCSigState rudderanglesaturation_UprLim_ZCE ; ZCSigState
rudderanglesaturation_LwrLim_ZCE ; } PrevZCX_SailingYachtModel_T ; struct
P_SailingYachtModel_T_ { real_T P_0 [ 8 ] ; real_T P_1 ; real_T P_2 ; real_T
P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; } ; extern
P_SailingYachtModel_T SailingYachtModel_rtDefaultP ;
#endif
