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
#include "../common/Decimal.hpp"
#include "../enums/InstrumentClass.hpp"
#include "../enums/MatchAlgorithm.hpp"
#include "../enums/SecurityUpdateAction.hpp"
#include "../enums/UserDefinedInstrument.hpp"
#include "../enums/LegInstrumentClass.hpp"
#include "../enums/LegSide.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// A definition of an instrument; the record of the definition schema
class RecordBodyInstrumentDefMsg {
  public:
    static constexpr const char* name = "RecordBodyInstrumentDefMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodyInstrumentDefMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodyInstrumentDefMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 504;
    static constexpr std::size_t fixed_size = 504;
    std::size_t encoded_size() const { return 504; }

    std::optional<std::chrono::nanoseconds> ts_recv() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<Decimal> min_price_increment() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> display_factor() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::chrono::nanoseconds> expiration() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::chrono::nanoseconds> activation() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(32)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<Decimal> high_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(40)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> low_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(48)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> max_price_variation() const { return wire::nullable_decimal(wire::read_i64_le(at(56)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> unit_of_measure_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(64)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> min_price_increment_amount() const { return wire::nullable_decimal(wire::read_i64_le(at(72)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> price_ratio() const { return wire::nullable_decimal(wire::read_i64_le(at(80)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> strike_price() const { return wire::nullable_decimal(wire::read_i64_le(at(88)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::uint64_t raw_instrument_id() const { return wire::read_u64_le(at(96)); }

    std::optional<Decimal> leg_price() const { return wire::nullable_decimal(wire::read_i64_le(at(104)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> leg_delta() const { return wire::nullable_decimal(wire::read_i64_le(at(112)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::int32_t inst_attrib_value() const { return wire::read_i32_le(at(120)); }

    std::uint32_t underlying_id() const { return wire::read_u32_le(at(124)); }

    std::int32_t market_depth_implied() const { return wire::read_i32_le(at(128)); }

    std::int32_t market_depth() const { return wire::read_i32_le(at(132)); }

    std::uint32_t market_segment_id() const { return wire::read_u32_le(at(136)); }

    std::uint32_t max_trade_vol() const { return wire::read_u32_le(at(140)); }

    std::int32_t min_lot_size() const { return wire::read_i32_le(at(144)); }

    std::int32_t min_lot_size_block() const { return wire::read_i32_le(at(148)); }

    std::int32_t min_lot_size_round_lot() const { return wire::read_i32_le(at(152)); }

    std::uint32_t min_trade_vol() const { return wire::read_u32_le(at(156)); }

    std::int32_t contract_multiplier() const { return wire::read_i32_le(at(160)); }

    std::int32_t decay_quantity() const { return wire::read_i32_le(at(164)); }

    std::int32_t original_contract_size() const { return wire::read_i32_le(at(168)); }

    std::uint32_t leg_instrument_id() const { return wire::read_u32_le(at(172)); }

    std::int32_t leg_ratio_price_numerator() const { return wire::read_i32_le(at(176)); }

    std::int32_t leg_ratio_price_denominator() const { return wire::read_i32_le(at(180)); }

    std::int32_t leg_ratio_qty_numerator() const { return wire::read_i32_le(at(184)); }

    std::int32_t leg_ratio_qty_denominator() const { return wire::read_i32_le(at(188)); }

    std::uint32_t leg_underlying_id() const { return wire::read_u32_le(at(192)); }

    std::int16_t appl_id() const { return wire::read_i16_le(at(196)); }

    std::uint16_t maturity_year() const { return wire::read_u16_le(at(198)); }

    std::uint16_t decay_start_date() const { return wire::read_u16_le(at(200)); }

    std::uint16_t channel() const { return wire::read_u16_le(at(202)); }

    std::uint16_t leg_count() const { return wire::read_u16_le(at(204)); }

    std::uint16_t leg_index() const { return wire::read_u16_le(at(206)); }

    std::string_view currency() const { return view::text(at(208), 4, '\0'); }

    std::string_view settl_currency() const { return view::text(at(212), 4, '\0'); }

    std::string_view secsubtype() const { return view::text(at(216), 6, '\0'); }

    std::string_view raw_symbol() const { return view::text(at(222), 71, '\0'); }

    std::string_view group() const { return view::text(at(293), 21, '\0'); }

    std::string_view exchange() const { return view::text(at(314), 5, '\0'); }

    std::string_view asset() const { return view::text(at(319), 11, '\0'); }

    std::string_view cfi() const { return view::text(at(330), 7, '\0'); }

    std::string_view security_type() const { return view::text(at(337), 7, '\0'); }

    std::string_view unit_of_measure() const { return view::text(at(344), 31, '\0'); }

    std::string_view underlying() const { return view::text(at(375), 21, '\0'); }

    std::string_view strike_price_currency() const { return view::text(at(396), 4, '\0'); }

    std::string_view leg_raw_symbol() const { return view::text(at(400), 71, '\0'); }

    InstrumentClass instrument_class() const { return static_cast<InstrumentClass>(wire::read_char(at(471))); }

    MatchAlgorithm match_algorithm() const { return static_cast<MatchAlgorithm>(wire::read_char(at(472))); }

    std::uint8_t main_fraction() const { return wire::read_u8(at(473)); }

    std::uint8_t price_display_format() const { return wire::read_u8(at(474)); }

    std::uint8_t sub_fraction() const { return wire::read_u8(at(475)); }

    std::uint8_t underlying_product() const { return wire::read_u8(at(476)); }

    SecurityUpdateAction security_update_action() const { return static_cast<SecurityUpdateAction>(wire::read_char(at(477))); }

    std::uint8_t maturity_month() const { return wire::read_u8(at(478)); }

    std::uint8_t maturity_day() const { return wire::read_u8(at(479)); }

    std::uint8_t maturity_week() const { return wire::read_u8(at(480)); }

    UserDefinedInstrument user_defined_instrument() const { return static_cast<UserDefinedInstrument>(wire::read_char(at(481))); }

    std::int8_t contract_multiplier_unit() const { return wire::read_i8(at(482)); }

    std::int8_t flow_schedule_type() const { return wire::read_i8(at(483)); }

    std::uint8_t tick_rule() const { return wire::read_u8(at(484)); }

    LegInstrumentClass leg_instrument_class() const { return static_cast<LegInstrumentClass>(wire::read_char(at(485))); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_char(at(486))); }

    std::span<const std::byte, 17> reserved_17() const { return bytes_.subspan(487).template first<17>(); }

    void print(std::ostream& out) const {
        out << "RecordBodyInstrumentDefMsg{";
        out << "ts_recv=";
        print::optional_duration(out, ts_recv());
        out << ", min_price_increment=";
        print::optional(out, min_price_increment());
        out << ", display_factor=";
        print::optional(out, display_factor());
        out << ", expiration=";
        print::optional_duration(out, expiration());
        out << ", activation=";
        print::optional_duration(out, activation());
        out << ", high_limit_price=";
        print::optional(out, high_limit_price());
        out << ", low_limit_price=";
        print::optional(out, low_limit_price());
        out << ", max_price_variation=";
        print::optional(out, max_price_variation());
        out << ", unit_of_measure_qty=";
        print::optional(out, unit_of_measure_qty());
        out << ", min_price_increment_amount=";
        print::optional(out, min_price_increment_amount());
        out << ", price_ratio=";
        print::optional(out, price_ratio());
        out << ", strike_price=";
        print::optional(out, strike_price());
        out << ", raw_instrument_id=";
        out << raw_instrument_id();
        out << ", leg_price=";
        print::optional(out, leg_price());
        out << ", leg_delta=";
        print::optional(out, leg_delta());
        out << ", inst_attrib_value=";
        out << inst_attrib_value();
        out << ", underlying_id=";
        out << underlying_id();
        out << ", market_depth_implied=";
        out << market_depth_implied();
        out << ", market_depth=";
        out << market_depth();
        out << ", market_segment_id=";
        out << market_segment_id();
        out << ", max_trade_vol=";
        out << max_trade_vol();
        out << ", min_lot_size=";
        out << min_lot_size();
        out << ", min_lot_size_block=";
        out << min_lot_size_block();
        out << ", min_lot_size_round_lot=";
        out << min_lot_size_round_lot();
        out << ", min_trade_vol=";
        out << min_trade_vol();
        out << ", contract_multiplier=";
        out << contract_multiplier();
        out << ", decay_quantity=";
        out << decay_quantity();
        out << ", original_contract_size=";
        out << original_contract_size();
        out << ", leg_instrument_id=";
        out << leg_instrument_id();
        out << ", leg_ratio_price_numerator=";
        out << leg_ratio_price_numerator();
        out << ", leg_ratio_price_denominator=";
        out << leg_ratio_price_denominator();
        out << ", leg_ratio_qty_numerator=";
        out << leg_ratio_qty_numerator();
        out << ", leg_ratio_qty_denominator=";
        out << leg_ratio_qty_denominator();
        out << ", leg_underlying_id=";
        out << leg_underlying_id();
        out << ", appl_id=";
        out << appl_id();
        out << ", maturity_year=";
        out << maturity_year();
        out << ", decay_start_date=";
        out << decay_start_date();
        out << ", channel=";
        out << channel();
        out << ", leg_count=";
        out << leg_count();
        out << ", leg_index=";
        out << leg_index();
        out << ", currency=";
        print::text(out, currency());
        out << ", settl_currency=";
        print::text(out, settl_currency());
        out << ", secsubtype=";
        print::text(out, secsubtype());
        out << ", raw_symbol=";
        print::text(out, raw_symbol());
        out << ", group=";
        print::text(out, group());
        out << ", exchange=";
        print::text(out, exchange());
        out << ", asset=";
        print::text(out, asset());
        out << ", cfi=";
        print::text(out, cfi());
        out << ", security_type=";
        print::text(out, security_type());
        out << ", unit_of_measure=";
        print::text(out, unit_of_measure());
        out << ", underlying=";
        print::text(out, underlying());
        out << ", strike_price_currency=";
        print::text(out, strike_price_currency());
        out << ", leg_raw_symbol=";
        print::text(out, leg_raw_symbol());
        out << ", instrument_class=";
        out << instrument_class();
        out << ", match_algorithm=";
        out << match_algorithm();
        out << ", main_fraction=";
        out << static_cast<int>(main_fraction());
        out << ", price_display_format=";
        out << static_cast<int>(price_display_format());
        out << ", sub_fraction=";
        out << static_cast<int>(sub_fraction());
        out << ", underlying_product=";
        out << static_cast<int>(underlying_product());
        out << ", security_update_action=";
        out << security_update_action();
        out << ", maturity_month=";
        out << static_cast<int>(maturity_month());
        out << ", maturity_day=";
        out << static_cast<int>(maturity_day());
        out << ", maturity_week=";
        out << static_cast<int>(maturity_week());
        out << ", user_defined_instrument=";
        out << user_defined_instrument();
        out << ", contract_multiplier_unit=";
        out << static_cast<int>(contract_multiplier_unit());
        out << ", flow_schedule_type=";
        out << static_cast<int>(flow_schedule_type());
        out << ", tick_rule=";
        out << static_cast<int>(tick_rule());
        out << ", leg_instrument_class=";
        out << leg_instrument_class();
        out << ", leg_side=";
        out << leg_side();
        out << ", reserved_17=";
        print::hex(out, reserved_17().data(), reserved_17().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordBodyInstrumentDefMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
