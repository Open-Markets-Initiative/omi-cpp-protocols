#include "FilePayloadOrderDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

FilePayloadOrderDeleteMessage::FilePayloadOrderDeleteMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number) {}

std::uint16_t FilePayloadOrderDeleteMessage::stock_locate() const { return stock_locate_; }
void FilePayloadOrderDeleteMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t FilePayloadOrderDeleteMessage::tracking_number() const { return tracking_number_; }
void FilePayloadOrderDeleteMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds FilePayloadOrderDeleteMessage::timestamp() const { return timestamp_; }
void FilePayloadOrderDeleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t FilePayloadOrderDeleteMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t FilePayloadOrderDeleteMessage::order_reference_number() const { return order_reference_number_; }
void FilePayloadOrderDeleteMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

FileMessageCode FilePayloadOrderDeleteMessage::type() const { return message_type; }

std::string_view FilePayloadOrderDeleteMessage::name() const { return "Order Delete Message"; }

std::size_t FilePayloadOrderDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FilePayloadOrderDeleteMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t FilePayloadOrderDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FilePayloadOrderDeleteMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    return offset;
}

std::size_t FilePayloadOrderDeleteMessage::encoded_size() const {
    return wire_size;
}

void FilePayloadOrderDeleteMessage::accept(FileMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<FileMessage> FilePayloadOrderDeleteMessage::clone() const {
    return std::make_unique<FilePayloadOrderDeleteMessage>(*this);
}

void FilePayloadOrderDeleteMessage::print(std::ostream& out) const {
    out << "FilePayloadOrderDeleteMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << '}';
}

bool FilePayloadOrderDeleteMessage::equals(const FileMessage& other) const {
    const auto* that = dynamic_cast<const FilePayloadOrderDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FilePayloadOrderDeleteMessage::operator==(const FilePayloadOrderDeleteMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_;
}

bool FilePayloadOrderDeleteMessage::operator!=(const FilePayloadOrderDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
