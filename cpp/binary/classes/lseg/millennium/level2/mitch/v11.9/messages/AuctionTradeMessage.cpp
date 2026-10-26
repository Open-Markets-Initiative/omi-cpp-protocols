#include "AuctionTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

AuctionTradeMessage::AuctionTradeMessage(std::uint32_t nanosecond, std::uint32_t quantity, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, std::uint64_t trade_match_id, AuctionType auction_type, const PtModFlags& pt_mod_flags)
  : nanosecond_(nanosecond), quantity_(quantity), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), price_(price), trade_match_id_(trade_match_id), auction_type_(auction_type), pt_mod_flags_(pt_mod_flags) {}

std::uint32_t AuctionTradeMessage::nanosecond() const { return nanosecond_; }
void AuctionTradeMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint32_t AuctionTradeMessage::quantity() const { return quantity_; }
void AuctionTradeMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t AuctionTradeMessage::instrument_id() const { return instrument_id_; }
void AuctionTradeMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& AuctionTradeMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& AuctionTradeMessage::reserved_a() { return reserved_a_; }
void AuctionTradeMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& AuctionTradeMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& AuctionTradeMessage::reserved_b() { return reserved_b_; }
void AuctionTradeMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

std::int64_t AuctionTradeMessage::price() const { return price_; }
void AuctionTradeMessage::set_price(std::int64_t value) { price_ = value; }

std::uint64_t AuctionTradeMessage::trade_match_id() const { return trade_match_id_; }
void AuctionTradeMessage::set_trade_match_id(std::uint64_t value) { trade_match_id_ = value; }

AuctionType AuctionTradeMessage::auction_type() const { return auction_type_; }
void AuctionTradeMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

const PtModFlags& AuctionTradeMessage::pt_mod_flags() const { return pt_mod_flags_; }
PtModFlags& AuctionTradeMessage::pt_mod_flags() { return pt_mod_flags_; }
void AuctionTradeMessage::set_pt_mod_flags(const PtModFlags& value) { pt_mod_flags_ = value; }

MessageCode AuctionTradeMessage::type() const { return message_type; }

std::string_view AuctionTradeMessage::name() const { return "Auction Trade Message"; }

std::size_t AuctionTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionTradeMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    price_ = wire::read_i64_le(data + offset);
    offset += 8;

    trade_match_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    offset += pt_mod_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t AuctionTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_match_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    offset += pt_mod_flags_.encode(data + offset, capacity - offset);

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
    out << "nanosecond=";
    out << nanosecond_;
    out << ", quantity=";
    out << quantity_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", reserved_a=";
    print::hex(out, reserved_a_.data(), reserved_a_.size());
    out << ", reserved_b=";
    print::hex(out, reserved_b_.data(), reserved_b_.size());
    out << ", price=";
    out << price_;
    out << ", trade_match_id=";
    out << trade_match_id_;
    out << ", auction_type=";
    out << auction_type_;
    out << ", pt_mod_flags=";
    pt_mod_flags_.print(out);
    out << '}';
}

bool AuctionTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionTradeMessage::operator==(const AuctionTradeMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && quantity_ == other.quantity_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && price_ == other.price_
        && trade_match_id_ == other.trade_match_id_
        && auction_type_ == other.auction_type_
        && pt_mod_flags_ == other.pt_mod_flags_;
}

bool AuctionTradeMessage::operator!=(const AuctionTradeMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
