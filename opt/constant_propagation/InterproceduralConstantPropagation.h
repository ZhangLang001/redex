/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <atomic>

#include "ConstPropConfig.h"
#include "Pass.h"

namespace interprocedural_constant_propagation {

struct Stats {
  size_t constant_fields{0};
  size_t branches_removed{0};
  size_t materialized_consts{0};
};

} // namespace interprocedural_constant_propagation

class InterproceduralConstantPropagationPass : public Pass {
 public:
  InterproceduralConstantPropagationPass()
      : Pass("InterproceduralConstantPropagationPass") {}

  void configure_pass(const PassConfig& pc) override {
    pc.get(
        "replace_moves_with_consts", false, m_config.replace_moves_with_consts);
    pc.get("fold_arithmetic", false, m_config.fold_arithmetic);
    pc.get("propagate_conditions", false, m_config.propagate_conditions);
  }

  // run() is exposed for testing purposes -- run_pass takes a PassManager
  // object, making it awkward to call in unit tests.
  interprocedural_constant_propagation::Stats run(Scope&);

  void run_pass(DexStoresVector& stores,
                ConfigFiles& cfg,
                PassManager& mgr) override;
 private:
  ConstPropConfig m_config;
};
