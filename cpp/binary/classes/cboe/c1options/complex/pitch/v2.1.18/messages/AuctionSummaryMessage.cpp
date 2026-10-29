#include "AuctionSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

AuctionSummaryMessage::AuctionSummaryMessage(std::chrono::nanoseconds time_offset, const std::string& complex_instrument_id_8, AuctionOpeningType auction_opening_type, Decimal price, std::uint32_t quantity)
  : time_offset_(time_offset), complex_instrument_id_8_(complex_instrument_id_8), auction_opening_type_(auction_opening_type), price_(price), quantity_(quantity) {}

std::chrono::nanoseconds AuctionSummaryMessage::time_offset() const { return time_offset_; }
void AuctionSummaryMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& AuctionSummaryMessage::complex_instrument_id_8() const { return complex_instrument_id_8_; }
std::string& AuctionSummaryMessage::complex_instrument_id_8() { return complex_instrument_id_8_; }
void AuctionSummaryMessage::set_complex_instrument_id_8(const std::string& value) { complex_instrument_id_8_ = value; }

AuctionOpeningType AuctionSummaryMessage::auction_opening_type() const { return auction_opening_type_; }
void AuctionSummaryMessage::set_auction_opening_type(AuctionOpeningType value) { auction_opening_type_ = value; }

Decimal AuctionSummaryMessage::price() const { return price_; }
void AuctionSummaryMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t AuctionSummaryMessage::quantity() const { return quantity_; }
void AuctionSummaryMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

MessageCode AuctionSummaryMessage::type() const { return message_type; }

std::string_view AuctionSummaryMessage::name() const { return "Auction Summary Message"; }

std::size_t AuctionSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionSummaryMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    complex_instrument_id_8_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    auction_opening_type_ = static_cast<AuctionOpeningType>(wire::read_char(data + offset));
    offset += 1;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t AuctionSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionSummaryMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', complex_instrument_id_8_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_opening_type_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_));
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
    out << ", complex_instrument_id_8=";
    print::text(out, complex_instrument_id_8_);
    out << ", auction_opening_type=";
    out << auction_opening_type_;
    out << ", price=";
    out << price_;
    out << ", quantity=";
    out << quantity_;
    out << '}';
}

bool AuctionSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionSummaryMessage::operator==(const AuctionSummaryMessage& other) const {
    return time_offset_ == other.time_offset_
        && complex_instrument_id_8_ == other.complex_instrument_id_8_
        && auction_opening_type_ == other.auction_opening_type_
        && price_ == other.price_
        && quantity_ == other.quantity_;
}

bool AuctionSummaryMessage::operator!=(const AuctionSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
