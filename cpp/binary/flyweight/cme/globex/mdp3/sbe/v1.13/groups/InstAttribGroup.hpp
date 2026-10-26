#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/InstAttribValue.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of repeating InstrAttribType entries
class InstAttribGroup {
  public:
    static constexpr const char* name = "InstAttribGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstAttribGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstAttribGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    InstAttribValue inst_attrib_value() const { return InstAttribValue{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "InstAttribGroup{";
        out << "inst_attrib_value=";
        inst_attrib_value().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstAttribGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
