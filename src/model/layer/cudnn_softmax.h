/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SINGA_MODEL_LAYER_CUDNN_SOFTMAX_H_
#define SINGA_MODEL_LAYER_CUDNN_SOFTMAX_H_
#ifdef USE_CUDNN
#include <cudnn.h>
#include <utility>
#include <string>
#include <vector>

#include "./softmax.h"
#include "singa/core/common.h"
#include "singa/model/layer.h"
#include "singa/proto/core.pb.h"

namespace singa {
class CudnnSoftmax : public Softmax {
 public:
  ~CudnnSoftmax();
  /// \copydoc Layer::layer_type()
  // const std::string layer_type() const override { return "CudnnSoftmax"; }

  /// \copydoc Layer::Setup(const LayerConf&);
  void Setup(const Shape& in_sample_shape, const LayerConf &conf) override;

  const Tensor Forward(int flag, const Tensor& input) override;
  const std::pair<Tensor, vector<Tensor>> Backward(int flag,
                                                   const Tensor& grad) override;

  const cudnnSoftmaxAlgorithm_t Algorithm() const { return algorithm_; }

 private:
  /// Init cudnn related data structures.
  void InitCudnn(Shape shape, DataType dtype);

 private:
  bool has_init_cudnn_ = false;
  cudnnTensorDescriptor_t desc_ = nullptr;
  cudnnSoftmaxAlgorithm_t algorithm_;
};
}  // namespace
#endif  // USE_CUDNN
#endif  // SINGA_MODEL_LAYER_CUDNN_SOFTMAX_H_
