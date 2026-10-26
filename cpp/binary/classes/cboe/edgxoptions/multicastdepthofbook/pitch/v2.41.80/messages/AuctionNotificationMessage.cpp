#include "AuctionNotificationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

AuctionNotificationMessage::AuctionNotificationMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, std::uint64_t auction_id, AuctionType auction_type, Side side, Decimal price_long, std::uint32_t contracts, CustomerIndicator customer_indicator, const std::string& participant_id, std::uint32_t auction_end_offset, const std::string& client_id)
  : time_offset_(time_offset), symbol_(symbol), auction_id_(auction_id), auction_type_(auction_type), side_(side), price_long_(price_long), contracts_(contracts), customer_indicator_(customer_indicator), participant_id_(participant_id), auction_end_offset_(auction_end_offset), client_id_(client_id) {}

std::chrono::nanoseconds AuctionNotificationMessage::time_offset() const { return time_offset_; }
void AuctionNotificationMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& AuctionNotificationMessage::symbol() const { return symbol_; }
std::string& AuctionNotificationMessage::symbol() { return symbol_; }
void AuctionNotificationMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t AuctionNotificationMessage::auction_id() const { return auction_id_; }
void AuctionNotificationMessage::set_auction_id(std::uint64_t value) { auction_id_ = value; }

AuctionType AuctionNotificationMessage::auction_type() const { return auction_type_; }
void AuctionNotificationMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

Side AuctionNotificationMessage::side() const { return side_; }
void AuctionNotificationMessage::set_side(Side value) { side_ = value; }

Decimal AuctionNotificationMessage::price_long() const { return price_long_; }
void AuctionNotificationMessage::set_price_long(Decimal value) { price_long_ = value; }

std::uint32_t AuctionNotificationMessage::contracts() const { return contracts_; }
void AuctionNotificationMessage::set_contracts(std::uint32_t value) { contracts_ = value; }

CustomerIndicator AuctionNotificationMessage::customer_indicator() const { return customer_indicator_; }
void AuctionNotificationMessage::set_customer_indicator(CustomerIndicator value) { customer_indicator_ = value; }

const std::string& AuctionNotificationMessage::participant_id() const { return participant_id_; }
std::string& AuctionNotificationMessage::participant_id() { return participant_id_; }
void AuctionNotificationMessage::set_participant_id(const std::string& value) { participant_id_ = value; }

std::uint32_t AuctionNotificationMessage::auction_end_offset() const { return auction_end_offset_; }
void AuctionNotificationMessage::set_auction_end_offset(std::uint32_t value) { auction_end_offset_ = value; }

const std::string& AuctionNotificationMessage::client_id() const { return client_id_; }
std::string& AuctionNotificationMessage::client_id() { return client_id_; }
void AuctionNotificationMessage::set_client_id(const std::string& value) { client_id_ = value; }

MessageCode AuctionNotificationMessage::type() const { return message_type; }

std::string_view AuctionNotificationMessage::name() const { return "Auction Notification Message"; }

std::size_t AuctionNotificationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionNotificationMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    auction_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    contracts_ = wire::read_u32_le(data + offset);
    offset += 4;

    customer_indicator_ = static_cast<CustomerIndicator>(wire::read_char(data + offset));
    offset += 1;

    participant_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    auction_end_offset_ = wire::read_u32_le(data + offset);
    offset += 4;

    client_id_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t AuctionNotificationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionNotificationMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(auction_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_long_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(contracts_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(customer_indicator_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', participant_id_);
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(auction_end_offset_));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', client_id_);
    offset += 4;

    return offset;
}

std::size_t AuctionNotificationMessage::encoded_size() const {
    return wire_size;
}

void AuctionNotificationMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionNotificationMessage::clone() const {
    return std::make_unique<AuctionNotificationMessage>(*this);
}

void AuctionNotificationMessage::print(std::ostream& out) const {
    out << "AuctionNotificationMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", auction_id=";
    out << auction_id_;
    out << ", auction_type=";
    out << auction_type_;
    out << ", side=";
    out << side_;
    out << ", price_long=";
    out << price_long_;
    out << ", contracts=";
    out << contracts_;
    out << ", customer_indicator=";
    out << customer_indicator_;
    out << ", participant_id=";
    print::text(out, participant_id_);
    out << ", auction_end_offset=";
    out << auction_end_offset_;
    out << ", client_id=";
    print::text(out, client_id_);
    out << '}';
}

bool AuctionNotificationMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionNotificationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionNotificationMessage::operator==(const AuctionNotificationMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_ == other.symbol_
        && auction_id_ == other.auction_id_
        && auction_type_ == other.auction_type_
        && side_ == other.side_
        && price_long_ == other.price_long_
        && contracts_ == other.contracts_
        && customer_indicator_ == other.customer_indicator_
        && participant_id_ == other.participant_id_
        && auction_end_offset_ == other.auction_end_offset_
        && client_id_ == other.client_id_;
}

bool AuctionNotificationMessage::operator!=(const AuctionNotificationMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
