#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// schema
struct schema {

    enum class enum_type : std::uint16_t {
        mbo = 0,
        mbp1 = 1,
        mbp10 = 2,
        tbbo = 3,
        trades = 4,
        ohlcv1_s = 5,
        ohlcv1_m = 6,
        ohlcv1_h = 7,
        ohlcv1_d = 8,
        definition = 9,
        statistics = 10,
        status = 11,
        imbalance = 12,
        ohlcv_eod = 13,
        cmbp1 = 14,
        cbbo1_s = 15,
        cbbo1_m = 16,
        tcbbo = 17,
        bbo1_s = 18,
        bbo1_m = 19,
        no_value = 65535
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 21> from_string_map = {{
        {"Bbo1 M", enum_type::bbo1_m},
        {"Bbo1 S", enum_type::bbo1_s},
        {"Cbbo1 M", enum_type::cbbo1_m},
        {"Cbbo1 S", enum_type::cbbo1_s},
        {"Cmbp1", enum_type::cmbp1},
        {"Definition", enum_type::definition},
        {"Imbalance", enum_type::imbalance},
        {"Mbo", enum_type::mbo},
        {"Mbp1", enum_type::mbp1},
        {"Mbp10", enum_type::mbp10},
        {"No Value", enum_type::no_value},
        {"Ohlcv Eod", enum_type::ohlcv_eod},
        {"Ohlcv1 D", enum_type::ohlcv1_d},
        {"Ohlcv1 H", enum_type::ohlcv1_h},
        {"Ohlcv1 M", enum_type::ohlcv1_m},
        {"Ohlcv1 S", enum_type::ohlcv1_s},
        {"Statistics", enum_type::statistics},
        {"Status", enum_type::status},
        {"Tbbo", enum_type::tbbo},
        {"Tcbbo", enum_type::tcbbo},
        {"Trades", enum_type::trades}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::mbo: return "Mbo";
            case enum_type::mbp1: return "Mbp1";
            case enum_type::mbp10: return "Mbp10";
            case enum_type::tbbo: return "Tbbo";
            case enum_type::trades: return "Trades";
            case enum_type::ohlcv1_s: return "Ohlcv1 S";
            case enum_type::ohlcv1_m: return "Ohlcv1 M";
            case enum_type::ohlcv1_h: return "Ohlcv1 H";
            case enum_type::ohlcv1_d: return "Ohlcv1 D";
            case enum_type::definition: return "Definition";
            case enum_type::statistics: return "Statistics";
            case enum_type::status: return "Status";
            case enum_type::imbalance: return "Imbalance";
            case enum_type::ohlcv_eod: return "Ohlcv Eod";
            case enum_type::cmbp1: return "Cmbp1";
            case enum_type::cbbo1_s: return "Cbbo1 S";
            case enum_type::cbbo1_m: return "Cbbo1 M";
            case enum_type::tcbbo: return "Tcbbo";
            case enum_type::bbo1_s: return "Bbo1 S";
            case enum_type::bbo1_m: return "Bbo1 M";
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

    static constexpr const char* name = "schema";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<schema::enum_type>;
    using storage_type = result_type;

    constexpr schema()
     : value{ static_cast<enum_type>(65535) } {}

    constexpr schema(enum_type v)
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
            set(static_cast<enum_type>(65535));
    }

  protected:
    enum_type value;
};
}
