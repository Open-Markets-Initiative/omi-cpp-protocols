#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../enums/RefMsgType.hpp"
#include "../structs/Memo.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// BusinessMessageRejectMessage
class BusinessMessageRejectMessage {
  public:
    static constexpr const char* name = "BusinessMessageRejectMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BusinessMessageRejectMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BusinessMessageRejectMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    std::size_t encoded_size() const { return text_end(); }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    RefMsgType ref_msg_type() const { return static_cast<RefMsgType>(wire::read_u8(at(18))); }

    std::span<const std::byte, 1> offset_19_padding_1() const { return bytes_.subspan(19).template first<1>(); }

    std::uint32_t ref_seq_num() const { return wire::read_u32_le(at(20)); }

    std::optional<std::uint64_t> business_reject_ref_id() const { return wire::nullable(wire::read_u64_le(at(24)), static_cast<std::uint64_t>(0ULL)); }

    std::uint32_t business_reject_reason() const { return wire::read_u32_le(at(32)); }

    Memo memo() const { return Memo{ bytes_.subspan(36) }; }

    Text text() const {
        wire::require("BusinessMessageRejectMessage", memo_end() + Text::minimum_size, bytes_.size());
        return Text{ bytes_.subspan(memo_end()) };
    }

    void print(std::ostream& out) const {
        out << "BusinessMessageRejectMessage{";
        out << "outbound_business_header=";
        outbound_business_header().print(out);
        out << ", ref_msg_type=";
        out << ref_msg_type();
        out << ", offset_19_padding_1=";
        print::hex(out, offset_19_padding_1().data(), offset_19_padding_1().size());
        out << ", ref_seq_num=";
        out << ref_seq_num();
        out << ", business_reject_ref_id=";
        print::optional(out, business_reject_ref_id());
        out << ", business_reject_reason=";
        out << business_reject_reason();
        out << ", memo=";
        memo().print(out);
        out << ", text=";
        text().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t memo_end() const { return 36 + memo().encoded_size(); }
    std::size_t text_end() const { return memo_end() + text().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BusinessMessageRejectMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
