#ifndef GIFVIEWER_H
#define GIFVIEWER_H
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QWheelEvent>
class GIFViewer : public QLabel {
public:
    GIFViewer(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dropEvent(QDropEvent *event) override;

private:
    void loadGIF(const QString &filePath);

    void updateGIFSize();

    QMovie *movie = nullptr;
    QPoint m_dragPosition;
    QSize originalSize; // 原始 GIF 尺寸
    qreal scaleFactor; // 当前缩放比例
};
#endif // GIFVIEWER_H
