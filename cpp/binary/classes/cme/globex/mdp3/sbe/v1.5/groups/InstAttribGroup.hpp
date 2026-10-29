#pragma once

#include <cstddef>
#include <ostream>

#include "../bitfields/InstAttribValue.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// Number of repeating InstrAttribType entries
class InstAttribGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    InstAttribGroup() = default;
    InstAttribGroup(const InstAttribValue& inst_attrib_value);

    // Inst Attrib Value: InstAttribValue bit set
    const InstAttribValue& inst_attrib_value() const;
    InstAttribValue& inst_attrib_value();
    void set_inst_attrib_value(const InstAttribValue& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstAttribGroup& other) const;
    bool operator!=(const InstAttribGroup& other) const;

  private:
    InstAttribValue inst_attrib_value_{};
};

std::ostream& operator<<(std::ostream& out, const InstAttribGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_5
