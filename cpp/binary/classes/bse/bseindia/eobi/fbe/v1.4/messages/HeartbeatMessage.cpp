#include "HeartbeatMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

HeartbeatMessage::HeartbeatMessage(std::uint32_t last_msg_seq_num_processed, const std::array<std::byte, 4>& pad_4)
  : last_msg_seq_num_processed_(last_msg_seq_num_processed), pad_4_(pad_4) {}

std::uint32_t HeartbeatMessage::last_msg_seq_num_processed() const { return last_msg_seq_num_processed_; }
void HeartbeatMessage::set_last_msg_seq_num_processed(std::uint32_t value) { last_msg_seq_num_processed_ = value; }

const std::array<std::byte, 4>& HeartbeatMessage::pad_4() const { return pad_4_; }
std::array<std::byte, 4>& HeartbeatMessage::pad_4() { return pad_4_; }
void HeartbeatMessage::set_pad_4(const std::array<std::byte, 4>& value) { pad_4_ = value; }

MessageCode HeartbeatMessage::type() const { return message_type; }

std::string_view HeartbeatMessage::name() const { return "Heartbeat Message"; }

std::size_t HeartbeatMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("HeartbeatMessage", wire_size, length);

    last_msg_seq_num_processed_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t HeartbeatMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("HeartbeatMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_msg_seq_num_processed_));
    offset += 4;

    wire::write_bytes(data + offset, pad_4_.data(), 4);
    offset += 4;

    return offset;
}

std::size_t HeartbeatMessage::encoded_size() const {
    return wire_size;
}

void HeartbeatMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> HeartbeatMessage::clone() const {
    return std::make_unique<HeartbeatMessage>(*this);
}

void HeartbeatMessage::print(std::ostream& out) const {
    out << "HeartbeatMessage{";
    out << "last_msg_seq_num_processed=";
    out << last_msg_seq_num_processed_;
    out << ", pad_4=";
    print::hex(out, pad_4_.data(), pad_4_.size());
    out << '}';
}

bool HeartbeatMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const HeartbeatMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool HeartbeatMessage::operator==(const HeartbeatMessage& other) const {
    return last_msg_seq_num_processed_ == other.last_msg_seq_num_processed_
        && pad_4_ == other.pad_4_;
}

bool HeartbeatMessage::operator!=(const HeartbeatMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
