/*
MathUtil utilization class declarations
Belongs to GradientEditor Project
Copyright (C) 2021 Volkan Orhan

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

#include <QPoint>
#include <QRect>
#include <QtGlobal>

namespace GradientEditor {
    namespace MathUtil {
        qreal getNormalizedValue(qreal value, qreal min, qreal max);
        qreal getNormalizedValue(QPoint position, QRect contentsRect, qreal boundarySpace, Qt::Orientation orientation);
        //QPoint getPositionForNormalizedValue(qreal value, qreal boundarySpace, qreal sliderWidth, Qt::Orientation orientation);
        QPoint getPositionForNormalizedValue(qreal normalizedValue, QRect contentsRect, qreal boundarySpace, Qt::Orientation orientation);
    }
}
