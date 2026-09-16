#include "RetailPriceImprovementIndicatorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

RetailPriceImprovementIndicatorMessage::RetailPriceImprovementIndicatorMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, InterestFlag interest_flag)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), interest_flag_(interest_flag) {}

std::uint16_t RetailPriceImprovementIndicatorMessage::stock_locate() const { return stock_locate_; }
void RetailPriceImprovementIndicatorMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t RetailPriceImprovementIndicatorMessage::tracking_number() const { return tracking_number_; }
void RetailPriceImprovementIndicatorMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds RetailPriceImprovementIndicatorMessage::timestamp() const { return timestamp_; }
void RetailPriceImprovementIndicatorMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& RetailPriceImprovementIndicatorMessage::stock() const { return stock_; }
std::string& RetailPriceImprovementIndicatorMessage::stock() { return stock_; }
void RetailPriceImprovementIndicatorMessage::set_stock(const std::string& value) { stock_ = value; }

InterestFlag RetailPriceImprovementIndicatorMessage::interest_flag() const { return interest_flag_; }
void RetailPriceImprovementIndicatorMessage::set_interest_flag(InterestFlag value) { interest_flag_ = value; }

MessageCode RetailPriceImprovementIndicatorMessage::type() const { return message_type; }

std::string_view RetailPriceImprovementIndicatorMessage::name() const { return "Retail Price Improvement Indicator Message"; }

std::size_t RetailPriceImprovementIndicatorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetailPriceImprovementIndicatorMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    interest_flag_ = static_cast<InterestFlag>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t RetailPriceImprovementIndicatorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetailPriceImprovementIndicatorMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(interest_flag_));
    offset += 1;

    return offset;
}

std::size_t RetailPriceImprovementIndicatorMessage::encoded_size() const {
    return wire_size;
}

void RetailPriceImprovementIndicatorMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RetailPriceImprovementIndicatorMessage::clone() const {
    return std::make_unique<RetailPriceImprovementIndicatorMessage>(*this);
}

void RetailPriceImprovementIndicatorMessage::print(std::ostream& out) const {
    out << "RetailPriceImprovementIndicatorMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", interest_flag=";
    out << interest_flag_;
    out << '}';
}

bool RetailPriceImprovementIndicatorMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RetailPriceImprovementIndicatorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetailPriceImprovementIndicatorMessage::operator==(const RetailPriceImprovementIndicatorMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && interest_flag_ == other.interest_flag_;
}

bool RetailPriceImprovementIndicatorMessage::operator!=(const RetailPriceImprovementIndicatorMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
