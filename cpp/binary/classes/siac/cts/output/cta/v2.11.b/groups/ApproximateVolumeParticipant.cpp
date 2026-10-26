#include "ApproximateVolumeParticipant.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cts::output::cta::v2_11_b {

ApproximateVolumeParticipant::ApproximateVolumeParticipant(ParticipantId participant_id, std::uint64_t trade_total_volume)
  : participant_id_(participant_id), trade_total_volume_(trade_total_volume) {}

ParticipantId ApproximateVolumeParticipant::participant_id() const { return participant_id_; }
void ApproximateVolumeParticipant::set_participant_id(ParticipantId value) { participant_id_ = value; }

std::uint64_t ApproximateVolumeParticipant::trade_total_volume() const { return trade_total_volume_; }
void ApproximateVolumeParticipant::set_trade_total_volume(std::uint64_t value) { trade_total_volume_ = value; }

std::size_t ApproximateVolumeParticipant::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ApproximateVolumeParticipant", wire_size, length);

    participant_id_ = static_cast<ParticipantId>(wire::read_char(data + offset));
    offset += 1;

    trade_total_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t ApproximateVolumeParticipant::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ApproximateVolumeParticipant", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(participant_id_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_total_volume_));
    offset += 8;

    return offset;
}

std::size_t ApproximateVolumeParticipant::encoded_size() const {
    return wire_size;
}

void ApproximateVolumeParticipant::print(std::ostream& out) const {
    out << "ApproximateVolumeParticipant{";
    out << "participant_id=";
    out << participant_id_;
    out << ", trade_total_volume=";
    out << trade_total_volume_;
    out << '}';
}

bool ApproximateVolumeParticipant::operator==(const ApproximateVolumeParticipant& other) const {
    return participant_id_ == other.participant_id_
        && trade_total_volume_ == other.trade_total_volume_;
}

bool ApproximateVolumeParticipant::operator!=(const ApproximateVolumeParticipant& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ApproximateVolumeParticipant& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
