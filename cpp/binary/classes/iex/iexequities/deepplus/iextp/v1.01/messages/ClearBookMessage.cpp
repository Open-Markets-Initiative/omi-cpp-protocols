#include "ClearBookMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::iextp::v1_01 {

ClearBookMessage::ClearBookMessage(char reserved_1, std::chrono::nanoseconds timestamp, const std::string& symbol)
  : reserved_1_(reserved_1), timestamp_(timestamp), symbol_(symbol) {}

char ClearBookMessage::reserved_1() const { return reserved_1_; }
void ClearBookMessage::set_reserved_1(char value) { reserved_1_ = value; }

std::chrono::nanoseconds ClearBookMessage::timestamp() const { return timestamp_; }
void ClearBookMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& ClearBookMessage::symbol() const { return symbol_; }
std::string& ClearBookMessage::symbol() { return symbol_; }
void ClearBookMessage::set_symbol(const std::string& value) { symbol_ = value; }

MessageCode ClearBookMessage::type() const { return message_type; }

std::string_view ClearBookMessage::name() const { return "Clear Book Message"; }

std::size_t ClearBookMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ClearBookMessage", wire_size, length);

    reserved_1_ = wire::read_char(data + offset);
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    return offset;
}

std::size_t ClearBookMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClearBookMessage", wire_size, capacity);

    wire::write_char(data + offset, reserved_1_);
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    return offset;
}

std::size_t ClearBookMessage::encoded_size() const {
    return wire_size;
}

void ClearBookMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ClearBookMessage::clone() const {
    return std::make_unique<ClearBookMessage>(*this);
}

void ClearBookMessage::print(std::ostream& out) const {
    out << "ClearBookMessage{";
    out << "reserved_1=";
    print::character(out, reserved_1_);
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << '}';
}

bool ClearBookMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ClearBookMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ClearBookMessage::operator==(const ClearBookMessage& other) const {
    return reserved_1_ == other.reserved_1_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_;
}

bool ClearBookMessage::operator!=(const ClearBookMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::iextp::v1_01
