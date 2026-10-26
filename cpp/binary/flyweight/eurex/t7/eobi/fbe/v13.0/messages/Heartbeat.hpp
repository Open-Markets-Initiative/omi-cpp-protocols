#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

class Heartbeat {
  public:
    static constexpr const char* name = "Heartbeat";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Heartbeat(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Heartbeat has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::optional<std::uint32_t> last_msg_seq_num_processed() const { return wire::nullable(wire::read_u32_le(at(0)), static_cast<std::uint32_t>(0xFFFFFFFFULL)); }

    std::span<const std::byte, 4> pad4() const { return bytes_.subspan(4).template first<4>(); }

    void print(std::ostream& out) const {
        out << "Heartbeat{";
        out << "last_msg_seq_num_processed=";
        print::optional(out, last_msg_seq_num_processed());
        out << ", pad4=";
        print::hex(out, pad4().data(), pad4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Heartbeat& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
