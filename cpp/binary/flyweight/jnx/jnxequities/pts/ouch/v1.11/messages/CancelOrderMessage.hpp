#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// A Cancel Order Message is used to request that an order be canceled
class CancelOrderMessage {
  public:
    static constexpr const char* name = "CancelOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CancelOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CancelOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint32_t order_token() const { return wire::read_u32_be(at(0)); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(4)); }

    void print(std::ostream& out) const {
        out << "CancelOrderMessage{";
        out << "order_token=";
        out << order_token();
        out << ", quantity=";
        out << quantity();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CancelOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
