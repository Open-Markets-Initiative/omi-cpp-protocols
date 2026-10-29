#include "PriorDayTradeCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v1_91 {

PriorDayTradeCorrectionMessage::PriorDayTradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const CorrectedTrade& corrected_trade, TradeReportingFacilityId trade_reporting_facility_id, const OriginalTrade& original_trade)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), corrected_trade_(corrected_trade), trade_reporting_facility_id_(trade_reporting_facility_id), original_trade_(original_trade) {}

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

const CorrectedTrade& PriorDayTradeCorrectionMessage::corrected_trade() const { return corrected_trade_; }
CorrectedTrade& PriorDayTradeCorrectionMessage::corrected_trade() { return corrected_trade_; }
void PriorDayTradeCorrectionMessage::set_corrected_trade(const CorrectedTrade& value) { corrected_trade_ = value; }

TradeReportingFacilityId PriorDayTradeCorrectionMessage::trade_reporting_facility_id() const { return trade_reporting_facility_id_; }
void PriorDayTradeCorrectionMessage::set_trade_reporting_facility_id(TradeReportingFacilityId value) { trade_reporting_facility_id_ = value; }

const OriginalTrade& PriorDayTradeCorrectionMessage::original_trade() const { return original_trade_; }
OriginalTrade& PriorDayTradeCorrectionMessage::original_trade() { return original_trade_; }
void PriorDayTradeCorrectionMessage::set_original_trade(const OriginalTrade& value) { original_trade_ = value; }

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

    offset += corrected_trade_.decode(data + offset, length - offset);

    trade_reporting_facility_id_ = static_cast<TradeReportingFacilityId>(wire::read_char(data + offset));
    offset += 1;

    offset += original_trade_.decode(data + offset, length - offset);

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

    offset += corrected_trade_.encode(data + offset, capacity - offset);

    wire::write_char(data + offset, static_cast<char>(trade_reporting_facility_id_));
    offset += 1;

    offset += original_trade_.encode(data + offset, capacity - offset);

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
    out << ", corrected_trade=";
    corrected_trade_.print(out);
    out << ", trade_reporting_facility_id=";
    out << trade_reporting_facility_id_;
    out << ", original_trade=";
    original_trade_.print(out);
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
        && corrected_trade_ == other.corrected_trade_
        && trade_reporting_facility_id_ == other.trade_reporting_facility_id_
        && original_trade_ == other.original_trade_;
}

bool PriorDayTradeCorrectionMessage::operator!=(const PriorDayTradeCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v1_91
