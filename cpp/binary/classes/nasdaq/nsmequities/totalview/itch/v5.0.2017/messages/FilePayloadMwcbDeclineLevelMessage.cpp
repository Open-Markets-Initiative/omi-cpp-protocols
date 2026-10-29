#include "FilePayloadMwcbDeclineLevelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

FilePayloadMwcbDeclineLevelMessage::FilePayloadMwcbDeclineLevelMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, Decimal level_1, Decimal level_2, Decimal level_3)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), level_1_(level_1), level_2_(level_2), level_3_(level_3) {}

std::uint16_t FilePayloadMwcbDeclineLevelMessage::stock_locate() const { return stock_locate_; }
void FilePayloadMwcbDeclineLevelMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t FilePayloadMwcbDeclineLevelMessage::tracking_number() const { return tracking_number_; }
void FilePayloadMwcbDeclineLevelMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds FilePayloadMwcbDeclineLevelMessage::timestamp() const { return timestamp_; }
void FilePayloadMwcbDeclineLevelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t FilePayloadMwcbDeclineLevelMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

Decimal FilePayloadMwcbDeclineLevelMessage::level_1() const { return level_1_; }
void FilePayloadMwcbDeclineLevelMessage::set_level_1(Decimal value) { level_1_ = value; }

Decimal FilePayloadMwcbDeclineLevelMessage::level_2() const { return level_2_; }
void FilePayloadMwcbDeclineLevelMessage::set_level_2(Decimal value) { level_2_ = value; }

Decimal FilePayloadMwcbDeclineLevelMessage::level_3() const { return level_3_; }
void FilePayloadMwcbDeclineLevelMessage::set_level_3(Decimal value) { level_3_ = value; }

FileMessageCode FilePayloadMwcbDeclineLevelMessage::type() const { return message_type; }

std::string_view FilePayloadMwcbDeclineLevelMessage::name() const { return "Mwcb Decline Level Message"; }

std::size_t FilePayloadMwcbDeclineLevelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FilePayloadMwcbDeclineLevelMessage", wire_size, length);

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

std::size_t FilePayloadMwcbDeclineLevelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FilePayloadMwcbDeclineLevelMessage", wire_size, capacity);

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

std::size_t FilePayloadMwcbDeclineLevelMessage::encoded_size() const {
    return wire_size;
}

void FilePayloadMwcbDeclineLevelMessage::accept(FileMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<FileMessage> FilePayloadMwcbDeclineLevelMessage::clone() const {
    return std::make_unique<FilePayloadMwcbDeclineLevelMessage>(*this);
}

void FilePayloadMwcbDeclineLevelMessage::print(std::ostream& out) const {
    out << "FilePayloadMwcbDeclineLevelMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", level_1=";
    out << level_1_;
    out << ", level_2=";
    out << level_2_;
    out << ", level_3=";
    out << level_3_;
    out << '}';
}

bool FilePayloadMwcbDeclineLevelMessage::equals(const FileMessage& other) const {
    const auto* that = dynamic_cast<const FilePayloadMwcbDeclineLevelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FilePayloadMwcbDeclineLevelMessage::operator==(const FilePayloadMwcbDeclineLevelMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && level_1_ == other.level_1_
        && level_2_ == other.level_2_
        && level_3_ == other.level_3_;
}

bool FilePayloadMwcbDeclineLevelMessage::operator!=(const FilePayloadMwcbDeclineLevelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
