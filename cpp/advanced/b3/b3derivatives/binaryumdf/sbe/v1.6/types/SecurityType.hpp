#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// security_type
struct security_type {

    enum class enum_type : std::uint8_t {
        cash = 1,
        corp = 2,
        cs = 3,
        dterm = 4,
        etf = 5,
        fopt = 6,
        forward = 7,
        fut = 8,
        index = 9,
        indexopt = 10,
        mleg = 11,
        opt = 12,
        optexer = 13,
        ps = 14,
        secloan = 15,
        sopt = 16,
        spot = 17
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Cash", enum_type::cash},
        {"Corp", enum_type::corp},
        {"Cs", enum_type::cs},
        {"Dterm", enum_type::dterm},
        {"Etf", enum_type::etf},
        {"Fopt", enum_type::fopt},
        {"Forward", enum_type::forward},
        {"Fut", enum_type::fut},
        {"Index", enum_type::index},
        {"Indexopt", enum_type::indexopt},
        {"Mleg", enum_type::mleg},
        {"Opt", enum_type::opt},
        {"Optexer", enum_type::optexer},
        {"Ps", enum_type::ps},
        {"Secloan", enum_type::secloan},
        {"Sopt", enum_type::sopt},
        {"Spot", enum_type::spot}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::cash: return "Cash";
            case enum_type::corp: return "Corp";
            case enum_type::cs: return "Cs";
            case enum_type::dterm: return "Dterm";
            case enum_type::etf: return "Etf";
            case enum_type::fopt: return "Fopt";
            case enum_type::forward: return "Forward";
            case enum_type::fut: return "Fut";
            case enum_type::index: return "Index";
            case enum_type::indexopt: return "Indexopt";
            case enum_type::mleg: return "Mleg";
            case enum_type::opt: return "Opt";
            case enum_type::optexer: return "Optexer";
            case enum_type::ps: return "Ps";
            case enum_type::secloan: return "Secloan";
            case enum_type::sopt: return "Sopt";
            case enum_type::spot: return "Spot";
            default: return "unknown";
        }
    }

    static constexpr std::optional<enum_type> from_string(std::string_view str) {
        auto it = std::lower_bound(
            from_string_map.begin(),
            from_string_map.end(),
            str,
            [](const auto& pair, std::string_view s) { return pair.first < s; }
        );
        if (it != from_string_map.end() && it->first == str) {
            return it->second;
        }
        return std::nullopt;
    }

    static constexpr const char* name = "security_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_type::enum_type>;
    using storage_type = result_type;

    constexpr security_type()
     : value{ enum_type::cash } {}

    constexpr security_type(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(enum_type::spot);
    }

  protected:
    enum_type value;
};
}
