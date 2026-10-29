#include "UnitClearMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

UnitClearMessage::UnitClearMessage(std::chrono::nanoseconds time_offset)
  : time_offset_(time_offset) {}

std::chrono::nanoseconds UnitClearMessage::time_offset() const { return time_offset_; }
void UnitClearMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

MessageCode UnitClearMessage::type() const { return message_type; }

std::string_view UnitClearMessage::name() const { return "Unit Clear Message"; }

std::size_t UnitClearMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnitClearMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t UnitClearMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnitClearMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    return offset;
}

std::size_t UnitClearMessage::encoded_size() const {
    return wire_size;
}

void UnitClearMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> UnitClearMessage::clone() const {
    return std::make_unique<UnitClearMessage>(*this);
}

void UnitClearMessage::print(std::ostream& out) const {
    out << "UnitClearMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << '}';
}

bool UnitClearMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const UnitClearMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnitClearMessage::operator==(const UnitClearMessage& other) const {
    return time_offset_ == other.time_offset_;
}

bool UnitClearMessage::operator!=(const UnitClearMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29
