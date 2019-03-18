// Copyright (c) 2018 Google LLC
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

#include <cassert>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>

#include "source/opt/build_module.h"
#include "source/opt/log.h"
#include "source/util/string_utils.h"
#include "tools/io.h"
#include "tools/util/cli_consumer.h"

namespace {

using ErrorOrInt = std::pair<std::string, int>;

// Message consumer for this tool.  Used to emit diagnostics during
// initialization and setup. Note that |source| and |position| are irrelevant
// here because we are still not processing a SPIR-V input file.
void VisDiagnostic(spv_message_level_t level, const char* /*source*/,
                   const spv_position_t& /*position*/, const char* message) {
  if (level == SPV_MSG_ERROR) {
    fprintf(stderr, "error: ");
  }
  fprintf(stderr, "%s\n", message);
}

}  // namespace

const auto kDefaultEnvironment = SPV_ENV_UNIVERSAL_1_3;

int main(int argc, const char** argv) {
  if (argc != 2) {
    spvtools::Error(VisDiagnostic, nullptr, {},
                    "One argument (SPIR-V binary input file) required");
    return 1;
  }
  const char* in_file = argv[1];

  std::vector<uint32_t> binary_in;
  if (!ReadFile<uint32_t>(in_file, "rb", &binary_in)) {
    spvtools::Error(VisDiagnostic, nullptr, {}, "Failed to read input file");
    return 1;
  }

  std::unique_ptr<spvtools::opt::IRContext> context = spvtools::BuildModule(
      kDefaultEnvironment, VisDiagnostic, binary_in.data(), binary_in.size());

  std::ofstream output_file("output.txt");

  for (auto& function : *context->module()) {
    output_file << "Function " << function.result_id() << std::endl;
  }

  return 0;
}
