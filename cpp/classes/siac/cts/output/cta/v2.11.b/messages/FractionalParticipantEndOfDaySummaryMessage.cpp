#include "FractionalParticipantEndOfDaySummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

FractionalParticipantEndOfDaySummaryMessage::FractionalParticipantEndOfDaySummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, char summary_participant_id, std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, Decimal open_price, std::uint64_t fractional_total_volume, Tick tick)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), security_symbol_(security_symbol), instrument_type_(instrument_type), summary_participant_id_(summary_participant_id), previous_close_price_date_(previous_close_price_date), last_price_(last_price), high_price_(high_price), low_price_(low_price), open_price_(open_price), fractional_total_volume_(fractional_total_volume), tick_(tick) {}

ParticipantId FractionalParticipantEndOfDaySummaryMessage::participant_id() const { return participant_id_; }
void FractionalParticipantEndOfDaySummaryMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& FractionalParticipantEndOfDaySummaryMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& FractionalParticipantEndOfDaySummaryMessage::timestamp_1() { return timestamp_1_; }
void FractionalParticipantEndOfDaySummaryMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t FractionalParticipantEndOfDaySummaryMessage::message_id() const { return message_id_; }
void FractionalParticipantEndOfDaySummaryMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t FractionalParticipantEndOfDaySummaryMessage::transaction_id() const { return transaction_id_; }
void FractionalParticipantEndOfDaySummaryMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t FractionalParticipantEndOfDaySummaryMessage::participant_reference_number() const { return participant_reference_number_; }
void FractionalParticipantEndOfDaySummaryMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

const std::string& FractionalParticipantEndOfDaySummaryMessage::security_symbol() const { return security_symbol_; }
std::string& FractionalParticipantEndOfDaySummaryMessage::security_symbol() { return security_symbol_; }
void FractionalParticipantEndOfDaySummaryMessage::set_security_symbol(const std::string& value) { security_symbol_ = value; }

InstrumentType FractionalParticipantEndOfDaySummaryMessage::instrument_type() const { return instrument_type_; }
void FractionalParticipantEndOfDaySummaryMessage::set_instrument_type(InstrumentType value) { instrument_type_ = value; }

char FractionalParticipantEndOfDaySummaryMessage::summary_participant_id() const { return summary_participant_id_; }
void FractionalParticipantEndOfDaySummaryMessage::set_summary_participant_id(char value) { summary_participant_id_ = value; }

std::uint32_t FractionalParticipantEndOfDaySummaryMessage::previous_close_price_date() const { return previous_close_price_date_; }
void FractionalParticipantEndOfDaySummaryMessage::set_previous_close_price_date(std::uint32_t value) { previous_close_price_date_ = value; }

Decimal FractionalParticipantEndOfDaySummaryMessage::last_price() const { return last_price_; }
void FractionalParticipantEndOfDaySummaryMessage::set_last_price(Decimal value) { last_price_ = value; }

Decimal FractionalParticipantEndOfDaySummaryMessage::high_price() const { return high_price_; }
void FractionalParticipantEndOfDaySummaryMessage::set_high_price(Decimal value) { high_price_ = value; }

Decimal FractionalParticipantEndOfDaySummaryMessage::low_price() const { return low_price_; }
void FractionalParticipantEndOfDaySummaryMessage::set_low_price(Decimal value) { low_price_ = value; }

Decimal FractionalParticipantEndOfDaySummaryMessage::open_price() const { return open_price_; }
void FractionalParticipantEndOfDaySummaryMessage::set_open_price(Decimal value) { open_price_ = value; }

std::uint64_t FractionalParticipantEndOfDaySummaryMessage::fractional_total_volume() const { return fractional_total_volume_; }
void FractionalParticipantEndOfDaySummaryMessage::set_fractional_total_volume(std::uint64_t value) { fractional_total_volume_ = value; }

Tick FractionalParticipantEndOfDaySummaryMessage::tick() const { return tick_; }
void FractionalParticipantEndOfDaySummaryMessage::set_tick(Tick value) { tick_ = value; }

SummaryMessagePayloadCode FractionalParticipantEndOfDaySummaryMessage::type() const { return message_type; }

std::string_view FractionalParticipantEndOfDaySummaryMessage::name() const { return "Fractional Participant End Of Day Summary Message"; }

std::size_t FractionalParticipantEndOfDaySummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FractionalParticipantEndOfDaySummaryMessage", wire_size, length);

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

    last_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    high_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    low_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    open_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    fractional_total_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    tick_ = static_cast<Tick>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t FractionalParticipantEndOfDaySummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FractionalParticipantEndOfDaySummaryMessage", wire_size, capacity);

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

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(high_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(low_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(open_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(fractional_total_volume_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(tick_));
    offset += 1;

    return offset;
}

std::size_t FractionalParticipantEndOfDaySummaryMessage::encoded_size() const {
    return wire_size;
}

void FractionalParticipantEndOfDaySummaryMessage::accept(SummaryMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SummaryMessagePayload> FractionalParticipantEndOfDaySummaryMessage::clone() const {
    return std::make_unique<FractionalParticipantEndOfDaySummaryMessage>(*this);
}

void FractionalParticipantEndOfDaySummaryMessage::print(std::ostream& out) const {
    out << "FractionalParticipantEndOfDaySummaryMessage{";
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
    out << ", last_price=";
    out << last_price_;
    out << ", high_price=";
    out << high_price_;
    out << ", low_price=";
    out << low_price_;
    out << ", open_price=";
    out << open_price_;
    out << ", fractional_total_volume=";
    out << fractional_total_volume_;
    out << ", tick=";
    out << tick_;
    out << '}';
}

bool FractionalParticipantEndOfDaySummaryMessage::equals(const SummaryMessagePayload& other) const {
    const auto* that = dynamic_cast<const FractionalParticipantEndOfDaySummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FractionalParticipantEndOfDaySummaryMessage::operator==(const FractionalParticipantEndOfDaySummaryMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && security_symbol_ == other.security_symbol_
        && instrument_type_ == other.instrument_type_
        && summary_participant_id_ == other.summary_participant_id_
        && previous_close_price_date_ == other.previous_close_price_date_
        && last_price_ == other.last_price_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && open_price_ == other.open_price_
        && fractional_total_volume_ == other.fractional_total_volume_
        && tick_ == other.tick_;
}

bool FractionalParticipantEndOfDaySummaryMessage::operator!=(const FractionalParticipantEndOfDaySummaryMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
