# axi_transacion_timer

A simple Vivado IP package designed to measure clock periods between write and read AXI operations at specified addresses.

## Register map

#### STATUS
- Address: 0x00

|  Bit | Field   | Reset| Type | Description|
|------|---------|------|------|------------|
| 31-5 | Reserved| 0    | RW   | Unused.    |
|  4   | OVERFLOW| 0    | R    | Overflow flag. Set if the current overflows. Cleared when a new detection of START_ADDRESS occurs (if ENABLE is set).|
|  3   |  VALID  | 0    | R    | Valid flag. Set after TIME_COUNT is written. Cleared when a new detection of START_ADDRESS occurs (if ENABLE is set).|
|  2   |  WAITING| 0    | R    | Waiting flag. Set only when waiting for START_ADDRESS |
|  1   |  BUSY   | 0    | R    | Busy flag. Set when a count is running or waiting for START_ADDRESS.|
|  0   |  ENABLE | 0    | W    | Enables the internal FSM. Cannot be cleared if the IP is counting |


#### TIME_COUNT
- Address: 0x04

|  Bit   | Field      | Reset| Type | Description|
|--------|------------|------|------|------------|
|  31-0  | TIME_COUNT |  0   | R    | Last count value. Written one cycle after a read at STOP_ADDRESS is detected.|

#### START_ADDRESS
- Address: 0x08

|  Bit   | Field      | Reset| Type | Description|
|--------|------------|------|------|------------|
|  31-0  | START_ADDR |  0   | RW   | The desired start address for counting. If ENABLE is set, an AXI write operation at START_ADDRESS will trigger the count.|

#### STOP_ADDRESS
- Address: 0x0C

|  Bit   | Field      | Reset| Type | Description|
|--------|------------|------|------|------------|
|  31-0  | STOP_ADDR  |  0   | RW   | The desired stop address for counting. If ENABLE is set, an AXI read operation at STOP_ADDRESS will stop the count and write the count in the TIME_COUNT register.|

#### Notes:
- RW: Read/Write.
- R: Read only.
- W: Write only.
