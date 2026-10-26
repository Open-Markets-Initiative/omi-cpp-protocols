#include "MassInstrumentStateChange.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

MassInstrumentStateChange::MassInstrumentStateChange(std::optional<InstrumentScopeProductComplex> instrument_scope_product_complex, std::optional<SecurityMassStatus> security_mass_status, std::optional<SecurityMassTradingStatus> security_mass_trading_status, std::optional<MassMarketCondition> mass_market_condition, std::optional<FastMarketIndicator> fast_market_indicator, std::optional<SecurityMassTradingEvent> security_mass_trading_event, std::optional<MassSoldOutIndicator> mass_sold_out_indicator, std::optional<TesSecurityMassStatus> tes_security_mass_status, std::optional<std::chrono::nanoseconds> transact_time, std::optional<LastFragment> last_fragment, std::optional<std::uint8_t> no_related_sym, const std::array<std::byte, 6>& pad6, const std::array<SecMassStatGrpComp, 24>& sec_mass_stat_grp_comp)
  : instrument_scope_product_complex_(instrument_scope_product_complex), security_mass_status_(security_mass_status), security_mass_trading_status_(security_mass_trading_status), mass_market_condition_(mass_market_condition), fast_market_indicator_(fast_market_indicator), security_mass_trading_event_(security_mass_trading_event), mass_sold_out_indicator_(mass_sold_out_indicator), tes_security_mass_status_(tes_security_mass_status), transact_time_(transact_time), last_fragment_(last_fragment), no_related_sym_(no_related_sym), pad6_(pad6), sec_mass_stat_grp_comp_(sec_mass_stat_grp_comp) {}

std::optional<InstrumentScopeProductComplex> MassInstrumentStateChange::instrument_scope_product_complex() const { return instrument_scope_product_complex_; }
void MassInstrumentStateChange::set_instrument_scope_product_complex(std::optional<InstrumentScopeProductComplex> value) { instrument_scope_product_complex_ = value; }

std::optional<SecurityMassStatus> MassInstrumentStateChange::security_mass_status() const { return security_mass_status_; }
void MassInstrumentStateChange::set_security_mass_status(std::optional<SecurityMassStatus> value) { security_mass_status_ = value; }

std::optional<SecurityMassTradingStatus> MassInstrumentStateChange::security_mass_trading_status() const { return security_mass_trading_status_; }
void MassInstrumentStateChange::set_security_mass_trading_status(std::optional<SecurityMassTradingStatus> value) { security_mass_trading_status_ = value; }

std::optional<MassMarketCondition> MassInstrumentStateChange::mass_market_condition() const { return mass_market_condition_; }
void MassInstrumentStateChange::set_mass_market_condition(std::optional<MassMarketCondition> value) { mass_market_condition_ = value; }

std::optional<FastMarketIndicator> MassInstrumentStateChange::fast_market_indicator() const { return fast_market_indicator_; }
void MassInstrumentStateChange::set_fast_market_indicator(std::optional<FastMarketIndicator> value) { fast_market_indicator_ = value; }

std::optional<SecurityMassTradingEvent> MassInstrumentStateChange::security_mass_trading_event() const { return security_mass_trading_event_; }
void MassInstrumentStateChange::set_security_mass_trading_event(std::optional<SecurityMassTradingEvent> value) { security_mass_trading_event_ = value; }

std::optional<MassSoldOutIndicator> MassInstrumentStateChange::mass_sold_out_indicator() const { return mass_sold_out_indicator_; }
void MassInstrumentStateChange::set_mass_sold_out_indicator(std::optional<MassSoldOutIndicator> value) { mass_sold_out_indicator_ = value; }

std::optional<TesSecurityMassStatus> MassInstrumentStateChange::tes_security_mass_status() const { return tes_security_mass_status_; }
void MassInstrumentStateChange::set_tes_security_mass_status(std::optional<TesSecurityMassStatus> value) { tes_security_mass_status_ = value; }

std::optional<std::chrono::nanoseconds> MassInstrumentStateChange::transact_time() const { return transact_time_; }
void MassInstrumentStateChange::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<LastFragment> MassInstrumentStateChange::last_fragment() const { return last_fragment_; }
void MassInstrumentStateChange::set_last_fragment(std::optional<LastFragment> value) { last_fragment_ = value; }

std::optional<std::uint8_t> MassInstrumentStateChange::no_related_sym() const { return no_related_sym_; }
void MassInstrumentStateChange::set_no_related_sym(std::optional<std::uint8_t> value) { no_related_sym_ = value; }

const std::array<std::byte, 6>& MassInstrumentStateChange::pad6() const { return pad6_; }
std::array<std::byte, 6>& MassInstrumentStateChange::pad6() { return pad6_; }
void MassInstrumentStateChange::set_pad6(const std::array<std::byte, 6>& value) { pad6_ = value; }

const std::array<SecMassStatGrpComp, 24>& MassInstrumentStateChange::sec_mass_stat_grp_comp() const { return sec_mass_stat_grp_comp_; }
std::array<SecMassStatGrpComp, 24>& MassInstrumentStateChange::sec_mass_stat_grp_comp() { return sec_mass_stat_grp_comp_; }
void MassInstrumentStateChange::set_sec_mass_stat_grp_comp(const std::array<SecMassStatGrpComp, 24>& value) { sec_mass_stat_grp_comp_ = value; }

