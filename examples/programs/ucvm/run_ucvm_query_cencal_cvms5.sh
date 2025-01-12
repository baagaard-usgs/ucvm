#!/bin/bash

if [ -z "$UCVM_INSTALL_PATH" ]; then
  echo "Need to set UCVM_INSTALL_PATH to run >" ${0##*/} 
  exit
fi
source $UCVM_INSTALL_PATH/conf/ucvm_env.sh

BIN_DIR=${UCVM_INSTALL_PATH}/bin
CONF_DIR=${UCVM_INSTALL_PATH}/conf
TEST_DIR=${UCVM_INSTALL_PATH}/tests/inputs
MODEL=cencal,cvms5

expect=$(mktemp) || exit 1
result=$(mktemp) || (trap 'rm -f "$expect"'; exit 1)

${BIN_DIR}/ucvm_query -m ${MODEL} -f ${CONF_DIR}/ucvm.conf < ${TEST_DIR}/test_latlonsonly_cencal_cvms_or_cvms5.txt > $result 2>&1 

cat > $expect << EOF_EXPECTED_RESULT
Using Geo Depth coordinates as default mode.
 -122.5000    35.0000      0.000  -4074.558    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.4000    35.0000      0.000  -4068.468    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.3000    35.0000      0.000  -4027.267    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.2000    35.0000      0.000  -3994.342    180.000      cvms5   5480.363   3148.167   2574.152       none      0.000      0.000      0.000      crust   5480.363   3148.167   2574.152
 -122.1000    35.0000      0.000  -3964.319    180.000      cvms5   5480.549   3148.439   2574.243       none      0.000      0.000      0.000      crust   5480.549   3148.439   2574.243
 -122.0000    35.0000      0.000  -3434.060    180.000      cvms5   5476.729   3145.111   2573.134       none      0.000      0.000      0.000      crust   5476.729   3145.111   2573.134
 -121.9000    35.0000      0.000  -2494.269    180.000      cvms5   5476.802   3145.111   2573.135       none      0.000      0.000      0.000      crust   5476.802   3145.111   2573.135
 -121.8000    35.0000      0.000  -2173.783    180.000      cvms5   5484.173   3151.094   2575.129       none      0.000      0.000      0.000      crust   5484.173   3151.094   2575.129
 -121.7000    35.0000      0.000  -1694.723    180.000      cvms5   5487.293   3153.348   2575.883       none      0.000      0.000      0.000      crust   5487.293   3153.348   2575.883
 -121.6000    35.0000      0.000  -1263.512    180.000      cvms5   5483.289   3149.994   2574.762       none      0.000      0.000      0.000      crust   5483.289   3149.994   2574.762
 -121.5000    35.0000      0.000   -696.014    180.000      cvms5   5470.201   3137.091   2570.478       none      0.000      0.000      0.000      crust   5470.201   3137.091   2570.478
 -121.4000    35.0000      0.000   -434.866    180.000      cvms5   5454.511   3115.799   2563.520       none      0.000      0.000      0.000      crust   5454.511   3115.799   2563.520
 -121.3000    35.0000      0.000   -559.783    180.000      cvms5   5454.409   3111.503   2562.132       none      0.000      0.000      0.000      crust   5454.409   3111.503   2562.132
 -121.2000    35.0000      0.000   -581.379    180.000      cvms5   5474.709   3126.054   2566.854       none      0.000      0.000      0.000      crust   5474.709   3126.054   2566.854
 -121.1000    35.0000      0.000   -534.246    180.000      cvms5   5419.580   3055.855   2544.659       none      0.000      0.000      0.000      crust   5419.580   3055.855   2544.659
 -121.0000    35.0000      0.000   -417.122    180.000      cvms5   5352.945   2949.932   2513.913       none      0.000      0.000      0.000      crust   5352.945   2949.932   2513.913
 -122.5000    35.1000      0.000  -4044.357    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.4000    35.1000      0.000  -3828.272    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.3000    35.1000      0.000  -3915.641    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.2000    35.1000      0.000  -3949.172    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.1000    35.1000      0.000  -3874.029    180.000      cvms5   5478.202   3146.325   2573.538       none      0.000      0.000      0.000      crust   5478.202   3146.325   2573.538
 -122.0000    35.1000      0.000  -3511.613    180.000     cencal   2670.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2670.000   1120.000   2650.000
 -121.9000    35.1000      0.000  -2538.444    180.000     cencal   2500.000    990.000   2650.000       none      0.000      0.000      0.000      crust   2500.000    990.000   2650.000
 -121.8000    35.1000      0.000  -1881.238    180.000     cencal   2490.000    980.000   2650.000       none      0.000      0.000      0.000      crust   2490.000    980.000   2650.000
 -121.7000    35.1000      0.000  -1448.021    180.000      cvms5   5486.060   3152.636   2575.645       none      0.000      0.000      0.000      crust   5486.060   3152.636   2575.645
 -121.6000    35.1000      0.000  -1052.060    180.000      cvms5   5473.283   3142.065   2572.123       none      0.000      0.000      0.000      crust   5473.283   3142.065   2572.123
 -121.5000    35.1000      0.000   -514.123    180.000      cvms5   5461.863   3132.221   2568.874       none      0.000      0.000      0.000      crust   5461.863   3132.221   2568.874
 -121.4000    35.1000      0.000   -504.541    180.000      cvms5   5481.522   3148.064   2574.118       none      0.000      0.000      0.000      crust   5481.522   3148.064   2574.118
 -121.3000    35.1000      0.000   -629.249    180.000      cvms5   5507.478   3165.025   2579.815       none      0.000      0.000      0.000      crust   5507.478   3165.025   2579.815
 -121.2000    35.1000      0.000   -584.848    180.000      cvms5   5448.139   3084.422   2553.513       none      0.000      0.000      0.000      crust   5448.139   3084.422   2553.513
 -121.1000    35.1000      0.000   -528.504    180.000      cvms5   5346.227   2962.374   2517.357       none      0.000      0.000      0.000      crust   5346.227   2962.374   2517.357
 -121.0000    35.1000      0.000   -376.499    180.000      cvms5   5284.087   2872.718   2493.504       none      0.000      0.000      0.000      crust   5284.087   2872.718   2493.504
 -122.5000    35.2000      0.000  -3602.417    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.4000    35.2000      0.000  -3786.994    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.3000    35.2000      0.000  -3851.427    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.2000    35.2000      0.000  -3831.823    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.1000    35.2000      0.000  -3744.307    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.0000    35.2000      0.000  -2816.880    180.000     cencal   2600.000   1070.000   2650.000       none      0.000      0.000      0.000      crust   2600.000   1070.000   2650.000
 -121.9000    35.2000      0.000  -2087.016    180.000     cencal   2560.000   1030.000   2650.000       none      0.000      0.000      0.000      crust   2560.000   1030.000   2650.000
 -121.8000    35.2000      0.000  -1614.312    180.000     cencal   2590.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2590.000   1050.000   2650.000
 -121.7000    35.2000      0.000  -1192.336    180.000     cencal   2520.000   1000.000   2650.000       none      0.000      0.000      0.000      crust   2520.000   1000.000   2650.000
 -121.6000    35.2000      0.000   -808.536    180.000      cvms5   5460.925   3131.448   2568.620       none      0.000      0.000      0.000      crust   5460.925   3131.448   2568.620
 -121.5000    35.2000      0.000   -633.593    180.000      cvms5   5471.568   3140.147   2571.488       none      0.000      0.000      0.000      crust   5471.568   3140.147   2571.488
 -121.4000    35.2000      0.000   -682.493    180.000      cvms5   5519.029   3180.684   2585.153       none      0.000      0.000      0.000      crust   5519.029   3180.684   2585.153
 -121.3000    35.2000      0.000   -644.526    180.000      cvms5   5492.730   3141.267   2571.859       none      0.000      0.000      0.000      crust   5492.730   3141.267   2571.859
 -121.2000    35.2000      0.000   -572.189    180.000      cvms5   5363.200   3006.755   2530.002       none      0.000      0.000      0.000      crust   5363.200   3006.755   2530.002
 -121.1000    35.2000      0.000   -492.491    180.000      cvms5   5202.100   2830.962   2483.140       none      0.000      0.000      0.000      crust   5202.100   2830.962   2483.140
 -121.0000    35.2000      0.000   -285.676    180.000      cvms5   5140.987   2736.172   2461.276       none      0.000      0.000      0.000      crust   5140.987   2736.172   2461.276
 -122.5000    35.3000      0.000  -3660.885    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.4000    35.3000      0.000  -3789.899    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.3000    35.3000      0.000  -3821.120    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.2000    35.3000      0.000  -3783.935    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.1000    35.3000      0.000  -3438.073    180.000     cencal   2480.000    960.000   2650.000       none      0.000      0.000      0.000      crust   2480.000    960.000   2650.000
 -122.0000    35.3000      0.000  -2622.578    180.000     cencal   2480.000    970.000   2650.000       none      0.000      0.000      0.000      crust   2480.000    970.000   2650.000
 -121.9000    35.3000      0.000  -1959.513    180.000     cencal   2610.000   1070.000   2650.000       none      0.000      0.000      0.000      crust   2610.000   1070.000   2650.000
 -121.8000    35.3000      0.000  -1536.277    180.000     cencal   2580.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2580.000   1050.000   2650.000
 -121.7000    35.3000      0.000  -1053.400    180.000     cencal   2560.000   1030.000   2650.000       none      0.000      0.000      0.000      crust   2560.000   1030.000   2650.000
 -121.6000    35.3000      0.000   -899.066    180.000     cencal   2580.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2580.000   1050.000   2650.000
 -121.5000    35.3000      0.000   -809.800    180.000     cencal   2550.000   1020.000   2650.000       none      0.000      0.000      0.000      crust   2550.000   1020.000   2650.000
 -121.4000    35.3000      0.000   -783.087    180.000      cvms5   5511.117   3164.555   2579.656       none      0.000      0.000      0.000      crust   5511.117   3164.555   2579.656
 -121.3000    35.3000      0.000   -593.427    180.000      cvms5   5448.171   3100.478   2558.597       none      0.000      0.000      0.000      crust   5448.171   3100.478   2558.597
 -121.2000    35.3000      0.000   -495.067    180.000      cvms5   5290.217   2948.071   2513.401       none      0.000      0.000      0.000      crust   5290.217   2948.071   2513.401
 -121.1000    35.3000      0.000   -346.597    180.000      cvms5   5169.265   2812.573   2478.721       none      0.000      0.000      0.000      crust   5169.265   2812.573   2478.721
 -121.0000    35.3000      0.000   -158.206    180.000      cvms5   5281.729   2866.215   2491.859       none      0.000      0.000      0.000      crust   5281.729   2866.215   2491.859
 -122.5000    35.4000      0.000  -3720.743    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.4000    35.4000      0.000  -3778.298    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.3000    35.4000      0.000  -3765.013    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.2000    35.4000      0.000  -3628.499    180.000     cencal   2670.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2670.000   1120.000   2650.000
 -122.1000    35.4000      0.000  -2811.225    180.000     cencal   2540.000   1020.000   2650.000       none      0.000      0.000      0.000      crust   2540.000   1020.000   2650.000
 -122.0000    35.4000      0.000  -1939.219    180.000     cencal   2530.000   1010.000   2650.000       none      0.000      0.000      0.000      crust   2530.000   1010.000   2650.000
 -121.9000    35.4000      0.000  -1708.366    180.000     cencal   2560.000   1030.000   2650.000       none      0.000      0.000      0.000      crust   2560.000   1030.000   2650.000
 -121.8000    35.4000      0.000  -1241.834    180.000     cencal   2570.000   1040.000   2650.000       none      0.000      0.000      0.000      crust   2570.000   1040.000   2650.000
 -121.7000    35.4000      0.000  -1212.805    180.000     cencal   2590.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2590.000   1050.000   2650.000
 -121.6000    35.4000      0.000  -1054.717    180.000     cencal   2480.000    970.000   2650.000       none      0.000      0.000      0.000      crust   2480.000    970.000   2650.000
 -121.5000    35.4000      0.000   -920.026    180.000     cencal   2540.000   1010.000   2650.000       none      0.000      0.000      0.000      crust   2540.000   1010.000   2650.000
 -121.4000    35.4000      0.000   -720.268    180.000     cencal   2530.000   1010.000   2650.000       none      0.000      0.000      0.000      crust   2530.000   1010.000   2650.000
 -121.3000    35.4000      0.000   -514.763    180.000     cencal   2540.000   1020.000   2650.000       none      0.000      0.000      0.000      crust   2540.000   1020.000   2650.000
 -121.2000    35.4000      0.000   -379.348    180.000      cvms5   5372.049   3013.470   2531.965       none      0.000      0.000      0.000      crust   5372.049   3013.470   2531.965
 -121.1000    35.4000      0.000   -259.038    180.000      cvms5   5476.538   3089.169   2555.008       none      0.000      0.000      0.000      crust   5476.538   3089.169   2555.008
 -121.0000    35.4000      0.000    -96.968    180.000      cvms5   5676.811   3212.971   2596.394       none      0.000      0.000      0.000      crust   5676.811   3212.971   2596.394
 -122.5000    35.5000      0.000  -3665.187    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.4000    35.5000      0.000  -3736.112    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.3000    35.5000      0.000  -3670.010    180.000     cencal   2580.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2580.000   1050.000   2650.000
 -122.2000    35.5000      0.000  -2959.641    180.000     cencal   2630.000   1090.000   2650.000       none      0.000      0.000      0.000      crust   2630.000   1090.000   2650.000
 -122.1000    35.5000      0.000  -2093.440    180.000     cencal   2480.000    970.000   2650.000       none      0.000      0.000      0.000      crust   2480.000    970.000   2650.000
 -122.0000    35.5000      0.000  -1502.429    180.000     cencal   2530.000   1000.000   2650.000       none      0.000      0.000      0.000      crust   2530.000   1000.000   2650.000
 -121.9000    35.5000      0.000  -1144.643    180.000     cencal   2470.000    960.000   2650.000       none      0.000      0.000      0.000      crust   2470.000    960.000   2650.000
 -121.8000    35.5000      0.000  -1080.726    180.000     cencal   2560.000   1040.000   2650.000       none      0.000      0.000      0.000      crust   2560.000   1040.000   2650.000
 -121.7000    35.5000      0.000  -1025.111    180.000     cencal   2510.000    990.000   2650.000       none      0.000      0.000      0.000      crust   2510.000    990.000   2650.000
 -121.6000    35.5000      0.000   -942.796    180.000     cencal   2480.000    970.000   2650.000       none      0.000      0.000      0.000      crust   2480.000    970.000   2650.000
 -121.5000    35.5000      0.000   -824.070    180.000     cencal   2520.000   1000.000   2650.000       none      0.000      0.000      0.000      crust   2520.000   1000.000   2650.000
 -121.4000    35.5000      0.000   -639.955    180.000     cencal   2490.000    980.000   2650.000       none      0.000      0.000      0.000      crust   2490.000    980.000   2650.000
 -121.3000    35.5000      0.000   -463.153    180.000     cencal   2650.000   1110.000   2650.000       none      0.000      0.000      0.000      crust   2650.000   1110.000   2650.000
 -121.2000    35.5000      0.000   -294.146    180.000     cencal   2580.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2580.000   1050.000   2650.000
 -121.1000    35.5000      0.000    -68.506    180.000     cencal   2620.000   1090.000   2650.000       none      0.000      0.000      0.000      crust   2620.000   1090.000   2650.000
 -121.0000    35.5000      0.000    167.331    733.400      cvms5   5728.912   3329.356   2639.555       none      0.000      0.000      0.000      crust   5728.912   3329.356   2639.555
 -122.5000    35.6000      0.000  -3602.426    180.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000       none      0.000      0.000      0.000
 -122.4000    35.6000      0.000  -3606.074    180.000     cencal   2620.000   1080.000   2650.000       none      0.000      0.000      0.000      crust   2620.000   1080.000   2650.000
 -122.3000    35.6000      0.000  -3588.284    180.000     cencal   2500.000    980.000   2650.000       none      0.000      0.000      0.000      crust   2500.000    980.000   2650.000
 -122.2000    35.6000      0.000  -2705.541    180.000     cencal   2600.000   1070.000   2650.000       none      0.000      0.000      0.000      crust   2600.000   1070.000   2650.000
 -122.1000    35.6000      0.000  -1734.997    180.000     cencal   2500.000    980.000   2650.000       none      0.000      0.000      0.000      crust   2500.000    980.000   2650.000
 -122.0000    35.6000      0.000  -1158.371    180.000     cencal   2490.000    970.000   2650.000       none      0.000      0.000      0.000      crust   2490.000    970.000   2650.000
 -121.9000    35.6000      0.000   -994.001    180.000     cencal   2670.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2670.000   1120.000   2650.000
 -121.8000    35.6000      0.000   -972.440    180.000     cencal   2590.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2590.000   1050.000   2650.000
 -121.7000    35.6000      0.000   -906.205    180.000     cencal   2590.000   1060.000   2650.000       none      0.000      0.000      0.000      crust   2590.000   1060.000   2650.000
 -121.6000    35.6000      0.000   -801.768    180.000     cencal   2560.000   1030.000   2650.000       none      0.000      0.000      0.000      crust   2560.000   1030.000   2650.000
 -121.5000    35.6000      0.000   -664.477    180.000     cencal   2660.000   1110.000   2650.000       none      0.000      0.000      0.000      crust   2660.000   1110.000   2650.000
 -121.4000    35.6000      0.000   -430.702    180.000     cencal   2660.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2660.000   1120.000   2650.000
 -121.3000    35.6000      0.000   -170.247    180.000     cencal   2610.000   1070.000   2650.000       none      0.000      0.000      0.000      crust   2610.000   1070.000   2650.000
 -121.2000    35.6000      0.000    -51.518    180.000     cencal   2660.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2660.000   1120.000   2650.000
 -121.1000    35.6000      0.000     26.809    445.721     cencal   1530.000    350.000   2670.000       none      0.000      0.000      0.000      crust   1530.000    350.000   2670.000
 -121.0000    35.6000      0.000    479.933    733.400     cencal   1830.000    500.000   2670.000       none      0.000      0.000      0.000      crust   1830.000    500.000   2670.000
 -122.5000    35.7000      0.000  -3509.279    180.000     cencal   2570.000   1040.000   2650.000       none      0.000      0.000      0.000      crust   2570.000   1040.000   2650.000
 -122.4000    35.7000      0.000  -3546.689    180.000     cencal   2660.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2660.000   1120.000   2650.000
 -122.3000    35.7000      0.000  -3509.567    180.000     cencal   2660.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2660.000   1120.000   2650.000
 -122.2000    35.7000      0.000  -2016.826    180.000     cencal   2510.000    990.000   2650.000       none      0.000      0.000      0.000      crust   2510.000    990.000   2650.000
 -122.1000    35.7000      0.000  -1332.427    180.000     cencal   2670.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2670.000   1120.000   2650.000
 -122.0000    35.7000      0.000  -1162.173    180.000     cencal   2520.000   1000.000   2650.000       none      0.000      0.000      0.000      crust   2520.000   1000.000   2650.000
 -121.9000    35.7000      0.000  -1078.812    180.000     cencal   2580.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2580.000   1050.000   2650.000
 -121.8000    35.7000      0.000   -998.253    180.000     cencal   2560.000   1030.000   2650.000       none      0.000      0.000      0.000      crust   2560.000   1030.000   2650.000
 -121.7000    35.7000      0.000   -883.623    180.000     cencal   2590.000   1060.000   2650.000       none      0.000      0.000      0.000      crust   2590.000   1060.000   2650.000
 -121.6000    35.7000      0.000   -713.057    180.000     cencal   2520.000   1000.000   2650.000       none      0.000      0.000      0.000      crust   2520.000   1000.000   2650.000
 -121.5000    35.7000      0.000   -571.129    180.000     cencal   2490.000    970.000   2650.000       none      0.000      0.000      0.000      crust   2490.000    970.000   2650.000
 -121.4000    35.7000      0.000   -115.261    180.000     cencal   2530.000   1010.000   2650.000       none      0.000      0.000      0.000      crust   2530.000   1010.000   2650.000
 -121.3000    35.7000      0.000      6.775    374.108     cencal   1760.000    460.000   2670.000       none      0.000      0.000      0.000      crust   1760.000    460.000   2670.000
 -121.2000    35.7000      0.000    112.337    733.400     cencal   1530.000    350.000   2670.000       none      0.000      0.000      0.000      crust   1530.000    350.000   2670.000
 -121.1000    35.7000      0.000    947.993    518.900     cencal   1890.000    540.000   2670.000       none      0.000      0.000      0.000      crust   1890.000    540.000   2670.000
 -121.0000    35.7000      0.000    363.420    733.400     cencal   1680.000    420.000   2670.000       none      0.000      0.000      0.000      crust   1680.000    420.000   2670.000
 -122.5000    35.8000      0.000  -3323.368    180.000     cencal   2640.000   1100.000   2650.000       none      0.000      0.000      0.000      crust   2640.000   1100.000   2650.000
 -122.4000    35.8000      0.000  -3371.569    180.000     cencal   2540.000   1010.000   2650.000       none      0.000      0.000      0.000      crust   2540.000   1010.000   2650.000
 -122.3000    35.8000      0.000  -2624.736    180.000     cencal   2550.000   1030.000   2650.000       none      0.000      0.000      0.000      crust   2550.000   1030.000   2650.000
 -122.2000    35.8000      0.000  -1420.446    180.000     cencal   2650.000   1110.000   2650.000       none      0.000      0.000      0.000      crust   2650.000   1110.000   2650.000
 -122.1000    35.8000      0.000  -1208.310    180.000     cencal   2510.000    990.000   2650.000       none      0.000      0.000      0.000      crust   2510.000    990.000   2650.000
 -122.0000    35.8000      0.000  -1098.382    180.000     cencal   2550.000   1020.000   2650.000       none      0.000      0.000      0.000      crust   2550.000   1020.000   2650.000
 -121.9000    35.8000      0.000  -1178.523    180.000     cencal   2650.000   1110.000   2650.000       none      0.000      0.000      0.000      crust   2650.000   1110.000   2650.000
 -121.8000    35.8000      0.000  -1040.159    180.000     cencal   2500.000    990.000   2650.000       none      0.000      0.000      0.000      crust   2500.000    990.000   2650.000
 -121.7000    35.8000      0.000   -860.963    180.000     cencal   2630.000   1100.000   2650.000       none      0.000      0.000      0.000      crust   2630.000   1100.000   2650.000
 -121.6000    35.8000      0.000   -654.867    180.000     cencal   2630.000   1090.000   2650.000       none      0.000      0.000      0.000      crust   2630.000   1090.000   2650.000
 -121.5000    35.8000      0.000   -347.077    180.000     cencal   2470.000    960.000   2650.000       none      0.000      0.000      0.000      crust   2470.000    960.000   2650.000
 -121.4000    35.8000      0.000    -59.861    180.000     cencal   1970.000    590.000   2670.000       none      0.000      0.000      0.000      crust   1970.000    590.000   2670.000
 -121.3000    35.8000      0.000    388.553    733.400     cencal   1590.000    380.000   2670.000       none      0.000      0.000      0.000      crust   1590.000    380.000   2670.000
 -121.2000    35.8000      0.000    655.345    571.600     cencal   1800.000    490.000   2670.000       none      0.000      0.000      0.000      crust   1800.000    490.000   2670.000
 -121.1000    35.8000      0.000    310.487    733.400     cencal   1740.000    450.000   2670.000       none      0.000      0.000      0.000      crust   1740.000    450.000   2670.000
 -121.0000    35.8000      0.000    427.572    385.100     cencal   1990.000    610.000   2670.000       none      0.000      0.000      0.000      crust   1990.000    610.000   2670.000
 -122.5000    35.9000      0.000  -3250.451    180.000     cencal   2490.000    970.000   2650.000       none      0.000      0.000      0.000      crust   2490.000    970.000   2650.000
 -122.4000    35.9000      0.000  -3091.451    180.000     cencal   2540.000   1010.000   2650.000       none      0.000      0.000      0.000      crust   2540.000   1010.000   2650.000
 -122.3000    35.9000      0.000  -2366.521    180.000     cencal   2640.000   1100.000   2650.000       none      0.000      0.000      0.000      crust   2640.000   1100.000   2650.000
 -122.2000    35.9000      0.000  -2030.920    180.000     cencal   2620.000   1090.000   2650.000       none      0.000      0.000      0.000      crust   2620.000   1090.000   2650.000
 -122.1000    35.9000      0.000  -1744.583    180.000     cencal   2510.000    990.000   2650.000       none      0.000      0.000      0.000      crust   2510.000    990.000   2650.000
 -122.0000    35.9000      0.000  -1451.392    180.000     cencal   2660.000   1120.000   2650.000       none      0.000      0.000      0.000      crust   2660.000   1120.000   2650.000
 -121.9000    35.9000      0.000  -1199.465    180.000     cencal   2530.000   1000.000   2650.000       none      0.000      0.000      0.000      crust   2530.000   1000.000   2650.000
 -121.8000    35.9000      0.000  -1016.485    180.000     cencal   2510.000    990.000   2650.000       none      0.000      0.000      0.000      crust   2510.000    990.000   2650.000
 -121.7000    35.9000      0.000   -845.739    180.000     cencal   2640.000   1100.000   2650.000       none      0.000      0.000      0.000      crust   2640.000   1100.000   2650.000
 -121.6000    35.9000      0.000   -600.649    180.000     cencal   2530.000   1010.000   2650.000       none      0.000      0.000      0.000      crust   2530.000   1010.000   2650.000
 -121.5000    35.9000      0.000   -109.969    180.000     cencal   2580.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2580.000   1050.000   2650.000
 -121.4000    35.9000      0.000    527.026    733.400     cencal   1900.000    540.000   2670.000       none      0.000      0.000      0.000      crust   1900.000    540.000   2670.000
 -121.3000    35.9000      0.000    564.373    733.400     cencal   1710.000    440.000   2670.000       none      0.000      0.000      0.000      crust   1710.000    440.000   2670.000
 -121.2000    35.9000      0.000    380.419    733.400     cencal   1700.000    430.000   2670.000       none      0.000      0.000      0.000      crust   1700.000    430.000   2670.000
 -121.1000    35.9000      0.000    307.845    444.000     cencal   1740.000    450.000   2670.000       none      0.000      0.000      0.000      crust   1740.000    450.000   2670.000
 -121.0000    35.9000      0.000    346.040    444.000     cencal   1850.000    520.000   2670.000       none      0.000      0.000      0.000      crust   1850.000    520.000   2670.000
 -122.5000    36.0000      0.000  -3116.774    180.000     cencal   2520.000   1000.000   2650.000       none      0.000      0.000      0.000      crust   2520.000   1000.000   2650.000
 -122.4000    36.0000      0.000  -2920.894    180.000     cencal   2650.000   1110.000   2650.000       none      0.000      0.000      0.000      crust   2650.000   1110.000   2650.000
 -122.3000    36.0000      0.000  -2024.892    180.000     cencal   2540.000   1020.000   2650.000       none      0.000      0.000      0.000      crust   2540.000   1020.000   2650.000
 -122.2000    36.0000      0.000  -1665.604    180.000     cencal   2580.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2580.000   1050.000   2650.000
 -122.1000    36.0000      0.000  -1463.736    180.000     cencal   2650.000   1110.000   2650.000       none      0.000      0.000      0.000      crust   2650.000   1110.000   2650.000
 -122.0000    36.0000      0.000  -1265.152    180.000     cencal   2580.000   1050.000   2650.000       none      0.000      0.000      0.000      crust   2580.000   1050.000   2650.000
 -121.9000    36.0000      0.000  -1246.280    180.000     cencal   2600.000   1070.000   2650.000       none      0.000      0.000      0.000      crust   2600.000   1070.000   2650.000
 -121.8000    36.0000      0.000  -1138.978    180.000     cencal   2630.000   1090.000   2650.000       none      0.000      0.000      0.000      crust   2630.000   1090.000   2650.000
 -121.7000    36.0000      0.000   -893.256    180.000     cencal   2540.000   1020.000   2650.000       none      0.000      0.000      0.000      crust   2540.000   1020.000   2650.000
 -121.6000    36.0000      0.000   -252.009    180.000     cencal   1570.000    370.000   2670.000       none      0.000      0.000      0.000      crust   1570.000    370.000   2670.000
 -121.5000    36.0000      0.000    140.531    733.400     cencal   1600.000    380.000   2670.000       none      0.000      0.000      0.000      crust   1600.000    380.000   2670.000
 -121.4000    36.0000      0.000    637.736    710.100     cencal   1680.000    420.000   2670.000       none      0.000      0.000      0.000      crust   1680.000    420.000   2670.000
 -121.3000    36.0000      0.000    556.417    710.100     cencal   1760.000    460.000   2670.000       none      0.000      0.000      0.000      crust   1760.000    460.000   2670.000
 -121.2000    36.0000      0.000    362.040    444.000     cencal   1630.000    390.000   2670.000       none      0.000      0.000      0.000      crust   1630.000    390.000   2670.000
 -121.1000    36.0000      0.000    514.570    385.100     cencal   1670.000    410.000   2670.000       none      0.000      0.000      0.000      crust   1670.000    410.000   2670.000
 -121.0000    36.0000      0.000    366.540    385.100     cencal   1520.000    350.000   2670.000       none      0.000      0.000      0.000      crust   1520.000    350.000   2670.000
EOF_EXPECTED_RESULT

echo "Running examples_programs_ucvm ucvm_query_cencal_cvms5"
cp $result oo
diff $result $expect > ooo
if diff $result $expect > /dev/null 2>&1
then
  echo [SUCCESS]
else
  echo [FAILURE]
fi

trap 'rm -f "$expect" "$result"' exit



