/* Copyright (c) Huawei Technologies Co., Ltd. 2022-2022. All rights reserved.

   Licensed under the Apache License, Version 2.0 (the "License"); you may
   not use this file except in compliance with the License. You may obtain
   a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
   WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
   License for the specific language governing permissions and limitations
   under the License.

   Author: Guangya Ding
   Create: 2022-11-29
   Description:
    This file defines the types for the Plugin dialect in MLIR. These MLIR types
    correspond to the Plugin IR type system.
*/

#include "Dialect/PluginDialect.h"
#include "Dialect/PluginTypes.h"

using namespace mlir;
using namespace PluginIR;

namespace PluginIR {
namespace detail {
    /// Integer Type Storage and Uniquing.
    struct PluginIntegerTypeStorage : public TypeStorage {
    PluginIntegerTypeStorage(unsigned width,
                        PluginIntegerType::SignednessSemantics signedness)
        : width(width), signedness(signedness) {}

    /// The hash key used for uniquing.
    using KeyTy = std::pair<unsigned, PluginIntegerType::SignednessSemantics>;

    static llvm::hash_code hashKey(const KeyTy &key)
    {
        return llvm::hash_value(key);
    }

    bool operator==(const KeyTy &key) const
    {
        return KeyTy(width, signedness) == key;
    }

    static PluginIntegerTypeStorage *construct(TypeStorageAllocator &allocator,
                                        KeyTy key)
    {
        return new (allocator.allocate<PluginIntegerTypeStorage>())
            PluginIntegerTypeStorage(key.first, key.second);
    }

    unsigned width : 30;
    PluginIntegerType::SignednessSemantics signedness : 2;
    };

    struct PluginFloatTypeStorage : public TypeStorage {
        PluginFloatTypeStorage(unsigned width) : width(width) {}

        /// The hash key used for uniquing.
        using KeyTy = unsigned;

        bool operator==(const KeyTy &key) const
        {
            return KeyTy(width) == key;
        }

        static PluginFloatTypeStorage *construct(TypeStorageAllocator &allocator, KeyTy key)
        {
            return new (allocator.allocate<PluginFloatTypeStorage>())
                PluginFloatTypeStorage(key);
        }

        unsigned width : 30;
    };

    struct PluginPointerTypeStorage : public TypeStorage {
        using KeyTy = std::tuple<Type, unsigned>;

        PluginPointerTypeStorage(const KeyTy &key)
            : pointee(std::get<0>(key)), readOnlyPointee(std::get<1>(key)) {}

        static PluginPointerTypeStorage *construct(TypeStorageAllocator &allocator, KeyTy key)
        {
            return new (allocator.allocate<PluginPointerTypeStorage>())
                PluginPointerTypeStorage(key);
        }

        bool operator==(const KeyTy &key) const
        {
            return std::make_tuple(pointee, readOnlyPointee) == key;
        }

        Type pointee;
        unsigned readOnlyPointee;
    };
}
}


// ===----------------------------------------------------------------------===//
// Plugin TypeBase
// ===----------------------------------------------------------------------===//

PluginTypeID PluginTypeBase::getPluginTypeID ()
{
    if (auto Ty = dyn_cast<PluginIR::PluginIntegerType>()) {
        return Ty.getPluginTypeID ();
    }
    if (auto Ty = dyn_cast<PluginIR::PluginFloatType>()) {
        return Ty.getPluginTypeID ();
    }
    if (auto Ty = dyn_cast<PluginIR::PluginBooleanType>()) {
        return Ty.getPluginTypeID ();
    }
    if (auto Ty = dyn_cast<PluginIR::PluginVoidType>()) {
        return Ty.getPluginTypeID ();
    }
    if (auto Ty = dyn_cast<PluginIR::PluginPointerType>()) {
        return Ty.getPluginTypeID ();
    }
    return PluginTypeID::UndefTyID;
}

unsigned PluginTypeBase::getPluginIntOrFloatBitWidth ()
{
    if (auto Ty = dyn_cast<PluginIR::PluginIntegerType>()) {
        return Ty.getWidth();
    }
    if (auto Ty = dyn_cast<PluginIR::PluginFloatType>()) {
        return Ty.getWidth();
    }
    return 0;
}

