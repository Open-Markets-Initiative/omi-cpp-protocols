#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/SecurityUpdateAction.hpp"
#include "../enums/MdSecurityTradingStatus.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../common/Decimal.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/LotTypeRulesGroups.hpp"
#include "../structs/LegacyLegsGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// MDInstrumentDefinitionSpread
class ServerPayloadMdInstrumentDefinitionSpread {
  public:
    static constexpr const char* name = "ServerPayloadMdInstrumentDefinitionSpread";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadMdInstrumentDefinitionSpread(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadMdInstrumentDefinitionSpread has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 193;
    std::size_t encoded_size() const { return legacy_legs_groups_end(); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(0) }; }

    std::optional<std::uint32_t> tot_num_reports_optional() const { return wire::nullable(wire::read_u32_le(at(1)), static_cast<std::uint32_t>(4294967295ULL)); }

    SecurityUpdateAction security_update_action() const { return static_cast<SecurityUpdateAction>(wire::read_char(at(5))); }

    std::chrono::nanoseconds last_update_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(6)))); }

    std::optional<MdSecurityTradingStatus> md_security_trading_status() const { return wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(at(14)), static_cast<std::uint8_t>(255ULL)); }

    std::int16_t appl_id() const { return wire::read_i16_le(at(15)); }

    std::uint8_t market_segment_id() const { return wire::read_u8(at(17)); }

    std::optional<std::uint8_t> underlying_product_optional() const { return wire::nullable(wire::read_u8(at(18)), static_cast<std::uint8_t>(255ULL)); }

    std::string_view security_exchange() const { return view::text(at(19), 4, '\0'); }

    std::string_view security_group() const { return view::text(at(23), 6, '\0'); }

    std::string_view asset() const { return view::text(at(29), 6, '\0'); }

    std::string_view symbol() const { return view::text(at(35), 20, '\0'); }

    std::int32_t security_id() const { return wire::read_i32_le(at(55)); }

    std::string_view security_type() const { return view::text(at(59), 6, '\0'); }

    std::string_view cfi_code() const { return view::text(at(65), 6, '\0'); }

    MaturityMonthYear maturity_month_year() const { return MaturityMonthYear{ bytes_.subspan(71) }; }

    std::string_view currency() const { return view::text(at(76), 3, '\0'); }

    std::string_view security_sub_type() const { return view::text(at(79), 5, '\0'); }

    char user_defined_instrument() const { return wire::read_char(at(84)); }

    char match_algorithm() const { return wire::read_char(at(85)); }

    std::uint32_t min_trade_vol() const { return wire::read_u32_le(at(86)); }

    std::uint32_t max_trade_vol() const { return wire::read_u32_le(at(90)); }

    Decimal min_price_increment() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(94))), -7); }

    Decimal display_factor() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(102))), -7); }

    std::optional<std::uint8_t> price_display_format() const { return wire::nullable(wire::read_u8(at(110)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<Decimal> price_ratio() const { return wire::nullable_decimal(wire::read_i64_le(at(111)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<std::int8_t> tick_rule() const { return wire::nullable(wire::read_i8(at(119)), static_cast<std::int8_t>(127LL)); }

    std::string_view unit_of_measure() const { return view::text(at(120), 30, '\0'); }

    std::optional<Decimal> trading_reference_price() const { return wire::nullable_decimal(wire::read_i64_le(at(150)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    SettlPriceType settl_price_type() const { return SettlPriceType{ bytes_.subspan(158) }; }

    std::optional<std::int32_t> open_interest_qty() const { return wire::nullable(wire::read_i32_le(at(159)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::int32_t> cleared_volume() const { return wire::nullable(wire::read_i32_le(at(163)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<Decimal> high_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(167)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<Decimal> low_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(175)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<Decimal> max_price_variation() const { return wire::nullable_decimal(wire::read_i64_le(at(183)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<std::uint8_t> main_fraction() const { return wire::nullable(wire::read_u8(at(191)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> sub_fraction() const { return wire::nullable(wire::read_u8(at(192)), static_cast<std::uint8_t>(255ULL)); }

    EventsGroups events_groups() const { return EventsGroups{ bytes_.subspan(193) }; }

    FeedTypesGroups feed_types_groups() const {
        wire::require("ServerPayloadMdInstrumentDefinitionSpread", events_groups_end() + FeedTypesGroups::minimum_size, bytes_.size());
        return FeedTypesGroups{ bytes_.subspan(events_groups_end()) };
    }

    InstAttribGroups inst_attrib_groups() const {
        wire::require("ServerPayloadMdInstrumentDefinitionSpread", feed_types_groups_end() + InstAttribGroups::minimum_size, bytes_.size());
        return InstAttribGroups{ bytes_.subspan(feed_types_groups_end()) };
    }

    LotTypeRulesGroups lot_type_rules_groups() const {
        wire::require("ServerPayloadMdInstrumentDefinitionSpread", inst_attrib_groups_end() + LotTypeRulesGroups::minimum_size, bytes_.size());
        return LotTypeRulesGroups{ bytes_.subspan(inst_attrib_groups_end()) };
    }

    LegacyLegsGroups legacy_legs_groups() const {
        wire::require("ServerPayloadMdInstrumentDefinitionSpread", lot_type_rules_groups_end() + LegacyLegsGroups::minimum_size, bytes_.size());
        return LegacyLegsGroups{ bytes_.subspan(lot_type_rules_groups_end()) };
    }

    void print(std::ostream& out) const {
        out << "ServerPayloadMdInstrumentDefinitionSpread{";
        out << "match_event_indicator=";
        match_event_indicator().print(out);
        out << ", tot_num_reports_optional=";
        print::optional(out, tot_num_reports_optional());
        out << ", security_update_action=";
        out << security_update_action();
        out << ", last_update_time=";
        out << last_update_time().count();
        out << ", md_security_trading_status=";
        print::optional(out, md_security_trading_status());
        out << ", appl_id=";
        out << appl_id();
        out << ", market_segment_id=";
        out << static_cast<int>(market_segment_id());
        out << ", underlying_product_optional=";
        print::optional(out, underlying_product_optional());
        out << ", security_exchange=";
        print::text(out, security_exchange());
        out << ", security_group=";
        print::text(out, security_group());
        out << ", asset=";
        print::text(out, asset());
        out << ", symbol=";
        print::text(out, symbol());
        out << ", security_id=";
        out << security_id();
        out << ", security_type=";
        print::text(out, security_type());
        out << ", cfi_code=";
        print::text(out, cfi_code());
        out << ", maturity_month_year=";
        maturity_month_year().print(out);
        out << ", currency=";
        print::text(out, currency());
        out << ", security_sub_type=";
        print::text(out, security_sub_type());
        out << ", user_defined_instrument=";
        print::character(out, user_defined_instrument());
        out << ", match_algorithm=";
        print::character(out, match_algorithm());
        out << ", min_trade_vol=";
        out << min_trade_vol();
        out << ", max_trade_vol=";
        out << max_trade_vol();
        out << ", min_price_increment=";
        out << min_price_increment();
        out << ", display_factor=";
        out << display_factor();
        out << ", price_display_format=";
        print::optional(out, price_display_format());
        out << ", price_ratio=";
        print::optional(out, price_ratio());
        out << ", tick_rule=";
        print::optional(out, tick_rule());
        out << ", unit_of_measure=";
        print::text(out, unit_of_measure());
        out << ", trading_reference_price=";
        print::optional(out, trading_reference_price());
        out << ", settl_price_type=";
        settl_price_type().print(out);
        out << ", open_interest_qty=";
        print::optional(out, open_interest_qty());
        out << ", cleared_volume=";
        print::optional(out, cleared_volume());
        out << ", high_limit_price=";
        print::optional(out, high_limit_price());
        out << ", low_limit_price=";
        print::optional(out, low_limit_price());
        out << ", max_price_variation=";
        print::optional(out, max_price_variation());
        out << ", main_fraction=";
        print::optional(out, main_fraction());
        out << ", sub_fraction=";
        print::optional(out, sub_fraction());
        out << ", events_groups=";
        events_groups().print(out);
        out << ", feed_types_groups=";
        feed_types_groups().print(out);
        out << ", inst_attrib_groups=";
        inst_attrib_groups().print(out);
        out << ", lot_type_rules_groups=";
        lot_type_rules_groups().print(out);
        out << ", legacy_legs_groups=";
        legacy_legs_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t events_groups_end() const { return 193 + events_groups().encoded_size(); }
    std::size_t feed_types_groups_end() const { return events_groups_end() + feed_types_groups().encoded_size(); }
    std::size_t inst_attrib_groups_end() const { return feed_types_groups_end() + inst_attrib_groups().encoded_size(); }
    std::size_t lot_type_rules_groups_end() const { return inst_attrib_groups_end() + lot_type_rules_groups().encoded_size(); }
    std::size_t legacy_legs_groups_end() const { return lot_type_rules_groups_end() + legacy_legs_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadMdInstrumentDefinitionSpread& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
