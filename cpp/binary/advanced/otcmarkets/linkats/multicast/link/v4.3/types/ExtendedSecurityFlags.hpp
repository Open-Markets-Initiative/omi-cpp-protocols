// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ExtendedSecurityFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// extended_security_flags
struct extended_security_flags {

    using type = uint16_t;

    static constexpr type piggyback = type{1} << 0;
    static constexpr type caveat_emptor_warning = type{1} << 1;
    static constexpr type qualified_institutional_buyers_only = type{1} << 2;
    static constexpr type unsolicited_only = type{1} << 3;
    static constexpr type sponsored_status = type{1} << 4;
    static constexpr type otc_link_ecn_eligible = type{1} << 5;
    static constexpr type otc_link_messaging_disabled = type{1} << 6;
    static constexpr type saturation_eligible = type{1} << 7;
    static constexpr type investment_grade = type{1} << 8;
    static constexpr type trading_flat = type{1} << 9;
    static constexpr type callable = type{1} << 10;

    static constexpr const char* name = "extended_security_flags";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<uint16_t>;
    using storage_type = result_type;

    constexpr extended_security_flags()
     : value{ 0 } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(uint16_t v) {
        value = v;
    }

    constexpr void set(result_type v) {
        if (v.has_value())
            set(v.value());
        else
            set(type{0});
    }

    [[nodiscard]] constexpr bool has(type bit) const { return (static_cast<type>(__builtin_bswap16(value)) & bit) != 0; }
    constexpr void set(type bit, bool enabled) { type held = static_cast<type>(__builtin_bswap16(value)); if (enabled) held |= bit; else held &= static_cast<type>(~bit); value = static_cast<type>(__builtin_bswap16(held)); }

    [[nodiscard]] constexpr bool has_piggyback() const { return has(piggyback); }
    [[nodiscard]] constexpr bool has_caveat_emptor_warning() const { return has(caveat_emptor_warning); }
    [[nodiscard]] constexpr bool has_qualified_institutional_buyers_only() const { return has(qualified_institutional_buyers_only); }
    [[nodiscard]] constexpr bool has_unsolicited_only() const { return has(unsolicited_only); }
    [[nodiscard]] constexpr bool has_sponsored_status() const { return has(sponsored_status); }
    [[nodiscard]] constexpr bool has_otc_link_ecn_eligible() const { return has(otc_link_ecn_eligible); }
    [[nodiscard]] constexpr bool has_otc_link_messaging_disabled() const { return has(otc_link_messaging_disabled); }
    [[nodiscard]] constexpr bool has_saturation_eligible() const { return has(saturation_eligible); }
    [[nodiscard]] constexpr bool has_investment_grade() const { return has(investment_grade); }
    [[nodiscard]] constexpr bool has_trading_flat() const { return has(trading_flat); }
    [[nodiscard]] constexpr bool has_callable() const { return has(callable); }

    constexpr void set_piggyback(bool v) { set(piggyback, v); }
    constexpr void set_caveat_emptor_warning(bool v) { set(caveat_emptor_warning, v); }
    constexpr void set_qualified_institutional_buyers_only(bool v) { set(qualified_institutional_buyers_only, v); }
    constexpr void set_unsolicited_only(bool v) { set(unsolicited_only, v); }
    constexpr void set_sponsored_status(bool v) { set(sponsored_status, v); }
    constexpr void set_otc_link_ecn_eligible(bool v) { set(otc_link_ecn_eligible, v); }
    constexpr void set_otc_link_messaging_disabled(bool v) { set(otc_link_messaging_disabled, v); }
    constexpr void set_saturation_eligible(bool v) { set(saturation_eligible, v); }
    constexpr void set_investment_grade(bool v) { set(investment_grade, v); }
    constexpr void set_trading_flat(bool v) { set(trading_flat, v); }
    constexpr void set_callable(bool v) { set(callable, v); }

  protected:
    type value;
};
}
