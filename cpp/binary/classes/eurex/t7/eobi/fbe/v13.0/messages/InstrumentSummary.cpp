#include "InstrumentSummary.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

InstrumentSummary::InstrumentSummary(std::optional<std::int64_t> security_id, std::optional<std::chrono::nanoseconds> last_update_time, std::optional<std::chrono::nanoseconds> trd_reg_ts_execution_time, std::optional<std::uint16_t> tot_no_orders, std::optional<SecurityStatus> security_status, std::optional<SecurityTradingStatus> security_trading_status, std::optional<MarketCondition> market_condition, std::optional<FastMarketIndicator> fast_market_indicator, std::optional<SecurityTradingEvent> security_trading_event, std::optional<SoldOutIndicator> sold_out_indicator, std::optional<Decimal> high_px, std::optional<Decimal> low_px, std::optional<ProductComplex> product_complex, std::optional<std::uint8_t> no_md_entries, std::optional<TesSecurityStatus> tes_security_status, const std::array<std::byte, 5>& pad5, const std::array<MdInstrumentEntryGrpComp, 15>& md_instrument_entry_grp_comp)
  : security_id_(security_id), last_update_time_(last_update_time), trd_reg_ts_execution_time_(trd_reg_ts_execution_time), tot_no_orders_(tot_no_orders), security_status_(security_status), security_trading_status_(security_trading_status), market_condition_(market_condition), fast_market_indicator_(fast_market_indicator), security_trading_event_(security_trading_event), sold_out_indicator_(sold_out_indicator), high_px_(high_px), low_px_(low_px), product_complex_(product_complex), no_md_entries_(no_md_entries), tes_security_status_(tes_security_status), pad5_(pad5), md_instrument_entry_grp_comp_(md_instrument_entry_grp_comp) {}

std::optional<std::int64_t> InstrumentSummary::security_id() const { return security_id_; }
void InstrumentSummary::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<std::chrono::nanoseconds> InstrumentSummary::last_update_time() const { return last_update_time_; }
void InstrumentSummary::set_last_update_time(std::optional<std::chrono::nanoseconds> value) { last_update_time_ = value; }

std::optional<std::chrono::nanoseconds> InstrumentSummary::trd_reg_ts_execution_time() const { return trd_reg_ts_execution_time_; }
void InstrumentSummary::set_trd_reg_ts_execution_time(std::optional<std::chrono::nanoseconds> value) { trd_reg_ts_execution_time_ = value; }

std::optional<std::uint16_t> InstrumentSummary::tot_no_orders() const { return tot_no_orders_; }
void InstrumentSummary::set_tot_no_orders(std::optional<std::uint16_t> value) { tot_no_orders_ = value; }

std::optional<SecurityStatus> InstrumentSummary::security_status() const { return security_status_; }
void InstrumentSummary::set_security_status(std::optional<SecurityStatus> value) { security_status_ = value; }

std::optional<SecurityTradingStatus> InstrumentSummary::security_trading_status() const { return security_trading_status_; }
void InstrumentSummary::set_security_trading_status(std::optional<SecurityTradingStatus> value) { security_trading_status_ = value; }

std::optional<MarketCondition> InstrumentSummary::market_condition() const { return market_condition_; }
void InstrumentSummary::set_market_condition(std::optional<MarketCondition> value) { market_condition_ = value; }

std::optional<FastMarketIndicator> InstrumentSummary::fast_market_indicator() const { return fast_market_indicator_; }
void InstrumentSummary::set_fast_market_indicator(std::optional<FastMarketIndicator> value) { fast_market_indicator_ = value; }

std::optional<SecurityTradingEvent> InstrumentSummary::security_trading_event() const { return security_trading_event_; }
void InstrumentSummary::set_security_trading_event(std::optional<SecurityTradingEvent> value) { security_trading_event_ = value; }

std::optional<SoldOutIndicator> InstrumentSummary::sold_out_indicator() const { return sold_out_indicator_; }
void InstrumentSummary::set_sold_out_indicator(std::optional<SoldOutIndicator> value) { sold_out_indicator_ = value; }

std::optional<Decimal> InstrumentSummary::high_px() const { return high_px_; }
void InstrumentSummary::set_high_px(std::optional<Decimal> value) { high_px_ = value; }

std::optional<Decimal> InstrumentSummary::low_px() const { return low_px_; }
void InstrumentSummary::set_low_px(std::optional<Decimal> value) { low_px_ = value; }

std::optional<ProductComplex> InstrumentSummary::product_complex() const { return product_complex_; }
void InstrumentSummary::set_product_complex(std::optional<ProductComplex> value) { product_complex_ = value; }

std::optional<std::uint8_t> InstrumentSummary::no_md_entries() const { return no_md_entries_; }
void InstrumentSummary::set_no_md_entries(std::optional<std::uint8_t> value) { no_md_entries_ = value; }

std::optional<TesSecurityStatus> InstrumentSummary::tes_security_status() const { return tes_security_status_; }
void InstrumentSummary::set_tes_security_status(std::optional<TesSecurityStatus> value) { tes_security_status_ = value; }

const std::array<std::byte, 5>& InstrumentSummary::pad5() const { return pad5_; }
std::array<std::byte, 5>& InstrumentSummary::pad5() { return pad5_; }
void InstrumentSummary::set_pad5(const std::array<std::byte, 5>& value) { pad5_ = value; }

const std::array<MdInstrumentEntryGrpComp, 15>& InstrumentSummary::md_instrument_entry_grp_comp() const { return md_instrument_entry_grp_comp_; }
std::array<MdInstrumentEntryGrpComp, 15>& InstrumentSummary::md_instrument_entry_grp_comp() { return md_instrument_entry_grp_comp_; }
void InstrumentSummary::set_md_instrument_entry_grp_comp(const std::array<MdInstrumentEntryGrpComp, 15>& value) { md_instrument_entry_grp_comp_ = value; }

