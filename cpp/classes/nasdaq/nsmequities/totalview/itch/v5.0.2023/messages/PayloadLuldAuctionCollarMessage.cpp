#include "PayloadLuldAuctionCollarMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadLuldAuctionCollarMessage::PayloadLuldAuctionCollarMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, Decimal auction_collar_reference_price, Decimal upper_auction_collar_price, Decimal lower_auction_collar_price, std::uint32_t auction_collar_extension)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), auction_collar_reference_price_(auction_collar_reference_price), upper_auction_collar_price_(upper_auction_collar_price), lower_auction_collar_price_(lower_auction_collar_price), auction_collar_extension_(auction_collar_extension) {}

std::uint16_t PayloadLuldAuctionCollarMessage::stock_locate() const { return stock_locate_; }
void PayloadLuldAuctionCollarMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadLuldAuctionCollarMessage::tracking_number() const { return tracking_number_; }
void PayloadLuldAuctionCollarMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadLuldAuctionCollarMessage::timestamp() const { return timestamp_; }
void PayloadLuldAuctionCollarMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& PayloadLuldAuctionCollarMessage::stock() const { return stock_; }
std::string& PayloadLuldAuctionCollarMessage::stock() { return stock_; }
void PayloadLuldAuctionCollarMessage::set_stock(const std::string& value) { stock_ = value; }

Decimal PayloadLuldAuctionCollarMessage::auction_collar_reference_price() const { return auction_collar_reference_price_; }
void PayloadLuldAuctionCollarMessage::set_auction_collar_reference_price(Decimal value) { auction_collar_reference_price_ = value; }

Decimal PayloadLuldAuctionCollarMessage::upper_auction_collar_price() const { return upper_auction_collar_price_; }
void PayloadLuldAuctionCollarMessage::set_upper_auction_collar_price(Decimal value) { upper_auction_collar_price_ = value; }

Decimal PayloadLuldAuctionCollarMessage::lower_auction_collar_price() const { return lower_auction_collar_price_; }
void PayloadLuldAuctionCollarMessage::set_lower_auction_collar_price(Decimal value) { lower_auction_collar_price_ = value; }

std::uint32_t PayloadLuldAuctionCollarMessage::auction_collar_extension() const { return auction_collar_extension_; }
void PayloadLuldAuctionCollarMessage::set_auction_collar_extension(std::uint32_t value) { auction_collar_extension_ = value; }

PacketMessageCode PayloadLuldAuctionCollarMessage::type() const { return message_type; }

std::string_view PayloadLuldAuctionCollarMessage::name() const { return "Luld Auction Collar Message"; }

std::size_t PayloadLuldAuctionCollarMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadLuldAuctionCollarMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    auction_collar_reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    upper_auction_collar_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    lower_auction_collar_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    auction_collar_extension_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t PayloadLuldAuctionCollarMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadLuldAuctionCollarMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(auction_collar_reference_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(upper_auction_collar_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(lower_auction_collar_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(auction_collar_extension_));
    offset += 4;

    return offset;
}

std::size_t PayloadLuldAuctionCollarMessage::encoded_size() const {
    return wire_size;
}

void PayloadLuldAuctionCollarMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadLuldAuctionCollarMessage::clone() const {
    return std::make_unique<PayloadLuldAuctionCollarMessage>(*this);
}

void PayloadLuldAuctionCollarMessage::print(std::ostream& out) const {
    out << "PayloadLuldAuctionCollarMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", auction_collar_reference_price=";
    out << auction_collar_reference_price_;
    out << ", upper_auction_collar_price=";
    out << upper_auction_collar_price_;
    out << ", lower_auction_collar_price=";
    out << lower_auction_collar_price_;
    out << ", auction_collar_extension=";
    out << auction_collar_extension_;
    out << '}';
}

bool PayloadLuldAuctionCollarMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadLuldAuctionCollarMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadLuldAuctionCollarMessage::operator==(const PayloadLuldAuctionCollarMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && auction_collar_reference_price_ == other.auction_collar_reference_price_
        && upper_auction_collar_price_ == other.upper_auction_collar_price_
        && lower_auction_collar_price_ == other.lower_auction_collar_price_
        && auction_collar_extension_ == other.auction_collar_extension_;
}

bool PayloadLuldAuctionCollarMessage::operator!=(const PayloadLuldAuctionCollarMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
