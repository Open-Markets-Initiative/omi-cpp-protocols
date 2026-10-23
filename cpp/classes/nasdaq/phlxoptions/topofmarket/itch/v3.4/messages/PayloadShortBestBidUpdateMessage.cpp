#include "PayloadShortBestBidUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

PayloadShortBestBidUpdateMessage::PayloadShortBestBidUpdateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, QuoteCondition quote_condition, Decimal price_2, std::uint16_t size_2)
  : nanoseconds_(nanoseconds), option_id_(option_id), quote_condition_(quote_condition), price_2_(price_2), size_2_(size_2) {}

std::chrono::nanoseconds PayloadShortBestBidUpdateMessage::nanoseconds() const { return nanoseconds_; }
void PayloadShortBestBidUpdateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t PayloadShortBestBidUpdateMessage::option_id() const { return option_id_; }
void PayloadShortBestBidUpdateMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

QuoteCondition PayloadShortBestBidUpdateMessage::quote_condition() const { return quote_condition_; }
void PayloadShortBestBidUpdateMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

Decimal PayloadShortBestBidUpdateMessage::price_2() const { return price_2_; }
void PayloadShortBestBidUpdateMessage::set_price_2(Decimal value) { price_2_ = value; }

std::uint16_t PayloadShortBestBidUpdateMessage::size_2() const { return size_2_; }
void PayloadShortBestBidUpdateMessage::set_size_2(std::uint16_t value) { size_2_ = value; }

PacketMessageCode PayloadShortBestBidUpdateMessage::type() const { return message_type; }

std::string_view PayloadShortBestBidUpdateMessage::name() const { return "Short Best Bid Update Message"; }

std::size_t PayloadShortBestBidUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadShortBestBidUpdateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    price_2_ = Decimal(static_cast<std::int64_t>(wire::read_u16_be(data + offset)), -2);
    offset += 2;

    size_2_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t PayloadShortBestBidUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadShortBestBidUpdateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(price_2_.mantissa()));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(size_2_));
    offset += 2;

    return offset;
}

std::size_t PayloadShortBestBidUpdateMessage::encoded_size() const {
    return wire_size;
}

void PayloadShortBestBidUpdateMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadShortBestBidUpdateMessage::clone() const {
    return std::make_unique<PayloadShortBestBidUpdateMessage>(*this);
}

void PayloadShortBestBidUpdateMessage::print(std::ostream& out) const {
    out << "PayloadShortBestBidUpdateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", price_2=";
    out << price_2_;
    out << ", size_2=";
    out << size_2_;
    out << '}';
}

bool PayloadShortBestBidUpdateMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadShortBestBidUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadShortBestBidUpdateMessage::operator==(const PayloadShortBestBidUpdateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && quote_condition_ == other.quote_condition_
        && price_2_ == other.price_2_
        && size_2_ == other.size_2_;
}

bool PayloadShortBestBidUpdateMessage::operator!=(const PayloadShortBestBidUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
