#include "VolumeAndOpenInterestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

VolumeAndOpenInterestMessage::VolumeAndOpenInterestMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, std::uint64_t cumulative_volume, std::uint64_t open_interest, std::uint16_t voi_trade_date)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), cumulative_volume_(cumulative_volume), open_interest_(open_interest), voi_trade_date_(voi_trade_date) {}

std::chrono::nanoseconds VolumeAndOpenInterestMessage::nanoseconds() const { return nanoseconds_; }
void VolumeAndOpenInterestMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t VolumeAndOpenInterestMessage::trade_date() const { return trade_date_; }
void VolumeAndOpenInterestMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t VolumeAndOpenInterestMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void VolumeAndOpenInterestMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

std::uint64_t VolumeAndOpenInterestMessage::cumulative_volume() const { return cumulative_volume_; }
void VolumeAndOpenInterestMessage::set_cumulative_volume(std::uint64_t value) { cumulative_volume_ = value; }

std::uint64_t VolumeAndOpenInterestMessage::open_interest() const { return open_interest_; }
void VolumeAndOpenInterestMessage::set_open_interest(std::uint64_t value) { open_interest_ = value; }

std::uint16_t VolumeAndOpenInterestMessage::voi_trade_date() const { return voi_trade_date_; }
void VolumeAndOpenInterestMessage::set_voi_trade_date(std::uint16_t value) { voi_trade_date_ = value; }

MessageCode VolumeAndOpenInterestMessage::type() const { return message_type; }

std::string_view VolumeAndOpenInterestMessage::name() const { return "Volume And Open Interest Message"; }

std::size_t VolumeAndOpenInterestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("VolumeAndOpenInterestMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    cumulative_volume_ = wire::read_u64_be(data + offset);
    offset += 8;

    open_interest_ = wire::read_u64_be(data + offset);
    offset += 8;

    voi_trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t VolumeAndOpenInterestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("VolumeAndOpenInterestMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(cumulative_volume_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(open_interest_));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(voi_trade_date_));
    offset += 2;

    return offset;
}

std::size_t VolumeAndOpenInterestMessage::encoded_size() const {
    return wire_size;
}

void VolumeAndOpenInterestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> VolumeAndOpenInterestMessage::clone() const {
    return std::make_unique<VolumeAndOpenInterestMessage>(*this);
}

void VolumeAndOpenInterestMessage::print(std::ostream& out) const {
    out << "VolumeAndOpenInterestMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", cumulative_volume=";
    out << cumulative_volume_;
    out << ", open_interest=";
    out << open_interest_;
    out << ", voi_trade_date=";
    out << voi_trade_date_;
    out << '}';
}

bool VolumeAndOpenInterestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const VolumeAndOpenInterestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool VolumeAndOpenInterestMessage::operator==(const VolumeAndOpenInterestMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && cumulative_volume_ == other.cumulative_volume_
        && open_interest_ == other.open_interest_
        && voi_trade_date_ == other.voi_trade_date_;
}

bool VolumeAndOpenInterestMessage::operator!=(const VolumeAndOpenInterestMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
