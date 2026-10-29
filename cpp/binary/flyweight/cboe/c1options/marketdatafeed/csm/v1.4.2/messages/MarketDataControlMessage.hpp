#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MdControlType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Market Data Control messages mark the start and end of the end of session Summary and the
// end of session Settlement data transmissions.
class MarketDataControlMessage {
  public:
    static constexpr const char* name = "MarketDataControlMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketDataControlMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketDataControlMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    MdControlType md_control_type() const { return static_cast<MdControlType>(wire::read_u8(at(0))); }

    void print(std::ostream& out) const {
        out << "MarketDataControlMessage{";
        out << "md_control_type=";
        out << md_control_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketDataControlMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
