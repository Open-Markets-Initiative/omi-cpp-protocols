#include "MassDeleteOrdersMbO52Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

MassDeleteOrdersMbO52Message::MassDeleteOrdersMbO52Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, MdEntryType md_entry_type, const std::array<std::byte, 1>& offset_11_padding_1, std::uint32_t md_entry_position_no, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), md_update_action_(md_update_action), md_entry_type_(md_entry_type), offset_11_padding_1_(offset_11_padding_1), md_entry_position_no_(md_entry_position_no), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t MassDeleteOrdersMbO52Message::security_id() const { return security_id_; }
void MassDeleteOrdersMbO52Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& MassDeleteOrdersMbO52Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& MassDeleteOrdersMbO52Message::match_event_indicator() { return match_event_indicator_; }
void MassDeleteOrdersMbO52Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

MdUpdateAction MassDeleteOrdersMbO52Message::md_update_action() const { return md_update_action_; }
void MassDeleteOrdersMbO52Message::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

MdEntryType MassDeleteOrdersMbO52Message::md_entry_type() const { return md_entry_type_; }
void MassDeleteOrdersMbO52Message::set_md_entry_type(MdEntryType value) { md_entry_type_ = value; }

const std::array<std::byte, 1>& MassDeleteOrdersMbO52Message::offset_11_padding_1() const { return offset_11_padding_1_; }
std::array<std::byte, 1>& MassDeleteOrdersMbO52Message::offset_11_padding_1() { return offset_11_padding_1_; }
void MassDeleteOrdersMbO52Message::set_offset_11_padding_1(const std::array<std::byte, 1>& value) { offset_11_padding_1_ = value; }

std::uint32_t MassDeleteOrdersMbO52Message::md_entry_position_no() const { return md_entry_position_no_; }
void MassDeleteOrdersMbO52Message::set_md_entry_position_no(std::uint32_t value) { md_entry_position_no_ = value; }

std::optional<std::chrono::nanoseconds> MassDeleteOrdersMbO52Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void MassDeleteOrdersMbO52Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> MassDeleteOrdersMbO52Message::rpt_seq() const { return rpt_seq_; }
void MassDeleteOrdersMbO52Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode MassDeleteOrdersMbO52Message::type() const { return message_type; }

std::string_view MassDeleteOrdersMbO52Message::name() const { return "Mass Delete Orders Mb O 52 Message"; }

std::size_t MassDeleteOrdersMbO52Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MassDeleteOrdersMbO52Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    md_entry_type_ = static_cast<MdEntryType>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_11_padding_1_.data(), 1);
    offset += 1;

    md_entry_position_no_ = wire::read_u32_le(data + offset);
    offset += 4;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t MassDeleteOrdersMbO52Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MassDeleteOrdersMbO52Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(md_entry_type_));
    offset += 1;

    wire::write_bytes(data + offset, offset_11_padding_1_.data(), 1);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(md_entry_position_no_));
    offset += 4;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t MassDeleteOrdersMbO52Message::encoded_size() const {
    return wire_size;
}

void MassDeleteOrdersMbO52Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MassDeleteOrdersMbO52Message::clone() const {
    return std::make_unique<MassDeleteOrdersMbO52Message>(*this);
}

void MassDeleteOrdersMbO52Message::print(std::ostream& out) const {
    out << "MassDeleteOrdersMbO52Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", md_entry_type=";
    out << md_entry_type_;
    out << ", offset_11_padding_1=";
    print::hex(out, offset_11_padding_1_.data(), offset_11_padding_1_.size());
    out << ", md_entry_position_no=";
    out << md_entry_position_no_;
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool MassDeleteOrdersMbO52Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MassDeleteOrdersMbO52Message*>(&other);
    return that != nullptr && *this == *that;
}

bool MassDeleteOrdersMbO52Message::operator==(const MassDeleteOrdersMbO52Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && md_update_action_ == other.md_update_action_
        && md_entry_type_ == other.md_entry_type_
        && offset_11_padding_1_ == other.offset_11_padding_1_
        && md_entry_position_no_ == other.md_entry_position_no_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool MassDeleteOrdersMbO52Message::operator!=(const MassDeleteOrdersMbO52Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
