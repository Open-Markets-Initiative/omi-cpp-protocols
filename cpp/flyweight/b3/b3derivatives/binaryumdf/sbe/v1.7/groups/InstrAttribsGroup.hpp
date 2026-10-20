#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/InstrAttribType.hpp"
#include "../enums/InstrAttribValue.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// noInstrAttribs
class InstrAttribsGroup {
  public:
    static constexpr const char* name = "InstrAttribsGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrAttribsGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrAttribsGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 2;
    static constexpr std::size_t fixed_size = 2;
    std::size_t encoded_size() const { return 2; }

    InstrAttribType instr_attrib_type() const { return static_cast<InstrAttribType>(wire::read_u8(at(0))); }

    InstrAttribValue instr_attrib_value() const { return static_cast<InstrAttribValue>(wire::read_u8(at(1))); }

    void print(std::ostream& out) const {
        out << "InstrAttribsGroup{";
        out << "instr_attrib_type=";
        out << instr_attrib_type();
        out << ", instr_attrib_value=";
        out << instr_attrib_value();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrAttribsGroup& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
