#include "common.h"
#include <bit>
#include "gui/IVramManager.h"
#include "gui/Gx.h"
#include "gui/VramContext.h"
#include "gui/GraphicsContext.h"
#include "core/StringUtil.h"
#include "Label3DView.h"

Label3DView::Label3DView(u32 width, u32 height, u32 maxStringLength, const nft2_header_t* font,
    VBlankTextureLoader* vblankTextureLoader)
    : LabelView(width, height, maxStringLength, font, true)
    , _vblankTextureLoader(vblankTextureLoader) { }

Label3DView::~Label3DView()
{
    _vblankTextureLoader->CancelLoad(_textureLoadRequest);
}

void Label3DView::InitVram(const VramContext& vramContext)
{
    const auto texVramManager = vramContext.GetTexVramManager();
    if (texVramManager)
    {
        _texVramOffset = texVramManager->Alloc(_tileBufferSize);
        // Text may have been assigned before VRAM existed. Upload it now so
        // unfocused rows are visible immediately, without requiring cursor focus.
        UpdateTileBuffer();
    }
}

void Label3DView::UpdateTileBuffer()
{
    _vblankTextureLoader->CancelLoad(_textureLoadRequest);
    LabelView::UpdateTileBuffer();
    // Keep the measured width current so centered labels work in custom themes.
    _stringWidth = _newStringWidth;
    _textureLoadRequest = VBlankTextureLoadRequest(_tileBuffer.get(), _tileBufferSize,
        _texVramOffset, nullptr, 0, 0, nullptr, nullptr);
    _vblankTextureLoader->RequestLoad(_textureLoadRequest);
}

void Label3DView::Draw(GraphicsContext& graphicsContext)
{
    if (!graphicsContext.IsVisible(GetBounds()))
        return;

    Gx::MtxIdentity();
    Gx::PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGON_MODE_MODULATE, GX_DISPLAY_MODE_FRONT,
        false, false, false, GX_DEPTH_FUNC_LESS, false, 31, graphicsContext.GetPolygonId());
    Gx::TexImageParam(_texVramOffset >> 3, false, false, false, false, (GxTexSize)(std::bit_width(_actualWidth) - 4),
        GX_TEXSIZE_1024, GX_TEXFMT_A5I3, false, GX_TEXGEN_NONE);
    graphicsContext.GetRgb6Palette()->ApplyColor(Rgb<6, 6, 6>(_foregroundColor));
    int xOffset = _position.x;
    if (_hAlign == Alignment::Center)
        xOffset += ((int)_width - (int)_stringWidth) / 2;
    else if (_hAlign == Alignment::End)
        xOffset += (int)_width - (int)_stringWidth;

    Gx::Begin(GX_PRIMITIVE_QUAD);
    Gx::TexCoord(0, 0);
    REG_GX_VTX_16 = GX_VTX_PACK(xOffset << 6, _position.y << 3);
    REG_GX_VTX_16 = (200) << 6;
    Gx::TexCoord(0, (int)_height);
    REG_GX_VTX_16 = GX_VTX_PACK(xOffset << 6, (_position.y + _height) << 3);
    REG_GX_VTX_16 = (200) << 6;
    Gx::TexCoord((int)_width, (int)_height);
    REG_GX_VTX_16 = GX_VTX_PACK((xOffset + _width) << 6, (_position.y + _height) << 3);
    REG_GX_VTX_16 = (200) << 6;
    Gx::TexCoord((int)_width, 0);
    REG_GX_VTX_16 = GX_VTX_PACK((xOffset + _width) << 6, _position.y << 3);
    REG_GX_VTX_16 = (200) << 6;
    Gx::End();
}