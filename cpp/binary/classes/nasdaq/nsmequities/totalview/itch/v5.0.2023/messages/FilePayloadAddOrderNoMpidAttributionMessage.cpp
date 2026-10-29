#include "FilePayloadAddOrderNoMpidAttributionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

FilePayloadAddOrderNoMpidAttributionMessage::FilePayloadAddOrderNoMpidAttributionMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, BuySellIndicator buy_sell_indicator, std::uint32_t shares, const std::string& stock, Decimal price)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number), buy_sell_indicator_(buy_sell_indicator), shares_(shares), stock_(stock), price_(price) {}

std::uint16_t FilePayloadAddOrderNoMpidAttributionMessage::stock_locate() const { return stock_locate_; }
void FilePayloadAddOrderNoMpidAttributionMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t FilePayloadAddOrderNoMpidAttributionMessage::tracking_number() const { return tracking_number_; }
void FilePayloadAddOrderNoMpidAttributionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds FilePayloadAddOrderNoMpidAttributionMessage::timestamp() const { return timestamp_; }
void FilePayloadAddOrderNoMpidAttributionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t FilePayloadAddOrderNoMpidAttributionMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint64_t FilePayloadAddOrderNoMpidAttributionMessage::order_reference_number() const { return order_reference_number_; }
void FilePayloadAddOrderNoMpidAttributionMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

BuySellIndicator FilePayloadAddOrderNoMpidAttributionMessage::buy_sell_indicator() const { return buy_sell_indicator_; }
void FilePayloadAddOrderNoMpidAttributionMessage::set_buy_sell_indicator(BuySellIndicator value) { buy_sell_indicator_ = value; }

std::uint32_t FilePayloadAddOrderNoMpidAttributionMessage::shares() const { return shares_; }
void FilePayloadAddOrderNoMpidAttributionMessage::set_shares(std::uint32_t value) { shares_ = value; }

const std::string& FilePayloadAddOrderNoMpidAttributionMessage::stock() const { return stock_; }
std::string& FilePayloadAddOrderNoMpidAttributionMessage::stock() { return stock_; }
void FilePayloadAddOrderNoMpidAttributionMessage::set_stock(const std::string& value) { stock_ = value; }

Decimal FilePayloadAddOrderNoMpidAttributionMessage::price() const { return price_; }
void FilePayloadAddOrderNoMpidAttributionMessage::set_price(Decimal value) { price_ = value; }

FileMessageCode FilePayloadAddOrderNoMpidAttributionMessage::type() const { return message_type; }

std::string_view FilePayloadAddOrderNoMpidAttributionMessage::name() const { return "Add Order No Mpid Attribution Message"; }

std::size_t FilePayloadAddOrderNoMpidAttributionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FilePayloadAddOrderNoMpidAttributionMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    buy_sell_indicator_ = static_cast<BuySellIndicator>(wire::read_char(data + offset));
    offset += 1;

    shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t FilePayloadAddOrderNoMpidAttributionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FilePayloadAddOrderNoMpidAttributionMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(buy_sell_indicator_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(shares_));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t FilePayloadAddOrderNoMpidAttributionMessage::encoded_size() const {
    return wire_size;
}

void FilePayloadAddOrderNoMpidAttributionMessage::accept(FileMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<FileMessage> FilePayloadAddOrderNoMpidAttributionMessage::clone() const {
    return std::make_unique<FilePayloadAddOrderNoMpidAttributionMessage>(*this);
}

void FilePayloadAddOrderNoMpidAttributionMessage::print(std::ostream& out) const {
    out << "FilePayloadAddOrderNoMpidAttributionMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << ", buy_sell_indicator=";
    out << buy_sell_indicator_;
    out << ", shares=";
    out << shares_;
    out << ", stock=";
    print::text(out, stock_);
    out << ", price=";
    out << price_;
    out << '}';
}

bool FilePayloadAddOrderNoMpidAttributionMessage::equals(const FileMessage& other) const {
    const auto* that = dynamic_cast<const FilePayloadAddOrderNoMpidAttributionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FilePayloadAddOrderNoMpidAttributionMessage::operator==(const FilePayloadAddOrderNoMpidAttributionMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_
        && buy_sell_indicator_ == other.buy_sell_indicator_
        && shares_ == other.shares_
        && stock_ == other.stock_
        && price_ == other.price_;
}

bool FilePayloadAddOrderNoMpidAttributionMessage::operator!=(const FilePayloadAddOrderNoMpidAttributionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
