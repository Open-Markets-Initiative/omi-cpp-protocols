// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: groups/RequestedMatchingEngine.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The trading session and sequence number the client asks of one matching engine, repeated
// once for each the login request counts
class RequestedMatchingEngine {
  public:
    static constexpr const char* name = "RequestedMatchingEngine";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RequestedMatchingEngine(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RequestedMatchingEngine has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::uint8_t requested_trading_session_id() const { return wire::read_u8(at(0)); }

    std::uint64_t requested_sequence_number() const { return wire::read_u64_le(at(1)); }

    void print(std::ostream& out) const {
        out << "RequestedMatchingEngine{";
        out << "requested_trading_session_id=";
        out << static_cast<int>(requested_trading_session_id());
        out << ", requested_sequence_number=";
        out << requested_sequence_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RequestedMatchingEngine& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
