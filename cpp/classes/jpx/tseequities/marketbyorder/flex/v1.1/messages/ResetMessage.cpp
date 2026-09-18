#include "ResetMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

ResetMessage::ResetMessage(ResetStartEndFlag reset_start_end_flag)
  : reset_start_end_flag_(reset_start_end_flag) {}

ResetStartEndFlag ResetMessage::reset_start_end_flag() const { return reset_start_end_flag_; }
void ResetMessage::set_reset_start_end_flag(ResetStartEndFlag value) { reset_start_end_flag_ = value; }

MessageCode ResetMessage::type() const { return message_type; }

std::string_view ResetMessage::name() const { return "Reset Message"; }

std::size_t ResetMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ResetMessage", wire_size, length);

    reset_start_end_flag_ = static_cast<ResetStartEndFlag>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t ResetMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ResetMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(reset_start_end_flag_));
    offset += 1;

    return offset;
}

std::size_t ResetMessage::encoded_size() const {
    return wire_size;
}

void ResetMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ResetMessage::clone() const {
    return std::make_unique<ResetMessage>(*this);
}

void ResetMessage::print(std::ostream& out) const {
    out << "ResetMessage{";
    out << "reset_start_end_flag=";
    out << reset_start_end_flag_;
    out << '}';
}

bool ResetMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ResetMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ResetMessage::operator==(const ResetMessage& other) const {
    return reset_start_end_flag_ == other.reset_start_end_flag_;
}

bool ResetMessage::operator!=(const ResetMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
