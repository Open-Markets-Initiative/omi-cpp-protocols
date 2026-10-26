#include "FractionalLongTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

FractionalLongTradeMessage::FractionalLongTradeMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const SaleCondition4& sale_condition_4, Decimal trade_price, Decimal fractional_trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, TradeReportingFacilityId trade_reporting_facility_id, const Timestamp2& timestamp_2, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, HeldTradeIndicator held_trade_indicator, ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator, ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), sale_condition_4_(sale_condition_4), trade_price_(trade_price), fractional_trade_volume_(fractional_trade_volume), sellers_sale_days_(sellers_sale_days), stop_stock_indicator_(stop_stock_indicator), trade_through_exempt_indicator_(trade_through_exempt_indicator), trade_reporting_facility_id_(trade_reporting_facility_id), timestamp_2_(timestamp_2), short_sale_restriction_indicator_(short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), held_trade_indicator_(held_trade_indicator), consolidated_high_low_last_indicator_(consolidated_high_low_last_indicator), participant_open_high_low_last_indicator_(participant_open_high_low_last_indicator) {}

ParticipantId FractionalLongTradeMessage::participant_id() const { return participant_id_; }
void FractionalLongTradeMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& FractionalLongTradeMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& FractionalLongTradeMessage::timestamp_1() { return timestamp_1_; }
void FractionalLongTradeMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t FractionalLongTradeMessage::message_id() const { return message_id_; }
void FractionalLongTradeMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t FractionalLongTradeMessage::transaction_id() const { return transaction_id_; }
void FractionalLongTradeMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t FractionalLongTradeMessage::participant_reference_number() const { return participant_reference_number_; }
void FractionalLongTradeMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& FractionalLongTradeMessage::security_symbol() const { return security_symbol_; }
std::string& FractionalLongTradeMessage::security_symbol() { return security_symbol_; }
void FractionalLongTradeMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType FractionalLongTradeMessage::instrument_type() const { return instrument_type_; }
void FractionalLongTradeMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

const SaleCondition4& FractionalLongTradeMessage::sale_condition_4() const { return sale_condition_4_; }
SaleCondition4& FractionalLongTradeMessage::sale_condition_4() { return sale_condition_4_; }
void FractionalLongTradeMessage::set_sale_condition_4(const SaleCondition4& value) { sale_condition_4_ = value; }

Decimal FractionalLongTradeMessage::trade_price() const { return trade_price_; }
void FractionalLongTradeMessage::set_trade_price(Decimal value) { trade_price_ = value; }

Decimal FractionalLongTradeMessage::fractional_trade_volume() const { return fractional_trade_volume_; }
void FractionalLongTradeMessage::set_fractional_trade_volume(Decimal value) { fractional_trade_volume_ = value; }

std::uint8_t FractionalLongTradeMessage::sellers_sale_days() const { return sellers_sale_days_; }
void FractionalLongTradeMessage::set_sellers_sale_days(std::uint8_t value) { sellers_sale_days_ = value; }

StopStockIndicator FractionalLongTradeMessage::stop_stock_indicator() const { return stop_stock_indicator_; }
void FractionalLongTradeMessage::set_stop_stock_indicator(StopStockIndicator value) { stop_stock_indicator_ = value; }

TradeThroughExemptIndicator FractionalLongTradeMessage::trade_through_exempt_indicator() const { return trade_through_exempt_indicator_; }
void FractionalLongTradeMessage::set_trade_through_exempt_indicator(TradeThroughExemptIndicator value) { trade_through_exempt_indicator_ = value; }

TradeReportingFacilityId FractionalLongTradeMessage::trade_reporting_facility_id() const { return trade_reporting_facility_id_; }
void FractionalLongTradeMessage::set_trade_reporting_facility_id(TradeReportingFacilityId value) { trade_reporting_facility_id_ = value; }

const Timestamp2& FractionalLongTradeMessage::timestamp_2() const { return timestamp_2_; }
Timestamp2& FractionalLongTradeMessage::timestamp_2() { return timestamp_2_; }
void FractionalLongTradeMessage::set_timestamp_2(const Timestamp2& value) { timestamp_2_ = value; }

ShortSaleRestrictionIndicator FractionalLongTradeMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void FractionalLongTradeMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId FractionalLongTradeMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void FractionalLongTradeMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator FractionalLongTradeMessage::financial_status_indicator() const { return financial_status_indicator_; }
void FractionalLongTradeMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

HeldTradeIndicator FractionalLongTradeMessage::held_trade_indicator() const { return held_trade_indicator_; }
void FractionalLongTradeMessage::set_held_trade_indicator(HeldTradeIndicator value) { held_trade_indicator_ = value; }

ConsolidatedHighLowLastIndicator FractionalLongTradeMessage::consolidated_high_low_last_indicator() const { return consolidated_high_low_last_indicator_; }
void FractionalLongTradeMessage::set_consolidated_high_low_last_indicator(ConsolidatedHighLowLastIndicator value) { consolidated_high_low_last_indicator_ = value; }

