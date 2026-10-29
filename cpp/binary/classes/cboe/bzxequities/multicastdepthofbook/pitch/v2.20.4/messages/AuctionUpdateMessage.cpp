#include "AuctionUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

AuctionUpdateMessage::AuctionUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& stock_symbol, AuctionType auction_type, std::uint64_t reference_price, std::uint32_t buy_shares, std::uint32_t sell_shares, std::uint64_t indicative_price, std::uint64_t auction_only_price)
  : time_offset_(time_offset), stock_symbol_(stock_symbol), auction_type_(auction_type), reference_price_(reference_price), buy_shares_(buy_shares), sell_shares_(sell_shares), indicative_price_(indicative_price), auction_only_price_(auction_only_price) {}

std::chrono::nanoseconds AuctionUpdateMessage::time_offset() const { return time_offset_; }
void AuctionUpdateMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& AuctionUpdateMessage::stock_symbol() const { return stock_symbol_; }
std::string& AuctionUpdateMessage::stock_symbol() { return stock_symbol_; }
void AuctionUpdateMessage::set_stock_symbol(const std::string& value) { stock_symbol_ = value; }

AuctionType AuctionUpdateMessage::auction_type() const { return auction_type_; }
void AuctionUpdateMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

std::uint64_t AuctionUpdateMessage::reference_price() const { return reference_price_; }
void AuctionUpdateMessage::set_reference_price(std::uint64_t value) { reference_price_ = value; }

std::uint32_t AuctionUpdateMessage::buy_shares() const { return buy_shares_; }
void AuctionUpdateMessage::set_buy_shares(std::uint32_t value) { buy_shares_ = value; }

std::uint32_t AuctionUpdateMessage::sell_shares() const { return sell_shares_; }
void AuctionUpdateMessage::set_sell_shares(std::uint32_t value) { sell_shares_ = value; }

std::uint64_t AuctionUpdateMessage::indicative_price() const { return indicative_price_; }
void AuctionUpdateMessage::set_indicative_price(std::uint64_t value) { indicative_price_ = value; }

std::uint64_t AuctionUpdateMessage::auction_only_price() const { return auction_only_price_; }
void AuctionUpdateMessage::set_auction_only_price(std::uint64_t value) { auction_only_price_ = value; }

MessageCode AuctionUpdateMessage::type() const { return message_type; }

std::string_view AuctionUpdateMessage::name() const { return "Auction Update Message"; }

std::size_t AuctionUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionUpdateMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    stock_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    reference_price_ = wire::read_u64_le(data + offset);
    offset += 8;

    buy_shares_ = wire::read_u32_le(data + offset);
    offset += 4;

    sell_shares_ = wire::read_u32_le(data + offset);
    offset += 4;

    indicative_price_ = wire::read_u64_le(data + offset);
    offset += 8;

    auction_only_price_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t AuctionUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionUpdateMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', stock_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(reference_price_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(buy_shares_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sell_shares_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(indicative_price_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(auction_only_price_));
    offset += 8;

    return offset;
}

std::size_t AuctionUpdateMessage::encoded_size() const {
    return wire_size;
}

void AuctionUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionUpdateMessage::clone() const {
    return std::make_unique<AuctionUpdateMessage>(*this);
}

void AuctionUpdateMessage::print(std::ostream& out) const {
    out << "AuctionUpdateMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", stock_symbol=";
    print::text(out, stock_symbol_);
    out << ", auction_type=";
    out << auction_type_;
    out << ", reference_price=";
    out << reference_price_;
    out << ", buy_shares=";
    out << buy_shares_;
    out << ", sell_shares=";
    out << sell_shares_;
    out << ", indicative_price=";
    out << indicative_price_;
    out << ", auction_only_price=";
    out << auction_only_price_;
    out << '}';
}

bool AuctionUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionUpdateMessage::operator==(const AuctionUpdateMessage& other) const {
    return time_offset_ == other.time_offset_
        && stock_symbol_ == other.stock_symbol_
        && auction_type_ == other.auction_type_
        && reference_price_ == other.reference_price_
        && buy_shares_ == other.buy_shares_
        && sell_shares_ == other.sell_shares_
        && indicative_price_ == other.indicative_price_
        && auction_only_price_ == other.auction_only_price_;
}

bool AuctionUpdateMessage::operator!=(const AuctionUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
