// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/ComplexInstrumentDefinitionMessage.hpp
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
#include "../enums/TradingCollarVariationType.hpp"
#include "../groups/InstrumentLeg.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Used to disseminate all Complex Instruments traded on MIAX Futures Onyx for the current
// trading session
class ComplexInstrumentDefinitionMessage {
  public:
    static constexpr const char* name = "ComplexInstrumentDefinitionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexInstrumentDefinitionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexInstrumentDefinitionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 84;
    std::size_t encoded_size() const { return instrument_leg_end(); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint32_t strategy_id() const { return wire::read_u32_le(at(8)); }

    UnderlyingAssetType underlying_asset_type() const { return static_cast<UnderlyingAssetType>(wire::read_char(at(12))); }

    std::string_view underlying_asset() const { return view::text(at(13), 4, ' '); }

    std::string_view product_group_code() const { return view::text(at(17), 6, ' '); }

    char spread_type() const { return wire::read_char(at(23)); }

    std::string_view exchange() const { return view::text(at(24), 4, ' '); }

    InstrumentIdSource instrument_id_source() const { return static_cast<InstrumentIdSource>(wire::read_char(at(28))); }

    InstrumentType instrument_type() const { return static_cast<InstrumentType>(wire::read_char(at(29))); }

    Currency currency() const { return static_cast<Currency>(wire::read_char(at(30))); }

    SettlementCurrency settlement_currency() const { return static_cast<SettlementCurrency>(wire::read_char(at(31))); }

    MatchAlgorithm match_algorithm() const { return static_cast<MatchAlgorithm>(wire::read_char(at(32))); }

    std::uint32_t minimum_size_field() const { return wire::read_u32_le(at(33)); }

    std::uint32_t maximum_size() const { return wire::read_u32_le(at(37)); }

    Decimal tick() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(41))), -9); }

    std::string_view unit_of_measure() const { return view::text(at(49), 5, ' '); }

    std::uint32_t unit_of_measure_quantity() const { return wire::read_u32_le(at(54)); }

    TradingCollarVariationType trading_collar_variation_type() const { return static_cast<TradingCollarVariationType>(wire::read_char(at(58))); }

    Decimal trading_collar_variation() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(59))), -9); }

    std::span<const std::byte, 16> reserved_16() const { return bytes_.subspan(67).template first<16>(); }

    std::uint8_t number_of_legs() const { return wire::read_u8(at(83)); }

    view::entries<InstrumentLeg> instrument_leg() const { return view::entries<InstrumentLeg>{ bytes_.subspan(84), wire::count(number_of_legs()) }; }

    void print(std::ostream& out) const {
        out << "ComplexInstrumentDefinitionMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", strategy_id=";
        out << strategy_id();
        out << ", underlying_asset_type=";
        out << underlying_asset_type();
        out << ", underlying_asset=";
        print::text(out, underlying_asset());
        out << ", product_group_code=";
        print::text(out, product_group_code());
        out << ", spread_type=";
        print::character(out, spread_type());
        out << ", exchange=";
        print::text(out, exchange());
        out << ", instrument_id_source=";
        out << instrument_id_source();
        out << ", instrument_type=";
        out << instrument_type();
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
        out << ", trading_collar_variation_type=";
        out << trading_collar_variation_type();
        out << ", trading_collar_variation=";
        out << trading_collar_variation();
        out << ", reserved_16=";
        print::hex(out, reserved_16().data(), reserved_16().size());
        out << ", number_of_legs=";
        out << static_cast<int>(number_of_legs());
        out << ", instrument_leg=";
        print::sequence(out, instrument_leg());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t instrument_leg_end() const { return 84 + instrument_leg().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexInstrumentDefinitionMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
