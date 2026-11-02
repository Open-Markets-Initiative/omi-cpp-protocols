#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// match_algorithm
struct match_algorithm {

    enum class enum_type : char {
        undefined = ' ',
        allocation = 'A',
        pro_rata = 'C',
        fifo = 'F',
        configurable = 'K',
        threshold_pro_rata = 'O',
        time_pro_rata = 'P',
        threshold_pro_rata_lmm = 'Q',
        fifo_top_lmm = 'S',
        fifo_lmm = 'T',
        institutional_prioritization = 'V',
        eurodollar_futures = 'Y'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 12> from_string_map = {{
        {"Allocation", enum_type::allocation},
        {"Configurable", enum_type::configurable},
        {"Eurodollar Futures", enum_type::eurodollar_futures},
        {"Fifo", enum_type::fifo},
        {"Fifo Lmm", enum_type::fifo_lmm},
        {"Fifo Top Lmm", enum_type::fifo_top_lmm},
        {"Institutional Prioritization", enum_type::institutional_prioritization},
        {"Pro Rata", enum_type::pro_rata},
        {"Threshold Pro Rata", enum_type::threshold_pro_rata},
        {"Threshold Pro Rata Lmm", enum_type::threshold_pro_rata_lmm},
        {"Time Pro Rata", enum_type::time_pro_rata},
        {"Undefined", enum_type::undefined}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::undefined: return "Undefined";
            case enum_type::allocation: return "Allocation";
            case enum_type::pro_rata: return "Pro Rata";
            case enum_type::fifo: return "Fifo";
            case enum_type::configurable: return "Configurable";
            case enum_type::threshold_pro_rata: return "Threshold Pro Rata";
            case enum_type::time_pro_rata: return "Time Pro Rata";
            case enum_type::threshold_pro_rata_lmm: return "Threshold Pro Rata Lmm";
            case enum_type::fifo_top_lmm: return "Fifo Top Lmm";
            case enum_type::fifo_lmm: return "Fifo Lmm";
            case enum_type::institutional_prioritization: return "Institutional Prioritization";
            case enum_type::eurodollar_futures: return "Eurodollar Futures";
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

    static constexpr const char* name = "match_algorithm";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<match_algorithm::enum_type>;
    using storage_type = result_type;

    constexpr match_algorithm()
     : value{ enum_type{} } {}

    constexpr match_algorithm(enum_type v)
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
            set(enum_type::eurodollar_futures);
    }

  protected:
    enum_type value;
};
}
