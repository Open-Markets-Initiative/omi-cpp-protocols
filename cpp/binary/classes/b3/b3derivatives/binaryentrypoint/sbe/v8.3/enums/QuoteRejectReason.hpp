#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// quoteRejectReason
enum class QuoteRejectReason : std::uint32_t {
    TechnicalErrorFunctionNotPerformed = 9999,                                                                    // Technical Error: Function not performed
    ExercisePriceNotAllowed = 8006,                                                                               // Exercise price not allowed
    NoPositionsBlocked = 8007,                                                                                    // No positions blocked
    QuantityDoesntMatchWithTheOriginalRequestQuantityOnOriginalRequestQuantityOnOriginalRequest = 8008,           // Quantity doesn't match with the original request [Quantity on original request: <quantity on original request>]
    ExerciseMustBeOnMaturityDate = 8011,                                                                          // Exercise must be on maturity date.
    FunctionNotAvailableThisTime = 8014,                                                                          // Function not available this time
    BlockingQuantityMoreThan999999999 = 8015,                                                                     // Blocking quantity more than 999999999
    TradeDoesNotBelongToTheSpecifiedFirmFirmIdXxx = 8020,                                                         // Trade does not belong to the specified firm ‘Firm Id: <XXX>’
    BlockingQtyMoreThanAvailableQuantity = 8021,                                                                  // Blocking qty more than available quantity
    ThereArentPositionsAvailableToExercise = 8022,                                                                // There aren't positions available to exercise
    TotalQtyMustBeTheSumOfAllAllocqty = 8023,                                                                     // Total qty must be the sum of all AllocQty
    TradeAlreadyCancelledOrDoesNotExistTradeIdXxx = 8024,                                                         // Trade already cancelled or does not exist ‘Trade Id: <XXX>’
    AvailableQuantityToBlockIsZero = 8027,                                                                        // Available quantity to block is zero
    InvalidOperationForContractType = 8028,                                                                       // Invalid Operation for contract type.
    FunctionClosedOrSuspended = 8036,                                                                             // Function closed or suspended.
    ExercisePriceOutsideRequiredMoneyness = 8039,                                                                 // Exercise price outside required moneyness.
    InvalidExerciseRequestIdToCancel = 8040,                                                                      // Invalid exercise request id to cancel
    InvalidBlockingIdToUnblock = 8059,                                                                            // Invalid blocking Id to unblock
    InvalidQuantityToUnblock = 8062,                                                                              // Invalid quantity to unblock
    OnBehalfOperationNotAllowedDuringCcrRecovery = 8063,                                                          // On Behalf Operation not allowed during CCR recovery
    ProblemParsingIncomingMessage = 8065,                                                                         // Problem parsing incoming message
    ExerciseQuantityShouldBeGreaterThanZero = 8066,                                                               // Exercise quantity should be greater than zero
    ContraryExerciseAlreadyRegisteredForThisPosition = 8069,                                                      // Contrary Exercise already registered for this position
    InthemoneyContractAllowsContraryExerciseToNotExerciseAutomaticallyOnly = 8070,                                // In-the-money contract allows Contrary Exercise to not exercise automatically only
    AtoutthemoneyContractAllowsContraryExerciseToExerciseAutomaticallyOnly = 8071,                                // At/Out-the-money contract allows Contrary Exercise to exercise automatically only
    DmaIsNotAllowedToRequestContraryExercise = 8072,                                                              // DMA is not allowed to request Contrary Exercise
    ContraryExercisesCanOnlyBeRequestedByDefaultLinkOrPositionOwnerWithDirectAccessOnAbsenceOfDefaultLink = 8073, // Contrary Exercises can only be requested by default link or position owner with direct access on absence of default link
    ContraryExerciseInvalidOperation = 8074,                                                                      // Contrary Exercise invalid operation.
    ThresholdMustNotBeInformed = 8075,                                                                            // Threshold must not be informed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteRejectReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteRejectReason value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
