#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TimeInForce.hpp"
#include "../enums/Display.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// A Replace Order Message is used to modify an existing order
class ReplaceOrderMessage {
  public:
    static constexpr const char* name = "ReplaceOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ReplaceOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ReplaceOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::uint32_t existing_order_token() const { return wire::read_u32_be(at(0)); }

    std::uint32_t replacement_order_token() const { return wire::read_u32_be(at(4)); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(8)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(12))), -1); }

    TimeInForce time_in_force() const { return static_cast<TimeInForce>(wire::read_u32_be(at(16))); }

    Display display() const { return static_cast<Display>(wire::read_char(at(20))); }

    std::uint32_t minimum_quantity() const { return wire::read_u32_be(at(21)); }

    void print(std::ostream& out) const {
        out << "ReplaceOrderMessage{";
        out << "existing_order_token=";
        out << existing_order_token();
        out << ", replacement_order_token=";
        out << replacement_order_token();
        out << ", quantity=";
        out << quantity();
        out << ", price=";
        out << price();
        out << ", time_in_force=";
        out << time_in_force();
        out << ", display=";
        out << display();
        out << ", minimum_quantity=";
        out << minimum_quantity();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ReplaceOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
