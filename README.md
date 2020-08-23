# Multi-Base-Calculator

## Description

A calculator capable of handling **addition** and **subtraction** operations on numbers of bases between 2 & 36 inclusive. 

#### Note:
*Currently assumes input from the user in the correct format when entering number values*. <br>
*Also assumes that the number is able to be represented in the specified base, i.e. 10102 is not a binary number*. <br>

## Commands

  * OFF - Exits the program.
  * RESET - Resets all storage locations to 0 and sets the current calculator base to 10.
  * SET - Sets the value of the accumulator to be a specified number.
  * DUMP - Prints the values in each storage location, including the accumulator.
  * BASE - Sets the current base of the calculator.
  * LOAD - Load a storage location value in the accumulator.
  * STORE - Stores the value in the accumulator into a valid storage location.
  * PRINT - Prints the current value of the accumulator.
  * ADD - Provide two values, these are added together and the result is stored in the accumulator.
  * SUBTRACT - Provide two values, these are subtracted and the result is stored in the accumulator.
  * H - Opens a help menu consisting of all possible commands that can be used.
  
## Other Details
  * A storage location is represented by a dollar sign followed by a capital letter from A-Z, i.e. $A
  * Values are represented in the following format: value@base. Ex. 5@10 represent the number 5 in base 10.
  * The accumulator is represented as storage location $0.
  * When entering a value for a mathematical operation, you may use either a new value in the correct format or a storage location.
  * When the base of the base of the calculator changes, it also converts all stored values to that base.
  
## Future Implementations
  * Allowing for numbers with decimals (subsequently allowing for Multiplication and Division).
  * Verifying user input is in the correct formats.
  <br>
  
  
