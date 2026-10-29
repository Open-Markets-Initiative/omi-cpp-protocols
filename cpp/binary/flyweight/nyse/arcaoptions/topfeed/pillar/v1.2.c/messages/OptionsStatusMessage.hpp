#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SeriesStatus.hpp"
#include "../enums/MarketState.hpp"
#include "../enums/HaltCondition.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// This message informs clients of changes in the status of a specific option outright series
// and complex series
class OptionsStatusMessage {
  public:
    static constexpr const char* name = "OptionsStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 19;
    static constexpr std::size_t fixed_size = 19;
    std::size_t encoded_size() const { return 19; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(12)); }

    SeriesStatus series_status() const { return static_cast<SeriesStatus>(wire::read_char(at(16))); }

    MarketState market_state() const { return static_cast<MarketState>(wire::read_char(at(17))); }

    HaltCondition halt_condition() const { return static_cast<HaltCondition>(wire::read_char(at(18))); }

    void print(std::ostream& out) const {
        out << "OptionsStatusMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", series_status=";
        out << series_status();
        out << ", market_state=";
        out << market_state();
        out << ", halt_condition=";
        out << halt_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
