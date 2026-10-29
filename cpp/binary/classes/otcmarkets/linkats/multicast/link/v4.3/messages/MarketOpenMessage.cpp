#include "MarketOpenMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

MarketOpenMessage::MarketOpenMessage(std::uint32_t channel_seq_num, std::chrono::milliseconds market_open, std::uint64_t market_close)
  : channel_seq_num_(channel_seq_num), market_open_(market_open), market_close_(market_close) {}

std::uint32_t MarketOpenMessage::channel_seq_num() const { return channel_seq_num_; }
void MarketOpenMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::chrono::milliseconds MarketOpenMessage::market_open() const { return market_open_; }
void MarketOpenMessage::set_market_open(std::chrono::milliseconds value) { market_open_ = value; }

std::uint64_t MarketOpenMessage::market_close() const { return market_close_; }
void MarketOpenMessage::set_market_close(std::uint64_t value) { market_close_ = value; }

MessageCode MarketOpenMessage::type() const { return message_type; }

std::string_view MarketOpenMessage::name() const { return "Market Open Message"; }

std::size_t MarketOpenMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MarketOpenMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    market_open_ = std::chrono::milliseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    market_close_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t MarketOpenMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketOpenMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(market_open_.count()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(market_close_));
    offset += 8;

    return offset;
}

std::size_t MarketOpenMessage::encoded_size() const {
    return wire_size;
}

void MarketOpenMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MarketOpenMessage::clone() const {
    return std::make_unique<MarketOpenMessage>(*this);
}

void MarketOpenMessage::print(std::ostream& out) const {
    out << "MarketOpenMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", market_open=";
    out << market_open_.count();
    out << ", market_close=";
    out << market_close_;
    out << '}';
}

bool MarketOpenMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MarketOpenMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketOpenMessage::operator==(const MarketOpenMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && market_open_ == other.market_open_
        && market_close_ == other.market_close_;
}

bool MarketOpenMessage::operator!=(const MarketOpenMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
