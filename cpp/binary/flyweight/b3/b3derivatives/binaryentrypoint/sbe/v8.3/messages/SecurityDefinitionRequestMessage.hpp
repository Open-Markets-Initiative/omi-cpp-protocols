#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../structs/LegsGroups.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// SecurityDefinitionRequestMessage
class SecurityDefinitionRequestMessage {
  public:
    static constexpr const char* name = "SecurityDefinitionRequestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityDefinitionRequestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityDefinitionRequestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 41;
    std::size_t encoded_size() const { return legs_groups_end(); }

    InboundBusinessHeader inbound_business_header() const { return InboundBusinessHeader{ bytes_.subspan(0) }; }

    std::uint64_t security_req_id() const { return wire::read_u64_le(at(18)); }

    std::string_view sender_location() const { return view::text(at(26), 10, '\0'); }

    std::string_view entering_trader() const { return view::text(at(36), 5, '\0'); }

    LegsGroups legs_groups() const { return LegsGroups{ bytes_.subspan(41) }; }

    void print(std::ostream& out) const {
        out << "SecurityDefinitionRequestMessage{";
        out << "inbound_business_header=";
        inbound_business_header().print(out);
        out << ", security_req_id=";
        out << security_req_id();
        out << ", sender_location=";
        print::text(out, sender_location());
        out << ", entering_trader=";
        print::text(out, entering_trader());
        out << ", legs_groups=";
        legs_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t legs_groups_end() const { return 41 + legs_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityDefinitionRequestMessage& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
