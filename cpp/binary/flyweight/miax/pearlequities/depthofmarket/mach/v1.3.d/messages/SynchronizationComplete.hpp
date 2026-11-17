// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/SynchronizationComplete.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// The ESesM server sends a Synchronization complete packet when it is done replaying all the
// old packets and is ready to start sending new packets from the Matching Engine
class SynchronizationComplete {
  public:
    static constexpr const char* name = "SynchronizationComplete";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SynchronizationComplete(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SynchronizationComplete has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t matching_engine_id() const { return wire::read_u8(at(0)); }

    void print(std::ostream& out) const {
        out << "SynchronizationComplete{";
        out << "matching_engine_id=";
        out << static_cast<int>(matching_engine_id());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SynchronizationComplete& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
