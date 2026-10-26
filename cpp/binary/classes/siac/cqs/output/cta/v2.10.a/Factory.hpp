#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/AdministrativeMessagePayload.hpp"
#include "messages/ControlMessagePayload.hpp"
#include "messages/MarketStatusMessagePayload.hpp"
#include "messages/QuoteMessagePayload.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// Makes the message a Message Category selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Administrative Message Type selects. A code the specification does
// not list makes an UnknownAdministrativeMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class AdministrativeMessagePayloadFactory {
  public:
    static std::unique_ptr<AdministrativeMessagePayload> create(AdministrativeMessagePayloadCode code);
};

// Makes the message a Control Message Type selects. A code the specification does
// not list makes an UnknownControlMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class ControlMessagePayloadFactory {
  public:
    static std::unique_ptr<ControlMessagePayload> create(ControlMessagePayloadCode code);
};

// Makes the message a Market Status Message Type selects. A code the specification does
// not list makes an UnknownMarketStatusMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class MarketStatusMessagePayloadFactory {
  public:
    static std::unique_ptr<MarketStatusMessagePayload> create(MarketStatusMessagePayloadCode code);
};

// Makes the message a Quote Message Type selects. A code the specification does
// not list makes an UnknownQuoteMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class QuoteMessagePayloadFactory {
  public:
    static std::unique_ptr<QuoteMessagePayload> create(QuoteMessagePayloadCode code);
};

} // namespace siac::cqs::output::cta::v2_10_a