MessageCode InstrumentSummary::type() const { return message_type; }

std::string_view InstrumentSummary::name() const { return "Instrument Summary"; }

std::size_t InstrumentSummary::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentSummary", wire_size, length);

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    last_update_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    trd_reg_ts_execution_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    tot_no_orders_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0xFFFFULL));
    offset += 2;

    security_status_ = wire::nullable_enum<SecurityStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_trading_status_ = wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    market_condition_ = wire::nullable_enum<MarketCondition>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    fast_market_indicator_ = wire::nullable_enum<FastMarketIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    security_trading_event_ = wire::nullable_enum<SecurityTradingEvent>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    sold_out_indicator_ = wire::nullable_enum<SoldOutIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    high_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    low_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    product_complex_ = wire::nullable_enum<ProductComplex>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    no_md_entries_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    tes_security_status_ = wire::nullable_enum<TesSecurityStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad5_.data(), 5);
    offset += 5;

    for (std::size_t index = 0; index < md_instrument_entry_grp_comp_.size(); ++index) {
        offset += md_instrument_entry_grp_comp_[index].decode(data + offset, length - offset);
    }

    return offset;
}

std::size_t InstrumentSummary::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentSummary", wire_size, capacity);

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_u64_le(data + offset, last_update_time_ ? static_cast<std::uint64_t>(last_update_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u64_le(data + offset, trd_reg_ts_execution_time_ ? static_cast<std::uint64_t>(trd_reg_ts_execution_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_u16_le(data + offset, tot_no_orders_.value_or(static_cast<std::uint16_t>(0xFFFFULL)));
    offset += 2;

    wire::write_u8(data + offset, security_status_ ? static_cast<std::uint8_t>(*security_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_trading_status_ ? static_cast<std::uint8_t>(*security_trading_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, market_condition_ ? static_cast<std::uint8_t>(*market_condition_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, fast_market_indicator_ ? static_cast<std::uint8_t>(*fast_market_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, security_trading_event_ ? static_cast<std::uint8_t>(*security_trading_event_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, sold_out_indicator_ ? static_cast<std::uint8_t>(*sold_out_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_i64_le(data + offset, high_px_ ? static_cast<std::int64_t>(high_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_px_ ? static_cast<std::int64_t>(low_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_u8(data + offset, product_complex_ ? static_cast<std::uint8_t>(*product_complex_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, no_md_entries_.value_or(static_cast<std::uint8_t>(0xFFULL)));
    offset += 1;

    wire::write_u8(data + offset, tes_security_status_ ? static_cast<std::uint8_t>(*tes_security_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad5_.data(), 5);
    offset += 5;

    for (const auto& entry : md_instrument_entry_grp_comp_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t InstrumentSummary::encoded_size() const {
    return wire_size;
}

void InstrumentSummary::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InstrumentSummary::clone() const {
    return std::make_unique<InstrumentSummary>(*this);
}

void InstrumentSummary::print(std::ostream& out) const {
    out << "InstrumentSummary{";
    out << "security_id=";
    print::optional(out, security_id_);
    out << ", last_update_time=";
    print::optional_duration(out, last_update_time_);
    out << ", trd_reg_ts_execution_time=";
    print::optional_duration(out, trd_reg_ts_execution_time_);
    out << ", tot_no_orders=";
    print::optional(out, tot_no_orders_);
    out << ", security_status=";
    print::optional(out, security_status_);
    out << ", security_trading_status=";
    print::optional(out, security_trading_status_);
    out << ", market_condition=";
    print::optional(out, market_condition_);
    out << ", fast_market_indicator=";
    print::optional(out, fast_market_indicator_);
    out << ", security_trading_event=";
    print::optional(out, security_trading_event_);
    out << ", sold_out_indicator=";
    print::optional(out, sold_out_indicator_);
    out << ", high_px=";
    print::optional(out, high_px_);
    out << ", low_px=";
    print::optional(out, low_px_);
    out << ", product_complex=";
    print::optional(out, product_complex_);
    out << ", no_md_entries=";
    print::optional(out, no_md_entries_);
    out << ", tes_security_status=";
    print::optional(out, tes_security_status_);
    out << ", pad5=";
    print::hex(out, pad5_.data(), pad5_.size());
    out << ", md_instrument_entry_grp_comp=";
    print::sequence(out, md_instrument_entry_grp_comp_);
    out << '}';
}

bool InstrumentSummary::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InstrumentSummary*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentSummary::operator==(const InstrumentSummary& other) const {
    return security_id_ == other.security_id_
        && last_update_time_ == other.last_update_time_
        && trd_reg_ts_execution_time_ == other.trd_reg_ts_execution_time_
        && tot_no_orders_ == other.tot_no_orders_
        && security_status_ == other.security_status_
        && security_trading_status_ == other.security_trading_status_
        && market_condition_ == other.market_condition_
        && fast_market_indicator_ == other.fast_market_indicator_
        && security_trading_event_ == other.security_trading_event_
        && sold_out_indicator_ == other.sold_out_indicator_
        && high_px_ == other.high_px_
        && low_px_ == other.low_px_
        && product_complex_ == other.product_complex_
        && no_md_entries_ == other.no_md_entries_
        && tes_security_status_ == other.tes_security_status_
        && pad5_ == other.pad5_
        && md_instrument_entry_grp_comp_ == other.md_instrument_entry_grp_comp_;
}

bool InstrumentSummary::operator!=(const InstrumentSummary& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v13_0
