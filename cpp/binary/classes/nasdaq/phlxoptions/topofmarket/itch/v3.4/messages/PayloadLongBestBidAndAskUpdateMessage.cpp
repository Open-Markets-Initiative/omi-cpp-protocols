#include "PayloadLongBestBidAndAskUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

PayloadLongBestBidAndAskUpdateMessage::PayloadLongBestBidAndAskUpdateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, QuoteCondition quote_condition, Decimal bid_price_4, std::uint32_t bid_size_4, Decimal ask_price_4, std::uint32_t ask_size_4)
  : nanoseconds_(nanoseconds), option_id_(option_id), quote_condition_(quote_condition), bid_price_4_(bid_price_4), bid_size_4_(bid_size_4), ask_price_4_(ask_price_4), ask_size_4_(ask_size_4) {}

std::chrono::nanoseconds PayloadLongBestBidAndAskUpdateMessage::nanoseconds() const { return nanoseconds_; }
void PayloadLongBestBidAndAskUpdateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t PayloadLongBestBidAndAskUpdateMessage::option_id() const { return option_id_; }
void PayloadLongBestBidAndAskUpdateMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

QuoteCondition PayloadLongBestBidAndAskUpdateMessage::quote_condition() const { return quote_condition_; }
void PayloadLongBestBidAndAskUpdateMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

Decimal PayloadLongBestBidAndAskUpdateMessage::bid_price_4() const { return bid_price_4_; }
void PayloadLongBestBidAndAskUpdateMessage::set_bid_price_4(Decimal value) { bid_price_4_ = value; }

std::uint32_t PayloadLongBestBidAndAskUpdateMessage::bid_size_4() const { return bid_size_4_; }
void PayloadLongBestBidAndAskUpdateMessage::set_bid_size_4(std::uint32_t value) { bid_size_4_ = value; }

Decimal PayloadLongBestBidAndAskUpdateMessage::ask_price_4() const { return ask_price_4_; }
void PayloadLongBestBidAndAskUpdateMessage::set_ask_price_4(Decimal value) { ask_price_4_ = value; }

std::uint32_t PayloadLongBestBidAndAskUpdateMessage::ask_size_4() const { return ask_size_4_; }
void PayloadLongBestBidAndAskUpdateMessage::set_ask_size_4(std::uint32_t value) { ask_size_4_ = value; }

PacketMessageCode PayloadLongBestBidAndAskUpdateMessage::type() const { return message_type; }

std::string_view PayloadLongBestBidAndAskUpdateMessage::name() const { return "Long Best Bid And Ask Update Message"; }

std::size_t PayloadLongBestBidAndAskUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadLongBestBidAndAskUpdateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    bid_price_4_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    bid_size_4_ = wire::read_u32_be(data + offset);
    offset += 4;

    ask_price_4_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    ask_size_4_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t PayloadLongBestBidAndAskUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadLongBestBidAndAskUpdateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(bid_price_4_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(bid_size_4_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(ask_price_4_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(ask_size_4_));
    offset += 4;

    return offset;
}

std::size_t PayloadLongBestBidAndAskUpdateMessage::encoded_size() const {
    return wire_size;
}

void PayloadLongBestBidAndAskUpdateMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadLongBestBidAndAskUpdateMessage::clone() const {
    return std::make_unique<PayloadLongBestBidAndAskUpdateMessage>(*this);
}

void PayloadLongBestBidAndAskUpdateMessage::print(std::ostream& out) const {
    out << "PayloadLongBestBidAndAskUpdateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", bid_price_4=";
    out << bid_price_4_;
    out << ", bid_size_4=";
    out << bid_size_4_;
    out << ", ask_price_4=";
    out << ask_price_4_;
    out << ", ask_size_4=";
    out << ask_size_4_;
    out << '}';
}

bool PayloadLongBestBidAndAskUpdateMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadLongBestBidAndAskUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadLongBestBidAndAskUpdateMessage::operator==(const PayloadLongBestBidAndAskUpdateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && quote_condition_ == other.quote_condition_
        && bid_price_4_ == other.bid_price_4_
        && bid_size_4_ == other.bid_size_4_
        && ask_price_4_ == other.ask_price_4_
        && ask_size_4_ == other.ask_size_4_;
}

bool PayloadLongBestBidAndAskUpdateMessage::operator!=(const PayloadLongBestBidAndAskUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
