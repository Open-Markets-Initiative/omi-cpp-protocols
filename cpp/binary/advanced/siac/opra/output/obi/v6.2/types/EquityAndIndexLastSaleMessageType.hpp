#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// equity_and_index_last_sale_message_type
struct equity_and_index_last_sale_message_type {

    enum class enum_type : char {
        canc = 'A',
        oseq = 'B',
        cncl = 'C',
        late = 'D',
        cnco = 'E',
        open = 'F',
        cnol = 'G',
        opnl = 'H',
        auto_value = 'I',
        reop = 'J',
        ajst = 'K',
        sprd = 'L',
        stdl = 'M',
        stpd = 'N',
        cstp = 'O',
        bwrt = 'P',
        cmbo = 'Q',
        spim = 'R',
        isoi = 'S',
        bnmt = 'T',
        xmpt = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 21> from_string_map = {{
        {"Ajst", enum_type::ajst},
        {"Auto", enum_type::auto_value},
        {"Bnmt", enum_type::bnmt},
        {"Bwrt", enum_type::bwrt},
        {"Canc", enum_type::canc},
        {"Cmbo", enum_type::cmbo},
        {"Cncl", enum_type::cncl},
        {"Cnco", enum_type::cnco},
        {"Cnol", enum_type::cnol},
        {"Cstp", enum_type::cstp},
        {"Isoi", enum_type::isoi},
        {"Late", enum_type::late},
        {"Open", enum_type::open},
        {"Opnl", enum_type::opnl},
        {"Oseq", enum_type::oseq},
        {"Reop", enum_type::reop},
        {"Spim", enum_type::spim},
        {"Sprd", enum_type::sprd},
        {"Stdl", enum_type::stdl},
        {"Stpd", enum_type::stpd},
        {"Xmpt", enum_type::xmpt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::canc: return "Canc";
            case enum_type::oseq: return "Oseq";
            case enum_type::cncl: return "Cncl";
            case enum_type::late: return "Late";
            case enum_type::cnco: return "Cnco";
            case enum_type::open: return "Open";
            case enum_type::cnol: return "Cnol";
            case enum_type::opnl: return "Opnl";
            case enum_type::auto_value: return "Auto";
            case enum_type::reop: return "Reop";
            case enum_type::ajst: return "Ajst";
            case enum_type::sprd: return "Sprd";
            case enum_type::stdl: return "Stdl";
            case enum_type::stpd: return "Stpd";
            case enum_type::cstp: return "Cstp";
            case enum_type::bwrt: return "Bwrt";
            case enum_type::cmbo: return "Cmbo";
            case enum_type::spim: return "Spim";
            case enum_type::isoi: return "Isoi";
            case enum_type::bnmt: return "Bnmt";
            case enum_type::xmpt: return "Xmpt";
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

    static constexpr const char* name = "equity_and_index_last_sale_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<equity_and_index_last_sale_message_type::enum_type>;
    using storage_type = result_type;

    constexpr equity_and_index_last_sale_message_type()
     : value{ enum_type{} } {}

    constexpr equity_and_index_last_sale_message_type(enum_type v)
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
            set(enum_type::xmpt);
    }

  protected:
    enum_type value;
};
}
