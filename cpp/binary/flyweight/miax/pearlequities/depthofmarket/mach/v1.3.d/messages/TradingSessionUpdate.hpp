// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/TradingSessionUpdate.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The ESesM server sends a Trading Session Update packet to inform the client that a new
// trading session is starting on the specified Matching Engine
class TradingSessionUpdate {
  public:
    static constexpr const char* name = "TradingSessionUpdate";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingSessionUpdate(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingSessionUpdate has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 2;
    static constexpr std::size_t fixed_size = 2;
    std::size_t encoded_size() const { return 2; }

    std::uint8_t matching_engine_id() const { return wire::read_u8(at(0)); }

    std::uint8_t trading_session_id() const { return wire::read_u8(at(1)); }

    void print(std::ostream& out) const {
        out << "TradingSessionUpdate{";
        out << "matching_engine_id=";
        out << static_cast<int>(matching_engine_id());
        out << ", trading_session_id=";
        out << static_cast<int>(trading_session_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingSessionUpdate& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
