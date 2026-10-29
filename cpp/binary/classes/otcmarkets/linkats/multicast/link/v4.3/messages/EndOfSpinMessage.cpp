#include "EndOfSpinMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

EndOfSpinMessage::EndOfSpinMessage(std::uint32_t channel_seq_num, SpinType spin_type, std::uint32_t spin_msg_ct, std::uint64_t spin_end_time_milli, std::uint32_t spin_last_seq_num)
  : channel_seq_num_(channel_seq_num), spin_type_(spin_type), spin_msg_ct_(spin_msg_ct), spin_end_time_milli_(spin_end_time_milli), spin_last_seq_num_(spin_last_seq_num) {}

std::uint32_t EndOfSpinMessage::channel_seq_num() const { return channel_seq_num_; }
void EndOfSpinMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

SpinType EndOfSpinMessage::spin_type() const { return spin_type_; }
void EndOfSpinMessage::set_spin_type(SpinType value) { spin_type_ = value; }

std::uint32_t EndOfSpinMessage::spin_msg_ct() const { return spin_msg_ct_; }
void EndOfSpinMessage::set_spin_msg_ct(std::uint32_t value) { spin_msg_ct_ = value; }

std::uint64_t EndOfSpinMessage::spin_end_time_milli() const { return spin_end_time_milli_; }
void EndOfSpinMessage::set_spin_end_time_milli(std::uint64_t value) { spin_end_time_milli_ = value; }

std::uint32_t EndOfSpinMessage::spin_last_seq_num() const { return spin_last_seq_num_; }
void EndOfSpinMessage::set_spin_last_seq_num(std::uint32_t value) { spin_last_seq_num_ = value; }

MessageCode EndOfSpinMessage::type() const { return message_type; }

std::string_view EndOfSpinMessage::name() const { return "End Of Spin Message"; }

std::size_t EndOfSpinMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfSpinMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    spin_type_ = static_cast<SpinType>(wire::read_u8(data + offset));
    offset += 1;

    spin_msg_ct_ = wire::read_u32_be(data + offset);
    offset += 4;

    spin_end_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    spin_last_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t EndOfSpinMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfSpinMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(spin_type_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(spin_msg_ct_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(spin_end_time_milli_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(spin_last_seq_num_));
    offset += 4;

    return offset;
}

std::size_t EndOfSpinMessage::encoded_size() const {
    return wire_size;
}

void EndOfSpinMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EndOfSpinMessage::clone() const {
    return std::make_unique<EndOfSpinMessage>(*this);
}

void EndOfSpinMessage::print(std::ostream& out) const {
    out << "EndOfSpinMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", spin_type=";
    out << spin_type_;
    out << ", spin_msg_ct=";
    out << spin_msg_ct_;
    out << ", spin_end_time_milli=";
    out << spin_end_time_milli_;
    out << ", spin_last_seq_num=";
    out << spin_last_seq_num_;
    out << '}';
}

bool EndOfSpinMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EndOfSpinMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfSpinMessage::operator==(const EndOfSpinMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && spin_type_ == other.spin_type_
        && spin_msg_ct_ == other.spin_msg_ct_
        && spin_end_time_milli_ == other.spin_end_time_milli_
        && spin_last_seq_num_ == other.spin_last_seq_num_;
}

bool EndOfSpinMessage::operator!=(const EndOfSpinMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
