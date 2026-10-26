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
#include "../common/Decimal.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/FxLotTypeRulesGroups.hpp"
#include "../structs/TradingSessionsGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// MDInstrumentDefinitionFX
class ServerPayloadMdInstrumentDefinitionFx {
  public:
    static constexpr const char* name = "ServerPayloadMdInstrumentDefinitionFx";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadMdInstrumentDefinitionFx(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadMdInstrumentDefinitionFx has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 337;
    std::size_t encoded_size() const { return trading_sessions_groups_end(); }

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

    std::string_view currency() const { return view::text(at(71), 3, '\0'); }

    std::string_view settl_currency() const { return view::text(at(74), 3, '\0'); }

    std::string_view price_quote_currency() const { return view::text(at(77), 3, '\0'); }

    char match_algorithm() const { return wire::read_char(at(80)); }

    std::uint32_t min_trade_vol() const { return wire::read_u32_le(at(81)); }

    std::uint32_t max_trade_vol() const { return wire::read_u32_le(at(85)); }

    Decimal min_price_increment_ex() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(89))), -9); }

    Decimal display_factor() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(97))), -9); }

    std::uint8_t price_precision() const { return wire::read_u8(at(105)); }

    std::string_view unit_of_measure() const { return view::text(at(106), 30, '\0'); }

    std::optional<Decimal> unit_of_measure_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(136)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> high_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(144)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> low_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(152)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> max_price_variation() const { return wire::nullable_decimal(wire::read_i64_le(at(160)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    char user_defined_instrument() const { return wire::read_char(at(168)); }

    std::string_view financial_instrument_full_name() const { return view::text(at(169), 35, '\0'); }

    std::string_view fx_currency_symbol() const { return view::text(at(204), 7, '\0'); }

    std::string_view settl_type() const { return view::text(at(211), 3, '\0'); }

    std::uint16_t intervening_days() const { return wire::read_u16_le(at(214)); }

    std::string_view fx_benchmark_rate_fix() const { return view::text(at(216), 20, '\0'); }

    std::string_view rate_source() const { return view::text(at(236), 12, '\0'); }

    std::string_view fix_rate_local_time() const { return view::text(at(248), 8, '\0'); }

    std::string_view fix_rate_local_time_zone() const { return view::text(at(256), 20, '\0'); }

    std::uint32_t min_quote_life() const { return wire::read_u32_le(at(276)); }

    Decimal max_price_discretion_offset() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(280))), -9); }

    std::optional<std::uint64_t> instrument_guid() const { return wire::nullable(wire::read_u64_le(at(288)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    MaturityMonthYear maturity_month_year() const { return MaturityMonthYear{ bytes_.subspan(296) }; }

    std::string_view settlement_locale() const { return view::text(at(301), 8, '\0'); }

    std::optional<Decimal> alt_min_price_increment() const { return wire::nullable_decimal(wire::read_i64_le(at(309)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::uint32_t> alt_min_quote_life() const { return wire::nullable(wire::read_u32_le(at(317)), static_cast<std::uint32_t>(4294967295ULL)); }

    std::optional<Decimal> alt_price_increment_constraint() const { return wire::nullable_decimal(wire::read_i64_le(at(321)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> max_bid_ask_constraint() const { return wire::nullable_decimal(wire::read_i64_le(at(329)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    EventsGroups events_groups() const { return EventsGroups{ bytes_.subspan(337) }; }

    FeedTypesGroups feed_types_groups() const {
        wire::require("ServerPayloadMdInstrumentDefinitionFx", events_groups_end() + FeedTypesGroups::minimum_size, bytes_.size());
        return FeedTypesGroups{ bytes_.subspan(events_groups_end()) };
    }

    InstAttribGroups inst_attrib_groups() const {
        wire::require("ServerPayloadMdInstrumentDefinitionFx", feed_types_groups_end() + InstAttribGroups::minimum_size, bytes_.size());
        return InstAttribGroups{ bytes_.subspan(feed_types_groups_end()) };
    }

    FxLotTypeRulesGroups fx_lot_type_rules_groups() const {
        wire::require("ServerPayloadMdInstrumentDefinitionFx", inst_attrib_groups_end() + FxLotTypeRulesGroups::minimum_size, bytes_.size());
        return FxLotTypeRulesGroups{ bytes_.subspan(inst_attrib_groups_end()) };
    }

    TradingSessionsGroups trading_sessions_groups() const {
        wire::require("ServerPayloadMdInstrumentDefinitionFx", fx_lot_type_rules_groups_end() + TradingSessionsGroups::minimum_size, bytes_.size());
        return TradingSessionsGroups{ bytes_.subspan(fx_lot_type_rules_groups_end()) };
    }

    void print(std::ostream& out) const {
        out << "ServerPayloadMdInstrumentDefinitionFx{";
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
        out << ", currency=";
        print::text(out, currency());
        out << ", settl_currency=";
        print::text(out, settl_currency());
        out << ", price_quote_currency=";
        print::text(out, price_quote_currency());
        out << ", match_algorithm=";
        print::character(out, match_algorithm());
        out << ", min_trade_vol=";
        out << min_trade_vol();
        out << ", max_trade_vol=";
        out << max_trade_vol();
        out << ", min_price_increment_ex=";
        out << min_price_increment_ex();
        out << ", display_factor=";
        out << display_factor();
        out << ", price_precision=";
        out << static_cast<int>(price_precision());
        out << ", unit_of_measure=";
        print::text(out, unit_of_measure());
        out << ", unit_of_measure_qty=";
        print::optional(out, unit_of_measure_qty());
        out << ", high_limit_price=";
        print::optional(out, high_limit_price());
        out << ", low_limit_price=";
        print::optional(out, low_limit_price());
        out << ", max_price_variation=";
        print::optional(out, max_price_variation());
        out << ", user_defined_instrument=";
        print::character(out, user_defined_instrument());
        out << ", financial_instrument_full_name=";
        print::text(out, financial_instrument_full_name());
        out << ", fx_currency_symbol=";
        print::text(out, fx_currency_symbol());
        out << ", settl_type=";
        print::text(out, settl_type());
        out << ", intervening_days=";
        out << intervening_days();
        out << ", fx_benchmark_rate_fix=";
        print::text(out, fx_benchmark_rate_fix());
        out << ", rate_source=";
        print::text(out, rate_source());
        out << ", fix_rate_local_time=";
        print::text(out, fix_rate_local_time());
        out << ", fix_rate_local_time_zone=";
        print::text(out, fix_rate_local_time_zone());
        out << ", min_quote_life=";
        out << min_quote_life();
        out << ", max_price_discretion_offset=";
        out << max_price_discretion_offset();
        out << ", instrument_guid=";
        print::optional(out, instrument_guid());
        out << ", maturity_month_year=";
        maturity_month_year().print(out);
        out << ", settlement_locale=";
        print::text(out, settlement_locale());
        out << ", alt_min_price_increment=";
        print::optional(out, alt_min_price_increment());
        out << ", alt_min_quote_life=";
        print::optional(out, alt_min_quote_life());
        out << ", alt_price_increment_constraint=";
        print::optional(out, alt_price_increment_constraint());
        out << ", max_bid_ask_constraint=";
        print::optional(out, max_bid_ask_constraint());
        out << ", events_groups=";
        events_groups().print(out);
        out << ", feed_types_groups=";
        feed_types_groups().print(out);
        out << ", inst_attrib_groups=";
        inst_attrib_groups().print(out);
        out << ", fx_lot_type_rules_groups=";
        fx_lot_type_rules_groups().print(out);
        out << ", trading_sessions_groups=";
        trading_sessions_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t events_groups_end() const { return 337 + events_groups().encoded_size(); }
    std::size_t feed_types_groups_end() const { return events_groups_end() + feed_types_groups().encoded_size(); }
    std::size_t inst_attrib_groups_end() const { return feed_types_groups_end() + inst_attrib_groups().encoded_size(); }
    std::size_t fx_lot_type_rules_groups_end() const { return inst_attrib_groups_end() + fx_lot_type_rules_groups().encoded_size(); }
    std::size_t trading_sessions_groups_end() const { return fx_lot_type_rules_groups_end() + trading_sessions_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadMdInstrumentDefinitionFx& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
