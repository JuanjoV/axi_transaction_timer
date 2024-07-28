# axi_transacion_timer

A simple Vivado IP package intended for measuring clock periods between write and read AXI operations at given addresses.

## Register map

#### STATUS
- Address: 0x00

|  Bit | Field   | Reset| Type | Description|
|------|---------|------|------|------------|
| 31-5 | Reserved| 0    | WR   | Unused.    |
|  4   | OVERFLOW| 0    | R    | Overflow flag. Set if the current is overflowed. If ENABLE flag is set, it is cleared every new dectection of START_ADDRESS.|
|  3   |  VALID  | 0    | R    | Valid flag. Set after TIME_COUNT is written. If ENABLE flag is set, it is cleared every new dectection of START_ADDRESS.|
|  2   |  WAITING| 0    | R    | Waiting flag. Set only when is waiting for START_ADDRESS |
|  1   |  BUSY   | 0    | R    | Busy flag. Set when a count is running or waiting for START_ADDRESS.|
|  0   |  ENABLE |0     | W    | Enables the internal FSM.Can't be clear if the IP is counting |


#### TIME_COUNT
- Address: 0x04

|  Bit   | Field      | Reset| Type | Description|
|--------|------------|------|------|------------|
|  31-0  | TIME_COUNT |  0   | R    | Last count value. It is written one cycle after a read at STOP_ADDRESS is detected.|

#### START_ADDRESS
- Address: 0x08

|  Bit   | Field      | Reset| Type | Description|
|--------|------------|------|------|------------|
|  31-0  | START_ADDR |  0   | RW   | The desired start address for counting. If ENABLE is set, an AXI write operation at START_ADDRESS will trigger the count.|

#### STOP_ADDRESS
- Address: 0x0C

|  Bit   | Field      | Reset| Type | Description|
|--------|------------|------|------|------------|
|  31-0  | STOP_ADDR  |  0   | RW   | The desired stop address for counting. If ENABLE is set, an AXI read operation at STOP_ADDRESS will stop the count and write its result in TIME_COUNT register.|