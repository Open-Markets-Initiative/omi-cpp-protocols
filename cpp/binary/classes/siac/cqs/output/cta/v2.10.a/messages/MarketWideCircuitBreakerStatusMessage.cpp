#include "MarketWideCircuitBreakerStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cqs::output::cta::v2_10_a {

MarketWideCircuitBreakerStatusMessage::MarketWideCircuitBreakerStatusMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, MarketWideCircuitBreakerLevelIndicator market_wide_circuit_breaker_level_indicator, char reserved)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), market_wide_circuit_breaker_level_indicator_(market_wide_circuit_breaker_level_indicator), reserved_(reserved) {}

ParticipantId MarketWideCircuitBreakerStatusMessage::participant_id() const { return participant_id_; }
void MarketWideCircuitBreakerStatusMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& MarketWideCircuitBreakerStatusMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& MarketWideCircuitBreakerStatusMessage::timestamp_1() { return timestamp_1_; }
void MarketWideCircuitBreakerStatusMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t MarketWideCircuitBreakerStatusMessage::message_id() const { return message_id_; }
void MarketWideCircuitBreakerStatusMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t MarketWideCircuitBreakerStatusMessage::transaction_id() const { return transaction_id_; }
void MarketWideCircuitBreakerStatusMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t MarketWideCircuitBreakerStatusMessage::participant_reference_number() const { return participant_reference_number_; }
void MarketWideCircuitBreakerStatusMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

MarketWideCircuitBreakerLevelIndicator MarketWideCircuitBreakerStatusMessage::market_wide_circuit_breaker_level_indicator() const { return market_wide_circuit_breaker_level_indicator_; }
void MarketWideCircuitBreakerStatusMessage::set_market_wide_circuit_breaker_level_indicator(MarketWideCircuitBreakerLevelIndicator value) { market_wide_circuit_breaker_level_indicator_ = value; }

char MarketWideCircuitBreakerStatusMessage::reserved() const { return reserved_; }
void MarketWideCircuitBreakerStatusMessage::set_reserved(char value) { reserved_ = value; }

MarketStatusMessagePayloadCode MarketWideCircuitBreakerStatusMessage::type() const { return message_type; }

std::string_view MarketWideCircuitBreakerStatusMessage::name() const { return "Market Wide Circuit Breaker Status Message"; }

std::size_t MarketWideCircuitBreakerStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MarketWideCircuitBreakerStatusMessage", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    market_wide_circuit_breaker_level_indicator_ = static_cast<MarketWideCircuitBreakerLevelIndicator>(wire::read_char(data + offset));
    offset += 1;

    reserved_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t MarketWideCircuitBreakerStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketWideCircuitBreakerStatusMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(market_wide_circuit_breaker_level_indicator_));
    offset += 1;

    wire::write_char(data + offset, reserved_);
    offset += 1;

    return offset;
}

std::size_t MarketWideCircuitBreakerStatusMessage::encoded_size() const {
    return wire_size;
}

void MarketWideCircuitBreakerStatusMessage::accept(MarketStatusMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MarketStatusMessagePayload> MarketWideCircuitBreakerStatusMessage::clone() const {
    return std::make_unique<MarketWideCircuitBreakerStatusMessage>(*this);
}

void MarketWideCircuitBreakerStatusMessage::print(std::ostream& out) const {
    out << "MarketWideCircuitBreakerStatusMessage{";
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
    out << ", market_wide_circuit_breaker_level_indicator=";
    out << market_wide_circuit_breaker_level_indicator_;
    out << ", reserved=";
    print::character(out, reserved_);
    out << '}';
}

bool MarketWideCircuitBreakerStatusMessage::equals(const MarketStatusMessagePayload& other) const {
    const auto* that = dynamic_cast<const MarketWideCircuitBreakerStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketWideCircuitBreakerStatusMessage::operator==(const MarketWideCircuitBreakerStatusMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && market_wide_circuit_breaker_level_indicator_ == other.market_wide_circuit_breaker_level_indicator_
        && reserved_ == other.reserved_;
}

bool MarketWideCircuitBreakerStatusMessage::operator!=(const MarketWideCircuitBreakerStatusMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cqs::output::cta::v2_10_a
