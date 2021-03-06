/* Copyright (c) 2018 Anakin Authors, Inc. All Rights Reserved.
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef ANAKIN_SABER_FUNCS_IMPL_ARM_SABER_LRN_H
#define ANAKIN_SABER_FUNCS_IMPL_ARM_SABER_LRN_H

#include "saber/funcs/impl/impl_lrn.h"

namespace anakin{

namespace saber{

template <DataType OpDtype>
class SaberLrn<ARM, OpDtype> : \
    public ImplBase<
        ARM,
        OpDtype,
        LrnParam<ARM > >
{
public:
    typedef typename DataTrait<ARM, OpDtype>::Dtype OpDataType;

    SaberLrn()
    {}

    ~SaberLrn() {}

    virtual SaberStatus init(const std::vector<Tensor<ARM> *>& inputs,
                            std::vector<Tensor<ARM> *>& outputs,
                            LrnParam<ARM>& param, Context<ARM>& ctx) {
        this->_ctx = &ctx;
        return create(inputs, outputs, param, ctx);
    }

    virtual SaberStatus create(const std::vector<Tensor<ARM> *>& inputs,
                            std::vector<Tensor<ARM> *>& outputs,
                            LrnParam<ARM>& param, Context<ARM> &ctx) {
        _pre_pad = (param.local_size - 1) / 2;
        _post_pad = param.local_size - _pre_pad - 1;
        return SaberSuccess;
    }

    virtual SaberStatus dispatch(const std::vector<Tensor<ARM> *>& inputs,
                          std::vector<Tensor<ARM> *>& outputs,
                          LrnParam<ARM>& param);
private:
    int _pre_pad;
    int _post_pad;

};

}

}
#endif //ANAKIN_SABER_FUNCS_IMPL_ARM_SABER_Lrn_H
