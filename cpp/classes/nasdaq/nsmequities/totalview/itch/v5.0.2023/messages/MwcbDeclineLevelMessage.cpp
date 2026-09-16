#include "MwcbDeclineLevelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

MwcbDeclineLevelMessage::MwcbDeclineLevelMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, Decimal level_1, Decimal level_2, Decimal level_3)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), level_1_(level_1), level_2_(level_2), level_3_(level_3) {}

std::uint16_t MwcbDeclineLevelMessage::stock_locate() const { return stock_locate_; }
void MwcbDeclineLevelMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t MwcbDeclineLevelMessage::tracking_number() const { return tracking_number_; }
void MwcbDeclineLevelMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds MwcbDeclineLevelMessage::timestamp() const { return timestamp_; }
void MwcbDeclineLevelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

Decimal MwcbDeclineLevelMessage::level_1() const { return level_1_; }
void MwcbDeclineLevelMessage::set_level_1(Decimal value) { level_1_ = value; }

Decimal MwcbDeclineLevelMessage::level_2() const { return level_2_; }
void MwcbDeclineLevelMessage::set_level_2(Decimal value) { level_2_ = value; }

Decimal MwcbDeclineLevelMessage::level_3() const { return level_3_; }
void MwcbDeclineLevelMessage::set_level_3(Decimal value) { level_3_ = value; }

MessageCode MwcbDeclineLevelMessage::type() const { return message_type; }

std::string_view MwcbDeclineLevelMessage::name() const { return "Mwcb Decline Level Message"; }

std::size_t MwcbDeclineLevelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MwcbDeclineLevelMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    level_1_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -8);
    offset += 8;

    level_2_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -8);
    offset += 8;

    level_3_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -8);
    offset += 8;

    return offset;
}

std::size_t MwcbDeclineLevelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MwcbDeclineLevelMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(level_1_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(level_2_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(level_3_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t MwcbDeclineLevelMessage::encoded_size() const {
    return wire_size;
}

void MwcbDeclineLevelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MwcbDeclineLevelMessage::clone() const {
    return std::make_unique<MwcbDeclineLevelMessage>(*this);
}

void MwcbDeclineLevelMessage::print(std::ostream& out) const {
    out << "MwcbDeclineLevelMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", level_1=";
    out << level_1_;
    out << ", level_2=";
    out << level_2_;
    out << ", level_3=";
    out << level_3_;
    out << '}';
}

bool MwcbDeclineLevelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MwcbDeclineLevelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MwcbDeclineLevelMessage::operator==(const MwcbDeclineLevelMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && level_1_ == other.level_1_
        && level_2_ == other.level_2_
        && level_3_ == other.level_3_;
}

bool MwcbDeclineLevelMessage::operator!=(const MwcbDeclineLevelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
