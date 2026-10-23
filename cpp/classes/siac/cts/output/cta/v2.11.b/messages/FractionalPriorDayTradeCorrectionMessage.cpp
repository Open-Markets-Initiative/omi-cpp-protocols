#include "FractionalPriorDayTradeCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

FractionalPriorDayTradeCorrectionMessage::FractionalPriorDayTradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const SaleCondition4& sale_condition_4, Decimal trade_price, std::uint64_t fractional_trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, ShortSaleRestrictionIndicator short_sale_restriction_indicator, TradeReportingFacilityId trade_reporting_facility_id, const PriorDayTradeDateAndTime& prior_day_trade_date_and_time)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), sale_condition_4_(sale_condition_4), trade_price_(trade_price), fractional_trade_volume_(fractional_trade_volume), sellers_sale_days_(sellers_sale_days), stop_stock_indicator_(stop_stock_indicator), trade_through_exempt_indicator_(trade_through_exempt_indicator), short_sale_restriction_indicator_(short_sale_restriction_indicator), trade_reporting_facility_id_(trade_reporting_facility_id), prior_day_trade_date_and_time_(prior_day_trade_date_and_time) {}

ParticipantId FractionalPriorDayTradeCorrectionMessage::participant_id() const { return participant_id_; }
void FractionalPriorDayTradeCorrectionMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& FractionalPriorDayTradeCorrectionMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& FractionalPriorDayTradeCorrectionMessage::timestamp_1() { return timestamp_1_; }
void FractionalPriorDayTradeCorrectionMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t FractionalPriorDayTradeCorrectionMessage::message_id() const { return message_id_; }
void FractionalPriorDayTradeCorrectionMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t FractionalPriorDayTradeCorrectionMessage::transaction_id() const { return transaction_id_; }
void FractionalPriorDayTradeCorrectionMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t FractionalPriorDayTradeCorrectionMessage::participant_reference_number() const { return participant_reference_number_; }
void FractionalPriorDayTradeCorrectionMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& FractionalPriorDayTradeCorrectionMessage::security_symbol() const { return security_symbol_; }
std::string& FractionalPriorDayTradeCorrectionMessage::security_symbol() { return security_symbol_; }
void FractionalPriorDayTradeCorrectionMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType FractionalPriorDayTradeCorrectionMessage::instrument_type() const { return instrument_type_; }
void FractionalPriorDayTradeCorrectionMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

const SaleCondition4& FractionalPriorDayTradeCorrectionMessage::sale_condition_4() const { return sale_condition_4_; }
SaleCondition4& FractionalPriorDayTradeCorrectionMessage::sale_condition_4() { return sale_condition_4_; }
void FractionalPriorDayTradeCorrectionMessage::set_sale_condition_4(const SaleCondition4& value) { sale_condition_4_ = value; }

Decimal FractionalPriorDayTradeCorrectionMessage::trade_price() const { return trade_price_; }
void FractionalPriorDayTradeCorrectionMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint64_t FractionalPriorDayTradeCorrectionMessage::fractional_trade_volume() const { return fractional_trade_volume_; }
void FractionalPriorDayTradeCorrectionMessage::set_fractional_trade_volume(std::uint64_t value) { fractional_trade_volume_ = value; }

std::uint8_t FractionalPriorDayTradeCorrectionMessage::sellers_sale_days() const { return sellers_sale_days_; }
void FractionalPriorDayTradeCorrectionMessage::set_sellers_sale_days(std::uint8_t value) { sellers_sale_days_ = value; }

StopStockIndicator FractionalPriorDayTradeCorrectionMessage::stop_stock_indicator() const { return stop_stock_indicator_; }
void FractionalPriorDayTradeCorrectionMessage::set_stop_stock_indicator(StopStockIndicator value) { stop_stock_indicator_ = value; }

TradeThroughExemptIndicator FractionalPriorDayTradeCorrectionMessage::trade_through_exempt_indicator() const { return trade_through_exempt_indicator_; }
void FractionalPriorDayTradeCorrectionMessage::set_trade_through_exempt_indicator(TradeThroughExemptIndicator value) { trade_through_exempt_indicator_ = value; }

