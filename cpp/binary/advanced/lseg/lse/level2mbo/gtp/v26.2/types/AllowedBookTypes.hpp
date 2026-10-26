#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// allowed_book_types
struct allowed_book_types {

    using type = uint8_t;

    static constexpr type firm_quote_book = type{1} << 1;
    static constexpr type offbook = type{1} << 2;
    static constexpr type electronic_order_book = type{1} << 3;
    static constexpr type private_rfq = type{1} << 4;

    static constexpr const char* name = "allowed_book_types";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr allowed_book_types()
     : value{ 0 } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(uint8_t v) {
        value = v;
    }

    constexpr void set(result_type v) {
        if (v.has_value())
            set(v.value());
        else
            set(type{0});
    }

    [[nodiscard]] constexpr bool has(type bit) const { return (value & bit) != 0; }
    constexpr void set(type bit, bool enabled) { if (enabled) value |= bit; else value &= static_cast<type>(~bit); }

    [[nodiscard]] constexpr bool has_firm_quote_book() const { return has(firm_quote_book); }
    [[nodiscard]] constexpr bool has_offbook() const { return has(offbook); }
    [[nodiscard]] constexpr bool has_electronic_order_book() const { return has(electronic_order_book); }
    [[nodiscard]] constexpr bool has_private_rfq() const { return has(private_rfq); }

    constexpr void set_firm_quote_book(bool v) { set(firm_quote_book, v); }
    constexpr void set_offbook(bool v) { set(offbook, v); }
    constexpr void set_electronic_order_book(bool v) { set(electronic_order_book, v); }
    constexpr void set_private_rfq(bool v) { set(private_rfq, v); }

  protected:
    type value;
};
}
