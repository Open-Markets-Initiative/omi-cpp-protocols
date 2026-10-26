#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace siac::opra::output::obi::v6_2 {

// Control Message
class ControlMessage {
  public:
    static constexpr const char* name = "ControlMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ControlMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ControlMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    char message_indicator() const { return wire::read_char(at(0)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(1)); }

    std::uint32_t participant_reference_number() const { return wire::read_u32_be(at(5)); }

    void print(std::ostream& out) const {
        out << "ControlMessage{";
        out << "message_indicator=";
        print::character(out, message_indicator());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ControlMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
