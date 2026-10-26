#include "Participant.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_11_b {

Participant::Participant(ParticipantId participant_id, Decimal fractional_trade_total_volume)
  : participant_id_(participant_id), fractional_trade_total_volume_(fractional_trade_total_volume) {}

ParticipantId Participant::participant_id() const { return participant_id_; }
void Participant::set_participant_id(ParticipantId value) { participant_id_ = value; }

Decimal Participant::fractional_trade_total_volume() const { return fractional_trade_total_volume_; }
void Participant::set_fractional_trade_total_volume(Decimal value) { fractional_trade_total_volume_ = value; }

std::size_t Participant::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Participant", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    fractional_trade_total_volume_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t Participant::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Participant", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(fractional_trade_total_volume_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t Participant::encoded_size() const {
    return wire_size;
}

void Participant::print(std::ostream& out) const {
    out << "Participant{";
    out << "participant_id=";
    out << participant_id_;
    out << ", fractional_trade_total_volume=";
    out << fractional_trade_total_volume_;
    out << '}';
}

bool Participant::operator==(const Participant& other) const {
    return participant_id_ == other.participant_id_
        && fractional_trade_total_volume_ == other.fractional_trade_total_volume_;
}

bool Participant::operator!=(const Participant& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Participant& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
