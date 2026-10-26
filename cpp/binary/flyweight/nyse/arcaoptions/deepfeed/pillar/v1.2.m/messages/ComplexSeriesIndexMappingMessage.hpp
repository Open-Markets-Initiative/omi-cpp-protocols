#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketId.hpp"
#include "../groups/ComplexSeriesIndexMappingLeg.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Published over the real-time data channels at system startup or in the context of a refresh
// sequence. Provides referential data for a single specified options complex series.
class ComplexSeriesIndexMappingMessage {
  public:
    static constexpr const char* name = "ComplexSeriesIndexMappingMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexSeriesIndexMappingMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexSeriesIndexMappingMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    std::size_t encoded_size() const { return complex_series_index_mapping_leg_end(); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(0)); }

    MarketId market_id() const { return static_cast<MarketId>(wire::read_u16_le(at(4))); }

    std::uint8_t system_id() const { return wire::read_u8(at(6)); }

    std::uint16_t no_of_legs() const { return wire::read_u16_le(at(7)); }

    view::entries<ComplexSeriesIndexMappingLeg> complex_series_index_mapping_leg() const { return view::entries<ComplexSeriesIndexMappingLeg>{ bytes_.subspan(9), wire::count(no_of_legs()) }; }

    void print(std::ostream& out) const {
        out << "ComplexSeriesIndexMappingMessage{";
        out << "series_index=";
        out << series_index();
        out << ", market_id=";
        out << market_id();
        out << ", system_id=";
        out << static_cast<int>(system_id());
        out << ", no_of_legs=";
        out << no_of_legs();
        out << ", complex_series_index_mapping_leg=";
        print::sequence(out, complex_series_index_mapping_leg());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t complex_series_index_mapping_leg_end() const { return 9 + complex_series_index_mapping_leg().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexSeriesIndexMappingMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
