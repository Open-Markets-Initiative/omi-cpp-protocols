// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.41.29: messages/EndOfSession.cpp
#include "EndOfSession.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

EndOfSession::EndOfSession(std::chrono::nanoseconds time_offset)
  : time_offset_(time_offset) {}

std::chrono::nanoseconds EndOfSession::time_offset() const { return time_offset_; }
void EndOfSession::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

MessageCode EndOfSession::type() const { return message_type; }

std::string_view EndOfSession::name() const { return "End Of Session"; }

std::size_t EndOfSession::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfSession", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t EndOfSession::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfSession", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    return offset;
}

std::size_t EndOfSession::encoded_size() const {
    return wire_size;
}

void EndOfSession::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EndOfSession::clone() const {
    return std::make_unique<EndOfSession>(*this);
}

void EndOfSession::print(std::ostream& out) const {
    out << "EndOfSession{";
    out << "time_offset=";
    out << time_offset_.count();
    out << '}';
}

bool EndOfSession::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EndOfSession*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfSession::operator==(const EndOfSession& other) const {
    return time_offset_ == other.time_offset_;
}

bool EndOfSession::operator!=(const EndOfSession& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29
