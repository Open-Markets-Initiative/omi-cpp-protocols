#include "ParticipantTimestamp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cqs::output::cta::v1_91 {

ParticipantTimestamp::ParticipantTimestamp(std::chrono::seconds seconds, std::chrono::nanoseconds nanoseconds)
  : seconds_(seconds), nanoseconds_(nanoseconds) {}

std::chrono::seconds ParticipantTimestamp::seconds() const { return seconds_; }
void ParticipantTimestamp::set_seconds(std::chrono::seconds value) { seconds_ = value; }

std::chrono::nanoseconds ParticipantTimestamp::nanoseconds() const { return nanoseconds_; }
void ParticipantTimestamp::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::size_t ParticipantTimestamp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ParticipantTimestamp", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t ParticipantTimestamp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ParticipantTimestamp", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    return offset;
}

std::size_t ParticipantTimestamp::encoded_size() const {
    return wire_size;
}

void ParticipantTimestamp::print(std::ostream& out) const {
    out << "ParticipantTimestamp{";
    out << "seconds=";
    out << seconds_.count();
    out << ", nanoseconds=";
    out << nanoseconds_.count();
    out << '}';
}

bool ParticipantTimestamp::operator==(const ParticipantTimestamp& other) const {
    return seconds_ == other.seconds_
        && nanoseconds_ == other.nanoseconds_;
}

bool ParticipantTimestamp::operator!=(const ParticipantTimestamp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ParticipantTimestamp& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v1_91
