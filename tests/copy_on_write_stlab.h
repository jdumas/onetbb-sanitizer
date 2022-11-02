/*
    Copyright 2013 Adobe
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
/**************************************************************************************************/

#pragma once

/**************************************************************************************************/

#include <atomic>
#include <cassert>
#include <cstddef>
#include <utility>

/**************************************************************************************************/

namespace stlab {

/**************************************************************************************************/

template <typename T> // T models Regular
class copy_on_write
{
    struct model
    {
        std::atomic<std::size_t> _count{1};

        model() noexcept(std::is_nothrow_constructible<T>::value) = default;

        template <class... Args>
        explicit model(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args&&...>::value)
            : m_value(std::forward<Args>(args)...)
        {}

        T m_value;
    };

    model* m_self;

    template <class U>
    using disable_copy = std::enable_if_t<!std::is_same<std::decay_t<U>, copy_on_write>::value>*;

    template <typename U>
    using disable_copy_assign =
        std::enable_if_t<!std::is_same<std::decay_t<U>, copy_on_write>::value, copy_on_write&>;

public:
    /* [[deprecated]] */ using value_type = T;

    using element_type = T;

    copy_on_write() noexcept(std::is_nothrow_constructible<T>::value)
    {
        static model default_s;
        m_self = &default_s;

        // coverity[useless_call]
        ++m_self->_count;
    }

    template <class U>
    copy_on_write(U&& x, disable_copy<U> = nullptr)
        : m_self(new model(std::forward<U>(x)))
    {}

    template <class U, class V, class... Args>
    copy_on_write(U&& x, V&& y, Args&&... args)
        : m_self(new model(std::forward<U>(x), std::forward<V>(y), std::forward<Args>(args)...))
    {}

    copy_on_write(const copy_on_write& x) noexcept
        : m_self(x.m_self)
    {
        assert(m_self && "FATAL (sparent) : using a moved copy_on_write object");

        // coverity[useless_call]
        ++m_self->_count;
    }
    copy_on_write(copy_on_write&& x) noexcept
        : m_self(x.m_self)
    {
        assert(m_self && "WARNING (sparent) : using a moved copy_on_write object");
        x.m_self = nullptr;
    }

    ~copy_on_write()
    {
        if (m_self && (--m_self->_count == 0)) delete m_self;
    }

    auto operator=(const copy_on_write& x) noexcept -> copy_on_write&
    {
        return *this = copy_on_write(x);
    }

    auto operator=(copy_on_write&& x) noexcept -> copy_on_write&
    {
        auto tmp = std::move(x);
        swap(*this, tmp);
        return *this;
    }

    template <class U>
    auto operator=(U&& x) -> disable_copy_assign<U>
    {
        if (m_self && unique()) {
            m_self->m_value = std::forward<U>(x);
            return *this;
        }

        return *this = copy_on_write(std::forward<U>(x));
    }

    auto write() -> element_type&
    {
        if (!unique()) *this = copy_on_write(read());

        return m_self->m_value;
    }

    auto read() const noexcept -> const element_type&
    {
        assert(m_self && "FATAL (sparent) : using a moved copy_on_write object");

        return m_self->m_value;
    }

    operator const element_type&() const noexcept { return read(); }

    auto operator*() const noexcept -> const element_type& { return read(); }

    auto operator->() const noexcept -> const element_type* { return &read(); }

    bool unique() const noexcept
    {
        assert(m_self && "FATAL (sparent) : using a moved copy_on_write object");

        return m_self->_count == 1;
    }

    bool identity(const copy_on_write& x) const noexcept
    {
        assert((m_self && x.m_self) && "FATAL (sparent) : using a moved copy_on_write object");

        return m_self == x.m_self;
    }

    friend inline void swap(copy_on_write& x, copy_on_write& y) noexcept
    {
        std::swap(x.m_self, y.m_self);
    }
};
/**************************************************************************************************/

} // namespace stlab

/**************************************************************************************************/
