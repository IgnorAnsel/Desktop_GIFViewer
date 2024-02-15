#include "gifviewer.h"


GIFViewer::GIFViewer(QWidget *parent) : QLabel(parent), scaleFactor(1.0) {
    setAcceptDrops(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(400, 400);
}

void GIFViewer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        event->accept();
    }
}

void GIFViewer::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void GIFViewer::wheelEvent(QWheelEvent *event) {
    const int delta = event->angleDelta().y();
    if (delta > 0) { // 向上滚动，放大
        scaleFactor *= 1.1; // 增加缩放比例
    } else if (delta < 0) { // 向下滚动，缩小
        scaleFactor *= 0.9; // 减少缩放比例
    }
    updateGIFSize(); // 更新 GIF 尺寸
    event->accept();
}

void GIFViewer::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void GIFViewer::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QString filePath = mimeData->urls().at(0).toLocalFile();
        loadGIF(filePath);
        event->acceptProposedAction();
        setAttribute(Qt::WA_TranslucentBackground); // 设置窗口背景为透明
    }
}

void GIFViewer::loadGIF(const QString &filePath) {
    movie = new QMovie(filePath);
    setMovie(movie);
    movie->start();
    originalSize = movie->frameRect().size(); // 存储原始 GIF 尺寸
    updateGIFSize(); // 根据当前缩放比例更新 GIF 尺寸
}

void GIFViewer::updateGIFSize() {
    QSize newSize = originalSize * scaleFactor; // 根据缩放比例计算新尺寸
    setFixedSize(newSize);
    if (movie) {
        movie->setScaledSize(newSize);
    }
}


