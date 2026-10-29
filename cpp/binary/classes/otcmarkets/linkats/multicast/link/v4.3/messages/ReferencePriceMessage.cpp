#include "ReferencePriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

ReferencePriceMessage::ReferencePriceMessage(std::uint32_t channel_seq_num, std::uint32_t reference_price_id, ReferencePriceAction reference_price_action, const QuoteFlags& quote_flags, std::uint32_t security_id, Decimal ask_price, std::uint32_t ask_size, std::uint64_t ask_time_milli, Decimal bid_price, std::uint32_t bid_size, std::uint64_t bid_time_milli)
  : channel_seq_num_(channel_seq_num), reference_price_id_(reference_price_id), reference_price_action_(reference_price_action), quote_flags_(quote_flags), security_id_(security_id), ask_price_(ask_price), ask_size_(ask_size), ask_time_milli_(ask_time_milli), bid_price_(bid_price), bid_size_(bid_size), bid_time_milli_(bid_time_milli) {}

std::uint32_t ReferencePriceMessage::channel_seq_num() const { return channel_seq_num_; }
void ReferencePriceMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

std::uint32_t ReferencePriceMessage::reference_price_id() const { return reference_price_id_; }
void ReferencePriceMessage::set_reference_price_id(std::uint32_t value) { reference_price_id_ = value; }

ReferencePriceAction ReferencePriceMessage::reference_price_action() const { return reference_price_action_; }
void ReferencePriceMessage::set_reference_price_action(ReferencePriceAction value) { reference_price_action_ = value; }

const QuoteFlags& ReferencePriceMessage::quote_flags() const { return quote_flags_; }
QuoteFlags& ReferencePriceMessage::quote_flags() { return quote_flags_; }
void ReferencePriceMessage::set_quote_flags(const QuoteFlags& value) { quote_flags_ = value; }

std::uint32_t ReferencePriceMessage::security_id() const { return security_id_; }
void ReferencePriceMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

Decimal ReferencePriceMessage::ask_price() const { return ask_price_; }
void ReferencePriceMessage::set_ask_price(Decimal value) { ask_price_ = value; }

std::uint32_t ReferencePriceMessage::ask_size() const { return ask_size_; }
void ReferencePriceMessage::set_ask_size(std::uint32_t value) { ask_size_ = value; }

std::uint64_t ReferencePriceMessage::ask_time_milli() const { return ask_time_milli_; }
void ReferencePriceMessage::set_ask_time_milli(std::uint64_t value) { ask_time_milli_ = value; }

Decimal ReferencePriceMessage::bid_price() const { return bid_price_; }
void ReferencePriceMessage::set_bid_price(Decimal value) { bid_price_ = value; }

std::uint32_t ReferencePriceMessage::bid_size() const { return bid_size_; }
void ReferencePriceMessage::set_bid_size(std::uint32_t value) { bid_size_ = value; }

std::uint64_t ReferencePriceMessage::bid_time_milli() const { return bid_time_milli_; }
void ReferencePriceMessage::set_bid_time_milli(std::uint64_t value) { bid_time_milli_ = value; }

MessageCode ReferencePriceMessage::type() const { return message_type; }

std::string_view ReferencePriceMessage::name() const { return "Reference Price Message"; }

std::size_t ReferencePriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ReferencePriceMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    reference_price_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    reference_price_action_ = static_cast<ReferencePriceAction>(wire::read_u8(data + offset));
    offset += 1;

    offset += quote_flags_.decode(data + offset, length - offset);

    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    ask_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -6);
    offset += 8;

    bid_size_ = wire::read_u32_be(data + offset);
    offset += 4;

    bid_time_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t ReferencePriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ReferencePriceMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(reference_price_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(reference_price_action_));
    offset += 1;

    offset += quote_flags_.encode(data + offset, capacity - offset);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_size_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_time_milli_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_time_milli_));
    offset += 8;

    return offset;
}

std::size_t ReferencePriceMessage::encoded_size() const {
    return wire_size;
}

void ReferencePriceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ReferencePriceMessage::clone() const {
    return std::make_unique<ReferencePriceMessage>(*this);
}

void ReferencePriceMessage::print(std::ostream& out) const {
    out << "ReferencePriceMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", reference_price_id=";
    out << reference_price_id_;
    out << ", reference_price_action=";
    out << reference_price_action_;
    out << ", quote_flags=";
    quote_flags_.print(out);
    out << ", security_id=";
    out << security_id_;
    out << ", ask_price=";
    out << ask_price_;
    out << ", ask_size=";
    out << ask_size_;
    out << ", ask_time_milli=";
    out << ask_time_milli_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", bid_size=";
    out << bid_size_;
    out << ", bid_time_milli=";
    out << bid_time_milli_;
    out << '}';
}

bool ReferencePriceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ReferencePriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ReferencePriceMessage::operator==(const ReferencePriceMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && reference_price_id_ == other.reference_price_id_
        && reference_price_action_ == other.reference_price_action_
        && quote_flags_ == other.quote_flags_
        && security_id_ == other.security_id_
        && ask_price_ == other.ask_price_
        && ask_size_ == other.ask_size_
        && ask_time_milli_ == other.ask_time_milli_
        && bid_price_ == other.bid_price_
        && bid_size_ == other.bid_size_
        && bid_time_milli_ == other.bid_time_milli_;
}

bool ReferencePriceMessage::operator!=(const ReferencePriceMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
