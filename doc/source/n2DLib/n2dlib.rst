.. _n2dlib:

================
n2DLib functions
================

++++++++++++++++++++++
Graphics
++++++++++++++++++++++

.. _n2d_clearBufferB:

.. js:function:: clearBufferB()

    Fills the buffer with black color.
    
.. _n2d_clearBufferW:

.. js:function:: clearBufferW()

    Fills the buffer with White color.
    
.. _n2d_clearBuffer:

.. js:function:: clearBuffer(color)

    Fills the buffer with White color.
    
.. _n2d_getPixel:

.. js:function:: getPixel(image, x, y)

    Returns the color of a given pixel in an image, or the transparent color of this image if the coordinates given are out-of-bounds.
    
.. _n2d_deinitBuffering:

.. js:function:: deinitBuffering()

    Frees memory used by the buffering functionalities. Call this as the very last instruction of your program (excepting return).

.. _n2d_drawLine:

.. js:function:: drawLine(x1, y1, x2, y2, color)

   Draws a line between two points of the given color.

.. _n2d_drawSprite:

.. js:function:: drawLine(sprite, x, y, flash, flashColor)

    Draws an image to the given coordinates.

.. _n2d_ddrawSpritePart:

.. js:function:: drawSpritePart(sprite, x, y, xp, yp, wp, hp, flash, flashColor)

    Draws part of an image to the given coordinates. The routine draws what of the sprite is in the rectangle given by `xp`, `yp`, `wp` and `hp`.

.. _n2d_drawSpriteRotated:

.. js:function:: drawSpriteRotated(sprite, xs, ys, ws, hs, xr, yr, angle, flash, flashColor)

    Draws a sprite rotated by a given angle at the coordinates given by `xs`, `ys`, `ws` and `hs` so that the rotation of the sprite is performed around the point (`xr`, `yr`), which is relative to the sprite itself. The center of the rotation will always be displayed at the coordinates (`xs`, `ys`). For example, if `xr` and `yr` are half the sprite's width and height, the sprite will be rotated around its center.

.. _n2d_drawSpriteScaled:

.. js:function:: drawSpriteScaled(sprite, xs, ys, ws, hs, flash, flashColor)

    Draws a sprite by scaling it so that it fits perfectly in the rectangle given by `xs`, `ys`, `ws` and `hs`.

.. _n2d_fillCircle:

.. js:function:: fillCircle(x, y, radius, color)

    Fills a circle of the given color.

.. _n2d_fillEllipse:

.. js:function:: fillEllipse(x, y, w, h, color)

    Fills an ellipse of the given size with the given color.

.. _n2d_fillRect:

.. js:function:: fillRect(x, y, w, h, color)

    Fills a rectangle of the given dimensions with the given color ; does clipping.

.. _n2d_initBuffering:

.. js:function:: initBuffering()

    Initializes the buffering functionalities. Call this as the very first instruction of your program if you want to use n2DLib's buffering.

.. _n2d_setPixel:

.. js:function:: setPixel(x, y, color)

    Sets a pixel to the given color after verifying the pixel is actually in the screen's dimensions.

.. _n2d_setPixelRGB:

.. js:function:: setPixelRGB(x, y, r, g, b)

    Sets a pixel to the given color after verifying the pixel is actually in the screen's dimensions and using three color components.

.. _n2d_setPixelUnsafe:

.. js:function:: setPixelUnsafe(x, y, color)

    Sets a pixel to the given color, but does not make sure the pixel is in the screen's dimensions. Faster than setPixel, but use only if you know you can't draw out of the screen.

.. _n2d_updateScreen:

.. js:function:: updateScreen()

    Copies the content of the buffer to the screen. This does not clear the buffer.

++++++++++++++++++++++
Text routines
++++++++++++++++++++++

.. _n2d_drawChar:

.. js:function:: drawChar(x, y, margin, char, fontColor, outlineColor)

    Draws a single character at the given position with the given front and outline color using n2DLib's built-in font. Does clipping and supports newlines with \n. When \n is passed as ch, the function resets the X value to the passed margin value and Y goes to newline. X and Y are modified like a cursor position would and are returned in an array.

.. _n2d_drawDecimal:

.. js:function:: drawDecimal(x, y, number, fontColor, outlineColor)

    Draws a signed integer at the given position with the given front and outline color using n2DLib's built-in font. Does clipping. X and Y are modified like a cursor position would. Use this as a fast way to display integers only.

.. _n2d_drawString:

.. js:function:: drawString(x, y, margin, str, fontColor, outlineColor)

    Draws a string of characters at the given position with the given front and outline color using n2DLib's built-in font. Does clipping and supports newlines with \n. When \n is encountered in the string, the function resets the X value to the passed margin value and Y goes to newline. X and Y are modified like a cursor position would. Use this as a fast way to display strings only.


.. _n2d_stringWidth:

.. js:function:: stringWidth(str)

    Returns the width of the string in pixels when using n2DLib's built-in font.

.. _n2d_numberWitdh:

.. js:function:: numberWitdh(number)

    Returns the width of the decimal in pixels when drawn to the screen using n2DLib's built-in font.

++++++++++++++++++++++
Math routines
++++++++++++++++++++++

.. _n2d_fixcos:

.. js:function:: fixcos(angle)

    Returns the cosinus of a binary angle in fixed-point format.

.. _n2d_fixdiv:

.. js:function:: fixdiv(a, b)

    Performs a division between two fixed-point numbers.

.. _n2d_fixmul:

.. js:function:: fixmul(a, b)

    Performs a multiplication between two fixed-point numbers.

.. _n2d_fixsin:

.. js:function:: fixsin(angle)

    Returns the sinus of a binary angle in fixed-point format.

.. _n2d_fixtoi:

.. js:function:: fixtoi(f)

    Turns a fixed-point number into an integer.

.. _n2d_itofix:

.. js:function:: itofix(i)

    Turns an integer into a fixed-point number.

++++++++++++++++++++++
Key detection routines
++++++++++++++++++++++

.. _n2d_getKeyPressed:

.. js:function:: getKeyPressed(key)

    Detects if any key is being pressed ; if so, returns the corresponding data. If no key is being pressed, returns the structure filled with _KEY_DUMMY and returns it.
    
    NOTE
        This doesn't detect the touchpad's arrow keys.

.. _n2d_isKey:

.. js:function:: _n2d_isKey(key, key_index)

    Returns `true` if given key match the enumeration index, or `false` if not.

    USAGE
        .. code-block:: js
        
            value = n2d.isKey(key, n2dk.ENTER)

    NOTE
        This is very useful for example when comparing a key that has been filled with get_key_pressed() with an Ndless `n2dk.` constant.

++++++++++++++++++++++
Image loading routines
++++++++++++++++++++++

.. _n2d_loadBMP:

.. js:function:: _n2d_loadBMP(path, colorMask)

    Returns a blob containing the loaded sprite with given alpha color mask if the file correctly loaded or null if it coudln't load it.

    NOTE
        This function load only 24-bit (R8G8B8) bitmap files. Make sure that you chose the correct format.
