#include "FractionalApproximateAdjustedVolumeMarketCenterMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

FractionalApproximateAdjustedVolumeMarketCenterMessage::FractionalApproximateAdjustedVolumeMarketCenterMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, std::uint8_t number_of_participants, const std::vector<Participant>& participant)
  : participant_id_(participant_id), timestamp_1_(timestamp_1), message_id_(message_id), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), number_of_participants_(number_of_participants), participant_(participant) {}

ParticipantId FractionalApproximateAdjustedVolumeMarketCenterMessage::participant_id() const { return participant_id_; }
void FractionalApproximateAdjustedVolumeMarketCenterMessage::set_participant_id(ParticipantId value) { participant_id_ = value; }

const Timestamp1& FractionalApproximateAdjustedVolumeMarketCenterMessage::timestamp_1() const { return timestamp_1_; }
Timestamp1& FractionalApproximateAdjustedVolumeMarketCenterMessage::timestamp_1() { return timestamp_1_; }
void FractionalApproximateAdjustedVolumeMarketCenterMessage::set_timestamp_1(const Timestamp1& value) { timestamp_1_ = value; }

std::uint8_t FractionalApproximateAdjustedVolumeMarketCenterMessage::message_id() const { return message_id_; }
void FractionalApproximateAdjustedVolumeMarketCenterMessage::set_message_id(std::uint8_t value) { message_id_ = value; }

std::uint32_t FractionalApproximateAdjustedVolumeMarketCenterMessage::transaction_id() const { return transaction_id_; }
void FractionalApproximateAdjustedVolumeMarketCenterMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::int64_t FractionalApproximateAdjustedVolumeMarketCenterMessage::participant_reference_number() const { return participant_reference_number_; }
void FractionalApproximateAdjustedVolumeMarketCenterMessage::set_participant_reference_number(std::int64_t value) { participant_reference_number_ = value; }

std::uint8_t FractionalApproximateAdjustedVolumeMarketCenterMessage::number_of_participants() const { return number_of_participants_; }
void FractionalApproximateAdjustedVolumeMarketCenterMessage::set_number_of_participants(std::uint8_t value) { number_of_participants_ = value; }

const std::vector<Participant>& FractionalApproximateAdjustedVolumeMarketCenterMessage::participant() const { return participant_; }
std::vector<Participant>& FractionalApproximateAdjustedVolumeMarketCenterMessage::participant() { return participant_; }
void FractionalApproximateAdjustedVolumeMarketCenterMessage::set_participant(const std::vector<Participant>& value) { participant_ = value; }

MarketStatusMessagePayloadCode FractionalApproximateAdjustedVolumeMarketCenterMessage::type() const { return message_type; }

std::string_view FractionalApproximateAdjustedVolumeMarketCenterMessage::name() const { return "Fractional Approximate Adjusted Volume Market Center Message"; }

std::size_t FractionalApproximateAdjustedVolumeMarketCenterMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("FractionalApproximateAdjustedVolumeMarketCenterMessage", offset + 1, length);
    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    offset += timestamp_1_.decode(data + offset, length - offset);

    wire::require("FractionalApproximateAdjustedVolumeMarketCenterMessage", offset + 1, length);
    message_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("FractionalApproximateAdjustedVolumeMarketCenterMessage", offset + 4, length);
    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("FractionalApproximateAdjustedVolumeMarketCenterMessage", offset + 8, length);
    participant_reference_number_ = wire::read_i64_be(data + offset);
    offset += 8;

    wire::require("FractionalApproximateAdjustedVolumeMarketCenterMessage", offset + 1, length);
    number_of_participants_ = wire::read_u8(data + offset);
    offset += 1;

    {
        const std::size_t count = wire::count(number_of_participants_);
        participant_.clear();
        participant_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            Participant entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            participant_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t FractionalApproximateAdjustedVolumeMarketCenterMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FractionalApproximateAdjustedVolumeMarketCenterMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto number_of_participants = number_of_participants_;
    number_of_participants = static_cast<std::uint8_t>(participant_.size());

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    offset += timestamp_1_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_id_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(participant_reference_number_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(number_of_participants));
    offset += 1;

    for (const auto& entry : participant_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t FractionalApproximateAdjustedVolumeMarketCenterMessage::encoded_size() const {
    return 1 + timestamp_1_.encoded_size() + 1 + 4 + 8 + 1 + wire::encoded_size_of(participant_);
}

void FractionalApproximateAdjustedVolumeMarketCenterMessage::accept(MarketStatusMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MarketStatusMessagePayload> FractionalApproximateAdjustedVolumeMarketCenterMessage::clone() const {
    return std::make_unique<FractionalApproximateAdjustedVolumeMarketCenterMessage>(*this);
}

void FractionalApproximateAdjustedVolumeMarketCenterMessage::print(std::ostream& out) const {
    out << "FractionalApproximateAdjustedVolumeMarketCenterMessage{";
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
    out << ", number_of_participants=";
    out << static_cast<int>(number_of_participants_);
    out << ", participant=";
    print::sequence(out, participant_);
    out << '}';
}

bool FractionalApproximateAdjustedVolumeMarketCenterMessage::equals(const MarketStatusMessagePayload& other) const {
    const auto* that = dynamic_cast<const FractionalApproximateAdjustedVolumeMarketCenterMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FractionalApproximateAdjustedVolumeMarketCenterMessage::operator==(const FractionalApproximateAdjustedVolumeMarketCenterMessage& other) const {
    return participant_id_ == other.participant_id_
        && timestamp_1_ == other.timestamp_1_
        && message_id_ == other.message_id_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && number_of_participants_ == other.number_of_participants_
        && participant_ == other.participant_;
}

bool FractionalApproximateAdjustedVolumeMarketCenterMessage::operator!=(const FractionalApproximateAdjustedVolumeMarketCenterMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
