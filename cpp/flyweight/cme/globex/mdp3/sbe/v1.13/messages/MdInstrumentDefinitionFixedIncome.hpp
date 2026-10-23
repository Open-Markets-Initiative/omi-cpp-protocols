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
#include "../enums/SecurityAltIdSource.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/LotTypeRulesGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// MDInstrumentDefinitionFixedIncome
class MdInstrumentDefinitionFixedIncome {
  public:
    static constexpr const char* name = "MdInstrumentDefinitionFixedIncome";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MdInstrumentDefinitionFixedIncome(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MdInstrumentDefinitionFixedIncome has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 338;
    std::size_t encoded_size() const { return lot_type_rules_groups_end(); }

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

    char match_algorithm() const { return wire::read_char(at(77)); }

    std::uint32_t min_trade_vol() const { return wire::read_u32_le(at(78)); }

    std::uint32_t max_trade_vol() const { return wire::read_u32_le(at(82)); }

    std::optional<Decimal> min_price_increment_optional_ex() const { return wire::nullable_decimal(wire::read_i64_le(at(86)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    Decimal display_factor() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(94))), -9); }

    std::optional<std::uint8_t> main_fraction() const { return wire::nullable(wire::read_u8(at(102)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> sub_fraction() const { return wire::nullable(wire::read_u8(at(103)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<std::uint8_t> price_display_format() const { return wire::nullable(wire::read_u8(at(104)), static_cast<std::uint8_t>(255ULL)); }

    std::string_view unit_of_measure() const { return view::text(at(105), 30, '\0'); }

    std::optional<Decimal> unit_of_measure_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(135)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> trading_reference_price() const { return wire::nullable_decimal(wire::read_i64_le(at(143)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::uint16_t> trading_reference_date() const { return wire::nullable(wire::read_u16_le(at(151)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<Decimal> high_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(153)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> low_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(161)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> max_price_variation() const { return wire::nullable_decimal(wire::read_i64_le(at(169)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> min_price_increment_amount() const { return wire::nullable_decimal(wire::read_i64_le(at(177)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::uint16_t> issue_date() const { return wire::nullable(wire::read_u16_le(at(185)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<std::uint16_t> dated_date() const { return wire::nullable(wire::read_u16_le(at(187)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<std::uint16_t> maturity_date() const { return wire::nullable(wire::read_u16_le(at(189)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<Decimal> coupon_rate() const { return wire::nullable_decimal(wire::read_i64_le(at(191)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> par_value() const { return wire::nullable_decimal(wire::read_i64_le(at(199)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::string_view coupon_frequency_unit() const { return view::text(at(207), 3, '\0'); }

    std::optional<std::uint16_t> coupon_frequency_period() const { return wire::nullable(wire::read_u16_le(at(210)), static_cast<std::uint16_t>(65535ULL)); }

    std::string_view coupon_day_count() const { return view::text(at(212), 20, '\0'); }

    std::string_view country_of_issue() const { return view::text(at(232), 2, '\0'); }

    std::string_view issuer() const { return view::text(at(234), 25, '\0'); }

    std::string_view financial_instrument_full_name() const { return view::text(at(259), 35, '\0'); }

    std::string_view security_alt_id() const { return view::text(at(294), 12, '\0'); }

    std::optional<SecurityAltIdSource> security_alt_id_source() const { return wire::nullable_enum<SecurityAltIdSource>(wire::read_u8(at(306)), static_cast<std::uint8_t>(255ULL)); }

    std::string_view price_quote_method() const { return view::text(at(307), 5, '\0'); }

    std::string_view party_role_clearing_org() const { return view::text(at(312), 5, '\0'); }

    char user_defined_instrument() const { return wire::read_char(at(317)); }

    std::string_view risk_set() const { return view::text(at(318), 6, '\0'); }

    std::string_view market_set() const { return view::text(at(324), 6, '\0'); }

    std::optional<std::uint64_t> instrument_guid() const { return wire::nullable(wire::read_u64_le(at(330)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    EventsGroups events_groups() const { return EventsGroups{ bytes_.subspan(338) }; }

    FeedTypesGroups feed_types_groups() const {
        wire::require("MdInstrumentDefinitionFixedIncome", events_groups_end() + FeedTypesGroups::minimum_size, bytes_.size());
        return FeedTypesGroups{ bytes_.subspan(events_groups_end()) };
    }

    InstAttribGroups inst_attrib_groups() const {
        wire::require("MdInstrumentDefinitionFixedIncome", feed_types_groups_end() + InstAttribGroups::minimum_size, bytes_.size());
        return InstAttribGroups{ bytes_.subspan(feed_types_groups_end()) };
    }

    LotTypeRulesGroups lot_type_rules_groups() const {
        wire::require("MdInstrumentDefinitionFixedIncome", inst_attrib_groups_end() + LotTypeRulesGroups::minimum_size, bytes_.size());
        return LotTypeRulesGroups{ bytes_.subspan(inst_attrib_groups_end()) };
    }

    void print(std::ostream& out) const {
        out << "MdInstrumentDefinitionFixedIncome{";
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
        out << ", match_algorithm=";
        print::character(out, match_algorithm());
        out << ", min_trade_vol=";
        out << min_trade_vol();
        out << ", max_trade_vol=";
        out << max_trade_vol();
        out << ", min_price_increment_optional_ex=";
        print::optional(out, min_price_increment_optional_ex());
        out << ", display_factor=";
        out << display_factor();
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
        out << ", trading_reference_date=";
        print::optional(out, trading_reference_date());
        out << ", high_limit_price=";
        print::optional(out, high_limit_price());
        out << ", low_limit_price=";
        print::optional(out, low_limit_price());
        out << ", max_price_variation=";
        print::optional(out, max_price_variation());
        out << ", min_price_increment_amount=";
        print::optional(out, min_price_increment_amount());
        out << ", issue_date=";
        print::optional(out, issue_date());
        out << ", dated_date=";
        print::optional(out, dated_date());
        out << ", maturity_date=";
        print::optional(out, maturity_date());
        out << ", coupon_rate=";
        print::optional(out, coupon_rate());
        out << ", par_value=";
        print::optional(out, par_value());
        out << ", coupon_frequency_unit=";
        print::text(out, coupon_frequency_unit());
        out << ", coupon_frequency_period=";
        print::optional(out, coupon_frequency_period());
        out << ", coupon_day_count=";
        print::text(out, coupon_day_count());
        out << ", country_of_issue=";
        print::text(out, country_of_issue());
        out << ", issuer=";
        print::text(out, issuer());
        out << ", financial_instrument_full_name=";
        print::text(out, financial_instrument_full_name());
        out << ", security_alt_id=";
        print::text(out, security_alt_id());
        out << ", security_alt_id_source=";
        print::optional(out, security_alt_id_source());
        out << ", price_quote_method=";
        print::text(out, price_quote_method());
        out << ", party_role_clearing_org=";
        print::text(out, party_role_clearing_org());
        out << ", user_defined_instrument=";
        print::character(out, user_defined_instrument());
        out << ", risk_set=";
        print::text(out, risk_set());
        out << ", market_set=";
        print::text(out, market_set());
        out << ", instrument_guid=";
        print::optional(out, instrument_guid());
        out << ", events_groups=";
        events_groups().print(out);
        out << ", feed_types_groups=";
        feed_types_groups().print(out);
        out << ", inst_attrib_groups=";
        inst_attrib_groups().print(out);
        out << ", lot_type_rules_groups=";
        lot_type_rules_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t events_groups_end() const { return 338 + events_groups().encoded_size(); }
    std::size_t feed_types_groups_end() const { return events_groups_end() + feed_types_groups().encoded_size(); }
    std::size_t inst_attrib_groups_end() const { return feed_types_groups_end() + inst_attrib_groups().encoded_size(); }
    std::size_t lot_type_rules_groups_end() const { return inst_attrib_groups_end() + lot_type_rules_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MdInstrumentDefinitionFixedIncome& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
