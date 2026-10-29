#include "AuctionTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

AuctionTradeMessage::AuctionTradeMessage(std::chrono::nanoseconds time_offset, std::uint64_t auction_id, std::uint64_t execution_id, Decimal price, std::uint32_t quantity)
  : time_offset_(time_offset), auction_id_(auction_id), execution_id_(execution_id), price_(price), quantity_(quantity) {}

std::chrono::nanoseconds AuctionTradeMessage::time_offset() const { return time_offset_; }
void AuctionTradeMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AuctionTradeMessage::auction_id() const { return auction_id_; }
void AuctionTradeMessage::set_auction_id(std::uint64_t value) { auction_id_ = value; }

std::uint64_t AuctionTradeMessage::execution_id() const { return execution_id_; }
void AuctionTradeMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

Decimal AuctionTradeMessage::price() const { return price_; }
void AuctionTradeMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t AuctionTradeMessage::quantity() const { return quantity_; }
void AuctionTradeMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

MessageCode AuctionTradeMessage::type() const { return message_type; }

std::string_view AuctionTradeMessage::name() const { return "Auction Trade Message"; }

std::size_t AuctionTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionTradeMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    auction_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t AuctionTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(auction_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    return offset;
}

std::size_t AuctionTradeMessage::encoded_size() const {
    return wire_size;
}

void AuctionTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionTradeMessage::clone() const {
    return std::make_unique<AuctionTradeMessage>(*this);
}

void AuctionTradeMessage::print(std::ostream& out) const {
    out << "AuctionTradeMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", auction_id=";
    out << auction_id_;
    out << ", execution_id=";
    out << execution_id_;
    out << ", price=";
    out << price_;
    out << ", quantity=";
    out << quantity_;
    out << '}';
}

bool AuctionTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionTradeMessage::operator==(const AuctionTradeMessage& other) const {
    return time_offset_ == other.time_offset_
        && auction_id_ == other.auction_id_
        && execution_id_ == other.execution_id_
        && price_ == other.price_
        && quantity_ == other.quantity_;
}

bool AuctionTradeMessage::operator!=(const AuctionTradeMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
