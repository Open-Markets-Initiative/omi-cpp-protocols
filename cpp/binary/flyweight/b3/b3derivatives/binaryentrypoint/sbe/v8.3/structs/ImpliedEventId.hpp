// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: structs/ImpliedEventId.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// ExecutionReport_TradeMessage
class ImpliedEventId {
  public:
    static constexpr const char* name = "ImpliedEventId";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ImpliedEventId(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ImpliedEventId has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 6;
    static constexpr std::size_t fixed_size = 6;
    std::size_t encoded_size() const { return 6; }

    std::optional<std::uint32_t> event_id() const { return wire::nullable(wire::read_u32_le(at(0)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint16_t> no_related_trades() const { return wire::nullable(wire::read_u16_le(at(4)), static_cast<std::uint16_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "ImpliedEventId{";
        out << "event_id=";
        print::optional(out, event_id());
        out << ", no_related_trades=";
        print::optional(out, no_related_trades());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ImpliedEventId& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
