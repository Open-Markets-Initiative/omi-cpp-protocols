// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/SimpleInstrumentDefinitionMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/UnderlyingAssetType.hpp"
#include "../enums/Exchange.hpp"
#include "../enums/InstrumentIdSource.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/Currency.hpp"
#include "../enums/SettlementCurrency.hpp"
#include "../enums/MatchAlgorithm.hpp"
#include "../common/Decimal.hpp"
#include "../enums/UnitOfMeasure.hpp"
#include "../enums/SettlementPriceTypeCalcMethod.hpp"
#include "../enums/TradingCollarVariationType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// used to disseminate all Simple Instruments traded on MIAX FuturesOnyx for the current
// trading session
class SimpleInstrumentDefinitionMessage {
  public:
    static constexpr const char* name = "SimpleInstrumentDefinitionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SimpleInstrumentDefinitionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SimpleInstrumentDefinitionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 119;
    static constexpr std::size_t fixed_size = 119;
    std::size_t encoded_size() const { return 119; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(8)); }

    UnderlyingAssetType underlying_asset_type() const { return static_cast<UnderlyingAssetType>(wire::read_char(at(12))); }

    std::string_view underlying_asset() const { return view::text(at(13), 4, ' '); }

    std::string_view product_group_code() const { return view::text(at(17), 6, ' '); }

    std::string_view exchange() const { return view::text(at(23), 4, ' '); }

    InstrumentIdSource instrument_id_source() const { return static_cast<InstrumentIdSource>(wire::read_char(at(27))); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(28))); }

    std::uint32_t maturity_month_year() const { return wire::read_u32_le(at(29)); }

    Currency currency() const { return static_cast<Currency>(wire::read_char(at(33))); }

    SettlementCurrency settlement_currency() const { return static_cast<SettlementCurrency>(wire::read_char(at(34))); }

    MatchAlgorithm match_algorithm() const { return static_cast<MatchAlgorithm>(wire::read_char(at(35))); }

    std::uint32_t minimum_size_field() const { return wire::read_u32_le(at(36)); }

    std::uint32_t maximum_size() const { return wire::read_u32_le(at(40)); }

    Decimal tick() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(44))), -9); }

    std::string_view unit_of_measure() const { return view::text(at(52), 5, ' '); }

    std::uint32_t unit_of_measure_quantity() const { return wire::read_u32_le(at(57)); }

    Decimal settlement_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(61))), -9); }

    SettlementPriceTypeCalcMethod settlement_price_type_calc_method() const { return static_cast<SettlementPriceTypeCalcMethod>(wire::read_char(at(69))); }

    std::uint32_t total_volume() const { return wire::read_u32_le(at(70)); }

    std::uint32_t open_interest_quantity() const { return wire::read_u32_le(at(74)); }

    Decimal high_limit_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(78))), -9); }

    Decimal low_limit_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(86))), -9); }

    TradingCollarVariationType trading_collar_variation_type() const { return static_cast<TradingCollarVariationType>(wire::read_char(at(94))); }

    Decimal trading_collar_variation() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(95))), -9); }

    std::span<const std::byte, 16> reserved_16() const { return bytes_.subspan(103).template first<16>(); }

    void print(std::ostream& out) const {
        out << "SimpleInstrumentDefinitionMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", underlying_asset_type=";
        out << underlying_asset_type();
        out << ", underlying_asset=";
        print::text(out, underlying_asset());
        out << ", product_group_code=";
        print::text(out, product_group_code());
        out << ", exchange=";
        print::text(out, exchange());
        out << ", instrument_id_source=";
        out << instrument_id_source();
        out << ", instrument_type=";
        out << instrument_type();
        out << ", maturity_month_year=";
        out << maturity_month_year();
        out << ", currency=";
        out << currency();
        out << ", settlement_currency=";
        out << settlement_currency();
        out << ", match_algorithm=";
        out << match_algorithm();
        out << ", minimum_size_field=";
        out << minimum_size_field();
        out << ", maximum_size=";
        out << maximum_size();
        out << ", tick=";
        out << tick();
        out << ", unit_of_measure=";
        print::text(out, unit_of_measure());
        out << ", unit_of_measure_quantity=";
        out << unit_of_measure_quantity();
        out << ", settlement_price=";
        out << settlement_price();
        out << ", settlement_price_type_calc_method=";
        out << settlement_price_type_calc_method();
        out << ", total_volume=";
        out << total_volume();
        out << ", open_interest_quantity=";
        out << open_interest_quantity();
        out << ", high_limit_price=";
        out << high_limit_price();
        out << ", low_limit_price=";
        out << low_limit_price();
        out << ", trading_collar_variation_type=";
        out << trading_collar_variation_type();
        out << ", trading_collar_variation=";
        out << trading_collar_variation();
        out << ", reserved_16=";
        print::hex(out, reserved_16().data(), reserved_16().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SimpleInstrumentDefinitionMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
