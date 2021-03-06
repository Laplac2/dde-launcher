/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "miniframeswitchbtn.h"
#include "../windowedframe.h"
#include "../global_util/util.h"

#include <QHBoxLayout>
#include <DGuiApplicationHelper>

DGUI_USE_NAMESPACE

MiniFrameSwitchBtn::MiniFrameSwitchBtn(QWidget *parent)
    : QWidget(parent)
    , m_textLabel(new QLabel)
    , m_enterIcon(new QLabel)
    , m_allIconLabel(new QLabel)
{
    setFocusPolicy(Qt::StrongFocus);

    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, [ = ](DGuiApplicationHelper::ColorType themeType) {
        if (DGuiApplicationHelper::LightType == themeType) {
            m_allIconLabel->setPixmap(renderSVG(":/widgets/images/all-dark.svg", QSize(24, 24)));
            m_enterIcon->setPixmap(renderSVG(":/widgets/images/enter_details_normal-dark.svg", QSize(20, 20)));
        } else {
            m_allIconLabel->setPixmap(renderSVG(":/widgets/images/all.svg", QSize(24, 24)));
            m_enterIcon->setPixmap(renderSVG(":/widgets/images/enter_details_normal.svg", QSize(20, 20)));
        }

        QPalette pa = m_textLabel->palette();
        pa.setBrush(QPalette::WindowText, pa.brightText());
        m_textLabel->setPalette(pa);
    });

    if (DGuiApplicationHelper::LightType == DGuiApplicationHelper::instance()->themeType()) {
        m_allIconLabel->setPixmap(renderSVG(":/widgets/images/all-dark.svg", QSize(24, 24)));
        m_enterIcon->setPixmap(renderSVG(":/widgets/images/enter_details_normal-dark.svg", QSize(20, 20)));
    } else {
        m_allIconLabel->setPixmap(renderSVG(":/widgets/images/all.svg", QSize(24, 24)));
        m_enterIcon->setPixmap(renderSVG(":/widgets/images/enter_details_normal.svg", QSize(20, 20)));
    }

    m_enterIcon->setFixedSize(20, 20);
    m_enterIcon->setVisible(false);

    m_allIconLabel->setFixedSize(24, 24);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    setLayout(mainLayout);
    setObjectName("MiniFrameSwitchBtn");
    setFixedHeight(36);

    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_allIconLabel);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(m_textLabel);
    mainLayout->addWidget(m_enterIcon);
    mainLayout->addSpacing(10);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
}

MiniFrameSwitchBtn::~MiniFrameSwitchBtn()
{
}

void MiniFrameSwitchBtn::updateStatus(int status)
{
    if (status == WindowedFrame::All) {
        m_textLabel->setText(tr("All Categories"));
        m_enterIcon->setVisible(true);
    } else {
        m_textLabel->setText(tr("Back"));
        m_enterIcon->setVisible(false);
    }
}

void MiniFrameSwitchBtn::click()
{
    emit clicked();
}

void MiniFrameSwitchBtn::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    if (hasFocus() || m_hover) {
        QPainterPath path;
        path.addRoundedRect(rect(), 4, 4);
        p.fillPath(path, QColor(21, 21, 21, 102));
    }
}

void MiniFrameSwitchBtn::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);

    m_hover = true;
    update();
}

void MiniFrameSwitchBtn::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

    m_hover = false;
    update();
}

void MiniFrameSwitchBtn::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);

    emit clicked();
}
