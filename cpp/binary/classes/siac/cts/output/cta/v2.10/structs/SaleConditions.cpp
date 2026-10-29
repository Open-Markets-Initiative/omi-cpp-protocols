#include "SaleConditions.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_10 {

SaleConditions::SaleConditions(SettlementType settlement_type, TradeThroughExemptReason trade_through_exempt_reason, ExtendedHoursOrSequenceType extended_hours_or_sequence_type, SroTradeDetail sro_trade_detail)
  : settlement_type_(settlement_type), trade_through_exempt_reason_(trade_through_exempt_reason), extended_hours_or_sequence_type_(extended_hours_or_sequence_type), sro_trade_detail_(sro_trade_detail) {}

SettlementType SaleConditions::settlement_type() const { return settlement_type_; }
void SaleConditions::set_settlement_type(SettlementType value) { settlement_type_ = value; }

TradeThroughExemptReason SaleConditions::trade_through_exempt_reason() const { return trade_through_exempt_reason_; }
void SaleConditions::set_trade_through_exempt_reason(TradeThroughExemptReason value) { trade_through_exempt_reason_ = value; }

ExtendedHoursOrSequenceType SaleConditions::extended_hours_or_sequence_type() const { return extended_hours_or_sequence_type_; }
void SaleConditions::set_extended_hours_or_sequence_type(ExtendedHoursOrSequenceType value) { extended_hours_or_sequence_type_ = value; }

SroTradeDetail SaleConditions::sro_trade_detail() const { return sro_trade_detail_; }
void SaleConditions::set_sro_trade_detail(SroTradeDetail value) { sro_trade_detail_ = value; }

std::size_t SaleConditions::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SaleConditions", wire_size, length);

    settlement_type_ = static_cast<SettlementType>(wire::read_char(data + offset));
    offset += 1;

    trade_through_exempt_reason_ = static_cast<TradeThroughExemptReason>(wire::read_char(data + offset));
    offset += 1;

    extended_hours_or_sequence_type_ = static_cast<ExtendedHoursOrSequenceType>(wire::read_char(data + offset));
    offset += 1;

    sro_trade_detail_ = static_cast<SroTradeDetail>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SaleConditions::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SaleConditions", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(settlement_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_through_exempt_reason_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(extended_hours_or_sequence_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(sro_trade_detail_));
    offset += 1;

    return offset;
}

std::size_t SaleConditions::encoded_size() const {
    return wire_size;
}

void SaleConditions::print(std::ostream& out) const {
    out << "SaleConditions{";
    out << "settlement_type=";
    out << settlement_type_;
    out << ", trade_through_exempt_reason=";
    out << trade_through_exempt_reason_;
    out << ", extended_hours_or_sequence_type=";
    out << extended_hours_or_sequence_type_;
    out << ", sro_trade_detail=";
    out << sro_trade_detail_;
    out << '}';
}

bool SaleConditions::operator==(const SaleConditions& other) const {
    return settlement_type_ == other.settlement_type_
        && trade_through_exempt_reason_ == other.trade_through_exempt_reason_
        && extended_hours_or_sequence_type_ == other.extended_hours_or_sequence_type_
        && sro_trade_detail_ == other.sro_trade_detail_;
}

bool SaleConditions::operator!=(const SaleConditions& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SaleConditions& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
