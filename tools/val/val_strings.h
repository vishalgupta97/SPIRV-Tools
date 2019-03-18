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

#ifndef TOOLS_VAL_VAL_STRINGS_H
#define TOOLS_VAL_VAL_STRINGS_H

namespace spvtools {
namespace val {

const char* kValidatorOptionHelpRelaxBlockLayout = R"(
  --relax-block-layout             Enable VK_KHR_relaxed_block_layout when checking standard
                                   uniform, storage buffer, and push constant layouts.
                                   This is the default when targeting Vulkan 1.1 or later.)";

const char* kValidatorOptionHelpRelaxLogicalPointer = R"(
  --relax-logical-pointer          Allow allocating an object of a pointer type and returning
                                   a pointer value from a function in logical addressing mode)";

const char* kValidatorOptionHelpRelaxStructStore = R"(
  --relax-struct-store             Allow store from one struct type to a
                                   different type with compatible layout and
                                   members.)";

const char* kValidatorOptionHelpScalarBlockLayout = R"(
  --scalar-block-layout            Enable VK_EXT_scalar_block_layout when checking standard
                                   uniform, storage buffer, and push constant layouts.  Scalar layout
                                   rules are more permissive than relaxed block layout so in effect
                                   this will override the --relax-block-layout option.)";

const char* kValidatorOptionHelpSkipBlockLayout = R"(
  --skip-block-layout              Skip checking standard uniform/storage buffer layout.
                                   Overrides any --relax-block-layout or --scalar-block-layout option.)";

}  // namespace val
}  // namespace spvtools

#endif  // TOOLS_VAL_VAL_STRINGS_H
