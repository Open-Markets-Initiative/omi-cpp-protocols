#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Repo Sub Security Type
struct RepoSubType {

    static constexpr auto name = "Repo Sub Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr RepoSubType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RepoSubType(const std::uint8_t &value)
     : value{ value } {}

    // get value of RepoSubType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
