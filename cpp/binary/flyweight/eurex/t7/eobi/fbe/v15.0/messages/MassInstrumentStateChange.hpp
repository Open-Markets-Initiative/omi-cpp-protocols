#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/InstrumentScopeProductComplex.hpp"
#include "../enums/SecurityMassStatus.hpp"
#include "../enums/SecurityMassTradingStatus.hpp"
#include "../enums/MassMarketCondition.hpp"
#include "../enums/FastMarketIndicator.hpp"
#include "../enums/SecurityMassTradingEvent.hpp"
#include "../enums/MassSoldOutIndicator.hpp"
#include "../enums/TesSecurityMassStatus.hpp"
#include "../enums/LastFragment.hpp"
#include "../groups/SecMassStatGrpComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

class MassInstrumentStateChange {
  public:
    static constexpr const char* name = "MassInstrumentStateChange";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MassInstrumentStateChange(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MassInstrumentStateChange has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 792;
    static constexpr std::size_t fixed_size = 792;
    std::size_t encoded_size() const { return 792; }

    std::optional<InstrumentScopeProductComplex> instrument_scope_product_complex() const { return wire::nullable_enum<InstrumentScopeProductComplex>(wire::read_u8(at(0)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SecurityMassStatus> security_mass_status() const { return wire::nullable_enum<SecurityMassStatus>(wire::read_u8(at(1)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SecurityMassTradingStatus> security_mass_trading_status() const { return wire::nullable_enum<SecurityMassTradingStatus>(wire::read_u8(at(2)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MassMarketCondition> mass_market_condition() const { return wire::nullable_enum<MassMarketCondition>(wire::read_u8(at(3)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<FastMarketIndicator> fast_market_indicator() const { return wire::nullable_enum<FastMarketIndicator>(wire::read_u8(at(4)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<SecurityMassTradingEvent> security_mass_trading_event() const { return wire::nullable_enum<SecurityMassTradingEvent>(wire::read_u8(at(5)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<MassSoldOutIndicator> mass_sold_out_indicator() const { return wire::nullable_enum<MassSoldOutIndicator>(wire::read_u8(at(6)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<TesSecurityMassStatus> tes_security_mass_status() const { return wire::nullable_enum<TesSecurityMassStatus>(wire::read_u8(at(7)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<LastFragment> last_fragment() const { return wire::nullable_enum<LastFragment>(wire::read_u8(at(16)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<std::uint8_t> no_related_sym() const { return wire::nullable(wire::read_u8(at(17)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 6> pad6() const { return bytes_.subspan(18).template first<6>(); }

    view::entries<SecMassStatGrpComp> sec_mass_stat_grp_comp() const { return view::entries<SecMassStatGrpComp>{ bytes_.subspan(24), 24 }; }

    void print(std::ostream& out) const {
        out << "MassInstrumentStateChange{";
        out << "instrument_scope_product_complex=";
        print::optional(out, instrument_scope_product_complex());
        out << ", security_mass_status=";
        print::optional(out, security_mass_status());
        out << ", security_mass_trading_status=";
        print::optional(out, security_mass_trading_status());
        out << ", mass_market_condition=";
        print::optional(out, mass_market_condition());
        out << ", fast_market_indicator=";
        print::optional(out, fast_market_indicator());
        out << ", security_mass_trading_event=";
        print::optional(out, security_mass_trading_event());
        out << ", mass_sold_out_indicator=";
        print::optional(out, mass_sold_out_indicator());
        out << ", tes_security_mass_status=";
        print::optional(out, tes_security_mass_status());
        out << ", transact_time=";
        print::optional_duration(out, transact_time());
        out << ", last_fragment=";
        print::optional(out, last_fragment());
        out << ", no_related_sym=";
        print::optional(out, no_related_sym());
        out << ", pad6=";
        print::hex(out, pad6().data(), pad6().size());
        out << ", sec_mass_stat_grp_comp=";
        print::sequence(out, sec_mass_stat_grp_comp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MassInstrumentStateChange& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v15_0
