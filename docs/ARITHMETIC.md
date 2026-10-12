# Arithmetic Model

The current arithmetic abstraction works over signed decimal accumulator values using a fixed ten-digit magnitude range. Arithmetic results are normalized into the configured decimal range and overflow is exposed through result metadata.

The model is intentionally explicit about its simplifications. It does not attempt to emulate electrical pulse propagation, tube-level timing, or every historical special case. Future arithmetic modules should make sign handling, carry behavior, and overflow semantics testable and document the archival basis for each behavior.
