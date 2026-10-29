#include "Participants.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_10 {

Participants::Participants(ParticipantId participant_id, std::uint64_t trade_total_volume)
  : participant_id_(participant_id), trade_total_volume_(trade_total_volume) {}

ParticipantId Participants::participant_id() const { return participant_id_; }
void Participants::set_participant_id(ParticipantId value) { participant_id_ = value; }

std::uint64_t Participants::trade_total_volume() const { return trade_total_volume_; }
void Participants::set_trade_total_volume(std::uint64_t value) { trade_total_volume_ = value; }

std::size_t Participants::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Participants", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    trade_total_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t Participants::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Participants", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_total_volume_));
    offset += 8;

    return offset;
}

std::size_t Participants::encoded_size() const {
    return wire_size;
}

void Participants::print(std::ostream& out) const {
    out << "Participants{";
    out << "participant_id=";
    out << participant_id_;
    out << ", trade_total_volume=";
    out << trade_total_volume_;
    out << '}';
}

bool Participants::operator==(const Participants& other) const {
    return participant_id_ == other.participant_id_
        && trade_total_volume_ == other.trade_total_volume_;
}

bool Participants::operator!=(const Participants& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Participants& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_10
