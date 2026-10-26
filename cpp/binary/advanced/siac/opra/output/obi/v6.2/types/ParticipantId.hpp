#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// participant_id
struct participant_id {

    enum class enum_type : char {
        amex = 'A',
        box = 'B',
        cboe = 'C',
        emerald = 'D',
        edgx = 'E',
        gemx = 'H',
        ise = 'I',
        mrx = 'J',
        miax = 'M',
        nyse = 'N',
        opra = 'O',
        pearl = 'P',
        nasd = 'Q',
        sphr = 'S',
        bx = 'T',
        memx = 'U',
        c_2 = 'W',
        phlx = 'X',
        bats = 'Z'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 19> from_string_map = {{
        {"Amex", enum_type::amex},
        {"Bats", enum_type::bats},
        {"Box", enum_type::box},
        {"Bx", enum_type::bx},
        {"C 2", enum_type::c_2},
        {"Cboe", enum_type::cboe},
        {"Edgx", enum_type::edgx},
        {"Emerald", enum_type::emerald},
        {"Gemx", enum_type::gemx},
        {"Ise", enum_type::ise},
        {"Memx", enum_type::memx},
        {"Miax", enum_type::miax},
        {"Mrx", enum_type::mrx},
        {"Nasd", enum_type::nasd},
        {"Nyse", enum_type::nyse},
        {"Opra", enum_type::opra},
        {"Pearl", enum_type::pearl},
        {"Phlx", enum_type::phlx},
        {"Sphr", enum_type::sphr}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::amex: return "Amex";
            case enum_type::box: return "Box";
            case enum_type::cboe: return "Cboe";
            case enum_type::emerald: return "Emerald";
            case enum_type::edgx: return "Edgx";
            case enum_type::gemx: return "Gemx";
            case enum_type::ise: return "Ise";
            case enum_type::mrx: return "Mrx";
            case enum_type::miax: return "Miax";
            case enum_type::nyse: return "Nyse";
            case enum_type::opra: return "Opra";
            case enum_type::pearl: return "Pearl";
            case enum_type::nasd: return "Nasd";
            case enum_type::sphr: return "Sphr";
            case enum_type::bx: return "Bx";
            case enum_type::memx: return "Memx";
            case enum_type::c_2: return "C 2";
            case enum_type::phlx: return "Phlx";
            case enum_type::bats: return "Bats";
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

    static constexpr const char* name = "participant_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<participant_id::enum_type>;
    using storage_type = result_type;

    constexpr participant_id()
     : value{ enum_type{} } {}

    constexpr participant_id(enum_type v)
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
            set(enum_type::bats);
    }

  protected:
    enum_type value;
};
}
