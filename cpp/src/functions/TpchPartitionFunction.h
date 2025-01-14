/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "velox/core/PlanNode.h"

using namespace facebook::velox;

namespace io::trino::bridge {

class TpchPartitionFunction : public core::PartitionFunction {
 public:
  explicit TpchPartitionFunction(int64_t rowsPerPartition, int numPartitions);

  std::optional<uint32_t> partition(const RowVector& input,
                                    std::vector<uint32_t>& partitions);

 private:
  int64_t rowNumberFromOrderKey(int64_t orderKey);

 private:
  const int64_t _rowsPerPartition;
  const int _numPartitions;

  DecodedVector decodedVector;
};

class TpchPartitionFunctionSpec : public core::PartitionFunctionSpec {
 public:
  explicit TpchPartitionFunctionSpec(int64_t rowsPerPartition);

  std::unique_ptr<core::PartitionFunction> create(int numPartitions) const override;

  std::string toString() const override;

  folly::dynamic serialize() const override;

  static core::PartitionFunctionSpecPtr deserialize(const folly::dynamic& obj,
                                                    void* context);

 private:
  const int64_t _rowsPerPartition;
};

}  // namespace io::trino::bridge