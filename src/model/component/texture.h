/**
 * @file texture.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-12
 */

#ifndef __AGE_TEXTURE_COMPONENT__
#define __AGE_TEXTURE_COMPONENT__

#include <vector>
#include <tuple>
#include "component.h"

namespace AGE
{

/** 
 * @brief A base class component for texture. A `CTexture` is required by `CRender`.
 * 
 * The angine provide three types of texture:
 * - CRectangle
 * - CASCII
 * - CBitmap
 */
class CTexture : public Component
{
public:
    CTexture(Entity &entity): Component {entity} {}
    ~CTexture() override {}
};



/** @brief Texture representing a rectangle. */
class CRectangle : public CTexture
{
public:
    CRectangle(Entity &entity, int width, int height): CTexture {entity}, width {width}, height {height} {}
    ~CRectangle() override {}
public:
    int width;
    int height;
};



/** @brief Texture representing a single ascii character. */
class CASCII : public CTexture
{
public:
    CASCII(Entity &entity, char ascii): CTexture {entity}, ascii {ascii} {}
    ~CASCII() override {}
public:
    char ascii;
};



/** @brief Data type representing each pixel */
using triple = std::tuple<int, int, char>;

/** @brief Texture representing a bitmap. */
class CBitmap : public CTexture
{
public:
    CBitmap(Entity &entity, char ascii, const std::vector<triple> &bitmap): CTexture {entity}, bitmap {bitmap} {}
    CBitmap(Entity &entity, char ascii, std::vector<triple> &&bitmap): CTexture {entity}, bitmap {std::move(bitmap)} {}
    ~CBitmap() override {}
public:
    std::vector<triple> bitmap;
};

} // AGE

#endif
