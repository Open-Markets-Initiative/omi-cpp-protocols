#include "FilePayloadOrderCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

FilePayloadOrderCancelMessage::FilePayloadOrderCancelMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, std::uint32_t canceled_shares)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), canceled_shares_(canceled_shares) {}

std::uint16_t FilePayloadOrderCancelMessage::stock_locate() const { return stock_locate_; }
void FilePayloadOrderCancelMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t FilePayloadOrderCancelMessage::tracking_number() const { return tracking_number_; }
void FilePayloadOrderCancelMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds FilePayloadOrderCancelMessage::timestamp() const { return timestamp_; }
void FilePayloadOrderCancelMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t FilePayloadOrderCancelMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t FilePayloadOrderCancelMessage::order_reference_number() const { return order_reference_number_; }
void FilePayloadOrderCancelMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

std::uint32_t FilePayloadOrderCancelMessage::canceled_shares() const { return canceled_shares_; }
void FilePayloadOrderCancelMessage::set_canceled_shares(std::uint32_t value) { canceled_shares_ = value; }

FileMessageCode FilePayloadOrderCancelMessage::type() const { return message_type; }

std::string_view FilePayloadOrderCancelMessage::name() const { return "Order Cancel Message"; }

std::size_t FilePayloadOrderCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FilePayloadOrderCancelMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    canceled_shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t FilePayloadOrderCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FilePayloadOrderCancelMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(canceled_shares_));
    offset += 4;

    return offset;
}

std::size_t FilePayloadOrderCancelMessage::encoded_size() const {
    return wire_size;
}

void FilePayloadOrderCancelMessage::accept(FileMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<FileMessage> FilePayloadOrderCancelMessage::clone() const {
    return std::make_unique<FilePayloadOrderCancelMessage>(*this);
}

void FilePayloadOrderCancelMessage::print(std::ostream& out) const {
    out << "FilePayloadOrderCancelMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", canceled_shares=";
    out << canceled_shares_;
    out << '}';
}

bool FilePayloadOrderCancelMessage::equals(const FileMessage& other) const {
    const auto* that = dynamic_cast<const FilePayloadOrderCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FilePayloadOrderCancelMessage::operator==(const FilePayloadOrderCancelMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && canceled_shares_ == other.canceled_shares_;
}

bool FilePayloadOrderCancelMessage::operator!=(const FilePayloadOrderCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
