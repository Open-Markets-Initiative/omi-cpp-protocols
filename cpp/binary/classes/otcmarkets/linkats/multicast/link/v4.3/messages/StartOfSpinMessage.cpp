#include "StartOfSpinMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

StartOfSpinMessage::StartOfSpinMessage(std::uint32_t channel_seq_num, SpinType spin_type, std::uint64_t spin_start_time_milli, std::uint32_t spin_last_seq_num)
  : channel_seq_num_(channel_seq_num), spin_type_(spin_type), spin_start_time_milli_(spin_start_time_milli), spin_last_seq_num_(spin_last_seq_num) {}

std::uint32_t StartOfSpinMessage::channel_seq_num() const { return channel_seq_num_; }
void StartOfSpinMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

SpinType StartOfSpinMessage::spin_type() const { return spin_type_; }
void StartOfSpinMessage::set_spin_type(SpinType value) { spin_type_ = value; }

std::uint64_t StartOfSpinMessage::spin_start_time_milli() const { return spin_start_time_milli_; }
void StartOfSpinMessage::set_spin_start_time_milli(std::uint64_t value) { spin_start_time_milli_ = value; }

std::uint32_t StartOfSpinMessage::spin_last_seq_num() const { return spin_last_seq_num_; }
void StartOfSpinMessage::set_spin_last_seq_num(std::uint32_t value) { spin_last_seq_num_ = value; }

MessageCode StartOfSpinMessage::type() const { return message_type; }

std::string_view StartOfSpinMessage::name() const { return "Start Of Spin Message"; }

std::size_t StartOfSpinMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StartOfSpinMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    spin_type_ = static_cast<SpinType>(wire::read_u8(data + offset));
    offset += 1;

    spin_start_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    spin_last_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t StartOfSpinMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StartOfSpinMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(spin_type_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(spin_start_time_milli_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(spin_last_seq_num_));
    offset += 4;

    return offset;
}

std::size_t StartOfSpinMessage::encoded_size() const {
    return wire_size;
}

void StartOfSpinMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StartOfSpinMessage::clone() const {
    return std::make_unique<StartOfSpinMessage>(*this);
}

void StartOfSpinMessage::print(std::ostream& out) const {
    out << "StartOfSpinMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", spin_type=";
    out << spin_type_;
    out << ", spin_start_time_milli=";
    out << spin_start_time_milli_;
    out << ", spin_last_seq_num=";
    out << spin_last_seq_num_;
    out << '}';
}

bool StartOfSpinMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StartOfSpinMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StartOfSpinMessage::operator==(const StartOfSpinMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && spin_type_ == other.spin_type_
        && spin_start_time_milli_ == other.spin_start_time_milli_
        && spin_last_seq_num_ == other.spin_last_seq_num_;
}

bool StartOfSpinMessage::operator!=(const StartOfSpinMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
