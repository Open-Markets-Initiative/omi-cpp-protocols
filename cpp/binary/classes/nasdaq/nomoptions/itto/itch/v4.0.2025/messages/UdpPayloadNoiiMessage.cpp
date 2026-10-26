#include "UdpPayloadNoiiMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

UdpPayloadNoiiMessage::UdpPayloadNoiiMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t auction_id, AuctionType auction_type, std::uint32_t paired_contracts, ImbalanceDirection imbalance_direction, std::uint32_t option_id, Decimal imbalance_price, std::uint32_t imbalance_volume, CustomerFirmIndicator customer_firm_indicator, const std::array<std::byte, 3>& reserved_3)
  : tracking_number_(tracking_number), timestamp_(timestamp), auction_id_(auction_id), auction_type_(auction_type), paired_contracts_(paired_contracts), imbalance_direction_(imbalance_direction), option_id_(option_id), imbalance_price_(imbalance_price), imbalance_volume_(imbalance_volume), customer_firm_indicator_(customer_firm_indicator), reserved_3_(reserved_3) {}

std::uint16_t UdpPayloadNoiiMessage::tracking_number() const { return tracking_number_; }
void UdpPayloadNoiiMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds UdpPayloadNoiiMessage::timestamp() const { return timestamp_; }
void UdpPayloadNoiiMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t UdpPayloadNoiiMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t UdpPayloadNoiiMessage::auction_id() const { return auction_id_; }
void UdpPayloadNoiiMessage::set_auction_id(std::uint32_t value) { auction_id_ = value; }

AuctionType UdpPayloadNoiiMessage::auction_type() const { return auction_type_; }
void UdpPayloadNoiiMessage::set_auction_type(AuctionType value) { auction_type_ = value; }

std::uint32_t UdpPayloadNoiiMessage::paired_contracts() const { return paired_contracts_; }
void UdpPayloadNoiiMessage::set_paired_contracts(std::uint32_t value) { paired_contracts_ = value; }

ImbalanceDirection UdpPayloadNoiiMessage::imbalance_direction() const { return imbalance_direction_; }
void UdpPayloadNoiiMessage::set_imbalance_direction(ImbalanceDirection value) { imbalance_direction_ = value; }

std::uint32_t UdpPayloadNoiiMessage::option_id() const { return option_id_; }
void UdpPayloadNoiiMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

Decimal UdpPayloadNoiiMessage::imbalance_price() const { return imbalance_price_; }
void UdpPayloadNoiiMessage::set_imbalance_price(Decimal value) { imbalance_price_ = value; }

std::uint32_t UdpPayloadNoiiMessage::imbalance_volume() const { return imbalance_volume_; }
void UdpPayloadNoiiMessage::set_imbalance_volume(std::uint32_t value) { imbalance_volume_ = value; }

CustomerFirmIndicator UdpPayloadNoiiMessage::customer_firm_indicator() const { return customer_firm_indicator_; }
void UdpPayloadNoiiMessage::set_customer_firm_indicator(CustomerFirmIndicator value) { customer_firm_indicator_ = value; }

const std::array<std::byte, 3>& UdpPayloadNoiiMessage::reserved_3() const { return reserved_3_; }
std::array<std::byte, 3>& UdpPayloadNoiiMessage::reserved_3() { return reserved_3_; }
void UdpPayloadNoiiMessage::set_reserved_3(const std::array<std::byte, 3>& value) { reserved_3_ = value; }

PacketMessageCode UdpPayloadNoiiMessage::type() const { return message_type; }

std::string_view UdpPayloadNoiiMessage::name() const { return "Noii Message"; }

std::size_t UdpPayloadNoiiMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UdpPayloadNoiiMessage", wire_size, length);

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    auction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    auction_type_ = static_cast<AuctionType>(wire::read_char(data + offset));
    offset += 1;

    paired_contracts_ = wire::read_u32_be(data + offset);
    offset += 4;

    imbalance_direction_ = static_cast<ImbalanceDirection>(wire::read_char(data + offset));
    offset += 1;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    imbalance_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    imbalance_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    customer_firm_indicator_ = static_cast<CustomerFirmIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t UdpPayloadNoiiMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UdpPayloadNoiiMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(auction_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(auction_type_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(paired_contracts_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(imbalance_direction_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(imbalance_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(imbalance_volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(customer_firm_indicator_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t UdpPayloadNoiiMessage::encoded_size() const {
    return wire_size;
}

void UdpPayloadNoiiMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> UdpPayloadNoiiMessage::clone() const {
    return std::make_unique<UdpPayloadNoiiMessage>(*this);
}

void UdpPayloadNoiiMessage::print(std::ostream& out) const {
    out << "UdpPayloadNoiiMessage{";
    out << "tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    calendar::print(out, timestamp_.count(), 1, "America/New_York");
    out << ", auction_id=";
    out << auction_id_;
    out << ", auction_type=";
    out << auction_type_;
    out << ", paired_contracts=";
    out << paired_contracts_;
    out << ", imbalance_direction=";
    out << imbalance_direction_;
    out << ", option_id=";
    out << option_id_;
    out << ", imbalance_price=";
    out << imbalance_price_;
    out << ", imbalance_volume=";
    out << imbalance_volume_;
    out << ", customer_firm_indicator=";
    out << customer_firm_indicator_;
    out << ", reserved_3=";
    print::hex(out, reserved_3_.data(), reserved_3_.size());
    out << '}';
}

bool UdpPayloadNoiiMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UdpPayloadNoiiMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UdpPayloadNoiiMessage::operator==(const UdpPayloadNoiiMessage& other) const {
    return tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && auction_id_ == other.auction_id_
        && auction_type_ == other.auction_type_
        && paired_contracts_ == other.paired_contracts_
        && imbalance_direction_ == other.imbalance_direction_
        && option_id_ == other.option_id_
        && imbalance_price_ == other.imbalance_price_
        && imbalance_volume_ == other.imbalance_volume_
        && customer_firm_indicator_ == other.customer_firm_indicator_
        && reserved_3_ == other.reserved_3_;
}

bool UdpPayloadNoiiMessage::operator!=(const UdpPayloadNoiiMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
