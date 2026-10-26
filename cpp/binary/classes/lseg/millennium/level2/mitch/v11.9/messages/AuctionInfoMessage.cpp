#include "AuctionInfoMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

AuctionInfoMessage::AuctionInfoMessage(std::uint32_t nanosecond, std::uint32_t paired_quantity, const std::array<std::byte, 4>& reserved_4, const std::array<std::byte, 1>& reserved_1, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, AuctionType auction_type)
  : nanosecond_(nanosecond), paired_quantity_(paired_quantity), reserved_4_(reserved_4), reserved_1_(reserved_1), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), price_(price), auction_type_(auction_type) {}

std::uint32_t AuctionInfoMessage::nanosecond() const { return nanosecond_; }
void AuctionInfoMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint32_t AuctionInfoMessage::paired_quantity() const { return paired_quantity_; }
void AuctionInfoMessage::set_paired_quantity(std::uint32_t value) { paired_quantity_ = value; }

const std::array<std::byte, 4>& AuctionInfoMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& AuctionInfoMessage::reserved_4() { return reserved_4_; }
void AuctionInfoMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

const std::array<std::byte, 1>& AuctionInfoMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& AuctionInfoMessage::reserved_1() { return reserved_1_; }
void AuctionInfoMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

std::uint32_t AuctionInfoMessage::instrument_id() const { return instrument_id_; }
void AuctionInfoMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& AuctionInfoMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& AuctionInfoMessage::reserved_a() { return reserved_a_; }
void AuctionInfoMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& AuctionInfoMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& AuctionInfoMessage::reserved_b() { return reserved_b_; }
void AuctionInfoMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

std::int64_t AuctionInfoMessage::price() const { return price_; }
void AuctionInfoMessage::set_price(std::int64_t value) { price_ = value; }

AuctionType AuctionInfoMessage::auction_type() const { return auction_type_; }
void AuctionInfoMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

MessageCode AuctionInfoMessage::type() const { return message_type; }

std::string_view AuctionInfoMessage::name() const { return "Auction Info Message"; }

std::size_t AuctionInfoMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionInfoMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    paired_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    price_ = wire::read_i64_le(data + offset);
    offset += 8;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t AuctionInfoMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionInfoMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(paired_quantity_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    return offset;
}

std::size_t AuctionInfoMessage::encoded_size() const {
    return wire_size;
}

void AuctionInfoMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionInfoMessage::clone() const {
    return std::make_unique<AuctionInfoMessage>(*this);
}

void AuctionInfoMessage::print(std::ostream& out) const {
    out << "AuctionInfoMessage{";
    out << "nanosecond=";
    out << nanosecond_;
    out << ", paired_quantity=";
    out << paired_quantity_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", reserved_a=";
    print::hex(out, reserved_a_.data(), reserved_a_.size());
    out << ", reserved_b=";
    print::hex(out, reserved_b_.data(), reserved_b_.size());
    out << ", price=";
    out << price_;
    out << ", auction_type=";
    out << auction_type_;
    out << '}';
}

bool AuctionInfoMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionInfoMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionInfoMessage::operator==(const AuctionInfoMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && paired_quantity_ == other.paired_quantity_
        && reserved_4_ == other.reserved_4_
        && reserved_1_ == other.reserved_1_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && price_ == other.price_
        && auction_type_ == other.auction_type_;
}

bool AuctionInfoMessage::operator!=(const AuctionInfoMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
