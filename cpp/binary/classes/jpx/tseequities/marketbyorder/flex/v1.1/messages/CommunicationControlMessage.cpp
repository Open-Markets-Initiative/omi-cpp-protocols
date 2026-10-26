#include "CommunicationControlMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

CommunicationControlMessage::CommunicationControlMessage(TestModeFlag test_mode_flag, CommunicationStartEndFlag communication_start_end_flag)
  : test_mode_flag_(test_mode_flag), communication_start_end_flag_(communication_start_end_flag) {}

TestModeFlag CommunicationControlMessage::test_mode_flag() const { return test_mode_flag_; }
void CommunicationControlMessage::set_test_mode_flag(TestModeFlag value) { test_mode_flag_ = value; }

CommunicationStartEndFlag CommunicationControlMessage::communication_start_end_flag() const { return communication_start_end_flag_; }
void CommunicationControlMessage::set_communication_start_end_flag(CommunicationStartEndFlag value) { communication_start_end_flag_ = value; }

MessageCode CommunicationControlMessage::type() const { return message_type; }

std::string_view CommunicationControlMessage::name() const { return "Communication Control Message"; }

std::size_t CommunicationControlMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CommunicationControlMessage", wire_size, length);

    test_mode_flag_ = static_cast<TestModeFlag>(wire::read_u8(data + offset));
    offset += 1;

    communication_start_end_flag_ = static_cast<CommunicationStartEndFlag>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t CommunicationControlMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CommunicationControlMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(test_mode_flag_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(communication_start_end_flag_));
    offset += 1;

    return offset;
}

std::size_t CommunicationControlMessage::encoded_size() const {
    return wire_size;
}

void CommunicationControlMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CommunicationControlMessage::clone() const {
    return std::make_unique<CommunicationControlMessage>(*this);
}

void CommunicationControlMessage::print(std::ostream& out) const {
    out << "CommunicationControlMessage{";
    out << "test_mode_flag=";
    out << test_mode_flag_;
    out << ", communication_start_end_flag=";
    out << communication_start_end_flag_;
    out << '}';
}

bool CommunicationControlMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CommunicationControlMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CommunicationControlMessage::operator==(const CommunicationControlMessage& other) const {
    return test_mode_flag_ == other.test_mode_flag_
        && communication_start_end_flag_ == other.communication_start_end_flag_;
}

bool CommunicationControlMessage::operator!=(const CommunicationControlMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
