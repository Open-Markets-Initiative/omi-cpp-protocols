#include "AuctionSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

AuctionSummaryMessage::AuctionSummaryMessage(std::chrono::nanoseconds time_offset, const std::string& stock_symbol, AuctionType auction_type, std::uint64_t price_binary_8, std::uint32_t shares)
  : time_offset_(time_offset), stock_symbol_(stock_symbol), auction_type_(auction_type), price_binary_8_(price_binary_8), shares_(shares) {}

std::chrono::nanoseconds AuctionSummaryMessage::time_offset() const { return time_offset_; }
void AuctionSummaryMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& AuctionSummaryMessage::stock_symbol() const { return stock_symbol_; }
std::string& AuctionSummaryMessage::stock_symbol() { return stock_symbol_; }
void AuctionSummaryMessage::set_stock_symbol(const std::string& value) { stock_symbol_ = value; }

AuctionType AuctionSummaryMessage::auction_type() const { return auction_type_; }
void AuctionSummaryMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

std::uint64_t AuctionSummaryMessage::price_binary_8() const { return price_binary_8_; }
void AuctionSummaryMessage::set_price_binary_8(std::uint64_t value) { price_binary_8_ = value; }

std::uint32_t AuctionSummaryMessage::shares() const { return shares_; }
void AuctionSummaryMessage::set_shares(std::uint32_t value) { shares_ = value; }

MessageCode AuctionSummaryMessage::type() const { return message_type; }

std::string_view AuctionSummaryMessage::name() const { return "Auction Summary Message"; }

std::size_t AuctionSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionSummaryMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    stock_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    price_binary_8_ = wire::read_u64_le(data + offset);
    offset += 8;

    shares_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t AuctionSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionSummaryMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', stock_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_binary_8_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(shares_));
    offset += 4;

    return offset;
}

std::size_t AuctionSummaryMessage::encoded_size() const {
    return wire_size;
}

void AuctionSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionSummaryMessage::clone() const {
    return std::make_unique<AuctionSummaryMessage>(*this);
}

void AuctionSummaryMessage::print(std::ostream& out) const {
    out << "AuctionSummaryMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", stock_symbol=";
    print::text(out, stock_symbol_);
    out << ", auction_type=";
    out << auction_type_;
    out << ", price_binary_8=";
    out << price_binary_8_;
    out << ", shares=";
    out << shares_;
    out << '}';
}

bool AuctionSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionSummaryMessage::operator==(const AuctionSummaryMessage& other) const {
    return time_offset_ == other.time_offset_
        && stock_symbol_ == other.stock_symbol_
        && auction_type_ == other.auction_type_
        && price_binary_8_ == other.price_binary_8_
        && shares_ == other.shares_;
}

bool AuctionSummaryMessage::operator!=(const AuctionSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
