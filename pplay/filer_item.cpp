//
// Created by cpasjuste on 03/12/18.
//

#include <sstream>

#include "cross2d/c2d.h"
#include "main.h"
#include "filer_item.h"

using namespace c2d;

FilerItem::FilerItem(Main *main, const c2d::FloatRect &rect, const MediaFile &file) : RectangleShape(rect) {

    this->main = main;
    this->file = file;

    setFillColor(Color::Transparent);

    textTitle = new Text(file.name, FONT_SIZE, main->getFont());
    textTitle->setPosition(16, 4);
    textTitle->setWidth(getSize().x - 64);
    add(textTitle);

    textVideo = new Text("", FONT_SIZE - 8, main->getFont());
    textVideo->setPosition(16, 4 + FONT_SIZE + 4);
    textVideo->setWidth(getSize().x - 64);
    textVideo->setFillColor(COLOR_FONT);
    add(textVideo);

    textAudio = new Text("", FONT_SIZE - 8, main->getFont());
    textAudio->setPosition(16, textVideo->getPosition().y + FONT_SIZE - 6);
    textAudio->setWidth(getSize().x - 64);
    textAudio->setFillColor(COLOR_FONT);
    add(textAudio);
}

c2d::Text *FilerItem::getTitle() {
    return textTitle;
}

const MediaFile FilerItem::getFile() const {
    return file;
}

void FilerItem::setFile(const MediaFile &file) {

    this->file = file;

    textTitle->setString(file.name);
    uint8_t alpha = textTitle->getAlpha();
    textTitle->setFillColor(COLOR_BLUE);
    textTitle->setAlpha(alpha);

    if (!file.getMedia().videos.empty()) {
        std::ostringstream oss;
        oss << "Video: " << file.getMedia().videos[0].width << "x" << file.getMedia().videos[0].height;
        oss << ", " << file.getMedia().videos[0].codec << " @ " << file.getMedia().videos[0].rate / 1000 << " kb/s";
        textVideo->setString(oss.str());
    } else {
        textVideo->setString("");
    }

    if (!file.getMedia().audios.empty()) {
        std::ostringstream oss;
        oss << "Audio: " << file.getMedia().audios[0].codec << " @ " << file.getMedia().audios[0].rate << " hz";
        textAudio->setString(oss.str());
    } else {
        textAudio->setString("");
    }
}

void FilerItem::onDraw(c2d::Transform &transform) {
    // don't change alpha bg on tween
    setFillColor(Color::Transparent);
    Shape::onDraw(transform);
}
