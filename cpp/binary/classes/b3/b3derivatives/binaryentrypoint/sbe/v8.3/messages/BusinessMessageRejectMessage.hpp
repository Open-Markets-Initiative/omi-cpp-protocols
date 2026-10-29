#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/RefMsgType.hpp"
#include "../messages/Message.hpp"
#include "../structs/Memo.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

class Visitor;

// BusinessMessageRejectMessage
class BusinessMessageRejectMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::BusinessMessageRejectMessage;

    BusinessMessageRejectMessage() = default;
    BusinessMessageRejectMessage(const OutboundBusinessHeader& outbound_business_header, RefMsgType ref_msg_type, const std::array<std::byte, 1>& offset_19_padding_1, std::uint32_t ref_seq_num, std::optional<std::uint64_t> business_reject_ref_id, std::uint32_t business_reject_reason, const Memo& memo, const Text& text);

    // Outbound Business Header: OutboundBusinessHeader
    const OutboundBusinessHeader& outbound_business_header() const;
    OutboundBusinessHeader& outbound_business_header();
    void set_outbound_business_header(const OutboundBusinessHeader& value);

    // Ref Msg Type: refMsgType
    RefMsgType ref_msg_type() const;
    void set_ref_msg_type(RefMsgType value);

    // Offset 19 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_19_padding_1() const;
    std::array<std::byte, 1>& offset_19_padding_1();
    void set_offset_19_padding_1(const std::array<std::byte, 1>& value);

    // Ref Seq Num: refSeqNum
    std::uint32_t ref_seq_num() const;
    void set_ref_seq_num(std::uint32_t value);

    // Business Reject Ref Id: businessRejectRefID
    std::optional<std::uint64_t> business_reject_ref_id() const;
    void set_business_reject_ref_id(std::optional<std::uint64_t> value);

    // Business Reject Reason: businessRejectReason
    std::uint32_t business_reject_reason() const;
    void set_business_reject_reason(std::uint32_t value);

    // Memo: memo data struct
    const Memo& memo() const;
    Memo& memo();
    void set_memo(const Memo& value);

    // Text: text data struct
    const Text& text() const;
    Text& text();
    void set_text(const Text& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const BusinessMessageRejectMessage& other) const;
    bool operator!=(const BusinessMessageRejectMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    RefMsgType ref_msg_type_{};
    std::array<std::byte, 1> offset_19_padding_1_{};
    std::uint32_t ref_seq_num_{};
    std::optional<std::uint64_t> business_reject_ref_id_{};
    std::uint32_t business_reject_reason_{};
    Memo memo_{};
    Text text_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
