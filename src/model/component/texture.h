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
#include <string>
#include "component.h"

#include "../../controller/adapter/ncurseAdapter.h"

namespace AGE
{

/** 
 * @brief An abstract base class component for texture. A `CTexture` is required 
 * by a `CRenderer`.
 * 
 * The AGE angine provide three types of texture:
 * - CRectangle
 * - CASCII
 * - CBitmap
 */
class CTexture : public Component
{
public:
    CTexture(Entity &entity): Component {entity} {}
    ~CTexture() override {}
public:
    /** 
     * @brief describes how to paint the texture onto the window buffer.
     * @warning Note that, this function does not refresh the buffer.
     */
    virtual void paint(Ncurses::Window &buffer, CPosition &position) = 0;
};



/** @brief Texture representing a rectangle. */
class CRectangle : public CTexture
{
public:
    CRectangle(Entity &entity, int width, int height, std::string fill)
        : CTexture {entity}, width {width}, height {height}, fill {fill} 
    {}
    ~CRectangle() override {}
public:
    void paint(Ncurses::Window &buffer, CPosition &position) override
    {
        vec2d<int> pos = roundvec2d(position.pos);
        for (SIZE x = pos.X(); x < pos.X() + width; ++x) {
            for (SIZE y = pos.Y(); y < pos.Y() + height; ++y) {
                buffer.print(fill, x, y);
            }
        }
    }
public:
    int width;
    int height;
    std::string fill;
};



/** @brief Texture representing a single ascii character. */
class CASCII : public CTexture
{
public:
    CASCII(Entity &entity, std::string ascii): CTexture {entity}, ascii {ascii} {}
    ~CASCII() override {}
public:
    void paint(Ncurses::Window &buffer, CPosition &position) override
    {
        vec2d<int> pos = roundvec2d(position.pos);
        buffer.print(ascii, pos.X(), pos.Y());
    }
public:
    std::string ascii;
};



/** @brief Data type representing each pixel (x, y, char) */
using triple = std::tuple<int, int, const char *>;

/** @brief Texture representing a bitmap. */
class CBitmap : public CTexture
{
public:
    CBitmap(Entity &entity, const std::vector<triple> &bitmap): CTexture {entity}, bitmap {bitmap} {}
    CBitmap(Entity &entity, std::vector<triple> &&bitmap): CTexture {entity}, bitmap { std::move(bitmap) } {}
    ~CBitmap() override {}
public:
    void paint(Ncurses::Window &buffer, CPosition &position) override
    {
        vec2d<int> pos = roundvec2d(position.pos);
        for (auto &[x, y, c] : bitmap) {
            buffer.print(c, pos.X() + x, pos.Y() + y);
        }
    }
public:
    std::vector<triple> bitmap;
};

} // AGE

#endif
