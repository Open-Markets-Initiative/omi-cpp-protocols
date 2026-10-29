#include "TradeCancelErrorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_9 {

TradeCancelErrorMessage::TradeCancelErrorMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const SaleConditions& sale_conditions, Decimal trade_price, std::uint32_t trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, TradeReportingFacilityId trade_reporting_facility_id, std::int64_t original_participant_reference_number, const Timestamp2& timestamp_2, CancelErrorAction cancel_error_action, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, const ConsolidatedData& consolidated_data, const ParticipantData& participant_data)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), sale_conditions_(sale_conditions), trade_price_(trade_price), trade_volume_(trade_volume), sellers_sale_days_(sellers_sale_days), stop_stock_indicator_(stop_stock_indicator), trade_through_exempt_indicator_(trade_through_exempt_indicator), trade_reporting_facility_id_(trade_reporting_facility_id), original_participant_reference_number_(original_participant_reference_number), timestamp_2_(timestamp_2), cancel_error_action_(cancel_error_action), short_sale_restriction_indicator_(short_sale_restriction_indicator), primary_listing_market_participant_id_(primary_listing_market_participant_id), financial_status_indicator_(financial_status_indicator), consolidated_data_(consolidated_data), participant_data_(participant_data) {}

ParticipantId TradeCancelErrorMessage::participant_id() const { return participant_id_; }
void TradeCancelErrorMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& TradeCancelErrorMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& TradeCancelErrorMessage::timestamp_1() { return timestamp_1_; }
void TradeCancelErrorMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t TradeCancelErrorMessage::message_id() const { return message_id_; }
void TradeCancelErrorMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t TradeCancelErrorMessage::transaction_id() const { return transaction_id_; }
void TradeCancelErrorMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t TradeCancelErrorMessage::participant_reference_number() const { return participant_reference_number_; }
void TradeCancelErrorMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& TradeCancelErrorMessage::security_symbol() const { return security_symbol_; }
std::string& TradeCancelErrorMessage::security_symbol() { return security_symbol_; }
void TradeCancelErrorMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType TradeCancelErrorMessage::instrument_type() const { return instrument_type_; }
void TradeCancelErrorMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

const SaleConditions& TradeCancelErrorMessage::sale_conditions() const { return sale_conditions_; }
SaleConditions& TradeCancelErrorMessage::sale_conditions() { return sale_conditions_; }
void TradeCancelErrorMessage::set_sale_conditions(const SaleConditions& value) { sale_conditions_ = value; }

Decimal TradeCancelErrorMessage::trade_price() const { return trade_price_; }
void TradeCancelErrorMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t TradeCancelErrorMessage::trade_volume() const { return trade_volume_; }
void TradeCancelErrorMessage::set_trade_volume(std::uint32_t value) { trade_volume_ = value; }

std::uint8_t TradeCancelErrorMessage::sellers_sale_days() const { return sellers_sale_days_; }
void TradeCancelErrorMessage::set_sellers_sale_days(std::uint8_t value) { sellers_sale_days_ = value; }

StopStockIndicator TradeCancelErrorMessage::stop_stock_indicator() const { return stop_stock_indicator_; }
void TradeCancelErrorMessage::set_stop_stock_indicator(StopStockIndicator value) { stop_stock_indicator_ = value; }

TradeThroughExemptIndicator TradeCancelErrorMessage::trade_through_exempt_indicator() const { return trade_through_exempt_indicator_; }
void TradeCancelErrorMessage::set_trade_through_exempt_indicator(TradeThroughExemptIndicator value) { trade_through_exempt_indicator_ = value; }

TradeReportingFacilityId TradeCancelErrorMessage::trade_reporting_facility_id() const { return trade_reporting_facility_id_; }
void TradeCancelErrorMessage::set_trade_reporting_facility_id(TradeReportingFacilityId value) { trade_reporting_facility_id_ = value; }

std::int64_t TradeCancelErrorMessage::original_participant_reference_number() const { return original_participant_reference_number_; }
void TradeCancelErrorMessage::set_original_participant_reference_number(std::int64_t value) { original_participant_reference_number_ = value; }

const Timestamp2& TradeCancelErrorMessage::timestamp_2() const { return timestamp_2_; }
Timestamp2& TradeCancelErrorMessage::timestamp_2() { return timestamp_2_; }
void TradeCancelErrorMessage::set_timestamp_2(const Timestamp2& value) { timestamp_2_ = value; }

CancelErrorAction TradeCancelErrorMessage::cancel_error_action() const { return cancel_error_action_; }
void TradeCancelErrorMessage::set_cancel_error_action(CancelErrorAction value) { cancel_error_action_ = value; }

ShortSaleRestrictionIndicator TradeCancelErrorMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void TradeCancelErrorMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

PrimaryListingMarketParticipantId TradeCancelErrorMessage::primary_listing_market_participant_id() const { return primary_listing_market_participant_id_; }
void TradeCancelErrorMessage::set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value) { primary_listing_market_participant_id_ = value; }

FinancialStatusIndicator TradeCancelErrorMessage::financial_status_indicator() const { return financial_status_indicator_; }
void TradeCancelErrorMessage::set_financial_status_indicator(FinancialStatusIndicator value) { financial_status_indicator_ = value; }

