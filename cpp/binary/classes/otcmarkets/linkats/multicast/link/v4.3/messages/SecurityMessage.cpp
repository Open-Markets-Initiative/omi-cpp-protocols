#include "SecurityMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

SecurityMessage::SecurityMessage(std::uint32_t channel_seq_num, const std::string& symbol, std::uint64_t last_update_milli, SecurityAction security_action, AssetClass asset_class, std::uint32_t security_id, const SecurityFlags& security_flags, Tier tier, ReportingStatus reporting_status, SecurityStatus security_status)
  : channel_seq_num_(channel_seq_num), symbol_(symbol), last_update_milli_(last_update_milli), security_action_(security_action), asset_class_(asset_class), security_id_(security_id), security_flags_(security_flags), tier_(tier), reporting_status_(reporting_status), security_status_(security_status) {}

std::uint32_t SecurityMessage::channel_seq_num() const { return channel_seq_num_; }
void SecurityMessage::set_channel_seq_num(std::uint32_t value) { channel_seq_num_ = value; }

const std::string& SecurityMessage::symbol() const { return symbol_; }
std::string& SecurityMessage::symbol() { return symbol_; }
void SecurityMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t SecurityMessage::last_update_milli() const { return last_update_milli_; }
void SecurityMessage::set_last_update_milli(std::uint64_t value) { last_update_milli_ = value; }

SecurityAction SecurityMessage::security_action() const { return security_action_; }
void SecurityMessage::set_security_action(SecurityAction value) { security_action_ = value; }

AssetClass SecurityMessage::asset_class() const { return asset_class_; }
void SecurityMessage::set_asset_class(AssetClass value) { asset_class_ = value; }

std::uint32_t SecurityMessage::security_id() const { return security_id_; }
void SecurityMessage::set_security_id(std::uint32_t value) { security_id_ = value; }

const SecurityFlags& SecurityMessage::security_flags() const { return security_flags_; }
SecurityFlags& SecurityMessage::security_flags() { return security_flags_; }
void SecurityMessage::set_security_flags(const SecurityFlags& value) { security_flags_ = value; }

Tier SecurityMessage::tier() const { return tier_; }
void SecurityMessage::set_tier(Tier value) { tier_ = value; }

ReportingStatus SecurityMessage::reporting_status() const { return reporting_status_; }
void SecurityMessage::set_reporting_status(ReportingStatus value) { reporting_status_ = value; }

SecurityStatus SecurityMessage::security_status() const { return security_status_; }
void SecurityMessage::set_security_status(SecurityStatus value) { security_status_ = value; }

MessageCode SecurityMessage::type() const { return message_type; }

std::string_view SecurityMessage::name() const { return "Security Message"; }

std::size_t SecurityMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityMessage", wire_size, length);

    channel_seq_num_ = wire::read_u32_be(data + offset);
    offset += 4;

    symbol_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    last_update_milli_ = wire::read_u64_be(data + offset);
    offset += 8;

    security_action_ = static_cast<SecurityAction>(wire::read_u8(data + offset));
    offset += 1;

    asset_class_ = static_cast<AssetClass>(wire::read_u8(data + offset));
    offset += 1;

    security_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    offset += security_flags_.decode(data + offset, length - offset);

    tier_ = static_cast<Tier>(wire::read_u8(data + offset));
    offset += 1;

    reporting_status_ = static_cast<ReportingStatus>(wire::read_char(data + offset));
    offset += 1;

    security_status_ = static_cast<SecurityStatus>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SecurityMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(channel_seq_num_));
    offset += 4;

    wire::write_text(data + offset, 10, ' ', symbol_);
    offset += 10;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(last_update_milli_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_action_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(asset_class_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(security_id_));
    offset += 4;

    offset += security_flags_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(tier_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(reporting_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(security_status_));
    offset += 1;

    return offset;
}

std::size_t SecurityMessage::encoded_size() const {
    return wire_size;
}

void SecurityMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityMessage::clone() const {
    return std::make_unique<SecurityMessage>(*this);
}

void SecurityMessage::print(std::ostream& out) const {
    out << "SecurityMessage{";
    out << "channel_seq_num=";
    out << channel_seq_num_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", last_update_milli=";
    out << last_update_milli_;
    out << ", security_action=";
    out << security_action_;
    out << ", asset_class=";
    out << asset_class_;
    out << ", security_id=";
    out << security_id_;
    out << ", security_flags=";
    security_flags_.print(out);
    out << ", tier=";
    out << tier_;
    out << ", reporting_status=";
    out << reporting_status_;
    out << ", security_status=";
    out << security_status_;
    out << '}';
}

bool SecurityMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityMessage::operator==(const SecurityMessage& other) const {
    return channel_seq_num_ == other.channel_seq_num_
        && symbol_ == other.symbol_
        && last_update_milli_ == other.last_update_milli_
        && security_action_ == other.security_action_
        && asset_class_ == other.asset_class_
        && security_id_ == other.security_id_
        && security_flags_ == other.security_flags_
        && tier_ == other.tier_
        && reporting_status_ == other.reporting_status_
        && security_status_ == other.security_status_;
}

bool SecurityMessage::operator!=(const SecurityMessage& other) const {
    return !(*this == other);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
