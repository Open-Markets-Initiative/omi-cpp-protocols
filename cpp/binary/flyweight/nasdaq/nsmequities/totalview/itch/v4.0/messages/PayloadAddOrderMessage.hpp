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

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// This message will be generated for unattributed orders accepted by the NASDAQ system.
class PayloadAddOrderMessage {
  public:
    static constexpr const char* name = "PayloadAddOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadAddOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadAddOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 27;
    static constexpr std::size_t fixed_size = 27;
    std::size_t encoded_size() const { return 27; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t order_reference_number() const { return wire::read_u64_be(at(4)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(12))); }

    std::uint32_t shares() const { return wire::read_u32_be(at(13)); }

    std::string_view stock() const { return view::text(at(17), 6, ' '); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(23))), -4); }

    void print(std::ostream& out) const {
        out << "PayloadAddOrderMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_reference_number=";
        out << order_reference_number();
        out << ", side=";
        out << side();
        out << ", shares=";
        out << shares();
        out << ", stock=";
        print::text(out, stock());
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PayloadAddOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
