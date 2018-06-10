/**
 * The ARTist Project (https://artist.cispa.saarland)
 *
 * Copyright (C) 2017 CISPA (https://cispa.saarland), Saarland University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @author "Oliver Schranz <oliver.schranz@cispa.saarland>"
 *
 */

#include <artist/filtering/method_name_filters.h>

#include "module.h"
#include "instrumentation_pass.h"

using std::make_shared;

using art::WhitelistFilter;

shared_ptr<HArtist> LogtimizationModule::createPass(const MethodInfo& method_info) const {
  return make_shared<HLogtimization>(method_info);
}

shared_ptr<const CodeLib> LogtimizationModule::createCodeLib() const {
  return nullptr;
}

/* (Arbitrary) restriction of compile-time output to "onCreate" methods (Activities, Applications, ...) to reduce
 * logcat spamming.
 */
unique_ptr<Filter> LogtimizationModule::getMethodFilter() const {
  const vector<const string> onCreate = {".onCreate("};
  return unique_ptr<Filter>(new WhitelistFilter(onCreate, false, true));
}

// the class factories

extern "C" shared_ptr <art::Module> create() {
  return make_shared<LogtimizationModule>();
}
