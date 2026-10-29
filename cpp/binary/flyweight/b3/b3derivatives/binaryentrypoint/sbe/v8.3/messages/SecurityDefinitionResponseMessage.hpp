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
#include "../structs/OutboundBusinessHeader.hpp"
#include "../enums/SecurityResponseType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// SecurityDefinitionResponseMessage
class SecurityDefinitionResponseMessage {
  public:
    static constexpr const char* name = "SecurityDefinitionResponseMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityDefinitionResponseMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityDefinitionResponseMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 83;
    static constexpr std::size_t fixed_size = 83;
    std::size_t encoded_size() const { return 83; }

    OutboundBusinessHeader outbound_business_header() const { return OutboundBusinessHeader{ bytes_.subspan(0) }; }

    std::span<const std::byte, 2> offset_18_padding_2() const { return bytes_.subspan(18).template first<2>(); }

    std::uint64_t security_req_id() const { return wire::read_u64_le(at(20)); }

    std::optional<std::uint64_t> security_id_optional() const { return wire::nullable(wire::read_u64_le(at(28)), static_cast<std::uint64_t>(0ULL)); }

    SecurityResponseType security_response_type() const { return static_cast<SecurityResponseType>(wire::read_u8(at(36))); }

    std::string_view security_strategy_type() const { return view::text(at(37), 3, '\0'); }

    std::string_view symbol() const { return view::text(at(40), 20, '\0'); }

    std::uint64_t security_response_id() const { return wire::read_u64_le(at(60)); }

    std::string_view sender_location() const { return view::text(at(68), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(78), 5, '\0'); }

    void print(std::ostream& out) const {
        out << "SecurityDefinitionResponseMessage{";
        out << "outbound_business_header=";
        outbound_business_header().print(out);
        out << ", offset_18_padding_2=";
        print::hex(out, offset_18_padding_2().data(), offset_18_padding_2().size());
        out << ", security_req_id=";
        out << security_req_id();
        out << ", security_id_optional=";
        print::optional(out, security_id_optional());
        out << ", security_response_type=";
        out << security_response_type();
        out << ", security_strategy_type=";
        print::text(out, security_strategy_type());
        out << ", symbol=";
        print::text(out, symbol());
        out << ", security_response_id=";
        out << security_response_id();
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityDefinitionResponseMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
