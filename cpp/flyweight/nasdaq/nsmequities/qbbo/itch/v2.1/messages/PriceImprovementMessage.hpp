#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/InterestFlag.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Indicates a retail interest indication of the Bid, Ask or both the Bid and Ask for
// Nasdaq-listed securities.
class PriceImprovementMessage {
  public:
    static constexpr const char* name = "PriceImprovementMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PriceImprovementMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PriceImprovementMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::uint16_t tracking() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds time_stamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::string_view stock() const { return view::text(at(8), 8, ' '); }

    InterestFlag interest_flag() const { return static_cast<InterestFlag>(wire::read_char(at(16))); }

    void print(std::ostream& out) const {
        out << "PriceImprovementMessage{";
        out << "tracking=";
        out << tracking();
        out << ", time_stamp=";
        out << time_stamp().count();
        out << ", stock=";
        print::text(out, stock());
        out << ", interest_flag=";
        out << interest_flag();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PriceImprovementMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
