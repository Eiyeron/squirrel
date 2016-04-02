#include <squirrel.h>
#include <sqstdblob.h>
#include "n2DLib/n2DLib.h"

 SQInteger register_global_func(HSQUIRRELVM v,SQFUNCTION f,const char *fname)
 {
        sq_pushroottable(v);
        sq_pushstring(v,fname,-1);
        sq_newclosure(v,f,0); //create a new function
        sq_newslot(v,-3, SQFalse);
        sq_pop(v,1); //pops the root table
        return 0;
 }

SQRESULT register_lib(HSQUIRRELVM v, const SQChar *lib_name, const SQRegFunction *reg)
{
    SQInteger top = sq_gettop(v);
	sq_pushstring(v,lib_name,-1);
	sq_newtable(v);
	int i = 0;
	while(reg[i].name != NULL) {
		const SQRegFunction* fun = &reg[i];
		sq_pushstring(v, fun->name, -1);
		sq_newclosure(v, fun->f, 0);
		sq_setparamscheck(v, fun->nparamscheck, fun->typemask);
		sq_setnativeclosurename(v, -1, fun->name);
		sq_newslot(v, -3, SQFalse);
		i++;
	}
	sq_newslot(v, -3, SQFalse);
    sq_settop(v,top);
    return SQ_ERROR;

}

//////////////////
// n2DLib glue. //
//////////////////

// Utilities

SQInteger n2d_itofix (HSQUIRRELVM v)
{
	int i;
	sq_getinteger(v, 2, &i);
	sq_pushinteger(v, itofix(i));
	return 1;
}

SQInteger n2d_fixtoi (HSQUIRRELVM v)
{
	Fixed f;
	sq_getinteger(v, 2, &f);
	sq_pushinteger(v, fixtoi(f));
	return 1;
}

SQInteger n2d_fixdiv (HSQUIRRELVM v)
{
	Fixed x, y;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_pushinteger(v, fixdiv(x, y));
}

SQInteger n2d_fixmul (HSQUIRRELVM v)
{
	Fixed x, y;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_pushinteger(v, fixmul(x, y));
	return 1;
}

SQInteger n2d_fixcos (HSQUIRRELVM v)
{
	Fixed angle;
	sq_getinteger(v, 2, &angle);
	sq_pushinteger(v, fixcos(angle));
	return 1;
}

SQInteger n2d_fixsin (HSQUIRRELVM v)
{
	Fixed angle;
	sq_getinteger(v, 2, &angle);
	sq_pushinteger(v, fixsin(angle));
	return 1;
}


// Drawing routines

SQInteger n2d_initBuffering (HSQUIRRELVM v)
{
	initBuffering();
	return 0;
}

SQInteger n2d_updateScreen (HSQUIRRELVM v)
{
	updateScreen();
	return 0;
}

SQInteger n2d_deinitBuffering (HSQUIRRELVM v)
{
	deinitBuffering();
	return 0;
}

SQInteger n2d_clearBuffer (HSQUIRRELVM v)
{
	unsigned int color;
	sq_getinteger(v, 2, &color);
	clearBuffer((unsigned short) color);
	return 0;
}

SQInteger n2d_clearBufferB (HSQUIRRELVM v)
{
	clearBufferB();
	return 0;
}

SQInteger n2d_clearBufferW (HSQUIRRELVM v)
{
	clearBufferW();
	return 0;
}

SQInteger n2d_getPixel (HSQUIRRELVM v)
{
	SQUserPointer image;
	unsigned int x, y;
	sqstd_getblob(v, 2, &image);
	sq_getinteger(v, 3, &x);
	sq_getinteger(v, 4, &y);
	unsigned int value = getPixel((unsigned short*) image, x, y);
	sq_pushinteger(v, value);
	return 1;
}

SQInteger n2d_setPixelUnsafe (HSQUIRRELVM v)
{
	unsigned int x, y, color;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &color);
	setPixelUnsafe(x, y, (unsigned short)color);
	return 0;
}

SQInteger n2d_setPixel (HSQUIRRELVM v)
{
	unsigned int x, y, color;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &color);
	setPixel(x, y, (unsigned short)color);
	return 0;
}

SQInteger n2d_setPixelRGB (HSQUIRRELVM v)
{
	unsigned int x, y, r, g, b;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &r);
	sq_getinteger(v, 5, &g);
	sq_getinteger(v, 6, &b);
	setPixelRGB(x, y, (unsigned char)r, (unsigned char)g, (unsigned char)b);
	return 0;

}

SQInteger n2d_drawHLine (HSQUIRRELVM v)
{
	int y, x1, x2;
	unsigned int color;
	sq_getinteger(v, 2, &y);
	sq_getinteger(v, 3, &x1);
	sq_getinteger(v, 4, &x2);
	sq_getinteger(v, 5, &color);
	drawHLine(y, x1, x2, color);
	return 0;
}

SQInteger n2d_drawVLine (HSQUIRRELVM v)
{
	int x, y1, y2;
	unsigned int color;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y1);
	sq_getinteger(v, 4, &y2);
	sq_getinteger(v, 5, &color);
	drawVLine(x, y1, y2, color);
	return 0;
}

