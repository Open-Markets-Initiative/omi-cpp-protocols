#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../structs/QuoteReqId.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// QuoteCancelMessage
class QuoteCancelMessage {
  public:
    static constexpr const char* name = "QuoteCancelMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteCancelMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteCancelMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 59;
    std::size_t encoded_size() const { return memo_end(); }

    BidirectionalBusinessHeader bidirectional_business_header() const { return BidirectionalBusinessHeader{ bytes_.subspan(0) }; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(19)); }

    std::optional<std::uint64_t> quote_id_optional() const { return wire::nullable(wire::read_u64_le(at(27)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> account() const { return wire::nullable(wire::read_u32_le(at(35)), static_cast<std::uint32_t>(0ULL)); }

    std::string_view sender_location() const { return view::text(at(39), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(49), 5, '\0'); }

    std::string_view executing_trader() const { return view::text(at(54), 5, '\0'); }

    QuoteReqId quote_req_id() const { return QuoteReqId{ bytes_.subspan(59) }; }

    DeskId desk_id() const {
        wire::require("QuoteCancelMessage", quote_req_id_end() + DeskId::minimum_size, bytes_.size());
        return DeskId{ bytes_.subspan(quote_req_id_end()) };
    }

    Memo memo() const {
        wire::require("QuoteCancelMessage", desk_id_end() + Memo::minimum_size, bytes_.size());
        return Memo{ bytes_.subspan(desk_id_end()) };
    }

    void print(std::ostream& out) const {
        out << "QuoteCancelMessage{";
        out << "bidirectional_business_header=";
        bidirectional_business_header().print(out);
        out << ", security_id=";
        out << security_id();
        out << ", quote_id_optional=";
        print::optional(out, quote_id_optional());
        out << ", account=";
        print::optional(out, account());
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", executing_trader=";
        print::text(out, executing_trader());
        out << ", quote_req_id=";
        quote_req_id().print(out);
        out << ", desk_id=";
        desk_id().print(out);
        out << ", memo=";
        memo().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t quote_req_id_end() const { return 59 + quote_req_id().encoded_size(); }
    std::size_t desk_id_end() const { return quote_req_id_end() + desk_id().encoded_size(); }
    std::size_t memo_end() const { return desk_id_end() + memo().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteCancelMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
