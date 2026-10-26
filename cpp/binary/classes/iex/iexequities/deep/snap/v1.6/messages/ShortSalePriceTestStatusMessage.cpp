#include "ShortSalePriceTestStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

ShortSalePriceTestStatusMessage::ShortSalePriceTestStatusMessage(ShortSalePriceTestStatus short_sale_price_test_status, std::chrono::nanoseconds timestamp, const std::string& symbol, Detail detail)
  : short_sale_price_test_status_(short_sale_price_test_status), timestamp_(timestamp), symbol_(symbol), detail_(detail) {}

ShortSalePriceTestStatus ShortSalePriceTestStatusMessage::short_sale_price_test_status() const { return short_sale_price_test_status_; }
void ShortSalePriceTestStatusMessage::set_short_sale_price_test_status(ShortSalePriceTestStatus value) { short_sale_price_test_status_ = value; }

std::chrono::nanoseconds ShortSalePriceTestStatusMessage::timestamp() const { return timestamp_; }
void ShortSalePriceTestStatusMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& ShortSalePriceTestStatusMessage::symbol() const { return symbol_; }
std::string& ShortSalePriceTestStatusMessage::symbol() { return symbol_; }
void ShortSalePriceTestStatusMessage::set_symbol(const std::string& value) { symbol_ = value; }

Detail ShortSalePriceTestStatusMessage::detail() const { return detail_; }
void ShortSalePriceTestStatusMessage::set_detail(Detail value) { detail_ = value; }

IexTpMessageDataCode ShortSalePriceTestStatusMessage::type() const { return message_type; }

std::string_view ShortSalePriceTestStatusMessage::name() const { return "Short Sale Price Test Status Message"; }

std::size_t ShortSalePriceTestStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ShortSalePriceTestStatusMessage", wire_size, length);

    short_sale_price_test_status_ = static_cast<ShortSalePriceTestStatus>(wire::read_u8(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    detail_ = static_cast<Detail>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t ShortSalePriceTestStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ShortSalePriceTestStatusMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(short_sale_price_test_status_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(detail_));
    offset += 1;

    return offset;
}

std::size_t ShortSalePriceTestStatusMessage::encoded_size() const {
    return wire_size;
}

void ShortSalePriceTestStatusMessage::accept(IexTpMessageDataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<IexTpMessageData> ShortSalePriceTestStatusMessage::clone() const {
    return std::make_unique<ShortSalePriceTestStatusMessage>(*this);
}

void ShortSalePriceTestStatusMessage::print(std::ostream& out) const {
    out << "ShortSalePriceTestStatusMessage{";
    out << "short_sale_price_test_status=";
    out << short_sale_price_test_status_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", detail=";
    out << detail_;
    out << '}';
}

bool ShortSalePriceTestStatusMessage::equals(const IexTpMessageData& other) const {
    const auto* that = dynamic_cast<const ShortSalePriceTestStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ShortSalePriceTestStatusMessage::operator==(const ShortSalePriceTestStatusMessage& other) const {
    return short_sale_price_test_status_ == other.short_sale_price_test_status_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && detail_ == other.detail_;
}

bool ShortSalePriceTestStatusMessage::operator!=(const ShortSalePriceTestStatusMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deep::snap::v1_6