SQInteger n2d_fillRect (HSQUIRRELVM v)
{
	int x, y, w, h, color;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &w);
	sq_getinteger(v, 5, &h);
	sq_getinteger(v, 6, &color);
	fillRect(x, y, w, h, color);
}

SQInteger n2d_drawSprite (HSQUIRRELVM v)
{
	SQUserPointer image;
	unsigned x, y, flash;
	unsigned int flash_color;
	sqstd_getblob(v, 2, &image);
	sq_getinteger(v, 3, &x);
	sq_getinteger(v, 4, &y);
	sq_getinteger(v, 5, &flash);
	sq_getinteger(v, 6, &flash_color);
	drawSprite((const unsigned short*)image, x, y, flash, (unsigned short) flash_color);
	return 0;

}

SQInteger n2d_drawSpritePart (HSQUIRRELVM v)
{
	SQUserPointer image;
	unsigned x, y, flash;
	unsigned xp, yp, wp, hp;
	unsigned int flash_color;
	sqstd_getblob(v, 2, &image);
	sq_getinteger(v, 3, &x);
	sq_getinteger(v, 4, &y);
	sq_getinteger(v, 5, &xp);
	sq_getinteger(v, 6, &yp);
	sq_getinteger(v, 7, &wp);
	sq_getinteger(v, 8, &hp);
	sq_getinteger(v, 9, &flash);
	sq_getinteger(v, 10, &flash_color);
	Rect r = {x, y, wp, hp};
	drawSpritePart((const unsigned short*)image, x, y, &r, flash, (unsigned short) flash_color);
	return 0;
	
}

SQInteger n2d_drawSpriteScaled (HSQUIRRELVM v)
{
	SQUserPointer image;
	int xs, ys, ws, hs, flash;
	unsigned int flash_color;
	sqstd_getblob(v, 2, &image);
	sq_getinteger(v, 3, &xs);
	sq_getinteger(v, 4, &ys);
	sq_getinteger(v, 5, &hs);
	sq_getinteger(v, 6, &ws);
	sq_getinteger(v, 7, &flash);
	sq_getinteger(v, 8, &flash_color);
	Rect r = {xs, ys, ws, hs};
	drawSpriteScaled((const unsigned short*)image, &r, flash, (unsigned short) flash_color);
	return 0;
	
}

SQInteger n2d_drawSpriteRotated (HSQUIRRELVM v)
{
	SQUserPointer image;
	int xsr, ysr, wsr, hsr;
	int xrc, yrc, wrc, hrc;
	int angle, flash;
	unsigned int flash_color;
	sqstd_getblob(v, 2, &image);
	sq_getinteger(v, 3, &xsr);
	sq_getinteger(v, 4, &ysr);
	sq_getinteger(v, 5, &wsr);
	sq_getinteger(v, 6, &hsr);
	
	sq_getinteger(v, 7, &xrc);
	sq_getinteger(v, 8, &yrc);
	sq_getinteger(v, 9, &wrc);
	sq_getinteger(v, 10, &hrc);

	sq_getinteger(v, 11, &angle);
	sq_getinteger(v, 12, &flash);
	sq_getinteger(v, 13, &flash_color);

	Rect sr = {xsr, ysr, wsr, hsr};
	Rect rc = {xrc, yrc, wrc, hrc};
	drawSpriteRotated((const unsigned short*)image, &sr, &rc, (Fixed)angle, flash, flash_color);

}

SQInteger n2d_drawLine (HSQUIRRELVM v)
{
	int x1, x2, y1, y2;
	unsigned int color;
	sq_getinteger(v, 2, &x1);
	sq_getinteger(v, 3, &y1);
	sq_getinteger(v, 4, &x2);
	sq_getinteger(v, 5, &y2);
	sq_getinteger(v, 6, &color);
	drawLine(x1, y1, x2, y2, color);
	return 0;
}

SQInteger n2d_fillCircle (HSQUIRRELVM v)
{
	int x, y, r, color;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &r);
	sq_getinteger(v, 5, &color);
	fillCircle(x, y, r, color);
}

SQInteger n2d_fillEllipse (HSQUIRRELVM v)
{
	int x, y, r, R, color;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &r);
	sq_getinteger(v, 5, &R);
	sq_getinteger(v, 6, &color);
	fillEllipse(x, y, r, R, color);
}

SQInteger n2d_drawString (HSQUIRRELVM v)
{
	int x, y, margin;
	SQChar* str;
	unsigned int fc, olc;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &margin);
	sq_getstring(v, 5, (const SQChar**)&str);
	sq_getinteger(v, 6, &fc);
	sq_getinteger(v, 7, &olc);
	drawString(&x, &y, margin, (char*)str, fc, olc);
	// pushing new X/Y values.
	sq_newarray(v, 2);
	sq_pushinteger(v, x);
	sq_set(v, -2);
	sq_pushinteger(v, y);
	sq_set(v, -2);
	return 1;
}

