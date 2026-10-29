#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// ssr_triggering_exchange_id
struct ssr_triggering_exchange_id {

    enum class enum_type : char {
        nyse_american = 'A',
        nasdaq_omx_bx = 'B',
        nyse_national = 'C',
        finra = 'D',
        ise = 'I',
        edga = 'J',
        edgx = 'K',
        chx = 'M',
        nyse = 'N',
        nyse_arca = 'P',
        nasdaq = 'Q',
        cts = 'S',
        nasdaq_omx = 'T',
        iex = 'V',
        cbsx = 'W',
        nasdaq_omx_psx = 'X',
        bats_y = 'Y',
        bats = 'Z',
        no_value = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 19> from_string_map = {{
        {"Bats", enum_type::bats},
        {"Bats Y", enum_type::bats_y},
        {"Cbsx", enum_type::cbsx},
        {"Chx", enum_type::chx},
        {"Cts", enum_type::cts},
        {"Edga", enum_type::edga},
        {"Edgx", enum_type::edgx},
        {"Finra", enum_type::finra},
        {"Iex", enum_type::iex},
        {"Ise", enum_type::ise},
        {"Nasdaq", enum_type::nasdaq},
        {"Nasdaq Omx", enum_type::nasdaq_omx},
        {"Nasdaq Omx Bx", enum_type::nasdaq_omx_bx},
        {"Nasdaq Omx Psx", enum_type::nasdaq_omx_psx},
        {"No Value", enum_type::no_value},
        {"Nyse", enum_type::nyse},
        {"Nyse American", enum_type::nyse_american},
        {"Nyse Arca", enum_type::nyse_arca},
        {"Nyse National", enum_type::nyse_national}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::nyse_american: return "Nyse American";
            case enum_type::nasdaq_omx_bx: return "Nasdaq Omx Bx";
            case enum_type::nyse_national: return "Nyse National";
            case enum_type::finra: return "Finra";
            case enum_type::ise: return "Ise";
            case enum_type::edga: return "Edga";
            case enum_type::edgx: return "Edgx";
            case enum_type::chx: return "Chx";
            case enum_type::nyse: return "Nyse";
            case enum_type::nyse_arca: return "Nyse Arca";
            case enum_type::nasdaq: return "Nasdaq";
            case enum_type::cts: return "Cts";
            case enum_type::nasdaq_omx: return "Nasdaq Omx";
            case enum_type::iex: return "Iex";
            case enum_type::cbsx: return "Cbsx";
            case enum_type::nasdaq_omx_psx: return "Nasdaq Omx Psx";
            case enum_type::bats_y: return "Bats Y";
            case enum_type::bats: return "Bats";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "ssr_triggering_exchange_id";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<ssr_triggering_exchange_id::enum_type>;
    using storage_type = result_type;

    constexpr ssr_triggering_exchange_id()
     : value{ enum_type{} } {}

    constexpr ssr_triggering_exchange_id(enum_type v)
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
            set(enum_type::no_value);
    }

  protected:
    enum_type value;
};
}
