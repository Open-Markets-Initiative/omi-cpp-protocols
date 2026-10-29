#include "MarketCloseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

MarketCloseMessage::MarketCloseMessage(std::uint32_t channel_seq_num, std::uint64_t market_close_time_milli, std::uint32_t market_msg_ct)
  : channel_seq_num_(channel_seq_num), market_close_time_milli_(market_close_time_milli), market_msg_ct_(market_msg_ct) {}

std::uint32_t MarketCloseMessage::channel_seq_num() const { return channel_seq_num_; }
void MarketCloseMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::uint64_t MarketCloseMessage::market_close_time_milli() const { return market_close_time_milli_; }
void MarketCloseMessage::set_market_close_time_milli(std::uint64_t value) { market_close_time_milli_ = value; }

std::uint32_t MarketCloseMessage::market_msg_ct() const { return market_msg_ct_; }
void MarketCloseMessage::set_market_msg_ct(std::uint32_t value) { market_msg_ct_ = value; }

MessageCode MarketCloseMessage::type() const { return message_type; }

std::string_view MarketCloseMessage::name() const { return "Market Close Message"; }

std::size_t MarketCloseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MarketCloseMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    market_close_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    market_msg_ct_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t MarketCloseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketCloseMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(market_close_time_milli_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(market_msg_ct_));
    offset += 4;

    return offset;
}

std::size_t MarketCloseMessage::encoded_size() const {
    return wire_size;
}

void MarketCloseMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MarketCloseMessage::clone() const {
    return std::make_unique<MarketCloseMessage>(*this);
}

void MarketCloseMessage::print(std::ostream& out) const {
    out << "MarketCloseMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", market_close_time_milli=";
    out << market_close_time_milli_;
    out << ", market_msg_ct=";
    out << market_msg_ct_;
    out << '}';
}

bool MarketCloseMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MarketCloseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketCloseMessage::operator==(const MarketCloseMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && market_close_time_milli_ == other.market_close_time_milli_
        && market_msg_ct_ == other.market_msg_ct_;
}

bool MarketCloseMessage::operator!=(const MarketCloseMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
