# ALU Design
This ALU implements:
  - add
  - substraction
  - &
  - |
  - ^
  - ~|
  - <<
  - \>\>  (logical and arrythmetical)

## Input
 - a (32 bits)
 - b (32 bits)
 - func (4 bits)
 - shamt (5 bits)

## Output
 - output (32 bits)
 - overflow (1 bit)

## Func Table
| func code | operation |
| ------ | ------ |
| 1000 | a + b |
| 1001 | a + b | 
| 1010 | a - b |
| 1011 | a - b |
| 1100 | a & b |
| 1101 | a \| b |
| 1110 | a ^ b |
| 1111 | ~(a \| b) |
| 0000 | b << shamt |
| 0010 | b >> shamt (complement 0) |
| 0011 | b >> shamt (complement most significant) |
| 0100 | a << b |
| 0110 | a >> b (complement 0)|
| 0111 | a >> b (complement most significant)|