SQInteger n2d_drawDecimal (HSQUIRRELVM v)
{
	int x, y, n;
	unsigned int fc, olc;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &n);
	sq_getinteger(v, 5, &fc);
	sq_getinteger(v, 6, &olc);
	drawDecimal(&x, &y, n, (unsigned short)fc, (unsigned short)olc);
	// pushing new X/Y values.
	sq_newarray(v, 2);
	sq_pushinteger(v, x);
	sq_set(v, -2);
	sq_pushinteger(v, y);
	sq_set(v, -2);
	return 1;
}

SQInteger n2d_drawChar (HSQUIRRELVM v)
{
	int x, y, margin, ch;
	unsigned int fc, olc;
	sq_getinteger(v, 2, &x);
	sq_getinteger(v, 3, &y);
	sq_getinteger(v, 4, &margin);
	sq_getinteger(v, 5, &ch);
	sq_getinteger(v, 6, &fc);
	sq_getinteger(v, 7, &olc);
	drawChar(&x, &y, margin, ch, fc, olc);
	// pushing new X/Y values.
	sq_newarray(v, 2);
	sq_pushinteger(v, x);
	sq_set(v, -2);
	sq_pushinteger(v, y);
	sq_set(v, -2);
	return 1;
}

SQInteger n2d_numberWidth (HSQUIRRELVM v)
{
	int n;
	sq_getinteger(v, 2);
	sq_pushinteger(v, numberWidth(n));
	return 1;
}

SQInteger n2d_stringWidth (HSQUIRRELVM v)
{
	SQChar* str;
	sq_getstring(v, 2, (const SQChar**)&str);
	sq_pushinteger(v, stringWidth((const char*)str));
	return 1;
}

#define _DECL_GLOBALIO_FUNC(name,nparams,typecheck) {_SC(#name),n2d_##name,nparams,typecheck}
static const SQRegFunction n2d_funcs[]={
    _DECL_GLOBALIO_FUNC(itofix,2,_SC(".i")),
    _DECL_GLOBALIO_FUNC(fixtoi,2,_SC(".i")),
    _DECL_GLOBALIO_FUNC(fixdiv,2,_SC(".ii")),
    _DECL_GLOBALIO_FUNC(fixmul,2,_SC(".ii")),
    _DECL_GLOBALIO_FUNC(fixsin,2,_SC(".i")),
    _DECL_GLOBALIO_FUNC(fixcos,2,_SC(".i")),

    _DECL_GLOBALIO_FUNC(initBuffering,1,_SC(".")),
    _DECL_GLOBALIO_FUNC(deinitBuffering,1,_SC(".")),
    _DECL_GLOBALIO_FUNC(updateScreen,1,_SC(".")),
    _DECL_GLOBALIO_FUNC(clearBuffer,2,_SC(".i")),
    _DECL_GLOBALIO_FUNC(clearBufferB,1,_SC(".")),
    _DECL_GLOBALIO_FUNC(clearBufferW,1,_SC(".")),
    _DECL_GLOBALIO_FUNC(getPixel,4,_SC(".sii")),
    _DECL_GLOBALIO_FUNC(setPixelUnsafe,4,_SC(".iii")),
    _DECL_GLOBALIO_FUNC(setPixel,4,_SC(".iii")),
    _DECL_GLOBALIO_FUNC(setPixelRGB,6,_SC(".iiiii")),
    _DECL_GLOBALIO_FUNC(drawHLine,5,_SC(".iiii")),
    _DECL_GLOBALIO_FUNC(drawVLine,5,_SC(".iiii")),
    _DECL_GLOBALIO_FUNC(fillRect,6,_SC(".iiiii")),
    _DECL_GLOBALIO_FUNC(drawSprite,6,_SC(".xiiii")),
    _DECL_GLOBALIO_FUNC(drawSpritePart,10,_SC(".xiiiiiiii")),
    _DECL_GLOBALIO_FUNC(drawSpriteScaled,8,_SC(".xiiiiiiii")),
    _DECL_GLOBALIO_FUNC(drawSpriteRotated,13,_SC(".xiiiiiiiiiii")),
    _DECL_GLOBALIO_FUNC(drawLine,6,_SC(".iiiii")),
    _DECL_GLOBALIO_FUNC(fillRect,6,_SC(".iiiii")),
    _DECL_GLOBALIO_FUNC(fillCircle,5,_SC(".iiii")),
    _DECL_GLOBALIO_FUNC(fillEllipse,5,_SC(".iiiii")),
    _DECL_GLOBALIO_FUNC(drawString,7,_SC(".iiisii")),
    _DECL_GLOBALIO_FUNC(drawDecimal,6,_SC(".iiiii")),
    _DECL_GLOBALIO_FUNC(drawChar,7,_SC(".iiiiiii")),
    _DECL_GLOBALIO_FUNC(numberWidth,2,_SC(".i")),
    _DECL_GLOBALIO_FUNC(stringWidth,2,_SC(".s")),

    {NULL,(SQFUNCTION)0,0,NULL}
};

SQRESULT register_n2dlib (HSQUIRRELVM v)
{
	return register_lib(v, _SC("n2d"), n2d_funcs);
}
#undef _DECL_GLOBALIO_FUNC