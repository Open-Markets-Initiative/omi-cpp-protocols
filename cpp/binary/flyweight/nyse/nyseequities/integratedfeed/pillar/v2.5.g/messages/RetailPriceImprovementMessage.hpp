#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RpiIndicator.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

// Published when RPI interest is added or removed between the best bid and best offer price.
class RetailPriceImprovementMessage {
  public:
    static constexpr const char* name = "RetailPriceImprovementMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RetailPriceImprovementMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RetailPriceImprovementMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::chrono::nanoseconds source_time_ns() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    RpiIndicator rpi_indicator() const { return static_cast<RpiIndicator>(wire::read_char(at(12))); }

    void print(std::ostream& out) const {
        out << "RetailPriceImprovementMessage{";
        out << "source_time_ns=";
        out << source_time_ns().count();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", rpi_indicator=";
        out << rpi_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RetailPriceImprovementMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
