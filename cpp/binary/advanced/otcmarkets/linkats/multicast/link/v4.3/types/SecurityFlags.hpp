// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SecurityFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// security_flags
struct security_flags {

    using type = uint8_t;

    static constexpr type piggyback = type{1} << 0;
    static constexpr type caveat_emptor_warning = type{1} << 1;
    static constexpr type qualified_institutional_buyers_only = type{1} << 2;
    static constexpr type unsolicited_only = type{1} << 3;
    static constexpr type bb_quoted = type{1} << 4;
    static constexpr type otc_link_ecn_eligible = type{1} << 5;
    static constexpr type otc_link_messaging_disabled = type{1} << 6;
    static constexpr type saturation_eligible = type{1} << 7;

    static constexpr const char* name = "security_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr security_flags()
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

    [[nodiscard]] constexpr bool has_piggyback() const { return has(piggyback); }
    [[nodiscard]] constexpr bool has_caveat_emptor_warning() const { return has(caveat_emptor_warning); }
    [[nodiscard]] constexpr bool has_qualified_institutional_buyers_only() const { return has(qualified_institutional_buyers_only); }
    [[nodiscard]] constexpr bool has_unsolicited_only() const { return has(unsolicited_only); }
    [[nodiscard]] constexpr bool has_bb_quoted() const { return has(bb_quoted); }
    [[nodiscard]] constexpr bool has_otc_link_ecn_eligible() const { return has(otc_link_ecn_eligible); }
    [[nodiscard]] constexpr bool has_otc_link_messaging_disabled() const { return has(otc_link_messaging_disabled); }
    [[nodiscard]] constexpr bool has_saturation_eligible() const { return has(saturation_eligible); }

    constexpr void set_piggyback(bool v) { set(piggyback, v); }
    constexpr void set_caveat_emptor_warning(bool v) { set(caveat_emptor_warning, v); }
    constexpr void set_qualified_institutional_buyers_only(bool v) { set(qualified_institutional_buyers_only, v); }
    constexpr void set_unsolicited_only(bool v) { set(unsolicited_only, v); }
    constexpr void set_bb_quoted(bool v) { set(bb_quoted, v); }
    constexpr void set_otc_link_ecn_eligible(bool v) { set(otc_link_ecn_eligible, v); }
    constexpr void set_otc_link_messaging_disabled(bool v) { set(otc_link_messaging_disabled, v); }
    constexpr void set_saturation_eligible(bool v) { set(saturation_eligible, v); }

  protected:
    type value;
};
}
