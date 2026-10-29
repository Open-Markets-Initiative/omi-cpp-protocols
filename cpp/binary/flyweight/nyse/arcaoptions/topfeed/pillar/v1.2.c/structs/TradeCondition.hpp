#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Series.hpp"
#include "../enums/Opening.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Trade Condition
class TradeCondition {
  public:
    static constexpr const char* name = "TradeCondition";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCondition(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCondition has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    Series series() const { return static_cast<Series>(wire::read_char(at(0))); }

    Opening opening() const { return static_cast<Opening>(wire::read_char(at(1))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(2).template first<1>(); }

    char offical() const { return wire::read_char(at(3)); }

    void print(std::ostream& out) const {
        out << "TradeCondition{";
        out << "series=";
        out << series();
        out << ", opening=";
        out << opening();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", offical=";
        print::character(out, offical());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCondition& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
