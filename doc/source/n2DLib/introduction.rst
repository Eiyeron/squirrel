.. _n2dLib_introduction:

============
Introduction
============

The n2DLib library consist in a set of functions inmplemented in C. They allow a TI-Nspire
developper access the screen and the keybaord and offers functions to allow interacting
with them.

The library uses buffering to display smoothly ; that means that all drawing is done to a separate buffer in memory which is then copied to the screen.

Thus, n2DLib offers various functions from drawing a pixel, a sprite or circles to open
a bitmap file to parse it and detect which key has been pressed.

+++++++++++++++
Data structures
+++++++++++++++

All colors, unless specified, must be in R5G6B5 format, meaning a 16-bits number organized this way ::

    Bit   | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 
    Color | R  | R  | R  | R  | R  | G  | G | G | G | G | G | B | B | B | B | B 

2DLib uses a variation on the NTI image format to store images. All images must be arrays of unsigned short organized this way ::

    Entry |        0       |        1       |         2       |   3-...
    Use   | Width in pixels|Height in pixels|Transparent color|Image data

n2DLib also offers the Rect structure that has four members : `x`, `y`, `w` and `h`. You're free to use it for various purposes.

+++++++++++++++++++++++++
About fixed-point numbers
+++++++++++++++++++++++++

In addition to graphical commands, n2DLib offers a fast alternative to floating-point numbers that is 24.8 fixed-point numbers. Those numbers are integers whose bits 0-7 are treated like a decimal part, and whose bits 8-24 are treated like an integer part. That means 256 is actually 1.0 when used with the appropriate commands. FIxed-point angles are written in binary angles, meaning a full period is [0, 256].

Since fixed-point numbers are special numbers, they can't interact normally with integers. The following array describes what you can and can't do normally :

+-----------+-------+-----------+
|           |integer|fixed-point|
+-----------+-------+-----------+
|integer    |  +-*/ |     *     |
+-----------+-------+-----------+
|fixed-point|   */  |     +-    |
+-----------+-------+-----------+

You need a special routine to :
- add an integer to a fixed-point number
- divide an integer by a fixed-point number
- multiply a fixed-point number by another fixed-point number
- divide a fixed-point number by another fixed-point number

See the "Math routines" part of the doc to find how to do all of this.

+++++++++++++++++++++++++++++++++
Using the key detection functions
+++++++++++++++++++++++++++++++++

n2DLib provides additional key detection functions to those already provided by Ndless, and aims for full compatibility with those latters. That's why n2DLib uses Ndless's t_key struct :

.. code-block:: c

    typedef struct {
        int row, col, tpad_row, tpad_col;
        tpad_arrow_t tpad_arrow;
    } t_key;

Here's the structure seend from squirrel's side. Note that the key listing is usable with the prefix `n2dk`. Example : `n2dk.ENTER` to acces `ENTER`'s index.

.. code-block:: js

    local key =  {
        row : 0, /*number*/
        col : 0, /*number*/
        tpad_row : 0, /*number*/
        tpad_col : 0; /*number*/
        tpad_arrow : 0; /*number*/
    };


Each key is stored depending on its position on the Nspire's keypad, row and column. You can see two different versions for each variable ; that's because the clickpad keypad and the touchpad keypad have different keymappings. This is taken care of by n2DLib internally, so you don't have to worry about it.

For more info about how the keypad(s) work(s), see http://hackspire.unsads.com/wiki/index.php/Keypads .

See the "Key detection functions" part of the doc to see what you can do. You don't necessarily need these routines unless you want to do specific things like custom keybinding, since what Ndless provides is enough for most cases .
