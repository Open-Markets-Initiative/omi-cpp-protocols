#include "PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, const std::string& stock, OpenEligibilityStatus open_eligibility_status, Decimal minimum_allowable_price, Decimal maximum_allowable_price, Decimal near_execution_price, std::uint64_t near_execution_time, Decimal lower_price_range_collar, Decimal upper_price_range_collar)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), stock_(stock), open_eligibility_status_(open_eligibility_status), minimum_allowable_price_(minimum_allowable_price), maximum_allowable_price_(maximum_allowable_price), near_execution_price_(near_execution_price), near_execution_time_(near_execution_time), lower_price_range_collar_(lower_price_range_collar), upper_price_range_collar_(upper_price_range_collar) {}

std::uint16_t PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::stock_locate() const { return stock_locate_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::tracking_number() const { return tracking_number_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::timestamp() const { return timestamp_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::stock() const { return stock_; }
std::string& PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::stock() { return stock_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_stock(const std::string& value) { stock_ = value; }

OpenEligibilityStatus PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::open_eligibility_status() const { return open_eligibility_status_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_open_eligibility_status(OpenEligibilityStatus value) { open_eligibility_status_ = value; }

Decimal PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::minimum_allowable_price() const { return minimum_allowable_price_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_minimum_allowable_price(Decimal value) { minimum_allowable_price_ = value; }

Decimal PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::maximum_allowable_price() const { return maximum_allowable_price_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_maximum_allowable_price(Decimal value) { maximum_allowable_price_ = value; }

Decimal PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::near_execution_price() const { return near_execution_price_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_near_execution_price(Decimal value) { near_execution_price_ = value; }

std::uint64_t PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::near_execution_time() const { return near_execution_time_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_near_execution_time(std::uint64_t value) { near_execution_time_ = value; }

Decimal PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::lower_price_range_collar() const { return lower_price_range_collar_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_lower_price_range_collar(Decimal value) { lower_price_range_collar_ = value; }

Decimal PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::upper_price_range_collar() const { return upper_price_range_collar_; }
void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::set_upper_price_range_collar(Decimal value) { upper_price_range_collar_ = value; }

PacketMessageCode PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::type() const { return message_type; }

std::string_view PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::name() const { return "Direct Listing With Capital Raise Price Discovery Message"; }

std::size_t PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    open_eligibility_status_ = static_cast<OpenEligibilityStatus>(wire::read_char(data + offset));
    offset += 1;

    minimum_allowable_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    maximum_allowable_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    near_execution_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    near_execution_time_ = wire::read_u64_be(data + offset);
    offset += 8;

    lower_price_range_collar_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    upper_price_range_collar_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(open_eligibility_status_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(minimum_allowable_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(maximum_allowable_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(near_execution_price_.mantissa()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(near_execution_time_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(lower_price_range_collar_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(upper_price_range_collar_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::encoded_size() const {
    return wire_size;
}

void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::clone() const {
    return std::make_unique<PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage>(*this);
}

void PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::print(std::ostream& out) const {
    out << "PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", stock=";
    print::text(out, stock_);
    out << ", open_eligibility_status=";
    out << open_eligibility_status_;
    out << ", minimum_allowable_price=";
    out << minimum_allowable_price_;
    out << ", maximum_allowable_price=";
    out << maximum_allowable_price_;
    out << ", near_execution_price=";
    out << near_execution_price_;
    out << ", near_execution_time=";
    out << near_execution_time_;
    out << ", lower_price_range_collar=";
    out << lower_price_range_collar_;
    out << ", upper_price_range_collar=";
    out << upper_price_range_collar_;
    out << '}';
}

bool PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::operator==(const PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && stock_ == other.stock_
        && open_eligibility_status_ == other.open_eligibility_status_
        && minimum_allowable_price_ == other.minimum_allowable_price_
        && maximum_allowable_price_ == other.maximum_allowable_price_
        && near_execution_price_ == other.near_execution_price_
        && near_execution_time_ == other.near_execution_time_
        && lower_price_range_collar_ == other.lower_price_range_collar_
        && upper_price_range_collar_ == other.upper_price_range_collar_;
}

bool PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::operator!=(const PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
