#include "__cf_SailingYachtModel.h"
#include <math.h>
#include "SailingYachtModel_acc.h"
#include "SailingYachtModel_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T u ;
B_SailingYachtModel_T * _rtB ; P_SailingYachtModel_T * _rtP ;
DW_SailingYachtModel_T * _rtDW ; _rtDW = ( ( DW_SailingYachtModel_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_SailingYachtModel_T * )
ssGetDefaultParam ( S ) ) ; _rtB = ( ( B_SailingYachtModel_T * )
_ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { memcpy ( & _rtB
-> B_0_0_0 [ 0 ] , & _rtP -> P_0 [ 0 ] , sizeof ( real_T ) << 3U ) ; } if (
_rtDW -> Integrator_IWORK . IcNeedsLoading ) { { int_T i1 ; real_T * xc = & (
( X_SailingYachtModel_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE [ 0
] ; const real_T * u1 = ( ( B_SailingYachtModel_T * ) _ssGetBlockIO ( S ) )
-> B_0_0_0 ; for ( i1 = 0 ; i1 < 8 ; i1 ++ ) { xc [ i1 ] = u1 [ i1 ] ; } } }
{ int_T i1 ; real_T * y0 = ( ( B_SailingYachtModel_T * ) _ssGetBlockIO ( S )
) -> B_0_1_0 ; real_T * xc = & ( ( X_SailingYachtModel_T * ) ssGetContStates
( S ) ) -> Integrator_CSTATE [ 0 ] ; for ( i1 = 0 ; i1 < 8 ; i1 ++ ) { y0 [
i1 ] = xc [ i1 ] ; } } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
ssCallAccelRunBlock ( S , 0 , 2 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_0_3_0 =
_rtP -> P_1 ; } _rtB -> B_0_5_0 [ 0 ] = _rtB -> B_0_1_0 [ 1 ] ; _rtB ->
B_0_5_0 [ 1 ] = _rtB -> B_0_3_0 ; _rtB -> B_0_5_0 [ 2 ] = _rtP -> P_2 * _rtB
-> B_0_1_0 [ 0 ] ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_0_6_0 [ 0 ]
= _rtP -> P_3 [ 0 ] ; _rtB -> B_0_6_0 [ 1 ] = _rtP -> P_3 [ 1 ] ; _rtB ->
B_0_6_0 [ 2 ] = _rtP -> P_3 [ 2 ] ; _rtB -> B_0_7_0 [ 0 ] = _rtP -> P_4 *
_rtB -> B_0_6_0 [ 0 ] ; _rtB -> B_0_7_0 [ 1 ] = _rtP -> P_4 * _rtB -> B_0_6_0
[ 1 ] ; _rtB -> B_0_7_0 [ 2 ] = _rtP -> P_4 * _rtB -> B_0_6_0 [ 2 ] ; _rtB ->
B_0_8_0 = _rtP -> P_5 ; } _rtB -> B_0_10_0 [ 0 ] = _rtB -> B_0_7_0 [ 0 ] ;
_rtB -> B_0_10_0 [ 1 ] = _rtB -> B_0_7_0 [ 1 ] ; _rtB -> B_0_10_0 [ 2 ] =
_rtB -> B_0_7_0 [ 2 ] ; _rtB -> B_0_10_0 [ 3 ] = _rtB -> B_0_1_0 [ 3 ] - _rtB
-> B_0_8_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_0_11_0 [ 0 ] =
_rtP -> P_6 [ 0 ] ; _rtB -> B_0_11_0 [ 1 ] = _rtP -> P_6 [ 1 ] ; _rtB ->
B_0_11_0 [ 2 ] = _rtP -> P_6 [ 2 ] ; } _rtB -> B_0_12_0 [ 0 ] = _rtB ->
B_0_11_0 [ 0 ] ; _rtB -> B_0_12_0 [ 1 ] = _rtB -> B_0_11_0 [ 1 ] ; _rtB ->
B_0_12_0 [ 2 ] = _rtB -> B_0_11_0 [ 2 ] ; _rtB -> B_0_12_0 [ 3 ] = _rtB ->
B_0_1_0 [ 2 ] ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_0_13_0 = _rtP
-> P_7 ; } _rtB -> B_0_14_0 = _rtB -> B_0_1_0 [ 3 ] - _rtB -> B_0_13_0 ; u =
_rtP -> P_8 * _rtB -> B_0_14_0 ; if ( u >= _rtP -> P_9 ) { _rtB -> B_0_16_0 =
_rtP -> P_9 ; } else if ( u <= _rtP -> P_10 ) { _rtB -> B_0_16_0 = _rtP ->
P_10 ; } else { _rtB -> B_0_16_0 = u ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) {
_rtB -> B_0_17_0 = _rtP -> P_11 ; } ssCallAccelRunBlock ( S , 0 , 18 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_0_19_0 [ 0 ] = _rtB -> B_0_6_0 [ 0 ] ; _rtB
-> B_0_19_0 [ 1 ] = _rtB -> B_0_6_0 [ 1 ] ; _rtB -> B_0_19_0 [ 2 ] = _rtB ->
B_0_6_0 [ 2 ] ; _rtB -> B_0_19_0 [ 3 ] = _rtB -> B_0_18_0 [ 8 ] ; _rtB ->
B_0_20_0 [ 0 ] = _rtB -> B_0_6_0 [ 0 ] ; _rtB -> B_0_20_0 [ 1 ] = _rtB ->
B_0_6_0 [ 1 ] ; _rtB -> B_0_20_0 [ 2 ] = _rtB -> B_0_6_0 [ 2 ] ; _rtB ->
B_0_20_0 [ 3 ] = _rtB -> B_0_16_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB
-> B_0_22_0 [ 0 ] = _rtP -> P_13 * _rtP -> P_12 [ 0 ] ; _rtB -> B_0_22_0 [ 1
] = _rtP -> P_13 * _rtP -> P_12 [ 1 ] ; _rtB -> B_0_22_0 [ 2 ] = _rtP -> P_13
* _rtP -> P_12 [ 2 ] ; _rtB -> B_0_23_0 = _rtP -> P_14 ; } _rtB -> B_0_24_0 [
0 ] = _rtB -> B_0_22_0 [ 0 ] ; _rtB -> B_0_24_0 [ 1 ] = _rtB -> B_0_22_0 [ 1
] ; _rtB -> B_0_24_0 [ 2 ] = _rtB -> B_0_22_0 [ 2 ] ; _rtB -> B_0_24_0 [ 3 ]
= _rtB -> B_0_23_0 ; ssCallAccelRunBlock ( S , 0 , 25 , SS_CALL_MDL_OUTPUTS )
; if ( ssIsSampleHit ( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 0 , 26 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 27 ,
SS_CALL_MDL_OUTPUTS ) ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_SailingYachtModel_T *
_rtB ; _rtB = ( ( B_SailingYachtModel_T * ) _ssGetBlockIO ( S ) ) ; ( (
DW_SailingYachtModel_T * ) ssGetRootDWork ( S ) ) -> Integrator_IWORK .
IcNeedsLoading = 0 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_SailingYachtModel_T * _rtB ;
_rtB = ( ( B_SailingYachtModel_T * ) _ssGetBlockIO ( S ) ) ; { { int_T i1 ;
const real_T * u0 = & ( ( B_SailingYachtModel_T * ) _ssGetBlockIO ( S ) ) ->
B_0_18_0 [ 0 ] ; real_T * xdot = & ( ( XDot_SailingYachtModel_T * ) ssGetdX (
S ) ) -> Integrator_CSTATE [ 0 ] ; for ( i1 = 0 ; i1 < 8 ; i1 ++ ) { xdot [
i1 ] = u0 [ i1 ] ; } } } } static void mdlInitializeSizes ( SimStruct * S ) {
ssSetChecksumVal ( S , 0 , 3925420884U ) ; ssSetChecksumVal ( S , 1 ,
2639654178U ) ; ssSetChecksumVal ( S , 2 , 2230930457U ) ; ssSetChecksumVal (
S , 3 , 3010131885U ) ; { mxArray * slVerStructMat = NULL ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.1" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_SailingYachtModel_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_SailingYachtModel_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_SailingYachtModel_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & SailingYachtModel_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof (
real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S ) { }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
