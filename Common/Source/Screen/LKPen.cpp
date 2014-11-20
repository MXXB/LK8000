/*
 * LK8000 Tactical Flight Computer -  WWW.LK8000.IT
 * Released under GNU/GPL License v.2
 * See CREDITS.TXT file for authors and copyrights
 *
 * File:   LKPen.cpp
 * Author: bruno de Lacheisserie
 * 
 * Created on 16 octobre 2014
 */
#ifdef WIN32
#include <windows.h>
#else
#warning "TODO: need to implement"
#endif

#include "LKPen.h"
#include "LKColor.h"

#include <utility>

#ifdef WIN32

const LKPen LK_NULL_PEN = LKPen::MakeStock(NULL_PEN);
const LKPen LK_BLACK_PEN = LKPen::MakeStock(BLACK_PEN);
const LKPen LK_WHITE_PEN = LKPen::MakeStock(WHITE_PEN);

LKPen::LKPen(LKPen&& Pen) : _Pen(Pen._Pen) {
    Pen._Pen = nullptr;
}

LKPen::LKPen(enumType Type, unsigned Size, const LKColor& Color) : _Pen() {
    Create(Type, Size, Color);
}

#else

LKPen::LKPen(){
}

LKPen::LKPen(enumType Type, unsigned Size, const LKColor& Color) {
    Create(Type, Size, Color);
}

#endif

LKPen::~LKPen() {
    Release();
}

LKPen& LKPen::operator= (LKPen&& Pen) {
#ifdef WIN32
    std::swap(_Pen, Pen._Pen);
#endif
    return (*this);
}

void LKPen::Create(enumType Type, unsigned Size, const LKColor& Color) {
    Release();

#ifdef WIN32
    _Pen = CreatePen(Type, Size, Color);
#endif
}

void LKPen::Release() {
#ifdef WIN32
    if (_Pen) {
        ::DeleteObject(_Pen);
    }
    _Pen = NULL;
#endif
}