ShortSaleRestrictionIndicator FractionalPriorDayTradeCorrectionMessage::short_sale_restriction_indicator() const { return short_sale_restriction_indicator_; }
void FractionalPriorDayTradeCorrectionMessage::set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value) { short_sale_restriction_indicator_ = value; }

TradeReportingFacilityId FractionalPriorDayTradeCorrectionMessage::trade_reporting_facility_id() const { return trade_reporting_facility_id_; }
void FractionalPriorDayTradeCorrectionMessage::set_trade_reporting_facility_id(TradeReportingFacilityId value) { trade_reporting_facility_id_ = value; }

const PriorDayTradeDateAndTime& FractionalPriorDayTradeCorrectionMessage::prior_day_trade_date_and_time() const { return prior_day_trade_date_and_time_; }
PriorDayTradeDateAndTime& FractionalPriorDayTradeCorrectionMessage::prior_day_trade_date_and_time() { return prior_day_trade_date_and_time_; }
void FractionalPriorDayTradeCorrectionMessage::set_prior_day_trade_date_and_time(const PriorDayTradeDateAndTime& value) { prior_day_trade_date_and_time_ = value; }

PriorDayMessagePayloadCode FractionalPriorDayTradeCorrectionMessage::type() const { return message_type; }

std::string_view FractionalPriorDayTradeCorrectionMessage::name() const { return "Fractional Prior Day Trade Correction Message"; }

std::size_t FractionalPriorDayTradeCorrectionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FractionalPriorDayTradeCorrectionMessage", wire_size, length);

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

    fractional_trade_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    stop_stock_indicator_ = static_cast<StopStockIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_through_exempt_indicator_ = static_cast<TradeThroughExemptIndicator>(wire::read_char(data + offset));
    offset += 1;

    short_sale_restriction_indicator_ = static_cast<ShortSaleRestrictionIndicator>(wire::read_char(data + offset));
    offset += 1;

    trade_reporting_facility_id_ = static_cast<TradeReportingFacilityId>(wire::read_char(data + offset));
    offset += 1;

    offset += prior_day_trade_date_and_time_.decode(data + offset, length - offset);

    return offset;
}

std::size_t FractionalPriorDayTradeCorrectionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FractionalPriorDayTradeCorrectionMessage", wire_size, capacity);

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

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(fractional_trade_volume_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(stop_stock_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_through_exempt_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(short_sale_restriction_indicator_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_reporting_facility_id_));
    offset += 1;

    offset += prior_day_trade_date_and_time_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t FractionalPriorDayTradeCorrectionMessage::encoded_size() const {
    return wire_size;
}

void FractionalPriorDayTradeCorrectionMessage::accept(PriorDayMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PriorDayMessagePayload> FractionalPriorDayTradeCorrectionMessage::clone() const {
    return std::make_unique<FractionalPriorDayTradeCorrectionMessage>(*this);
}

void FractionalPriorDayTradeCorrectionMessage::print(std::ostream& out) const {
    out << "FractionalPriorDayTradeCorrectionMessage{";
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
    out << ", short_sale_restriction_indicator=";
    out << short_sale_restriction_indicator_;
    out << ", trade_reporting_facility_id=";
    out << trade_reporting_facility_id_;
    out << ", prior_day_trade_date_and_time=";
    prior_day_trade_date_and_time_.print(out);
    out << '}';
}

bool FractionalPriorDayTradeCorrectionMessage::equals(const PriorDayMessagePayload& other) const {
    const auto* that = dynamic_cast<const FractionalPriorDayTradeCorrectionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FractionalPriorDayTradeCorrectionMessage::operator==(const FractionalPriorDayTradeCorrectionMessage& other) const {
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
        && short_sale_restriction_indicator_ == other.short_sale_restriction_indicator_
        && trade_reporting_facility_id_ == other.trade_reporting_facility_id_
        && prior_day_trade_date_and_time_ == other.prior_day_trade_date_and_time_;
}

bool FractionalPriorDayTradeCorrectionMessage::operator!=(const FractionalPriorDayTradeCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
