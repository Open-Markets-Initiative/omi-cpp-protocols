#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// expiration_month
struct expiration_month {

    enum class enum_type : char {
        january_call = 'A',
        january_put = 'M',
        february_call = 'B',
        february_put = 'N',
        march_call = 'C',
        march_put = 'O',
        april_call = 'D',
        april_put = 'P',
        may_call = 'E',
        may_put = 'Q',
        june_call = 'F',
        june_put = 'R',
        july_call = 'G',
        july_put = 'S',
        august_call = 'H',
        august_put = 'T',
        september_call = 'I',
        september_put = 'U',
        october_call = 'J',
        october_put = 'V',
        november_call = 'K',
        november_put = 'W',
        december_call = 'L',
        december_put = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 24> from_string_map = {{
        {"April Call", enum_type::april_call},
        {"April Put", enum_type::april_put},
        {"August Call", enum_type::august_call},
        {"August Put", enum_type::august_put},
        {"December Call", enum_type::december_call},
        {"December Put", enum_type::december_put},
        {"February Call", enum_type::february_call},
        {"February Put", enum_type::february_put},
        {"January Call", enum_type::january_call},
        {"January Put", enum_type::january_put},
        {"July Call", enum_type::july_call},
        {"July Put", enum_type::july_put},
        {"June Call", enum_type::june_call},
        {"June Put", enum_type::june_put},
        {"March Call", enum_type::march_call},
        {"March Put", enum_type::march_put},
        {"May Call", enum_type::may_call},
        {"May Put", enum_type::may_put},
        {"November Call", enum_type::november_call},
        {"November Put", enum_type::november_put},
        {"October Call", enum_type::october_call},
        {"October Put", enum_type::october_put},
        {"September Call", enum_type::september_call},
        {"September Put", enum_type::september_put}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::january_call: return "January Call";
            case enum_type::january_put: return "January Put";
            case enum_type::february_call: return "February Call";
            case enum_type::february_put: return "February Put";
            case enum_type::march_call: return "March Call";
            case enum_type::march_put: return "March Put";
            case enum_type::april_call: return "April Call";
            case enum_type::april_put: return "April Put";
            case enum_type::may_call: return "May Call";
            case enum_type::may_put: return "May Put";
            case enum_type::june_call: return "June Call";
            case enum_type::june_put: return "June Put";
            case enum_type::july_call: return "July Call";
            case enum_type::july_put: return "July Put";
            case enum_type::august_call: return "August Call";
            case enum_type::august_put: return "August Put";
            case enum_type::september_call: return "September Call";
            case enum_type::september_put: return "September Put";
            case enum_type::october_call: return "October Call";
            case enum_type::october_put: return "October Put";
            case enum_type::november_call: return "November Call";
            case enum_type::november_put: return "November Put";
            case enum_type::december_call: return "December Call";
            case enum_type::december_put: return "December Put";
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

    static constexpr const char* name = "expiration_month";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<expiration_month::enum_type>;
    using storage_type = result_type;

    constexpr expiration_month()
     : value{ enum_type{} } {}

    constexpr expiration_month(enum_type v)
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
            set(enum_type::december_put);
    }

  protected:
    enum_type value;
};
}
