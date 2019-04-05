/* 
 * CS:APP Data Lab 
 * 
 * Qingwei Zeng <classqze>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.  *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  /* multiply x by 3 in two's complement is equivalent to x + x + x */
  int product = x + x + x;

  /* Note that integer division ALWAYS ROUNDS TOWARDS ZERO.
   * Also note that right shift in two's complement ALWAYS ROUNDS DOWN.
   * Consider following 3-bit integer division example:
   *
   *   - Right shifting 101 (i.e. -3) yields 110 (i.e. -2). -3/2=-1.5~-2
   *
   * As a result, right shift is not always equivalent to division by the powers
   * of two, specifically not equivalent when the quotient is negative.
   *
   * In a nutshell, integer divition with negative quotient should ROUND UP, but 
   * the right shift operation ROUNDS DOWN.
   *
   *
   * To tackle this issue, we use the following strategy:
   *
   * Notice that in this problem the quotient is negative only when the
   * numerator (product, or x*3) is negative.
   *
   * Therefore, when the numerator is negative, we can add a SUPPLEMENT PART to 
   * the numerator. The supplement part should be chosen in a way such that the 
   * quotient would seems to be rounding up instead of rounding down. Also,
   * notice that when the quotient is an exact integer, no rounding should
   * happen.
   *
   * It turns out the supplement should be denominator-1 (in this case 4-1=3).
   *
   * This would cause an addition of 3/4 (0.75) on the quotient, why this helps?
   * because: (let k denote the integer part of the quotient)
   *   - k.0  + 0.75 = k.75     --round_down-->      k.0
   *   - k.25 + 0.75 = (k+1).0  --round_down-->  (k+1).0
   *   - k.50 + 0.75 = (k+1).25 --round_down-->  (k+1).0
   *   - k.75 + 0.75 = (k+1).50 --round_down-->  (k+1).0
   *
   * This gives us proper round up.
   */
   
  // 0 when positive, 3 when negative
  int supplement = (product >> 31) & 3;
  return (product + supplement) >> 2;  
}

