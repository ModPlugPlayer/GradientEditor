/****************************************************************************
**
** Copyright (c) 2012 Richard Steffen and/or its subsidiary(-ies).
** All rights reserved.
** Contact: rsteffen@messbild.de, rsteffen@uni-bonn.de
**
** QColorRampEditor is free to use unter the terms of the LGPL 2.1 License in
** Free and Commercial Products.
****************************************************************************/

#pragma once

#include <QWidget>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>

#include <iostream>
using namespace std;
typedef QVector<QPair<qreal, QColor>> ColorRamp;

// -----------------------------------------------------------
// QColorRampEditor ------------------------------------------
// -----------------------------------------------------------
class SliderHandleWidget;
class ColorRampWidget;
class MultiHandleSliderWidget;
class QSliderTextWidget;
class QColorRampEditor : public QWidget
{
    Q_OBJECT
public:

    /// Basic Constructor
    QColorRampEditor(QWidget* parent=0, Qt::Orientation orientation = Qt::Horizontal);

    /// Destructor
    virtual ~QColorRampEditor();

    // define friends to access protected members
    friend class ColorRampWidget;
    friend class MultiHandleSliderWidget;
    friend class QSliderTextWidget;


	/// return a 256 colortable from the ramp
	QVector<QRgb> getColorTable();

signals:

    /// signal that hide is changed
    void rampChanged();

public slots:

protected slots:

    /// resize required
    virtual void resizeEvent(QResizeEvent* e);

    /// detect a mouse is pressed
    virtual void mousePressEvent(QMouseEvent* e);    

protected:
    /// the orientation
    Qt::Orientation orientation;

    /// the widgets drawint the ramp, the sliders, the text
    ColorRampWidget* rampwid_;
    MultiHandleSliderWidget* slidewid_;
};

class ColorRampWidget : public QWidget
{
    Q_OBJECT
public:
    ColorRampWidget(QWidget* parent=NULL);
    QColorRampEditor* rampeditor_;

public slots:
    void onColorRampChanged(ColorRamp colorRamp);

protected:
    ColorRamp colorRamp;
    void paintEvent(QPaintEvent* e);
};