MessageCode MassInstrumentStateChange::type() const { return message_type; }

std::string_view MassInstrumentStateChange::name() const { return "Mass Instrument State Change"; }

std::size_t MassInstrumentStateChange::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MassInstrumentStateChange", wire_size, length);

    instrument_scope_product_complex_ = wire::nullable_enum<InstrumentScopeProductComplex>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_mass_status_ = wire::nullable_enum<SecurityMassStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_mass_trading_status_ = wire::nullable_enum<SecurityMassTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    mass_market_condition_ = wire::nullable_enum<MassMarketCondition>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    fast_market_indicator_ = wire::nullable_enum<FastMarketIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_mass_trading_event_ = wire::nullable_enum<SecurityMassTradingEvent>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    mass_sold_out_indicator_ = wire::nullable_enum<MassSoldOutIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    tes_security_mass_status_ = wire::nullable_enum<TesSecurityMassStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    last_fragment_ = wire::nullable_enum<LastFragment>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    no_related_sym_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad6_.data(), 6);
    offset += 6;

    for (std::size_t index = 0; index < sec_mass_stat_grp_comp_.size(); ++index) {
        offset += sec_mass_stat_grp_comp_[index].decode(data + offset, length - offset);
    }

    return offset;
}

std::size_t MassInstrumentStateChange::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MassInstrumentStateChange", wire_size, capacity);

    wire::write_u8(data + offset, instrument_scope_product_complex_ ? static_cast<std::uint8_t>(*instrument_scope_product_complex_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_mass_status_ ? static_cast<std::uint8_t>(*security_mass_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_mass_trading_status_ ? static_cast<std::uint8_t>(*security_mass_trading_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, mass_market_condition_ ? static_cast<std::uint8_t>(*mass_market_condition_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, fast_market_indicator_ ? static_cast<std::uint8_t>(*fast_market_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_mass_trading_event_ ? static_cast<std::uint8_t>(*security_mass_trading_event_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, mass_sold_out_indicator_ ? static_cast<std::uint8_t>(*mass_sold_out_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, tes_security_mass_status_ ? static_cast<std::uint8_t>(*tes_security_mass_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u8(data + offset, last_fragment_ ? static_cast<std::uint8_t>(*last_fragment_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, no_related_sym_.value_or(static_cast<std::uint8_t>(0xFFULL)));
    offset += 1;

    wire::write_bytes(data + offset, pad6_.data(), 6);
    offset += 6;

    for (const auto& entry : sec_mass_stat_grp_comp_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t MassInstrumentStateChange::encoded_size() const {
    return wire_size;
}

void MassInstrumentStateChange::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MassInstrumentStateChange::clone() const {
    return std::make_unique<MassInstrumentStateChange>(*this);
}

void MassInstrumentStateChange::print(std::ostream& out) const {
    out << "MassInstrumentStateChange{";
    out << "instrument_scope_product_complex=";
    print::optional(out, instrument_scope_product_complex_);
    out << ", security_mass_status=";
    print::optional(out, security_mass_status_);
    out << ", security_mass_trading_status=";
    print::optional(out, security_mass_trading_status_);
    out << ", mass_market_condition=";
    print::optional(out, mass_market_condition_);
    out << ", fast_market_indicator=";
    print::optional(out, fast_market_indicator_);
    out << ", security_mass_trading_event=";
    print::optional(out, security_mass_trading_event_);
    out << ", mass_sold_out_indicator=";
    print::optional(out, mass_sold_out_indicator_);
    out << ", tes_security_mass_status=";
    print::optional(out, tes_security_mass_status_);
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", last_fragment=";
    print::optional(out, last_fragment_);
    out << ", no_related_sym=";
    print::optional(out, no_related_sym_);
    out << ", pad6=";
    print::hex(out, pad6_.data(), pad6_.size());
    out << ", sec_mass_stat_grp_comp=";
    print::sequence(out, sec_mass_stat_grp_comp_);
    out << '}';
}

bool MassInstrumentStateChange::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MassInstrumentStateChange*>(&other);
    return that != nullptr && *this == *that;
}

bool MassInstrumentStateChange::operator==(const MassInstrumentStateChange& other) const {
    return instrument_scope_product_complex_ == other.instrument_scope_product_complex_
        && security_mass_status_ == other.security_mass_status_
        && security_mass_trading_status_ == other.security_mass_trading_status_
        && mass_market_condition_ == other.mass_market_condition_
        && fast_market_indicator_ == other.fast_market_indicator_
        && security_mass_trading_event_ == other.security_mass_trading_event_
        && mass_sold_out_indicator_ == other.mass_sold_out_indicator_
        && tes_security_mass_status_ == other.tes_security_mass_status_
        && transact_time_ == other.transact_time_
        && last_fragment_ == other.last_fragment_
        && no_related_sym_ == other.no_related_sym_
        && pad6_ == other.pad6_
        && sec_mass_stat_grp_comp_ == other.sec_mass_stat_grp_comp_;
}

bool MassInstrumentStateChange::operator!=(const MassInstrumentStateChange& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v15_0