const ConsolidatedData& TradeCancelErrorMessage::consolidated_data() const { return consolidated_data_; }
ConsolidatedData& TradeCancelErrorMessage::consolidated_data() { return consolidated_data_; }
void TradeCancelErrorMessage::set_consolidated_data(const ConsolidatedData& value) { consolidated_data_ = value; }

const ParticipantData& TradeCancelErrorMessage::participant_data() const { return participant_data_; }
ParticipantData& TradeCancelErrorMessage::participant_data() { return participant_data_; }
void TradeCancelErrorMessage::set_participant_data(const ParticipantData& value) { participant_data_ = value; }

TradeMessagePayloadCode TradeCancelErrorMessage::type() const { return message_type; }

std::string_view TradeCancelErrorMessage::name() const { return "Trade Cancel Error Message"; }

std::size_t TradeCancelErrorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCancelErrorMessage", wire_size, length);

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

    offset += sale_conditions_.decode(data + offset, length - offset);

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    stop_stock_indicator_ = static_cast<StopStockIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_through_exempt_indicator_ = static_cast<TradeThroughExemptIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_reporting_facility_id_ = static_cast<TradeReportingFacilityId>(wire::read_char(data + offset));
    offset += 1;

    original_participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    offset += timestamp_2_.decode(data + offset, length - offset);

    cancel_error_action_ = static_cast<CancelErrorAction>(wire::read_char(data + offset));
    offset += 1;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    primary_listing_market_participant_id_ = static_cast<PrimaryListingMarketParticipantId>(wire::read_char(data + offset));
    offset += 1;

    financial_status_indicator_ = static_cast<FinancialStatusIndicator>(wire::read_char(data + offset));
    offset += 1;

    offset += consolidated_data_.decode(data + offset, length - offset);

    offset += participant_data_.decode(data + offset, length - offset);

    return offset;
}

std::size_t TradeCancelErrorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCancelErrorMessage", wire_size, capacity);

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

    offset += sale_conditions_.encode(data + offset, capacity - offset);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(stop_stock_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_through_exempt_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_reporting_facility_id_));
    offset += 1;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(original_participant_reference_number_));
    offset += 8;

    offset += timestamp_2_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(cancel_error_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(primary_listing_market_participant_id_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(financial_status_indicator_));
    offset += 1;

    offset += consolidated_data_.encode(data + offset, capacity - offset);

    offset += participant_data_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t TradeCancelErrorMessage::encoded_size() const {
    return wire_size;
}

void TradeCancelErrorMessage::accept(TradeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TradeMessagePayload> TradeCancelErrorMessage::clone() const {
    return std::make_unique<TradeCancelErrorMessage>(*this);
}

void TradeCancelErrorMessage::print(std::ostream& out) const {
    out << "TradeCancelErrorMessage{";
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
    out << ", sale_conditions=";
    sale_conditions_.print(out);
    out << ", trade_price=";
    out << trade_price_;
    out << ", trade_volume=";
    out << trade_volume_;
    out << ", sellers_sale_days=";
    out << static_cast<int>(sellers_sale_days_);
    out << ", stop_stock_indicator=";
    out << stop_stock_indicator_;
    out << ", trade_through_exempt_indicator=";
    out << trade_through_exempt_indicator_;
    out << ", trade_reporting_facility_id=";
    out << trade_reporting_facility_id_;
    out << ", original_participant_reference_number=";
    out << original_participant_reference_number_;
    out << ", timestamp_2=";
    timestamp_2_.print(out);
    out << ", cancel_error_action=";
    out << cancel_error_action_;
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", primary_listing_market_participant_id=";
    out << primary_listing_market_participant_id_;
    out << ", financial_status_indicator=";
    out << financial_status_indicator_;
    out << ", consolidated_data=";
    consolidated_data_.print(out);
    out << ", participant_data=";
    participant_data_.print(out);
    out << '}';
}

bool TradeCancelErrorMessage::equals(const TradeMessagePayload& other) const {
    const auto* that = dynamic_cast<const TradeCancelErrorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCancelErrorMessage::operator==(const TradeCancelErrorMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && sale_conditions_ == other.sale_conditions_
        && trade_price_ == other.trade_price_
        && trade_volume_ == other.trade_volume_
        && sellers_sale_days_ == other.sellers_sale_days_
        && stop_stock_indicator_ == other.stop_stock_indicator_
        && trade_through_exempt_indicator_ == other.trade_through_exempt_indicator_
        && trade_reporting_facility_id_ == other.trade_reporting_facility_id_
        && original_participant_reference_number_ == other.original_participant_reference_number_
        && timestamp_2_ == other.timestamp_2_
        && cancel_error_action_ == other.cancel_error_action_
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && primary_listing_market_participant_id_ == other.primary_listing_market_participant_id_
        && financial_status_indicator_ == other.financial_status_indicator_
        && consolidated_data_ == other.consolidated_data_
        && participant_data_ == other.participant_data_;
}

bool TradeCancelErrorMessage::operator!=(const TradeCancelErrorMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_9
