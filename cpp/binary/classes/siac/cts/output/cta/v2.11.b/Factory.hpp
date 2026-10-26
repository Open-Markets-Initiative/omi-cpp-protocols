#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/AdministrativeMessagePayload.hpp"
#include "messages/ControlMessagePayload.hpp"
#include "messages/IndicesMessagePayload.hpp"
#include "messages/MarketStatusMessagePayload.hpp"
#include "messages/PriorDayMessagePayload.hpp"
#include "messages/SummaryMessagePayload.hpp"
#include "messages/TradeMessagePayload.hpp"

namespace siac::cts::output::cta::v2_11_b {

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

// Makes the message a Indices Message Type selects. A code the specification does
// not list makes an UnknownIndicesMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class IndicesMessagePayloadFactory {
  public:
    static std::unique_ptr<IndicesMessagePayload> create(IndicesMessagePayloadCode code);
};

// Makes the message a Market Status Message Type selects. A code the specification does
// not list makes an UnknownMarketStatusMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class MarketStatusMessagePayloadFactory {
  public:
    static std::unique_ptr<MarketStatusMessagePayload> create(MarketStatusMessagePayloadCode code);
};

// Makes the message a Prior Day Message Type selects. A code the specification does
// not list makes an UnknownPriorDayMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class PriorDayMessagePayloadFactory {
  public:
    static std::unique_ptr<PriorDayMessagePayload> create(PriorDayMessagePayloadCode code);
};

// Makes the message a Summary Message Type selects. A code the specification does
// not list makes an UnknownSummaryMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class SummaryMessagePayloadFactory {
  public:
    static std::unique_ptr<SummaryMessagePayload> create(SummaryMessagePayloadCode code);
};

// Makes the message a Trade Message Type selects. A code the specification does
// not list makes an UnknownTradeMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class TradeMessagePayloadFactory {
  public:
    static std::unique_ptr<TradeMessagePayload> create(TradeMessagePayloadCode code);
};

} // namespace siac::cts::output::cta::v2_11_b
