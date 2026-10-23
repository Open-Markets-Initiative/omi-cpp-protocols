#include "PriceImprovementMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

PriceImprovementMessage::PriceImprovementMessage(std::uint16_t tracking, std::chrono::nanoseconds time_stamp, const std::string& stock, InterestFlag interest_flag)
  : tracking_(tracking), time_stamp_(time_stamp), stock_(stock), interest_flag_(interest_flag) {}

std::uint16_t PriceImprovementMessage::tracking() const { return tracking_; }
void PriceImprovementMessage::set_tracking(std::uint16_t value) { tracking_ = value; }

std::chrono::nanoseconds PriceImprovementMessage::time_stamp() const { return time_stamp_; }
void PriceImprovementMessage::set_time_stamp(std::chrono::nanoseconds value) { time_stamp_ = value; }

const std::string& PriceImprovementMessage::stock() const { return stock_; }
std::string& PriceImprovementMessage::stock() { return stock_; }
void PriceImprovementMessage::set_stock(const std::string& value) { stock_ = value; }

InterestFlag PriceImprovementMessage::interest_flag() const { return interest_flag_; }
void PriceImprovementMessage::set_interest_flag(InterestFlag value) { interest_flag_ = value; }

MessageCode PriceImprovementMessage::type() const { return message_type; }

std::string_view PriceImprovementMessage::name() const { return "Price Improvement Message"; }

std::size_t PriceImprovementMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriceImprovementMessage", wire_size, length);

    tracking_ = wire::read_u16_be(data + offset);
    offset += 2;

    time_stamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    interest_flag_ = static_cast<InterestFlag>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t PriceImprovementMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriceImprovementMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(time_stamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(interest_flag_));
    offset += 1;

    return offset;
}

std::size_t PriceImprovementMessage::encoded_size() const {
    return wire_size;
}

void PriceImprovementMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PriceImprovementMessage::clone() const {
    return std::make_unique<PriceImprovementMessage>(*this);
}

void PriceImprovementMessage::print(std::ostream& out) const {
    out << "PriceImprovementMessage{";
    out << "tracking=";
    out << tracking_;
    out << ", time_stamp=";
    out << time_stamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", interest_flag=";
    out << interest_flag_;
    out << '}';
}

bool PriceImprovementMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PriceImprovementMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PriceImprovementMessage::operator==(const PriceImprovementMessage& other) const {
    return tracking_ == other.tracking_
        && time_stamp_ == other.time_stamp_
        && stock_ == other.stock_
        && interest_flag_ == other.interest_flag_;
}

bool PriceImprovementMessage::operator!=(const PriceImprovementMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
