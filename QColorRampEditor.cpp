/****************************************************************************
**
** Copyright (c) 2012 Richard Steffen and/or its subsidiary(-ies).
** All rights reserved.
** Contact: rsteffen@messbild.de, rsteffen@uni-bonn.de
**
** QColorRampEditor is free to use unter the terms of the LGPL 2.1 License in
** Free and Commercial Products.
****************************************************************************/

#include "QColorRampEditor.hpp"
#include <QPainter>
#include <QMouseEvent>
#include "MultiHandleSlider.hpp"
#include "ColorRampWidget.hpp"
#include "MathUtil.hpp"
#include <QDebug>

// -----------------------------------------------------------
// QColorRampEditor ------------------------------------------
// -----------------------------------------------------------
QColorRampEditor::QColorRampEditor(QWidget* parent, Qt::Orientation orientation) : QWidget(parent)
{
    this->orientation = orientation;
    if (orientation==Qt::Horizontal)
        setMinimumSize(50,40);
    else
        setMinimumSize(40,50);

    setContentsMargins(0,0,0,0);
    if (orientation==Qt::Horizontal)
        setLayout(new QVBoxLayout());
    else
        setLayout(new QHBoxLayout());
    //layout()->setMargin(0);
    layout()->setSpacing(0);
    layout()->setContentsMargins(0,0,0,0);

    colorRampWidget = new ColorRampWidget();
    colorRampWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    colorRampWidget->setContentsMargins(0,0,0,0);

    layout()->addWidget(colorRampWidget);

    multiHandleSlider = new MultiHandleSlider(this, orientation);
    if (orientation==Qt::Horizontal)
    {
        multiHandleSlider->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        multiHandleSlider->setFixedHeight(16);
    }
    else
    {
        multiHandleSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        multiHandleSlider->setFixedWidth(16);
    }
    multiHandleSlider->setContentsMargins(0,0,0,0);
    layout()->addWidget(multiHandleSlider);

    // init sliders
    QVector<QPair<qreal, QColor> > ramp;
    //ramp.push_back(QPair<qreal, QColor>(0.0, Qt::black));
    ramp.push_back(QPair<qreal, QColor>(0.5, Qt::red));
    multiHandleSlider->setRamp(ramp);
    connect(multiHandleSlider, &MultiHandleSlider::sliderChanged, this, &QColorRampEditor::onColorRampChanged);
    connect(colorRampWidget, &ColorRampWidget::colorClicked, this, &QColorRampEditor::onColorClicked);
}

QColorRampEditor::~QColorRampEditor() {
}

QVector<QRgb> QColorRampEditor::getColorTable() {
    // get ramp and normalize
    QVector<QPair<qreal, QColor> > ramp = multiHandleSlider->getColorRamp();
    for (int i=0; i<ramp.size(); i++) ramp[i].first = multiHandleSlider->getNormalizedValue(ramp[i].first);
    QVector<QRgb> ctable;
    int index = 0;
    for (int i = 0; i < 256; i++)
    {
        float val = 1.0f*i/255;
        if (val>ramp[index+1].first) index++;
        // linear interpolate color
        QColor cc;
        float d = val - ramp[index].first;
        float dr = ramp[index+1].second.redF() - ramp[index].second.redF();
        float dg = ramp[index+1].second.greenF() - ramp[index].second.greenF();
        float db = ramp[index+1].second.blueF() - ramp[index].second.blueF();
        qreal dd = ramp[index+1].first - ramp[index].first;
        float red = ramp[index].second.redF() +  d*dr/dd;
        float green = ramp[index].second.greenF() +  d*dg/dd;
        float blue = ramp[index].second.blueF() +  d*db/dd;
		if (red<0.0f) red=0;
		if (red>1.0f) red=1;
		if (green<0.0f) green=0;
		if (green>1.0f) green=1;
		if (blue<0.0f) blue=0;
		if (blue>1.0f) blue=1;
        cc.setRedF(red);
        cc.setGreenF(green);
        cc.setBlueF(blue);
        ctable.push_back(cc.rgb());
    }
    return ctable;
}

void QColorRampEditor::onColorClicked(double value, QColor color)
{
    qDebug()<<"Color clicked. Value: "<< value << " Color: " << color;
    //static QPoint getPositionForNormalizedValue(qreal value, qreal boundarySpace, qreal sliderHandleWidth, qreal sliderWidth, Qt::Orientation orientation);

    QPoint position = MathUtil::getPositionForNormalizedValue(value, 5, 8, 421, Qt::Horizontal);
    multiHandleSlider->addSlider(position, color);
}

void QColorRampEditor::onColorRampChanged()
{
    qDebug()<<"Slider changed";
    ColorRamp colorRamp = multiHandleSlider->getColorRamp();
    colorRampWidget->setColorRamp(colorRamp);
    colorRampWidget->update();
}

void QColorRampEditor::resizeEvent (QResizeEvent*) {
}

void QColorRampEditor::mousePressEvent(QMouseEvent* e) {
    if (e->button()== Qt::LeftButton)
    {
        QRect crec = contentsRect();
        //crec.adjust(bspace_,0,-bspace_,0);
        if (crec.contains(e->pos(), true )) // test mouse is in ramp
        {
            multiHandleSlider->addSlider(e->pos(), Qt::white);
        }
    }
}
