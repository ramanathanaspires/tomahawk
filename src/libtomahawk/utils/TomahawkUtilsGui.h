/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TOMAHAWKUTILSGUI_H
#define TOMAHAWKUTILSGUI_H

#include <QSize>
#include <QModelIndex>
#include <QColor>
#include <QRect>
#include <QTextOption>

#include "TomahawkUtils.h"
#include "DllMacro.h"

class PlayableItem;
class QStyleOptionViewItemV4;
class QPainter;
class QPixmap;
class QLayout;
class QPalette;
class QRect;
class QScrollBar;

namespace TomahawkUtils
{
    DLLEXPORT void drawQueryBackground( QPainter* p, const QPalette& palette, const QRect& r, qreal lightnessFactor = 1 );
    DLLEXPORT QWidget* tomahawkWindow();
    /// Platform-specific bringing tomahawk mainwindow to front, b/c qt's activate() and such don't seem to work well enough for us
    DLLEXPORT void bringToFront();

    DLLEXPORT QPixmap createAvatarFrame( const QPixmap &avatar );

    DLLEXPORT QColor alphaBlend( const QColor& colorFrom, const QColor& colorTo, float opacity );
    DLLEXPORT QPixmap createDragPixmap( MediaType type, int itemCount = 1 );

    DLLEXPORT void drawShadowText( QPainter* p, const QRect& rect, const QString& text, const QTextOption& textOption );
    DLLEXPORT void drawBackgroundAndNumbers( QPainter* p, const QString& text, const QRect& rect );

    DLLEXPORT void unmarginLayout( QLayout* layout );

    DLLEXPORT int headerHeight();
    DLLEXPORT void setHeaderHeight( int height );

    DLLEXPORT QPixmap defaultPixmap( ImageType type, ImageMode mode = TomahawkUtils::Original, const QSize& size = QSize( 0, 0 ) );

    DLLEXPORT void prepareStyleOption( QStyleOptionViewItemV4* option, const QModelIndex& index, PlayableItem* item );

    DLLEXPORT void drawRoundedButton( QPainter* painter, const QRect& btnRect, const QColor& color, const QColor &gradient1bottom = QColor(), const QColor& gradient2top = QColor(), const QColor& gradient2bottom = QColor() );

    DLLEXPORT void styleScrollBar( QScrollBar* scrollBar );
}

#endif // TOMAHAWKUTILSGUI_H
