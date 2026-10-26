#include "WidthUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

WidthUpdateMessage::WidthUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& underlying, WidthType width_type, Decimal multiplier)
  : time_offset_(time_offset), underlying_(underlying), width_type_(width_type), multiplier_(multiplier) {}

std::chrono::nanoseconds WidthUpdateMessage::time_offset() const { return time_offset_; }
void WidthUpdateMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& WidthUpdateMessage::underlying() const { return underlying_; }
std::string& WidthUpdateMessage::underlying() { return underlying_; }
void WidthUpdateMessage::set_underlying(const std::string& value) { underlying_ = value; }

WidthType WidthUpdateMessage::width_type() const { return width_type_; }
void WidthUpdateMessage::set_width_type(WidthType value) { width_type_ = value; }

Decimal WidthUpdateMessage::multiplier() const { return multiplier_; }
void WidthUpdateMessage::set_multiplier(Decimal value) { multiplier_ = value; }

MessageCode WidthUpdateMessage::type() const { return message_type; }

std::string_view WidthUpdateMessage::name() const { return "Width Update Message"; }

std::size_t WidthUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("WidthUpdateMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    underlying_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    width_type_ = static_cast<WidthType>(wire::read_char(data + offset));
    offset += 1;

    multiplier_ = Decimal(static_cast<std::int64_t>(wire::read_u32_le(data + offset)), -1);
    offset += 4;

    return offset;
}

std::size_t WidthUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("WidthUpdateMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', underlying_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(width_type_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(multiplier_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t WidthUpdateMessage::encoded_size() const {
    return wire_size;
}

void WidthUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> WidthUpdateMessage::clone() const {
    return std::make_unique<WidthUpdateMessage>(*this);
}

void WidthUpdateMessage::print(std::ostream& out) const {
    out << "WidthUpdateMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", underlying=";
    print::text(out, underlying_);
    out << ", width_type=";
    out << width_type_;
    out << ", multiplier=";
    out << multiplier_;
    out << '}';
}

bool WidthUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const WidthUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool WidthUpdateMessage::operator==(const WidthUpdateMessage& other) const {
    return time_offset_ == other.time_offset_
        && underlying_ == other.underlying_
        && width_type_ == other.width_type_
        && multiplier_ == other.multiplier_;
}

bool WidthUpdateMessage::operator!=(const WidthUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