ParticipantOpenHighLowLastIndicator FractionalLongTradeMessage::participant_open_high_low_last_indicator() const { return participant_open_high_low_last_indicator_; }
void FractionalLongTradeMessage::set_participant_open_high_low_last_indicator(ParticipantOpenHighLowLastIndicator value) { participant_open_high_low_last_indicator_ = value; }

TradeMessagePayloadCode FractionalLongTradeMessage::type() const { return message_type; }

std::string_view FractionalLongTradeMessage::name() const { return "Fractional Long Trade Message"; }

std::size_t FractionalLongTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FractionalLongTradeMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    security_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    instrument_type_ = static_cast<InstrumentType>(wire::read_char(data + offset));
    offset += 1;

    offset += sale_condition_4_.decode(data + offset, length - offset);

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    fractional_trade_volume_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    stop_stock_indicator_ = static_cast<StopStockIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_through_exempt_indicator_ = static_cast<TradeThroughExemptIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_reporting_facility_id_ = static_cast<TradeReportingFacilityId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_2_.decode(data + offset, length - offset);

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    held_trade_indicator_ = static_cast<HeldTradeIndicator>(wire::read_char(data + offset));
    offset += 1;

    consolidated_high_low_last_indicator_ = static_cast<ConsolidatedHighLowLastIndicator>(wire::read_char(data + offset));
    offset += 1;

    participant_open_high_low_last_indicator_ = static_cast<ParticipantOpenHighLowLastIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t FractionalLongTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FractionalLongTradeMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_text(data + offset, 11, ' ', security_symbol_);
    offset += 11;

    wire::write_char(data + offset, static_cast<char>(instrument_type_));
    offset += 1;

    offset += sale_condition_4_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(fractional_trade_volume_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(stop_stock_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_through_exempt_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_reporting_facility_id_));
    offset += 1;

    offset += timestamp_2_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(held_trade_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(consolidated_high_low_last_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(participant_open_high_low_last_indicator_));
    offset += 1;

    return offset;
}

std::size_t FractionalLongTradeMessage::encoded_size() const {
    return wire_size;
}

void FractionalLongTradeMessage::accept(TradeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TradeMessagePayload> FractionalLongTradeMessage::clone() const {
    return std::make_unique<FractionalLongTradeMessage>(*this);
}

void FractionalLongTradeMessage::print(std::ostream& out) const {
    out << "FractionalLongTradeMessage{";
    out << "participant_id=";
    out << participant_id_;
    out << ", timestamp_1=";
    timestamp_1_.print(out);
    out << ", message_id=";
    out << static_cast<int>(message_id_);
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << ", security_symbol=";
    print::text(out, security_symbol_);
    out << ", instrument_type=";
    out << instrument_type_;
    out << ", sale_condition_4=";
    sale_condition_4_.print(out);
    out << ", trade_price=";
    out << trade_price_;
    out << ", fractional_trade_volume=";
    out << fractional_trade_volume_;
    out << ", sellers_sale_days=";
    out << static_cast<int>(sellers_sale_days_);
    out << ", stop_stock_indicator=";
    out << stop_stock_indicator_;
    out << ", trade_through_exempt_indicator=";
    out << trade_through_exempt_indicator_;
    out << ", trade_reporting_facility_id=";
    out << trade_reporting_facility_id_;
    out << ", timestamp_2=";
    timestamp_2_.print(out);
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", held_trade_indicator=";
    out << held_trade_indicator_;
    out << ", consolidated_high_low_last_indicator=";
    out << consolidated_high_low_last_indicator_;
    out << ", participant_open_high_low_last_indicator=";
    out << participant_open_high_low_last_indicator_;
    out << '}';
}

bool FractionalLongTradeMessage::equals(const TradeMessagePayload& other) const {
    const auto* that = dynamic_cast<const FractionalLongTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FractionalLongTradeMessage::operator==(const FractionalLongTradeMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && sale_condition_4_ == other.sale_condition_4_
        && trade_price_ == other.trade_price_
        && fractional_trade_volume_ == other.fractional_trade_volume_
        && sellers_sale_days_ == other.sellers_sale_days_
        && stop_stock_indicator_ == other.stop_stock_indicator_
        && trade_through_exempt_indicator_ == other.trade_through_exempt_indicator_
        && trade_reporting_facility_id_ == other.trade_reporting_facility_id_
        && timestamp_2_ == other.timestamp_2_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && held_trade_indicator_ == other.held_trade_indicator_
        && consolidated_high_low_last_indicator_ == other.consolidated_high_low_last_indicator_
        && participant_open_high_low_last_indicator_ == other.participant_open_high_low_last_indicator_;
}

bool FractionalLongTradeMessage::operator!=(const FractionalLongTradeMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
