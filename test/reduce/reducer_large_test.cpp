// Copyright (c) 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "source/reduce/reducer.h"
#include "test/reduce/reduce_test_util.h"

namespace spvtools {
namespace reduce {
namespace {

class EventuallyInteresting {
 public:
  explicit EventuallyInteresting(uint32_t always_interesting_after)
      : always_interesting_after_(always_interesting_after), count_(0) {}

  bool IsInteresting() {
    if (count_ == 0) {
      ++count_;
      return true;
    }
    if (count_ < always_interesting_after_) {
      ++count_;
      return false;
    }
    return true;
  }

 private:
  const uint32_t always_interesting_after_;
  uint32_t count_;
};
/*
TEST(ReducerTest, FuzzOne) {
  const std::string original = R"(
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %4 "main" %73 %106
               OpExecutionMode %4 OriginUpperLeft
               OpSource ESSL 310
               OpName %4 "main"
               OpName %27 "buf0"
               OpMemberName %27 0 "injectionSwitch"
               OpName %29 ""
               OpName %47 "buf2"
               OpMemberName %47 0 "GLF_live3resolution"
               OpName %49 ""
               OpName %73 "_GLF_color"
               OpName %106 "gl_FragCoord"
               OpName %133 "buf1"
               OpMemberName %133 0 "resolution"
               OpName %135 ""
               OpName %187 "data"
               OpName %1869 "GLF_live3data"
               OpName %2228 "GLF_live3data"
               OpMemberDecorate %27 0 Offset 0
               OpDecorate %27 Block
               OpDecorate %29 DescriptorSet 0
               OpDecorate %29 Binding 0
               OpMemberDecorate %47 0 Offset 0
               OpDecorate %47 Block
               OpDecorate %49 DescriptorSet 0
               OpDecorate %49 Binding 2
               OpDecorate %73 Location 0
               OpDecorate %106 BuiltIn FragCoord
               OpMemberDecorate %133 0 Offset 0
               OpDecorate %133 Block
               OpDecorate %135 DescriptorSet 0
               OpDecorate %135 Binding 1
               OpDecorate %190 RelaxedPrecision
               OpDecorate %198 RelaxedPrecision
               OpDecorate %395 RelaxedPrecision
               OpDecorate %442 RelaxedPrecision
               OpDecorate %1115 RelaxedPrecision
               OpDecorate %1117 RelaxedPrecision
               OpDecorate %1804 RelaxedPrecision
               OpDecorate %4762 RelaxedPrecision
               OpDecorate %1887 RelaxedPrecision
               OpDecorate %31 RelaxedPrecision
               OpDecorate %1905 RelaxedPrecision
               OpDecorate %1912 RelaxedPrecision
               OpDecorate %1967 RelaxedPrecision
               OpDecorate %2017 RelaxedPrecision
               OpDecorate %2030 RelaxedPrecision
               OpDecorate %2032 RelaxedPrecision
               OpDecorate %2032 RelaxedPrecision
               OpDecorate %31 RelaxedPrecision
               OpDecorate %31 RelaxedPrecision
               OpDecorate %197 RelaxedPrecision
               OpDecorate %2032 RelaxedPrecision
               OpDecorate %2237 RelaxedPrecision
               OpDecorate %2249 RelaxedPrecision
               OpDecorate %2250 RelaxedPrecision
               OpDecorate %2010 RelaxedPrecision
               OpDecorate %2272 RelaxedPrecision
               OpDecorate %2275 RelaxedPrecision
               OpDecorate %2278 RelaxedPrecision
               OpDecorate %2336 RelaxedPrecision
               OpDecorate %2340 RelaxedPrecision
               OpDecorate %2341 RelaxedPrecision
               OpDecorate %2342 RelaxedPrecision
               OpDecorate %2353 RelaxedPrecision
               OpDecorate %2354 RelaxedPrecision
               OpDecorate %2010 RelaxedPrecision
               OpDecorate %2418 RelaxedPrecision
               OpDecorate %31 RelaxedPrecision
               OpDecorate %197 RelaxedPrecision
               OpDecorate %4181 RelaxedPrecision
               OpDecorate %4233 RelaxedPrecision
               OpDecorate %4234 RelaxedPrecision
               OpDecorate %4244 RelaxedPrecision
               OpDecorate %4245 RelaxedPrecision
               OpDecorate %4468 RelaxedPrecision
          %2 = OpTypeVoid
          %3 = OpTypeFunction %2
          %6 = OpTypeFloat 32
          %7 = OpTypePointer Function %6
          %8 = OpTypeBool
         %22 = OpTypeVector %6 4
         %26 = OpTypeVector %6 2
         %27 = OpTypeStruct %26
         %28 = OpTypePointer Uniform %27
         %29 = OpVariable %28 Uniform
         %30 = OpTypeInt 32 1
         %31 = OpConstant %30 0
         %32 = OpTypeInt 32 0
         %33 = OpConstant %32 0
         %34 = OpTypePointer Uniform %6
         %45 = OpConstant %32 1
         %47 = OpTypeStruct %26
         %48 = OpTypePointer Uniform %47
         %49 = OpVariable %48 Uniform
         %52 = OpConstant %6 2
         %69 = OpConstantFalse %8
         %72 = OpTypePointer Output %22
         %73 = OpVariable %72 Output
         %75 = OpConstant %6 8.39999962
         %86 = OpConstant %6 1
         %87 = OpConstant %6 0
         %96 = OpConstant %6 -5.5999999
        %105 = OpTypePointer Input %22
        %106 = OpVariable %105 Input
        %107 = OpTypePointer Input %6
        %133 = OpTypeStruct %26
        %134 = OpTypePointer Uniform %133
        %135 = OpVariable %134 Uniform
        %136 = OpTypePointer Uniform %26
        %170 = OpConstant %6 5.9000001
        %182 = OpConstant %30 10
        %184 = OpConstant %32 10
        %185 = OpTypeArray %6 %184
        %186 = OpTypePointer Function %185
        %197 = OpConstant %30 1
        %206 = OpConstant %30 9
        %215 = OpConstant %6 -429.423004
        %216 = OpConstant %6 4.69999981
        %217 = OpConstant %6 -3.70000005
        %218 = OpConstant %6 95.2300034
        %219 = OpConstantComposite %22 %215 %216 %217 %218
        %224 = OpConstant %6 0.600000024
        %231 = OpConstant %6 0.899999976
        %247 = OpConstant %30 5
        %250 = OpConstant %6 10
        %273 = OpConstant %6 56.7999992
        %274 = OpConstant %6 -811.284973
        %275 = OpConstant %6 -453.970001
        %276 = OpConstantComposite %22 %273 %273 %274 %275
        %282 = OpConstant %6 9.89999962
        %283 = OpConstant %6 -5047.12891
        %284 = OpConstant %6 6.5999999
        %285 = OpConstant %6 8.19999981
        %286 = OpConstantComposite %22 %282 %283 %284 %285
        %302 = OpConstant %6 -3542.03198
        %303 = OpConstant %6 85.4800034
        %304 = OpConstant %6 3271.4563
        %305 = OpConstant %6 -8949.08789
        %306 = OpConstantComposite %22 %302 %303 %304 %305
        %334 = OpConstant %6 -1.79999995
        %353 = OpConstant %6 -7.9000001
        %361 = OpConstant %6 8.10000038
        %370 = OpConstant %6 2480.22949
        %371 = OpConstant %6 421340.969
        %372 = OpConstant %6 402863.062
        %373 = OpConstant %6 -29270.1816
        %374 = OpConstantComposite %22 %370 %371 %372 %373
        %386 = OpConstant %6 3.4564009e+09
        %387 = OpConstant %6 313336224
        %388 = OpConstant %6 -1288412.5
        %389 = OpConstant %6 -3171447.5
        %390 = OpConstantComposite %22 %386 %387 %388 %389
        %408 = OpConstant %6 667.192017
        %409 = OpConstant %6 3484.80884
        %410 = OpConstant %6 4585.1377
        %411 = OpConstant %6 766.448975
        %412 = OpConstantComposite %22 %408 %409 %410 %411
        %475 = OpConstant %6 713.882019
        %476 = OpConstant %6 82.9300003
        %477 = OpConstant %6 -16.5799999
        %478 = OpConstantComposite %22 %475 %476 %224 %477
        %479 = OpConstant %6 41.0499992
        %480 = OpConstant %6 -9.5
        %481 = OpConstant %6 -8162.50732
        %482 = OpConstant %6 9235.83301
        %483 = OpConstantComposite %22 %479 %480 %481 %482
        %490 = OpConstant %6 -91.6299973
        %491 = OpConstant %6 5933.18066
        %492 = OpConstant %6 3888.53296
        %493 = OpConstant %6 -4.5
        %494 = OpConstantComposite %22 %490 %491 %492 %493
        %511 = OpConstant %6 2.20000005
        %528 = OpConstant %30 100
        %536 = OpConstant %30 20
        %572 = OpConstant %30 120
        %595 = OpConstantTrue %8
        %602 = OpConstant %6 -0x1.8p+128
        %618 = OpConstant %6 -0.5
        %630 = OpConstant %30 140
        %670 = OpConstant %6 -7.0999999
        %679 = OpConstant %30 160
        %707 = OpConstant %6 4.19999981
        %714 = OpConstant %30 180
        %729 = OpConstant %6 -6
        %731 = OpConstant %6 -6.5999999
        %732 = OpConstant %6 -8
        %742 = OpConstant %6 -3.4000001
        %761 = OpConstant %30 40
        %852 = OpConstant %6 5.69999981
        %889 = OpConstant %6 -1
        %895 = OpConstant %6 8.5
        %906 = OpConstant %6 -0.100000001
        %927 = OpConstant %6 -2.0999999
        %964 = OpTypeVector %8 4
        %994 = OpConstant %6 1.20000005
        %995 = OpConstant %6 1786.66895
        %996 = OpConstantComposite %22 %994 %353 %231 %995
       %1002 = OpConstant %6 5.80000019
       %1053 = OpConstant %6 -9928.7959
       %1054 = OpConstant %6 34.0299988
       %1055 = OpConstant %6 -1.20000005
       %1056 = OpConstantComposite %22 %1053 %1054 %1055 %334
       %1089 = OpConstant %6 -1.13817677e+09
       %1090 = OpConstant %6 -2.7104428e+11
       %1091 = OpConstant %6 9.92742605e+09
       %1092 = OpConstant %6 7.94885095e+11
       %1093 = OpConstantComposite %22 %1089 %1090 %1091 %1092
       %1103 = OpConstant %6 -25786532
       %1104 = OpConstant %6 678706.688
       %1105 = OpConstant %6 5175642.5
       %1106 = OpConstant %6 435821.219
       %1107 = OpConstantComposite %22 %1103 %1104 %1105 %1106
       %1151 = OpConstant %6 0.800000012
       %1152 = OpConstant %6 6.4000001
       %1156 = OpTypeVector %30 2
       %1211 = OpConstant %30 80
       %1296 = OpConstant %6 6
       %1434 = OpConstant %6 -0.400000006
       %1595 = OpConstant %6 -3.9000001
       %1671 = OpConstant %6 -559.072021
       %1686 = OpConstant %6 230.44928
       %1687 = OpConstant %6 0.0788643509
       %1688 = OpConstant %6 2.13091493
       %1689 = OpConstant %6 -158.932465
       %1690 = OpConstantComposite %22 %1686 %1687 %1688 %1689
       %1711 = OpConstant %6 744.479004
       %1712 = OpConstant %6 -821.825012
       %1713 = OpConstantComposite %22 %1711 %1712 %927 %285
       %1731 = OpConstant %6 20.5
       %1732 = OpConstant %6 -8533.47559
       %1733 = OpConstantComposite %22 %1731 %742 %1732 %618
       %1743 = OpConstant %6 -5.9000001
       %1755 = OpConstant %6 9450.57031
       %1764 = OpConstant %6 8206.55273
       %1765 = OpConstant %6 -336.707001
       %1766 = OpConstantComposite %22 %1764 %1151 %1765 %731
       %1769 = OpConstant %30 -64378
       %1815 = OpConstant %6 0.5
       %1826 = OpConstant %6 0.516481102
       %1827 = OpConstant %6 0.0332018062
       %1828 = OpConstant %6 0.0853110254
       %1829 = OpConstant %6 0.3771846
       %1830 = OpConstantComposite %22 %1826 %1827 %1828 %1829
       %1848 = OpConstant %6 912.705017
       %1849 = OpConstant %6 -5215.13379
       %1850 = OpConstantComposite %22 %1848 %170 %511 %1849
       %1863 = OpConstant %6 -42.2099991
       %1864 = OpConstant %6 -3.5999999
       %1865 = OpConstant %6 -63.8899994
       %1866 = OpConstant %6 6379.14355
       %1867 = OpConstantComposite %22 %1863 %1864 %1865 %1866
       %1943 = OpConstant %6 -64
       %1944 = OpConstant %6 5876
       %1945 = OpConstant %6 -579
       %1946 = OpConstantComposite %22 %1943 %889 %1944 %1945
       %1961 = OpConstant %6 -0.300000012
       %1962 = OpConstant %6 -1.60000002
       %1963 = OpConstant %6 98.0599976
       %1964 = OpConstant %6 50.4099998
       %1965 = OpConstantComposite %22 %1961 %1962 %1963 %1964
       %1977 = OpConstant %6 -6533.68018
       %1978 = OpConstant %6 -6341.41357
       %1979 = OpConstant %6 -6.80000019
       %1980 = OpConstantComposite %22 %1977 %1978 %1979 %1743
       %1994 = OpConstant %6 2.9000001
       %1995 = OpConstant %6 714.504028
       %1996 = OpConstant %6 3
       %1997 = OpConstant %6 -56.1699982
       %1998 = OpConstantComposite %22 %1994 %1995 %1996 %1997
       %2008 = OpConstantComposite %22 %602 %602 %602 %602
       %2010 = OpConstant %30 16734
       %2017 = OpConstant %30 80206
       %2023 = OpConstant %6 988.695984
       %2024 = OpConstant %6 62.4000015
       %2025 = OpConstantComposite %22 %75 %75 %2023 %2024
       %2088 = OpConstant %6 -3.20000005
       %2132 = OpConstant %6 9.80000019
       %2180 = OpConstant %6 -965.56897
       %2181 = OpConstant %6 697.947021
       %2182 = OpConstant %6 -27.9400005
       %2183 = OpConstant %6 826.880005
       %2184 = OpConstantComposite %22 %2180 %2181 %2182 %2183
       %2191 = OpConstant %6 -754.640015
       %2192 = OpConstant %6 443.207001
       %2193 = OpConstant %6 8160.7168
       %2194 = OpConstantComposite %22 %2191 %2192 %1434 %2193
       %2196 = OpConstant %6 -231.335999
       %2197 = OpConstant %6 -7
       %2198 = OpConstantComposite %22 %2196 %361 %994 %2197
       %2452 = OpConstant %6 6.80000019
       %2453 = OpConstant %6 -6581.60303
       %2454 = OpConstant %6 51.5800018
       %2455 = OpConstantComposite %22 %2452 %2453 %2454 %670
       %2523 = OpConstant %6 2.29999995
       %2524 = OpConstant %6 72
       %2525 = OpConstantComposite %22 %707 %2523 %2524 %729
       %2607 = OpConstant %6 0.00999999978
       %2728 = OpConstant %6 2.4000001
       %2926 = OpConstant %6 694.672974
       %2927 = OpConstantComposite %22 %732 %732 %732 %2926
       %2957 = OpConstant %6 8011.97363
       %2958 = OpConstant %6 -3268.37427
       %2959 = OpConstant %6 510.910004
       %2960 = OpConstant %6 56.5499992
       %2961 = OpConstantComposite %22 %2957 %2958 %2959 %2960
       %2967 = OpConstant %6 68.5899963
       %2968 = OpConstant %6 -1851.28369
       %2969 = OpConstant %6 1.60000002
       %2970 = OpConstantComposite %22 %2967 %2132 %2968 %2969
       %2979 = OpConstant %6 -6350.67529
       %2980 = OpConstant %6 -2.70000005
       %2981 = OpConstant %6 -2886.21802
       %2982 = OpConstant %6 85.1600037
       %2983 = OpConstantComposite %22 %2979 %2980 %2981 %2982
       %2994 = OpConstant %6 5.30223718e+09
       %2995 = OpConstant %6 1.56579482e+09
       %2996 = OpConstant %6 -598372224
       %2997 = OpConstant %6 733208512
       %2998 = OpConstantComposite %22 %2994 %2995 %2996 %2997
       %3093 = OpConstant %6 -29.6900005
       %3094 = OpConstant %6 9.60000038
       %3095 = OpConstantComposite %22 %96 %361 %3093 %3094
       %3096 = OpConstant %6 88.3899994
       %3097 = OpConstant %6 -876.89502
       %3098 = OpConstantComposite %22 %285 %3096 %1595 %3097
       %3134 = OpConstant %6 -0.903252363
       %3135 = OpConstant %6 -0.202964693
       %3136 = OpConstant %6 0.0393057764
       %3137 = OpConstant %6 -0.376026005
       %3138 = OpConstantComposite %22 %3134 %3135 %3136 %3137
       %3146 = OpConstant %6 53.5200005
       %3151 = OpConstant %6 -27.1299992
       %3153 = OpConstantComposite %22 %52 %52 %86 %86
       %3166 = OpConstant %6 -6914.4165
       %3204 = OpConstant %6 -7579.19434
       %3205 = OpConstant %6 -538.606995
       %3206 = OpConstantComposite %26 %3204 %3205
       %3259 = OpConstant %6 342.022003
       %3287 = OpConstant %6 0.733281255
       %3288 = OpConstant %6 0.728188097
       %3289 = OpConstant %6 0.557907641
       %3290 = OpConstant %6 1.52067983
       %3291 = OpConstantComposite %22 %3287 %3288 %3289 %3290
       %3304 = OpConstant %6 -330.308014
       %3305 = OpConstant %6 -0.800000012
       %3306 = OpConstantComposite %22 %3304 %895 %3305 %2728
       %3307 = OpConstant %6 -7.5999999
       %3308 = OpConstant %6 78.6100006
       %3309 = OpConstant %6 7237.50879
       %3310 = OpConstantComposite %22 %1815 %3307 %3308 %3309
       %3318 = OpConstantComposite %22 %1815 %895 %3308 %3309
       %3328 = OpConstant %6 -795.588989
       %3329 = OpConstant %6 832.585022
       %3330 = OpConstant %6 117.203003
       %3331 = OpConstant %6 -5
       %3332 = OpConstantComposite %22 %3328 %3329 %3330 %3331
       %3415 = OpConstant %30 60
       %3727 = OpConstant %6 -9144.70215
       %3731 = OpConstant %6 -3.29999995
       %3732 = OpConstant %6 544.411011
       %3734 = OpConstant %6 452.122986
       %3740 = OpConstant %6 -16.0599995
       %3751 = OpConstant %6 -971.773987
       %3752 = OpConstant %6 -23.0400009
       %3753 = OpConstant %6 738.101013
       %3754 = OpConstant %6 -4.69999981
       %3755 = OpConstantComposite %22 %3751 %3752 %3753 %3754
       %3778 = OpConstant %6 5408.23926
       %3779 = OpConstant %6 -741.745972
       %3780 = OpConstant %6 -45.3199997
       %3781 = OpConstantComposite %22 %3778 %3779 %3780 %852
       %3798 = OpConstant %6 -136.399002
       %3819 = OpConstant %6 -1.39999998
       %3820 = OpConstant %6 -4866.70068
       %3821 = OpConstantComposite %22 %1152 %2088 %3819 %3820
       %3980 = OpConstant %6 928.000977
       %3981 = OpConstant %6 -1171.61975
       %3982 = OpConstant %6 6123.19922
       %3983 = OpConstantComposite %22 %3980 %3981 %906 %3982
       %4038 = OpConstant %6 27400.9336
       %4039 = OpConstant %6 -8101.42578
       %4040 = OpConstant %6 19.4400005
       %4041 = OpConstant %6 13.7700005
       %4042 = OpConstantComposite %22 %4038 %4039 %4040 %4041
       %4240 = OpUndef %22
       %4762 = OpConstant %30 -64377
       %4764 = OpConstantComposite %22 %2728 %2728 %2728 %2728
       %4765 = OpConstant %6 -41133
       %4766 = OpConstant %6 -0.0183049608
       %4767 = OpConstantComposite %22 %4766 %4766 %4766 %4766
       %4768 = OpConstant %6 0.100000001
       %4773 = OpUndef %6
       %4774 = OpUndef %22
       %4775 = OpUndef %1156
          %4 = OpFunction %2 None %3
          %5 = OpLabel
        %187 = OpVariable %186 Function
       %1869 = OpVariable %186 Function
       %2228 = OpVariable %186 Function
               OpBranch %176
        %176 = OpLabel
       %4233 = OpPhi %30 %31 %5 %198 %177
        %183 = OpSLessThan %8 %4233 %182
               OpLoopMerge %178 %177 None
               OpBranchConditional %183 %177 %178
        %177 = OpLabel
        %190 = OpISub %30 %182 %4233
        %191 = OpConvertSToF %6 %190
        %192 = OpAccessChain %34 %29 %31 %45
        %193 = OpLoad %6 %192
        %194 = OpFMul %6 %191 %193
        %195 = OpAccessChain %7 %187 %4233
               OpStore %195 %194
        %198 = OpIAdd %30 %4233 %197
               OpBranch %176
        %178 = OpLabel
               OpBranch %200
        %200 = OpLabel
       %4234 = OpPhi %30 %31 %178 %1117 %290
        %207 = OpSLessThan %8 %4234 %206
               OpLoopMerge %202 %290 None
               OpBranchConditional %207 %201 %202
        %201 = OpLabel
        %208 = OpAccessChain %34 %29 %31 %33
        %209 = OpLoad %6 %208
        %210 = OpAccessChain %34 %29 %31 %45
        %211 = OpLoad %6 %210
        %212 = OpFOrdGreaterThan %8 %209 %211
               OpSelectionMerge %214 None
               OpBranchConditional %212 %213 %214
        %213 = OpLabel
               OpStore %73 %219
               OpBranch %214
        %214 = OpLabel
               OpSelectionMerge %272 None
               OpBranchConditional %212 %271 %272
        %271 = OpLabel
               OpStore %73 %276
               OpBranch %272
        %272 = OpLabel
        %277 = OpAccessChain %107 %106 %33
        %278 = OpLoad %6 %277
        %279 = OpFOrdLessThan %8 %278 %87
               OpSelectionMerge %281 None
               OpBranchConditional %279 %280 %281
        %280 = OpLabel
               OpStore %73 %286
               OpBranch %281
        %281 = OpLabel
               OpBranch %288
        %288 = OpLabel
       %4468 = OpPhi %30 %31 %281 %1115 %291
        %294 = OpSLessThan %8 %4468 %182
               OpLoopMerge %290 %291 None
               OpBranchConditional %294 %289 %290
        %289 = OpLabel
               OpSelectionMerge %301 None
               OpBranchConditional %212 %300 %301
        %300 = OpLabel
               OpStore %73 %306
               OpBranch %301
        %301 = OpLabel
        %367 = OpFOrdLessThan %8 %278 %209
               OpSelectionMerge %369 None
               OpBranchConditional %367 %368 %369
        %368 = OpLabel
               OpStore %73 %374
               OpBranch %369
        %369 = OpLabel
        %377 = OpAccessChain %136 %29 %31
        %378 = OpLoad %26 %377
        %381 = OpExtInst %26 %1 FMax %378 %378
        %382 = OpCompositeExtract %6 %381 1
        %383 = OpFOrdGreaterThan %8 %209 %382
               OpSelectionMerge %385 None
               OpBranchConditional %383 %384 %385
        %384 = OpLabel
               OpStore %73 %390
               OpBranch %385
        %385 = OpLabel
        %395 = OpIAdd %30 %4234 %197
        %396 = OpSLessThan %8 %4468 %395
               OpSelectionMerge %398 None
               OpBranchConditional %396 %397 %398
        %397 = OpLabel
               OpSelectionMerge %407 None
               OpBranchConditional %279 %406 %407
        %406 = OpLabel
               OpStore %73 %412
               OpBranch %407
        %407 = OpLabel
               OpBranch %291
        %398 = OpLabel
        %442 = OpExtInst %30 %1 SMin %4234 %4234
        %445 = OpAccessChain %7 %187 %442
        %446 = OpLoad %6 %445
        %448 = OpAccessChain %7 %187 %4468
        %449 = OpLoad %6 %448
       %4045 = OpAccessChain %107 %106 %45
       %4046 = OpLoad %6 %4045
       %4047 = OpAccessChain %136 %135 %31
       %4048 = OpLoad %26 %4047
       %4053 = OpCompositeConstruct %26 %211 %211
       %4056 = OpFMul %26 %4053 %4048
       %4057 = OpExtInst %26 %1 FMax %4048 %4056
       %4058 = OpCompositeExtract %6 %4057 1
       %4059 = OpFMul %6 %4058 %1815
       %4060 = OpFOrdLessThan %8 %4046 %4059
               OpSelectionMerge %4061 None
               OpBranchConditional %4060 %4062 %4063
       %4063 = OpLabel
       %4066 = OpFOrdLessThan %8 %446 %449
               OpBranch %4061
       %4062 = OpLabel
       %4071 = OpFOrdGreaterThan %8 %446 %449
               OpBranch %4061
       %4061 = OpLabel
       %4485 = OpPhi %8 %4066 %4063 %4071 %4062
       %4073 = OpLogicalOr %8 %4485 %69
               OpSelectionMerge %453 None
               OpBranchConditional %4073 %452 %453
        %452 = OpLabel
        %456 = OpFOrdLessThan %8 %4046 %87
               OpSelectionMerge %458 None
               OpBranchConditional %456 %457 %458
        %457 = OpLabel
        %467 = OpExtInst %6 %1 FMin %278 %278
        %470 = OpExtInst %6 %1 FClamp %278 %467 %278
        %471 = OpExtInst %6 %1 FMin %278 %470
        %472 = OpFOrdLessThan %8 %471 %87
               OpSelectionMerge %474 None
               OpBranchConditional %472 %473 %474
        %473 = OpLabel
               OpStore %73 %478
               OpBranch %474
        %474 = OpLabel
               OpStore %73 %483
               OpBranch %458
        %458 = OpLabel
               OpSelectionMerge %489 None
               OpBranchConditional %279 %488 %489
        %488 = OpLabel
               OpStore %73 %494
               OpBranch %489
        %489 = OpLabel
        %513 = OpLoad %22 %106
               OpSelectionMerge %993 None
               OpBranchConditional %456 %992 %993
        %992 = OpLabel
               OpStore %73 %996
               OpBranch %993
        %993 = OpLabel
       %1006 = OpCompositeConstruct %22 %278 %4046 %1002 %4773
       %1014 = OpVectorShuffle %22 %4774 %1006 4 5 2 7
       %1017 = OpExtInst %22 %1 FMin %1014 %513
       %1020 = OpExtInst %22 %1 FClamp %1017 %513 %513
       %1021 = OpCompositeExtract %6 %1020 1
       %1024 = OpFOrdLessThan %8 %1021 %209
               OpSelectionMerge %1026 None
               OpBranchConditional %1024 %1025 %1026
       %1025 = OpLabel
               OpStore %73 %1056
               OpBranch %1026
       %1026 = OpLabel
       %1062 = OpAccessChain %7 %187 %4234
       %1063 = OpLoad %6 %1062
       %1069 = OpLoad %6 %448
       %1070 = OpFAdd %6 %209 %1069
               OpStore %1062 %1070
               OpStore %448 %1063
               OpBranch %453
        %453 = OpLabel
               OpSelectionMerge %1088 None
               OpBranchConditional %212 %1087 %1088
       %1087 = OpLabel
               OpStore %73 %1093
               OpBranch %1088
       %1088 = OpLabel
       %1099 = OpCompositeExtract %6 %378 1
       %1100 = OpFOrdGreaterThan %8 %209 %1099
               OpSelectionMerge %1102 None
               OpBranchConditional %1100 %1101 %1102
       %1101 = OpLabel
               OpStore %73 %1107
               OpBranch %1102
       %1102 = OpLabel
               OpBranch %291
        %291 = OpLabel
       %1115 = OpIAdd %30 %4468 %197
               OpBranch %288
        %290 = OpLabel
       %1117 = OpIAdd %30 %4234 %197
               OpBranch %200
        %202 = OpLabel
       %1680 = OpLoad %22 %106
       %1682 = OpCompositeExtract %6 %1680 1
       %1683 = OpFOrdLessThan %8 %1682 %87
               OpSelectionMerge %1685 None
               OpBranchConditional %1683 %1684 %1685
       %1684 = OpLabel
               OpStore %73 %1690
               OpBranch %1685
       %1685 = OpLabel
       %1706 = OpAccessChain %107 %106 %33
       %1707 = OpLoad %6 %1706
       %1708 = OpFOrdLessThan %8 %1707 %87
               OpSelectionMerge %1710 None
               OpBranchConditional %1708 %1709 %1710
       %1709 = OpLabel
               OpStore %73 %1713
               OpBranch %1710
       %1710 = OpLabel
       %1714 = OpAccessChain %34 %29 %31 %33
       %1715 = OpLoad %6 %1714
       %1722 = OpExtInst %6 %1 FClamp %1715 %1715 %1715
       %1723 = OpExtInst %6 %1 FMax %1715 %1722
       %1726 = OpAccessChain %34 %29 %31 %45
       %1727 = OpLoad %6 %1726
       %1728 = OpFOrdGreaterThan %8 %1723 %1727
               OpSelectionMerge %1730 None
               OpBranchConditional %1728 %1729 %1730
       %1729 = OpLabel
               OpStore %73 %1733
               OpBranch %1730
       %1730 = OpLabel
       %1737 = OpExtInst %22 %1 FMax %1680 %1680
       %1738 = OpExtInst %22 %1 FMax %1680 %1737
       %1739 = OpCompositeExtract %6 %1738 1
       %1740 = OpFOrdLessThan %8 %1739 %87
               OpSelectionMerge %1742 None
               OpBranchConditional %1740 %1741 %1742
       %1741 = OpLabel
       %1751 = OpExtInst %6 %1 FClamp %1743 %1743 %1743
       %1752 = OpExtInst %6 %1 FClamp %1743 %1743 %1751
       %1753 = OpExtInst %6 %1 FMin %1752 %1743
       %1754 = OpExtInst %6 %1 FMin %1743 %1753
       %1756 = OpCompositeConstruct %22 %1055 %1754 %1755 %852
               OpStore %73 %1756
               OpBranch %1742
       %1742 = OpLabel
       %1761 = OpFOrdGreaterThan %8 %1715 %1727
               OpSelectionMerge %1763 None
               OpBranchConditional %1761 %1762 %1763
       %1762 = OpLabel
               OpStore %73 %1766
               OpBranch %1763
       %1763 = OpLabel
               OpBranch %1791
       %1791 = OpLabel
       %4245 = OpPhi %30 %31 %1763 %1804 %1794
       %4244 = OpPhi %30 %31 %1763 %1967 %1794
       %1797 = OpSLessThan %8 %4244 %182
               OpLoopMerge %1793 %1794 None
               OpBranchConditional %1797 %1792 %1793
       %1792 = OpLabel
       %1799 = OpSGreaterThanEqual %8 %4245 %247
               OpSelectionMerge %1801 None
               OpBranchConditional %1799 %1800 %1801
       %1800 = OpLabel
               OpBranch %1793
       %1801 = OpLabel
       %1804 = OpIAdd %30 %4245 %197
       %1808 = OpSLessThan %8 %4244 %4762
               OpSelectionMerge %1810 None
               OpBranchConditional %1808 %1809 %1810
       %1809 = OpLabel
               OpBranch %1794
       %1810 = OpLabel
               OpSelectionMerge %1825 None
               OpBranchConditional %1761 %1824 %1825
       %1824 = OpLabel
               OpStore %73 %1830
               OpBranch %1825
       %1825 = OpLabel
       %1835 = OpFOrdLessThan %8 %1707 %1715
               OpSelectionMerge %1837 None
               OpBranchConditional %1835 %1836 %1837
       %1836 = OpLabel
               OpStore %73 %1850
               OpBranch %1837
       %1837 = OpLabel
       %1851 = OpAccessChain %107 %106 %45
       %1852 = OpLoad %6 %1851
       %1853 = OpFOrdLessThan %8 %1852 %87
               OpSelectionMerge %1855 None
               OpBranchConditional %1853 %1854 %1855
       %1854 = OpLabel
               OpStore %73 %1867
               OpBranch %1855
       %1855 = OpLabel
       %1878 = OpSGreaterThanEqual %8 %4244 %31
       %1881 = OpLogicalAnd %8 %1878 %1797
               OpSelectionMerge %1884 None
               OpBranchConditional %1881 %1883 %1888
       %1888 = OpLabel
               OpBranch %1884
       %1883 = OpLabel
       %1887 = OpExtInst %30 %1 SMin %4244 %4244
               OpBranch %1884
       %1884 = OpLabel
       %4249 = OpPhi %30 %31 %1888 %1887 %1883
       %1891 = OpAccessChain %7 %1869 %31
       %1892 = OpLoad %6 %1891
       %1894 = OpAccessChain %7 %1869 %4249
       %1895 = OpLoad %6 %1894
       %4085 = OpCompositeConstruct %22 %1715 %1715 %1715 %1715
       %4086 = OpFSub %22 %4240 %4085
       %4087 = OpCompositeExtract %6 %4086 1
       %4088 = OpAccessChain %34 %49 %31 %45
       %4089 = OpLoad %6 %4088
       %4090 = OpFMul %6 %4089 %1815
       %4091 = OpFOrdLessThan %8 %4087 %4090
               OpSelectionMerge %4092 None
               OpBranchConditional %4091 %4093 %4094
       %4094 = OpLabel
       %4097 = OpFOrdLessThan %8 %1892 %1895
               OpBranch %4092
       %4093 = OpLabel
       %4100 = OpFOrdGreaterThan %8 %1892 %1895
               OpBranch %4092
       %4092 = OpLabel
       %4262 = OpPhi %8 %4097 %4094 %4100 %4093
               OpSelectionMerge %1899 None
               OpBranchConditional %4262 %1898 %1899
       %1898 = OpLabel
       %1905 = OpExtInst %30 %1 SMax %31 %31
       %1906 = OpSGreaterThanEqual %8 %1769 %1905
       %1909 = OpLogicalAnd %8 %1906 %595
       %1911 = OpSelect %30 %1909 %1769 %31
       %1912 = OpISub %30 %1911 %31
       %1913 = OpAccessChain %7 %1869 %1912
       %1914 = OpLoad %6 %1913
       %1929 = OpLogicalAnd %8 %1881 %595
       %1930 = OpLogicalNot %8 %1929
       %1932 = OpLogicalNot %8 %1930
       %1934 = OpSelect %30 %1932 %4244 %31
       %1935 = OpAccessChain %7 %1869 %1934
       %1936 = OpLoad %6 %1935
               OpStore %1891 %1936
               OpSelectionMerge %1942 None
               OpBranchConditional %1853 %1941 %1942
       %1941 = OpLabel
               OpStore %73 %1946
               OpBranch %1942
       %1942 = OpLabel
       %1953 = OpSelect %30 %1881 %4244 %31
       %1955 = OpAccessChain %7 %1869 %1953
               OpStore %1955 %1914
               OpBranch %1899
       %1899 = OpLabel
               OpSelectionMerge %1960 None
               OpBranchConditional %1853 %1959 %1960
       %1959 = OpLabel
               OpStore %73 %1965
               OpBranch %1960
       %1960 = OpLabel
               OpBranch %1794
       %1794 = OpLabel
       %1967 = OpIAdd %30 %4244 %197
               OpBranch %1791
       %1793 = OpLabel
       %1972 = OpAccessChain %107 %106 %45
       %1973 = OpLoad %6 %1972
       %1974 = OpFOrdLessThan %8 %1973 %87
               OpSelectionMerge %1976 None
               OpBranchConditional %1974 %1975 %1976
       %1975 = OpLabel
               OpStore %73 %1980
               OpBranch %1976
       %1976 = OpLabel
       %1991 = OpFOrdLessThan %8 %1973 %1715
               OpSelectionMerge %1993 None
               OpBranchConditional %1991 %1992 %1993
       %1992 = OpLabel
               OpStore %73 %1998
               OpBranch %1993
       %1993 = OpLabel
               OpSelectionMerge %2005 None
               OpBranchConditional %1991 %2004 %2005
       %2004 = OpLabel
               OpStore %73 %2008
               OpBranch %2005
       %2005 = OpLabel
               OpSelectionMerge %2022 None
               OpBranchConditional %1708 %2021 %2022
       %2021 = OpLabel
               OpStore %73 %2025
               OpBranch %2022
       %2022 = OpLabel
       %2030 = OpExtInst %30 %1 SMin %2017 %2017
       %2032 = OpExtInst %30 %1 SClamp %2017 %2030 %2017
       %4181 = OpCompositeInsert %1156 %2032 %4775 1
               OpSelectionMerge %2174 None
               OpBranchConditional %1708 %2173 %2174
       %2173 = OpLabel
               OpSelectionMerge %2179 None
               OpBranchConditional %1974 %2178 %2179
       %2178 = OpLabel
               OpStore %73 %2184
               OpBranch %2179
       %2179 = OpLabel
               OpSelectionMerge %2190 None
               OpBranchConditional %1708 %2189 %2190
       %2189 = OpLabel
               OpStore %73 %2194
               OpBranch %2190
       %2190 = OpLabel
               OpStore %73 %2198
               OpBranch %2174
       %2174 = OpLabel
       %2237 = OpSDiv %30 %2032 %197
       %2238 = OpSGreaterThanEqual %8 %2237 %31
               OpSelectionMerge %2240 None
               OpBranchConditional %2238 %2239 %2240
       %2239 = OpLabel
       %2249 = OpExtInst %30 %1 SMin %2032 %2032
       %2250 = OpExtInst %30 %1 SClamp %2032 %2032 %2249
       %2251 = OpSLessThan %8 %2250 %182
               OpBranch %2240
       %2240 = OpLabel
       %2252 = OpPhi %8 %2238 %2174 %2251 %2239
       %4777 = OpSelect %30 %2252 %2032 %31
       %2272 = OpExtInst %30 %1 SMax %2010 %2010
       %2275 = OpExtInst %30 %1 SClamp %2010 %2272 %2010
       %2278 = OpExtInst %30 %1 SMax %2275 %2010
       %2279 = OpSGreaterThanEqual %8 %2278 %31
       %4778 = OpSelect %8 %2279 %69 %2279
       %2290 = OpLogicalNot %8 %4778
       %2291 = OpLogicalNot %8 %2290
       %4779 = OpSelect %30 %2291 %2010 %31
       %2300 = OpAccessChain %7 %2228 %4777
       %2301 = OpLoad %6 %2300
       %2303 = OpAccessChain %7 %2228 %4779
       %2304 = OpLoad %6 %2303
       %4113 = OpCompositeConstruct %22 %1715 %1715 %1715 %1715
       %4114 = OpFSub %22 %4240 %4113
       %4115 = OpCompositeExtract %6 %4114 1
       %4116 = OpAccessChain %34 %49 %31 %45
       %4117 = OpLoad %6 %4116
       %4118 = OpFMul %6 %4117 %1815
       %4119 = OpFOrdLessThan %8 %4115 %4118
               OpSelectionMerge %4120 None
               OpBranchConditional %4119 %4121 %4122
       %4122 = OpLabel
       %4125 = OpFOrdLessThan %8 %2301 %2304
               OpBranch %4120
       %4121 = OpLabel
       %4128 = OpFOrdGreaterThan %8 %2301 %2304
               OpBranch %4120
       %4120 = OpLabel
       %4354 = OpPhi %8 %4125 %4122 %4128 %4121
               OpSelectionMerge %2308 None
               OpBranchConditional %4354 %2307 %2308
       %2307 = OpLabel
       %2312 = OpSGreaterThanEqual %8 %2032 %31
               OpSelectionMerge %2314 None
               OpBranchConditional %2312 %2313 %2314
       %2313 = OpLabel
       %2317 = OpSLessThan %8 %2032 %182
               OpBranch %2314
       %2314 = OpLabel
       %2318 = OpPhi %8 %2312 %2307 %2317 %2313
       %4780 = OpSelect %30 %2318 %2032 %31
       %2326 = OpAccessChain %7 %2228 %4780
       %2327 = OpLoad %6 %2326
               OpSelectionMerge %2332 None
               OpBranchConditional %2312 %2331 %2332
       %2331 = OpLabel
       %2336 = OpConvertFToS %30 %1727
       %2340 = OpCompositeConstruct %1156 %2336 %2336
       %2341 = OpSDiv %1156 %4181 %2340
       %2342 = OpCompositeExtract %30 %2341 1
       %2343 = OpSLessThan %8 %2342 %182
               OpBranch %2332
       %2332 = OpLabel
       %2344 = OpPhi %8 %2312 %2314 %2343 %2331
       %2345 = OpLogicalNot %8 %2344
       %2346 = OpLogicalAnd %8 %2345 %595
       %2347 = OpLogicalNot %8 %2346
               OpSelectionMerge %2350 None
               OpBranchConditional %2347 %2349 %2355
       %2355 = OpLabel
               OpBranch %2350
       %2349 = OpLabel
       %2353 = OpExtInst %1156 %1 SMin %4181 %4181
       %2354 = OpCompositeExtract %30 %2353 1
               OpBranch %2350
       %2350 = OpLabel
       %4363 = OpPhi %30 %31 %2355 %2354 %2349
       %2357 = OpAccessChain %7 %2228 %4363
       %2358 = OpLoad %6 %2357
               OpSelectionMerge %2363 None
               OpBranchConditional %2312 %2362 %2363
       %2362 = OpLabel
       %2367 = OpLogicalOr %8 %1974 %69
       %2368 = OpLogicalNot %8 %2367
               OpSelectionMerge %2370 None
               OpBranchConditional %2368 %2369 %2370
       %2369 = OpLabel
       %2373 = OpSLessThan %8 %2032 %182
       %2374 = OpLogicalNot %8 %2373
       %2375 = OpLogicalNot %8 %2374
       %2376 = OpLogicalNot %8 %2375
               OpBranch %2370
       %2370 = OpLabel
       %2377 = OpPhi %8 %2367 %2362 %2376 %2369
       %2378 = OpLogicalNot %8 %2377
               OpBranch %2363
       %2363 = OpLabel
       %2379 = OpPhi %8 %2312 %2350 %2378 %2370
       %4781 = OpSelect %30 %2379 %2032 %31
       %2387 = OpAccessChain %7 %2228 %4781
       %2388 = OpLoad %6 %2387
       %2389 = OpExtInst %6 %1 FClamp %2327 %2358 %2388
               OpSelectionMerge %2401 None
               OpBranchConditional %2312 %2400 %2401
       %2400 = OpLabel
       %2404 = OpSLessThan %8 %2032 %182
               OpBranch %2401
       %2401 = OpLabel
       %2405 = OpPhi %8 %2312 %2363 %2404 %2400
       %4782 = OpSelect %30 %2405 %2032 %31
       %2418 = OpExtInst %30 %1 SMin %2010 %2010
       %2419 = OpSGreaterThanEqual %8 %2418 %31
       %4783 = OpSelect %8 %2419 %69 %2419
       %4784 = OpSelect %30 %4783 %2010 %31
       %2433 = OpAccessChain %7 %2228 %4784
       %2434 = OpLoad %6 %2433
       %2435 = OpAccessChain %7 %2228 %4782
               OpStore %2435 %2434
               OpSelectionMerge %2451 None
               OpBranchConditional %1708 %2450 %2451
       %2450 = OpLabel
               OpStore %73 %2455
               OpBranch %2451
       %2451 = OpLabel
       %2485 = OpAccessChain %7 %2228 %31
               OpStore %2485 %2389
               OpBranch %2308
       %2308 = OpLabel
               OpSelectionMerge %2522 None
               OpBranchConditional %1708 %2521 %2522
       %2521 = OpLabel
               OpStore %73 %2525
               OpBranch %2522
       %2522 = OpLabel
       %2598 = OpLogicalNot %8 %1708
               OpSelectionMerge %2600 None
               OpBranchConditional %2598 %2599 %2600
       %2599 = OpLabel
       %2606 = OpFMod %6 %4765 %1671
       %2610 = OpExtInst %6 %1 FMin %2607 %2607
       %2611 = OpFOrdLessThanEqual %8 %2606 %2610
       %2612 = OpLogicalNot %8 %2611
               OpBranch %2600
       %2600 = OpLabel
       %2613 = OpPhi %8 %1708 %2522 %2612 %2599
       %2614 = OpLogicalNot %8 %2613
               OpSelectionMerge %2617 None
               OpBranchConditional %2614 %2616 %2617
       %2616 = OpLabel
               OpSelectionMerge %2918 None
               OpBranchConditional %1708 %2917 %2918
       %2917 = OpLabel
               OpStore %73 %2927
               OpBranch %2918
       %2918 = OpLabel
               OpSelectionMerge %2943 None
               OpBranchConditional %1708 %2942 %2943
       %2942 = OpLabel
               OpStore %73 %2961
               OpBranch %2943
       %2943 = OpLabel
               OpSelectionMerge %2966 None
               OpBranchConditional %1708 %2965 %2966
       %2965 = OpLabel
               OpStore %73 %2970
               OpBranch %2966
       %2966 = OpLabel
       %2974 = OpLogicalAnd %8 %1708 %595
       %2975 = OpLogicalNot %8 %2974
       %2976 = OpLogicalNot %8 %2975
               OpSelectionMerge %2978 None
               OpBranchConditional %2976 %2977 %2978
       %2977 = OpLabel
               OpStore %73 %2983
               OpBranch %2978
       %2978 = OpLabel
               OpSelectionMerge %2993 None
               OpBranchConditional %1708 %2992 %2993
       %2992 = OpLabel
               OpStore %73 %2998
               OpBranch %2993
       %2993 = OpLabel
               OpBranch %2617
       %2617 = OpLabel
       %3076 = OpAccessChain %34 %135 %31 %33
       %3077 = OpLoad %6 %3076
       %3078 = OpFMul %6 %3077 %1815
       %3079 = OpFOrdLessThan %8 %1707 %3078
               OpSelectionMerge %3082 None
               OpBranchConditional %3079 %3081 %3281
       %3281 = OpLabel
               OpSelectionMerge %3286 None
               OpBranchConditional %1708 %3285 %3286
       %3285 = OpLabel
               OpStore %73 %3291
               OpBranch %3286
       %3286 = OpLabel
       %3316 = OpCompositeConstruct %964 %595 %1761 %595 %595
       %3317 = OpSelect %22 %3316 %3310 %3306
       %3319 = OpExtInst %22 %1 FMax %3317 %3318
       %3322 = OpFMul %22 %3319 %4767
               OpSelectionMerge %3327 None
               OpBranchConditional %1708 %3326 %3327
       %3326 = OpLabel
               OpStore %73 %3332
               OpBranch %3327
       %3327 = OpLabel
       %3334 = OpCompositeExtract %6 %3322 0
       %3335 = OpConvertFToS %30 %3334
       %3336 = OpSLessThan %8 %3335 %536
               OpSelectionMerge %3338 None
               OpBranchConditional %3336 %3337 %3392
       %3392 = OpLabel
       %3397 = OpSLessThan %8 %3335 %761
               OpSelectionMerge %3399 None
               OpBranchConditional %3397 %3398 %3411
       %3411 = OpLabel
       %3416 = OpSLessThan %8 %3335 %3415
               OpSelectionMerge %3418 None
               OpBranchConditional %3416 %3417 %3435
       %3435 = OpLabel
       %3439 = OpSLessThan %8 %3335 %1211
               OpSelectionMerge %3441 None
               OpBranchConditional %3439 %3440 %3458
       %3458 = OpLabel
       %3462 = OpSLessThan %8 %3335 %528
               OpSelectionMerge %3464 None
               OpBranchConditional %3462 %3463 %3561
       %3561 = OpLabel
       %3565 = OpExtInst %22 %1 FMax %3322 %3322
       %3566 = OpExtInst %22 %1 FMax %3322 %3565
       %3567 = OpCompositeExtract %6 %3566 0
       %3568 = OpConvertFToS %30 %3567
       %3569 = OpSLessThan %8 %3568 %572
               OpSelectionMerge %3571 None
               OpBranchConditional %3569 %3570 %3585
       %3585 = OpLabel
       %3602 = OpSLessThan %8 %3335 %630
               OpSelectionMerge %3604 None
               OpBranchConditional %3602 %3603 %3658
       %3658 = OpLabel
       %3662 = OpSLessThan %8 %3335 %679
               OpSelectionMerge %3664 None
               OpBranchConditional %3662 %3663 %3684
       %3684 = OpLabel
       %3694 = OpExtInst %22 %1 FMin %3322 %3322
       %3696 = OpExtInst %22 %1 FMax %3694 %3322
       %3697 = OpCompositeExtract %6 %3696 0
       %3698 = OpConvertFToS %30 %3697
       %3699 = OpSLessThan %8 %3698 %714
               OpSelectionMerge %3701 None
               OpBranchConditional %3699 %3700 %3745
       %3745 = OpLabel
               OpSelectionMerge %3750 None
               OpBranchConditional %1708 %3749 %3750
       %3749 = OpLabel
               OpStore %73 %3755
               OpBranch %3750
       %3750 = OpLabel
               OpSelectionMerge %3777 None
               OpBranchConditional %1708 %3776 %3777
       %3776 = OpLabel
               OpStore %73 %3781
               OpBranch %3777
       %3777 = OpLabel
               OpBranch %3701
       %3700 = OpLabel
               OpSelectionMerge %3726 None
               OpBranchConditional %1991 %3725 %3726
       %3725 = OpLabel
       %3730 = OpFOrdGreaterThanEqual %8 %1707 %87
       %3733 = OpSelect %6 %3730 %3731 %3732
       %3741 = OpSelect %6 %1761 %1962 %3740
       %3742 = OpCompositeConstruct %22 %3727 %3733 %3734 %3741
       %3744 = OpExtInst %22 %1 Step %4764 %3742
               OpStore %73 %3744
               OpBranch %3726
       %3726 = OpLabel
               OpBranch %3701
       %3701 = OpLabel
               OpBranch %3664
       %3663 = OpLabel
               OpBranch %3664
       %3664 = OpLabel
               OpBranch %3604
       %3603 = OpLabel
               OpBranch %3604
       %3604 = OpLabel
               OpBranch %3571
       %3570 = OpLabel
               OpBranch %3571
       %3571 = OpLabel
               OpBranch %3464
       %3463 = OpLabel
               OpBranch %3464
       %3464 = OpLabel
               OpBranch %3441
       %3440 = OpLabel
               OpBranch %3441
       %3441 = OpLabel
               OpBranch %3418
       %3417 = OpLabel
               OpBranch %3418
       %3418 = OpLabel
               OpBranch %3399
       %3398 = OpLabel
               OpBranch %3399
       %3399 = OpLabel
               OpBranch %3338
       %3337 = OpLabel
               OpBranch %3338
       %3338 = OpLabel
       %3786 = OpAccessChain %7 %187 %247
       %3787 = OpLoad %6 %3786
       %3788 = OpFMul %6 %3787 %4768
       %3789 = OpAccessChain %7 %187 %206
       %3790 = OpLoad %6 %3789
       %3791 = OpFMul %6 %3790 %4768
       %3793 = OpAccessChain %7 %187 %31
       %3794 = OpLoad %6 %3793
       %3797 = OpFOrdGreaterThanEqual %8 %1707 %87
       %3799 = OpSelect %6 %3797 %250 %3798
       %3800 = OpExtInst %6 %1 FMin %3799 %250
       %3801 = OpFDiv %6 %3794 %3800
       %3802 = OpCompositeConstruct %22 %3788 %3791 %3801 %86
               OpStore %73 %3802
               OpSelectionMerge %3813 None
               OpBranchConditional %1761 %3812 %3813
       %3812 = OpLabel
               OpStore %73 %3821
               OpBranch %3813
       %3813 = OpLabel
               OpSelectionMerge %3979 None
               OpBranchConditional %1974 %3978 %3979
       %3978 = OpLabel
               OpStore %73 %3983
               OpBranch %3979
       %3979 = OpLabel
               OpBranch %3082
       %3081 = OpLabel
               OpSelectionMerge %3087 None
               OpBranchConditional %1974 %3086 %3087
       %3086 = OpLabel
               OpSelectionMerge %3092 None
               OpBranchConditional %1708 %3091 %3092
       %3091 = OpLabel
               OpStore %73 %3095
               OpBranch %3092
       %3092 = OpLabel
               OpStore %73 %3098
               OpBranch %3087
       %3087 = OpLabel
               OpSelectionMerge %3122 None
               OpBranchConditional %1974 %3121 %3122
       %3121 = OpLabel
       %3130 = OpExtInst %6 %1 FClamp %1707 %1707 %1707
       %3131 = OpFOrdLessThan %8 %3130 %87
               OpSelectionMerge %3133 None
               OpBranchConditional %3131 %3132 %3133
       %3132 = OpLabel
               OpStore %73 %3138
               OpBranch %3133
       %3133 = OpLabel
       %3150 = OpSelect %6 %1708 %1296 %3146
       %3152 = OpCompositeConstruct %22 %1979 %3150 %3151 %86
       %3163 = OpFAdd %22 %3153 %4113
       %3164 = OpExtInst %22 %1 FMin %3163 %3153
       %3165 = OpCompositeExtract %6 %3164 0
       %3167 = OpCompositeConstruct %22 %3165 %52 %86 %3166
       %3170 = OpFOrdGreaterThanEqual %8 %1707 %87
       %3175 = OpExtInst %22 %1 FMax %1737 %1680
       %3176 = OpCompositeExtract %6 %3175 0
       %3177 = OpFOrdLessThan %8 %3176 %87
       %3178 = OpLogicalAnd %8 %3177 %595
       %3179 = OpCompositeConstruct %964 %3170 %595 %595 %3178
       %3180 = OpSelect %22 %3179 %3167 %3152
               OpStore %73 %3180
               OpBranch %3122
       %3122 = OpLabel
       %3181 = OpAccessChain %7 %187 %31
       %3182 = OpLoad %6 %3181
       %3183 = OpFMul %6 %3182 %4768
       %3184 = OpAccessChain %7 %187 %247
       %3185 = OpLoad %6 %3184
       %3186 = OpFMul %6 %3185 %4768
       %3187 = OpAccessChain %7 %187 %206
       %3188 = OpLoad %6 %3187
       %3189 = OpFMul %6 %3188 %4768
       %3190 = OpAccessChain %136 %29 %31
       %3191 = OpLoad %26 %3190
       %3193 = OpCompositeExtract %6 %3191 0
       %3201 = OpExtInst %6 %1 FClamp %3193 %1715 %1715
       %3211 = OpCompositeConstruct %26 %1715 %1727
       %3213 = OpVectorShuffle %26 %3211 %3206 0 1
       %3215 = OpExtInst %26 %1 FMax %3191 %3213
       %3224 = OpExtInst %26 %1 FClamp %3191 %3191 %3191
       %3247 = OpExtInst %26 %1 FClamp %3224 %3224 %3224
       %3255 = OpExtInst %26 %1 FClamp %3224 %3247 %3224
       %3256 = OpExtInst %26 %1 FClamp %3215 %3191 %3255
       %3257 = OpCompositeExtract %6 %3256 1
       %3258 = OpFOrdLessThan %8 %3201 %3257
       %3260 = OpSelect %6 %3258 %86 %3259
       %3261 = OpCompositeConstruct %22 %3183 %3186 %3189 %3260
               OpStore %73 %3261
               OpBranch %3082
       %3082 = OpLabel
               OpSelectionMerge %4037 None
               OpBranchConditional %1974 %4036 %4037
       %4036 = OpLabel
               OpStore %73 %4042
               OpBranch %4037
       %4037 = OpLabel
               OpReturn
               OpFunctionEnd
  )";

  spv_target_env env = SPV_ENV_UNIVERSAL_1_3;
  Reducer reducer(env);
  EventuallyInteresting eventually_interesting(100);

  reducer.SetInterestingnessFunction(
      [&](const std::vector<uint32_t>&, uint32_t) -> bool {
        return eventually_interesting.IsInteresting();
      });
  reducer.AddDefaultReductionPasses();
  reducer.SetMessageConsumer(CLIMessageConsumer);

  std::vector<uint32_t> binary_in;
  SpirvTools t(env);

  ASSERT_TRUE(t.Assemble(original, &binary_in, kReduceAssembleOption));
  std::vector<uint32_t> binary_out;
  spvtools::ReducerOptions reducer_options;
  reducer_options.set_step_limit(500);
  spvtools::ValidatorOptions validator_options;

  Reducer::ReductionResultStatus status = reducer.Run(
      std::move(binary_in), &binary_out, reducer_options, validator_options);

  ASSERT_EQ(status, Reducer::ReductionResultStatus::kComplete);
}
*/
}  // namespace
}  // namespace reduce
}  // namespace spvtools
