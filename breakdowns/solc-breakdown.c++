// Contract creation code
// 0x608060405234801561000f575f80fd5b506101438061001d5f395ff3

// Runtime code
// fe608060405234801561000f575f80fd5b5060043610610034575f3560e01c8063cdfead2e14610038578063e026c01714610054575b5f80fd5b610052600480360381019061004d91906100ba565b610072565b005b61005c61007b565b60405161006991906100f4565b60405180910390f35b805f8190555050565b5f8054905090565b5f80fd5b5f819050919050565b61009981610087565b81146100a3575f80fd5b50565b5f813590506100b481610090565b92915050565b5f602082840312156100cf576100ce610083565b5b5f6100dc848285016100a6565b91505092915050565b6100ee81610087565b82525050565b5f6020820190506101075f8301846100e5565b9291505056

// Metdata
// fea2646970667358221220462de7c464d866cf54830a1f9828d5b7fe11fe99903e05798aabbb7d0dfbc95864736f6c63430008140033

// 3 sections
// 1. Contract Creation
// 2. Runtime
// 3. Metadata

// 1. Contract Creation Code
// Free Memory Pointer
PUSH1 0x80      // [0x80]
PUSH1 0x40      // [0x40, 0x80]
MSTORE          // [] // Memory 0x40 -> 0x80

// What's this chunk do??
// If someone sent value eth this call revert!!
// Otherwise, jump, to continue execution
CALLVALUE       // [msg.sender]
DUP1            // [msg.sender, msg.sender]
ISZERO          // [msg.sender == 0, msg.sender]
PUSH2 0x000f    // [0x000f, msg.sender == 0, msg.sender]
JUMPI           // [msg.sender]
PUSH0           // [0x00, msg.sender]
DUP1            // [0x00, 0x00, msg.sender]
REVERT          // [msg.sender]

// Jump dest if msg.sender == 0
// Sticks the runtime code on chain
JUMPDEST        // [msg.sender]
POP             // []
PUSH2 0x0143    // [0x0143]
DUP1            // [0x0143, 0x0143]
PUSH2 0x001d    // [0x001d, 0x0143, 0x0143]
PUSH0           // [0x00, 0x001d, 0x0143, 0x0143]
CODECOPY        // [0x05]       // Memory: [runtime code]
PUSH0           // [0x00, 0x0143]
RETURN          // []
INVALID         // []

// 2. Runtime Code
// Entry point of all calls
// 
PUSH1 0x80
PUSH1 0x40
MSTORE

// Checking for msg.value, and if given, reverting
CALLVALUE       // [msg.value]
DUP1            // [msg.value, msg.value]
ISZERO          // [msg.value == 0, msg.value]
PUSH2 0x000f    // [0x000f, msg.value == 0, msg.value]   
JUMPI           // [msg.value]
// Jump to "continue!" if msg.value == 0

PUSH0           // [0x00, msg.value]
DUP1            // [0x00, 0x00, msg.value]
REVERT          // [msg.value]

// If msg.value == 0, start here!
// continue!
JUMPDEST        // [msg.value]
POP             // []
PUSH1 0x04      // [0x04]
CALLDATASIZE    // [calldata_size, 0x04]
LT              // [calldata_size < 0x04]
PUSH2 0x0034    // [0x0034, calldata_size < 0x04]
JUMPI           // []
// if calldata_size < 0x04 -> calldata_jump

// function dispatching in solidity!
PUSH0           // [0]
CALLDATALOAD    // [32bytes of calldata] 
PUSH1 0xe0      // [0xe0, 32bytes of calldata]
SHR             // [calldata[0:4]] // function_selector

// dispathching for setNumberOfHorses
DUP1            // [function_selector, function_selector]
PUSH4 0xcdfead2e// [0xcdfead2e, function_selector, function_selector]
EQ              // [function_selector == 0xcdfead2e, function_selector]
PUSH2 0x0038    // [0x0038, function_selector == 0xcdfead2e, function_selector]
JUMPI           // [function_selector]
// if function_selector == 0xcdfead2e -> set_nember_of_horses

// function dispatching for readNumberOfHorses
DUP1            // [function_selector, function_selector]
PUSH4 0xe026c017// [0xe026c017, function_selector, function_selector]
EQ              // [function_selector == 0xe026c017, function_selector]
PUSH2 0x0054    // [0x0054, function_selector == 0xe026c017, function_selector]
JUMPI           // [function_selector]
// if function_selector == 0xe026c017 -> get_nember_of_horse

// calldata_jump
// revert Jumpdest
JUMPDEST        // []
PUSH0           // [0]
DUP1            // [0, 0]
REVERT          // []

// updateHorseNumber jump dest 1
JUMPDEST        // [function_selector]
PUSH2 0x0052    // [0x0052, function_selector]
PUSH1 0x04      // [0xx04, 0x0052, function_selector]
DUP1            // [0x04, 0xx04, 0x0052, function_selector]
CALLDATASIZE    // [calldata_size, 0x04, 0xx04, 0x0052, function_selector]
SUB             // []
DUP2
ADD
SWAP1
PUSH2 0x004d
SWAP2
SWAP1
PUSH2 0x00ba
JUMP
JUMPDEST
PUSH2 0x0072
JUMP
JUMPDEST
STOP
JUMPDEST
PUSH2 0x005c
PUSH2 0x007b
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
PUSH2 0x0069
SWAP2
SWAP1
PUSH2 0x00f4
JUMP

JUMPDEST
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN

// updateHorseNumber jump dest 2
// Check to see if there is a value to update the horse number to
// 4 bytes for function selector, 32bytes for horse number
JUMPDEST
DUP1
PUSH0
DUP2
SWAP1
SSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
DUP1
SLOAD
SWAP1
POP
SWAP1
JUMP
JUMPDEST
PUSH0
DUP1
REVERT
JUMPDEST
PUSH0
DUP2
SWAP1
POP
SWAP2
SWAP1
POP
JUMP
JUMPDEST
PUSH2 0x0099
DUP2
PUSH2 0x0087
JUMP
JUMPDEST
DUP2
EQ
PUSH2 0x00a3
JUMPI
PUSH0
DUP1
REVERT
JUMPDEST
POP
JUMP
JUMPDEST
PUSH0
DUP2
CALLDATALOAD
SWAP1
POP
PUSH2 0x00b4
DUP2
PUSH2 0x0090
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
DUP5
SUB
SLT
ISZERO
PUSH2 0x00cf
JUMPI
PUSH2 0x00ce
PUSH2 0x0083
JUMP
JUMPDEST
JUMPDEST
PUSH0
PUSH2 0x00dc
DUP5
DUP3
DUP6
ADD
PUSH2 0x00a6
JUMP
JUMPDEST
SWAP2
POP
POP
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH2 0x00ee
DUP2
PUSH2 0x0087
JUMP
JUMPDEST
DUP3
MSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
ADD
SWAP1
POP
PUSH2 0x0107
PUSH0
DUP4
ADD
DUP5
PUSH2 0x00e5
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP

// 3. Metadata
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
CHAINID
INVALID
INVALID
INVALID
PUSH5 0xd866cf5483
EXP
INVALID
SWAP9
INVALID
INVALID
INVALID
INVALID
GT
INVALID
SWAP10
SWAP1
RETURNDATACOPY
SDIV
PUSH26 0x8aabbb7d0dfbc95864736f6c63430008140033