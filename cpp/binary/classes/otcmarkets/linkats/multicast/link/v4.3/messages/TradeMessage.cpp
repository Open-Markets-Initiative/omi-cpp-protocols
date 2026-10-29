#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

TradeMessage::TradeMessage(std::uint32_t channel_seq_num, std::uint32_t trade_id, TradeAction trade_action, std::uint8_t trade_flags, std::uint32_t security_id, const TradeStatus& trade_status, const std::string& deprecated, Decimal trade_price, std::uint32_t trade_size, std::uint64_t trade_time_milli)
  : channel_seq_num_(channel_seq_num), trade_id_(trade_id), trade_action_(trade_action), trade_flags_(trade_flags), security_id_(security_id), trade_status_(trade_status), deprecated_(deprecated), trade_price_(trade_price), trade_size_(trade_size), trade_time_milli_(trade_time_milli) {}

std::uint32_t TradeMessage::channel_seq_num() const { return channel_seq_num_; }
void TradeMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::uint32_t TradeMessage::trade_id() const { return trade_id_; }
void TradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

TradeAction TradeMessage::trade_action() const { return trade_action_; }
void TradeMessage::set_trade_action(TradeAction value) { trade_action_ = value; }

std::uint8_t TradeMessage::trade_flags() const { return trade_flags_; }
void TradeMessage::set_trade_flags(std::uint8_t value) { trade_flags_ = value; }

std::uint32_t TradeMessage::security_id() const { return security_id_; }
void TradeMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

const TradeStatus& TradeMessage::trade_status() const { return trade_status_; }
TradeStatus& TradeMessage::trade_status() { return trade_status_; }
void TradeMessage::set_trade_status(const TradeStatus& value) { trade_status_ = value; }

const std::string& TradeMessage::deprecated() const { return deprecated_; }
std::string& TradeMessage::deprecated() { return deprecated_; }
void TradeMessage::set_deprecated(const std::string& value) { deprecated_ = value; }

Decimal TradeMessage::trade_price() const { return trade_price_; }
void TradeMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t TradeMessage::trade_size() const { return trade_size_; }
void TradeMessage::set_trade_size(std::uint32_t value) { trade_size_ = value; }

std::uint64_t TradeMessage::trade_time_milli() const { return trade_time_milli_; }
void TradeMessage::set_trade_time_milli(std::uint64_t value) { trade_time_milli_ = value; }

MessageCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_action_ = static_cast<TradeAction>(wire::read_u8(data + offset));
    offset += 1;

    trade_flags_ = wire::read_u8(data + offset);
    offset += 1;

    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += trade_status_.decode(data + offset, length - offset);

    deprecated_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    trade_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trade_action_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trade_flags_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    offset += trade_status_.encode(data + offset, capacity - offset);

    wire::write_text(data + offset, 8, ' ', deprecated_);
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(trade_size_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_time_milli_));
    offset += 8;

    return offset;
}

std::size_t TradeMessage::encoded_size() const {
    return wire_size;
}

void TradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", trade_action=";
    out << trade_action_;
    out << ", trade_flags=";
    out << static_cast<int>(trade_flags_);
    out << ", security_id=";
    out << security_id_;
    out << ", trade_status=";
    trade_status_.print(out);
    out << ", deprecated=";
    print::text(out, deprecated_);
    out << ", trade_price=";
    out << trade_price_;
    out << ", trade_size=";
    out << trade_size_;
    out << ", trade_time_milli=";
    out << trade_time_milli_;
    out << '}';
}

bool TradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && trade_id_ == other.trade_id_
        && trade_action_ == other.trade_action_
        && trade_flags_ == other.trade_flags_
        && security_id_ == other.security_id_
        && trade_status_ == other.trade_status_
        && deprecated_ == other.deprecated_
        && trade_price_ == other.trade_price_
        && trade_size_ == other.trade_size_
        && trade_time_milli_ == other.trade_time_milli_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
