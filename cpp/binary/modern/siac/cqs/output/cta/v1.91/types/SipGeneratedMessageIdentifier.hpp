#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Identifies CQS as the originator of a message
struct SipGeneratedMessageIdentifier {

    static constexpr auto name = "Sip Generated Message Identifier";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SipGeneratedMessageIdentifier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SipGeneratedMessageIdentifier(const char &value)
     : value{ value } {}

    // get value of SipGeneratedMessageIdentifier field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
