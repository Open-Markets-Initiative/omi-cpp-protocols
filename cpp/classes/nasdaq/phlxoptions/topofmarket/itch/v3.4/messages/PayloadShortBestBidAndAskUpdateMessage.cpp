#include "PayloadShortBestBidAndAskUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

PayloadShortBestBidAndAskUpdateMessage::PayloadShortBestBidAndAskUpdateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, QuoteCondition quote_condition, Decimal bid_price_2, std::uint16_t bid_size_2, Decimal ask_price_2, std::uint16_t ask_size_2)
  : nanoseconds_(nanoseconds), option_id_(option_id), quote_condition_(quote_condition), bid_price_2_(bid_price_2), bid_size_2_(bid_size_2), ask_price_2_(ask_price_2), ask_size_2_(ask_size_2) {}

std::chrono::nanoseconds PayloadShortBestBidAndAskUpdateMessage::nanoseconds() const { return nanoseconds_; }
void PayloadShortBestBidAndAskUpdateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t PayloadShortBestBidAndAskUpdateMessage::option_id() const { return option_id_; }
void PayloadShortBestBidAndAskUpdateMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

QuoteCondition PayloadShortBestBidAndAskUpdateMessage::quote_condition() const { return quote_condition_; }
void PayloadShortBestBidAndAskUpdateMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

Decimal PayloadShortBestBidAndAskUpdateMessage::bid_price_2() const { return bid_price_2_; }
void PayloadShortBestBidAndAskUpdateMessage::set_bid_price_2(Decimal value) { bid_price_2_ = value; }

std::uint16_t PayloadShortBestBidAndAskUpdateMessage::bid_size_2() const { return bid_size_2_; }
void PayloadShortBestBidAndAskUpdateMessage::set_bid_size_2(std::uint16_t value) { bid_size_2_ = value; }

Decimal PayloadShortBestBidAndAskUpdateMessage::ask_price_2() const { return ask_price_2_; }
void PayloadShortBestBidAndAskUpdateMessage::set_ask_price_2(Decimal value) { ask_price_2_ = value; }

std::uint16_t PayloadShortBestBidAndAskUpdateMessage::ask_size_2() const { return ask_size_2_; }
void PayloadShortBestBidAndAskUpdateMessage::set_ask_size_2(std::uint16_t value) { ask_size_2_ = value; }

PacketMessageCode PayloadShortBestBidAndAskUpdateMessage::type() const { return message_type; }

std::string_view PayloadShortBestBidAndAskUpdateMessage::name() const { return "Short Best Bid And Ask Update Message"; }

std::size_t PayloadShortBestBidAndAskUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadShortBestBidAndAskUpdateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    bid_price_2_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    bid_size_2_ = wire::read_u16_be(data + offset);
    offset += 2;

    ask_price_2_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    ask_size_2_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t PayloadShortBestBidAndAskUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadShortBestBidAndAskUpdateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_price_2_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(bid_size_2_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(ask_price_2_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(ask_size_2_));
    offset += 2;

    return offset;
}

std::size_t PayloadShortBestBidAndAskUpdateMessage::encoded_size() const {
    return wire_size;
}

void PayloadShortBestBidAndAskUpdateMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadShortBestBidAndAskUpdateMessage::clone() const {
    return std::make_unique<PayloadShortBestBidAndAskUpdateMessage>(*this);
}

void PayloadShortBestBidAndAskUpdateMessage::print(std::ostream& out) const {
    out << "PayloadShortBestBidAndAskUpdateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", bid_price_2=";
    out << bid_price_2_;
    out << ", bid_size_2=";
    out << bid_size_2_;
    out << ", ask_price_2=";
    out << ask_price_2_;
    out << ", ask_size_2=";
    out << ask_size_2_;
    out << '}';
}

bool PayloadShortBestBidAndAskUpdateMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadShortBestBidAndAskUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadShortBestBidAndAskUpdateMessage::operator==(const PayloadShortBestBidAndAskUpdateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && quote_condition_ == other.quote_condition_
        && bid_price_2_ == other.bid_price_2_
        && bid_size_2_ == other.bid_size_2_
        && ask_price_2_ == other.ask_price_2_
        && ask_size_2_ == other.ask_size_2_;
}

bool PayloadShortBestBidAndAskUpdateMessage::operator!=(const PayloadShortBestBidAndAskUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
