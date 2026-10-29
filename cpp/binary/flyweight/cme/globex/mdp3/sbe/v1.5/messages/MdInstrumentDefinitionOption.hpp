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
#include "../enums/PutOrCall.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../common/Decimal.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/LotTypeRulesGroups.hpp"
#include "../structs/OptionUnderlyingsGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// MDInstrumentDefinitionOption
class MdInstrumentDefinitionOption {
  public:
    static constexpr const char* name = "MdInstrumentDefinitionOption";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MdInstrumentDefinitionOption(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MdInstrumentDefinitionOption has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 211;
    std::size_t encoded_size() const { return option_underlyings_groups_end(); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(0) }; }

    std::optional<std::uint32_t> tot_num_reports_optional() const { return wire::nullable(wire::read_u32_le(at(1)), static_cast<std::uint32_t>(4294967295ULL)); }

    SecurityUpdateAction security_update_action() const { return static_cast<SecurityUpdateAction>(wire::read_char(at(5))); }

    std::chrono::nanoseconds last_update_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(6)))); }

    std::optional<MdSecurityTradingStatus> md_security_trading_status() const { return wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(at(14)), static_cast<std::uint8_t>(255ULL)); }

    std::int16_t appl_id() const { return wire::read_i16_le(at(15)); }

    std::uint8_t market_segment_id() const { return wire::read_u8(at(17)); }

    std::uint8_t underlying_product() const { return wire::read_u8(at(18)); }

    std::string_view security_exchange() const { return view::text(at(19), 4, '\0'); }

    std::string_view security_group() const { return view::text(at(23), 6, '\0'); }

    std::string_view asset() const { return view::text(at(29), 6, '\0'); }

    std::string_view symbol() const { return view::text(at(35), 20, '\0'); }

    std::int32_t security_id() const { return wire::read_i32_le(at(55)); }

    std::string_view security_type() const { return view::text(at(59), 6, '\0'); }

    std::string_view cfi_code() const { return view::text(at(65), 6, '\0'); }

    PutOrCall put_or_call() const { return static_cast<PutOrCall>(wire::read_u8(at(71))); }

    MaturityMonthYear maturity_month_year() const { return MaturityMonthYear{ bytes_.subspan(72) }; }

    std::string_view currency() const { return view::text(at(77), 3, '\0'); }

    std::optional<Decimal> strike_price() const { return wire::nullable_decimal(wire::read_i64_le(at(80)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::string_view strike_currency() const { return view::text(at(88), 3, '\0'); }

    std::string_view settl_currency() const { return view::text(at(91), 3, '\0'); }

    std::optional<Decimal> min_cab_price() const { return wire::nullable_decimal(wire::read_i64_le(at(94)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    char match_algorithm() const { return wire::read_char(at(102)); }

    std::uint32_t min_trade_vol() const { return wire::read_u32_le(at(103)); }

    std::uint32_t max_trade_vol() const { return wire::read_u32_le(at(107)); }

    std::optional<Decimal> min_price_increment_optional() const { return wire::nullable_decimal(wire::read_i64_le(at(111)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<Decimal> min_price_increment_amount() const { return wire::nullable_decimal(wire::read_i64_le(at(119)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    Decimal display_factor() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(127))), -7); }

    std::optional<std::int8_t> tick_rule() const { return wire::nullable(wire::read_i8(at(135)), static_cast<std::int8_t>(127LL)); }

    std::optional<std::uint8_t> main_fraction() const { return wire::nullable(wire::read_u8(at(136)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> sub_fraction() const { return wire::nullable(wire::read_u8(at(137)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> price_display_format() const { return wire::nullable(wire::read_u8(at(138)), static_cast<std::uint8_t>(255ULL)); }

    std::string_view unit_of_measure() const { return view::text(at(139), 30, '\0'); }

    std::optional<Decimal> unit_of_measure_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(169)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<Decimal> trading_reference_price() const { return wire::nullable_decimal(wire::read_i64_le(at(177)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    SettlPriceType settl_price_type() const { return SettlPriceType{ bytes_.subspan(185) }; }

    std::optional<std::int32_t> cleared_volume() const { return wire::nullable(wire::read_i32_le(at(186)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::int32_t> open_interest_qty() const { return wire::nullable(wire::read_i32_le(at(190)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<Decimal> low_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(194)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    std::optional<Decimal> high_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(202)), static_cast<std::int64_t>(9223372036854775807LL), -7); }

    char user_defined_instrument() const { return wire::read_char(at(210)); }

    EventsGroups events_groups() const { return EventsGroups{ bytes_.subspan(211) }; }

    FeedTypesGroups feed_types_groups() const {
        wire::require("MdInstrumentDefinitionOption", events_groups_end() + FeedTypesGroups::minimum_size, bytes_.size());
        return FeedTypesGroups{ bytes_.subspan(events_groups_end()) };
    }

    InstAttribGroups inst_attrib_groups() const {
        wire::require("MdInstrumentDefinitionOption", feed_types_groups_end() + InstAttribGroups::minimum_size, bytes_.size());
        return InstAttribGroups{ bytes_.subspan(feed_types_groups_end()) };
    }

    LotTypeRulesGroups lot_type_rules_groups() const {
        wire::require("MdInstrumentDefinitionOption", inst_attrib_groups_end() + LotTypeRulesGroups::minimum_size, bytes_.size());
        return LotTypeRulesGroups{ bytes_.subspan(inst_attrib_groups_end()) };
    }

    OptionUnderlyingsGroups option_underlyings_groups() const {
        wire::require("MdInstrumentDefinitionOption", lot_type_rules_groups_end() + OptionUnderlyingsGroups::minimum_size, bytes_.size());
        return OptionUnderlyingsGroups{ bytes_.subspan(lot_type_rules_groups_end()) };
    }

    void print(std::ostream& out) const {
        out << "MdInstrumentDefinitionOption{";
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
        out << ", underlying_product=";
        out << static_cast<int>(underlying_product());
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
        out << ", put_or_call=";
        out << put_or_call();
        out << ", maturity_month_year=";
        maturity_month_year().print(out);
        out << ", currency=";
        print::text(out, currency());
        out << ", strike_price=";
        print::optional(out, strike_price());
        out << ", strike_currency=";
        print::text(out, strike_currency());
        out << ", settl_currency=";
        print::text(out, settl_currency());
        out << ", min_cab_price=";
        print::optional(out, min_cab_price());
        out << ", match_algorithm=";
        print::character(out, match_algorithm());
        out << ", min_trade_vol=";
        out << min_trade_vol();
        out << ", max_trade_vol=";
        out << max_trade_vol();
        out << ", min_price_increment_optional=";
        print::optional(out, min_price_increment_optional());
        out << ", min_price_increment_amount=";
        print::optional(out, min_price_increment_amount());
        out << ", display_factor=";
        out << display_factor();
        out << ", tick_rule=";
        print::optional(out, tick_rule());
        out << ", main_fraction=";
        print::optional(out, main_fraction());
        out << ", sub_fraction=";
        print::optional(out, sub_fraction());
        out << ", price_display_format=";
        print::optional(out, price_display_format());
        out << ", unit_of_measure=";
        print::text(out, unit_of_measure());
        out << ", unit_of_measure_qty=";
        print::optional(out, unit_of_measure_qty());
        out << ", trading_reference_price=";
        print::optional(out, trading_reference_price());
        out << ", settl_price_type=";
        settl_price_type().print(out);
        out << ", cleared_volume=";
        print::optional(out, cleared_volume());
        out << ", open_interest_qty=";
        print::optional(out, open_interest_qty());
        out << ", low_limit_price=";
        print::optional(out, low_limit_price());
        out << ", high_limit_price=";
        print::optional(out, high_limit_price());
        out << ", user_defined_instrument=";
        print::character(out, user_defined_instrument());
        out << ", events_groups=";
        events_groups().print(out);
        out << ", feed_types_groups=";
        feed_types_groups().print(out);
        out << ", inst_attrib_groups=";
        inst_attrib_groups().print(out);
        out << ", lot_type_rules_groups=";
        lot_type_rules_groups().print(out);
        out << ", option_underlyings_groups=";
        option_underlyings_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t events_groups_end() const { return 211 + events_groups().encoded_size(); }
    std::size_t feed_types_groups_end() const { return events_groups_end() + feed_types_groups().encoded_size(); }
    std::size_t inst_attrib_groups_end() const { return feed_types_groups_end() + inst_attrib_groups().encoded_size(); }
    std::size_t lot_type_rules_groups_end() const { return inst_attrib_groups_end() + lot_type_rules_groups().encoded_size(); }
    std::size_t option_underlyings_groups_end() const { return lot_type_rules_groups_end() + option_underlyings_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MdInstrumentDefinitionOption& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
