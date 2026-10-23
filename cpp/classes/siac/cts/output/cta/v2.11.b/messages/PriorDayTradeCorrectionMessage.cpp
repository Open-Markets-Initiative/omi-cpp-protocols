#include "PriorDayTradeCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

PriorDayTradeCorrectionMessage::PriorDayTradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const std::string& corrected_sale_condition, Decimal corrected_trade_price, std::uint32_t corrected_trade_volume, std::uint8_t corrected_sellers_sale_days, char corrected_stop_stock_indicator, char corrected_trade_through_exempt_indicator, char corrected_short_sale_restriction_indicator, const CorrectedPriorDayTradeDateAndTime& corrected_prior_day_trade_date_and_time, TradeReportingFacilityId trade_reporting_facility_id, const std::string& original_sale_condition, Decimal original_trade_price, std::uint32_t original_trade_volume, std::uint8_t original_sellers_sale_days, char original_stop_stock_indicator, char original_trade_through_exempt_indicator, char original_short_sale_restriction_indicator, const OriginalPriorDayTradeDateAndTime& original_prior_day_trade_date_and_time)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), corrected_sale_condition_(corrected_sale_condition), corrected_trade_price_(corrected_trade_price), corrected_trade_volume_(corrected_trade_volume), corrected_sellers_sale_days_(corrected_sellers_sale_days), corrected_stop_stock_indicator_(corrected_stop_stock_indicator), corrected_trade_through_exempt_indicator_(corrected_trade_through_exempt_indicator), corrected_short_sale_restriction_indicator_(corrected_short_sale_restriction_indicator), corrected_prior_day_trade_date_and_time_(corrected_prior_day_trade_date_and_time), trade_reporting_facility_id_(trade_reporting_facility_id), original_sale_condition_(original_sale_condition), original_trade_price_(original_trade_price), original_trade_volume_(original_trade_volume), original_sellers_sale_days_(original_sellers_sale_days), original_stop_stock_indicator_(original_stop_stock_indicator), original_trade_through_exempt_indicator_(original_trade_through_exempt_indicator), original_short_sale_restriction_indicator_(original_short_sale_restriction_indicator), original_prior_day_trade_date_and_time_(original_prior_day_trade_date_and_time) {}

ParticipantId PriorDayTradeCorrectionMessage::participant_id() const { return participant_id_; }
void PriorDayTradeCorrectionMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& PriorDayTradeCorrectionMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& PriorDayTradeCorrectionMessage::timestamp_1() { return timestamp_1_; }
void PriorDayTradeCorrectionMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t PriorDayTradeCorrectionMessage::message_id() const { return message_id_; }
void PriorDayTradeCorrectionMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t PriorDayTradeCorrectionMessage::transaction_id() const { return transaction_id_; }
void PriorDayTradeCorrectionMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t PriorDayTradeCorrectionMessage::participant_reference_number() const { return participant_reference_number_; }
void PriorDayTradeCorrectionMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& PriorDayTradeCorrectionMessage::security_symbol() const { return security_symbol_; }
std::string& PriorDayTradeCorrectionMessage::security_symbol() { return security_symbol_; }
void PriorDayTradeCorrectionMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType PriorDayTradeCorrectionMessage::instrument_type() const { return instrument_type_; }
void PriorDayTradeCorrectionMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

const std::string& PriorDayTradeCorrectionMessage::corrected_sale_condition() const { return corrected_sale_condition_; }
std::string& PriorDayTradeCorrectionMessage::corrected_sale_condition() { return corrected_sale_condition_; }
void PriorDayTradeCorrectionMessage::set_corrected_sale_condition(const std::string& value) { corrected_sale_condition_ = value; }

Decimal PriorDayTradeCorrectionMessage::corrected_trade_price() const { return corrected_trade_price_; }
void PriorDayTradeCorrectionMessage::set_corrected_trade_price(Decimal value) { corrected_trade_price_ = value; }

std::uint32_t PriorDayTradeCorrectionMessage::corrected_trade_volume() const { return corrected_trade_volume_; }
void PriorDayTradeCorrectionMessage::set_corrected_trade_volume(std::uint32_t value) { corrected_trade_volume_ = value; }

std::uint8_t PriorDayTradeCorrectionMessage::corrected_sellers_sale_days() const { return corrected_sellers_sale_days_; }
void PriorDayTradeCorrectionMessage::set_corrected_sellers_sale_days(std::uint8_t value) { corrected_sellers_sale_days_ = value; }

char PriorDayTradeCorrectionMessage::corrected_stop_stock_indicator() const { return corrected_stop_stock_indicator_; }
void PriorDayTradeCorrectionMessage::set_corrected_stop_stock_indicator(char value) { corrected_stop_stock_indicator_ = value; }

char PriorDayTradeCorrectionMessage::corrected_trade_through_exempt_indicator() const { return corrected_trade_through_exempt_indicator_; }
void PriorDayTradeCorrectionMessage::set_corrected_trade_through_exempt_indicator(char value) { corrected_trade_through_exempt_indicator_ = value; }