bool PluginTypeBase::isSignedPluginInteger ()
{
    if (auto Ty = dyn_cast<PluginIR::PluginIntegerType>()) {
        return Ty.isSigned();
    }
    return false;
}

bool PluginTypeBase::isUnsignedPluginInteger ()
{
    if (auto Ty = dyn_cast<PluginIR::PluginIntegerType>()) {
        return Ty.isUnsigned();
    }
    return false;
}

void PluginTypeBase::setTypeSize (unsigned size)
{
    this->size = size;
}

unsigned PluginTypeBase::getTypeSize ()
{
    return size;
}

// ===----------------------------------------------------------------------===//
// Plugin Integer Type
// ===----------------------------------------------------------------------===//

unsigned PluginIntegerType::getWidth() const
{
    return getImpl()->width;
}

PluginIntegerType::SignednessSemantics PluginIntegerType::getSignedness() const
{
    return getImpl()->signedness;
}

PluginTypeID PluginIntegerType::getPluginTypeID()
{
    if (isSigned()) {
        switch (getWidth()) {
            case 1:
                return PluginTypeID::IntegerTy1ID;
            case 8:
                return PluginTypeID::IntegerTy8ID;
            case 16:
                return PluginTypeID::IntegerTy16ID;
            case 32:
                return PluginTypeID::IntegerTy32ID;
            case 64:
                return PluginTypeID::IntegerTy64ID;
            default:
                return PluginTypeID::UndefTyID;
        }
    }
    if (isUnsigned()) {
        switch (getWidth()) {
            case 1:
                return PluginTypeID::UIntegerTy1ID;
            case 8:
                return PluginTypeID::UIntegerTy8ID;
            case 16:
                return PluginTypeID::UIntegerTy16ID;
            case 32:
                return PluginTypeID::UIntegerTy32ID;
            case 64:
                return PluginTypeID::UIntegerTy64ID;
            default:
                return PluginTypeID::UndefTyID;
        }
    }
    return PluginTypeID::UndefTyID;
}

PluginIntegerType PluginIntegerType::get (MLIRContext *context, unsigned width,
    PluginIntegerType::SignednessSemantics signedness)
{
    return Base::get(context, width, signedness);
}

// ===----------------------------------------------------------------------===//
// Plugin Float Type
// ===----------------------------------------------------------------------===//
unsigned PluginFloatType::getWidth () const
{
    return getImpl()->width;
}

PluginTypeID PluginFloatType::getPluginTypeID()
{
    if (getWidth() == 32) {
        return PluginTypeID::FloatTyID;
    }
    if (getWidth() == 64) {
        return PluginTypeID::DoubleTyID;
    }
    return PluginTypeID::UndefTyID;
}

PluginFloatType PluginFloatType::get (MLIRContext *context, unsigned width)
{
    return Base::get(context, width);
}

// ===----------------------------------------------------------------------===//
// Plugin Boolean Type
// ===----------------------------------------------------------------------===//

PluginTypeID PluginBooleanType::getPluginTypeID()
{
    return PluginTypeID::BooleanTyID;
}

// ===----------------------------------------------------------------------===//
// Plugin Void Type
// ===----------------------------------------------------------------------===//

PluginTypeID PluginVoidType::getPluginTypeID()
{
    return PluginTypeID::VoidTyID;
}

// ===----------------------------------------------------------------------===//
// Plugin Undef Type
// ===----------------------------------------------------------------------===//

PluginTypeID PluginUndefType::getPluginTypeID()
{
    return PluginTypeID::UndefTyID;
}

// ===----------------------------------------------------------------------===//
// Plugin Pointer Type
// ===----------------------------------------------------------------------===//

PluginTypeID PluginPointerType::getPluginTypeID()
{
    return PluginTypeID::PointerTyID;
}

Type PluginPointerType::getElementType()
{
    return getImpl()->pointee;
}

unsigned PluginPointerType::isReadOnlyElem()
{
    return getImpl()->readOnlyPointee;
}

PluginPointerType PluginPointerType::get (MLIRContext *context, Type pointee, unsigned readOnlyPointee)
{
    return Base::get(context, pointee, readOnlyPointee);
}