#include "OptionsAuctionUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

OptionsAuctionUpdateMessage::OptionsAuctionUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& expanded_symbol, AuctionType auction_type, Decimal reference_price, std::uint32_t buy_contracts, std::uint32_t sell_contracts, Decimal indicative_price, Decimal auction_only_price, OpeningCondition opening_condition, Decimal composite_market_bid_price, Decimal composite_market_offer_price)
  : time_offset_(time_offset), expanded_symbol_(expanded_symbol), auction_type_(auction_type), reference_price_(reference_price), buy_contracts_(buy_contracts), sell_contracts_(sell_contracts), indicative_price_(indicative_price), auction_only_price_(auction_only_price), opening_condition_(opening_condition), composite_market_bid_price_(composite_market_bid_price), composite_market_offer_price_(composite_market_offer_price) {}

std::chrono::nanoseconds OptionsAuctionUpdateMessage::time_offset() const { return time_offset_; }
void OptionsAuctionUpdateMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& OptionsAuctionUpdateMessage::expanded_symbol() const { return expanded_symbol_; }
std::string& OptionsAuctionUpdateMessage::expanded_symbol() { return expanded_symbol_; }
void OptionsAuctionUpdateMessage::set_expanded_symbol(const std::string& value) { expanded_symbol_ = value; }

AuctionType OptionsAuctionUpdateMessage::auction_type() const { return auction_type_; }
void OptionsAuctionUpdateMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

Decimal OptionsAuctionUpdateMessage::reference_price() const { return reference_price_; }
void OptionsAuctionUpdateMessage::set_reference_price(Decimal value) { reference_price_ = value; }

std::uint32_t OptionsAuctionUpdateMessage::buy_contracts() const { return buy_contracts_; }
void OptionsAuctionUpdateMessage::set_buy_contracts(std::uint32_t value) { buy_contracts_ = value; }

std::uint32_t OptionsAuctionUpdateMessage::sell_contracts() const { return sell_contracts_; }
void OptionsAuctionUpdateMessage::set_sell_contracts(std::uint32_t value) { sell_contracts_ = value; }

Decimal OptionsAuctionUpdateMessage::indicative_price() const { return indicative_price_; }
void OptionsAuctionUpdateMessage::set_indicative_price(Decimal value) { indicative_price_ = value; }

Decimal OptionsAuctionUpdateMessage::auction_only_price() const { return auction_only_price_; }
void OptionsAuctionUpdateMessage::set_auction_only_price(Decimal value) { auction_only_price_ = value; }

OpeningCondition OptionsAuctionUpdateMessage::opening_condition() const { return opening_condition_; }
void OptionsAuctionUpdateMessage::set_opening_condition(OpeningCondition value) { opening_condition_ = value; }

Decimal OptionsAuctionUpdateMessage::composite_market_bid_price() const { return composite_market_bid_price_; }
void OptionsAuctionUpdateMessage::set_composite_market_bid_price(Decimal value) { composite_market_bid_price_ = value; }

Decimal OptionsAuctionUpdateMessage::composite_market_offer_price() const { return composite_market_offer_price_; }
void OptionsAuctionUpdateMessage::set_composite_market_offer_price(Decimal value) { composite_market_offer_price_ = value; }

MessageCode OptionsAuctionUpdateMessage::type() const { return message_type; }

std::string_view OptionsAuctionUpdateMessage::name() const { return "Options Auction Update Message"; }

std::size_t OptionsAuctionUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsAuctionUpdateMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    expanded_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    buy_contracts_ = wire::read_u32_le(data + offset);
    offset += 4;

    sell_contracts_ = wire::read_u32_le(data + offset);
    offset += 4;

    indicative_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    auction_only_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    opening_condition_ = static_cast<OpeningCondition>(wire::read_char(data + offset));
    offset += 1;

    composite_market_bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    composite_market_offer_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t OptionsAuctionUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsAuctionUpdateMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', expanded_symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(reference_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(buy_contracts_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sell_contracts_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(indicative_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(auction_only_price_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(opening_condition_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(composite_market_bid_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(composite_market_offer_price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t OptionsAuctionUpdateMessage::encoded_size() const {
    return wire_size;
}

void OptionsAuctionUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsAuctionUpdateMessage::clone() const {
    return std::make_unique<OptionsAuctionUpdateMessage>(*this);
}

void OptionsAuctionUpdateMessage::print(std::ostream& out) const {
    out << "OptionsAuctionUpdateMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", expanded_symbol=";
    print::text(out, expanded_symbol_);
    out << ", auction_type=";
    out << auction_type_;
    out << ", reference_price=";
    out << reference_price_;
    out << ", buy_contracts=";
    out << buy_contracts_;
    out << ", sell_contracts=";
    out << sell_contracts_;
    out << ", indicative_price=";
    out << indicative_price_;
    out << ", auction_only_price=";
    out << auction_only_price_;
    out << ", opening_condition=";
    out << opening_condition_;
    out << ", composite_market_bid_price=";
    out << composite_market_bid_price_;
    out << ", composite_market_offer_price=";
    out << composite_market_offer_price_;
    out << '}';
}

bool OptionsAuctionUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsAuctionUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsAuctionUpdateMessage::operator==(const OptionsAuctionUpdateMessage& other) const {
    return time_offset_ == other.time_offset_
        && expanded_symbol_ == other.expanded_symbol_
        && auction_type_ == other.auction_type_
        && reference_price_ == other.reference_price_
        && buy_contracts_ == other.buy_contracts_
        && sell_contracts_ == other.sell_contracts_
        && indicative_price_ == other.indicative_price_
        && auction_only_price_ == other.auction_only_price_
        && opening_condition_ == other.opening_condition_
        && composite_market_bid_price_ == other.composite_market_bid_price_
        && composite_market_offer_price_ == other.composite_market_offer_price_;
}

bool OptionsAuctionUpdateMessage::operator!=(const OptionsAuctionUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
