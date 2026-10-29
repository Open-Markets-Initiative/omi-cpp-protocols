#include "AuctionUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

AuctionUpdateMessage::AuctionUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& complex_instrument_id_8, AuctionOpeningType auction_opening_type, Decimal reference_price, std::uint32_t buy_contracts, std::uint32_t sell_contracts, Decimal indicative_price, Decimal auction_only_price, char opening_condition, Decimal composite_market_bid_price, Decimal composite_market_offer_price)
  : time_offset_(time_offset), complex_instrument_id_8_(complex_instrument_id_8), auction_opening_type_(auction_opening_type), reference_price_(reference_price), buy_contracts_(buy_contracts), sell_contracts_(sell_contracts), indicative_price_(indicative_price), auction_only_price_(auction_only_price), opening_condition_(opening_condition), composite_market_bid_price_(composite_market_bid_price), composite_market_offer_price_(composite_market_offer_price) {}

std::chrono::nanoseconds AuctionUpdateMessage::time_offset() const { return time_offset_; }
void AuctionUpdateMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& AuctionUpdateMessage::complex_instrument_id_8() const { return complex_instrument_id_8_; }
std::string& AuctionUpdateMessage::complex_instrument_id_8() { return complex_instrument_id_8_; }
void AuctionUpdateMessage::set_complex_instrument_id_8(const std::string& value) { complex_instrument_id_8_ = value; }

AuctionOpeningType AuctionUpdateMessage::auction_opening_type() const { return auction_opening_type_; }
void AuctionUpdateMessage::set_auction_opening_type(AuctionOpeningType value) { auction_opening_type_ = value; }

Decimal AuctionUpdateMessage::reference_price() const { return reference_price_; }
void AuctionUpdateMessage::set_reference_price(Decimal value) { reference_price_ = value; }

std::uint32_t AuctionUpdateMessage::buy_contracts() const { return buy_contracts_; }
void AuctionUpdateMessage::set_buy_contracts(std::uint32_t value) { buy_contracts_ = value; }

std::uint32_t AuctionUpdateMessage::sell_contracts() const { return sell_contracts_; }
void AuctionUpdateMessage::set_sell_contracts(std::uint32_t value) { sell_contracts_ = value; }

Decimal AuctionUpdateMessage::indicative_price() const { return indicative_price_; }
void AuctionUpdateMessage::set_indicative_price(Decimal value) { indicative_price_ = value; }

Decimal AuctionUpdateMessage::auction_only_price() const { return auction_only_price_; }
void AuctionUpdateMessage::set_auction_only_price(Decimal value) { auction_only_price_ = value; }

char AuctionUpdateMessage::opening_condition() const { return opening_condition_; }
void AuctionUpdateMessage::set_opening_condition(char value) { opening_condition_ = value; }

Decimal AuctionUpdateMessage::composite_market_bid_price() const { return composite_market_bid_price_; }
void AuctionUpdateMessage::set_composite_market_bid_price(Decimal value) { composite_market_bid_price_ = value; }

Decimal AuctionUpdateMessage::composite_market_offer_price() const { return composite_market_offer_price_; }
void AuctionUpdateMessage::set_composite_market_offer_price(Decimal value) { composite_market_offer_price_ = value; }

MessageCode AuctionUpdateMessage::type() const { return message_type; }

std::string_view AuctionUpdateMessage::name() const { return "Auction Update Message"; }

std::size_t AuctionUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionUpdateMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    complex_instrument_id_8_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    auction_opening_type_ = static_cast<AuctionOpeningType>(wire::read_char(data + offset));
    offset += 1;

    reference_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    buy_contracts_ = wire::read_u32_le(data + offset);
    offset += 4;

    sell_contracts_ = wire::read_u32_le(data + offset);
    offset += 4;

    indicative_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    auction_only_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    opening_condition_ = wire::read_char(data + offset);
    offset += 1;

    composite_market_bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    composite_market_offer_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t AuctionUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionUpdateMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', complex_instrument_id_8_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_opening_type_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(reference_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(buy_contracts_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(sell_contracts_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(indicative_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(auction_only_price_.mantissa()));
    offset += 8;

    wire::write_char(data + offset, opening_condition_);
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(composite_market_bid_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(composite_market_offer_price_.mantissa()));
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
    out << ", complex_instrument_id_8=";
    print::text(out, complex_instrument_id_8_);
    out << ", auction_opening_type=";
    out << auction_opening_type_;
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
    print::character(out, opening_condition_);
    out << ", composite_market_bid_price=";
    out << composite_market_bid_price_;
    out << ", composite_market_offer_price=";
    out << composite_market_offer_price_;
    out << '}';
}

bool AuctionUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionUpdateMessage::operator==(const AuctionUpdateMessage& other) const {
    return time_offset_ == other.time_offset_
        && complex_instrument_id_8_ == other.complex_instrument_id_8_
        && auction_opening_type_ == other.auction_opening_type_
        && reference_price_ == other.reference_price_
        && buy_contracts_ == other.buy_contracts_
        && sell_contracts_ == other.sell_contracts_
        && indicative_price_ == other.indicative_price_
        && auction_only_price_ == other.auction_only_price_
        && opening_condition_ == other.opening_condition_
        && composite_market_bid_price_ == other.composite_market_bid_price_
        && composite_market_offer_price_ == other.composite_market_offer_price_;
}

bool AuctionUpdateMessage::operator!=(const AuctionUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
