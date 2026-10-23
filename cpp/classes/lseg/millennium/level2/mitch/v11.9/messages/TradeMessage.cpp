#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

TradeMessage::TradeMessage(std::uint32_t nanosecond, std::uint32_t executed_quantity, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, std::uint64_t trade_match_id, std::optional<CrossType> cross_type, SubBook sub_book, const PtModFlags& pt_mod_flags)
  : nanosecond_(nanosecond), executed_quantity_(executed_quantity), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), price_(price), trade_match_id_(trade_match_id), cross_type_(cross_type), sub_book_(sub_book), pt_mod_flags_(pt_mod_flags) {}

std::uint32_t TradeMessage::nanosecond() const { return nanosecond_; }
void TradeMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint32_t TradeMessage::executed_quantity() const { return executed_quantity_; }
void TradeMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

std::uint32_t TradeMessage::instrument_id() const { return instrument_id_; }
void TradeMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& TradeMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& TradeMessage::reserved_a() { return reserved_a_; }
void TradeMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& TradeMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& TradeMessage::reserved_b() { return reserved_b_; }
void TradeMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

std::int64_t TradeMessage::price() const { return price_; }
void TradeMessage::set_price(std::int64_t value) { price_ = value; }

std::uint64_t TradeMessage::trade_match_id() const { return trade_match_id_; }
void TradeMessage::set_trade_match_id(std::uint64_t value) { trade_match_id_ = value; }

std::optional<CrossType> TradeMessage::cross_type() const { return cross_type_; }
void TradeMessage::set_cross_type(std::optional<CrossType> value) { cross_type_ = value; }

SubBook TradeMessage::sub_book() const { return sub_book_; }
void TradeMessage::set_sub_book(SubBook value) { sub_book_ = value; }

const PtModFlags& TradeMessage::pt_mod_flags() const { return pt_mod_flags_; }
PtModFlags& TradeMessage::pt_mod_flags() { return pt_mod_flags_; }
void TradeMessage::set_pt_mod_flags(const PtModFlags& value) { pt_mod_flags_ = value; }

MessageCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    executed_quantity_ = wire::read_u32_le(data + offset);
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

    cross_type_ = wire::nullable_enum<CrossType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    sub_book_ = static_cast<SubBook>(wire::read_u8(data + offset));
    offset += 1;

    offset += pt_mod_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(executed_quantity_));
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

    wire::write_u8(data + offset, cross_type_ ? static_cast<std::uint8_t>(*cross_type_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sub_book_));
    offset += 1;

    offset += pt_mod_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t TradeMessage::encoded_size() const {
    return wire_size;
}

void TradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "nanosecond=";
    out << nanosecond_;
    out << ", executed_quantity=";
    out << executed_quantity_;
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
    out << ", cross_type=";
    print::optional(out, cross_type_);
    out << ", sub_book=";
    out << sub_book_;
    out << ", pt_mod_flags=";
    pt_mod_flags_.print(out);
    out << '}';
}

bool TradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && executed_quantity_ == other.executed_quantity_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && price_ == other.price_
        && trade_match_id_ == other.trade_match_id_
        && cross_type_ == other.cross_type_
        && sub_book_ == other.sub_book_
        && pt_mod_flags_ == other.pt_mod_flags_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
