#include "BusinessMessageRejectMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

BusinessMessageRejectMessage::BusinessMessageRejectMessage(const OutboundBusinessHeader& outbound_business_header, RefMsgType ref_msg_type, const std::array<std::byte, 1>& offset_19_padding_1, std::uint32_t ref_seq_num, std::optional<std::uint64_t> business_reject_ref_id, std::uint32_t business_reject_reason, const Memo& memo, const Text& text)
  : outbound_business_header_(outbound_business_header), ref_msg_type_(ref_msg_type), offset_19_padding_1_(offset_19_padding_1), ref_seq_num_(ref_seq_num), business_reject_ref_id_(business_reject_ref_id), business_reject_reason_(business_reject_reason), memo_(memo), text_(text) {}

const OutboundBusinessHeader& BusinessMessageRejectMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& BusinessMessageRejectMessage::outbound_business_header() { return outbound_business_header_; }
void BusinessMessageRejectMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

RefMsgType BusinessMessageRejectMessage::ref_msg_type() const { return ref_msg_type_; }
void BusinessMessageRejectMessage::set_ref_msg_type(RefMsgType value) { ref_msg_type_ = value; }

const std::array<std::byte, 1>& BusinessMessageRejectMessage::offset_19_padding_1() const { return offset_19_padding_1_; }
std::array<std::byte, 1>& BusinessMessageRejectMessage::offset_19_padding_1() { return offset_19_padding_1_; }
void BusinessMessageRejectMessage::set_offset_19_padding_1(const std::array<std::byte, 1>& value) { offset_19_padding_1_ = value; }

std::uint32_t BusinessMessageRejectMessage::ref_seq_num() const { return ref_seq_num_; }
void BusinessMessageRejectMessage::set_ref_seq_num(std::uint32_t value) { ref_seq_num_ = value; }

std::optional<std::uint64_t> BusinessMessageRejectMessage::business_reject_ref_id() const { return business_reject_ref_id_; }
void BusinessMessageRejectMessage::set_business_reject_ref_id(std::optional<std::uint64_t> value) { business_reject_ref_id_ = value; }

std::uint32_t BusinessMessageRejectMessage::business_reject_reason() const { return business_reject_reason_; }
void BusinessMessageRejectMessage::set_business_reject_reason(std::uint32_t value) { business_reject_reason_ = value; }

const Memo& BusinessMessageRejectMessage::memo() const { return memo_; }
Memo& BusinessMessageRejectMessage::memo() { return memo_; }
void BusinessMessageRejectMessage::set_memo(const Memo& value) { memo_ = value; }

const Text& BusinessMessageRejectMessage::text() const { return text_; }
Text& BusinessMessageRejectMessage::text() { return text_; }
void BusinessMessageRejectMessage::set_text(const Text& value) { text_ = value; }

MessageCode BusinessMessageRejectMessage::type() const { return message_type; }

std::string_view BusinessMessageRejectMessage::name() const { return "Business Message Reject Message"; }

std::size_t BusinessMessageRejectMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("BusinessMessageRejectMessage", offset + 1, length);
    ref_msg_type_ = static_cast<RefMsgType>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("BusinessMessageRejectMessage", offset + 1, length);
    wire::read_bytes(data + offset, offset_19_padding_1_.data(), 1);
    offset += 1;

    wire::require("BusinessMessageRejectMessage", offset + 4, length);
    ref_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("BusinessMessageRejectMessage", offset + 8, length);
    business_reject_ref_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("BusinessMessageRejectMessage", offset + 4, length);
    business_reject_reason_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += memo_.decode(data + offset, length - offset);

    offset += text_.decode(data + offset, length - offset);

    return offset;
}

std::size_t BusinessMessageRejectMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BusinessMessageRejectMessage", encoded_size(), capacity);

    offset += outbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(ref_msg_type_));
    offset += 1;

    wire::write_bytes(data + offset, offset_19_padding_1_.data(), 1);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ref_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, business_reject_ref_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(business_reject_reason_));
    offset += 4;

    offset += memo_.encode(data + offset, capacity - offset);

    offset += text_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t BusinessMessageRejectMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 1 + 1 + 4 + 8 + 4 + memo_.encoded_size() + text_.encoded_size();
}

void BusinessMessageRejectMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> BusinessMessageRejectMessage::clone() const {
    return std::make_unique<BusinessMessageRejectMessage>(*this);
}

void BusinessMessageRejectMessage::print(std::ostream& out) const {
    out << "BusinessMessageRejectMessage{";
    out << "outbound_business_header=";
    outbound_business_header_.print(out);
    out << ", ref_msg_type=";
    out << ref_msg_type_;
    out << ", offset_19_padding_1=";
    print::hex(out, offset_19_padding_1_.data(), offset_19_padding_1_.size());
    out << ", ref_seq_num=";
    out << ref_seq_num_;
    out << ", business_reject_ref_id=";
    print::optional(out, business_reject_ref_id_);
    out << ", business_reject_reason=";
    out << business_reject_reason_;
    out << ", memo=";
    memo_.print(out);
    out << ", text=";
    text_.print(out);
    out << '}';
}

bool BusinessMessageRejectMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const BusinessMessageRejectMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool BusinessMessageRejectMessage::operator==(const BusinessMessageRejectMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && ref_msg_type_ == other.ref_msg_type_
        && offset_19_padding_1_ == other.offset_19_padding_1_
        && ref_seq_num_ == other.ref_seq_num_
        && business_reject_ref_id_ == other.business_reject_ref_id_
        && business_reject_reason_ == other.business_reject_reason_
        && memo_ == other.memo_
        && text_ == other.text_;
}

bool BusinessMessageRejectMessage::operator!=(const BusinessMessageRejectMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
