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

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Identifies a retail interest indication of the Bid, Ask or both the Bid and Ask for
// NASDAQ-listed securities.
class PayloadRetailInterestMessage {
  public:
    static constexpr const char* name = "PayloadRetailInterestMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadRetailInterestMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadRetailInterestMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 19;
    static constexpr std::size_t fixed_size = 19;
    std::size_t encoded_size() const { return 19; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }

    std::string_view stock() const { return view::text(at(10), 8, ' '); }

    InterestFlag interest_flag() const { return static_cast<InterestFlag>(wire::read_char(at(18))); }

    void print(std::ostream& out) const {
        out << "PayloadRetailInterestMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        out << timestamp().count();
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

inline std::ostream& operator<<(std::ostream& out, const PayloadRetailInterestMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
