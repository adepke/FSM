# FSM
Collection of Finite State Machine Implementations

Inspired by Mateusz Pusz's [CppCon 2018 talk](https://www.youtube.com/watch?v=gKbORJtnVu8).

## Implementations
### Single Dispatch
  Minimalistic lightweight implementation of a FSM where events do not store any data. This uses a single dynamic dispatch approach.
  
### Double Dispatch
  Classic FSM which uses two dynamic dispatches, enabling events to store internal data.
  
### Variant
  Static polymorphism approach which does not use any dynamic dispatching. Events are still able to hold internal data.
