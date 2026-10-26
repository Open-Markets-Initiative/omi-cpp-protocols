#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/FastMarketIndicator.hpp"
#include "../enums/InstrumentScopeProductComplex.hpp"
#include "../enums/LastFragment.hpp"
#include "../enums/MassMarketCondition.hpp"
#include "../enums/MassSoldOutIndicator.hpp"
#include "../enums/SecurityMassStatus.hpp"
#include "../enums/SecurityMassTradingEvent.hpp"
#include "../enums/SecurityMassTradingStatus.hpp"
#include "../enums/TesSecurityMassStatus.hpp"
#include "../groups/SecMassStatGrpComp.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class Visitor;

// Mass Instrument State Change
class MassInstrumentStateChange : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::MassInstrumentStateChange;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 792;

    MassInstrumentStateChange() = default;
    MassInstrumentStateChange(std::optional<InstrumentScopeProductComplex> instrument_scope_product_complex, std::optional<SecurityMassStatus> security_mass_status, std::optional<SecurityMassTradingStatus> security_mass_trading_status, std::optional<MassMarketCondition> mass_market_condition, std::optional<FastMarketIndicator> fast_market_indicator, std::optional<SecurityMassTradingEvent> security_mass_trading_event, std::optional<MassSoldOutIndicator> mass_sold_out_indicator, std::optional<TesSecurityMassStatus> tes_security_mass_status, std::optional<std::chrono::nanoseconds> transact_time, std::optional<LastFragment> last_fragment, std::optional<std::uint8_t> no_related_sym, const std::array<std::byte, 6>& pad6, const std::array<SecMassStatGrpComp, 24>& sec_mass_stat_grp_comp);

    // Instrument Scope Product Complex:
    std::optional<InstrumentScopeProductComplex> instrument_scope_product_complex() const;
    void set_instrument_scope_product_complex(std::optional<InstrumentScopeProductComplex> value);

    // Security Mass Status:
    std::optional<SecurityMassStatus> security_mass_status() const;
    void set_security_mass_status(std::optional<SecurityMassStatus> value);

    // Security Mass Trading Status:
    std::optional<SecurityMassTradingStatus> security_mass_trading_status() const;
    void set_security_mass_trading_status(std::optional<SecurityMassTradingStatus> value);

    // Mass Market Condition:
    std::optional<MassMarketCondition> mass_market_condition() const;
    void set_mass_market_condition(std::optional<MassMarketCondition> value);

    // Fast Market Indicator:
    std::optional<FastMarketIndicator> fast_market_indicator() const;
    void set_fast_market_indicator(std::optional<FastMarketIndicator> value);

    // Security Mass Trading Event:
    std::optional<SecurityMassTradingEvent> security_mass_trading_event() const;
    void set_security_mass_trading_event(std::optional<SecurityMassTradingEvent> value);

    // Mass Sold Out Indicator:
    std::optional<MassSoldOutIndicator> mass_sold_out_indicator() const;
    void set_mass_sold_out_indicator(std::optional<MassSoldOutIndicator> value);

    // Tes Security Mass Status:
    std::optional<TesSecurityMassStatus> tes_security_mass_status() const;
    void set_tes_security_mass_status(std::optional<TesSecurityMassStatus> value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Last Fragment:
    std::optional<LastFragment> last_fragment() const;
    void set_last_fragment(std::optional<LastFragment> value);

    // No Related Sym:
    std::optional<std::uint8_t> no_related_sym() const;
    void set_no_related_sym(std::optional<std::uint8_t> value);

    // Pad6:
    const std::array<std::byte, 6>& pad6() const;
    std::array<std::byte, 6>& pad6();
    void set_pad6(const std::array<std::byte, 6>& value);

    // Sec Mass Stat Grp Comp:
    const std::array<SecMassStatGrpComp, 24>& sec_mass_stat_grp_comp() const;
    std::array<SecMassStatGrpComp, 24>& sec_mass_stat_grp_comp();
    void set_sec_mass_stat_grp_comp(const std::array<SecMassStatGrpComp, 24>& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const MassInstrumentStateChange& other) const;
    bool operator!=(const MassInstrumentStateChange& other) const;

  private:
    std::optional<InstrumentScopeProductComplex> instrument_scope_product_complex_{};
    std::optional<SecurityMassStatus> security_mass_status_{};
    std::optional<SecurityMassTradingStatus> security_mass_trading_status_{};
    std::optional<MassMarketCondition> mass_market_condition_{};
    std::optional<FastMarketIndicator> fast_market_indicator_{};
    std::optional<SecurityMassTradingEvent> security_mass_trading_event_{};
    std::optional<MassSoldOutIndicator> mass_sold_out_indicator_{};
    std::optional<TesSecurityMassStatus> tes_security_mass_status_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
    std::optional<LastFragment> last_fragment_{};
    std::optional<std::uint8_t> no_related_sym_{};
    std::array<std::byte, 6> pad6_{};
    std::array<SecMassStatGrpComp, 24> sec_mass_stat_grp_comp_{};
};

} // namespace eurex::t7::eobi::fbe::v13_0
