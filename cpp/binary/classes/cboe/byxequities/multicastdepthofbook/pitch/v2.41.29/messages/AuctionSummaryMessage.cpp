#include "AuctionSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

AuctionSummaryMessage::AuctionSummaryMessage(std::chrono::nanoseconds time_offset, const std::string& symbol_long, char auction_opening_type, Decimal price, std::uint32_t shares_contracts)
  : time_offset_(time_offset), symbol_long_(symbol_long), auction_opening_type_(auction_opening_type), price_(price), shares_contracts_(shares_contracts) {}

std::chrono::nanoseconds AuctionSummaryMessage::time_offset() const { return time_offset_; }
void AuctionSummaryMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& AuctionSummaryMessage::symbol_long() const { return symbol_long_; }
std::string& AuctionSummaryMessage::symbol_long() { return symbol_long_; }
void AuctionSummaryMessage::set_symbol_long(const std::string& value) { symbol_long_ = value; }

char AuctionSummaryMessage::auction_opening_type() const { return auction_opening_type_; }
void AuctionSummaryMessage::set_auction_opening_type(char value) { auction_opening_type_ = value; }

Decimal AuctionSummaryMessage::price() const { return price_; }
void AuctionSummaryMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t AuctionSummaryMessage::shares_contracts() const { return shares_contracts_; }
void AuctionSummaryMessage::set_shares_contracts(std::uint32_t value) { shares_contracts_ = value; }

MessageCode AuctionSummaryMessage::type() const { return message_type; }

std::string_view AuctionSummaryMessage::name() const { return "Auction Summary Message"; }

std::size_t AuctionSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionSummaryMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_long_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    auction_opening_type_ = wire::read_char(data + offset);
    offset += 1;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    shares_contracts_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t AuctionSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionSummaryMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', symbol_long_);
    offset += 8;

    wire::write_char(data + offset, auction_opening_type_);
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(shares_contracts_));
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
    out << ", symbol_long=";
    print::text(out, symbol_long_);
    out << ", auction_opening_type=";
    print::character(out, auction_opening_type_);
    out << ", price=";
    out << price_;
    out << ", shares_contracts=";
    out << shares_contracts_;
    out << '}';
}

bool AuctionSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionSummaryMessage::operator==(const AuctionSummaryMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_long_ == other.symbol_long_
        && auction_opening_type_ == other.auction_opening_type_
        && price_ == other.price_
        && shares_contracts_ == other.shares_contracts_;
}

bool AuctionSummaryMessage::operator!=(const AuctionSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
