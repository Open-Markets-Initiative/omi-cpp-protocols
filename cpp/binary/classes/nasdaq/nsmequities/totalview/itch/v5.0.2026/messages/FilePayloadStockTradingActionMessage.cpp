#include "FilePayloadStockTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

FilePayloadStockTradingActionMessage::FilePayloadStockTradingActionMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, TradingState trading_state, char reserved, const std::string& reason_code)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), trading_state_(trading_state), reserved_(reserved), reason_code_(reason_code) {}

std::uint16_t FilePayloadStockTradingActionMessage::stock_locate() const { return stock_locate_; }
void FilePayloadStockTradingActionMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t FilePayloadStockTradingActionMessage::tracking_number() const { return tracking_number_; }
void FilePayloadStockTradingActionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds FilePayloadStockTradingActionMessage::timestamp() const { return timestamp_; }
void FilePayloadStockTradingActionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t FilePayloadStockTradingActionMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

const std::string& FilePayloadStockTradingActionMessage::stock() const { return stock_; }
std::string& FilePayloadStockTradingActionMessage::stock() { return stock_; }
void FilePayloadStockTradingActionMessage::set_stock(const std::string& value) { stock_ = value; }

TradingState FilePayloadStockTradingActionMessage::trading_state() const { return trading_state_; }
void FilePayloadStockTradingActionMessage::set_trading_state(TradingState value) { trading_state_ = value; }

char FilePayloadStockTradingActionMessage::reserved() const { return reserved_; }
void FilePayloadStockTradingActionMessage::set_reserved(char value) { reserved_ = value; }

const std::string& FilePayloadStockTradingActionMessage::reason_code() const { return reason_code_; }
std::string& FilePayloadStockTradingActionMessage::reason_code() { return reason_code_; }
void FilePayloadStockTradingActionMessage::set_reason_code(const std::string& value) { reason_code_ = value; }

FileMessageCode FilePayloadStockTradingActionMessage::type() const { return message_type; }

std::string_view FilePayloadStockTradingActionMessage::name() const { return "Stock Trading Action Message"; }

std::size_t FilePayloadStockTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("FilePayloadStockTradingActionMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    trading_state_ = static_cast<TradingState>(wire::read_char(data + offset));
    offset += 1;

    reserved_ = wire::read_char(data + offset);
    offset += 1;

    reason_code_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t FilePayloadStockTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FilePayloadStockTradingActionMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trading_state_));
    offset += 1;

    wire::write_char(data + offset, reserved_);
    offset += 1;

    wire::write_text(data + offset, 4, ' ', reason_code_);
    offset += 4;

    return offset;
}

std::size_t FilePayloadStockTradingActionMessage::encoded_size() const {
    return wire_size;
}

void FilePayloadStockTradingActionMessage::accept(FileMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<FileMessage> FilePayloadStockTradingActionMessage::clone() const {
    return std::make_unique<FilePayloadStockTradingActionMessage>(*this);
}

void FilePayloadStockTradingActionMessage::print(std::ostream& out) const {
    out << "FilePayloadStockTradingActionMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", stock=";
    print::text(out, stock_);
    out << ", trading_state=";
    out << trading_state_;
    out << ", reserved=";
    print::character(out, reserved_);
    out << ", reason_code=";
    print::text(out, reason_code_);
    out << '}';
}

bool FilePayloadStockTradingActionMessage::equals(const FileMessage& other) const {
    const auto* that = dynamic_cast<const FilePayloadStockTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool FilePayloadStockTradingActionMessage::operator==(const FilePayloadStockTradingActionMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && trading_state_ == other.trading_state_
        && reserved_ == other.reserved_
        && reason_code_ == other.reason_code_;
}

bool FilePayloadStockTradingActionMessage::operator!=(const FilePayloadStockTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
