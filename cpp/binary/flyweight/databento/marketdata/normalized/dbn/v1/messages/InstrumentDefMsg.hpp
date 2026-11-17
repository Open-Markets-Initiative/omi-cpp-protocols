// Databento.MarketData.Normalized.Dbn.v1: messages/InstrumentDefMsg.hpp
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

namespace databento::marketdata::normalized::dbn::v1 {

// A definition of an instrument; the record of the definition schema
class InstrumentDefMsg {
  public:
    static constexpr const char* name = "InstrumentDefMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentDefMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentDefMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 344;
    static constexpr std::size_t fixed_size = 344;
    std::size_t encoded_size() const { return 344; }

    std::optional<std::chrono::nanoseconds> ts_recv() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<Decimal> min_price_increment() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> display_factor() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<std::chrono::nanoseconds> expiration() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<std::chrono::nanoseconds> activation() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(32)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    std::optional<Decimal> high_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(40)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> low_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(48)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> max_price_variation() const { return wire::nullable_decimal(wire::read_i64_le(at(56)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> trading_reference_price() const { return wire::nullable_decimal(wire::read_i64_le(at(64)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> unit_of_measure_qty() const { return wire::nullable_decimal(wire::read_i64_le(at(72)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> min_price_increment_amount() const { return wire::nullable_decimal(wire::read_i64_le(at(80)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> price_ratio() const { return wire::nullable_decimal(wire::read_i64_le(at(88)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::int32_t inst_attrib_value() const { return wire::read_i32_le(at(96)); }

    std::uint32_t underlying_id() const { return wire::read_u32_le(at(100)); }

    std::uint32_t raw_instrument_id() const { return wire::read_u32_le(at(104)); }

    std::int32_t market_depth_implied() const { return wire::read_i32_le(at(108)); }

    std::int32_t market_depth() const { return wire::read_i32_le(at(112)); }

    std::uint32_t market_segment_id() const { return wire::read_u32_le(at(116)); }

    std::uint32_t max_trade_vol() const { return wire::read_u32_le(at(120)); }

    std::int32_t min_lot_size() const { return wire::read_i32_le(at(124)); }

    std::int32_t min_lot_size_block() const { return wire::read_i32_le(at(128)); }

    std::int32_t min_lot_size_round_lot() const { return wire::read_i32_le(at(132)); }

    std::uint32_t min_trade_vol() const { return wire::read_u32_le(at(136)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(140).template first<4>(); }

    std::int32_t contract_multiplier() const { return wire::read_i32_le(at(144)); }

    std::int32_t decay_quantity() const { return wire::read_i32_le(at(148)); }

    std::int32_t original_contract_size() const { return wire::read_i32_le(at(152)); }

    std::span<const std::byte, 4> second_reserved_4() const { return bytes_.subspan(156).template first<4>(); }

    std::uint16_t trading_reference_date() const { return wire::read_u16_le(at(160)); }

    std::int16_t appl_id() const { return wire::read_i16_le(at(162)); }

    std::uint16_t maturity_year() const { return wire::read_u16_le(at(164)); }

    std::uint16_t decay_start_date() const { return wire::read_u16_le(at(166)); }

    std::uint16_t channel() const { return wire::read_u16_le(at(168)); }

    std::string_view currency() const { return view::text(at(170), 4, '\0'); }

    std::string_view settl_currency() const { return view::text(at(174), 4, '\0'); }

    std::string_view secsubtype() const { return view::text(at(178), 6, '\0'); }

    std::string_view raw_symbol() const { return view::text(at(184), 22, '\0'); }

    std::string_view group() const { return view::text(at(206), 21, '\0'); }

    std::string_view exchange() const { return view::text(at(227), 5, '\0'); }

    std::string_view asset() const { return view::text(at(232), 7, '\0'); }

    std::string_view cfi() const { return view::text(at(239), 7, '\0'); }

    std::string_view security_type() const { return view::text(at(246), 7, '\0'); }

    std::string_view unit_of_measure() const { return view::text(at(253), 31, '\0'); }

    std::string_view underlying() const { return view::text(at(284), 21, '\0'); }

    std::string_view strike_price_currency() const { return view::text(at(305), 4, '\0'); }

    InstrumentClass instrument_class() const { return static_cast<InstrumentClass>(wire::read_char(at(309))); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(310).template first<2>(); }

    std::optional<Decimal> strike_price() const { return wire::nullable_decimal(wire::read_i64_le(at(312)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::span<const std::byte, 6> reserved_6() const { return bytes_.subspan(320).template first<6>(); }

    MatchAlgorithm match_algorithm() const { return static_cast<MatchAlgorithm>(wire::read_char(at(326))); }

    std::uint8_t md_security_trading_status() const { return wire::read_u8(at(327)); }

    std::uint8_t main_fraction() const { return wire::read_u8(at(328)); }

    std::uint8_t price_display_format() const { return wire::read_u8(at(329)); }

    std::uint8_t settl_price_type() const { return wire::read_u8(at(330)); }

    std::uint8_t sub_fraction() const { return wire::read_u8(at(331)); }

    std::uint8_t underlying_product() const { return wire::read_u8(at(332)); }

    SecurityUpdateAction security_update_action() const { return static_cast<SecurityUpdateAction>(wire::read_char(at(333))); }

    std::uint8_t maturity_month() const { return wire::read_u8(at(334)); }

    std::uint8_t maturity_day() const { return wire::read_u8(at(335)); }

    std::uint8_t maturity_week() const { return wire::read_u8(at(336)); }

    UserDefinedInstrument user_defined_instrument() const { return static_cast<UserDefinedInstrument>(wire::read_char(at(337))); }

    std::int8_t contract_multiplier_unit() const { return wire::read_i8(at(338)); }

    std::int8_t flow_schedule_type() const { return wire::read_i8(at(339)); }

    std::uint8_t tick_rule() const { return wire::read_u8(at(340)); }

    std::span<const std::byte, 3> dummy_3() const { return bytes_.subspan(341).template first<3>(); }

    void print(std::ostream& out) const {
        out << "InstrumentDefMsg{";
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
        out << ", trading_reference_price=";
        print::optional(out, trading_reference_price());
        out << ", unit_of_measure_qty=";
        print::optional(out, unit_of_measure_qty());
        out << ", min_price_increment_amount=";
        print::optional(out, min_price_increment_amount());
        out << ", price_ratio=";
        print::optional(out, price_ratio());
        out << ", inst_attrib_value=";
        out << inst_attrib_value();
        out << ", underlying_id=";
        out << underlying_id();
        out << ", raw_instrument_id=";
        out << raw_instrument_id();
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
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << ", contract_multiplier=";
        out << contract_multiplier();
        out << ", decay_quantity=";
        out << decay_quantity();
        out << ", original_contract_size=";
        out << original_contract_size();
        out << ", second_reserved_4=";
        print::hex(out, second_reserved_4().data(), second_reserved_4().size());
        out << ", trading_reference_date=";
        out << trading_reference_date();
        out << ", appl_id=";
        out << appl_id();
        out << ", maturity_year=";
        out << maturity_year();
        out << ", decay_start_date=";
        out << decay_start_date();
        out << ", channel=";
        out << channel();
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
        out << ", instrument_class=";
        out << instrument_class();
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << ", strike_price=";
        print::optional(out, strike_price());
        out << ", reserved_6=";
        print::hex(out, reserved_6().data(), reserved_6().size());
        out << ", match_algorithm=";
        out << match_algorithm();
        out << ", md_security_trading_status=";
        out << static_cast<int>(md_security_trading_status());
        out << ", main_fraction=";
        out << static_cast<int>(main_fraction());
        out << ", price_display_format=";
        out << static_cast<int>(price_display_format());
        out << ", settl_price_type=";
        out << static_cast<int>(settl_price_type());
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
        out << ", dummy_3=";
        print::hex(out, dummy_3().data(), dummy_3().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentDefMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
