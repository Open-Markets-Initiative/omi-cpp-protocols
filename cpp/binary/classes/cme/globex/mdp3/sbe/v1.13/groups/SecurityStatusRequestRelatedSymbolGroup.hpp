#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of instruments requested. When NoSecurityGroups > 0 specified in the request, the
// NoRelatedSym should be equal 0
class SecurityStatusRequestRelatedSymbolGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    SecurityStatusRequestRelatedSymbolGroup() = default;
    SecurityStatusRequestRelatedSymbolGroup(std::int32_t security_id);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SecurityStatusRequestRelatedSymbolGroup& other) const;
    bool operator!=(const SecurityStatusRequestRelatedSymbolGroup& other) const;

  private:
    std::int32_t security_id_{};
};

std::ostream& operator<<(std::ostream& out, const SecurityStatusRequestRelatedSymbolGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
