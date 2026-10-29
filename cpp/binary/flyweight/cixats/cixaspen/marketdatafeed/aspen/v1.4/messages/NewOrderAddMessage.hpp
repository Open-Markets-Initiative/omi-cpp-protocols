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
#include "../enums/Side.hpp"
#include "../common/Decimal.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// A new resting order added to the book
class NewOrderAddMessage {
  public:
    static constexpr const char* name = "NewOrderAddMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NewOrderAddMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NewOrderAddMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 50;
    static constexpr std::size_t fixed_size = 50;
    std::size_t encoded_size() const { return 50; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint16_t symbol_id() const { return wire::read_u16_le(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(10)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(18))); }

    Decimal quantity() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(19))), -6); }

    std::string_view symbol() const { return view::text(at(27), 11, ' '); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(38))), -6); }

    std::string_view broker() const { return view::text(at(46), 3, ' '); }

    char reserved_1() const { return wire::read_char(at(49)); }

    void print(std::ostream& out) const {
        out << "NewOrderAddMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << ", order_id=";
        out << order_id();
        out << ", side=";
        out << side();
        out << ", quantity=";
        out << quantity();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", price=";
        out << price();
        out << ", broker=";
        print::text(out, broker());
        out << ", reserved_1=";
        print::character(out, reserved_1());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NewOrderAddMessage& value) {
    value.print(out);
    return out;
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