char PriorDayTradeCorrectionMessage::corrected_short_sale_restriction_indicator() const { return corrected_short_sale_restriction_indicator_; }
void PriorDayTradeCorrectionMessage::set_corrected_short_sale_restriction_indicator(char value) { corrected_short_sale_restriction_indicator_ = value; }

const CorrectedPriorDayTradeDateAndTime& PriorDayTradeCorrectionMessage::corrected_prior_day_trade_date_and_time() const { return corrected_prior_day_trade_date_and_time_; }
CorrectedPriorDayTradeDateAndTime& PriorDayTradeCorrectionMessage::corrected_prior_day_trade_date_and_time() { return corrected_prior_day_trade_date_and_time_; }
void PriorDayTradeCorrectionMessage::set_corrected_prior_day_trade_date_and_time(const CorrectedPriorDayTradeDateAndTime& value) { corrected_prior_day_trade_date_and_time_ = value; }

TradeReportingFacilityId PriorDayTradeCorrectionMessage::trade_reporting_facility_id() const { return trade_reporting_facility_id_; }
void PriorDayTradeCorrectionMessage::set_trade_reporting_facility_id(TradeReportingFacilityId value) { trade_reporting_facility_id_ = value; }

const std::string& PriorDayTradeCorrectionMessage::original_sale_condition() const { return original_sale_condition_; }
std::string& PriorDayTradeCorrectionMessage::original_sale_condition() { return original_sale_condition_; }
void PriorDayTradeCorrectionMessage::set_original_sale_condition(const std::string& value) { original_sale_condition_ = value; }

Decimal PriorDayTradeCorrectionMessage::original_trade_price() const { return original_trade_price_; }
void PriorDayTradeCorrectionMessage::set_original_trade_price(Decimal value) { original_trade_price_ = value; }

std::uint32_t PriorDayTradeCorrectionMessage::original_trade_volume() const { return original_trade_volume_; }
void PriorDayTradeCorrectionMessage::set_original_trade_volume(std::uint32_t value) { original_trade_volume_ = value; }

std::uint8_t PriorDayTradeCorrectionMessage::original_sellers_sale_days() const { return original_sellers_sale_days_; }
void PriorDayTradeCorrectionMessage::set_original_sellers_sale_days(std::uint8_t value) { original_sellers_sale_days_ = value; }

char PriorDayTradeCorrectionMessage::original_stop_stock_indicator() const { return original_stop_stock_indicator_; }
void PriorDayTradeCorrectionMessage::set_original_stop_stock_indicator(char value) { original_stop_stock_indicator_ = value; }

char PriorDayTradeCorrectionMessage::original_trade_through_exempt_indicator() const { return original_trade_through_exempt_indicator_; }
void PriorDayTradeCorrectionMessage::set_original_trade_through_exempt_indicator(char value) { original_trade_through_exempt_indicator_ = value; }

char PriorDayTradeCorrectionMessage::original_short_sale_restriction_indicator() const { return original_short_sale_restriction_indicator_; }
void PriorDayTradeCorrectionMessage::set_original_short_sale_restriction_indicator(char value) { original_short_sale_restriction_indicator_ = value; }

const OriginalPriorDayTradeDateAndTime& PriorDayTradeCorrectionMessage::original_prior_day_trade_date_and_time() const { return original_prior_day_trade_date_and_time_; }
OriginalPriorDayTradeDateAndTime& PriorDayTradeCorrectionMessage::original_prior_day_trade_date_and_time() { return original_prior_day_trade_date_and_time_; }
void PriorDayTradeCorrectionMessage::set_original_prior_day_trade_date_and_time(const OriginalPriorDayTradeDateAndTime& value) { original_prior_day_trade_date_and_time_ = value; }

PriorDayMessagePayloadCode PriorDayTradeCorrectionMessage::type() const { return message_type; }

std::string_view PriorDayTradeCorrectionMessage::name() const { return "Prior Day Trade Correction Message"; }

std::size_t PriorDayTradeCorrectionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriorDayTradeCorrectionMessage", wire_size, length);

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

    corrected_sale_condition_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    corrected_trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    corrected_trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    corrected_sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    corrected_stop_stock_indicator_ = wire::read_char(data + offset);
    offset += 1;

    corrected_trade_through_exempt_indicator_ = wire::read_char(data + offset);
    offset += 1;

    corrected_short_sale_restriction_indicator_ = wire::read_char(data + offset);
    offset += 1;

    offset += corrected_prior_day_trade_date_and_time_.decode(data + offset, length - offset);

    trade_reporting_facility_id_ = static_cast<TradeReportingFacilityId>(wire::read_char(data + offset));
    offset += 1;

    original_sale_condition_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    original_trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    original_trade_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    original_sellers_sale_days_ = wire::read_u8(data + offset);
    offset += 1;

    original_stop_stock_indicator_ = wire::read_char(data + offset);
    offset += 1;

    original_trade_through_exempt_indicator_ = wire::read_char(data + offset);
    offset += 1;

    original_short_sale_restriction_indicator_ = wire::read_char(data + offset);
    offset += 1;

    offset += original_prior_day_trade_date_and_time_.decode(data + offset, length - offset);

    return offset;
}

std::size_t PriorDayTradeCorrectionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriorDayTradeCorrectionMessage", wire_size, capacity);

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

    wire::write_text(data + offset, 4, ' ', corrected_sale_condition_);
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(corrected_trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(corrected_trade_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(corrected_sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, corrected_stop_stock_indicator_);
    offset += 1;

    wire::write_char(data + offset, corrected_trade_through_exempt_indicator_);
    offset += 1;

    wire::write_char(data + offset, corrected_short_sale_restriction_indicator_);
    offset += 1;

    offset += corrected_prior_day_trade_date_and_time_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(trade_reporting_facility_id_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', original_sale_condition_);
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_trade_volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(original_sellers_sale_days_));
    offset += 1;

    wire::write_char(data + offset, original_stop_stock_indicator_);
    offset += 1;

    wire::write_char(data + offset, original_trade_through_exempt_indicator_);
    offset += 1;

    wire::write_char(data + offset, original_short_sale_restriction_indicator_);
    offset += 1;

    offset += original_prior_day_trade_date_and_time_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t PriorDayTradeCorrectionMessage::encoded_size() const {
    return wire_size;
}

void PriorDayTradeCorrectionMessage::accept(PriorDayMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PriorDayMessagePayload> PriorDayTradeCorrectionMessage::clone() const {
    return std::make_unique<PriorDayTradeCorrectionMessage>(*this);
}

void PriorDayTradeCorrectionMessage::print(std::ostream& out) const {
    out << "PriorDayTradeCorrectionMessage{";
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
    out << ", corrected_sale_condition=";
    print::text(out, corrected_sale_condition_);
    out << ", corrected_trade_price=";
    out << corrected_trade_price_;
    out << ", corrected_trade_volume=";
    out << corrected_trade_volume_;
    out << ", corrected_sellers_sale_days=";
    out << static_cast<int>(corrected_sellers_sale_days_);
    out << ", corrected_stop_stock_indicator=";
    print::character(out, corrected_stop_stock_indicator_);
    out << ", corrected_trade_through_exempt_indicator=";
    print::character(out, corrected_trade_through_exempt_indicator_);
    out << ", corrected_short_sale_restriction_indicator=";
    print::character(out, corrected_short_sale_restriction_indicator_);
    out << ", corrected_prior_day_trade_date_and_time=";
    corrected_prior_day_trade_date_and_time_.print(out);
    out << ", trade_reporting_facility_id=";
    out << trade_reporting_facility_id_;
    out << ", original_sale_condition=";
    print::text(out, original_sale_condition_);
    out << ", original_trade_price=";
    out << original_trade_price_;
    out << ", original_trade_volume=";
    out << original_trade_volume_;
    out << ", original_sellers_sale_days=";
    out << static_cast<int>(original_sellers_sale_days_);
    out << ", original_stop_stock_indicator=";
    print::character(out, original_stop_stock_indicator_);
    out << ", original_trade_through_exempt_indicator=";
    print::character(out, original_trade_through_exempt_indicator_);
    out << ", original_short_sale_restriction_indicator=";
    print::character(out, original_short_sale_restriction_indicator_);
    out << ", original_prior_day_trade_date_and_time=";
    original_prior_day_trade_date_and_time_.print(out);
    out << '}';
}

bool PriorDayTradeCorrectionMessage::equals(const PriorDayMessagePayload& other) const {
    const auto* that = dynamic_cast<const PriorDayTradeCorrectionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PriorDayTradeCorrectionMessage::operator==(const PriorDayTradeCorrectionMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && corrected_sale_condition_ == other.corrected_sale_condition_
        && corrected_trade_price_ == other.corrected_trade_price_
        && corrected_trade_volume_ == other.corrected_trade_volume_
        && corrected_sellers_sale_days_ == other.corrected_sellers_sale_days_
        && corrected_stop_stock_indicator_ == other.corrected_stop_stock_indicator_
        && corrected_trade_through_exempt_indicator_ == other.corrected_trade_through_exempt_indicator_
        && corrected_short_sale_restriction_indicator_ == other.corrected_short_sale_restriction_indicator_
        && corrected_prior_day_trade_date_and_time_ == other.corrected_prior_day_trade_date_and_time_
        && trade_reporting_facility_id_ == other.trade_reporting_facility_id_
        && original_sale_condition_ == other.original_sale_condition_
        && original_trade_price_ == other.original_trade_price_
        && original_trade_volume_ == other.original_trade_volume_
        && original_sellers_sale_days_ == other.original_sellers_sale_days_
        && original_stop_stock_indicator_ == other.original_stop_stock_indicator_
        && original_trade_through_exempt_indicator_ == other.original_trade_through_exempt_indicator_
        && original_short_sale_restriction_indicator_ == other.original_short_sale_restriction_indicator_
        && original_prior_day_trade_date_and_time_ == other.original_prior_day_trade_date_and_time_;
}

bool PriorDayTradeCorrectionMessage::operator!=(const PriorDayTradeCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
