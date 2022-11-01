/*
 * Copyright 2022 Adobe
 * All Rights Reserved.
 *
 * NOTICE: Adobe permits you to use, modify, and distribute this file in
 * accordance with the terms of the Adobe license agreement accompanying
 * it.
 */
#pragma once

#include <cassert>
#include <memory>

namespace foo {

///
/// A handle type with copy-on-write semantics. Any copy of the handle will share data ownership,
/// causing potential copies of the data on write access.
///
/// @tparam     T     Pointee type.
///
template <typename T>
class copy_on_write_ptr
{
public:
    using pointer = T*;
    using const_pointer = typename std::add_const<T>::type*;
    using reference = T&;
    using const_reference = typename std::add_const<T>::type&;
    using element_type = T;

public:
    /// Construct a copy-on-write ptr from a shared-pointer
    copy_on_write_ptr(std::shared_ptr<T>&& ptr = nullptr)
        : m_data(std::move(ptr))
    {
        if (m_data) {
            assert(m_data.use_count() == 1);
        }
    }

    /// Default move constructor.
    copy_on_write_ptr(copy_on_write_ptr&&) = default;

    /// Default move assignment operator.
    copy_on_write_ptr& operator=(copy_on_write_ptr&&) = default;

    /// Default copy constructor.
    copy_on_write_ptr(const copy_on_write_ptr&) = default;

    /// Default copy assignment operator.
    copy_on_write_ptr& operator=(const copy_on_write_ptr&) = default;

    /// Returns a const pointer to the data. Does not require ownership and will not lead to any copy.
    const T* read() const { return m_data.get(); }

    /// Returns a writable pointer to the data. Will cause a copy if ownership is shared.
    T* write()
    {
        ensure_unique_owner();
        return m_data.get();
    }

protected:
    /// Shared object.
    std::shared_ptr<T> m_data;

    /// If we are not the owner of the shared object, make a private copy of it
    void ensure_unique_owner()
    {
        if (m_data.use_count() != 1) {
            m_data = std::make_shared<T>(*m_data);
        }
    }
};

} // namespace foo
