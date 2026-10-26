#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NegotiationResponse
class ServerPayloadNegotiationResponse {
  public:
    static constexpr const char* name = "ServerPayloadNegotiationResponse";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadNegotiationResponse(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadNegotiationResponse has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 22;
    static constexpr std::size_t fixed_size = 22;
    std::size_t encoded_size() const { return 22; }

    std::uint64_t uuid() const { return wire::read_u64_le(at(0)); }

    std::chrono::nanoseconds request_timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    std::optional<std::uint16_t> secret_key_secure_id_expiration() const { return wire::nullable(wire::read_u16_le(at(16)), static_cast<std::uint16_t>(65535ULL)); }

    std::span<const std::byte, 4> padding_4() const { return bytes_.subspan(18).template first<4>(); }

    void print(std::ostream& out) const {
        out << "ServerPayloadNegotiationResponse{";
        out << "uuid=";
        out << uuid();
        out << ", request_timestamp=";
        out << request_timestamp().count();
        out << ", secret_key_secure_id_expiration=";
        print::optional(out, secret_key_secure_id_expiration());
        out << ", padding_4=";
        print::hex(out, padding_4().data(), padding_4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadNegotiationResponse& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
