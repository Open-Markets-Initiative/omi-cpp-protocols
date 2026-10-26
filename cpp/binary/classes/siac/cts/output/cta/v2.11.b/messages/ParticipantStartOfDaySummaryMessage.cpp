#include "ParticipantStartOfDaySummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

ParticipantStartOfDaySummaryMessage::ParticipantStartOfDaySummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, char summary_participant_id, std::uint32_t previous_close_price_date, Decimal previous_close_price)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), summary_participant_id_(summary_participant_id), previous_close_price_date_(previous_close_price_date), previous_close_price_(previous_close_price) {}

ParticipantId ParticipantStartOfDaySummaryMessage::participant_id() const { return participant_id_; }
void ParticipantStartOfDaySummaryMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& ParticipantStartOfDaySummaryMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& ParticipantStartOfDaySummaryMessage::timestamp_1() { return timestamp_1_; }
void ParticipantStartOfDaySummaryMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t ParticipantStartOfDaySummaryMessage::message_id() const { return message_id_; }
void ParticipantStartOfDaySummaryMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t ParticipantStartOfDaySummaryMessage::transaction_id() const { return transaction_id_; }
void ParticipantStartOfDaySummaryMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t ParticipantStartOfDaySummaryMessage::participant_reference_number() const { return participant_reference_number_; }
void ParticipantStartOfDaySummaryMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& ParticipantStartOfDaySummaryMessage::security_symbol() const { return security_symbol_; }
std::string& ParticipantStartOfDaySummaryMessage::security_symbol() { return security_symbol_; }
void ParticipantStartOfDaySummaryMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType ParticipantStartOfDaySummaryMessage::instrument_type() const { return instrument_type_; }
void ParticipantStartOfDaySummaryMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

char ParticipantStartOfDaySummaryMessage::summary_participant_id() const { return summary_participant_id_; }
void ParticipantStartOfDaySummaryMessage::set_summary_participant_id(char value) { summary_participant_id_ = value; }

std::uint32_t ParticipantStartOfDaySummaryMessage::previous_close_price_date() const { return previous_close_price_date_; }
void ParticipantStartOfDaySummaryMessage::set_previous_close_price_date(std::uint32_t value) { previous_close_price_date_ = value; }

Decimal ParticipantStartOfDaySummaryMessage::previous_close_price() const { return previous_close_price_; }
void ParticipantStartOfDaySummaryMessage::set_previous_close_price(Decimal value) { previous_close_price_ = value; }

SummaryMessagePayloadCode ParticipantStartOfDaySummaryMessage::type() const { return message_type; }

std::string_view ParticipantStartOfDaySummaryMessage::name() const { return "Participant Start Of Day Summary Message"; }

std::size_t ParticipantStartOfDaySummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ParticipantStartOfDaySummaryMessage", wire_size, length);

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

    summary_participant_id_ = wire::read_char(data + offset);
    offset += 1;

    previous_close_price_date_ = wire::read_u32_be(data + offset);
    offset += 4;

    previous_close_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t ParticipantStartOfDaySummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ParticipantStartOfDaySummaryMessage", wire_size, capacity);

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

    wire::write_char(data + offset, summary_participant_id_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(previous_close_price_date_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(previous_close_price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t ParticipantStartOfDaySummaryMessage::encoded_size() const {
    return wire_size;
}

void ParticipantStartOfDaySummaryMessage::accept(SummaryMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SummaryMessagePayload> ParticipantStartOfDaySummaryMessage::clone() const {
    return std::make_unique<ParticipantStartOfDaySummaryMessage>(*this);
}

void ParticipantStartOfDaySummaryMessage::print(std::ostream& out) const {
    out << "ParticipantStartOfDaySummaryMessage{";
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
    out << ", summary_participant_id=";
    print::character(out, summary_participant_id_);
    out << ", previous_close_price_date=";
    out << previous_close_price_date_;
    out << ", previous_close_price=";
    out << previous_close_price_;
    out << '}';
}

bool ParticipantStartOfDaySummaryMessage::equals(const SummaryMessagePayload& other) const {
    const auto* that = dynamic_cast<const ParticipantStartOfDaySummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ParticipantStartOfDaySummaryMessage::operator==(const ParticipantStartOfDaySummaryMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && summary_participant_id_ == other.summary_participant_id_
        && previous_close_price_date_ == other.previous_close_price_date_
        && previous_close_price_ == other.previous_close_price_;
}

bool ParticipantStartOfDaySummaryMessage::operator!=(const ParticipantStartOfDaySummaryMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
