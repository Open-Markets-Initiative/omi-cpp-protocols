#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

// security_directory_flags
struct security_directory_flags {

    using type = uint8_t;

    static constexpr type etp = type{1} << 5;
    static constexpr type when_issued = type{1} << 6;
    static constexpr type test_security = type{1} << 7;

    static constexpr const char* name = "security_directory_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr security_directory_flags()
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

    [[nodiscard]] constexpr bool has_etp() const { return has(etp); }
    [[nodiscard]] constexpr bool has_when_issued() const { return has(when_issued); }
    [[nodiscard]] constexpr bool has_test_security() const { return has(test_security); }

    constexpr void set_etp(bool v) { set(etp, v); }
    constexpr void set_when_issued(bool v) { set(when_issued, v); }
    constexpr void set_test_security(bool v) { set(test_security, v); }

  protected:
    type value;
};
}
